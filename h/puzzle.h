#ifndef PUZZLE_H
#define PUZZLE_H

#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <thread>
#include <vector>

class Puzzle {
private:
    class Node {
    public:
        Node(const std::array<std::array<int, 3>, 3>& mat, int level, int came_from, const std::shared_ptr<Node>& parent);
        bool operator==(const Node& second_node) const;
        std::shared_ptr<Node> parent_of_node;
        std::array<std::array<int, 3>, 3> mat;
        int zero_x, zero_y, level, came_from;
    };
    bool is_Solvable();
    bool Check_Coordinates(int x, int y) { return (x >= 0 && x < 3 && y >= 0 && y < 3); };
    int Calculate_Cost(const std::shared_ptr<Node>& input_node, int mode) const;
    mutable int step { 1 };
    std::array<std::array<int, 3>, 3> initial_puzzle;
    std::array<std::array<int, 3>, 3> goal_puzzle;
    std::array<int, 4> row { 1, 0, 0, -1 };
    std::array<int, 4> col { 0, -1, 1, 0 };
    void Show_Solution(const std::shared_ptr<Node>& all_nodes, const int& mode, const int& text_color, const int& border_color, const int& time_interval) const;

public:
    Puzzle(const std::array<std::array<int, 3>, 3>& initial_puzzle, const std::array<std::array<int, 3>, 3>& goal_puzzle);
    void Set_New_Matrixes(const std::array<std::array<int, 3>, 3>& initial_puzzle, const std::array<std::array<int, 3>, 3>& goal_puzzle);
    void Solve_Puzzle(const std::array<int, 4>& settings);
};

#endif