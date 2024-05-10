/*************************************************************************
                           SensorAnalyzer  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <SensorAnalyzer> (fichier SensorAnalyzer.h) ----------------
#if ! defined ( SENSOR_ANALYZER_H )
#define SENSOR_ANALYZER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>

#include "../model/Sensor.h"
#include "../model/PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <SensorAnalyzer>
//
//
//------------------------------------------------------------------------

class SensorAnalyzer
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    //current date à voir
    double ComputeMeanAirQualityForSensor (
        const Sensor & sensor,
        const string & attributeId,
        time_t startDate,
        time_t endDate
    );
    // Mode d'emploi :
    //
    // Contrat : //endDates > startDate
    //
    double ComputeMeanAirQualityInArea (
        const double latitude,
        const double longitude,
        const double radius,
        vector<Sensor> sensorsToExclude,
        const string & attributeId,
        const time_t & startDate,
        const time_t & endDate
    );
    // Mode d'emploi :
    //
    // Contrat : rayon en km, endDates > startDate
    //

    bool CheckFunctioningOfSensor (
        Sensor & sensor,
        const double radius,
        const time_t timeRange,
        const double relativeDifferenceAllowed
    );
    // Mode d'emploi :
    //
    // Contrat :
    //

    multimap<bool, Sensor &> CheckFunctioningOfAllSensors (
        const double radius,
        const time_t timeRange,
        const double relativeDifferenceAllowed
    );
    // Mode d'emploi :
    //
    // Contrat :
    //

    multimap<double, Sensor &> RankSensorsBySimilarity (
        const Sensor & sensorToCompareTo,
        const string & attributeId,
        const time_t timeRange
    );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    SensorAnalyzer ( vector<Sensor> & sensors );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~SensorAnalyzer ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<Sensor> sensors;
};

//-------------------------------- Autres définitions dépendantes de <SensorAnalyzer>

#endif // SENSOR_ANALYZER_H
