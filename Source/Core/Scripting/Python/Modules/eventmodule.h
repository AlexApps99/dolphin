// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>
#include <deque>
#include <optional>
#include <Python.h>

#include "Scripting/Python/Utils/object_wrapper.h"
#include "Core/API/Events.h"
#include <functional>

namespace PyScripting
{

struct EventModuleState
{
  API::EventHub* event_hub;
  std::optional<std::function<void()>> cleanup_listeners;
  Py::Object callback;
  std::deque<Py::Object> awaiting_coroutines;
};

PyMODINIT_FUNC PyInit_event();

using CoroutineScheduler = void(*)(const Py::Object, const Py::Object);
std::optional<CoroutineScheduler> GetCoroutineScheduler(std::string aeventname);

void SetupEventModule(PyObject* module, EventModuleState* state);
void CleanupEventModule(PyObject* module, EventModuleState* state);

}
