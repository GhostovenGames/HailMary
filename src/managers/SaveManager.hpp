//
// Created by elsa on 13.04.2020.
//

#ifndef TREFUSISENGINE_SAVEMANAGER_HPP
#define TREFUSISENGINE_SAVEMANAGER_HPP

#include "GameManager.hpp"

class SaveManager {
  public:
    GameManager loadGame(std::string fileName);
    void saveGame(std::string fileName, GameManager gameManager);
};

#endif // TREFUSISENGINE_SAVEMANAGER_HPP