/*
 * g++ pywrap.cc -std=c++11 -fPIC -shared -DSUPPORT_PYTHON3 -I$PYTHON3_INC
 * -o release/libpywrap.so
 * python3 test_pywrap.py
 */

#include <Python.h>
#include <iostream>
#include <vector>
#include "doX.h"
#include "pthinf.h"

extern "C" {

const char* VERSION = "v0.0.1";

static PyObject* func1(PyObject* self, PyObject* args) {
  char* arg1 = nullptr;
  int m;

  if (PyArg_ParseTuple(args, "si", &arg1, &m)) {
    std::vector<pthinf> tasks;
    tasks_collection(arg1, tasks);
    do_X(tasks, m);
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

static PyObject* func2(PyObject* self, PyObject* args) {
  char* arg1 = nullptr;
  char* arg2 = nullptr;

  if (PyArg_ParseTuple(args, "ss", &arg1, &arg2)) {
    std::cout << arg1 << " " << arg2 << std::endl;
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

#ifdef SUPPORT_PYTHON3

#define PYFUNC(name) \
  { #name, (PyCFunction)name, METH_VARARGS, "" }
#define PYENDFUNC \
  { nullptr, nullptr, 0, nullptr }

PyMethodDef* get_all_methods() {
  static PyMethodDef g_python_methods[]{
      PYFUNC(func1),
      PYFUNC(func2),
      PYENDFUNC,
  };
  return g_python_methods;
}

static struct PyModuleDef libpywrap = {PyModuleDef_HEAD_INIT, "libpywrap", "",
                                       -1, get_all_methods()};

PyMODINIT_FUNC PyInit_libpywrap(void) {
  printf("%s\n", VERSION);
  return PyModule_Create(&libpywrap);
}

#else  // PYTHON2

#define PYFUNC(name) \
  { #name, name, METH_VARARGS, "" }
#define PYENDFUNC \
  { nullptr, nullptr, 0, nullptr }

PyMethodDef* get_all_methods() {
  static PyMethodDef g_python_methods[]{
      PYFUNC(func1),
      PYFUNC(func2),
      PYENDFUNC,
  };
  return g_python_methods;
}

PyMODINIT_FUNC initlibpywrap() {
  printf("%s\n", VERSION);
  PyObject* module = Py_InitModule("libpywrap", get_all_methods());
  if (module == nullptr) return;
}
#endif  // SUPPORT_PYTHON3
}
