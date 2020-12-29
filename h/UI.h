#ifndef UI_H
#define UI_H

#include <array>
#include <iostream>
#include <random>
#include <string>

/**
 * Checks if user wants to Re-run program 
 * @param  {int} text_color : Color of text for UI
 * @return {bool}           : Whether re-run program or not
 */
bool ReRun(int text_color);

/**
 * Checks if a puzzle is solvable
 * @param  {std::array<std::array<int, 3>, 3>} initial   : Initial state of Puzzle
 * @param  {std::array<std::array<int, 3>, 3>} goal      : Goal state of Puzzle
 * @return {bool}                                        : Puzzle is solvable or not
 */
bool is_Solvable(
    const std::array<std::array<int, 3>, 3>& initial,
    const std::array<std::array<int, 3>, 3>& goal);

/**
 * Sets init and goal puzzle and UI Colors based on users preferences
 * @param  {std::array<std::array<int, 3>, 3>&} initial  : Initial state of Puzzle
 * @param  {std::array<std::array<int, 3>, 3>&} goal     : Goal state of Puzzle
 * @param  {std::array<int, 5>&}                settings : User settings
 */
void UI_Settings(
    std::array<std::array<int, 3>, 3>& initial,
    std::array<std::array<int, 3>, 3>& goal,
    std::array<int, 5>& settings);

#endif