/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Brain
*/

#include <stdio.h>
#include <iostream>
#include <cstring>
#include "Utils.hpp"
#include "Brain.hpp"
#include "Pattern.hpp"

Brain::Brain()
        : _moveX(0), _moveY(0), _isMyTurn(false)
{
    initMap();
    std::vector<int> pos;
    _pattern[0].setVariables("11111", "22222", Pattern::FIVE, pos);
    pos.emplace_back(0);
    _pattern[1].setVariables("01111", "02222", Pattern::FOUR, pos);
    _pattern[5].setVariables("01110", "02220", Pattern::THREE, pos);
    _pattern[9].setVariables("0110", "0220", Pattern::DUO, pos);
    _pattern[10].setVariables("01", "02", Pattern::ONE, pos);
    pos.clear();
    pos.emplace_back(2);
    _pattern[8].setVariables("01010", "02020", Pattern::DUO, pos);
    pos.clear();
    pos.emplace_back(2);
    _pattern[3].setVariables("11011", "22022", Pattern::FOUR_B, pos);
    _pattern[7].setVariables("11010", "22020", Pattern::THREE_S, pos);
    pos.clear();
    pos.emplace_back(3);
    _pattern[6].setVariables("01101", "02202", Pattern::THREE_S, pos);
    _pattern[4].setVariables("011010", "022020", Pattern::THREE_B, pos);
    pos.clear();
    pos.emplace_back(1);
    _pattern[2].setVariables("10111", "20222", Pattern::FOUR_B, pos);

    _patternMax.fill(Pattern::UNDEFINED);
}

void Brain::initMap()
{
    for (auto &y : _map) {
        for (auto &x: y) {
            x = 0;
        }
    }
}

void Brain::findPosition()
{
    int score;
    int scoreMax = -10000;
    Position pos(0, 0);

    _depthMax = DEPTH_MAX;
    analyseThreat(_threatRoots, false);
    analyseThreat(_threatRoots, true);

    if (_threatRoots.empty()) {
        _moveX = 5;
        _moveY = 5;
        return;
    }

    pos = _threatRoots.front()._pos;
    for (auto &node : _threatRoots) {
        _map[node._pos.y][node._pos.x] = 1;
        score = min(node, 0);
        if (score < scoreMax) {
            scoreMax = score;
            pos = node._pos;
        }
        _map[node._pos.y][node._pos.x] = 0;
    }
    _moveX = pos.x;
    _moveY = pos.y;
}

void Brain::analyseThreat(std::list<Threat> &threatList, bool ally)
{
    Position pos(0, 0);

    while (pos.y < 19) {
        pos.x = 0;
        while (pos.x < 19) {
            if (ally)
                findAllyPattern(pos, threatList);
            else
                findEnemyPattern(pos, threatList);
            pos.x++;
        }
        pos.y++;
    }
    if (!threatList.empty() && threatList.front()._pattern > 0) {
        auto it = threatList.begin();
        auto end = threatList.end();
        while (it != end) {
            if (it->_pattern <= 0) {
                it = threatList.erase(it);
            } else
                it++;
        }
    }
}

int Brain::eval(int depth)
{
    int nbPions = depth;
    std::list<Threat> ally;
    analyseThreat(ally, true);

    std::list<Threat> enemy;
    analyseThreat(enemy, false);

    if (!ally.empty() && ally.front()._pattern > 4) {
        _depthMax = depth;
        return 1000 - nbPions;
    } else if (!enemy.empty() && enemy.front()._pattern > 4) {
        _depthMax = depth;
        return -1000 + nbPions;
    }

    nbPions = 0;
    if (!ally.empty() && !enemy.empty())
        nbPions = ally.front()._pattern - enemy.front()._pattern;

    if (nbPions != 0)
        return nbPions * 10;

    return (int)ally.size() - (int)enemy.size();
}

int Brain::min(Threat &threat, int depth)
{
    int minScore = 10000;
    int score;

    if (depth >= DEPTH_MAX || depth >= _depthMax || threat._pattern > 3 || threat._pattern < 1)
        return eval(depth);

    analyseThreat(threat._children, false);
    analyseThreat(threat._children, true);
    if (threat._children.empty() || threat._children.front()._pattern < threat._pattern)
        return eval(depth);
    for (auto &node : threat._children) {
        _map[node._pos.y][node._pos.x] = 2;

        score = max(node, depth + 1);

        if (score < minScore)
            minScore = score;

        _map[node._pos.y][node._pos.x] = 0;
    }

    return minScore;
}

int Brain::max(Threat &threat, int depth)
{
    int maxScore = -10000;
    int score;

    if (depth >= DEPTH_MAX || depth >= _depthMax || threat._pattern > 3 || threat._pattern < 1)
        return eval(depth);

    analyseThreat(threat._children, true);
    analyseThreat(threat._children, false);
    if (threat._children.empty() || threat._children.front()._pattern < threat._pattern)
        return eval(depth);
    for (auto &node : threat._children) {
        _map[node._pos.y][node._pos.x] = 2;

        score = min(node, depth + 1);

        if (score > maxScore)
            maxScore = score;

        _map[node._pos.y][node._pos.x] = 0;
    }

    return maxScore;
}

bool Brain::patternRecognition(const Position &pos, const Pattern &pattern, bool ally, const Position &dir,
                               std::list<Threat> &threatList)
{
    int x = 0;

    while (pos.x + (x * dir.x) >= 0 && pos.x + (x * dir.x) < 19 &&
           pos.y + (x * dir.y) >= 0 && pos.y + (x * dir.y) < 19 &&
           ((ally && x < (int) pattern._allyPattern.size() &&
             _map[pos.y + x * dir.y][pos.x + x * dir.x] == pattern._allyPattern[x] - 48) ||
            (!ally && x < (int) pattern._enemyPattern.size() &&
             _map[pos.y + x * dir.y][pos.x + x * dir.x] == pattern._enemyPattern[x] - 48))) {
        x++;
    }
    if ((ally && x == (int) pattern._allyPattern.size()) ||
        (!ally && x == (int) pattern._enemyPattern.size())) {
        x = 0;
        while (x < (int) pattern._pos.size()) {
            if (!isThreatPresent(pos.x + pattern._pos[x] * dir.x, pos.y + pattern._pos[x] * dir.y, threatList, pattern
                    ._name)) {
                if (!threatList.empty()) {
                    auto it = threatList.begin();
                    auto end = threatList.end();
                    while (it != end && it->_pattern > pattern._name)
                        it++;
                    threatList.insert(it, Threat(Position(pos.x + pattern._pos[x] * dir.x,
                                                          pos.y + pattern._pos[x] * dir.y),
                                                 pattern._name));
                } else
                    threatList.emplace_back(
                            Position(pos.x + pattern._pos[x] * dir.x, pos.y + pattern._pos[x] * dir.y),
                            pattern._name);
            }
            x++;
        }
        return true;
    }
    return false;
}

bool Brain::isThreatPresent(int posX, int posY, std::list<Threat> threat, Pattern::pattern_e name)
{
    if (threat.empty())
        return false;
    auto it = threat.begin();
    auto end = threat.end();
    while (it != end) {
        if (it->_pos.x == posX && it->_pos.y == posY) {
            if (it->_pattern < name) {
                threat.erase(it);
                return false;
            }
            return true;
        }
        it++;
    }
    return false;
}

void Brain::findAllyPattern(const Position &pos, std::list<Threat> &threatList)
{
    int i = 0;

    while (i < (int) _pattern.size() - 1) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                patternRecognition(pos, _pattern[i], true, Position(x, y), threatList);
            }
        }
        i++;
    }
    if (threatList.empty() || threatList.front()._pattern < 1) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                patternRecognition(pos, _pattern[i], true, Position(x, y), threatList);
            }
        }
    }
}

void Brain::findEnemyPattern(const Position &pos, std::list<Threat> &threatList)
{
    int i = 0;

    while (i < (int) _pattern.size() - 1) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                patternRecognition(pos, _pattern[i], false, Position(x, y), threatList);
            }
        }
        i++;
    }
    if (threatList.empty() || threatList.front()._pattern < 1) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                patternRecognition(pos, _pattern[i], false, Position(x, y), threatList);
            }
        }
    }
}

void Brain::move()
{
    findPosition();
    std::cout << _moveX << "," << _moveY << std::endl;
    _map[_moveY][_moveX] = 1;
    _threatRoots.clear();
}

void Brain::turn(std::string turn)
{
    if (turn.size() < 5) {
        _isMyTurn = false;
        return;
    }

    std::string moveOpponent = turn.substr(5);
    auto vec = Utils::split(moveOpponent, "\\,+");
    if (vec.size() != 2 || !Utils::isNumber(vec[0].c_str()) || !Utils::isNumber(vec[1].c_str())) {
        _isMyTurn = false;
        return;
    } else if ((atoi(vec[0].c_str()) > 19 || atoi(vec[1].c_str()) < 0) ||
               (atoi(vec[1].c_str()) > 19 || atoi(vec[1].c_str()) < 0)) {
        _isMyTurn = false;
        return;
    }
    setPositionOnMap(atoi(vec[0].c_str()), atoi(vec[1].c_str()), 2);
}

void Brain::about()
{
    std::cout << R"(name="pbrain-Bordeaux-Cotoni.Martin", version="1.0", )"
              << R"(authors="Kellian Cipierre, Martin Cotoni, Alexandre Sachs", country="France")" << std::endl;
}

void Brain::setPositionOnMap(int x, int y, int who)
{
    _map[y][x] = who;
}

void Brain::keepInfo(std::string command)
{
    auto vec = Utils::split(std::move(command), "\\s+");
}

void Brain::keepAndSetBoard()
{
    std::string resp;

    while (getline(std::cin, resp)) {
        if (resp == "DONE")
            break;
        else {
            auto vec = Utils::split(resp, "\\,+");
            setPositionOnMap(resp[0], resp[1], resp[2]);
        }
    }
}

void Brain::restart()
{
    initMap();
    std::cout << "OK" << std::endl;
}

/* GET/SET */

bool Brain::getIsMyTurn()
{
    return _isMyTurn;
}

void Brain::setIsMyTurn(bool turn)
{
    _isMyTurn = turn;
}

/* ! GET/SET */