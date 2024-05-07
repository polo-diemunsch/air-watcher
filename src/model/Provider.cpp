/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Provider> (fichier Provider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Provider::GetId ( ) const
// Algorithme :
//
{
    return id;
} //----- Fin de GetId

vector<Cleaner> Provider::GetCleaners ( ) const
// Algorithme :
//
{
    return cleaners;
} //----- Fin de GetCleaners

void Provider::AddCleaner ( Cleaner & cleaner )
// Algorithme :
//
{
    cleaners.push_back(cleaner);
} //----- Fin de AddCleaner


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & out, const Provider & provider )
// Algorithme :
//
{
    out << "Provider(id: " << provider.id<< ", cleaners count: " << provider.cleaners.size() << ")";
    return out;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Provider::Provider ( const string & id ) :
id(id)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Provider>" << endl;
#endif
} //----- Fin de Provider


Provider::~Provider ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
