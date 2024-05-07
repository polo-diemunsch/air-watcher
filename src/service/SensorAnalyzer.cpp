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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorAnalyzer::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


double SensorAnalyzer::ComputeMeanAirQualityForSensor(const Sensor & sensor, const string & attributeId, time_t debut, time_t fin)
{
    vector <Measurement> mesures = sensor.GetMeasurementsWithAttributeWithinDateRange(attributeId, debut, fin);
    double res = 0;
    double nb = 0;

    for (const Measurement & mesure : mesures)
    {
        res += mesure.GetValue();
        nb++;
    }

    return (nb == 0) ? 0 : (res / nb);
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
