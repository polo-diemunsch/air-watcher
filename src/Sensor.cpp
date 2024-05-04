/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const void * Sensor::GetPrivateIndividual ( ) const
// Algorithme :
//
{
    return privateIndividual;
} //----- Fin de GetPrivateIndividual

void Sensor::SetPrivateIndividual ( const void * privateIndividual_ )
// Algorithme :
//
{
    privateIndividual = privateIndividual_;
} //----- Fin de SetPrivateIndividual

double Sensor::GetLatitude ( ) const
// Algorithme :
//
{
    return latitude;
} //----- Fin de GetLatitude

double Sensor::GetLongitude ( ) const
// Algorithme :
//
{
    return longitude;
} //----- Fin de GetLongitude

bool Sensor::GetIsFunctioning ( ) const
// Algorithme :
//
{
    return isFunctioning;
} //----- Fin de GetIsFunctioning

void Sensor::SetIsFunctioning ( bool isFuntioning_ )
// Algorithme :
//
{
    isFunctioning = isFuntioning_;
} //----- Fin de SetIsFunctioning


void Sensor::AddMeasurement ( Measurement & measurement )
// Algorithme :
//
{
    string attributeId = measurement.GetAttribute().GetId();
    if (!measurements.count(attributeId)) {
        map<time_t, Measurement> measurementsWithAttribute;
        measurements.insert({attributeId, measurementsWithAttribute});
    }
    measurements[attributeId].insert({measurement.GetTimestamp(), measurement});
} //----- Fin de AddMeasurement


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << (ostream & out, const Sensor & sensor)
// Algorithme :
//
{
    out << "Sensor(id: " << sensor.id<< ", latitude: " << sensor.latitude << ", longitude: " << sensor.longitude
        << ", isFunctioning: " << sensor.isFunctioning << ", measurements count: " << sensor.measurements.size() << ")";
    return out;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor ( const string & id, const double latitude, const double longitude ) :
id(id), latitude(latitude), longitude(longitude)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    isFunctioning = true;
} //----- Fin de Sensor


Sensor::~Sensor ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
