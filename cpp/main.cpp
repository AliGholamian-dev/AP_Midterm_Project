#include "puzzle.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::array<std::array<int, 3>, 3> in = {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 5, 6, 0 },
        std::array<int, 3> { 7, 8, 4 }
    };
    std::array<std::array<int, 3>, 3> fi = {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 5, 8, 6 },
        std::array<int, 3> { 0, 7, 4 }
    };
    Puzzle a { in, fi };
    a.Solve_Puzzle(100);
    return 0;
}