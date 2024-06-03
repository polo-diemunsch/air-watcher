/*************************************************************************
                           Parser  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Parser> (fichier Parser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>

//------------------------------------------------------ Include personnel
#include "Parser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Parser::Parse ( const string sensorsPath, const string attributesPath, const string measurementsPath,
                     const string privateIndividualsPath, const string cleanersPath, const string providersPath )
// Algorithme :
//
{
    parseAttributes(attributesPath);
    parseSensors(sensorsPath);
    parseMeasurements(measurementsPath);
    parsePrivateIndividuals(privateIndividualsPath);
    parseCleaners(cleanersPath);
    parseProviders(providersPath);
} //----- Fin de Parse

vector<Attribute> Parser::GetMeasurementsAttributes ( ) const
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

vector<Sensor> Parser::GetSensors ( ) const
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

Sensor * Parser::GetSensorById ( const string & id )
// Algorithme :
//
{
    Sensor * result = nullptr;

    unordered_map<string, Sensor>::iterator it = sensors.find(id);
    if (it != sensors.end())
    {
        result = &(it->second);
    }

    return result;
} //----- Fin de GetSensors

PrivateIndividual * Parser::GetPrivateIndividualById ( const string & id )
// Algorithme :
//
{
    PrivateIndividual * result = nullptr;

    unordered_map<string, PrivateIndividual>::iterator it = privateIndividuals.find(id);
    if (it != privateIndividuals.end())
    {
        result = &(it->second);
    }

    return result;
} //----- Fin de GetPrivateIndividualById

Provider * Parser::GetProviderById ( const string & id )
// Algorithme :
//
{
    Provider * result = nullptr;

    unordered_map<string, Provider>::iterator it = providers.find(id);
    if (it != providers.end())
    {
        result = &(it->second);
    }

    return result;
} //----- Fin de GetProviderById

vector<PrivateIndividual> Parser::GetPrivateIndividuals ( ) const
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

vector<Cleaner> Parser::GetCleaners ( ) const
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

vector<Provider> Parser::GetProviders ( ) const
// Algorithme :
//
{
    vector<Provider> result;
    result.reserve(providers.size());

    for (const auto& element : providers)
    {
        result.push_back(element.second);
    }

    return result;
} //----- Fin de GetProviders


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Parser::Parser ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Parser>" << endl;
#endif
} //----- Fin de Parser


Parser::~Parser ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Parser>" << endl;
#endif
} //----- Fin de ~Parser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Parser::parseAttributes ( const string attributesPath )
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

void Parser::parseSensors ( const string sensorsPath )
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

void Parser::parseMeasurements ( const string measurementsPath )
// Algorithme :
//
{
    ifstream measurementsFile(measurementsPath);

    string line;
    smatch match;
    const regex measurementPattern("^(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2});([^;]+);([^;]+);([0-9]*\\.?[0-9]+);$");

    time_t timestamp;
    string sensorId, attributeId;
    double value;

    istringstream dateStringStream;
    tm time;

    // Init time zone ? (prevent first value to sometimes have -1 hour)
    dateStringStream = istringstream("1970-01-01 01:00:00");
    dateStringStream >> get_time(&time, "%Y-%m-%d %H:%M:%S");
    timestamp = mktime(&time);

    while (getline(measurementsFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
            dateStringStream = istringstream(match[1]);
            dateStringStream >> get_time(&time, "%Y-%m-%d %H:%M:%S");
            timestamp = mktime(&time);

            sensorId = match[2];
            attributeId = match[3];
            value = stod(match[4]);

            unordered_map<string, Attribute>::iterator attributesIterator = attributes.find(attributeId);
            if (attributesIterator != attributes.end())
            {
                unordered_map<string, Sensor>::iterator sensorsIterator = sensors.find(sensorId);
                if (sensorsIterator != sensors.end())
                {
                    Measurement measurement(timestamp, &(attributesIterator->second), value);
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

void Parser::parsePrivateIndividuals ( const string privateIndividualsPath )
// Algorithme :
//
{
    ifstream privateIndividualsFile(privateIndividualsPath);

    string line;
    smatch match;
    const regex measurementPattern("^([^;]+);([^;]+);$");

    string privateIndividualId, sensorId;
    PrivateIndividual * privateIndividualPointer;

    // Create PrivateIndividuals
    while (getline(privateIndividualsFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
            privateIndividualId = match[1];

            if (!privateIndividuals.count(privateIndividualId))
            {
                PrivateIndividual privateIndividual(privateIndividualId);
                privateIndividuals.insert({privateIndividualId, privateIndividual});
            }
        }
    }

    privateIndividualsFile.clear();
    privateIndividualsFile.seekg(0);

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

void Parser::parseCleaners ( const string cleanersPath )
// Algorithme :
//
{
    ifstream cleanersFile(cleanersPath);

    string line;
    smatch match;
    const regex sensorPattern("^([^;]+);([-+]?[0-9]*\\.?[0-9]+);([-+]?[0-9]*\\.?[0-9]+);(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2});(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2});$");

    string id;
    double latitude, longitude;
    time_t startDate, endDate;

    istringstream dateStringStream;
    tm time;

    // Init time zone ? (prevent first value to sometimes have -1 hour)
    dateStringStream = istringstream("1970-01-01 01:00:00");
    dateStringStream >> get_time(&time, "%Y-%m-%d %H:%M:%S");
    startDate = mktime(&time);

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

            dateStringStream = istringstream(match[4]);
            dateStringStream >> get_time(&time, "%Y-%m-%d %H:%M:%S");
            startDate = mktime(&time);
            dateStringStream = istringstream(match[5]);
            dateStringStream >> get_time(&time, "%Y-%m-%d %H:%M:%S");
            endDate = mktime(&time);

            cleaners.insert({id, Cleaner(id, latitude, longitude, startDate, endDate)});
        }
        else
        {
            cerr << "Warning: invalid cleaner ignored: " << line << endl;
        }
    }
} //----- Fin de parseCleaners

void Parser::parseProviders ( const string providersPath )
// Algorithme :
//
{
    ifstream providersFile(providersPath);

    string line;
    smatch match;
    const regex measurementPattern("^([^;]+);([^;]+);$");

    string providerId, cleanerId;
    Provider * providerPointer;

    // Create Providers
    while (getline(providersFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
            providerId = match[1];

            if (!providers.count(providerId))
            {
                Provider provider(providerId);
                providers.insert({providerId, provider});
            }
        }
    }

    providersFile.clear();
    providersFile.seekg(0);

    while (getline(providersFile, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        if (regex_match(line, match, measurementPattern))
        {
            providerId = match[1];
            cleanerId = match[2];

            unordered_map<string, Provider>::iterator providerIterator = providers.find(providerId);
            providerPointer = &(providerIterator->second);

            unordered_map<string, Cleaner>::iterator cleanersIterator = cleaners.find(cleanerId);
            if (cleanersIterator != cleaners.end())
            {
                if (cleanersIterator->second.GetProvider() == nullptr)
                {
                    cleanersIterator->second.SetProvider(providerPointer);
                    providerPointer->AddCleaner(cleanersIterator->second);
                }
                else
                {
                    cerr << "Warning: cleaner " << cleanerId << " already has a provider ("
                         << cleanersIterator->second.GetProvider()->GetId()
                         << "), provider cleaner relation ignored: " << line << endl;
                }
            }
            else
            {
                cerr << "Warning: unknown cleaner : " << cleanerId
                     << ", provider cleaner relation ignored: " << line << endl;
            }
        }
        else
        {
            cerr << "Warning: invalid provider cleaner relation ignored: " << line << endl;
        }
    }
} //----- Fin de parseProviders
