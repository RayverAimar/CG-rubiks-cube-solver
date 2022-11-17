#include "./solver_cube.h"
#include "./cross.h"
#include "./corners.h"
#include "./edges.h"
#include "./OLL.h"
#include "./PLL.h"

#include <string>

namespace solver{

std::string format_solution(std::string);

std::string solve(std::string argString) {
    SolverCube myCube(false);
    std::string scramble = format_solution(argString);
    myCube.moves(scramble, false);
    Cross::solveCross(myCube);
    Corners::solveCorners(myCube);
    Edges::solveEdges(myCube);
    OLL::solveOLL(myCube);
    PLL::solvePLL(myCube);
    return myCube.solution;
}

std::string format_movements(std::string str)
{
    std::string ans;
    for (int i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
            case F_MOVEMENT:
                ans.push_back(F_MOVEMENT);
                break;
            case B_MOVEMENT:
                ans.push_back(B_MOVEMENT);
                break;
            case R_MOVEMENT:
                ans.push_back(R_MOVEMENT);
                break;
            case L_MOVEMENT:
                ans.push_back(L_MOVEMENT);
                break;
            case D_MOVEMENT:
                ans.push_back(D_MOVEMENT);
                break;
            case U_MOVEMENT:
                ans.push_back(U_MOVEMENT);
                break;
            case M_MOVEMENT:
                ans.push_back(M_MOVEMENT);
                break;
            case E_MOVEMENT:
                ans.push_back(E_MOVEMENT);
                break;
            case S_MOVEMENT:
                ans.push_back(S_MOVEMENT);
                break;
            case F_PRIME_MOVEMENT:
                ans.push_back(F_MOVEMENT);
                ans.push_back('\'');
                break;
            case B_PRIME_MOVEMENT:
                ans.push_back(B_MOVEMENT);
                ans.push_back('\'');
                break;
            case R_PRIME_MOVEMENT:
                ans.push_back(R_MOVEMENT);
                ans.push_back('\'');
                break;
            case L_PRIME_MOVEMENT:
                ans.push_back(L_MOVEMENT);
                ans.push_back('\'');
                break;
            case D_PRIME_MOVEMENT:
                ans.push_back(D_MOVEMENT);
                ans.push_back('\'');
                break;
            case U_PRIME_MOVEMENT:
                ans.push_back(U_MOVEMENT);
                ans.push_back('\'');
                break;
            case M_PRIME_MOVEMENT:
                ans.push_back(M_MOVEMENT);
                ans.push_back('\'');
                break;
            case E_PRIME_MOVEMENT:
                ans.push_back(E_MOVEMENT);
                ans.push_back('\'');
                break;
            case S_PRIME_MOVEMENT:
                ans.push_back(S_MOVEMENT);
                ans.push_back('\'');
                break;
            default:
                break;
        }
        ans.push_back(' ');
    }
    ans.pop_back();
    return ans;
}

std::string format_solution(std::string s)
    {
        std::string formatted;
        for (int i=0; i<s.length(); ++i)
        {
            if (s[i] == '\'')
            {
                char movement = s[i - 1];
                formatted.pop_back();
                switch (movement)
                {
                    case F_MOVEMENT:
                        formatted.push_back(F_PRIME_MOVEMENT);
                        break;
                    case B_MOVEMENT:
                        formatted.push_back(B_PRIME_MOVEMENT);
                        break;
                    case D_MOVEMENT:
                        formatted.push_back(D_PRIME_MOVEMENT);
                        break;
                    case U_MOVEMENT:
                        formatted.push_back(U_PRIME_MOVEMENT);
                        break;
                    case L_MOVEMENT:
                        formatted.push_back(L_PRIME_MOVEMENT);
                        break;
                    case R_MOVEMENT:
                        formatted.push_back(R_PRIME_MOVEMENT);
                        break;
                    case M_MOVEMENT:
                        formatted.push_back(M_PRIME_MOVEMENT);
                        break;
                    case E_MOVEMENT:
                        formatted.push_back(E_PRIME_MOVEMENT);
                        break;
                    case S_MOVEMENT:
                        formatted.push_back(S_PRIME_MOVEMENT);
                        break;
                    default:
                        break;
                }
            }
            else if (s[i] == '2')
            {
                formatted += s[i-1];
            }
            else if (s[i] == ' ')
            {
            }
            else {
                formatted += s[i];
            }
        }
      return formatted;
    }

}