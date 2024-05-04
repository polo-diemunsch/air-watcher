/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Attribute>
//
//
//------------------------------------------------------------------------

class Attribute
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string GetID ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string GetUnit ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string GetDescription ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << (ostream &, const Attribute &);
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Attribute ( const string id, const string unit, const string description );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Attribute ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string id;
    string unit;
    string description;
};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // ATTRIBUTE_H