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
#include <filesystem>

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

bool cleanerEquality ( const Cleaner & cleanerA, const Cleaner & cleanerB )
// Algorithme :
//
{
    return cleanerA.GetId() == cleanerB.GetId() &&
        cleanerA.GetLatitude() == cleanerB.GetLatitude() &&
        cleanerA.GetLongitude() == cleanerB.GetLongitude() &&
        cleanerA.GetStartDate() == cleanerB.GetStartDate() &&
        cleanerA.GetEndDate() == cleanerB.GetEndDate();
} //----- Fin de cleanerEquality

bool providerEquality ( const Provider & providerA, const Provider & providerB, bool testCleaners = true )
// Algorithme :
//
{
    bool sameCleaners = true;

    if (testCleaners)
    {
        vector<Cleaner> cleanersA = providerA.GetCleaners();
        vector<Cleaner> cleanersB = providerB.GetCleaners();
        sameCleaners = cleanersA.size() == cleanersB.size();
        size_t i = 0;
        while (sameCleaners && i < cleanersA.size())
        {
            sameCleaners = cleanerEquality(cleanersA[i], cleanersB[i]);
            i++;
        }
    }

    return sameCleaners &&
        providerA.GetId() == providerB.GetId();
} //----- Fin de providerEquality

pair<int, int> testParser(const string datasetPath)
// Algorithme :
//
{
    int testCount = 0;
    int successCount = 0;

    int localTestCount = 0;
    int localSuccessCount = 0;

    string sensorsPath = datasetPath + "/sensors.csv";
    string attributesPath = datasetPath + "/attributes.csv";
    string measurementsPath = datasetPath + "/measurements.csv";
    string privateIndividualsPath = datasetPath + "/users.csv";
    string cleanersPath = datasetPath + "/cleaners.csv";
    string providersPath = datasetPath + "/providers.csv";

    Parser parser(sensorsPath, attributesPath, measurementsPath,
        privateIndividualsPath, cleanersPath, providersPath);
    
    cout << "\tParser Measurement Attributes tests ";
    localTestCount = 0;
    localSuccessCount = 0;
    vector<Attribute> parserAttributes = parser.GetMeasurementsAttributes();
    for (size_t i = 0; i < parserAttributes.size(); i++)
    {
        if (attributeEquality(globalAttributes[i], parserAttributes[i]))
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
        if (sensorEquality(sensors[i], parserSensors[i]))
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

            if (parserMeasurementsIterator != parserMeasurements.end() && measurementsIterator != measurements.end())
            {
                while (parserMeasurementsIterator != parserMeasurements.end() && measurementsIterator != measurements.end())
                {
                    if (measurementEquality(measurementsIterator->second, parserMeasurementsIterator->second))
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
        if (privateIndividualEquality(privateIndividuals[i], parserPrivateIndividuals[i]))
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
    const vector<Sensor> privateIndividualSensors({sensorDecimalCoordinates, sensorNegativeCoordinates, sensorMeasurement2, sensorMeasurement1, sensorMeasurement0});
    for (size_t i = 0; i < parserSensors.size(); i++)
    {
        PrivateIndividual * parserSensorPrivateIndividual = parserSensors[i].GetPrivateIndividual();
        PrivateIndividual * sensorPrivateIndividual = privateIndividualSensors[i].GetPrivateIndividual();
        if (sensorPrivateIndividual == parserSensorPrivateIndividual || privateIndividualEquality(*sensorPrivateIndividual, *parserSensorPrivateIndividual, false))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tPrivate Individual Sensor Test " << localTestCount << " failed for "
                 << parserSensors[i] << ", expected private individual " << *sensorPrivateIndividual << endl;
        }
        localTestCount++;
    }
    if (localSuccessCount != localTestCount)
        cout << "\tSuccess ";
    cout << "[" << localSuccessCount << "/" << localTestCount << "]" << endl;
    testCount += localTestCount;
    successCount += localSuccessCount;

    cout << "\tParser Cleaners tests ";
    Cleaner cleaner0("Cleaner0", 42, -42, 1000, 1100);
    Cleaner cleaner1("Cleaner1", 69, 4.20, 1200, 1400);
    const vector<Cleaner> cleaners({cleaner1, cleaner0});
    localTestCount = 0;
    localSuccessCount = 0;
    vector<Cleaner> parserCleaners = parser.GetCleaners();
    for (size_t i = 0; i < parserCleaners.size(); i++)
    {
        if (cleanerEquality(cleaners[i], parserCleaners[i]))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tCleaner Test " << localTestCount << " failed for "
                 << parserCleaners[i] << ", expected " << cleaners[i] << endl;
        }
        localTestCount++;
    }
    if (localSuccessCount != localTestCount)
        cout << "\tSuccess ";
    cout << "[" << localSuccessCount << "/" << localTestCount << "]" << endl;
    testCount += localTestCount;
    successCount += localSuccessCount;

    cout << "\tParser Providers tests ";
    Provider provider0("Provider0");
    cleaner1.SetProvider(&provider0);
    provider0.AddCleaner(cleaner1);
    const vector<Provider> providers({provider0});
    localTestCount = 0;
    localSuccessCount = 0;
    vector<Provider> parserProviders = parser.GetProviders();
    for (size_t i = 0; i < parserProviders.size(); i++)
    {
        if (providerEquality(providers[i], parserProviders[i]))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tProvider Test " << localTestCount << " failed for "
                 << parserProviders[i] << ", expected " << providers[i] << endl;
        }
        localTestCount++;
    }
    const vector<Cleaner> providerCleaners({cleaner1, cleaner0});
    for (size_t i = 0; i < parserCleaners.size(); i++)
    {
        const Provider * parserCleanerProvider = parserCleaners[i].GetProvider();
        const Provider * cleanerProvider = providerCleaners[i].GetProvider();
        if (cleanerProvider == parserCleanerProvider || providerEquality(*cleanerProvider, *parserCleanerProvider, false))
        {
            localSuccessCount++;
        }
        else
        {
            if (localSuccessCount == localTestCount)
                cout << "\n";
            cout << "\t\tProvider Cleaner Test " << localTestCount << " failed for "
                 << parserCleaners[i] << ", expected provider " << *cleanerProvider << endl;
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

    double expected;
    double got;

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
    expected = 64.0;
    got = sensorAnalyzer.ComputeMeanAirQualityForSensor(&sensorMean1, "O3", 0, 2000);
    if (got == expected)
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
    expected = 48.0;
    got = sensorAnalyzer.ComputeMeanAirQualityForSensor(&sensorMean2, "O3", 0, 1200);
    if (got == expected)
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

    double expected;
    double got;

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
    expected = -1.0;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(100, 100, 20, {}, "O3", 0, 1200);
    if (got == expected)
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
    expected = 22.0;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(20, 20, 4000, {&sensorMean0}, "SO2", 0, 2000);
    if (got == expected)
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
    expected = 56.0 + 2.0 / 3.0;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 20, {}, "O3", 0, 2000);
    if (got == expected)
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
    expected = 54.5;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 20, {}, "O3", 0, 1200);
    if (got == expected)
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

    expected = 54.0 + 1.0 / 3.0;
    got = sensorAnalyzer.ComputeMeanAirQualityInArea(20, 20, 10000, {}, "O3", 0, 2000);
    if (got == expected)
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

pair<int, int> testFunctioningOfSensor()
// Algorithme :
//
{
    int testCount = 0;
    int successCount = 0;

    vector<bool> expected;
    bool got;

    Sensor sensorFunctioning0("SensorFunctioning0", 0, 0);
    Sensor sensorFunctioning1("SensorFunctioning1", 0, 0);
    Sensor sensorFunctioning2("SensorFunctioning2", 0, 0);

    sensorFunctioning0.AddMeasurement(measurement0);
    sensorFunctioning0.AddMeasurement(measurement2);

    sensorFunctioning1.AddMeasurement(measurement3);
    sensorFunctioning1.AddMeasurement(measurement4);

    vector<Sensor *> sensors({&sensorFunctioning0, &sensorFunctioning1, &sensorFunctioning2});
    SensorAnalyzer sensorAnalyzer(sensors);
    
    cout << "\tFunctioning of Sensor tests ";
    
    // Test without setting isFunctioning

    expected = vector<bool>({false, false, true});
    for (size_t i = 0; i < sensors.size(); i++)
    {
        got = sensorAnalyzer.CheckFunctioningOfSensor(sensors[i], 100, 0, 2000, 0.25, false);
        if (expected[i] == got)
        {
            successCount++;
        }
        else
        {
            if (successCount == testCount)
                cout << "\n";
            cout << "\t\tFunctioning of Sensor Test " << testCount << " failed, "
                << "expected " << expected[i] << " but got " << got << endl;
        }
        testCount++;
    }

    // Test with setting isFunctioning

    sensorFunctioning2.AddMeasurement(measurement3);
    sensorFunctioning2.AddMeasurement(measurement4);
    
    expected = vector<bool>({false, true, true});
    for (size_t i = 0; i < sensors.size(); i++)
    {
        got = sensorAnalyzer.CheckFunctioningOfSensor(sensors[i], 100, 0, 2000, 0.25, true);
        if (expected[i] == got && expected[i] == sensors[i]->GetIsFunctioning())
        {
            successCount++;
        }
        else
        {
            if (successCount == testCount)
                cout << "\n";
            cout << "\t\tFunctioning of Sensor Test " << testCount << " failed, "
                << "expected " << expected[i] << " but got " << got << endl;
        }
        testCount++;
    }

    if (successCount != testCount)
        cout << "\tSuccess ";
    cout << "[" << successCount << "/" << testCount << "]" << endl;
    
    return make_pair(successCount, testCount);
} //----- Fin de testFunctioningOfSensor

pair<int, int> testFunctioningOfAllSensors()
// Algorithme :
//
{
    int testCount = 0;
    int successCount = 0;

    multimap<bool, Sensor *> expected;
    multimap<bool, Sensor *> got;

    Sensor sensorFunctioning0("SensorFunctioning0", 0, 0);
    Sensor sensorFunctioning1("SensorFunctioning1", 0, 0);
    Sensor sensorFunctioning2("SensorFunctioning2", 0, 0);

    sensorFunctioning0.AddMeasurement(measurement0);
    sensorFunctioning0.AddMeasurement(measurement2);

    sensorFunctioning1.AddMeasurement(measurement3);
    sensorFunctioning1.AddMeasurement(measurement4);

    vector<Sensor *> sensors({&sensorFunctioning0, &sensorFunctioning1, &sensorFunctioning2});
    SensorAnalyzer sensorAnalyzer(sensors);
    
    cout << "\tFunctioning of All Sensors tests ";
    
    // Test without setting isFunctioning
    
    expected = multimap<bool, Sensor *>({{false, &sensorFunctioning0}, {false, &sensorFunctioning1}, {true, &sensorFunctioning2}});
    got = sensorAnalyzer.CheckFunctioningOfAllSensors(100, 0, 2000, 0.25, false);
    if (expected == got)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tFunctioning of All Sensors Test " << testCount << " failed" << endl;
    }
    testCount++;
    
    // Test with setting isFunctioning

    sensorFunctioning2.AddMeasurement(measurement3);
    sensorFunctioning2.AddMeasurement(measurement4);
    
    expected = multimap<bool, Sensor *>({{false, &sensorFunctioning0}, {true, &sensorFunctioning1}, {true, &sensorFunctioning2}});
    got = sensorAnalyzer.CheckFunctioningOfAllSensors(100, 0, 2000, 0.25, true);
    if (expected == got)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tFunctioning of All Sensors Test " << testCount << " failed" << endl;
    }
    testCount++;

    vector<bool> expectedIsFunctioning({false, true, true});
    for (size_t i = 0; i < sensors.size(); i++)
    {
       if (expectedIsFunctioning[i] == sensors[i]->GetIsFunctioning())
        {
            successCount++;
        }
        else
        {
            if (successCount == testCount)
                cout << "\n";
            cout << "\t\tFunctioning of All Sensors Test " << testCount << " failed" << endl;
        }
        testCount++;
    }

    if (successCount != testCount)
        cout << "\tSuccess ";
    cout << "[" << successCount << "/" << testCount << "]" << endl;
    
    return make_pair(successCount, testCount);
} //----- Fin de testFunctioningOfAllSensors

pair<int,int> testRankSensorBySimilarity()
{
    int testCount = 0;
    int successCount = 0;

    multimap<double, Sensor*> expected;
    multimap<double, Sensor*> got;

    cout << "\tRank Sensor By Similarity ";

    //TEST1 : Sensors similaires et différents
    time_t date = time(NULL) - 3;
    Sensor sensor1 = Sensor("sensor1", 0.0, 0.0);
    Sensor sensor2 = Sensor("sensor2", 0.0, 0.0);
    Sensor sensor3 = Sensor("sensor3", 0.0, 0.0);

    Attribute O3 = Attribute ( "O3", "unit", "description" );
    Attribute SO2 = Attribute ( "SO2", "unit", "description" );

    Measurement mesurement1 = Measurement ( date, &O3, 12 );
    Measurement mesurement2 = Measurement ( date, &SO2, 20 );
    Measurement mesurement3 = Measurement ( date, &O3, 11 );
    Measurement mesurement4 = Measurement ( date, &SO2, 21 );
    Measurement mesurement5 = Measurement ( date, &SO2, 10000 );

    sensor1.AddMeasurement ( mesurement1 );
    sensor1.AddMeasurement ( mesurement2 );
    sensor1.AddMeasurement ( mesurement3 );
    sensor2.AddMeasurement ( mesurement1 );
    sensor2.AddMeasurement ( mesurement4 );
    sensor3.AddMeasurement ( mesurement1 );
    sensor3.AddMeasurement ( mesurement5 );

    vector<Sensor *> sensors({&sensor1, &sensor2, &sensor3});

    SensorAnalyzer analyzer = SensorAnalyzer ( sensors );

    expected = multimap<double, Sensor*>({{1.0, &sensor2}, {9980.0, &sensor3}});
    got = analyzer.RankSensorsBySimilarity(&sensor1, "SO2", date - 30*24*60*60, date);

    /*multimap<double, Sensor *>::iterator it;

    for(it = got.begin(); it != got.end(); it++)
    {
        cout << (*it).first << ":" << (*it).second->GetId() << endl;
    }*/
    
    if (expected == got)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tRank Sensors by Similarity " << testCount << " failed" << endl;
    }
    testCount++;

    //Test 2 Il n’y a pas de sensors pour comparer

    sensors = vector<Sensor *>({&sensor1});
    analyzer = SensorAnalyzer ( sensors );
    expected = multimap<double, Sensor*>({});
    got = analyzer.RankSensorsBySimilarity(&sensor1, "SO2", date - 30*24*60*60, date);
    if (expected == got)
    {
        successCount++;
    }
    else
    {
        if (successCount == testCount)
            cout << "\n";
        cout << "\t\tRank Sensors by Similarity " << testCount << " failed" << endl;
    }
    testCount++;

    if (successCount != testCount)
            cout << "\tSuccess ";
    cout << "[" << successCount << "/" << testCount << "]" << endl;

    return make_pair(successCount, testCount);

} //----- fin de testRankSensorBySimilarity


int main(int argc, char *argv[])
{
    const string relativePathToExe = argv[0];
    const string datasetPath = filesystem::path(relativePathToExe).parent_path().string() + "/../test/dataset";

    int successCount = 0;
    int testCount = 0;
    pair<int, int> results;

    cout << "Test Parser:" << endl;
    results = testParser(datasetPath);
    successCount += results.first;
    testCount += results.second;

    cout << "\n";

    cout << "Test Mean Air Quality for Sensor:" << endl;
    results = testMeanAirQualityForSensor();
    successCount += results.first;
    testCount += results.second;

    cout << "\n";

    cout << "Test Mean Air Quality in Area:" << endl;
    results = testMeanAirQualityInArea();
    successCount += results.first;
    testCount += results.second;

    cout << "\n";

    cout << "Test Functioning of Sensor:" << endl;
    results = testFunctioningOfSensor();
    successCount += results.first;
    testCount += results.second;

    cout << "\n";

    cout << "Test Functioning of All Sensors:" << endl;
    results = testFunctioningOfAllSensors();
    successCount += results.first;
    testCount += results.second;

    cout << "\n";

    cout << "Test Rank Sensors By Similarity:" << endl;
    results = testRankSensorBySimilarity();
    successCount += results.first;
    testCount += results.second;

    cout << "\n";

    cout << "TOTAL [" << successCount << "/" << testCount << "]" << endl;

    return EXIT_SUCCESS;
} //----- Fin de main