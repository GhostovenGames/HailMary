//
// Created by elsa on 15.04.2020.
//

#include <vector>
#include "TrefusisConfig.h"

std::string TrefusisConfig::configFile;
std::string TrefusisConfig::tilemapLocation;
std::string  TrefusisConfig::mapsDirectory;
std::vector<std::string> TrefusisConfig::mapFileNames;
bool TrefusisConfig::isInitialised = false;

bool TrefusisConfig::initConfig(std::string fileName) {
    if (isInitialised) {
        return true;
    } else {
        FILE* fileptr;
        fileptr = fopen(fileName.c_str(), "r");
        if (fileptr == nullptr) {
            return false; // In  case file is not found etc.
        }
        configFile = fileName;
        std::string token;
        int read_char = 14;
        bool isWriteMode = false;
        std::string writeTo;
        while (read_char != EOF) {
            read_char = fgetc(fileptr);
            switch (read_char) {
                case ' ':
                    isWriteMode = !isWriteMode;
                    writeTo = token;
                    break;
                case '\n':
                    if (writeTo == "maps") {
                        mapsDirectory = token;
                    } else if (writeTo == "tilemap") {
                        tilemapLocation = token;
                    } else if (writeTo == "map") {
                        mapFileNames.push_back(token + ".csv");
                    }
                    token = "";
                    break;
                default:
                    token += (char) read_char;
            }
        }
        fclose(fileptr);
        return true;
    }
}