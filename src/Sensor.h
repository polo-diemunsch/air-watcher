/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( SENSOR_H )
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>
#include <unordered_map>
#include <map>

#include "Measurement.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // TODO PrivateIndividual
    const void * GetPrivateIndividual ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetPrivateIndividual ( const void * privateIndividual );
    // Mode d'emploi :
    //
    // Contrat :
    //

    double GetLatitude ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    double GetLongitude ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool GetIsFunctioning ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetIsFunctioning ( bool isFunctioning );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AddMeasurement ( Measurement & measurement );
    // Mode d'emploi :
    //
    // Contrat :
    //

    unordered_map<string, unordered_map<time_t, Measurement>> GetMeasurements ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << (ostream & out, const Sensor & sensor);
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Sensor ( const string & id, const double latitude, const double longitude );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const string id;
    const double latitude;
    const double longitude;
    const void * privateIndividual;   // TODO PrivateIndividual
    unordered_map<string, map<time_t, Measurement>> measurements;
    bool isFunctioning;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H
