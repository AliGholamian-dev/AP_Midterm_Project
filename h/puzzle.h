#ifndef PUZZLE_H
#define PUZZLE_H

#include <array>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
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
    std::array<std::array<int, 3>, 3> initial_puzzle;
    std::array<std::array<int, 3>, 3> goal_puzzle;
    std::array<int, 4> row = { 1, 0, 0, -1 };
    std::array<int, 4> col = { 0, -1, 1, 0 };
    void Show_Solution(const std::shared_ptr<Node>& all_nodes, int mode) const;

public:
    Puzzle(const std::array<std::array<int, 3>, 3>& initial_puzzle, const std::array<std::array<int, 3>, 3>& goal_puzzle);
    void Set_New_Matrixes(const std::array<std::array<int, 3>, 3>& initial_puzzle, const std::array<std::array<int, 3>, 3>& goal_puzzle);
    void Solve_Puzzle(int _max_depth);
};

#endif