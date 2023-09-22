#ifndef TREFUSISENGINE_HARLEQUIN_HPP
#define TREFUSISENGINE_HARLEQUIN_HPP

#include "DialogManager.hpp"
#include <Python.h>

PyObject *harlequin_add_dialog(PyObject *self, PyObject *args);
static PyMethodDef harlequinMethods[] = {
    {"add_dialog", harlequin_add_dialog, METH_VARARGS, "Add a new dialog to the game."}, {NULL, NULL, 0, NULL}};
static PyModuleDef harlequinModule = {
    PyModuleDef_HEAD_INIT, "harlequin", NULL, -1, harlequinMethods, NULL, NULL, NULL, NULL};

static PyObject *PyInit_harlequin(void) { return PyModule_Create(&harlequinModule); }
#endif