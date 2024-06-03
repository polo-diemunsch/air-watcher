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

using namespace std;

//------------------------------------------------------ Include personnel
#include "UserInterface.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
int role = 0;

//----------------------------------------------------------------- Fonctions utilisées pour l'affichage
void menuGA()
{
    cout << "\n";
    if (!role) {
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
{
    cout << "\n";
    if (!role) {
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
{
    cout << "\n";
    if (!role) {
        cout << "You have chosen Private Individual\n\n";
        cout << "You can now :\n";
    }

	cout << "\t1. Consult Mean Air Quality\n";
	cout << "\t2. Rank Sensors By Similarity\n";
	cout << "\t3. Consult Your Points\n";
    cout << "\t0. Exit" << endl;
}

time_t inputDate()
{
    // TODO
    time_t timestamp;
    tm time = {};

    cin >> get_time(&time, "%T %d/%m/%Y");
    /*
    cout<<"year : "<<time.tm_year<<" month : "<<time.tm_mon<<" day : "<<time.tm_mday<<endl;
    cout<<"hrs : "<<time.tm_hour<<" min : "<<time.tm_min<<" ss : "<<time.tm_sec<<endl;
    */
    // Convert to time_t
    timestamp = mktime(&time);

    return timestamp;
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
    parser.Parse(sensorsPath, attributesPath, measurementsPath, privateIndividualsPath, cleanersPath, providersPath);

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
            cout << "Provider id (Providerxx) :" << endl;
            cin >> providerId;
            provider = parser.GetProviderById(providerId);

            while (provider == nullptr)
            {
                cout << providerId << " not found\n" << "Provider id (Providerxx) :" << endl;
                cin >> providerId;
                provider = parser.GetProviderById(providerId);
            }

            menuPr();
            break;
        }
        case 3:
        {
            cout << "Private Individual id (Userxx) :" << endl;
            cin >> privateIndividualId;
            privateIndividual = parser.GetPrivateIndividualById(privateIndividualId);

            while (privateIndividual == nullptr)
            {
                cout << privateIndividualId << " not found\n" << "Private Individual id (Userxx) :" << endl;
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

            cout << "Sensor id (Sensorxx) :" << endl;
            cin >> sensorId;
            sensor = parser.GetSensorById(sensorId);

            while (sensor == nullptr)
            {
                cout << sensorId << " not found\n" << "Sensor id (Sensorxx) :" << endl;
                cin >> sensorId;
                sensor = parser.GetSensorById(sensorId);
            }

            cout << "Attribute (PM10, NO2, SO2 or O3) :" << endl;
            cin >> attribute;
                                        
            cout << "Date de début (HH:MM:ss dd/mm/yyyy) :" << endl;
            startDate = inputDate();
            
            cout << "Date de fin (HH:MM:ss dd/mm/yyyy) :" << endl;
            endDate= inputDate(); 
            
            double sensorMean = sensorAnalyzer.ComputeMeanAirQualityForSensor(sensor, attribute, startDate, endDate);

            cout << "\nAverage air quality of "<< attribute << " for " << sensorId << " between " << ctime(&startDate) << " and " << ctime(&endDate) << " is " << sensorMean << endl;

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
            
            cout << "Start date (HH:MM:ss dd/mm/yyyy) :" << endl;
            startDate = inputDate();
            
            cout << "End date (HH:MM:ss dd/mm/yyyy) :" <<endl;
            endDate= inputDate(); 

            double areaMean = sensorAnalyzer.ComputeMeanAirQualityInArea(latitude, longitude, radius, sensorsToExclude, attribute, startDate, endDate);
            
            cout << "\nAverage air quality of " << attribute << " for " << latitude << "," << longitude << " between " << ctime(&startDate) << " and " << ctime(&endDate) << " is " << areaMean << endl;

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

    cout << "Sensor id (Sensorxx) :" << endl;
    cin >> sensorId;
    sensor = parser.GetSensorById(sensorId);

    while (sensor == nullptr)
    {
        cout << sensorId << " not found\n" << "Sensor id (Sensorxx) :" << endl;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
    }

    cout << "Attribute (PM10, NO2, SO2 or O3) :" << endl;
    cin >> attribute;

    cout << "Start date (HH:MM:ss dd/mm/yyyy) :" << endl;
    startDate = inputDate();
    cout << "End date (HH:MM:ss dd/mm/yyyy) :" <<endl;
    endDate= inputDate(); 

    multimap<double, Sensor *> ranking = sensorAnalyzer.RankSensorsBySimilarity(sensor, attribute, startDate, endDate);

    multimap<double, Sensor *>::iterator it = ranking.begin();
    while (it != ranking.end())
    {
        cout << it->first << " : " << it->second->GetId() << endl;
        it++;
    }
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

    cout << "Start date (HH:MM:ss dd/mm/yyyy) : " << endl;
    startDate = inputDate();
    cout << "End date (HH:MM:ss dd/mm/yyyy) : " << endl;
    endDate= inputDate();

    multimap<bool, Sensor *> sensorsFunctioning = sensorAnalyzer.CheckFunctioningOfAllSensors(radius, startDate, endDate, relativeDifferenceAllowed, true);

    multimap<bool, Sensor *>::iterator it = sensorsFunctioning.begin();

    while (it != sensorsFunctioning.end())
    {
        cout << left << setw(8) << it->second->GetId() << " is " << (it->first ? "" : "not ") << "functional" << endl;
        it++;
    }
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

    cout << "Sensor id (Sensorxx) :" << endl;
    cin >> sensorId;
    sensor = parser.GetSensorById(sensorId);

    while (sensor == nullptr)
    {
        cout << sensorId << " not found\n" << "Sensor id (Sensorxx) :" << endl;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
    }

    cout << "Radius (km) : " << endl;
    cin >> radius;

    cout << "Start date (HH:MM:ss dd/mm/yyyy) : " << endl;
    startDate = inputDate();
    cout << "End date (HH:MM:ss dd/mm/yyyy) : " << endl;
    endDate= inputDate();

    bool functioning = sensorAnalyzer.CheckFunctioningOfSensor(sensor, radius, startDate, endDate, relativeDifferenceAllowed, true);
    cout << "\n" << sensorId << " is" << (functioning ? "" : "not ") << "functionnal" << endl;
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

    cout << "You have " << privateIndividual->GetPoints() << " points" << endl;
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
}
