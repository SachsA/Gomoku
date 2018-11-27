/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Pattern
*/

#include <vector>
#include <string>

#ifndef PATTERN_HPP_
#define PATTERN_HPP_

class Pattern {
public:
	enum pattern_e {
		FIVE = 7,
		FOUR = 6,
		FOUR_B = 5,
        THREE_B = 4,
		THREE = 3,
        THREE_S = 2,
        DUO = 1,
		ONE = 0,
		UNDEFINED = -1
	};

public:
	Pattern() = default;
	~Pattern() = default;

	void setVariables(const std::string &, const std::string &, pattern_e, const std::vector<int>);

    pattern_e _name;
    std::string _allyPattern;
    std::string _enemyPattern;
	std::vector<int> _pos;
};

#endif /* !PATTERN_HPP_ */