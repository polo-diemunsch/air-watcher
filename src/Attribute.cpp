/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Attribute> (fichier Attribute.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Attribute::GetID ( ) const
// Algorithme :
//
{
    return id;
} //----- Fin de GetID

string Attribute::GetUnit ( ) const
// Algorithme :
//
{
    return unit;
} //----- Fin de GetUnit

string Attribute::GetDescription ( ) const
// Algorithme :
//
{
    return description;
} //----- Fin de GetDescription


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << (ostream & out, const Attribute & attribute)
// Algorithme :
//
{
    out << attribute.id << " " << attribute.unit << " " << attribute.description;
    return out;
} //----- Fin de operator <<

//-------------------------------------------- Constructeurs - destructeur
Attribute::Attribute ( const string id, const string unit, const string description ) :
id(id), unit(unit), description(description)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Attribute>" << endl;
#endif
} //----- Fin de Attribute


Attribute::~Attribute ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Attribute>" << endl;
#endif
} //----- Fin de ~Attribute


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
