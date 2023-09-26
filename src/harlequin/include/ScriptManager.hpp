//
// Created by elsa on 21.04.2020.
//

#ifndef HAILMARY_SCRIPTMANAGER_HPP
#define HAILMARY_SCRIPTMANAGER_HPP
#include "Python.h"
#include "harlequin_api.hpp"
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

#endif // HAILMARY_SCRIPTMANAGER_HPP