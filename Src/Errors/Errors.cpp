/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Errors
*/

#include "Errors.hpp"

Errors::Errors(std::ostream &os, const std::string &message) noexcept
        : _os(os)
{
        _message = message;
}

const char *Errors::what() const noexcept
{
        return _message.c_str();
}