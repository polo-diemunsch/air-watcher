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
#include "Analyzer.h"

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

    Analyzer analyzer(sensorsPath, attributesPath, measurementsPath,
                      privateIndividualsPath, cleanersPath, providersPath);
    
    for (const Attribute & attribute : analyzer.GetMeasurementsAttributes())
    {
        cout << attribute << endl;
    }
    cout << analyzer.GetMeasurementsAttributes().size() << " measurements attributes" << endl;

    long measurementsCount = 0;
    for (const Sensor & sensor : analyzer.GetSensors())
    {
        cout << sensor << endl;
        for (const auto& measurementsWithAttribute : sensor.GetMeasurements())
        {
            measurementsCount += measurementsWithAttribute.second.size();
        }
    }
    cout << analyzer.GetSensors().size() << " sensors\n"
         << measurementsCount << " measurements" << endl;

    return EXIT_SUCCESS;
} //----- fin de main