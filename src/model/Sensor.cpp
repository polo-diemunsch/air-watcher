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
#include "PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Sensor::GetId ( ) const
// Algorithme :
//
{
    return id;
} //----- Fin de GetId

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

pair<double, double> Sensor::GetPosition ( ) const
// Algorithme :
//
{
    return make_pair(latitude, longitude);
} //----- Fin de GetLongitude

const PrivateIndividual * Sensor::GetPrivateIndividual ( ) const
// Algorithme :
//
{
    return privateIndividual;
} //----- Fin de GetPrivateIndividual

void Sensor::SetPrivateIndividual ( const PrivateIndividual * privateIndividualPointer )
// Algorithme :
//
{
    privateIndividual = privateIndividualPointer;
} //----- Fin de SetPrivateIndividual

bool Sensor::GetIsFunctioning ( ) const
// Algorithme :
//
{
    return isFunctioning;
} //----- Fin de GetIsFunctioning

void Sensor::SetIsFunctioning ( bool isFunctioning_ )
// Algorithme :
//
{
    isFunctioning = isFunctioning_;
} //----- Fin de SetIsFunctioning

void Sensor::AddMeasurement ( Measurement & measurement )
// Algorithme :
//
{
    string attributeId = measurement.GetAttribute().GetId();
    if (!measurements.count(attributeId))
    {
        map<time_t, Measurement> measurementsWithAttribute;
        measurements.insert({attributeId, measurementsWithAttribute});
    }
    measurements[attributeId].insert({measurement.GetTimestamp(), measurement});
} //----- Fin de AddMeasurement

unordered_map<string, map<time_t, Measurement>> Sensor::GetMeasurements ( ) const
// Algorithme :
//
{
    return measurements;
} //----- Fin de GetMeasurements

map<time_t, Measurement> Sensor::GetMeasurementsWithAttribute ( const string & attributeId ) const
// Algorithme :
//
{
    map<time_t, Measurement> result;

    unordered_map<string, map<time_t, Measurement>>::const_iterator measurementsIterator = measurements.find(attributeId);
    if (measurementsIterator != measurements.end())
    {
        result = measurementsIterator->second;
    }

    return result;
} //----- Fin de GetMeasurementsWithAttribute

vector<Measurement> Sensor::GetMeasurementsWithAttributeWithinDateRange ( const string & attributeId, const time_t startDate, const time_t endDate ) const
// Algorithme :
//
{
    map<time_t, Measurement> measurementsWithAttribute = GetMeasurementsWithAttribute(attributeId);

    map<time_t, Measurement>::iterator startIterator = measurementsWithAttribute.lower_bound(startDate);
    map<time_t, Measurement>::iterator endIterator = measurementsWithAttribute.upper_bound(endDate);

    vector<Measurement> result;
    result.reserve(distance(startIterator, endIterator));

    for (map<time_t, Measurement>::iterator it = startIterator; it != endIterator; it++)
    {
        result.push_back(it->second);
    }

    return result;
} //----- Fin de GetMeasurementsWithAttributeWithinDateRange

vector<string> Sensor::GetAttributeIds ( ) const
// Algorithme :
//
{
    vector<string> result;
    result.reserve(measurements.size());

    for (const auto& element : measurements)
    {
        result.push_back(element.first);
    }

    return result;
} //----- Fin de GetAttributeIds


//------------------------------------------------- Surcharge d'opérateurs
bool Sensor::operator == ( const Sensor & aSensor ) const
// Algorithme :
//
 {
    return this->id == aSensor.GetId();
 }

bool Sensor::operator != ( const Sensor & aSensor ) const
// Algorithme :
//
 {
    return this->id != aSensor.GetId();
} //----- Fin de operator <<

ostream & operator << ( ostream & out, const Sensor & sensor )
// Algorithme :
//
{
    long measurementsCount = 0;
    for (const auto& measurementsWithAttribute : sensor.measurements)
    {
        measurementsCount += measurementsWithAttribute.second.size();
    }
    out << "Sensor(id: " << sensor.id<< ", latitude: " << sensor.latitude << ", longitude: " << sensor.longitude
        << ", isFunctioning: " << sensor.isFunctioning << ", measurements count: " << measurementsCount
        << ", privateIndividual: ";
    if (sensor.privateIndividual != nullptr)
    {
        out << *(sensor.privateIndividual);
    }
    else
    {
        out << "None";
    }
    out << ")";

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
    privateIndividual = nullptr;
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
