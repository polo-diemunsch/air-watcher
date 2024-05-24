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
const Measurement measurement0(1000, &O3, 42);
const Measurement measurement1(1100, &SO2, 76);
const Measurement measurement2(500, &O3, 35);
const Measurement measurement3(1400, &O3, 61);
const Measurement measurement4(1200, &O3, 67);
const Measurement measurement5(1000, &NO2, 47);
const Measurement measurement6(1300, &SO2, 22);
const Measurement measurement7(1300, &PM10, 48.75);

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
        sensorA.GetIsFunctioning() == sensorB.GetIsFunctioning();
} //----- Fin de sensorEquality

bool measurementEquality ( const Measurement & measurementA, const Measurement & measurementB )
// Algorithme :
//
{
    return attributeEquality(measurementA.GetAttribute(), measurementB.GetAttribute()) &&
        measurementA.GetTimestamp() == measurementB.GetTimestamp() &&
        measurementA.GetValue() == measurementB.GetValue();
} //----- Fin de measurementEquality

bool privateIndividualEquality ( const PrivateIndividual & privateIndividualA, const PrivateIndividual & privateIndividualB, bool testSensors = true )
// Algorithme :
//
{
    bool sameSensors = true;

    if (testSensors)
    {
        vector<Sensor> sensorsA = privateIndividualA.GetSensors();
        vector<Sensor> sensorsB = privateIndividualB.GetSensors();
        sameSensors = sensorsA.size() == sensorsB.size();
        size_t i = 0;
        while (sameSensors && i < sensorsA.size())
        {
            sameSensors = sensorEquality(sensorsA[i], sensorsB[i]);
            i++;
        }
    }

    return sameSensors &&
        privateIndividualA.GetId() == privateIndividualB.GetId() &&
        privateIndividualA.GetIsReliable() == privateIndividualB.GetIsReliable() &&
        privateIndividualA.GetPoints() == privateIndividualB.GetPoints();
} //----- Fin de privateIndividualEquality

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
                 << parserAttributes[i] << ", expected " << globalAttributes[i] << endl;
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
                 << parserSensors[i] << ", expected " << sensors[i] << endl;
        }
        localTestCount++;
    }
    if (localSuccessCount != localTestCount)
        cout << "\tSuccess ";
    cout << "[" << localSuccessCount << "/" << localTestCount << "]" << endl;
    testCount += localTestCount;
    successCount += localSuccessCount;

    cout << "\tParser Measurements tests ";
    Sensor sensorMeasurement0("Sensor0", 0, 0);
    Sensor sensorMeasurement1("Sensor1", 0, 0);
    Sensor sensorMeasurement2("Sensor2", 30, 25);
    sensorMeasurement0.AddMeasurement(measurement0);
    sensorMeasurement0.AddMeasurement(measurement1);
    sensorMeasurement0.AddMeasurement(measurement2);
    sensorMeasurement1.AddMeasurement(measurement3);
    sensorMeasurement2.AddMeasurement(measurement4);
    sensorMeasurement0.AddMeasurement(measurement5);
    sensorMeasurement2.AddMeasurement(measurement6);
    sensorMeasurement1.AddMeasurement(measurement7);
    const vector<Sensor> measurementSensors({sensorDecimalCoordinates, sensorNegativeCoordinates, sensorMeasurement2, sensorMeasurement1, sensorMeasurement0});
    localTestCount = 0;
    localSuccessCount = 0;
    for (size_t i = 0; i < parserSensors.size(); i++)
    {
        for (const Attribute& attribute : globalAttributes)
        {
            map<time_t, Measurement> parserMeasurements = parserSensors[i].GetMeasurementsWithAttribute(attribute.GetId());
            map<time_t, Measurement> measurements = measurementSensors[i].GetMeasurementsWithAttribute(attribute.GetId());
            map<time_t, Measurement>::iterator parserMeasurementsIterator = parserMeasurements.begin();
            map<time_t, Measurement>::iterator measurementsIterator = measurements.begin();

            while (parserMeasurementsIterator != parserMeasurements.end() && measurementsIterator != measurements.end())
            {
                if(measurementEquality(measurementsIterator->second, parserMeasurementsIterator->second))
                {
                    localSuccessCount++;
                }
                else
                {
                    if (localSuccessCount == localTestCount)
                        cout << "\n";
                    cout << "\t\tMeasurement Test " << localTestCount << " failed for "
                        << parserMeasurementsIterator->second << ", expected " << measurementsIterator->second << endl;
                }
                localTestCount++;
                parserMeasurementsIterator++;
                measurementsIterator++;
            }
            if (parserMeasurementsIterator == parserMeasurements.end() && measurementsIterator == measurements.end())
            {
                localSuccessCount++;
            }
            else
            {
                if (localSuccessCount == localTestCount)
                    cout << "\n";
                cout << "\t\tMeasurement Test " << localTestCount << " failed, wrong number of measurements, "
                     << "expected " << measurements.size() << " but got " << parserMeasurements.size() << endl;
            }
            localTestCount++;
        }
    }
    if (localSuccessCount != localTestCount)
        cout << "\tSuccess ";
    cout << "[" << localSuccessCount << "/" << localTestCount << "]" << endl;
    testCount += localTestCount;
    successCount += localSuccessCount;

    cout << "\tParser Private Individuals tests ";
    PrivateIndividual user0("User0");
    PrivateIndividual user1("User1");
    sensorMeasurement1.SetPrivateIndividual(&user0);
    user0.AddSensor(sensorMeasurement1);
    sensorMeasurement2.SetPrivateIndividual(&user1);
    user1.AddSensor(sensorMeasurement2);
    const vector<PrivateIndividual> privateIndividuals({user1, user0});
    localTestCount = 0;
    localSuccessCount = 0;
    vector<PrivateIndividual> parserPrivateIndividuals = parser.GetPrivateIndividuals();
    for (size_t i = 0; i < parserPrivateIndividuals.size(); i++)
    {
        if(privateIndividualEquality(privateIndividuals[i], parserPrivateIndividuals[i]))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tPrivate Individual Test " << localTestCount << " failed for "
                 << parserPrivateIndividuals[i] << ", expected " << privateIndividuals[i] << endl;
        }
        localTestCount++;
    }
    const vector<Sensor> privateIndividualSensors({sensorMeasurement2, sensorMeasurement1});
    for (size_t i = 0; i < parserPrivateIndividuals.size(); i++)
    {
        if(privateIndividualEquality(*(privateIndividualSensors[i].GetPrivateIndividual()), parserPrivateIndividuals[i], false))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tPrivate Individual Sensor Test " << localTestCount << " failed for "
                 << privateIndividualSensors[i] << ", expected private individual " << *(privateIndividualSensors[i].GetPrivateIndividual()) << endl;
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

    vector<Sensor *> sensors({&sensorMean0, &sensorMean1, &sensorMean2});
    SensorAnalyzer sensorAnalyzer(sensors);
    
    cout << "\tMean Air Quality for Sensor tests ";

    // test classique O3 sur le capteur 1 avec toutes les mesures
    expected = 64;
    got = sensorAnalyzer.ComputeMeanAirQualityForSensor(&sensorMean1, "O3", 0, 2000);
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
    got = sensorAnalyzer.ComputeMeanAirQualityForSensor(&sensorMean2, "O3", 0, 1200);
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

    sensorMean1.AddMeasurement(measurement3);
    sensorMean1.AddMeasurement(measurement4);

    sensorMean2.AddMeasurement(measurement2);
    sensorMean2.AddMeasurement(measurement6);

    vector<Sensor *> sensors({&sensorMean0, &sensorMean1, &sensorMean2});
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
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(20, 20, 4000, {&sensorMean0}, "SO2", 0, 2000);
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

    // test classique avec un capteur non pris en compte par le rayon
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

    // test periode 0-1200 avec un capteur non pris en compte par le rayon
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

    // test classique avec un sensor non fonctionnel (sensorMean0)
    sensorMean0.SetIsFunctioning(false);

    expected = 54;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(20, 20, 10000, {}, "O3", 0, 2000);
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