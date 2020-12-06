#include "puzzle.h"

Puzzle::Node::Node(std::array<std::array<int, 3>, 3> mat, std::shared_ptr<Node> parent)
{
    this->mat = mat;
    this->parent_of_node = parent;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (this->mat[i][j] == 0) {
                this->zero_y = i;
                this->zero_x = j;
            }
}

Puzzle::Puzzle(std::array<std::array<int, 3>, 3> initial_puzzle, std::array<std::array<int, 3>, 3> goal_puzzle)
{
    this->initial_puzzle = initial_puzzle;
    this->goal_puzzle = goal_puzzle;
}

int Puzzle::Calculate_Cost(std::shared_ptr<Node> input_node)
{
    int cost = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (input_node->mat[i][j] != 0 && input_node->mat[i][j] != this->goal_puzzle[i][j])
                cost++;
    return cost;
}

void Puzzle::Solve_Puzzle(int _max_depth)
{
    int depth_counetr = 0;

    auto compare_lambda { [&](const std::shared_ptr<Node> first_node, const std::shared_ptr<Node> second_node) { return this->Calculate_Cost(first_node) > this->Calculate_Cost(second_node); } };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(compare_lambda)> Container_of_Nodes(compare_lambda);

    std::shared_ptr<Node> root { std::make_shared<Node>(this->initial_puzzle, nullptr) };

    Container_of_Nodes.push(root);

    while (!Container_of_Nodes.empty()) {
        depth_counetr++;
        std::shared_ptr<Node> low_cost_node { Container_of_Nodes.top() };

        Container_of_Nodes.pop();

        if (Calculate_Cost(low_cost_node) == 0) {
            this->Show_Solution(low_cost_node);
            return;
        } else if (depth_counetr >= _max_depth) {
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (this->Check_Coordinates(low_cost_node->zero_x + this->row[i], low_cost_node->zero_y + this->col[i])) {
                std::array<std::array<int, 3>, 3> temp { low_cost_node->mat };
                std::swap(temp[low_cost_node->zero_y][low_cost_node->zero_x], temp[low_cost_node->zero_y + this->col[i]][low_cost_node->zero_x + this->row[i]]);
                std::shared_ptr<Node> child { std::make_shared<Node>(temp, low_cost_node) };
                Container_of_Nodes.push(child);
            }
        }
    }
}

void Puzzle::Show_Solution(std::shared_ptr<Node> final_node) const
{
    if (final_node == nullptr)
        return;
    this->Show_Solution(final_node->parent_of_node);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++)
            std::cout << final_node->mat[i][j] << "    ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}