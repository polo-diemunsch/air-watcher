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

//------------------------------------------------------ Include personnel
#include "UserInterface.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void UserInterface::MainLoop ( )
// Algorithme :
//
{
    // TODO menus and stuff
    
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
UserInterface::UserInterface ( const string & datasetPath, double relativeDifferenceAllowed )
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
