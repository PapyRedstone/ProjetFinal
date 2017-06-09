#include "aStar.h"

int aStar(Robot *rob, char *filename) {
  PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;

  // Initialize the Python Interpreter
  Py_Initialize();

  // Build the name object
  // pName = PyString_FromString("call_function");

  // // Load the module object
  // pModule = PyImport_Import(pName);

  // // pDict is a borrowed reference
  // pDict = PyModule_GetDict(pModule);

  // // pFunc is also a borrowed reference
  // pFunc = PyDict_GetItemString(pDict, "aStar");

  pArgs = PyTuple_New(5);

  pValue = PyString_FromString(filename);
  PyTuple_SetItem(pArgs, 0, pValue);
  pValue = PyInt_FromLong(rob->position.x);
  PyTuple_SetItem(pArgs, 1, pValue);
  pValue = PyInt_FromLong(rob->position.y);
  PyTuple_SetItem(pArgs, 2, pValue);
  pValue = PyInt_FromLong(rob->path->position.x);
  PyTuple_SetItem(pArgs, 3, pValue);
  pValue = PyInt_FromLong(rob->path->position.y);
  PyTuple_SetItem(pArgs, 4, pValue);

  if (pValue = PyCallable_Check(pFunc)) {
    PyObject_CallObject(pFunc, pArgs);
  } else {
    PyErr_Print();
  }

  // Clean up
  Py_DECREF(pModule);
  Py_DECREF(pName);

  // Finish the Python Interpreter
  Py_Finalize();

  return PyInt_AsLong(pValue);
}
