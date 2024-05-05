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
    parseMeasurements(measurementsPath);
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
        if (line.back() == '\r')
        {
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
    const regex sensorPattern("^([^;]+);([-+]?[0-9]*\\.?[0-9]+);([-+]?[0-9]*\\.?[0-9]+);$");

    string id;
    double latitude, longitude;

    while (getline(sensorsFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, sensorPattern))
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

void Analyzer::parseMeasurements ( const string measurementsPath )
// Algorithme :
//
{
    ifstream measurementsFile(measurementsPath);

    string line;
    smatch match;
    const regex measurementPattern("^([^;]+);([^;]+);([^;]+);([0-9]*\\.?[0-9]+);$");

    time_t timestamp;
    string sensorId, attributeId;
    double value;

    while (getline(measurementsFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
            struct tm tm;
            strptime(match[1].str().c_str(), "%Y-%m-%d %H:%M:%S", &tm);
            timestamp = mktime(&tm);
            sensorId = match[2];
            attributeId = match[3];
            value = stod(match[4]);

            unordered_map<string, Attribute>::iterator attributesIterator = attributes.find(attributeId);
            if (attributesIterator != attributes.end())
            {
                Attribute attribute = attributesIterator->second;
                unordered_map<string, Sensor>::iterator sensorsIterator = sensors.find(sensorId);
                if (sensorsIterator != sensors.end())
                {
                    Measurement measurement(timestamp, &attribute, value);
                    sensorsIterator->second.AddMeasurement(measurement);
                }
                else
                {
                    cerr << "Warning: unknown sensor : " << sensorId
                         << ", measurement ignored: " << line << endl;
                }
            }
            else
            {
                cerr << "Warning: unknown measurement attribute : " << attributeId
                     << ", measurement ignored: " << line << endl;
            }
        }
        else
        {
            cerr << "Warning: invalid measurement ignored: " << line << endl;
        }
    }
} //----- Fin de parseMeasurements
