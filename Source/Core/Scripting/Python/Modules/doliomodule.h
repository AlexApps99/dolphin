// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <Python.h>
#include <sstream>

namespace PyScripting
{
// keep in mind this spaicng for others
struct DolioModuleState {
  std::stringstream buffer;
};

void flush_stdout(PyObject* module);

void flush_stderr(PyObject* module);

void dol_write_stdout(PyObject* module, const char* what);

void dol_write_stderr(PyObject* module, const char* what);

void setup_dolio_module_stdout(PyObject* module, DolioModuleState* state);

void setup_dolio_module_stderr(PyObject* module, DolioModuleState* state);

void cleanup_dolio_module(PyObject* module, DolioModuleState* state);

PyMODINIT_FUNC PyInit_dolio_stdout();

PyMODINIT_FUNC PyInit_dolio_stderr();

}
