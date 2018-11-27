/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Brain
*/

#include <string>
#include <array>
#include <list>
#include "Pattern.hpp"
#include "Threat.hpp"

#ifndef BRAIN_HPP_
	#define BRAIN_HPP_

const int DEPTH_MAX = 5;

class Brain {
	public:
		Brain();
		~Brain() = default;

        void initMap();
        void turn(std::string turn);
        void about();
        void move();
        void restart();
        void setPositionOnMap(int x, int y, int who);
        void keepInfo(std::string command);
		void keepAndSetBoard();
        void findPosition();
        void findAllyPattern(const Position &pos, std::list<Threat> &threatList);
		void findEnemyPattern(const Position &pos, std::list<Threat> &threatList);
		bool patternRecognition(const Position &pos, const Pattern &pattern, bool ally,
		                        const Position &dir, std::list<Threat> &threatList);
		bool isThreatPresent(int posX, int posY, std::list<Threat> threat, Pattern::pattern_e name);
		void analyseThreat(std::list<Threat> &threatList, bool ally);
        int max(Threat &threat, int depth);
        int min(Threat &threat, int depth);
        int eval(int depth);


    /* GET/SET */
        bool getIsMyTurn();
        void setIsMyTurn(bool turn);
        /* ! GET/SET */

	private:
		std::list<Threat> _threatRoots;

		int _depthMax;
        int _moveX;
        int _moveY;
    	bool _isMyTurn;
		std::array<Pattern, 11> _pattern;
		std::array<Pattern::pattern_e , DEPTH_MAX> _patternMax;
        std::array<std::array<int, 19>, 19> _map;
};

#endif /* !BRAIN_HPP_ */
