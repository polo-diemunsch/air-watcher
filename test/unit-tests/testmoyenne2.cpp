using namespace std;
#include <iostream>

#include "../../src/service/SensorAnalyzer.h"
#include "../../src/model/Sensor.h"
#include "../../src/data/Parser.h"
#include "../../src/model/Attribute.h"
#include "../../src/model/Measurement.h"
#include <functional>

#include <vector>

const Attribute O3("O3", "µg/m3", "ozone concentration");
const Attribute SO2("SO2", "µg/m3", "sulphur dioxide concentration");
const Attribute NO2("NO2", "µg/m3", "nitrogen dioxide concentration");
const Attribute PM10("PM10", "µg/m3", "particulate matter concentration");

Measurement measurement0(1000, &O3, 42); //sensor0
Measurement measurement1(1100, &SO2, 76); //sensor0
Measurement measurement2(500, &O3, 35); //sensor2
Measurement measurement3(1400, &O3, 61); //sensor1
Measurement measurement4(1200, &O3, 67); //sensor1
Measurement measurement5(1000, &NO2, 47); //sensor0
Measurement measurement6(1300, &SO2, 22); //sensor2


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

    SensorAnalyzer sensorAnalyzer = SensorAnalyzer(sensors);
    return sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 20, {}, "O3", 0, 2000); //test classique -> 56.6 attendu
}

double test_temps()
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
    return sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 20, {}, "O3", 0, 1200); //test periode 0-1200 -> 54.5 attendu
}

double test_null()
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
    return sensorAnalyzer.ComputeMeanAirQualityInArea(100, 100, 20, {}, "O3", 0, 1200); //test zone non couverte -> 0 attendu
}

double test_exclusion()
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
    return sensorAnalyzer.ComputeMeanAirQualityInArea(0, 0, 100, {sensor2}, "SO2", 0, 2000); //test zone non couverte -> 76 attendu
}

int main()
{
    double val;

    val = test_classique();
    cout << "valeur du test classique : " << val << endl;

    val = test_null();
    cout << "valeur du test null : " << val << endl;

    val = test_temps();
    cout << "valeur du test temps : " << val << endl;

    val = test_exclusion();
    cout << "valeur du test exclu : " << val << endl;

    //Calcul de la moyenne des capteurs dans une période donnée 
    //et une aire donnée

    //Calcul de la moyenne dans une zone sans capteurs

    //Calcul de la moyenne où on exclut des calculs un sensor

    //test particuliers non fiables à faire

    return EXIT_SUCCESS;
}
