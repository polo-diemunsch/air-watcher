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
#include "../../src/data/Parser.h"

//------------------------------------------------------------- Constantes

// Attributes
const Attribute O3("O3", "µg/m3", "ozone concentration");
const Attribute SO2("SO2", "µg/m3", "sulphur dioxide concentration");
const Attribute NO2("NO2", "µg/m3", "nitrogen dioxide concentration");
const Attribute PM10("PM10", "µg/m3", "particulate matter concentration");
const vector<Attribute> attributes({PM10, NO2, SO2, O3});

//----------------------------------------------------------------- PUBLIC

bool attributeEquality ( const Attribute & attributeA, const Attribute & attributeB )
// Algorithme :
//
{
    return attributeA.GetId() == attributeB.GetId() &&
        attributeA.GetUnit() == attributeB.GetUnit() &&
        attributeA.GetDescription() == attributeB.GetDescription();
} //----- Fin de attributeEquality

bool sensorEquality ( const Sensor & sensorA, const Sensor & sensorB )
// Algorithme :
//
{
    return sensorA.GetId() == sensorB.GetId() &&
        sensorA.GetLatitude() == sensorB.GetLatitude() &&
        sensorA.GetLongitude() == sensorB.GetLongitude() &&
        // sensorA.GetPrivateIndividual() == sensorB.GetPrivateIndividual() &&
        sensorA.GetIsFunctioning() == sensorB.GetIsFunctioning();
        // TODO measurements
} //----- Fin de attributeEquality

pair<int, int> testParser()
// Algorithme :
//
{
    int testCount = 0;
    int successCount = 0;

    int localTestCount = 0;
    int localSuccessCount = 0;

    string sensorsPath = "test/data/sensors.csv";
    string attributesPath = "test/data/attributes.csv";
    string measurementsPath = "test/data/measurements.csv";
    string privateIndividualsPath = "test/data/users.csv";
    string cleanersPath = "test/data/cleaners.csv";
    string providersPath = "test/data/providers.csv";

    Parser parser(sensorsPath, attributesPath, measurementsPath,
        privateIndividualsPath, cleanersPath, providersPath);
    
    cout << "\tParser Measurement Attributes tests ";
    localTestCount = 0;
    localSuccessCount = 0;
    vector<Attribute> parserAttributes = parser.GetMeasurementsAttributes();
    for (size_t i = 0; i < parserAttributes.size(); i++)
    {
        if(attributeEquality(attributes[i], parserAttributes[i]))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tAttribute Test " << localTestCount << " failed for "
                 << parserAttributes[i] << endl;
        }
        localTestCount++;
    }
    if (localSuccessCount != localTestCount)
        cout << "\tSuccess ";
    cout << "[" << localSuccessCount << "/" << localTestCount << "]" << endl;
    testCount += localTestCount;
    successCount += localSuccessCount;
    
    cout << "\tParser Sensors tests ";
    const Sensor sensor0("sensor0", 0, 0);
    const Sensor sensor1("sensor1", 0, 0);
    const Sensor sensor2("sensor2", 123, 48);
    const Sensor sensor3("sensor3", -45, -124);
    const Sensor sensor4("sensor4", 12.4, -75.873);
    const vector<Sensor> sensors({sensor4, sensor3, sensor2, sensor1, sensor0});
    localTestCount = 0;
    localSuccessCount = 0;
    vector<Sensor> parserSensors = parser.GetSensors();
    for (size_t i = 0; i < parserSensors.size(); i++)
    {
        if(sensorEquality(sensors[i], parserSensors[i]))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tSensor Test " << localTestCount << " failed for "
                 << parserSensors[i] << endl;
        }
        localTestCount++;
    }
    if (localSuccessCount != localTestCount)
        cout << "\tSuccess ";
    cout << "[" << localSuccessCount << "/" << localTestCount << "]" << endl;
    testCount += localTestCount;
    successCount += localSuccessCount;
    
    return make_pair(successCount, testCount);
} //----- Fin de testParser

int main()
{
    pair<int, int> results;

    cout << "Test Parser:" << endl;
    results = testParser();
    cout << "Success [" << results.first << "/" << results.second << "]" << endl;

    return EXIT_SUCCESS;
} //----- fin de main