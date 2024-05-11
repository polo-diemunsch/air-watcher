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
#include <vector>

//------------------------------------------------------ Include personnel
#include "../../src/data/Parser.h"
#include "../../src/service/SensorAnalyzer.h"

//------------------------------------------------------------- Constantes

// Attributes
const Attribute O3("O3", "µg/m3", "ozone concentration");
const Attribute SO2("SO2", "µg/m3", "sulphur dioxide concentration");
const Attribute NO2("NO2", "µg/m3", "nitrogen dioxide concentration");
const Attribute PM10("PM10", "µg/m3", "particulate matter concentration");
const vector<Attribute> globalAttributes({PM10, NO2, SO2, O3});

// Sensors
const Sensor sensor0("Sensor0", 0, 0);
const Sensor sensor1("Sensor1", 0, 0);
const Sensor sensor2("Sensor2", 30, 25);

// Measurements
Measurement measurement0(1000, &O3, 42); //sensor0
Measurement measurement1(1100, &SO2, 76); //sensor0 
Measurement measurement2(500, &O3, 35); //sensor2
Measurement measurement3(1400, &O3, 61); //sensor1
Measurement measurement4(1200, &O3, 67); //sensor1
Measurement measurement5(1000, &NO2, 47); //sensor0
Measurement measurement6(1300, &SO2, 22); //sensor2

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
        if(attributeEquality(globalAttributes[i], parserAttributes[i]))
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
    const Sensor sensorNegativeCoordinates("SensorNegativeCoordinates", -45, -124);
    const Sensor sensorDecimalCoordinates("SensorDecimalCoordinates", 12.4, -75.873);
    const vector<Sensor> sensors({sensorDecimalCoordinates, sensorNegativeCoordinates, sensor2, sensor1, sensor0});
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

pair<int, int> testMeanAirQualityForSensor()
// Algorithme :
//
{
    int testCount = 0;
    int successCount = 0;

    int expected = 0;
    int got = 0;

    Sensor sensorMean0("SensorMean0", 0, 0);
    Sensor sensorMean1("SensorMean1", 0, 0);
    Sensor sensorMean2("SensorMean2", 40, 40);

    sensorMean0.AddMeasurement(measurement0);
    sensorMean0.AddMeasurement(measurement1);
    sensorMean0.AddMeasurement(measurement5);

    sensorMean1.AddMeasurement(measurement3);
    sensorMean1.AddMeasurement(measurement4);

    sensorMean2.AddMeasurement(measurement0);
    sensorMean2.AddMeasurement(measurement1);
    sensorMean2.AddMeasurement(measurement2);
    sensorMean2.AddMeasurement(measurement3);
    sensorMean2.AddMeasurement(measurement4);
    sensorMean2.AddMeasurement(measurement5);
    sensorMean2.AddMeasurement(measurement6);

    vector<Sensor> sensors({sensorMean0, sensorMean1, sensorMean2});
    SensorAnalyzer sensorAnalyzer(sensors);
    
    cout << "\tMean Air Quality for Sensor tests ";

    // test classique O3 sur le capteur 1 avec toutes les mesures
    expected = 64;
    got = sensorAnalyzer.ComputeMeanAirQualityForSensor(sensorMean1, "O3", 0, 2000);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality for Sensor Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    // test classique periode 0-1200
    expected = 48;
    got = sensorAnalyzer.ComputeMeanAirQualityForSensor(sensorMean2, "O3", 0, 1200);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality for Sensor Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    if (successCount != testCount)
        cout << "\tSuccess ";
    cout << "[" << successCount << "/" << testCount << "]" << endl;
    
    return make_pair(successCount, testCount);
} //----- Fin de testMeanAirQualityForSensor


pair<int, int> testMeanAirQualityInArea()
// Algorithme :
//
{
    int testCount = 0;
    int successCount = 0;

    int expected = 0;
    int got = 0;

    Sensor sensorMean0("SensorMean0", 0, 0);
    Sensor sensorMean1("SensorMean1", 0, 0);
    Sensor sensorMean2("SensorMean2", 40, 40);

    sensorMean0.AddMeasurement(measurement0);
    sensorMean0.AddMeasurement(measurement1);
    sensorMean0.AddMeasurement(measurement5);

    sensorMean2.AddMeasurement(measurement6);
    sensorMean2.AddMeasurement(measurement2);

    sensorMean1.AddMeasurement(measurement4);
    sensorMean1.AddMeasurement(measurement3);

    vector<Sensor> sensors({sensorMean0, sensorMean1, sensorMean2});
    SensorAnalyzer sensorAnalyzer(sensors);
    
    cout << "\tMean Air Quality in Area tests ";
    
    // test zone non couverte
    expected = 0;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(100, 100, 20, {}, "O3", 0, 1200);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality in Area Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    // test exclusion d'un capteur sensorMean0
    expected = 22;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(20, 20, 4000, {sensorMean0}, "SO2", 0, 2000);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality in Area Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    // test classique avec un capteur non pris en compte dû au rayon
    expected = 56;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 20, {}, "O3", 0, 2000);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality in Area Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    //test periode 0-1200 avec un capteur non pris en compte du au rayon
    expected = 54;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 20, {}, "O3", 0, 1200);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality in Area Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    //test classique avec un sensor non fonctionnel (sensorMean0)
    sensorMean0.SetIsFunctioning(false);
    
    vector<Sensor> sensors2({sensorMean0, sensorMean1, sensorMean2}); //obligatoire pour les changements de fonctionnement
    SensorAnalyzer sensorAnalyzer2(sensors2);

    expected = 54;
    got = sensorAnalyzer2.ComputeMeanAirQualityInArea(20, 20, 10000, {}, "O3", 0, 2000);
    if(got == expected)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tMean Air Quality in Area Test " << testCount << " failed, "
             << "expected " << expected << " but got " << got << endl;
    }
    testCount++;

    if (successCount != testCount)
        cout << "\tSuccess ";
    cout << "[" << successCount << "/" << testCount << "]" << endl;
    
    return make_pair(successCount, testCount);
} //----- Fin de testMeanAirQualityInArea

int main()
{
    pair<int, int> results;

    cout << "Test Parser:" << endl;
    results = testParser();

    cout << "Test Mean Air Quality for Sensor:" << endl;
    results = testMeanAirQualityForSensor();

    cout << "Test Mean Air Quality in Area:" << endl;
    results = testMeanAirQualityInArea();

    return EXIT_SUCCESS;
} //----- Fin de main