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
        std::array<int, 3> { 4, 2, 7 },
        std::array<int, 3> { 1, 5, 6 },
        std::array<int, 3> { 8, 3, 0 }
    };
    Puzzle a { in, fi };
    a.Solve_Puzzle(1000);
    std::cout << "New puzzle" << std::endl;
    std::array<std::array<int, 3>, 3> in2 = {
        std::array<int, 3> { 1, 7, 6 },
        std::array<int, 3> { 4, 5, 0 },
        std::array<int, 3> { 3, 2, 8 }
    };
    std::array<std::array<int, 3>, 3> fi2 = {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 7, 8, 0 }
    };

    a.Set_New_Matrixes(in2, fi2);
    a.Solve_Puzzle(1000);
    return 0;
}