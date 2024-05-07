/*************************************************************************
                           PrivateIndividual  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <PrivateIndividual> (fichier PrivateIndividual.h) ----------------
#if ! defined ( PRIVATE_INDIVIDUAL_H )
#define PRIVATE_INDIVIDUAL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>

#include "Sensor.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateIndividual>
//
//
//------------------------------------------------------------------------

class PrivateIndividual
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string GetId ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Sensor> GetSensors ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AddSensor ( Sensor & sensor );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool GetIsReliable ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetIsReliable ( bool isReliable );
    // Mode d'emploi :
    //
    // Contrat :
    //

    long GetPoints ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetPoints ( long points );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AddPoints ( long pointsToAdd );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << ( ostream & out, const PrivateIndividual & privateIndividual );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    PrivateIndividual ( const string & id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~PrivateIndividual ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const string id;
    vector<Sensor> sensors;
    bool isReliable;
    long points;
};

//-------------------------------- Autres définitions dépendantes de <PrivateIndividual>

#endif // PRIVATE_INDIVIDUAL_H
