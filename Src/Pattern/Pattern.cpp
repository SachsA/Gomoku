/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Pattern
*/

#include <iostream>
#include "Pattern.hpp"

void Pattern::setVariables(const std::string &allyPattern, const std::string &enemyPattern, pattern_e name,
                           const std::vector<int> pos)
{
    _allyPattern = allyPattern;
    _enemyPattern = enemyPattern;
    _name = name;
    _pos = pos;
}