/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Measurement> (fichier Measurement.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
time_t Measurement::GetTimestamp ( ) const
// Algorithme :
//
{
    return timestamp;
} //----- Fin de GetTimestamp

Attribute Measurement::GetAttribute ( ) const
// Algorithme :
//
{
    return *attribute;
} //----- Fin de GetAttribute

double Measurement::GetValue ( ) const
// Algorithme :
//
{
    return value;
} //----- Fin de GetValue


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & out, const Measurement & measurement )
// Algorithme :
//
{
    out << "Measurement(timestamp: "
        << put_time(localtime(&(measurement.timestamp)), "%Y-%m-%d %H:%M:%S") << " (" << measurement.timestamp << ")"
        << ", attribute: " << *(measurement.attribute) << ", value: " << measurement.value << ")";
    return out;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement ( const time_t timestamp, const Attribute * attributePointer, const double value ) :
timestamp(timestamp), attribute(attributePointer), value(value)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Measurement>" << endl;
#endif
} //----- Fin de Measurement


Measurement::~Measurement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
#endif
} //----- Fin de ~Measurement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
