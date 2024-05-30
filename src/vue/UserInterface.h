/*************************************************************************
                           UserInterface  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <UserInterface> (fichier UserInterface.h) ----------------
#if ! defined ( USER_INTERFACE_H )
#define USER_INTERFACE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

#include "../data/Parser.h"
#include "../service/SensorAnalyzer.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <UserInterface>
//
//
//------------------------------------------------------------------------

class UserInterface
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void MainLoop ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    UserInterface ( const string & datasetPath, double relativeDifferenceAllowed, double defaultRadius );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~UserInterface ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Parser parser;
    SensorAnalyzer sensorAnalyzer;
    double relativeDifferenceAllowed;
    double defaultRadius;
};

//-------------------------------- Autres définitions dépendantes de <UserInterface>

#endif // USER_INTERFACE_H
