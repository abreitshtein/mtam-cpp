
#ifndef UNTITLED22_GAME_H
#define UNTITLED22_GAME_H

#include "Auxiliaries.h"
#include "iostream"
#include "Character.h"
#include "Compare.h"
#include <map>
#include <memory>

namespace mtm{
    class Game{
        std::map<GridPoint, std::shared_ptr <Character>, compare> board;
        int height;
        int width;
        /** checkInRange
         * @param: GridPoint with coordinates.
        * @return true if the GridPoint inside the map. false otherwise.
          **/
        bool checkInRange(const GridPoint& coordinates) const;
    public:
        /** constructor
        * @param: height - the height of the board.
        * @param: width - the width of the board.
        * @return a new game with this height and width.
        * @throw IllegalArgument if one of the parameters is zero or below.
         **/
        Game(int height, int width);

        /** copy constructor
        * @param: other - another game.
        * @return a new copied game with same data.
        * @throw bad_alloc if there was a allocation problem **/
        Game(const Game& other);

        /** default destructor.**/
        ~Game() = default;

        /** overloading operator =
        * @param: other - another game.
        * @return a new reference to copied game with same data.
        * @throw bad_alloc if there was a allocation problem
         **/
        Game& operator=(const Game& other);

        /** addCharacter
        * @param: coordinates - coordinates.
        * @param: character - smart ptr to a character.
        * add this character to the location of the coordinates
        * @return nothing.
        * @throw IllegalCell if the coordinates not in the board.
        * @throw CellOccupied if there i already a character in the cell
         **/
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

        /** makeCharacter
        * @param: type - enum of the charcaterType.
        * @param: team - enum of the team.
        * @param - health - the health as a positive number.
        * @param - ammo - number of the ammo.
        * @param - range - the range of the character
        * @param - power - the power of the character
        * @return  a smart_ptr to the new character with this data.
        * @throw IllegalArgument if one of the parameters is below zero
        * @throw bad_alloc if there was a allocation problem
         **/
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
                                                        units_t ammo, units_t range, units_t power);

        /** move
         * @param: src_coordinates and dst_coordinates.
         * move a character from src_coordinates to dst_coordinates in the board.
         * @return  nothing.
         * @throw IllegalCell if one of the coordinates is not in the board.
         * @throw CellEmpty if the src_coordinates cell is empty.
         * @throw MoveTooFar if attempt to move the character beyond his max move range.
         * @throw CellOccupied id the dst_coordinates cell is occupied
          **/
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

        /** reload
        * @param: coordinates.
        * reload a character ammo in this coordinates.
        * @return  nothing.
        * @throw IllegalCell if the coordinates is not in the board.
        * @throw CellEmpty if the cell with this coordinates is empty
         **/
        void reload(const GridPoint& coordinates);

        /** overload operator <<
         * @param: ostream, referance to a game.
         * @return  the printing function provided by the stuff.
         * fill a vector of char according to the rules:
         * if the cell is empty, it will be fill with '-'.
         * for Crossfitters team: if solider in this cell, will fill with 's'.
         * if medic, will be fill with 'm'. if sniper, with 'n'.
         * for the powerlifting team, same latter but in cappital.
         * @throw bad_alloc if there was a allocation problem
         **/
        friend std::ostream& operator<<(std::ostream &os, const Game &game);

        /** isOver
         * @param: pointer that set in default to be null
         * @return  return true if a game over. false otherwise.
         * if there is winning team, put it in the pointer if not null.
         **/
        bool isOver(Team* winningTeam = nullptr);

        /** attack
         * @param: src_coordinates and dst_coordinates.
         * @return  nothing.
         * make attack from src_coordinates to dst_coordinates.
         * @throw IllegalCell if one of the coordination is not in the board.
         * @throw CellEmpty if the src_coordination is empty.
         * @throw a exception from the character function. if no exception, make the attack
         **/
        void attack(const GridPoint& src_coordination, const GridPoint& dst_coordination);

    };
}

#endif //UNTITLED22_GAME_H
