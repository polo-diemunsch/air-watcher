/*************************************************************************
                           SensorAnalyzer  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <SensorAnalyzer> (fichier SensorAnalyzer.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>

//------------------------------------------------------ Include personnel
#include "SensorAnalyzer.h"

#include "../model/PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double SensorAnalyzer::ComputeMeanAirQualityForSensor( const Sensor & sensor, const string & attributeId, time_t startDate, time_t endDate )
// Algorithme :
//
{
    /*if (sensor.GetPrivateIndividual() != NULL)
    {
        if (!sensor.GetPrivateIndividual()->GetIsReliable())
        {
            return 0;
        }
    } si on ne prend pas en compte les privates individuals non fiables*/

    vector <Measurement> mesures = sensor.GetMeasurementsWithAttributeWithinDateRange(attributeId, startDate, endDate);
    double sum = 0;
    double measurementCount = 0;

    // TODO test du private individual à faire plus tard

    for (const Measurement & mesure : mesures)
    {
        sum += mesure.GetValue();
        measurementCount++;
    }

    return (measurementCount == 0) ? 0 : (sum / measurementCount);
} //----- Fin de ComputeMeanAirQualityForSensor

double SensorAnalyzer::ComputeMeanAirQualityInArea ( const double latitude, const double longitude, const double radius,
    vector<Sensor> sensorsToExclude, const string & attributeId, const time_t & startDate, const time_t & endDate )
// Algorithme :
//
{
    double sum = 0; 
    double measurementCount = 0;

    int x1 = latitude;
    int y1 = longitude;
    
    for (const Sensor & sensor : sensors)
    {
        vector<Sensor>::iterator it = find(sensorsToExclude.begin(), sensorsToExclude.end(), sensor);
        const PrivateIndividual * privateIndividual = sensor.GetPrivateIndividual();
        if (it != sensorsToExclude.end() || !sensor.GetIsFunctioning() || (privateIndividual != nullptr && !privateIndividual->GetIsReliable()))
        {
            continue;
        }

        int x2 = sensor.GetLatitude();
        int y2 = sensor.GetLongitude();
        double sous_formule = sin(x2-x1/2) * sin(x2-x1/2) + cos(x1) * cos(x2) * sin(y2-y1/2) * sin(y2-y1/2);
        if (2 * 6371 * asin(sqrt(sous_formule)) < radius) //formule Harversine pour distance sphérique
        {
            vector <Measurement> measurements = sensor.GetMeasurementsWithAttributeWithinDateRange(attributeId, startDate, endDate);
            for (const Measurement & measurement : measurements)
            {
                sum += measurement.GetValue();
                measurementCount++;
            }
        }   
    }

    return (measurementCount == 0) ? 0 : (sum / measurementCount);
} //----- Fin de ComputeMeanAirQualityInArea

multimap<double, Sensor &> SensorAnalyzer::RankSensorsBySimilarity( const Sensor & sensorToCompareTo, const string & attributeID, const time_t timeRange )
// Algorithme :
//
{
    double meanRefrence;

    double meanDynamic;
    multimap<double, Sensor &> ranking;

    const time_t endDate = time(nullptr);
    const time_t startDate = endDate - timeRange;

    meanRefrence = ComputeMeanAirQualityForSensor(sensorToCompareTo, attributeID, startDate, endDate);

    for(Sensor & sensor : sensors)
    {
        #ifdef DEB
        cout << "Sensor: " << sensor.GetId() << endl;
        #endif

        if (sensor != sensorToCompareTo)    //  TODO private individual     && (sensor.GetPrivateIndividual() == NULL || sensor.GetPrivateIndividual()->GetIsReliable())
        {
            meanDynamic = ComputeMeanAirQualityForSensor(sensor, attributeID, startDate, endDate);            
            ranking.insert({abs(meanRefrence - meanDynamic), sensor});

            #ifdef DEB
            cout << sensor.GetId() << ":" << meanDynamic << ":" << abs(meanRefrence - meanDynamic) << endl;
            #endif

        }
    }

    return ranking;
} //----- Fin de RankSensorsBySimilarity

bool SensorAnalyzer::CheckFunctioningOfSensor ( Sensor & sensor, const double radius, const time_t timeRange, const double relativeDifferenceAllowed )
// Algorithme :
//
{
    bool result = true;

    const time_t endDate = time(nullptr);
    const time_t startDate = endDate - timeRange;
    for (const string & attributeId : sensor.GetAttributeIds())
    {
        double meanAirQualitySensor = ComputeMeanAirQualityForSensor(sensor, attributeId, startDate, endDate);
        double meanAirQualityWithoutSensor = ComputeMeanAirQualityInArea(
            sensor.GetLatitude(),
            sensor.GetLongitude(),
            radius,
            vector<Sensor>({sensor}),
            attributeId,
            startDate,
            endDate
        );
        if (abs(meanAirQualitySensor - meanAirQualityWithoutSensor) / meanAirQualityWithoutSensor > relativeDifferenceAllowed)
        {
            result = false;
            // sensor.SetIsFunctioning(false);
            break;
        }
    }

    return result;
} //----- Fin de CheckFunctioningOfSensor

multimap<bool, Sensor &> SensorAnalyzer::CheckFunctioningOfAllSensors ( const double radius, const time_t timeRange, const double relativeDifferenceAllowed )
// Algorithme :
//
{
    multimap<bool, Sensor &> sensorFunctionement;

    for (Sensor & sensor : sensors)
    {
        sensorFunctionement.insert({CheckFunctioningOfSensor(sensor, radius, timeRange, relativeDifferenceAllowed), sensor});
    }

    return sensorFunctionement;
} //----- Fin de CheckFunctioningOfAllSensors


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
SensorAnalyzer::SensorAnalyzer ( vector<Sensor> & sensors_ )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <SensorAnalyzer>" << endl;
#endif
    for (Sensor & sensor : sensors_)
    {
        sensors.push_back(sensor);
    }
} //----- Fin de SensorAnalyzer


SensorAnalyzer::~SensorAnalyzer ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <SensorAnalyzer>" << endl;
#endif
} //----- Fin de ~SensorAnalyzer


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
