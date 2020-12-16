#include "puzzle.h"

Puzzle::Node::Node(
    const std::array<std::array<int, 3>, 3>& mat,
    int level,
    int came_from,
    const Node_ptr& parent)
{
    this->came_from = came_from;
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

Puzzle::Puzzle(
    const std::array<std::array<int, 3>, 3>& initial_puzzle,
    const std::array<std::array<int, 3>, 3>& goal_puzzle)
{
    this->step = 1;
    this->initial_puzzle = initial_puzzle;
    this->goal_puzzle = goal_puzzle;
}

int Puzzle::Calculate_Cost(const Node_ptr& input_node, int mode) const
{
    int cost { 0 };
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

void Puzzle::Set_New_Matrixes(
    const std::array<std::array<int, 3>, 3>& initial_puzzle,
    const std::array<std::array<int, 3>, 3>& goal_puzzle)
{
    this->initial_puzzle = initial_puzzle;
    this->goal_puzzle = goal_puzzle;
}

void Puzzle::Solve_Puzzle(const std::array<int, 4>& settings)
{

    int text_color { settings[0] }, border_color { settings[1] }, _max_depth { settings[2] }, time_interval { settings[3] };
    this->step = 1;

    std::cout << "\n\u001b[s\u001b[u\u001b[H\u001b[2J";
    if (!is_Solvable(this->initial_puzzle, this->goal_puzzle)) {
        std::cout << "This Puzzle is not solvable" << std::endl;
        return;
    }
    std::cout << "Solving..." << std::endl;
    auto comp {
        [&](const Node_ptr& n1, const Node_ptr& n2) {
            return (this->Calculate_Cost(n1, 0) + n1->level) > (this->Calculate_Cost(n2, 0) + n2->level);
        }
    };
    auto rcomp {
        [&](const Node_ptr& n1, const Node_ptr& n2) {
            return (this->Calculate_Cost(n1, 1) + n1->level) > (this->Calculate_Cost(n2, 1) + n2->level);
        }
    };
    std::priority_queue<Node_ptr, std::vector<Node_ptr>, decltype(comp)> Nodes_pq(comp);
    std::priority_queue<Node_ptr, std::vector<Node_ptr>, decltype(rcomp)> Nodes_rpq(rcomp);

    Node_ptr root { std::make_shared<Node>(this->initial_puzzle, 0, 5, nullptr) };
    Node_ptr goal_root { std::make_shared<Node>(this->goal_puzzle, 0, 5, nullptr) };

    Nodes_pq.push(root);
    Nodes_rpq.push(goal_root);

    while (!Nodes_pq.empty() && !Nodes_rpq.empty()) {
        Node_ptr prior_node { Nodes_pq.top() };
        Node_ptr r_prior_node { Nodes_rpq.top() };

        Nodes_pq.pop();
        Nodes_rpq.pop();

        if (Calculate_Cost(prior_node, 0) == 0) {
            std::cout << "\u001b[H\u001b[2J";
            this->Show_Solution(prior_node, 0, text_color, border_color, time_interval);
            return;
        } else if (Calculate_Cost(r_prior_node, 1) == 0) {
            std::cout << "\u001b[H\u001b[2J";
            this->Show_Solution(r_prior_node, 1, text_color, border_color, time_interval);
            return;
        } else if (*prior_node == *r_prior_node) {
            while (*(prior_node->parent_of_node) == *(r_prior_node->parent_of_node)) {
                r_prior_node = r_prior_node->parent_of_node;
                prior_node = prior_node->parent_of_node;
            }

            std::cout << "\u001b[H\u001b[2J";
            this->Show_Solution(prior_node, 0, text_color, border_color, time_interval);
            std::cout << std::endl;
            this->Show_Solution(r_prior_node->parent_of_node, 1, text_color, border_color, time_interval);
            return;
        } else if (prior_node->level >= _max_depth || r_prior_node->level >= _max_depth) {
            std::cout << "\u001b[H\u001b[2J";
            std::cout << "Search reached Max defined depth and found no answers -> Sorry" << std::endl;
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (
                this->Check_Coordinates(prior_node->zero_x + this->row[i], prior_node->zero_y + this->col[i])
                && prior_node->came_from != 3 - i) {
                std::array<std::array<int, 3>, 3> temp { prior_node->mat };
                std::swap(
                    temp[prior_node->zero_y][prior_node->zero_x],
                    temp[prior_node->zero_y + this->col[i]][prior_node->zero_x + this->row[i]]);
                Node_ptr child { std::make_shared<Node>(temp, prior_node->level + 1, i, prior_node) };
                Nodes_pq.push(child);
            }

            if (
                this->Check_Coordinates(r_prior_node->zero_x + this->row[i], r_prior_node->zero_y + this->col[i])
                && r_prior_node->came_from != 3 - i) {
                std::array<std::array<int, 3>, 3> temp { r_prior_node->mat };
                std::swap(
                    temp[r_prior_node->zero_y][r_prior_node->zero_x],
                    temp[r_prior_node->zero_y + this->col[i]][r_prior_node->zero_x + this->row[i]]);
                Node_ptr child { std::make_shared<Node>(temp, r_prior_node->level + 1, i, r_prior_node) };
                Nodes_rpq.push(child);
            }
        }
    }
}

void Puzzle::Show_Solution(
    const Node_ptr& all_nodes,
    const int& mode,
    const int& text_color,
    const int& border_color,
    const int& time_interval) const
{
    if (all_nodes == nullptr)
        return;
    if (mode == 0)
        this->Show_Solution(all_nodes->parent_of_node, 0, text_color, border_color, time_interval);
    std::cout << std::endl
              << "\u001b[" << 29 + text_color << ";1mStep. \u001b[32;1m" << step
              << " \u001b[31;1m:" << std::endl
              << std::endl;
    this->step++;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (all_nodes->mat[i][j] == 0) {
                std::cout << "  \u001b[0m\u001b[" << 29 + border_color
                          << ";1m|\u001b[s\u001b[1A-----\u001b[u\n\u001b[u\u001b[1B-----\u001b[u"
                          << "\u001b[" << 39 + text_color << ";1m"
                          << "\u001b[" << 29 + text_color << ";1m   ";
                continue;
            }
            std::cout << "  \u001b[0m\u001b[" << 29 + border_color
                      << ";1m|\u001b[s\u001b[1A-----\u001b[u\n\u001b[u\u001b[1B-----\u001b[u  "
                      << "\u001b[" << 29 + text_color << ";1m" << all_nodes->mat[i][j];
        }

        std::cout << "  \u001b[0m\u001b[" << 29 + border_color << ";1m|" << std::endl
                  << std::endl;
    }
    std::cout << "  \u001b[0m\u001b[1m---------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(time_interval));
    if (mode == 1)
        this->Show_Solution(all_nodes->parent_of_node, 1, text_color, border_color, time_interval);
}
