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
#include <vector>

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
    void chooseRole ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void meanAirQuality ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void rankSensors ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void checkFunctioningOfAllSensors ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void checkFunctioningOfASensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void checkReliabilityOfPrivateIndividual ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void consultPointsOfPrivateIndividual ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void radiusCleanedZone ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void airImprovement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void consultDataset ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    Parser parser;
    SensorAnalyzer sensorAnalyzer;
    double relativeDifferenceAllowed;
    double defaultRadius;
    vector<Sensor> sensors;
    Provider * provider;
    PrivateIndividual * privateIndividual;
};

//-------------------------------- Autres définitions dépendantes de <UserInterface>

#endif // USER_INTERFACE_H
