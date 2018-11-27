/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Threat
*/

#include <vector>
#include <string>

#ifndef THREAT_HPP_
#define THREAT_HPP_

struct Position {
	Position(int new_x, int new_y) : x(new_x), y(new_y) {}
	int x;
	int y;
};

struct Threat {
	Threat(Position pos, Pattern::pattern_e pattern) : _pos(pos) {
	    _pattern = pattern;
	}
	~Threat() = default;

	Position _pos;
    std::list<Threat> _children;
	Pattern::pattern_e _pattern;
};

#endif	/* !THREAT_HPP_ */