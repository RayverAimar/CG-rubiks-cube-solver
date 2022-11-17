#ifndef PLL_H
#define PLL_H

#include "./solver_cube.h"

class PLL {

public:
  static void solvePLL(SolverCube &);
  static void adjustUFace(SolverCube &);
  static void solveCorners(SolverCube &);
  static int checkCorners(SolverCube &);
  static int checkEdges(SolverCube &);
  static void solveEdges(SolverCube &);
};

void PLL::solvePLL(SolverCube &cube) {
  adjustUFace(cube);
  while (!checkCorners(cube)) {
    solveCorners(cube);
    adjustUFace(cube);
  }

  while (!checkEdges(cube)) {
    solveEdges(cube);
  }
}

void PLL::adjustUFace(SolverCube &cube) {
  while (cube.cubies[2][5] != 5 || cube.cubies[0][2] != 2) {
    cube.moves("U");
  }
}

void PLL::solveEdges(SolverCube &cube) {
  if (cube.cubies[1][2] == 5 && cube.cubies[1][3] == 2 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 3) {
    cube.moves("RRURURRRUUURRRUUURRRURRR");
  }
  else if (cube.cubies[1][2] == 3 && cube.cubies[1][3] == 5 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 2) {
    cube.moves("RUUURURURUUURRRUUURR");
  }
  else if (cube.cubies[1][2] == 4 && cube.cubies[1][3] == 5 && cube.cubies[1][4] == 2 && cube.cubies[1][5] == 3) {
    cube.moves("RRLLDRRLLUURRLLDRRLL");
  }
  else if (cube.cubies[1][2] == 3 && cube.cubies[1][3] == 2 && cube.cubies[1][4] == 5 && cube.cubies[1][5] == 4) {
    cube.moves("URRRUUURUUURURUUURRRURURRUUURRRU");
  }
  else {
    cube.moves("RRURURRRUUURRRUUURRRURRR");
    adjustUFace(cube);
    cube.moves("RRLLDRRLLUURRLLDRRLL");
    cube.moves("RRURURRRUUURRRUUURRRURRR");
    adjustUFace(cube);
  }
}

void PLL::solveCorners(SolverCube &cube) {
  if (cube.cubies[2][2] == 4 && cube.cubies[0][3] == 5 && cube.cubies[2][3] == 2
  && cube.cubies[0][4] == 3 && cube.cubies[2][4] == 3 && cube.cubies[0][5] == 4) {
    cube.moves("RRRFRRRBBRFFFRRRBBRR");
  }
  else if (cube.cubies[2][2] == 4 && cube.cubies[0][3] == 5 && cube.cubies[2][3] == 3
  && cube.cubies[0][4] == 4 && cube.cubies[2][4] == 2 && cube.cubies[0][5] == 3) {
    cube.moves("RBBBRRRFRBRRRFFLLLBLFLLLBBBL");
  }
  else {
    cube.moves("RRRFRRRBBRFFFRRRBBRR");
  }
}

int PLL::checkCorners(SolverCube &cube) {
  if (cube.cubies[0][2] != 2 || cube.cubies[2][2] != 2 || cube.cubies[0][3] != 3 || cube.cubies[2][3] != 3 || cube.cubies[0][4] != 4 || cube.cubies[2][4] != 4 || cube.cubies[0][5] != 5 || cube.cubies[2][5] != 5) {
    return 0;
  }
  else
    return 1;
}

int PLL::checkEdges(SolverCube &cube) {
    if (cube.cubies[1][2] == 2 && cube.cubies[1][3] == 3 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 5) {
      return 1;
    }
    else {
      return 0;
    }
}

#endif