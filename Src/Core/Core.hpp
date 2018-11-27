/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Core
*/

#include <string>
#include <unordered_map>
#include <functional>
#include "Brain.hpp"
#include "Reader.hpp"

#ifndef CORE_HPP_
	#define CORE_HPP_

class Core {
	public:
		Core();
		~Core() = default;

		void dispatchCommand(std::string commandType, std::string command);
		void getCommand();
		void play();

		void startGame(std::string command);
		void beginGame();
		void endGame();
		void about();
		void restart();

	private:
		enum status_info {
			TURN,
			START,
			INFO,
			BOARD,
			UNDEFINED
		};
		Brain _brain;
		Reader _reader;
		int _boardSize;
		bool _playing;
		bool _gameLaunched;
		Core::status_info statusFinder(std::string);
		std::unordered_map<std::string, void(Core::*)()> _commands;
};

#endif /* !CORE_HPP_ */
