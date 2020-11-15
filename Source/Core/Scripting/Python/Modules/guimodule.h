// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <Python.h>
#include "Core/API/Gui.h"

namespace PyScripting
{

struct GuiModuleState
{
  API::Gui* gui;
};

void add_osd_message(PyObject* self, const char* message, u32 duration_ms, u32 color_argb);

void clear_osd_messages(PyObject* self);

PyObject* get_display_size(PyObject* self, PyObject* args);

void draw_line(PyObject* self, float ax, float ay, float bx, float by, u32 color, float thickness = 1.0f);

void draw_rect(PyObject* self, float ax, float ay, float bx, float by, u32 color, float rounding = 0.0f, float thickness = 1.0f);

void draw_rect_filled(PyObject* self, float ax, float ay, float bx, float by, u32 color, float rounding = 0.0f);

void draw_quad(PyObject* self, float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy, u32 color, float thickness = 1.0f);

void draw_quad_filled(PyObject* self, float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy, u32 color);

void draw_triangle(PyObject* self, float ax, float ay, float bx, float by, float cx, float cy,
                   u32 color, float thickness = 1.0f);

void draw_triangle_filled(PyObject* self, float ax, float ay, float bx, float by, float cx,
                          float cy, u32 color);

void draw_circle(PyObject* self, float centerX, float centerY, float radius, u32 color,
                 int num_segments = 12, float thickness = 1.0f);

void draw_circle_filled(PyObject* self, float centerX, float centerY, float radius, u32 color,
                        int num_segments = 12);

void draw_text(PyObject* self, float posX, float posY, u32 color, const char* text);

PyObject* draw_polyline(PyObject* self, PyObject* args);

PyObject* draw_convex_poly_filled(PyObject* self, PyObject* args);

void draw_bezier_curve(PyObject* self, float pos0x, float pos0y, float cp0x, float cp0y, float cp1x,
                       float cp1y, float pos1x, float pos1y, u32 color, float thickness,
                       int num_segments = 0);

void SetupGuiModule(PyObject* module, GuiModuleState* state);

void CleanupGuiModule(PyObject* module, GuiModuleState* state);

PyMODINIT_FUNC PyInit_gui();

}  // namespace PyScripting
