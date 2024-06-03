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
    puts("");
    if (!role) {
        puts("You have chosen Government Agency\n");
        puts("You can now :");
    }

	puts("\t 1. Consult Mean Air Quality");
	puts("\t 2. Rank Sensors By Similarity");
	puts("\t 3. Check Functioning Of All Sensors");
    puts("\t 4. Check Functioning Of A Specific Sensors");
    puts("\t 5. Check Reliability of Private Induviduals");
    puts("\t 0. Exit");
}

void menuPr()
{
    puts("");
    if (!role) {
        puts("You have chosen Provider\n");
        puts("You can now :");
    }

	puts("\t 1. Consult Mean Air Quality");
	puts("\t 2. Rank Sensors By Similarity");
	puts("\t 3. Consult radius of cleaned zone");
	puts("\t 4. Consult air quality improvement level");
    puts("\t 0. Exit");
}

void menuPI()
{
    puts("");
    if (!role) {
        puts("You have chosen Private Individual\n");
        puts("You can now :");
    }
    
	//a tout les appels
	puts("\t 1. Consult Mean Air Quality");
	puts("\t 2. Rank Sensors By Similarity");
	puts("\t 3. Consult your points");
    puts("\t 0. Exit");
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
    puts("\nAirWatcher : it all starts with air\n");

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

    parser = Parser(sensorsPath, attributesPath, measurementsPath,
                    privateIndividualsPath, cleanersPath, providersPath);
        
    sensors = parser.GetSensors();

    vector<Sensor *> sensorsPointers;
    sensorsPointers.reserve(sensors.size());

    for (Sensor & sensor : sensors)
    {
        sensorsPointers.push_back(&sensor);
    }

    cout << endl;

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
    string ProviderId;
    string PrivateIndividualId;

	puts("Choose your role :");
	puts("\t 1. Government Agency");
	puts("\t 2. Provider ");
	puts("\t 3. Private Individual");
    puts("\t 0. Exit");
    
	puts("\nOnce you choose a role, you will not be able to modify it !\n");
    cin >> role;
    
    switch (role)
    {
        case 1 :
            menuGA();
            break;
        case 2:
            cout << "Provider id (Providerxx) :" << endl;
            cin >> ProviderId;
            provider = parser.GetProviderById(ProviderId);
            menuPr();
            break;
        case 3:
            cout << "Private Individual id (Userxx) :" << endl;
            cin >> PrivateIndividualId;
            privateIndividual = parser.GetPrivateIndividualById(PrivateIndividualId);
            menuPI();
            break;
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
    puts("\nYou have chosen Consult Mean Air Quality\n");
    puts("You can either :");
    puts("\t 1. Consult Mean Air Quality For Sensor");
    puts("\t 2. Consult Mean Air Quality In Area");
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
            
            cout << "Sensor id (Sensorxx): " << endl;
            cin >> sensorId;
            sensor = parser.GetSensorById(sensorId);

            cout << "Attribute (PM10, NO2, SO2 or O3): " << endl;
            cin >> attribute;
                                        
            cout << "Date de début (HH:MM:ss dd/mm/yyyy) : " << endl;
            startDate = inputDate();
            
            cout << "Date de fin (HH:MM:ss dd/mm/yyyy) : " << endl;
            endDate= inputDate(); 
            
            double sensorMean = sensorAnalyzer.ComputeMeanAirQualityForSensor(sensor, attribute, startDate, endDate);

            cout << "\nAverage air quality of "<< attribute << " for " << sensorId << " between " << ctime(&startDate) << " and " << ctime(&endDate) << " is " << sensorMean << endl;

            break;
        } 
        case 2 : //In Area
        {
            double latitude;
            double longitude;
            double radius;
            vector<Sensor *> sensorsToExclude = {};
            string attribute;
            time_t startDate;
            time_t endDate;
            
            cout << "Latitude : " << endl;
            cin >> latitude;

            cout << "Longitude :  " << endl;
            cin >> longitude;

            cout << "Radius (km):  " << endl;
            cin >> radius;

            cout << "Attribute (PM10, NO2, SO2 or O3): "<< endl;
            cin >> attribute;
            
            cout << "Start date (HH:MM:ss dd/mm/yyyy) : " << endl;
            startDate = inputDate();
            
            cout << "End date (HH:MM:ss dd/mm/yyyy) : " <<endl;
            endDate= inputDate(); 

            double areaMean = sensorAnalyzer.ComputeMeanAirQualityInArea (latitude, longitude, radius, sensorsToExclude, attribute, startDate, endDate );
            
            cout << "\nAverage air quality of " << attribute << " for " << latitude << "," << longitude << " between " << ctime(&startDate) << " and " << ctime(&endDate) << " is " << areaMean << endl;

            break;
        }
    }
}

void UserInterface::rankSensors()
// Algorithme :
//
{
    puts("\nYou have chosen Rank Sensors By Similarity\n");
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
        cout << "Sensor id : (Sensorxx): " << endl;
        cin >> sensorId;
        sensor = parser.GetSensorById(sensorId);
    }

    cout << "Attribute (PM10, NO2, SO2 or O3): " << endl;
    cin >> attribute;

    cout << "Start date (HH:MM:ss dd/mm/yyyy) : " << endl;
    startDate = inputDate();
    cout << "End date (HH:MM:ss dd/mm/yyyy) : " <<endl;
    endDate= inputDate(); 

    puts("début ranking");
    multimap<double, Sensor *> ranking = sensorAnalyzer.RankSensorsBySimilarity (sensor, attribute, startDate, endDate);
    puts("fin ranking");
    multimap<double, Sensor *>::iterator it = ranking.begin();
    it++;
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
    puts("\nYou have chosen Check Functioning Of All Sensors\n");
    double radius;
    time_t startDate;
    time_t endDate;
    cout << "Radius (km) : " << endl;
    cin >> radius;

    cout << "Start date (HH:MM:ss dd/mm/yyyy) : " << endl;
    startDate = inputDate();
    cout << "End date (HH:MM:ss dd/mm/yyyy) : " << endl;
    endDate= inputDate(); 
    multimap<bool, Sensor *> sensorsFunctioning = sensorAnalyzer.CheckFunctioningOfAllSensors(radius, startDate, endDate, relativeDifferenceAllowed, true); // TODO true à modifier

    multimap<bool, Sensor *>::iterator it = sensorsFunctioning.begin();
    string val;
    puts("");
    it++;
    while (it != sensorsFunctioning.end())
    {
        if (it->first)
        {
            val = "functionnal";
        }
        else 
        {
            val = "not functionnal";
        }

        cout << left << setw(8) << it->second->GetId() << " is " << val << endl;
        it++;
    }
}

void UserInterface::checkFunctioningOfASensor()
// Algorithme :
//
{
    puts("\nYou have chosen Check Functioning Of A Specific Sensors\n");
    string sensorId;
    Sensor * sensor;
    double radius;
    time_t startDate;
    time_t endDate;

    cout << "Sensor id (Sensorxx): " << endl;
    cin >> sensorId;
    sensor = parser.GetSensorById(sensorId);
    cout << "Radius (km) : " << endl;
    cin >> radius;
    cout << "Start date (HH:MM:ss dd/mm/yyyy) : " << endl;
    startDate = inputDate();
    cout << "End date (HH:MM:ss dd/mm/yyyy) : " << endl;
    endDate= inputDate(); 
    bool value = sensorAnalyzer.CheckFunctioningOfSensor(sensor, radius, startDate, endDate, relativeDifferenceAllowed, true);
    if (value)
    {
        cout << "\n" << sensorId << " is functionnal " << endl;
    }
    else 
    {
        cout << "\n" << sensorId << " is not functionnal " << endl;
    }
}

void UserInterface::checkReliabilityOfPrivateIndividual()
// Algorithme :
//
{
    puts("\nYou have chosen Check Reliability of Private Induviduals\n");
                        
    for (const PrivateIndividual & privateIndividual : parser.GetPrivateIndividuals())
    {
        if (privateIndividual.GetIsReliable())
        {
            cout << privateIndividual.GetId() << " is reliable" << endl;
        }
        else 
        {
            cout << privateIndividual.GetId() << " is not reliable" << endl;
        }
    }
}

void UserInterface::consultPointsOfPrivateIndividual()
// Algorithme :
//
{
    puts("\nYou have chosen Consult points\n");

    for (const PrivateIndividual & privateIndividual : parser.GetPrivateIndividuals())
    {
        cout << privateIndividual.GetId() << " has " << privateIndividual.GetPoints() << " points" << endl;
    }
}

void UserInterface::radiusCleanedZone()
// Algorithme :
//
{
	puts("\nYou have chosen Consult radius of cleaned zone\n");
    
	puts("Air cleaner 1 cleaned a radius of xx km.");
	puts("Air cleaner 2 cleaned a radius of yy km.");
}

void UserInterface::airImprovement()
// Algorithme :
//
{
	puts("\nYou have chosen Consult air quality improvement level\n");
    
	puts("Air cleaner 1 improved air quality by xx%");
	puts("Air cleaner 2 improved air quality by yy%");
}

void UserInterface::consultDataset()
// Algorithme :
//
{
    puts("\nYou have chosen the secret option : Consult Dataset\n");
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
