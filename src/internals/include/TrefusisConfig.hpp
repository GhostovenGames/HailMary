//
// Created by elsa on 15.04.2020.
//

#ifndef HAILMARY_TREFUSISCONFIG_HPP
#define HAILMARY_TREFUSISCONFIG_HPP

#include <string>
#include <vector>

class TrefusisConfig {
  public:
    // Config
    static std::string configFile;
    static std::string prefix;
    static std::string scriptFile;
    static std::string levelsLocation;

    // Directories
    static std::string resourcesDirectory;
    static std::string mapsDirectory;
    static std::string musicsDirectory;

    // Images
    static std::string splash;
    static std::string engineSplash;
    static std::string spritesheet;

    // Graphic Geometry
    static const int deltaTime = 0;
    static const int tileSize = 64;
    static const int screenWidth = 640;
    static const int screenHeight = 480;

    // Time
    static const int dayLength = 150;
    static const int seasonLength = 45000;

    static bool isInitialised;
    /**
     * Initialise the config object.
     * @param fileName Filename to the main trefusis.conf
     * @return If config object is initialised, false if config file not found.
     */
    static bool initConfig(std::string fileName);
};

#endif // HAILMARY_TREFUSISCONFIG_HPP