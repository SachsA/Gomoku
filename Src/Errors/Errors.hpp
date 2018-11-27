/*
** EPITECH PROJECT, 2018
** Gomoku
** File description:
** Errors
*/

#include <ostream>
#include <string>
#include <exception>

#ifndef ERRORS_HPP_
	#define ERRORS_HPP_

class Errors: public std::exception {
public:
        Errors(std::ostream &, const std::string &) throw();
        virtual ~Errors(void) throw() = default;

        const char *what(void) const throw();

private:
        std::string _message;
        std::ostream &_os;
};

#endif /* !ERRORS_HPP_ */