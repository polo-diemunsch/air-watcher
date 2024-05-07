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
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

#include "Measurement.h"

class PrivateIndividual;

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
    string GetId ( ) const;
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

    pair<double, double> GetPosition ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const PrivateIndividual * GetPrivateIndividual ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetPrivateIndividual ( const PrivateIndividual * privateIndividual );
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

    unordered_map<string, map<time_t, Measurement>> GetMeasurements ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    map<time_t, Measurement> GetMeasurementsWithAttribute ( const string & attributeId ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> GetMeasurementsWithAttributeWithinDateRange ( const string & attributeId, const time_t startDate, const time_t endDate ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<string> GetAttributeIds ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << ( ostream & out, const Sensor & sensor );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool operator== ( const Sensor & aSensor ) const;

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
    const PrivateIndividual * privateIndividual;
    unordered_map<string, map<time_t, Measurement>> measurements;
    bool isFunctioning;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H
