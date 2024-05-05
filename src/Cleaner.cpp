/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Cleaner> (fichier Cleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"
# include "Provider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Cleaner::GetId ( ) const
// Algorithme :
//
{
    return id;
} //----- Fin de GetId

double Cleaner::GetLatitude ( ) const
// Algorithme :
//
{
    return latitude;
} //----- Fin de GetLatitude

double Cleaner::GetLongitude ( ) const
// Algorithme :
//
{
    return longitude;
} //----- Fin de GetLongitude

pair<double, double> Cleaner::GetPosition ( ) const
// Algorithme :
//
{
    return make_pair(latitude, longitude);
} //----- Fin de GetLongitude

time_t Cleaner::GetStartDate ( ) const
// Algorithme :
//
{
    return startDate;
} //----- Fin de GetStartDate

time_t Cleaner::GetEndDate ( ) const
// Algorithme :
//
{
    return endDate;
} //----- Fin de GetEndDate

const Provider * Cleaner::GetProvider ( ) const
// Algorithme :
//
{
    return provider;
} //----- Fin de GetProvider

void Cleaner::SetProvider ( const Provider * providerPointer )
// Algorithme :
//
{
    provider = providerPointer;
} //----- Fin de SetProvider


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & out, const Cleaner & cleaner )
// Algorithme :
//
{
    out << "Cleaner(id: " << cleaner.id<< ", latitude: " << cleaner.latitude << ", longitude: " << cleaner.longitude
        << ", startDate: " << cleaner.startDate << ", endDate: " << cleaner.endDate             // TODO format time_t (see measurement too)
        << ", provider: ";
    if (cleaner.provider != nullptr)
    {
        out << *(cleaner.provider);
    }
    else
    {
        out << "None";
    }
    out << ")";

    return out;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner ( const string & id, const double latitude, const double longitude,
                   const time_t startDate, const time_t endDate ) :
id(id), latitude(latitude), longitude(longitude), startDate(startDate), endDate(endDate)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
    provider = nullptr;
} //----- Fin de Cleaner


Cleaner::~Cleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
