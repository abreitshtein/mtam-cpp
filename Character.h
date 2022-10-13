//
// Created by aribr on 11/06/2021.
//

#ifndef MTM_EX2_B_GAME_CHARACTER_H
#define MTM_EX2_B_GAME_CHARACTER_H

#include "Auxiliaries.h"
#include <vector>
#include <map>
#include <memory>
#include "Compare.h"
namespace mtm {
    class Character {
    public:

        static const int min_health = 0;

        /**
         * constructor:
        @param team , health, ammo, range, power - all characters' units
        @return new Character
         **/

        Character(Team team , units_t health, units_t ammo, units_t range, units_t power) :
                team(team) , health(health), ammo(ammo), range(range), power(power) {}
        /**
         * copy constructor:
         * @param character - a reference to another character to copy from
         * @return the copied character
         */

        Character(const Character& character) = default;

        /**
         * a virtual default destructor of a character
         */

        virtual ~Character() = default;

        typedef std::map<GridPoint, std::shared_ptr <Character>, compare> Map;

        /**
         * attacks the destination coordinates
         * @param board - the game board
         * @param src - the coordinates of the attacker
         * @param des - the coordinates of the destination
         */

        virtual void attack(Map & board,const GridPoint& src, const GridPoint& dest) = 0;

        /**
         * reloads characters ammo
         */

        virtual void reload() = 0;
        /**
         * getMaxMove
         * @return returns the num of max steps at each move
         */

        virtual units_t getMaxMove() const = 0;

        /**
         * function that checks if the target of attack is legal
         * @param attacker - the coordinates of the attacker
         * @param attacked - the coordinates of the destination
         * @param attacked_character - the character which is being attacked
         * @throws OutOfRange() - if the target coordinates are out of range
         * @return OutOfAmmo() - if character is out of ammo
         * @return IllegalTarget() - this throw is according to the characters' rules
         *         and explained by each character
         */

        virtual void checkTarget(const GridPoint& attacker ,const GridPoint& attacked,
                                 std::shared_ptr<Character> attacked_character) const = 0;

        /**
         * a virtual function that copies the character by its type
         * @return a pointer to the character
         */

        virtual Character* clone() const = 0;

        /**
         * returns
         * @return the symbol ( M , m , S , s , N , n) of the character
         * according to the rules of printing
         */

        virtual char getType() const = 0;

        /**
         * function that adds health to a character
         * @param points - num of health units to add
         */

        void addHealth( int points);

        /**
         * function that reduces health form a character
         * @param points - num of health units to reduce
         * @return :
         * true - if the health units are above 0
         * false - otherwise
         */

        bool reduceHealth(int points);

        /**
         * function that returns the characters' team
         * @return  characters' team
         */

        Team getTeam() const;



    protected:
        Team team;
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
    };
    typedef std::pair<const GridPoint ,std::shared_ptr<Character>> it;


}

#endif //MTM_EX2_B_GAME_CHARACTER_H
