#include "UI.h"
#include "puzzle.h"

int main(int argc, char** argv)
{
    std::array<std::array<int, 3>, 3> initial {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 7, 8, 0 }
    };
    std::array<std::array<int, 3>, 3> goal {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 7, 8, 0 }
    };
    std::array<int, 4> settings { 1, 1, 1000, 100 };
    UI_Settings(initial, goal, settings);
    Puzzle New_Puzzle { initial, goal };
    New_Puzzle.Solve_Puzzle(settings);
    return 0;
}