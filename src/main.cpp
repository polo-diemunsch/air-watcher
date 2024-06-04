/*************************************************************************
                           main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

//------------------------------------------------------ Include personnel
#include "vue/UserInterface.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

int main(int argc, char *argv[])
{
    string configFilePath = "";

    try
    {
        const vector<string> args(argv + 1, argv + argc); // Liste des arguments passés au programme

        vector<string>::const_iterator it = args.begin();

        // On parcourt les arguments
        while (it != args.end())
        {
            // On affiche l'aide
            if (*it == "-h" || *it == "--help")
            {
                cout << "Usage: air-watcher [OPTION]...\n";
                cout << "\n";
                cout << "Options:\n";
                cout << "  -h, --help                           Print this help\n";
                cout << "  -c, --config <FILE>                  Configuration file (default bin/air-watcher.conf)\n";
                cout << flush;

                return EXIT_SUCCESS;
            }
            
            // On récupère le chemin vers le fichier de config
            else if (*it == "-c" || *it == "--config")
            {
                if (configFilePath != "")
                {
                    throw runtime_error("cannot use -c/--config param twice!");
                }
                it++;
                if (it == args.end())
                {
                    throw runtime_error("invalid param for -c/--config option");
                }
                configFilePath = *it;
            }

            it++;
        }
    }
    // En cas d'erreur, on affiche l'erreur et on quitte le programme
    catch (exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    const string relativePathToExe = argv[0];
    const string relativePathToParentFolder = filesystem::path(relativePathToExe).parent_path().string();
    
    // On récupère depuis fichier de config le dossier contenant les données ainsi que
    // la différence relative autorisée pour qu'un capteur soit considéré fonctionnel

    if (configFilePath == "")
    {
        // Fichier de configuration par défaut
        configFilePath = relativePathToParentFolder + "/air-watcher.conf";
    }

    ifstream configFile (configFilePath);
    if (! configFile.good())
    {
        cerr << "Warning: config file not found" << endl;
    }
    
    string datasetPath = "../dataset ";
    double relativeDifferenceAllowed = 0.2;
    double defaultRadius = 75;
    string line;

    while (getline(configFile, line))
    { // On parcourt le fichier de config

        // On récupère le chemin du dossier contenant les données
        if (regex_search(line, regex("^dataset-path *=")))
        {
            string::const_iterator start = line.begin() + line.find('=') + 1;
            string::const_iterator end = start;
            while (end != line.end() && *end != '#') end++;
            regex nonWhitespaceRegex("\\S+");
            sregex_iterator match(start, end, nonWhitespaceRegex);
            datasetPath = match->str();
        }

        // On récupère la différence relative autorisée
        else if (regex_search(line, regex("^relative-difference-allowed *=")))
        {
            string::const_iterator start = line.begin() + line.find('=') + 1;
            string::const_iterator end = start;
            while (end != line.end() && *end != '#') end++;
            regex doubleRegex("[0-9]*\\.?[0-9]+");
            sregex_iterator match(start, end, doubleRegex);
            relativeDifferenceAllowed = stod(match->str());
        }

        // On récupère le rayon par défaut
        else if (regex_search(line, regex("^default-radius *=")))
        {
            string::const_iterator start = line.begin() + line.find('=') + 1;
            string::const_iterator end = start;
            while (end != line.end() && *end != '#') end++;
            regex doubleRegex("[0-9]*\\.?[0-9]+");
            sregex_iterator match(start, end, doubleRegex);
            defaultRadius = stod(match->str());
        }
    }

    if (!datasetPath.empty() && datasetPath[0] != '/')
    {
        datasetPath = relativePathToParentFolder + "/" + datasetPath;
    }

    UserInterface userInterface(datasetPath, relativeDifferenceAllowed, defaultRadius);

    userInterface.MainLoop();

    return EXIT_SUCCESS;
} //----- fin de main