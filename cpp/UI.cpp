#include "UI.h"

/**
 * Checks if user wants to Re-run program 
 * @param  {int} text_color : Color of text for UI
 * @return {bool}           : Whether re-run program or not
 */
bool ReRun(int text_color)
{
    char ReRun_State = 'Y';
    // Ask the user whether to re-run program or not
    std::cout << "\n\u001b[" << 29 + text_color << ";1m" << std::endl;
    std::cout << "Do you want to ReRun the Program? -> \u001b[32;1mY(yes)"
              << "\u001b[" << 29 + text_color << ";1m"
              << " / \u001b[31;1mN(No): "
              << "\u001b[" << 29 + text_color << ";1m\u001b[s";
    // keep recieving input till it's valid (y or Y or n or N)
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> ReRun_State;
    } while (ReRun_State != 'y' && ReRun_State != 'Y' && ReRun_State != 'n' && ReRun_State != 'N');
    // Clear Terminal
    std::cout << "\u001b[H\u001b[3J\u001b[2J\u001b[0m";
    return (ReRun_State == 'y' || ReRun_State == 'Y');
}

/**
 * Checks if a puzzle is solvable
 * @param  {std::array<std::array<int, 3>, 3>} initial   : Initial state of Puzzle
 * @param  {std::array<std::array<int, 3>, 3>} goal      : Goal state of Puzzle
 * @return {bool}                                        : Puzzle is solvable or not
 */
bool is_Solvable(
    const std::array<std::array<int, 3>, 3>& initial_puzzle,
    const std::array<std::array<int, 3>, 3>& goal_puzzle)
{
    // Parity counter
    int inv_count { 0 };
    int inv_count_goal { 0 };
    std::vector<int> init, goal;

    // Calculate the number of inversions in initial puzzle
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++) {
            if (initial_puzzle[i][j] != 0)
                init.push_back(initial_puzzle[i][j]);
            if (goal_puzzle[i][j] != 0)
                goal.push_back(goal_puzzle[i][j]);
        }

    // Calculate the number of inversions in goal puzzle
    for (int i = 0; i < 7; i++)
        for (int j = i + 1; j < 8; j++)
            if (init[i] > init[j])
                inv_count++;
    for (int i = 0; i < 7; i++)
        for (int j = i + 1; j < 8; j++)
            if (goal[i] > goal[j])
                inv_count_goal++;
    // If both inversions are from same parity it's solvable
    // If Both parities are odd or evevn it's solvable
    return inv_count % 2 == inv_count_goal % 2;
}

/**
 * Sets init and goal puzzle and UI Colors based on users preferences
 * @param  {std::array<std::array<int, 3>, 3>&} initial  : Initial state of Puzzle
 * @param  {std::array<std::array<int, 3>, 3>&} goal     : Goal state of Puzzle
 * @param  {std::array<int, 4>&}                settings : User settings
 */
void UI_Settings(
    std::array<std::array<int, 3>, 3>& initial,
    std::array<std::array<int, 3>, 3>& goal,
    std::array<int, 4>& settings)
{
    char special_puzzle;
    std::string name {};
    // Saying Hi to user and ask for him/her name
    std::cout
        << std::endl
        << "\u001b[H\u001b[3J\u001b[2J\u001b[0mHi, Welcome to the 8-Puzzle Solver" << std::endl;
    std::cout << "What's Your Name: ";
    // Get name of user
    std::cin >> name;
    // Ask for user color preferences
    std::cout << std::endl
              << "Nice to meet you " << name << ", Please choose your prefered color :" << std::endl;
    std::cout << "\u001b[30;1m 1 - Black" << std::endl
              << "\u001b[31;1m 2 - Red" << std::endl
              << "\u001b[32;1m 3 - Green" << std::endl
              << "\u001b[33;1m 4 - Yellow" << std::endl
              << "\u001b[34;1m 5 - Blue" << std::endl
              << "\u001b[35;1m 6 - Magenta" << std::endl
              << "\u001b[36;1m 7 - Cyan" << std::endl
              << "\u001b[37;1m 8 - White \u001b[0m" << std::endl;

    // Color for puzzle border
    std::cout << "My Prefered Color for puzzle border is: \u001b[s";
    // keep recieving input till it's valid (a nubmer from 1 to 8)
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[1];
    } while (settings[1] < 1 || settings[1] > 8);

    // Color for text
    std::cout << "My Prefered Color for text is: \u001b[s";
    // keep recieving input till it's valid (a nubmer from 1 to 8)
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[0];
    } while (settings[0] < 1 || settings[0] > 8);

    // Asking if user wants a special *** Goal *** puzzle
    std::cout << "\u001b[" << 29 + settings[0] << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[3J\u001b[2J";
    std::cout << "Do you have  a special *** Goal *** Puzzle in mind? -> \u001b[32;1mY(yes)"
              << "\u001b[" << 29 + settings[0] << ";1m"
              << " / \u001b[31;1mN(No): "
              << "\u001b[" << 29 + settings[0] << ";1m\u001b[s";
    // keep recieving input till it's valid (y or Y or n or N)
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> special_puzzle;
    } while (special_puzzle != 'y' && special_puzzle != 'Y' && special_puzzle != 'n' && special_puzzle != 'N');

    // In case user wants a special state take in puzzle from user
    if (special_puzzle == 'Y' || special_puzzle == 'y') {
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "Nice, Enter your puzzle bellow: (Left to Right -> Top to Bottom)" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1]
                          << ";1m|\u001b[s\u001b[1B-----\u001b[u\u001b[1A-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m";
                std::cout << "\u001b[s";
                // keep recieving input till it's valid (a nubmer from 0 to 8)
                do {
                    std::cout << "\u001b[u\u001b[0K";
                    std::cin >> goal[i][j];
                } while (goal[i][j] < 0 || goal[i][j] > 8);

                std::cout << "\u001b[u\u001b[1C";
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }

    } else { // In case user does not want a special state set it to default
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "OK, Goal Node will be default" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1]
                          << ";1m|\u001b[s\u001b[1A-----\u001b[u\n\u001b[u\u001b[1B-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m" << goal[i][j];
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }
        std::cout << "\n\u001b[" << 29 + settings[0] << ";1m"
                  << "Press Enter to continue..." << std::endl;
        // Wainting for user to press Enter
        std::getline(std::cin, name);
        std::getline(std::cin, name);
    }

    // Asking if user wants a special *** Initial *** puzzle
    std::cout << "\u001b[" << 29 + settings[0] << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[3J\u001b[2J";
    std::cout << "Do you have  a special *** Initial *** Puzzle in mind? -> \u001b[32;1mY(yes)"
              << "\u001b[" << 29 + settings[0] << ";1m"
              << " / \u001b[31;1mN(No): "
              << "\u001b[" << 29 + settings[0] << ";1m\u001b[s";
    // keep recieving input till it's valid (y or Y or n or N)
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> special_puzzle;
    } while (special_puzzle != 'y' && special_puzzle != 'Y' && special_puzzle != 'n' && special_puzzle != 'N');

    // In case user wants a special state take in puzzle from user
    if (special_puzzle == 'Y' || special_puzzle == 'y') {
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "Nice, Enter your puzzle bellow: (Left to Right -> Top to Bottom)" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1]
                          << ";1m|\u001b[s\u001b[1B-----\u001b[u\u001b[1A-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m";
                std::cout << "\u001b[s";
                // keep recieving input till it's valid (a nubmer from 0 to 8)
                do {
                    std::cout << "\u001b[u\u001b[0K";
                    std::cin >> initial[i][j];
                } while (initial[i][j] < 0 || initial[i][j] > 8);

                std::cout << "\u001b[u\u001b[1C";
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }

    } else { // In case user does not want a special state generate a random one
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "OK, I Will generate a random puzzle:" << std::endl
                  << std::endl;
        std::default_random_engine generator(std::random_device {}());
        std::uniform_int_distribution<int> dist { 0, 8 };
        std::array<int, 9> random_array { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
        auto lambda { [&dist, &generator](int i) { return dist(generator); } };

        /*** Pay Attentin Here *****/
        // Keep generating a random initial puzzle till it's solvable based on goal state
        do {
            // Randomly shuffle puzzle numbers
            std::random_shuffle(random_array.begin(), random_array.end(), lambda);
            for (size_t i = 0; i < 3; i++)
                for (size_t j = 0; j < 3; j++)
                    initial[i][j] = random_array[i * 3 + j];
        } while (!is_Solvable(initial, goal));

        // Print generated puzzle
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1]
                          << ";1m|\u001b[s\u001b[1A-----\u001b[u\n\u001b[u\u001b[1B-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m" << initial[i][j];
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }

        std::cout << "\n\u001b[" << 29 + settings[0] << ";1m"
                  << "Press Enter to continue..." << std::endl;
        // Wainting for user to press Enter
        std::getline(std::cin, name);
        std::getline(std::cin, name);
    }

    // Asking for Max search depth
    std::cout << "\u001b[" << 29 + settings[0] << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[3J\u001b[2J";
    std::cout << "Almost there ----> Please enter Max search depth: \u001b[s";
    // keep recieving input till it's valid
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[2];
    } while (settings[2] < 0);

    // Asking for Delay time between showing each state of answer
    std::cout << "\u001b[H\u001b[3J\u001b[2J";
    std::cout << "One last thing ----> Please enter time intervals for showing each step in ms : \u001b[s";
    // keep recieving input till it's valid
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[3];
    } while (settings[3] < 0);
}
