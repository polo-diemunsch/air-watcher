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
using namespace std;
#include <string>
#include <unordered_map>
#include <vector>

#include "Attribute.h"

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
    vector<Attribute> GetMeasurementsAttributes ( );
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

//----------------------------------------------------- Attributs protégés
    unordered_map<string, Attribute> attributes;

};

//-------------------------------- Autres définitions dépendantes de <Analyzer>

#endif // ANALYZER_H
