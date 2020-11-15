// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <Python.h>

namespace PyScripting
{

struct DolphinModuleState;

void SetupDolphinModule(PyObject* module, DolphinModuleState* state);
void CleanupDolphinModule(PyObject* module, DolphinModuleState* state);
PyMODINIT_FUNC PyInit_dolphin();

}  // namespace PyScripting
