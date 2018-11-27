/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Utils
*/

#include <vector>
#include <string>

#ifndef UTILS_HPP_
	#define UTILS_HPP_

namespace Utils {
    bool isNumber(std::string const&);
    std::vector<std::string> split(std::string str, std::string splitter);
}

#endif /* !UTILS_HPP_ */
