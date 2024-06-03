/*************************************************************************
                           UserInterface  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <UserInterface> (fichier UserInterface.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <cmath>

using namespace std;

//------------------------------------------------------ Include personnel
#include "UserInterface.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------------------- Fonctions utilisées pour l'affichage
time_t inputDate( bool isStartDate )
// Algorithme :
//
{
    time_t timestamp = -1;

    cout << (isStartDate ? "Start" : "End") << " Date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :\n";
    cout << "> " << flush;

    cin.ignore();
    if (cin.peek() != '\n')
    {
        string date;
        istringstream dateStringStream;
        tm tm;

        getline(cin, date);

        const vector<string> formats{"%d/%m/%Y", "%H:%M:%S%t%d/%m/%Y"};

        size_t i = 0;
        while (timestamp == -1 && i < formats.size())
        {
            dateStringStream = istringstream(date);
            dateStringStream >> get_time(&tm, formats[i].c_str());

            if (dateStringStream)
            {
                timestamp = mktime(&tm);
            }

            i++;
        }
    }

    if (timestamp == -1)
    {
        timestamp = isStartDate ? 0 : time(nullptr);
    }

    return timestamp;
}

string nanosecondsToDisplayableTime( chrono::nanoseconds ns )
// Algorithme :
//
{
    vector<string> units{"ns", "µs", "ms", "s"};

    chrono::nanoseconds::rep count = ns.count();

    size_t i = 0;
    double ajustedCount = count;
    while (ajustedCount > 1000 && i < units.size())
    {
        i++;
        ajustedCount = count / pow(1000.0, i);
    }

    stringstream ss;
    ss.precision(4);
    ss << ajustedCount;
    return ss.str() + units[i];
}

//----------------------------------------------------- Méthodes publiques
void UserInterface::MainLoop( )
// Algorithme :
//
{
    cout << "\nAirWatcher : it all starts with air\n\n";

    chooseRole();

    int option = 1;
    cin >> option;
    while (option) 
    {
        switch (option)
        {
            case 1: // Calcul de la qualité moyenne de l'air
                meanAirQuality();
                break;
            case 2:
                rankSensors();
                break;
            default :
                if (role == GOVERNMENT_AGENCY) // Government Agency
                {
                    switch (option) 
                    {
                        case 3:
                            checkFunctioningOfAllSensors();
                            break;
                        case 4:
                            checkFunctioningOfASensor();
                            break;
                        case 5:
                            checkReliabilityOfPrivateIndividual();
                            break;
                        case 7:
                            consultDataset();
                            break;
                    }
                }

                if (role == PROVIDER) // Provider
                {
                    switch (option) 
                    {
                        case 3:
                            radiusCleanedZone();
                            break;
                        case 4:
                            airImprovement();
                            break;
                    }
                }

                if (role == PRIVATE_INDIVIDUAL && option == 3) // Private Individual && Consult Points
                {
                    consultPointsOfPrivateIndividual();
                    break;
                }
        }

        switch (role)
        {
            case GOVERNMENT_AGENCY:
                menuGovernmentAgency();
                break;
            case PROVIDER:
                menuProvider();
                break;
            case PRIVATE_INDIVIDUAL:
                menuPrivateIndividual();
                break;
        }

        cout << "> " << flush;
        cin >> option;
    }
} //----- Fin de MainLoop


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
UserInterface::UserInterface ( const string & datasetPath, double relativeDifferenceAllowed, double defaultRadius ) :
relativeDifferenceAllowed(relativeDifferenceAllowed), defaultRadius(defaultRadius)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UserInterface>" << endl;
#endif
    const string sensorsPath = datasetPath + "/sensors.csv";
    const string attributesPath = datasetPath + "/attributes.csv";
    const string measurementsPath = datasetPath + "/measurements.csv";
    const string privateIndividualsPath = datasetPath + "/users.csv";
    const string cleanersPath = datasetPath + "/cleaners.csv";
    const string providersPath = datasetPath + "/providers.csv";

    parser = Parser();

    cout << "\nLoading...\n" << endl;

    chrono::time_point start = chrono::steady_clock::now();
    parser.Parse(sensorsPath, attributesPath, measurementsPath, privateIndividualsPath, cleanersPath, providersPath);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "Done Loading" << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;

    sensors = parser.GetSensors();

    vector<Sensor *> sensorsPointers;
    sensorsPointers.reserve(sensors.size());

    for (Sensor & sensor : sensors)
    {
        sensorsPointers.push_back(&sensor);
    }

    sensorAnalyzer = SensorAnalyzer(sensorsPointers);
} //----- Fin de UserInterface


UserInterface::~UserInterface ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UserInterface>" << endl;
#endif
} //----- Fin de ~UserInterface


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void UserInterface::chooseRole( )
// Algorithme :
//
{
    string providerId;
    string privateIndividualId;
    int roleCode;

	cout << "Choose your role :\n";
	cout << "\t1. Government Agency\n";
	cout << "\t2. Provider\n";
	cout << "\t3. Private Individual\n";
    cout << "\t0. Exit\n";

	cout << "\nOnce you choose a role, you will not be able to modify it !\n";

    cout << "> " << flush;
    cin >> roleCode;

    switch (roleCode)
    {
        case 1:
            role = GOVERNMENT_AGENCY;
            menuGovernmentAgency(true);
            break;
        case 2:
        {
            role = PROVIDER;

            do
            {
                cout << "Provider id (ProviderXX) :\n";
                cout << "> " << flush;
                cin >> providerId;
                provider = parser.GetProviderById(providerId);
                if (provider == nullptr)
                {
                    cout << providerId << " not found" << endl; 
                }
            } while (provider == nullptr);

            menuProvider(true);
            break;
        }
        case 3:
        {
            role = PRIVATE_INDIVIDUAL;

            do
            {
                cout << "Private Individual id (UserXX) :\n";
                cout << "> " << flush;
                cin >> privateIndividualId;
                privateIndividual = parser.GetPrivateIndividualById(privateIndividualId);
                if (privateIndividual == nullptr)
                {
                    cout << privateIndividualId << " not found" << endl;
                }
            } while (privateIndividual == nullptr);

            menuPrivateIndividual(true);
            break;
        }
        default:
            cout << "Goodbye" << endl;
            exit(0);
    }
}

void UserInterface::menuGovernmentAgency( bool firstTime )
// Algorithme :
//
{
    cout << "\n";
    if (firstTime)
    {
        cout << "You have chosen Government Agency\n\n";
        cout << "You can now :\n";
    }
    else
    {
        cout << "Menu :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Check Functioning Of All Sensors\n";
    cout << "\t4. Check Functioning Of A Specific Sensors\n";
    cout << "\t5. Check Reliability of Private Individuals\n";
    cout << "\t0. Exit\n";
}

void UserInterface::menuProvider( bool firstTime )
// Algorithme :
//
{
    cout << "\n";
    if (firstTime)
    {
        cout << "You have chosen Provider\n\n";
        cout << "You can now :\n";
    }
    else
    {
        cout << "Menu :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Consult radius of cleaned zone\n";
	cout << "\t4. Consult air quality improvement level\n";
    cout << "\t0. Exit\n";
}

void UserInterface::menuPrivateIndividual( bool firstTime )
// Algorithme :
//
{
    cout << "\n";
    if (firstTime)
    {
        cout << "You have chosen Private Individual\n\n";
        cout << "You can now :\n";
    }
    else
    {
        cout << "Menu :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Consult Your Points\n";
    cout << "\t0. Exit\n";
}

void UserInterface::meanAirQuality( )
// Algorithme :
//
{
    int mean;
    cout << "\nYou have chosen Consult Mean Air Quality\n\n";
    cout << "You can either :\n";
    cout << "\t1. Consult Mean Air Quality For Sensor\n";
    cout << "\t2. Consult Mean Air Quality In Area\n";

    cout << "> " << flush;
    cin >> mean;

    switch (mean)
    {
        case 1: // For sensor
        {
            string sensorId;
            string attributeId;
            time_t startDate;
            time_t endDate;
            Sensor * sensor;
            Attribute * attribute;

            do
            {
                cout << "Sensor id (SensorXX) :\n";
                cout << "> " << flush;
                cin >> sensorId;
                sensor = parser.GetSensorById(sensorId);
                if (sensor == nullptr)
                {
                    cout << sensorId << " not found" << endl;
                }
            } while (sensor == nullptr);

            do
            {
                cout << "Attribute (PM10, NO2, SO2 or O3) :\n";
                cout << "> " << flush;
                cin >> attributeId;
                attribute = parser.GetAttributeById(attributeId);
                if (attribute == nullptr)
                {
                    cout << attributeId << " not found" << endl;
                }
            } while (attribute == nullptr);

            startDate = inputDate(true);

            endDate= inputDate(false); 

            chrono::time_point start = chrono::steady_clock::now();
            double sensorMean = sensorAnalyzer.ComputeMeanAirQualityForSensor(sensor, attributeId, startDate, endDate);
            chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

            cout << "\nAverage air quality of "<< attributeId << " for " << sensorId << " between "
                 << put_time(localtime(&startDate), "%H:%M:%S %d/%m/%Y") << " and "
                 << put_time(localtime(&endDate), "%H:%M:%S %d/%m/%Y") << " is "
                 << sensorMean << attribute->GetUnit()
                 << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;

            break;
        } 
        case 2: // In Area
        {
            double latitude;
            double longitude;
            double radius;
            vector<Sensor *> sensorsToExclude = {};
            string attributeId;
            time_t startDate;
            time_t endDate;
            Attribute * attribute;

            cout << "Latitude :\n";
            cout << "> " << flush;
            cin >> latitude;

            cout << "Longitude :\n";
            cout << "> " << flush;
            cin >> longitude;

            cout << "Radius (km) :\n";
            cout << "> " << flush;
            cin >> radius;

            do
            {
                cout << "Attribute (PM10, NO2, SO2 or O3) :\n";
                cout << "> " << flush;
                cin >> attributeId;
                attribute = parser.GetAttributeById(attributeId);
                if (attribute == nullptr)
                {
                    cout << attributeId << " not found" << endl;
                }
            } while (attribute == nullptr);

            startDate = inputDate(true);

            endDate= inputDate(false); 

            chrono::time_point start = chrono::steady_clock::now();
            double areaMean = sensorAnalyzer.ComputeMeanAirQualityInArea(latitude, longitude, radius, sensorsToExclude, attributeId, startDate, endDate);
            chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

            cout << "\nAverage air quality of " << attributeId << " for coorinates ("
                 << latitude << ", " << longitude << ") and radius " << radius << " km between "
                 << put_time(localtime(&startDate), "%H:%M:%S %d/%m/%Y") << " and "
                 << put_time(localtime(&endDate), "%H:%M:%S %d/%m/%Y") << " is "
                 << areaMean << attribute->GetUnit()
                 << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;

            break;
        }
    }
}

void UserInterface::rankSensors( )
// Algorithme :
//
{
    cout << "\nYou have chosen Rank Sensors By Similarity\n\n";

    string sensorId;
    string attributeId;
    time_t startDate;
    time_t endDate;
    Sensor * sensor;
    Attribute * attribute;

    do
    {
        cout << "Sensor id (SensorXX) :\n";
        cout << "> " << flush;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
        if (sensor == nullptr)
        {
            cout << sensorId << " not found" << endl;
        }
    } while (sensor == nullptr);

    do
    {
        cout << "Attribute (PM10, NO2, SO2 or O3) :\n";
        cout << "> " << flush;
        cin >> attributeId;
        attribute = parser.GetAttributeById(attributeId);
        if (attribute == nullptr)
        {
            cout << attributeId << " not found" << endl;
        }
    } while (attribute == nullptr);

    startDate = inputDate(true);

    endDate= inputDate(false); 

    chrono::time_point start = chrono::steady_clock::now();
    multimap<double, Sensor *> ranking = sensorAnalyzer.RankSensorsBySimilarity(sensor, attributeId, startDate, endDate);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\nRanking of sensors comparing to " << sensor->GetId() << " between "
         << put_time(localtime(&startDate), "%H:%M:%S %d/%m/%Y") << " and "
         << put_time(localtime(&endDate), "%H:%M:%S %d/%m/%Y")
         << " for attribute " << attributeId << " :\n";

    multimap<double, Sensor *>::iterator it = ranking.begin();
    while (it != ranking.end())
    {
        cout << "- " << left << setw(8) << it->second->GetId() << " : " << left << setw(7) << (1 - it->first) * 100 << " % similarity" << endl;
        it++;
    }
    cout << "\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::checkFunctioningOfAllSensors( )
// Algorithme :
//
{
    cout << "\nYou have chosen Check Functioning Of All Sensors\n\n";

    time_t startDate;
    time_t endDate;

    startDate = inputDate(true);

    endDate= inputDate(false);

    chrono::time_point start = chrono::steady_clock::now();
    multimap<bool, Sensor *> sensorsFunctioning = sensorAnalyzer.CheckFunctioningOfAllSensors(defaultRadius, startDate, endDate, relativeDifferenceAllowed, true);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\nFunctionement of all sensors between "
         << put_time(localtime(&startDate), "%H:%M:%S %d/%m/%Y") << " and "
         << put_time(localtime(&endDate), "%H:%M:%S %d/%m/%Y") << " :\n";

    multimap<bool, Sensor *>::iterator it = sensorsFunctioning.begin();
    while (it != sensorsFunctioning.end())
    {
        cout << "- " << left << setw(8) << it->second->GetId() << " is " << (it->first ? "" : "not ") << "functional" << endl;
        it++;
    }
    cout << "\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::checkFunctioningOfASensor( )
// Algorithme :
//
{
    cout << "\nYou have chosen Check Functioning Of A Specific Sensors\n\n";

    string sensorId;
    Sensor * sensor;
    time_t startDate;
    time_t endDate;

    do
    {
        cout << "Sensor id (SensorXX) :\n";
        cout << "> " << flush;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
        if (sensor == nullptr)
        {
            cout << sensorId << " not found" << endl;
        }
    } while (sensor == nullptr);

    startDate = inputDate(true);

    endDate= inputDate(false);

    chrono::time_point start = chrono::steady_clock::now();
    bool functioning = sensorAnalyzer.CheckFunctioningOfSensor(sensor, defaultRadius, startDate, endDate, relativeDifferenceAllowed, true);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\n" << sensorId << " is" << (functioning ? "" : "not ") << "functionnal between "
         << put_time(localtime(&startDate), "%H:%M:%S %d/%m/%Y") << " and "
         << put_time(localtime(&endDate), "%H:%M:%S %d/%m/%Y")
         << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::checkReliabilityOfPrivateIndividual( )
// Algorithme :
//
{
    cout << "\nYou have chosen Check Reliability of Private Individuals\n\n";

    cout << "Functionality not implemented :'/" << endl;
}

void UserInterface::consultPointsOfPrivateIndividual( )
// Algorithme :
//
{
    cout << "\nYou have chosen Consult Your Points\n\n";

    chrono::time_point start = chrono::steady_clock::now();
    cout << "You have " << privateIndividual->GetPoints() << " points" << endl;
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::radiusCleanedZone( )
// Algorithme :
//
{
	cout << "\nYou have chosen Consult radius of cleaned zone\n\n";

    cout << "Functionality not implemented :'/" << endl;
}

void UserInterface::airImprovement( )
// Algorithme :
//
{
	cout << "\nYou have chosen Consult air quality improvement level\n\n";

    cout << "Functionality not implemented :'/" << endl;
}

void UserInterface::consultDataset( )
// Algorithme :
//
{
    cout << "\nYou have chosen the secret option : Consult Dataset\n\n";

    chrono::time_point start = chrono::steady_clock::now();

    for (const Attribute & attribute : parser.GetMeasurementsAttributes())
    {
        cout << attribute << endl;
    }
    cout << parser.GetMeasurementsAttributes().size() << " measurements attributes" << endl;

    long measurementsCount = 0;
    for (const Sensor & sensor : parser.GetSensors())
    {
        cout << sensor << endl;
        for (const auto& measurementsWithAttribute : sensor.GetMeasurements())
        {
            measurementsCount += measurementsWithAttribute.second.size();
        }
    }
    cout << parser.GetSensors().size() << " sensors\n"
         << measurementsCount << " measurements" << endl;

    for (const PrivateIndividual & privateIndividual : parser.GetPrivateIndividuals())
    {
        cout << privateIndividual << endl;
    }
    cout << parser.GetPrivateIndividuals().size() << " private individuals" << endl;

    for (const Cleaner & cleaner : parser.GetCleaners())
    {
        cout << cleaner << endl;
    }
    cout << parser.GetCleaners().size() << " cleaners" << endl;

    for (const Provider & provider : parser.GetProviders())
    {
        cout << provider << endl;
    }
    cout << parser.GetProviders().size() << " providers" << endl;

    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}
