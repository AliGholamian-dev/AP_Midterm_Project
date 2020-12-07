#include "puzzle.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::array<std::array<int, 3>, 3> in = {
        std::array<int, 3> { 3, 1, 2 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 8, 7, 0 }
    };
    std::array<std::array<int, 3>, 3> fi = {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 8, 7, 0 }
    };
    Puzzle a { in, fi };
    a.Solve_Puzzle(10000);
    return 0;
}