/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Reader
*/

#include <iostream>
#include "Utils.hpp"
#include "Reader.hpp"

bool Reader::checkBoardSizeValid(std::string& boardSizeString)
{
    if (!Utils::isNumber(boardSizeString)) {
        return false;
    }
    return boardSizeString == "19";
}

bool Reader::checkResponseStart(std::string& response)
{
    std::string boardSizeString;
    if (response.length() > 6) {
        boardSizeString = response.substr(6);
        if (checkBoardSizeValid(boardSizeString)) {
            return true;
            }
        }
    return false;
}

std::string Reader::read()
{
    std::string response;
    std::getline(std::cin, response);
    return response;
}

std::string Reader::retrieveCommandType(std::string command)
{
    for (size_t i = 0; i < command.length(); i++)
    {
        if (command[i] == ' ') {
            return command.substr(0,i);
        }
    }
    return command;
}