/*************************************************************************
                           Parser  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Parser> (fichier Parser.h) ----------------
#if ! defined ( PARSER_H )
#define PARSER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <vector>

#include "../model/Attribute.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/PrivateIndividual.h"
#include "../model/Cleaner.h"
#include "../model/Provider.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Parser>
//
//
//------------------------------------------------------------------------

class Parser
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    vector<Attribute> GetMeasurementsAttributes ( ) const;
    // Mode d'emploi :
    // 
    // Contrat :
    // 

    vector<Sensor> GetSensors ( ) const;
    // Mode d'emploi :
    // 
    // Contrat :
    // 

    vector<PrivateIndividual> GetPrivateIndividuals ( ) const;
    // Mode d'emploi :
    // 
    // Contrat :
    // 

    vector<Cleaner> GetCleaners ( ) const;
    // Mode d'emploi :
    // 
    // Contrat :
    // 

    vector<Provider> GetProviders ( ) const;
    // Mode d'emploi :
    // 
    // Contrat :
    // 

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Parser ( const string sensorsPath, const string attributesPath, const string measurementsPath,
               const string privateIndividualsPath, const string cleanersPath, const string providersPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Parser ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void parseAttributes ( const string attributesPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void parseSensors ( const string sensorsPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void parseMeasurements ( const string measurementsPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void parsePrivateIndividuals ( const string privateIndividualsPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void parseCleaners ( const string cleanersPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void parseProviders ( const string providersPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    unordered_map<string, Attribute> attributes;
    unordered_map<string, Sensor> sensors;
    unordered_map<string, PrivateIndividual> privateIndividuals;
    unordered_map<string, Cleaner> cleaners;
    unordered_map<string, Provider> providers;
};

//-------------------------------- Autres définitions dépendantes de <Parser>

#endif // PARSER_H
