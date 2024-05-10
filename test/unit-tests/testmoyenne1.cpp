using namespace std;
#include <iostream>

#include "../../src/service/SensorAnalyzer.h"
#include "../../src/model/Sensor.h"
#include "../../src/data/Parser.h"
#include "../../src/model/Attribute.h"
#include "../../src/model/Measurement.h"

#include <vector>

const Attribute O3("O3", "µg/m3", "ozone concentration");
const Attribute SO2("SO2", "µg/m3", "sulphur dioxide concentration");
const Attribute NO2("NO2", "µg/m3", "nitrogen dioxide concentration");
const Attribute PM10("PM10", "µg/m3", "particulate matter concentration");

Measurement measurement0(1000, &O3, 42);
Measurement measurement1(1100, &SO2, 76);
Measurement measurement2(500, &O3, 35);
Measurement measurement3(1400, &O3, 61);
Measurement measurement4(1200, &O3, 67);
Measurement measurement5(1000, &NO2, 47);
Measurement measurement6(1300, &SO2, 22);

double test_classique()
{
    Sensor sensor0 = Sensor("sensor0", 0, 0); 
    Sensor sensor1("sensor1", 0, 0);
    Sensor sensor2("sensor2", 30, 25);

    sensor0.AddMeasurement(measurement0);
    sensor0.AddMeasurement(measurement1);
    sensor0.AddMeasurement(measurement5);

    sensor2.AddMeasurement(measurement6);
    sensor2.AddMeasurement(measurement2);

    sensor1.AddMeasurement(measurement4);
    sensor1.AddMeasurement(measurement3);

    vector<Sensor> sensors = {sensor0, sensor1, sensor2};
    SensorAnalyzer sensorAnalyzer(sensors);
    return sensorAnalyzer.ComputeMeanAirQualityForSensor(sensor1, "O3", 0, 2000); //test classique O3 sur le sensor 1 avec toutes les mesures -> 64 attendu
}

double test_periode()
{
    Sensor sensor3 = Sensor("sensor3", 0, 0); 
    Sensor sensor4("sensor4", 0, 0);
    Sensor sensor5("sensor5", 30, 25);

    sensor3.AddMeasurement(measurement0);
    sensor3.AddMeasurement(measurement1);
    sensor3.AddMeasurement(measurement2);
    sensor3.AddMeasurement(measurement3);
    sensor3.AddMeasurement(measurement4);
    sensor3.AddMeasurement(measurement5);
    sensor3.AddMeasurement(measurement6);

    vector<Sensor> sensors = {sensor3, sensor4, sensor5};

    SensorAnalyzer sensorAnalyzer(sensors);
    return sensorAnalyzer.ComputeMeanAirQualityForSensor(sensor3, "O3", 0, 1200); //test classique periode 0-1200 -> 48 attendu
}

int main()
{
    double val;

    val = test_classique();
    cout << "valeur du test classique : " << val << endl;

    val = test_periode();
    cout << "valeur du test periode: " << val << endl;

    return EXIT_SUCCESS;
}
