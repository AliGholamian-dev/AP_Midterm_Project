#include "puzzle.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    int text_color = 1, puzzle_color = 1, max_depth = 1000, time_interval = 100;
    char special_puzzle;
    std::string name {};
    std::array<std::array<int, 3>, 3> initial = {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 7, 8, 0 }
    };
    std::array<std::array<int, 3>, 3> final = {
        std::array<int, 3> { 1, 2, 3 },
        std::array<int, 3> { 4, 5, 6 },
        std::array<int, 3> { 7, 8, 0 }
    };

    std::cout << std::endl
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

    std::cout << "My Prefered Color for puzzle border is: ";
    std::cin >> puzzle_color;
    std::cout << "My Prefered Color for text is: ";
    std::cin >> text_color;
    std::cout << "\u001b[" << 29 + text_color << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "OK, Do you have  a special puzzle in mind? -> \u001b[32;1mY(yes) / \u001b[31;1mN(No): ";
    std::cin >> special_puzzle;
    if (special_puzzle == 'Y' || special_puzzle == 'y') {
        std::cout << "\u001b[" << 29 + text_color << ";1m"
                  << "Nice, Enter your puzzle bellow: (Left to Right -> Top to Bottom)" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + puzzle_color << ";1m|  "
                          << "\u001b[" << 29 + text_color << ";1m";
                std::cout << "\u001b[s";
                std::cin >> initial[i][j];
                std::cout << "\u001b[u\u001b[1C";
            }
            std::cout << "  \u001b[" << 29 + puzzle_color << ";1m|" << std::endl;
        }

    } else {
        std::cout << "\u001b[" << 29 + text_color << ";1m"
                  << "OK, I Will generate a random puzzle:" << std::endl;
        //generate an show random puzzle (initial)
    }

    std::cout << "\u001b[" << 29 + text_color << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "Do you have  a special Goal Puzzle in mind? -> \u001b[32;1mY(yes) / \u001b[31;1mN(No): ";
    std::cin >> special_puzzle;
    if (special_puzzle == 'Y' || special_puzzle == 'y') {
        std::cout << "\u001b[" << 29 + text_color << ";1m"
                  << "Nice, Enter your puzzle bellow: (Left to Right -> Top to Bottom)" << std::endl
                  << std::endl;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                std::cout << "  \u001b[" << 29 + puzzle_color << ";1m|  "
                          << "\u001b[" << 29 + text_color << ";1m";
                std::cout << "\u001b[s";
                std::cin >> final[i][j];
                std::cout << "\u001b[u\u001b[1C";
            }
            std::cout << "  \u001b[" << 29 + puzzle_color << ";1m|" << std::endl;
        }

    } else {
        std::cout << "\u001b[" << 29 + text_color << ";1m"
                  << "OK, I Will generate a random puzzle:" << std::endl;
        //generate an show random puzzle (final)
    }

    std::cout << "\u001b[" << 29 + text_color << ";1m" << std::endl;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "Almost there ----> Please enter Max search depth: ";
    std::cin >> max_depth;
    std::cout << "\u001b[H\u001b[2J";
    std::cout << "One last thing ----> Please enter time intervals for showing each step in ms : ";
    std::cin >> time_interval;
    std::cout << "\n\u001b[s\u001b[u";
    Puzzle New_Puzzle { initial, final };
    // New_Puzzle .Set_New_Matrixes(in2, fi2);
    New_Puzzle.Solve_Puzzle(max_depth, text_color, puzzle_color, time_interval);
    std::cout << "\u001b[0m";
    return 0;
}