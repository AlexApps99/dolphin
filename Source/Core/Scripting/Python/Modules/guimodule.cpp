// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "guimodule.h"

#include "Common/Logging/Log.h"
#include "Core/API/Gui.h"
#include "Scripting/Python/PyScriptingBackend.h"
#include "Scripting/Python/Utils/module.h"

namespace PyScripting
{

void add_osd_message(PyObject* self, const char* message, u32 duration_ms, u32 color_argb)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->AddOSDMessage(std::string(message), duration_ms, color_argb);
}

void clear_osd_messages(PyObject* self)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->ClearOSDMessages();
}

PyObject* get_display_size(PyObject* self, PyObject* args)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  auto size = state->gui->GetDisplaySize();
  return Py_BuildValue("(ff)", size.x, size.y);
}

void draw_line(PyObject* self, float ax, float ay, float bx, float by, u32 color, float thickness)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawLine({ax, ay}, {bx, by}, color, thickness);
}

void draw_rect(PyObject* self, float ax, float ay, float bx, float by, u32 color,
               float rounding, float thickness)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawRect({ax, ay}, {bx, by}, color, rounding, thickness);
}

void draw_rect_filled(PyObject* self, float ax, float ay, float bx, float by, u32 color,
                      float rounding)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawRectFilled({ax, ay}, {bx, by}, color, rounding);
}

void draw_quad(PyObject* self, float ax, float ay, float bx, float by, float cx, float cy, float dx,
               float dy, u32 color, float thickness)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawQuad({ax, ay}, {bx, by}, {cx, cy}, {dx, dy}, color, thickness);
}

void draw_quad_filled(PyObject* self, float ax, float ay, float bx, float by, float cx, float cy,
                      float dx, float dy, u32 color)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawQuadFilled({ax, ay}, {bx, by}, {cx, cy}, {dx, dy}, color);
}

void draw_triangle(PyObject* self, float ax, float ay, float bx, float by, float cx, float cy,
                   u32 color, float thickness)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawTriangle({ax, ay}, {bx, by}, {cx, cy}, color, thickness);
}

void draw_triangle_filled(PyObject* self, float ax, float ay, float bx, float by, float cx,
                          float cy, u32 color)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawTriangleFilled({ax, ay}, {bx, by}, {cx, cy}, color);
}

void draw_circle(PyObject* self, float centerX, float centerY, float radius, u32 color,
                 int num_segments, float thickness)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawCircle({centerX, centerY}, radius, color, num_segments, thickness);
}

void draw_circle_filled(PyObject* self, float centerX, float centerY, float radius, u32 color,
                        int num_segments)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawCircleFilled({centerX, centerY}, radius, color, num_segments);
}

void draw_text(PyObject* self, float posX, float posY, u32 color, const char* text)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawText({posX, posY}, color, std::string(text));
}

PyObject* draw_polyline(PyObject* self, PyObject* args)
{
  PyObject* points_list_obj;
  u32 color;
  bool closed;
  float thickness;
  if (!PyArg_ParseTuple(args, "O!Ipf", &PyList_Type, &points_list_obj, &color, &closed,
                        &thickness))
    return nullptr;
  int num_points = PyList_Size(points_list_obj);
  if (num_points < 0)
    return nullptr;
  std::vector<Vec2f> points_collecting;
  for (int i = 0; i < num_points; ++i)
  {
    PyObject* item = PyList_GetItem(points_list_obj, i);
    float x, y;
    if (!PyArg_ParseTuple(item, "ff", &x, &y))
      return nullptr;
    points_collecting.push_back({x, y});
  }
  const std::vector<Vec2f> points = points_collecting;
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawPolyline(points, color, closed, thickness);
  Py_RETURN_NONE;
}

PyObject* draw_convex_poly_filled(PyObject* self, PyObject* args)
{
  PyObject* points_list_obj;
  u32 color;
  if (!PyArg_ParseTuple(args, "O!I", &PyList_Type, &points_list_obj, &color))
    return nullptr;
  int num_points = PyList_Size(points_list_obj);
  if (num_points < 0)
    return nullptr;
  std::vector<Vec2f> points;
  for (int i = 0; i < num_points; ++i)
  {
    PyObject* item = PyList_GetItem(points_list_obj, i);
    float x, y;
    if (!PyArg_ParseTuple(item, "ff", &x, &y))
      return nullptr;
    points.push_back({x, y});
  }
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawConvexPolyFilled(points, color);
  Py_RETURN_NONE;
}

void draw_bezier_curve(PyObject* self, float pos0x, float pos0y, float cp0x, float cp0y, float cp1x,
                       float cp1y, float pos1x, float pos1y, u32 color, float thickness,
                       int num_segments)
{
  GuiModuleState* state = Py::GetState<GuiModuleState>(self);
  state->gui->DrawBezierCurve({pos0x, pos0y}, {cp0x, cp0y}, {cp1x, cp1y}, {pos1x, pos1y}, color,
                              thickness, num_segments);
}

void SetupGuiModule(PyObject* module, GuiModuleState* state)
{
  static const char pycode[] = R"(
def add_osd_message(message: str, duration_ms: int = 2000, color_argb: int = 0xFFFFFF30):
    return _add_osd_message(message, duration_ms, color_argb)

def draw_line(a, b, color, thickness = 1):
    _draw_line(a[0], a[1], b[0], b[1], color, thickness)

def draw_rect(a, b, color, rounding = 0, thickness = 1):
    _draw_rect(a[0], a[1], b[0], b[1], color, rounding, thickness)

def draw_rect_filled(a, b, color, rounding= 0):
    _draw_rect_filled(a[0], a[1], b[0], b[1], color, rounding)

def draw_quad(a, b, c, d, color, thickness = 1):
    _draw_quad(a[0], a[1], b[0], b[1], c[0], c[1], d[0], d[1], color, thickness)

def draw_quad_filled(a, b, c, d, color):
    _draw_quad_filled(a[0], a[1], b[0], b[1], c[0], c[1], d[0], d[1], color)

def draw_triangle(a, b, c, color, thickness = 1):
    _draw_triangle(a[0], a[1], b[0], b[1], c[0], c[1], color, thickness)

def draw_triangle_filled(a, b, c, color):
    _draw_triangle_filled(a[0], a[1], b[0], b[1], c[0], c[1], color)

def draw_circle(center, radius, color, num_segments = None, thickness = 1):
    if num_segments is None:
        num_segments = 8 + int(radius // 50)
    _draw_circle(center[0], center[1], radius, color, num_segments, thickness)

def draw_circle_filled(center, radius, color, num_segments = None):
    if num_segments is None:
        num_segments = 8 + int(radius // 50)
    _draw_circle_filled(center[0], center[1], radius, color, num_segments)

def draw_text(pos, color, text):
    _draw_text(pos[0], pos[1], color, text)

def draw_polyline(points, color, closed = False, thickness = 1):
    _draw_polyline(points, color, closed, thickness)

def draw_convex_poly_filled(points, color):
    _draw_convex_poly_filled(points, color)

def draw_bezier_curve(pos0, cp0, cp1, pos1, color, thickness = 1, num_segments = 0):
    _draw_bezier_curve(pos0[0], pos0[1], cp0[0], cp0[1], cp1[0], cp1[1], pos1[0], pos1[1], color, thickness, num_segments)
)";
  Py::Object result = Py::LoadPyCodeIntoModule(module, pycode);
  if (result.IsNull())
  {
    ERROR_LOG(SCRIPTING, "Failed to load embedded python code into gui module");
  }
  API::Gui* gui = PyScripting::PyScriptingBackend::GetCurrent()->GetGui();
  state->gui = gui;
}

void CleanupGuiModule(PyObject* module, GuiModuleState* state)
{
}

PyMODINIT_FUNC PyInit_gui()
{
  static PyMethodDef methods[] = {
      {"_add_osd_message", Py::as_py_func<add_osd_message>, METH_VARARGS, ""},
      {"clear_osd_messages", Py::as_py_func<clear_osd_messages>, METH_VARARGS, ""},

      {"get_display_size", get_display_size, METH_NOARGS, ""},
      {"_draw_line", Py::as_py_func<draw_line>, METH_VARARGS, ""},
      {"_draw_rect", Py::as_py_func<draw_rect>, METH_VARARGS, ""},
      {"_draw_rect_filled", Py::as_py_func<draw_rect_filled>, METH_VARARGS, ""},
      {"_draw_quad", Py::as_py_func<draw_quad>, METH_VARARGS, ""},
      {"_draw_quad_filled", Py::as_py_func<draw_quad_filled>, METH_VARARGS, ""},
      {"_draw_triangle", Py::as_py_func<draw_triangle>, METH_VARARGS, ""},
      {"_draw_triangle_filled", Py::as_py_func<draw_triangle_filled>, METH_VARARGS, ""},
      {"_draw_circle", Py::as_py_func<draw_circle>, METH_VARARGS, ""},
      {"_draw_circle_filled", Py::as_py_func<draw_circle_filled>, METH_VARARGS, ""},
      {"_draw_text", Py::as_py_func<draw_text>, METH_VARARGS, ""},
      {"_draw_polyline", draw_polyline, METH_VARARGS, ""},
      {"_draw_convex_poly_filled", draw_convex_poly_filled, METH_VARARGS, ""},
      {"_draw_bezier_curve", Py::as_py_func<draw_bezier_curve>, METH_VARARGS, ""},

      {nullptr, nullptr, 0, nullptr}  // Sentinel
  };
  static PyModuleDef module_def =
      Py::MakeStatefulModuleDef<GuiModuleState, SetupGuiModule, CleanupGuiModule>("gui", methods);
  PyObject* def_obj = PyModuleDef_Init(&module_def);
  return def_obj;
}

}  // namespace PyScripting
