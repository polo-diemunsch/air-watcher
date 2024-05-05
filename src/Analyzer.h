/*************************************************************************
                           Analyzer  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Analyzer> (fichier Analyzer.h) ----------------
#if ! defined ( ANALYZER_H )
#define ANALYZER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <vector>

#include "Attribute.h"
#include "Sensor.h"
#include "Measurement.h"
#include "PrivateIndividual.h"
#include "Cleaner.h"
#include "Provider.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Analyzer>
//
//
//------------------------------------------------------------------------

class Analyzer
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
    Analyzer ( const string sensorsPath, const string attributesPath, const string measurementsPath,
               const string privateIndividualsPath, const string cleanersPath, const string providersPath );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Analyzer ( );
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

//-------------------------------- Autres définitions dépendantes de <Analyzer>

#endif // ANALYZER_H
