#include "puzzle.h"

/**
 * Node Constructor
 * @param  {std::array<std::array<int, 3>, 3>}  mat : Puzzle state
 * @param  {int} level                              : Depth of tree
 * @param  {int} lastDirection                      : Pervious move (avoid returnig to last state)
 * @param  {std::shared_ptr<Node>} parent           : Parent of current node
 */
Puzzle::Node::Node(
    const std::array<std::array<int, 3>, 3>& mat,
    int level,
    int lastDirection,
    const std::shared_ptr<Node>& parent)
{
    this->lastDirection = lastDirection;
    this->level = level;
    this->mat = mat;
    this->parent_of_node = parent;
    // Find coordinates of empty square
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (this->mat[i][j] == 0) {
                this->zero_y = i;
                this->zero_x = j;
            }
}

/**
 * Checks if two states are the same
 * @param  {Node} second_node : Second puzzle to compare to
 * @return {bool}             : Two states are the same or not
 */
bool Puzzle::Node::operator==(const Node& second_node) const
{
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (this->mat[i][j] != second_node.mat[i][j])
                return false;
    return true;
}

/**
 * Puzzle Constructor 
 * @param  {std::array<std::array<int, 3>, 3>}  initial_puzzle  : Init puzzle state 
 * @param  {std::array<std::array<int, 3>, 3>}  goal_puzzle     : Goal puzzle state
 */
Puzzle::Puzzle(
    const std::array<std::array<int, 3>, 3>& initial_puzzle,
    const std::array<std::array<int, 3>, 3>& goal_puzzle)
{
    this->step = 1;
    this->initial_puzzle = initial_puzzle;
    this->goal_puzzle = goal_puzzle;
}

/**
 * Calculate number of puzzle's disorder for ( A* ) algorithm
 * @param  {Node_ptr} input_node : State to calculate it's cost
 * @param  {int} mode            : Compare to init or goal puzzle ( for Bidirectional) 
 * @return {int}                 : Number of puzzle's disorder
 */
int Puzzle::Calculate_Cost(const Node_ptr& input_node, int mode) const
{
    // In DLS Calculate_Cost is not called
    if (mode == 2) // BFS -> just sort based on level not disorder
        return input_node->level;
    int cost { 0 };
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (input_node->mat[i][j] != 0) {
                // Compare to goal state
                if (mode == 0 && input_node->mat[i][j] != this->goal_puzzle[i][j])
                    cost++; // increase cost if two squares are not equal
                // Compare to init state
                else if (mode == 1 && input_node->mat[i][j] != this->initial_puzzle[i][j])
                    cost++; // increase cost if two squares are not equal
            }
    return cost + input_node->level;
}

/**
 * Change init and goal state of puzzle
 * @param  {std::array<std::array<int, 3>, 3>} initial_puzzle   : Init puzzle state 
 * @param  {std::array<std::array<int, 3>, 3>} goal_puzzle      : Goal puzzle state
 */
void Puzzle::Set_New_Matrixes(
    const std::array<std::array<int, 3>, 3>& initial_puzzle,
    const std::array<std::array<int, 3>, 3>& goal_puzzle)
{
    this->initial_puzzle = initial_puzzle;
    this->goal_puzzle = goal_puzzle;
}

/**
 * Solves the puzzle
 * @param  {std::array<int, 5>} settings : Users prefrences 
 */
void Puzzle::Solve_Puzzle(const std::array<int, 5>& settings)
{
    // Parse user settings
    int text_color { settings[0] }, border_color { settings[1] }, _max_depth { settings[2] }, time_interval { settings[3] };
    this->step = 1;
    int cl_forw { 0 }, cl_rev { 1 };
    // Clear terminal
    std::cout << "\n\u001b[s\u001b[u\u001b[H\u001b[3J\u001b[2J";
    // Warn user if puzzle is not solvable
    if (!is_Solvable(this->initial_puzzle, this->goal_puzzle)) {
        std::cout << "This Puzzle is not solvable" << std::endl;
        return;
    }
    // Warn user that program is solving puzzle
    std::cout << "Solving..." << std::endl;
    // Lambda function for comaparing two node's cost (Used in priority_queue)
    // Sorts nodes based on cost for ( A* ) algorithm and BFS
    // Cost = puzzle's disorder + level(depth) -> A* + Bidirectinal
    // Cost = level(depth) -> BFS + Bidirectinal

    if (settings[4] == 1) // User wants to run with BFS
        cl_forw = cl_rev = 2;
    else if (settings[4] == 2) // User wants to run with DLS
        cl_forw = cl_rev = 3;
    auto comp {
        [&](const Node_ptr& n1, const Node_ptr& n2) {
            return (cl_forw == 3 ? true : this->Calculate_Cost(n1, cl_forw) > this->Calculate_Cost(n2, cl_forw));
        }
    };
    // Same as above but for reverse traversing of tree (Bidirectional)
    auto rcomp {
        [&](const Node_ptr& n1, const Node_ptr& n2) {
            return (cl_rev == 3 ? true : this->Calculate_Cost(n1, cl_rev) > this->Calculate_Cost(n2, cl_rev));
        }
    };
    // priority_queue -> Container of nodes based on (lowers)cost for ( A* ) algorithm
    // Faster than std::vector + std::sort -> Tested
    std::priority_queue<Node_ptr, std::vector<Node_ptr>, decltype(comp)> Nodes_pq(comp);
    std::priority_queue<Node_ptr, std::vector<Node_ptr>, decltype(rcomp)> Nodes_rpq(rcomp);

    // Root of Tree (init state)
    Node_ptr root { std::make_shared<Node>(this->initial_puzzle, 0, 5, nullptr) };
    // Root of Tree (goal state)(Bidirectional)
    Node_ptr goal_root { std::make_shared<Node>(this->goal_puzzle, 0, 5, nullptr) };

    // Push Nodes to priority_queue
    Nodes_pq.push(root);
    Nodes_rpq.push(goal_root);
    std::vector<Node_ptr> forward {};
    std::vector<Node_ptr> backward {};
    while (!Nodes_pq.empty() && !Nodes_rpq.empty()) {
        // Extract the node with lowest cost for checking
        Node_ptr prior_node { Nodes_pq.top() };
        Node_ptr r_prior_node { Nodes_rpq.top() };
        // Remove extracted node from container
        Nodes_pq.pop();
        Nodes_rpq.pop();
        // Bidirectional algorithm
        // First possible result -> init state reaches goal first
        if (*prior_node == *goal_root) {
            std::cout << "\u001b[H\u001b[3J\u001b[2J";
            // Show result
            this->Show_Solution(prior_node, 0, text_color, border_color, time_interval);
            return;
        }
        // Second possible result -> goal state reaches init first
        else if (*r_prior_node == *root) {
            std::cout << "\u001b[H\u001b[3J\u001b[2J";
            // Show result
            this->Show_Solution(r_prior_node, 1, text_color, border_color, time_interval);
            return;
        }
        // This is where Bidirectional search comes to benefit really
        /**
         * Third possible result -> inint state and goal state intersect
         * in the middle of their searches
         */
        else {
            // Find intersection
            auto r1 = std::find_if(std::execution::par, forward.begin(), forward.end(),
                [&](Node_ptr temp) { return *temp == *r_prior_node; });
            if (r1 != forward.end()) {
                prior_node = *r1;
                /**
                 *Important -> remove redundant moves
                 *when two searches intersect from the point of intersection
                 *to a specific piont second search just rolls back first searche's moves
                */
                while (*(prior_node->parent_of_node) == *(r_prior_node->parent_of_node)) {
                    r_prior_node = r_prior_node->parent_of_node;
                    prior_node = prior_node->parent_of_node;
                }
                std::cout << "\u001b[H\u001b[3J\u001b[2J";
                // Show result -> inti to middle
                this->Show_Solution(prior_node, 0, text_color, border_color, time_interval);
                std::cout << std::endl;
                // Show result -> middle to goal
                this->Show_Solution(r_prior_node->parent_of_node, 1, text_color, border_color, time_interval);
                return;
            } else {
                auto r2 = std::find_if(std::execution::par, backward.begin(), backward.end(),
                    [&](Node_ptr temp) { return *temp == *prior_node; });
                if (r2 != backward.end()) {
                    r_prior_node = *r2;
                    /**
                    *Important -> remove redundant moves
                    *when two searches intersect from the point of intersection
                    *to a specific piont second search just rolls back first searche's moves
                    */
                    while (*(prior_node->parent_of_node) == *(r_prior_node->parent_of_node)) {
                        r_prior_node = r_prior_node->parent_of_node;
                        prior_node = prior_node->parent_of_node;
                    }
                    std::cout << "\u001b[H\u001b[3J\u001b[2J";
                    // Show result -> inti to middle
                    this->Show_Solution(prior_node, 0, text_color, border_color, time_interval);
                    std::cout << std::endl;
                    // Show result -> middle to goal
                    this->Show_Solution(r_prior_node->parent_of_node, 1, text_color, border_color, time_interval);
                    return;
                }
            }
        }
        // Generate every valid neighbor of empty square
        for (int i = 0; i < 4; i++) {
            // Ckeck if next move is valid -> Forward search
            if (
                this->Check_Coordinates(prior_node->zero_x + this->row[i], prior_node->zero_y + this->col[i])
                && prior_node->lastDirection != 3 - i
                && prior_node->level < _max_depth) {
                std::array<std::array<int, 3>, 3> temp { prior_node->mat };
                // Swap empty square with it's neighbor
                std::swap(
                    temp[prior_node->zero_y][prior_node->zero_x],
                    temp[prior_node->zero_y + this->col[i]][prior_node->zero_x + this->row[i]]);
                // Generate new state of puzzle
                Node_ptr child { std::make_shared<Node>(temp, prior_node->level + 1, i, prior_node) };
                // Push new state of puzzle to priority_queue
                Nodes_pq.push(child);
                forward.push_back(child);
            }
            // Ckeck if next move is valid -> Reverse search
            if (
                this->Check_Coordinates(r_prior_node->zero_x + this->row[i], r_prior_node->zero_y + this->col[i])
                && r_prior_node->lastDirection != 3 - i
                && r_prior_node->level < _max_depth) {
                std::array<std::array<int, 3>, 3> temp { r_prior_node->mat };
                // Swap empty square with it's neighbor
                std::swap(
                    temp[r_prior_node->zero_y][r_prior_node->zero_x],
                    temp[r_prior_node->zero_y + this->col[i]][r_prior_node->zero_x + this->row[i]]);
                // Generate new state of puzzle
                Node_ptr child { std::make_shared<Node>(temp, r_prior_node->level + 1, i, r_prior_node) };
                // Push new state of puzzle to priority_queue
                Nodes_rpq.push(child);
                backward.push_back(child);
            }
        }
    }
    std::cout << "\u001b[H\u001b[3J\u001b[2J";
    std::cout << "Search reached Max defined depth and found no answers -> Sorry" << std::endl;
}

/**
 * Show Solution in a beautiful maner
 * @param  {Node_ptr} all_nodes : The sate of puzzle to start  from  
 * @param  {int} mode           : start from init or goal puzzle ( for Bidirectional) 
 * @param  {int} text_color     : Color of text
 * @param  {int} border_color   : Color of puzzle border
 * @param  {int} time_interval  : Delay time between showing each state of answer
 */
void Puzzle::Show_Solution(
    const Node_ptr& all_nodes,
    const int& mode,
    const int& text_color,
    const int& border_color,
    const int& time_interval) const
{
    // Return in case reaching end
    if (all_nodes == nullptr)
        return;
    // Go deep down till we reach init node
    if (mode == 0)
        this->Show_Solution(all_nodes->parent_of_node, 0, text_color, border_color, time_interval);
    // Show puzzle in a beautiful maner
    std::cout << std::endl
              << "\u001b[" << 29 + text_color << ";1mStep. \u001b[32;1m" << step
              << " \u001b[31;1m:" << std::endl
              << std::endl;
    // Increase step of answer
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
    // Return in case reaching end
    if (all_nodes->parent_of_node == nullptr)
        return;
    // Delay between showing each step
    std::this_thread::sleep_for(std::chrono::milliseconds(time_interval));
    // Go deep down till we reach goal node
    if (mode == 1)
        this->Show_Solution(all_nodes->parent_of_node, 1, text_color, border_color, time_interval);
}
