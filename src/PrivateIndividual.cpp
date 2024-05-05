/*************************************************************************
                           PrivateIndividual  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <PrivateIndividual> (fichier PrivateIndividual.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string PrivateIndividual::GetId ( ) const
// Algorithme :
//
{
    return id;
} //----- Fin de GetId

void PrivateIndividual::AddSensor ( Sensor & sensor )
// Algorithme :
//
{
    sensors.push_back(sensor);
} //----- Fin de AddPoints

bool PrivateIndividual::GetIsReliable ( ) const
// Algorithme :
//
{
    return isReliable;
} //----- Fin de GetIsReliable

void PrivateIndividual::SetIsReliable ( bool isReliable_ )
// Algorithme :
//
{
    isReliable = isReliable_;
} //----- Fin de SetIsReliable

long PrivateIndividual::GetPoints ( ) const
// Algorithme :
//
{
    return points;
} //----- Fin de GetPoints

void PrivateIndividual::SetPoints ( long points_ )
// Algorithme :
//
{
    points = points_;
} //----- Fin de SetPoints

void PrivateIndividual::AddPoints ( long pointsToAdd )
// Algorithme :
//
{
    points += pointsToAdd;
} //----- Fin de AddPoints


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << (ostream & out, const PrivateIndividual & privateIndividual)
// Algorithme :
//
{
    out << "PrivateIndividual(id: " << privateIndividual.id<< ", sensors count: " << privateIndividual.sensors.size()
        << ", points: " << privateIndividual.points << ", isReliable: " << privateIndividual.isReliable << ")";
    return out;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
PrivateIndividual::PrivateIndividual ( const string & id ) :
id(id)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <PrivateIndividual>" << endl;
#endif
    points = 0;
    isReliable = true;
} //----- Fin de PrivateIndividual


PrivateIndividual::~PrivateIndividual ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PrivateIndividual>" << endl;
#endif
} //----- Fin de ~PrivateIndividual


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
