// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <Python.h>

namespace PyScripting
{

struct SavestateModuleState
{
  // If State wasn't static, you'd store an instance here:
  //API::SavestateManager* stateManager; // or however it would be called
};

PyObject* SaveToSlot(PyObject* self, PyObject* args);

PyObject* LoadFromSlot(PyObject* self, PyObject* args);

PyObject* SaveToFile(PyObject* self, PyObject* args);

PyObject* LoadFromFile(PyObject* self, PyObject* args);

PyObject* SaveToBytes(PyObject* self, PyObject* args);

PyObject* LoadFromBytes(PyObject* self, PyObject* args);

void SetupSavestateModule(PyObject* module, SavestateModuleState* state);

void CleanupSavestateModule(PyObject* module, SavestateModuleState* state);

PyMODINIT_FUNC PyInit_savestate();

}
