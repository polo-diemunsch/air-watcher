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

//------------------------------------------------------ Include personnel
#include "SensorAnalyzer.h"
#include "../model/PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorAnalyzer::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


multimap<double, Sensor> SensorAnalyzer::RankSensorsBySimilarity(const Sensor & sensorToCompareTo, const string & attributeID)
{
    double meanRefrence;
    double meanDynamic;
    multimap<double, Sensor> ranking;

    time_t currentTime = time(NULL);

    //currentTime - 30*24*60*60 === today minus one month
    meanRefrence=ComputeMeanAirQualityForSensor(sensorToCompareTo, attributeID, currentTime - 30*24*60*60,currentTime);

    for(vector<Sensor>::const_iterator sensorIt = sensors.begin(); sensorIt != sensors.end(); sensorIt++)
    {
        if (!(*sensorIt == sensorToCompareTo) && ((*sensorIt).GetPrivateIndividual() == NULL || (*sensorIt).GetPrivateIndividual()->GetIsReliable()))
        {
            meanDynamic = ComputeMeanAirQualityForSensor(*sensorIt, attributeID, currentTime - 30*24*60*60,currentTime);
            ranking.insert({abs(meanRefrence - meanDynamic), *sensorIt});
        }
    }

    return ranking;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
SensorAnalyzer::SensorAnalyzer ( vector<Sensor> & sensors ) :
sensors(sensors)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <SensorAnalyzer>" << endl;
#endif
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
