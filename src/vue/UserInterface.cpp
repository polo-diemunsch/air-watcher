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
using namespace std;
#include <iostream>
#include <ctime>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "UserInterface.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------------------- Fonctions utilisées pour l'affichage
void choix_role() 
{
	puts("Choose your role :");
	puts("\t 1. Government Agency");
	puts("\t 2. Provider ");
	puts("\t 3. Private Individual");
    
	puts("\nOnce you choose a role, you will not be able to modify it !\n");
}

void menu_GA() 
{
	// au premier appel
	puts("\nYou have chosen Government Agency\n");
	puts("You can now : ");
    
	//a tout les appels
	puts("\t 1. Calculate air quality mean");
	puts("\t 2. Rank Sensors By Similarity");
	puts("\t 3. Consult air quality");
	puts("\t 4. Check Functioning Of All Sensors");

}

void menu_Pr() 
{
	// au premier appel
	puts("\nYou have chosen Provider\n");
	puts("You can now : ");
    
	//a tout les appels
    
	puts("\t 1. Calculate air quality mean");
	puts("\t 2. Rank Sensors By Similarity");
	puts("\t 3. Consult air quality");
	puts("\t 4. Consult radius of cleaned zone");
	puts("\t 5. Consult air quality improvement level");

}

void menu_PI() 
{
   // au premier appel
	puts("\nYou have chosen Private Individual\n");
	puts("You can now : ");
    
	//a tout les appels
	puts("\t 1. Calculate air quality mean");
	puts("\t 2. Rank Sensors By Similarity");
	puts("\t 3. Consult air quality");
	puts("\t 4. Consult your points");

}


void air_mean()
{
	puts("\nYou have chosen Calculate air quality mean\n");
	puts("In order to do so, you must provide a latitude, a longitude and a radius as well as a start date");
	puts("Latitude : 45.3");
	puts("Longitude : 1.3");
	puts("Radius (km) : 4");
	puts("Start date (dd/mm/yyyy) : 01/01/2023 "); //obligatoire
	puts("\nWould you like to add an end date ? Yes");
    
	//si pas de date de fin alors date de fin = date de debut
	puts("End date (dd/mm/yyyy) : 01/04/2023");
    
    
	puts("\nThe average air quality is : xxxxxx \n");
   
}

void ranking()
{
	puts("\nYou have chosen Rank sensors\n");
	puts("Please provide a sensor ID : xxxxxxxx ");
    
	//durée de 6 mois codée en dure
	puts("\nBased on the data generated in the last 6 months, here is a sensor ranking based on similarities to sensor xxxxxxxx : ");
   
	puts("1. sensor101");
	puts("2. sensor37");
	puts("3. sensor75");
	puts("4. ...");
}

void air_quality() 
{
	puts("\nYou have chosen Consult air quality\n");
	puts("In order to do so, you must provide a latitude and a longitude");
	puts("Latitude : 45.3");
	puts("Longitude : 1.3");
    
	puts("\nThe current air quality is xxx\n");
}

void classify_PI()
{
	puts("\nYou have chosen Classify private individuals' sensors\n");
    
	puts("\nPI 1 : reliable");
	puts("\tSensor 10 : reliable");
	puts("\tSensor 11 : reliable");
	puts("\tSensor 12 : reliable");
    
	puts("\nPI 2 : reliable");
	puts("\tSensor 20 : reliable");
    
	puts("\nPI 3 : unreliable");
	puts("\tSensor 30 : unreliable");
	puts("\tSensor 31 : reliable");
    
	puts("\nPI 4 : reliable");
	puts("\tSensor 40 : reliable");
	puts("\tSensor 41 : reliable");
}


void radius_cleaned_zone() 
{
	puts("\nYou have chosen Consult radius of cleaned zone\n");
    
	puts("Air cleaner 1 cleaned a radius of xx km.");
	puts("Air cleaner 2 cleaned a radius of x km.");
    
}

void air_improvement() 
{
	puts("\nYou have chosen Consult air quality improvement level\n");
    
	puts("Air cleaner 1 improved air quality by xx%");
	puts("Air cleaner 2 improved air quality by xx%");
}

void points()
{
	puts("\nYou have chosen Consult your points\n");
	 
	puts("You have xx points\n");
}

time_t inputDate()
{
    time_t timestamp;
    tm time = {};

    cin >> get_time(&time, "%T %m/%d/%Y");

    // Convert to time_t
    timestamp = mktime(&time);

    return timestamp;
}
//----------------------------------------------------- Méthodes publiques
void UserInterface::MainLoop ( )
// Algorithme :
//
{
    // TODO menus and stuff
    int role;
        puts("\nAirWatcher : it all starts with air\n");
        
        choix_role();
        cin>>role;
        
        switch (role) {
            case 1 :
                menu_GA();
            break;
            case 2 :
                menu_Pr();
            break;
            case 3 :
                menu_PI();
            break;
        }

        int option = 1;
        while (option) 
        {
            cin>>option;
            switch (option)
            {
                case 1:
                {
                    air_mean();
                    break;
                }
                case 2:
                {
                    puts("\nYou have chosen Rank Sensors By Similarity \n");
                    string sensorId;
                    string attribute;
                    time_t startDate;
                    time_t endDate;
                    Sensor * sensor;
                    cout << "Sensor id (Sensorxx): "<< endl;
                    cin>>sensorId;
                    sensor = parser.GetSensorById(sensorId);

                    cout << "Attribute (PM10, NO2, SO2 or O3): "<< endl;
                    cin>>attribute;
                    
                    
                    cout << "Date de début (HH:MM:ss dd/mm/yyyy) : " << endl;
                    startDate = inputDate();
                    cout << "Date de fin (HH:MM:ss dd/mm/yyyy) : " <<endl;
                    endDate= inputDate(); 

                    multimap<double, Sensor *> ranking = sensorAnalyzer.RankSensorsBySimilarity(sensor, attribute, startDate, endDate);
                    multimap<double, Sensor *>::iterator it = ranking.begin();
                    it++;
                    while (it != ranking.end())
                    {
                        cout << it->first << " : sensor n° " << it->second->GetId() << endl;
                        it++;
                    }
                    break;
                }
                case 3:
                {
                    air_quality();
                    break;
                }
                default :
                {
                    if (role == 1 && option == 4) //Government Agency && Check Functioning Of All Sensors
                    {
                        puts("\nYou have chosen Check Functioning Of All Sensors sensors\n");
                        double radius;
                        time_t startDate;
                        time_t endDate;
                        cout << "Rayon en km : "<< endl;
                        cin>>radius;
                    
                            
                        cout << "Date de début (HH:MM:ss dd/mm/yyyy) : " << endl;
                        startDate = inputDate();
                        cout << "Date de fin (HH:MM:ss dd/mm/yyyy) : " <<endl;
                        endDate= inputDate(); 
                        multimap<bool, Sensor *> sensorsFunctioning = sensorAnalyzer.CheckFunctioningOfAllSensors(radius, startDate, endDate, relativeDifferenceAllowed, true);
                        
                        multimap<bool, Sensor *>::iterator it = sensorsFunctioning.begin();
                        string val;
                        it++;
                        while (it != sensorsFunctioning.end())
                        {
                            if ((*it).first)
                            {
                                val = "functionnal";
                            }

                            else 
                            {
                                val = "not functionnal";
                            }

                            cout << "Sensor n° " << it->second->GetId() << " is " << (string) val << endl;
                            it++;
                        }
                        break;
                    }
                    if (role == 3 && option == 4) //Private Individual && Consult Points
                    {
                        puts("\nYou have chosen Consult points\n");
                        
                        for (const PrivateIndividual & privateIndividual : parser.GetPrivateIndividuals())
                        {
                            cout << privateIndividual.GetId() <<" has " << privateIndividual.GetPoints() << " points" << endl;
                        }
                        
                        break;
                    }
            
                    if (role == 2) //Provider
                    {
                        switch (option) 
                        {
                        case 4:
                            radius_cleaned_zone();
                            break;
                        case 5:
                            air_improvement();
                            break;
                        }
                    }
                }
            }

        switch (role) {
            case 1 :
                menu_GA();
            break;
            case 2 :
                menu_Pr();
            break;
            case 3 :
                menu_PI();
            break;
        }
    }

    //Test des données
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
} //----- Fin de MainLoop


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
UserInterface::UserInterface ( const string & datasetPath, double relativeDifferenceAllowed, double defaultRadius ):
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
    
    vector<Sensor> sensors = parser.GetSensors();
    vector<Sensor *> sensorsPointers;
    sensorsPointers.reserve(sensors.size());

    vector<Sensor>::iterator it = sensors.begin();
    while (it != sensors.end())
    {
        sensorsPointers.push_back(&(*it));
        it++;
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
