
//
// Created by alonx on 11/06/2021.
//
#include "iostream"
#ifndef UNTITLED22_EXCEPTION_H
#define UNTITLED22_EXCEPTION_H

namespace mtm {
    class Exceptions : public std::exception{
    public:
        virtual const char* what() const noexcept override = 0;
    };

    class IllegalArgument : public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell : public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty: public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: CellEmpty";
        }
    };
    class MoveTooFar: public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class CellOccupied: public Exceptions {
    public:
        const char* what() const noexcept override {
            return "A game related error has occurred: CellOccupied";
        }
    };
    class OutOfRange: public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo: public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget: public Exceptions {
    public:
        const char* what() const noexcept override{
            return "A game related error has occurred: IllegalTarget";
        }

    };
}

#endif //UNTITLED22_EXCEPTION_H
