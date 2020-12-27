#ifndef PUZZLE_H
#define PUZZLE_H

#include "UI.h"
#include <chrono>
#include <memory>
#include <queue>
#include <thread>
#include <vector>

class Puzzle {
private:
    // Nested class for Node (each state of puzzle is a node)
    class Node {
    public:
        /**
         * Node Constructor
         * @param  {std::array<std::array<int, 3>, 3>}  mat : Puzzle state
         * @param  {int} level                              : Depth of tree
         * @param  {int} came_from                          : Pervious move (avoid returnig to last state)
         * @param  {std::shared_ptr<Node>} parent           : Parent of current node
         */
        Node(
            const std::array<std::array<int, 3>, 3>& mat,
            int level,
            int came_from,
            const std::shared_ptr<Node>& parent);
        /**
         * Checks if two states are the same
         * @param  {Node} second_node : Second puzzle to compare to
         * @return {bool}             : Two states are the same or not
         */
        bool operator==(const Node& second_node) const;
        std::shared_ptr<Node> parent_of_node;
        std::array<std::array<int, 3>, 3> mat;
        int zero_x, zero_y, level, came_from;
    };
    // Avoid verbose writing
    using Node_ptr = std::shared_ptr<Node>;
    // Step of puzzle's answer
    mutable int step { 1 };
    std::array<std::array<int, 3>, 3> initial_puzzle;
    std::array<std::array<int, 3>, 3> goal_puzzle;
    // Indicators of four moves for empty square
    std::array<int, 4> row { 1, 0, 0, -1 };
    std::array<int, 4> col { 0, -1, 1, 0 };

    // Solvable function from "UI.h"
    friend bool is_Solvable(
        const std::array<std::array<int, 3>, 3>& initial,
        const std::array<std::array<int, 3>, 3>& goal);

    /**
     * Checks if the next coordinate is in range of puzzle coordinates
     * @param  {int} x : next coordinate's x
     * @param  {int} y : next coordinate's y
     * @return {bool}  : If the next coordinate is in range of puzzle coordinates
     */
    bool Check_Coordinates(int x, int y) { return (x >= 0 && x < 3 && y >= 0 && y < 3); };

    /**
     * Calculate number of puzzle's disorder for ( A* ) algorithm
     * @param  {Node_ptr} input_node : State to calculate it's cost
     * @param  {int} mode            : Compare to init or goal puzzle ( for Bidirectional) 
     * @return {int}                 : Number of puzzle's disorder
     */
    int Calculate_Cost(const Node_ptr& input_node, int mode) const;

    /**
     * Show Solution in a beautiful maner
     * @param  {Node_ptr} all_nodes : The sate of puzzle to start  from  
     * @param  {int} mode           : start from init or goal puzzle ( for Bidirectional) 
     * @param  {int} text_color     : Color of text
     * @param  {int} border_color   : Color of puzzle border
     * @param  {int} time_interval  : Delay time between showing each state of answer
     */
    void Show_Solution(
        const Node_ptr& all_nodes,
        const int& mode,
        const int& text_color,
        const int& border_color,
        const int& time_interval) const;

public:
    /**
     * Puzzle Constructor 
     * @param  {std::array<std::array<int, 3>, 3>}  initial_puzzle  : Init puzzle state 
     * @param  {std::array<std::array<int, 3>, 3>}  goal_puzzle     : Goal puzzle state
     */
    Puzzle(
        const std::array<std::array<int, 3>, 3>& initial_puzzle,
        const std::array<std::array<int, 3>, 3>& goal_puzzle);
    /**
     * Change init and goal state of puzzle
     * @param  {std::array<std::array<int, 3>, 3>} initial_puzzle   : Init puzzle state 
     * @param  {std::array<std::array<int, 3>, 3>} goal_puzzle      : Goal puzzle state
     */
    void Set_New_Matrixes(
        const std::array<std::array<int, 3>, 3>& initial_puzzle,
        const std::array<std::array<int, 3>, 3>& goal_puzzle);
    /**
     * Solves the puzzle
     * @param  {std::array<int, 4>} settings : Users prefrences 
     */
    void Solve_Puzzle(const std::array<int, 4>& settings);
};

#endif