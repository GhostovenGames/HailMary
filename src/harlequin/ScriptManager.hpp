//
// Created by elsa on 21.04.2020.
//

#ifndef TREFUSISENGINE_SCRIPTMANAGER_H
#define TREFUSISENGINE_SCRIPTMANAGER_H
#include "harlequin_api.hpp"
#include <Python.h>
#include <iostream>
#include <string>

class ScriptManager {
  private:
    PyObject *pModule;

  public:
    ScriptManager();
    ~ScriptManager();
    void loadScript(std::string fileName);
};

#endif // TREFUSISENGINE_SCRIPTMANAGER_H
