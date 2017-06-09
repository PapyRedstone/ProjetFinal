#include "aStar.h"

int aStar() {
  Py_Initialize();

  PyRun_SimpleString("import aStar.py");
  PyRun_SimpleString("pathfinding()");

  Py_Finalize();
}