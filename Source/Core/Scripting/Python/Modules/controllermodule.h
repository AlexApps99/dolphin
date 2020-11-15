// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <Python.h>
#include "Core/API/Controller.h"
#include "Core/HW/GCPad.h"
#include "Core/HW/Wiimote.h"

namespace PyScripting
{

struct ControllerModuleState
{
  API::GCManip* gc_manip;
  API::WiiManip* wii_manip;
};

PyObject* GCPadStatusToPyDict(GCPadStatus status);

GCPadStatus GCPadStatusFromPyDict(PyObject* dict);

PyObject* WiiButtonDataToPyDict(WiimoteCommon::ButtonData status);

WiimoteCommon::ButtonData WiiButtonDataFromPyDict(PyObject* dict);

PyObject* get_gc_buttons(PyObject* module, PyObject* args);

PyObject* set_gc_buttons(PyObject* module, PyObject* args);

PyObject* get_wii_buttons(PyObject* module, PyObject* args);

PyObject* set_wii_buttons(PyObject* module, PyObject* args);

void setup_controller_module(PyObject* module, ControllerModuleState* state);

void cleanup_controller_module(PyObject* module, ControllerModuleState* state);

PyMODINIT_FUNC PyInit_controller();

}  // namespace PyScripting
