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
using namespace std;
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
} //----- Fin de GetSensors

vector<PrivateIndividual> Analyzer::GetPrivateIndividuals ( )
// Algorithme :
//
{
    vector<PrivateIndividual> result;
    result.reserve(privateIndividuals.size());

    for (const auto& element : privateIndividuals)
    {
        result.push_back(element.second);
    }

    return result;
} //----- Fin de GetPrivateIndividuals

vector<Cleaner> Analyzer::GetCleaners ( )
// Algorithme :
//
{
    vector<Cleaner> result;
    result.reserve(cleaners.size());

    for (const auto& element : cleaners)
    {
        result.push_back(element.second);
    }

    return result;
} //----- Fin de GetCleaners


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
    parsePrivateIndividuals(privateIndividualsPath);
    parseCleaners(cleanersPath);
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

    struct tm tm;

    while (getline(measurementsFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
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

void Analyzer::parsePrivateIndividuals( const string privateIndividualsPath )
// Algorithme :
//
{
    ifstream privateIndividualsFile(privateIndividualsPath);

    string line;
    smatch match;
    const regex measurementPattern("^([^;]+);([^;]+);$");

    string privateIndividualId, sensorId;
    PrivateIndividual * privateIndividualPointer;

    while (getline(privateIndividualsFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
            privateIndividualId = match[1];
            sensorId = match[2];

            unordered_map<string, PrivateIndividual>::iterator privateIndividualIterator = privateIndividuals.find(privateIndividualId);
            if (privateIndividualIterator == privateIndividuals.end())
            {
                PrivateIndividual privateIndividual(privateIndividualId);
                privateIndividualIterator = privateIndividuals.insert({privateIndividualId, privateIndividual}).first;
            }
            privateIndividualPointer = &(privateIndividualIterator->second);

            unordered_map<string, Sensor>::iterator sensorsIterator = sensors.find(sensorId);
            if (sensorsIterator != sensors.end())
            {
                if (sensorsIterator->second.GetPrivateIndividual() == nullptr)
                {
                    sensorsIterator->second.SetPrivateIndividual(privateIndividualPointer);
                    privateIndividualPointer->AddSensor(sensorsIterator->second);
                }
                else
                {
                    cerr << "Warning: sensor " << sensorId << " already has a private individual ("
                         << sensorsIterator->second.GetPrivateIndividual()->GetId()
                         << "), private individual sensor relation ignored: " << line << endl;
                }
            }
            else
            {
                cerr << "Warning: unknown sensor : " << sensorId
                     << ", private individual sensor relation ignored: " << line << endl;
            }
        }
        else
        {
            cerr << "Warning: invalid private individual sensor relation ignored: " << line << endl;
        }
    }
} //----- Fin de parsePrivateIndividuals

void Analyzer::parseCleaners ( const string cleanersPath )
// Algorithme :
//
{
    ifstream cleanersFile(cleanersPath);

    string line;
    smatch match;
    const regex sensorPattern("^([^;]+);([-+]?[0-9]*\\.?[0-9]+);([-+]?[0-9]*\\.?[0-9]+);([^;]+);([^;]+);$");

    string id;
    double latitude, longitude;
    time_t startDate, endDate;

    struct tm tm;

    while (getline(cleanersFile, line))
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
            strptime(match[4].str().c_str(), "%Y-%m-%d %H:%M:%S", &tm);
            startDate = mktime(&tm);
            strptime(match[5].str().c_str(), "%Y-%m-%d %H:%M:%S", &tm);
            endDate = mktime(&tm);

            cleaners.insert({id, Cleaner(id, latitude, longitude, startDate, endDate)});
        }
        else
        {
            cerr << "Warning: invalid cleaner ignored: " << line << endl;
        }
    }
} //----- Fin de parseCleaners
