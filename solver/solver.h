#include "./cube.h"
#include "./cross.h"
#include "./corners.h"
#include "./edges.h"
#include "./OLL.h"
#include "./PLL.h"

#include <string>

namespace rubik{

std::string format(std::string);

std::string solve(std::string argString) {
  Cube myCube(false);
  std::string scramble = format(argString);
  myCube.moves(scramble, false);
  Cross::solveCross(myCube);
  Corners::solveCorners(myCube);
  Edges::solveEdges(myCube);
  OLL::solveOLL(myCube);
  PLL::solvePLL(myCube);
  return myCube.solution;
}

std::string format(std::string s) {
  std::string formatted;
  for (int i=0; i<s.length(); ++i) {
    if (s[i] == '\'') {
      formatted += s[i-1];
      formatted += s[i-1];
    }
    else if (s[i] == '2') {
      formatted += s[i-1];
    }
    else if (s[i] == ' ') {
    }
    else {
      formatted += s[i];
    }
  }
  return formatted;
}

}