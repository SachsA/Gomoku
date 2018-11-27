/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Reader
*/

#include <string>

#ifndef READER_HPP_
	#define READER_HPP_

class Reader {
	public:
		Reader() = default;
		~Reader() = default;

		bool checkBoardSizeValid(std::string& boardSizeString);
		bool checkResponseStart(std::string& response);
		std::string read();
		std::string retrieveCommandType(std::string command);
};

#endif /* !READER_HPP_ */
