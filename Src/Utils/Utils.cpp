/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Utils
*/

#include <regex>
#include "Utils.hpp"

namespace Utils {

    bool isNumber(std::string const &s)
    {
        return !s.empty() && find_if(s.begin(),
                                          s.end(), [](char c) { return !isdigit(c); }) == s.end();
    }

    std::vector<std::string> split(std::string str, std::string splitter)
    {
        std::regex ws_re(splitter);

        std::vector<std::string> result{
                std::sregex_token_iterator(str.begin(), str.end(), ws_re, -1), {}
        };
        return result;
    }
}