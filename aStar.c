#include "aStar.h"

int astar(Robot *rob, char *filename, PythonObj *python) {
  PyObject *pFunc, *pValue, *pArgs;

  // pFunc is also a borrowed reference
  pFunc = PyDict_GetItemString(python->pDict, "pathfinding");

  pArgs = PyTuple_New(5);

  //Initialisation des arguments utiliser par astar
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

  //appel de la fonction
  if (PyCallable_Check(pFunc)) {
    pValue = PyObject_CallObject(pFunc, pArgs);
  } else {
    PyErr_Print();
  }

  return PyInt_AsLong(pValue);
}
