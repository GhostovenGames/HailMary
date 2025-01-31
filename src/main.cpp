//
// Created by elsa on 12.04.2020.
//

#include "DialogManager.hpp"
#include "GameManager.hpp"
#include "TrefusisConfig.hpp"
#include <iostream>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
#ifdef DEBUG
    bool fileFound = TrefusisConfig::initConfig("../trefusis.conf");
#else
    bool fileFound = TrefusisConfig::initConfig("trefusis.conf");
#endif
    std::cout << fileFound;
#ifdef DEBUG
    std::cout << TrefusisConfig::configFile << "Maps directory: " << TrefusisConfig::mapsDirectory
              << " List of maps: \n";
#endif
    GameManager gm = GameManager::getInstance();
#ifndef DEBUG
    gm.showSplashScreen();
#endif
    while (!gm.quit) {
        SDL_Delay(TrefusisConfig::deltaTime);
        gm.Update();
    }
    gm.close();
}
