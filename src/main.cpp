/*************************************************************************
                           main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "data/Parser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

int main()
{
    // TODO config file
    string sensorsPath = "dataset/sensors.csv";
    string attributesPath = "dataset/attributes.csv";
    string measurementsPath = "dataset/measurements.csv";
    string privateIndividualsPath = "dataset/users.csv";
    string cleanersPath = "dataset/cleaners.csv";
    string providersPath = "dataset/providers.csv";

    Parser parser(sensorsPath, attributesPath, measurementsPath,
                      privateIndividualsPath, cleanersPath, providersPath);
    
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

    double SensorAnalyzer::ComputeMeanAirQualityInArea (const double latitude,const double longitude,const double radius,vector<Sensor> sensorsToExclude,
const string & attributeId,const time_t & startDate,const time_t & endDate)

    Sensor sensor1 = parser.GetSensors()[0];

    return EXIT_SUCCESS;
} //----- fin de main