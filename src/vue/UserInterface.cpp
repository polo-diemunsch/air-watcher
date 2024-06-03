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
int role = 0;

//----------------------------------------------------------------- Fonctions utilisées pour l'affichage
void menuGA()
// Algorithme :
//
{
    cout << "\n";
    if (!role)
    {
        cout << "You have chosen Government Agency\n\n";
        cout << "You can now :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Check Functioning Of All Sensors\n";
    cout << "\t4. Check Functioning Of A Specific Sensors\n";
    cout << "\t5. Check Reliability of Private Induviduals\n";
    cout << "\t0. Exit" << endl;
}

void menuPr()
// Algorithme :
//
{
    cout << "\n";
    if (!role)
    {
        cout << "You have chosen Provider\n\n";
        cout << "You can now :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Consult radius of cleaned zone\n";
	cout << "\t4. Consult air quality improvement level\n";
    cout << "\t0. Exit" << endl;
}

void menuPI()
// Algorithme :
//
{
    cout << "\n";
    if (!role)
    {
        cout << "You have chosen Private Individual\n\n";
        cout << "You can now :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Consult Your Points\n";
    cout << "\t0. Exit" << endl;
}

time_t inputDate(bool isStartDate)
// Algorithme :
//
{
    time_t timestamp = -1;

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

string nanosecondsToDisplayableTime(chrono::nanoseconds ns)
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
void UserInterface::MainLoop()
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
                if (role == 1) // Government Agency
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

                if (role == 2) // Provider
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

                if (role == 3 && option == 3) // Private Individual && Consult Points
                {
                    consultPointsOfPrivateIndividual();
                    break;
                }
        }

        switch (role)
        {
            case 1:
                menuGA();
                break;
            case 2:
                menuPr();
                break;
            case 3:
                menuPI();
                break;
        }

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

    cout << "Loading...\n" << endl;

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

void UserInterface::chooseRole()
// Algorithme :
//
{
    string providerId;
    string privateIndividualId;

	cout << "Choose your role :\n";
	cout << "\t1. Government Agency\n";
	cout << "\t2. Provider\n";
	cout << "\t3. Private Individual\n";
    cout << "\t0. Exit\n";

	cout << "\nOnce you choose a role, you will not be able to modify it !\n" << endl;
    cin >> role;

    switch (role)
    {
        case 1 :
            menuGA();
            break;
        case 2:
        {
            cout << "Provider id (ProviderXX) :" << endl;
            cin >> providerId;
            provider = parser.GetProviderById(providerId);

            while (provider == nullptr)
            {
                cout << providerId << " not found\n" << "Provider id (ProviderXX) :" << endl;
                cin >> providerId;
                provider = parser.GetProviderById(providerId);
            }

            menuPr();
            break;
        }
        case 3:
        {
            cout << "Private Individual id (UserXX) :" << endl;
            cin >> privateIndividualId;
            privateIndividual = parser.GetPrivateIndividualById(privateIndividualId);

            while (privateIndividual == nullptr)
            {
                cout << privateIndividualId << " not found\n" << "Private Individual id (UserXX) :" << endl;
                cin >> privateIndividualId;
                privateIndividual = parser.GetPrivateIndividualById(privateIndividualId);
            }

            menuPI();
            break;
        }
        default:
            cout << "Goodbye" << endl;
            exit(0);
    }
}

void UserInterface::meanAirQuality()
// Algorithme :
//
{
    int mean;
    cout << "\nYou have chosen Consult Mean Air Quality\n\n";
    cout << "You can either :\n";
    cout << "\t1. Consult Mean Air Quality For Sensor\n";
    cout << "\t2. Consult Mean Air Quality In Area" << endl;
    cin >> mean;

    switch (mean)
    {
        case 1: // For sensor
        {
            string sensorId;
            string attribute;
            time_t startDate;
            time_t endDate;
            Sensor * sensor;

            cout << "Sensor id (SensorXX) :" << endl;
            cin >> sensorId;
            sensor = parser.GetSensorById(sensorId);

            while (sensor == nullptr)
            {
                cout << sensorId << " not found\n" << "Sensor id (SensorXX) :" << endl;
                cin >> sensorId;
                sensor = parser.GetSensorById(sensorId);
            }

            cout << "Attribute (PM10, NO2, SO2 or O3) :" << endl;
            cin >> attribute;

            cout << "Start date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
            startDate = inputDate(true);

            cout << "End Date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
            endDate= inputDate(false); 

            chrono::time_point start = chrono::steady_clock::now();
            double sensorMean = sensorAnalyzer.ComputeMeanAirQualityForSensor(sensor, attribute, startDate, endDate);
            chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

            cout << "\nAverage air quality of "<< attribute << " for " << sensorId << " between "
                 << put_time(localtime(&startDate), "%H:%M:%S %Y-%m-%d") << " and "
                 << put_time(localtime(&endDate), "%H:%M:%S %Y-%m-%d") << " is " << sensorMean
                 << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;

            break;
        } 
        case 2 : // In Area
        {
            double latitude;
            double longitude;
            double radius;
            vector<Sensor *> sensorsToExclude = {};
            string attribute;
            time_t startDate;
            time_t endDate;

            cout << "Latitude :" << endl;
            cin >> latitude;

            cout << "Longitude :" << endl;
            cin >> longitude;

            cout << "Radius (km) :" << endl;
            cin >> radius;

            cout << "Attribute (PM10, NO2, SO2 or O3) :"<< endl;
            cin >> attribute;

            cout << "Start date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
            startDate = inputDate(true);

            cout << "End date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" <<endl;
            endDate= inputDate(false); 

            chrono::time_point start = chrono::steady_clock::now();
            double areaMean = sensorAnalyzer.ComputeMeanAirQualityInArea(latitude, longitude, radius, sensorsToExclude, attribute, startDate, endDate);
            chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

            cout << "\nAverage air quality of " << attribute << " for coorinates ("
                 << latitude << ", " << longitude << ") and radius " << radius << " between "
                 << put_time(localtime(&startDate), "%H:%M:%S %Y-%m-%d") << " and "
                 << put_time(localtime(&endDate), "%H:%M:%S %Y-%m-%d") << " is " << areaMean
                 << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;

            break;
        }
    }
}

void UserInterface::rankSensors()
// Algorithme :
//
{
    cout << "\nYou have chosen Rank Sensors By Similarity\n\n";

    string sensorId;
    string attribute;
    time_t startDate;
    time_t endDate;
    Sensor * sensor;

    cout << "Sensor id (SensorXX) :" << endl;
    cin >> sensorId;
    sensor = parser.GetSensorById(sensorId);

    while (sensor == nullptr)
    {
        cout << sensorId << " not found\n" << "Sensor id (SensorXX) :" << endl;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
    }

    cout << "Attribute (PM10, NO2, SO2 or O3) :" << endl;
    cin >> attribute;

    cout << "Start date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
    startDate = inputDate(true);

    cout << "End date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" <<endl;
    endDate= inputDate(false); 

    chrono::time_point start = chrono::steady_clock::now();
    multimap<double, Sensor *> ranking = sensorAnalyzer.RankSensorsBySimilarity(sensor, attribute, startDate, endDate);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    multimap<double, Sensor *>::iterator it = ranking.begin();
    while (it != ranking.end())
    {
        cout << it->first << " : " << it->second->GetId() << endl;
        it++;
    }
    cout << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::checkFunctioningOfAllSensors()
// Algorithme :
//
{
    cout << "\nYou have chosen Check Functioning Of All Sensors\n\n";

    double radius;
    time_t startDate;
    time_t endDate;

    cout << "Radius (km) :" << endl;
    cin >> radius;

    cout << "Start date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
    startDate = inputDate(true);

    cout << "End date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
    endDate= inputDate(false);

    chrono::time_point start = chrono::steady_clock::now();
    multimap<bool, Sensor *> sensorsFunctioning = sensorAnalyzer.CheckFunctioningOfAllSensors(radius, startDate, endDate, relativeDifferenceAllowed, true);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    multimap<bool, Sensor *>::iterator it = sensorsFunctioning.begin();
    while (it != sensorsFunctioning.end())
    {
        cout << left << setw(8) << it->second->GetId() << " is " << (it->first ? "" : "not ") << "functional" << endl;
        it++;
    }
    cout << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::checkFunctioningOfASensor()
// Algorithme :
//
{
    cout << "\nYou have chosen Check Functioning Of A Specific Sensors\n\n";

    string sensorId;
    Sensor * sensor;
    double radius;
    time_t startDate;
    time_t endDate;

    cout << "Sensor id (SensorXX) :" << endl;
    cin >> sensorId;
    sensor = parser.GetSensorById(sensorId);

    while (sensor == nullptr)
    {
        cout << sensorId << " not found\n" << "Sensor id (SensorXX) :" << endl;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
    }

    cout << "Radius (km) :" << endl;
    cin >> radius;

    cout << "Start date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
    startDate = inputDate(true);

    cout << "End date (dd/mm/yyyy, HH:MM:SS dd/mm/yyyy or anything else) :" << endl;
    endDate= inputDate(false);

    chrono::time_point start = chrono::steady_clock::now();
    bool functioning = sensorAnalyzer.CheckFunctioningOfSensor(sensor, radius, startDate, endDate, relativeDifferenceAllowed, true);
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\n" << sensorId << " is" << (functioning ? "" : "not ") << "functionnal"
         << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::checkReliabilityOfPrivateIndividual()
// Algorithme :
//
{
    cout << "\nYou have chosen Check Reliability of Private Individuals\n\n";

    cout << "Functionality not implemented :'/" << endl;
}

void UserInterface::consultPointsOfPrivateIndividual()
// Algorithme :
//
{
    cout << "\nYou have chosen Consult Your Points\n\n";

    chrono::time_point start = chrono::steady_clock::now();
    cout << "You have " << privateIndividual->GetPoints() << " points" << endl;
    chrono::nanoseconds elapsed = std::chrono::steady_clock::now() - start;

    cout << "\n\nTime elapsed: " << nanosecondsToDisplayableTime(elapsed) << endl;
}

void UserInterface::radiusCleanedZone()
// Algorithme :
//
{
	cout << "\nYou have chosen Consult radius of cleaned zone\n\n";

    cout << "Functionality not implemented :'/" << endl;
}

void UserInterface::airImprovement()
// Algorithme :
//
{
	cout << "\nYou have chosen Consult air quality improvement level\n\n";

    cout << "Functionality not implemented :'/" << endl;
}

void UserInterface::consultDataset()
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
