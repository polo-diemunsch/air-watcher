/*************************************************************************
                           Analyzer  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Analyzer> (fichier Analyzer.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <regex>

//------------------------------------------------------ Include personnel
#include "Analyzer.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<Attribute> Analyzer::GetMeasurementsAttributes ( )
// Algorithme :
//
{
    vector<Attribute> result;
    result.reserve(attributes.size());

    for (const auto& element : attributes)
    {
        result.push_back(element.second);
    }

    return result;
} //----- Fin de GetMeasurementsAttributes

vector<Sensor> Analyzer::GetSensors ( )
// Algorithme :
//
{
    vector<Sensor> result;
    result.reserve(sensors.size());

    for (const auto& element : sensors)
    {
        result.push_back(element.second);
    }

    return result;
} //----- Fin de GetMeasurementsAttributes


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Analyzer::Analyzer ( const string sensorsPath, const string attributesPath, const string measurementsPath,
                     const string privateIndividualsPath, const string cleanersPath, const string providersPath )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Analyzer>" << endl;
#endif
    parseAttributes(attributesPath);
    parseSensors(sensorsPath);
} //----- Fin de Analyzer


Analyzer::~Analyzer ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Analyzer>" << endl;
#endif
} //----- Fin de ~Analyzer


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Analyzer::parseAttributes ( const string attributesPath )
// Algorithme :
//
{
    ifstream attributesFile(attributesPath);

    string line;
    smatch match;
    const regex attributePattern("^([^;]+);([^;]+);([^;]+);$");

    string id, unit, description;

    getline(attributesFile, line);  // remove first line (column titles)
    while (getline(attributesFile, line))
    {
        if (line.back() == '\r') {
            line.pop_back();
        }
        if (regex_match(line, match, attributePattern))
        {
            id = match[1];
            unit = match[2];
            description = match[3];

            attributes.insert({id, Attribute(id, unit, description)});
        }
        else
        {
            cerr << "Warning: invalid attribute ignored: " << line << endl;
        }
    }
} //----- Fin de parseAttributes

void Analyzer::parseSensors ( const string sensorsPath )
// Algorithme :
//
{
    ifstream sensorsFile(sensorsPath);

    string line;
    smatch match;
    const regex attributePattern("^([^;]+);([-+]?[0-9]*\\.?[0-9]+);([-+]?[0-9]*\\.?[0-9]+);$");

    string id;
    double latitude, longitude;

    getline(sensorsFile, line);  // remove first line (column titles)
    while (getline(sensorsFile, line))
    {
        if (line.back() == '\r') {
            line.pop_back();
        }
        if (regex_match(line, match, attributePattern))
        {
            id = match[1];
            latitude = stod(match[2]);
            longitude = stod(match[3]);

            sensors.insert({id, Sensor(id, latitude, longitude)});
        }
        else
        {
            cerr << "Warning: invalid sensor ignored: " << line << endl;
        }
    }
} //----- Fin de parseSensors
