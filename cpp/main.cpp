#include "UI.h"
#include "puzzle.h"

int main(int argc, char** argv)
{
    // generate default puzzles
    std::array<int, 5> settings { 1, 1, 1000, 100, 0 };
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
    // Create an object of puzzle class an pass default puzzles
    Puzzle New_Puzzle { initial, goal };
    // Re-run program if user tends to do so
    do {
        // Ask for user's prefernces
        UI_Settings(initial, goal, settings);
        // Set puzzles to new puzzles
        New_Puzzle.Set_New_Matrixes(initial, goal);
        // Solve puzzle
        New_Puzzle.Solve_Puzzle(settings);
    } while (ReRun(settings[0]));

    return 0;
}
