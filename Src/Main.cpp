/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Main
*/

#include <iostream>
#include "Core.hpp"

int main()
{
    try {
        Core core;
        core.play();
    } catch(const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown Error(s)." << std::endl;
    }
    return 0;
}
