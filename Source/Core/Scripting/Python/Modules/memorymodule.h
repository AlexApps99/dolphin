// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <Python.h>

namespace PyScripting
{

struct MemoryModuleState
{
  // If Memory wasn't static, you'd store the memory instance here:
  //API::Memory* memory;
};

void SetupMemoryModule(PyObject* module, MemoryModuleState* state);

void CleanupMemoryModule(PyObject* module, MemoryModuleState* state);

PyMODINIT_FUNC PyInit_memory();

}
