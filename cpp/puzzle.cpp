#include "puzzle.h"

Puzzle::Node::Node(std::array<std::array<int, 3>, 3> mat, int level, std::shared_ptr<Node> parent)
{
    this->level = level;
    this->mat = mat;
    this->parent_of_node = parent;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (this->mat[i][j] == 0) {
                this->zero_y = i;
                this->zero_x = j;
            }
}
bool Puzzle::Node::operator==(const Node& second_node) const
{
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (this->mat[i][j] != second_node.mat[i][j])
                return false;
    return true;
}

Puzzle::Puzzle(std::array<std::array<int, 3>, 3> initial_puzzle, std::array<std::array<int, 3>, 3> goal_puzzle)
{
    this->initial_puzzle = initial_puzzle;
    this->goal_puzzle = goal_puzzle;
}

int Puzzle::Calculate_Cost(std::shared_ptr<Node> input_node, int mode)
{
    int cost = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (input_node->mat[i][j] != 0) {
                if (mode == 0 && input_node->mat[i][j] != this->goal_puzzle[i][j])
                    cost++;
                else if (mode == 1 && input_node->mat[i][j] != this->initial_puzzle[i][j])
                    cost++;
            }
    return cost;
}

void Puzzle::Solve_Puzzle(int _max_depth)
{
    auto compare_lambda { [&](const std::shared_ptr<Node> first_node, const std::shared_ptr<Node> second_node) { return this->Calculate_Cost(first_node, 0) + first_node->level > this->Calculate_Cost(second_node, 0) + second_node->level; } };
    auto compare_lambda_reverse { [&](const std::shared_ptr<Node> first_node, const std::shared_ptr<Node> second_node) { return this->Calculate_Cost(first_node, 1) + first_node->level > this->Calculate_Cost(second_node, 1) + second_node->level; } };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(compare_lambda)> Container_of_Nodes(compare_lambda);
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(compare_lambda_reverse)> Container_of_Nodes_reverse(compare_lambda_reverse);

    std::shared_ptr<Node> root { std::make_shared<Node>(this->initial_puzzle, 0, nullptr) };
    std::shared_ptr<Node> goal_root { std::make_shared<Node>(this->goal_puzzle, 0, nullptr) };

    Container_of_Nodes.push(root);
    Container_of_Nodes_reverse.push(goal_root);

    while (!Container_of_Nodes.empty() || !Container_of_Nodes_reverse.empty()) {
        std::shared_ptr<Node> low_cost_node { Container_of_Nodes.top() };
        std::shared_ptr<Node> low_cost_node_reverse { Container_of_Nodes_reverse.top() };

        Container_of_Nodes.pop();
        Container_of_Nodes_reverse.pop();

        if (Calculate_Cost(low_cost_node, 0) == 0) {
            this->Show_Solution(low_cost_node, 0);
            return;
        } else if (Calculate_Cost(low_cost_node_reverse, 1) == 0) {
            this->Show_Solution(low_cost_node_reverse, 1);
            return;
        } else if (*low_cost_node == *low_cost_node_reverse) {
            this->Show_Solution(low_cost_node, 0);
            this->Show_Solution(low_cost_node_reverse->parent_of_node, 1);
            return;
        } else if (low_cost_node->level >= _max_depth || low_cost_node_reverse->level >= _max_depth) {
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (this->Check_Coordinates(low_cost_node->zero_x + this->row[i], low_cost_node->zero_y + this->col[i])) {
                std::array<std::array<int, 3>, 3> temp { low_cost_node->mat };
                std::swap(temp[low_cost_node->zero_y][low_cost_node->zero_x], temp[low_cost_node->zero_y + this->col[i]][low_cost_node->zero_x + this->row[i]]);
                std::shared_ptr<Node> child { std::make_shared<Node>(temp, low_cost_node->level + 1, low_cost_node) };
                Container_of_Nodes.push(child);
            }

            if (this->Check_Coordinates(low_cost_node_reverse->zero_x + this->row[i], low_cost_node_reverse->zero_y + this->col[i])) {
                std::array<std::array<int, 3>, 3> temp { low_cost_node_reverse->mat };
                std::swap(temp[low_cost_node_reverse->zero_y][low_cost_node_reverse->zero_x], temp[low_cost_node_reverse->zero_y + this->col[i]][low_cost_node_reverse->zero_x + this->row[i]]);
                std::shared_ptr<Node> child { std::make_shared<Node>(temp, low_cost_node_reverse->level + 1, low_cost_node_reverse) };
                Container_of_Nodes_reverse.push(child);
            }
        }
    }
}

void Puzzle::Show_Solution(std::shared_ptr<Node> all_nodes, int mode) const
{
    if (all_nodes == nullptr)
        return;
    if (mode == 0)
        this->Show_Solution(all_nodes->parent_of_node, 0);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++)
            std::cout << all_nodes->mat[i][j] << "    ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if (mode == 1)
        this->Show_Solution(all_nodes->parent_of_node, 1);
}