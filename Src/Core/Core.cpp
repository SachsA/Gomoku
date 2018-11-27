/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"
#include "Utils.hpp"

Core::Core()
    :   _brain(Brain()), _reader(Reader()), _boardSize(19), _playing(false), _gameLaunched(false)
{
    _commands["BEGIN"] = &Core::beginGame;
    _commands["END"] = &Core::endGame;
    _commands["ABOUT"] = &Core::about;
    _commands["RESTART"] = &Core::restart;
}

Core::status_info Core::statusFinder(std::string commandType)
{
	if (commandType == "TURN") {
		return Core::TURN;
	}
	if (commandType == "START") {
		return Core::START;
	}
	if (commandType == "INFO") {
		return Core::INFO;
	}
	if (commandType == "BOARD") {
		return Core::BOARD;
	}
	return Core::UNDEFINED;
}

void Core::dispatchCommand(std::string commandType, std::string command)
{
	switch (statusFinder(commandType)) {
	case Core::TURN :
		_brain.setIsMyTurn(true);
		_brain.turn(command);
		break;
	case Core::START :
		startGame(command);
		break;
	case Core::INFO :
		_brain.keepInfo(command);
		break;
	case Core::BOARD :
		_brain.keepAndSetBoard();
		break;
	default:
		auto iter = _commands.find(command);
		if (iter != _commands.end())
			(this->*_commands[commandType])();
		break;
	}
}

void Core::getCommand()
{
    std::string command;
    std::string commandType;
    command = _reader.read();
    commandType = _reader.retrieveCommandType(command);
    dispatchCommand(commandType, command);
}


void Core::play()
{
    while (true) {
        getCommand();
        if (_playing) {
            if (_brain.getIsMyTurn()) {
                _brain.move();
				_brain.setIsMyTurn(false);
            }
        } else if (_gameLaunched){
            break;
        }
    }
}

void Core::startGame(std::string command)
{
    if (!_reader.checkResponseStart(command)) {
        std::cout << "ERROR Size not valid (expected 19x19)" << std::endl;
    } else {
        _playing = true;
        _gameLaunched = true;
		std::cout << "OK" << std::endl;
    }
}

void Core::beginGame()
{
    _brain.setIsMyTurn(true);
}

void Core::endGame()
{
    _playing = false;
    _gameLaunched = false;
}

void Core::about()
{
    _brain.about();
}

void Core::restart()
{
    _playing = true;
    _gameLaunched = true;
    _brain.restart();
}