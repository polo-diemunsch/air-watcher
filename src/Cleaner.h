/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ----------------
#if ! defined ( CLEANER_H )
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

class Provider;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
//
//
//------------------------------------------------------------------------

class Cleaner
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

    time_t GetStartDate ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    time_t GetEndDate ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool IsActiveAt ( const time_t date ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const Provider * GetProvider ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetProvider ( const Provider * provider );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << ( ostream & out, const Cleaner & cleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Cleaner ( const string & id, const double latitude, const double longitude,
              const time_t startDate, const time_t endDate );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Cleaner ( );
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
    const time_t startDate;
    const time_t endDate;
    const Provider * provider;
};

//-------------------------------- Autres définitions dépendantes de <Cleaner>

#endif // CLEANER_H
