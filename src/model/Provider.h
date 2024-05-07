/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if ! defined ( PROVIDER_H )
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>

#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Provider>
//
//
//------------------------------------------------------------------------

class Provider
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string GetId ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Cleaner> GetCleaners ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AddCleaner ( Cleaner & cleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << ( ostream & out, const Provider & provider );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Provider ( const string & id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Provider ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const string id;
    vector<Cleaner> cleaners;
};

//-------------------------------- Autres définitions dépendantes de <Provider>

#endif // PROVIDER_H
