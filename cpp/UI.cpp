#include "UI.h"

bool is_Solvable(const std::array<std::array<int, 3>, 3>& initial_puzzle, const std::array<std::array<int, 3>, 3>& goal_puzzle)
{
    int inv_count { 0 };
    int inv_count_goal { 0 };
    std::vector<int> init, goal;

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++) {
            if (initial_puzzle[i][j] != 0)
                init.push_back(initial_puzzle[i][j]);
            if (goal_puzzle[i][j] != 0)
                goal.push_back(goal_puzzle[i][j]);
        }

    for (int i = 0; i < 7; i++)
        for (int j = i + 1; j < 8; j++)
            if (init[i] > init[j])
                inv_count++;
    for (int i = 0; i < 7; i++)
        for (int j = i + 1; j < 8; j++)
            if (goal[i] > goal[j])
                inv_count_goal++;

    return inv_count % 2 == inv_count_goal % 2;
}

void UI_Settings(std::array<std::array<int, 3>, 3>& initial, std::array<std::array<int, 3>, 3>& goal, std::array<int, 4>& settings)
{
    char special_puzzle;
    std::string name {};

    std::cout
        << std::endl
        << "Hi, Welcome to the 8-Puzzle Solver" << std::endl;
    std::cout << "What's Your Name: ";
    std::cin >> name;
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

    std::cout << "My Prefered Color for puzzle border is: \u001b[s";
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[1];
    } while (settings[1] < 1 || settings[1] > 8);

    std::cout << "My Prefered Color for text is: \u001b[s";
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[0];
    } while (settings[0] < 1 || settings[0] > 8);

    std::cout << "\u001b[" << 29 + settings[0] << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "Do you have  a special Goal Puzzle in mind? -> \u001b[32;1mY(yes)"
              << "\u001b[" << 29 + settings[0] << ";1m"
              << " / \u001b[31;1mN(No): "
              << "\u001b[" << 29 + settings[0] << ";1m";
    std::cin >> special_puzzle;
    if (special_puzzle == 'Y' || special_puzzle == 'y') {
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "Nice, Enter your puzzle bellow: (Left to Right -> Top to Bottom)" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1] << ";1m|\u001b[s\u001b[1B-----\u001b[u\u001b[1A-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m";
                std::cout << "\u001b[s";
                do {
                    std::cout << "\u001b[u\u001b[0K";
                    std::cin >> goal[i][j];
                } while (goal[i][j] < 0 || goal[i][j] > 8);

                std::cout << "\u001b[u\u001b[1C";
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }

    } else {
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "OK, Goal Node will be default" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1] << ";1m|\u001b[s\u001b[1A-----\u001b[u\n\u001b[u\u001b[1B-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m" << goal[i][j];
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }
        std::cout << "\n\u001b[" << 29 + settings[0] << ";1m"
                  << "Press Enter to continue..." << std::endl;
        std::getline(std::cin, name);
        std::getline(std::cin, name);
    }

    std::cout << "\u001b[" << 29 + settings[0] << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "Do you have  a special Initial Puzzle in mind? -> \u001b[32;1mY(yes)"
              << "\u001b[" << 29 + settings[0] << ";1m"
              << " / \u001b[31;1mN(No): "
              << "\u001b[" << 29 + settings[0] << ";1m";
    std::cin >> special_puzzle;
    if (special_puzzle == 'Y' || special_puzzle == 'y') {
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "Nice, Enter your puzzle bellow: (Left to Right -> Top to Bottom)" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1] << ";1m|\u001b[s\u001b[1B-----\u001b[u\u001b[1A-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m";
                std::cout << "\u001b[s";
                do {
                    std::cout << "\u001b[u\u001b[0K";
                    std::cin >> initial[i][j];
                } while (initial[i][j] < 0 || initial[i][j] > 8);

                std::cout << "\u001b[u\u001b[1C";
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }

    } else {
        std::cout << "\u001b[" << 29 + settings[0] << ";1m"
                  << "OK, I Will generate a random puzzle:" << std::endl
                  << std::endl;
        std::default_random_engine generator(std::random_device {}());
        std::uniform_int_distribution<int> dist { 0, 8 };
        std::array<int, 9> random_array { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
        do {
            std::random_shuffle(random_array.begin(), random_array.end(), [&dist, &generator](int i) { return dist(generator); });
            for (size_t i = 0; i < 3; i++)
                for (size_t j = 0; j < 3; j++)
                    initial[i][j] = random_array[i * 3 + j];
        } while (!is_Solvable(initial, goal));

        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + settings[1] << ";1m|\u001b[s\u001b[1A-----\u001b[u\n\u001b[u\u001b[1B-----\u001b[u  "
                          << "\u001b[" << 29 + settings[0] << ";1m" << initial[i][j];
            }
            std::cout << "  \u001b[" << 29 + settings[1] << ";1m|" << std::endl
                      << std::endl;
        }

        std::cout << "\n\u001b[" << 29 + settings[0] << ";1m"
                  << "Press Enter to continue..." << std::endl;
        std::getline(std::cin, name);
        std::getline(std::cin, name);
    }

    std::cout << "\u001b[" << 29 + settings[0] << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "Almost there ----> Please enter Max search depth: \u001b[s";
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[2];
    } while (settings[2] < 0);

    std::cout << "\u001b[H\u001b[2J";
    std::cout << "One last thing ----> Please enter time intervals for showing each step in ms : \u001b[s";
    do {
        std::cout << "\u001b[u\u001b[0K";
        std::cin >> settings[3];
    } while (settings[3] < 0);
}