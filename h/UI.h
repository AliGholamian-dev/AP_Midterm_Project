#ifndef UI_H
#define UI_H

#include <array>
#include <iostream>
#include <random>
#include <string>

bool is_Solvable(const std::array<std::array<int, 3>, 3>& initial, const std::array<std::array<int, 3>, 3>& goal);
void UI_Settings(std::array<std::array<int, 3>, 3>& initial, std::array<std::array<int, 3>, 3>& goal, std::array<int, 4>& settings);

#endif