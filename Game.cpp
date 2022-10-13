
#include "Game.h"
#include "Exceptions.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Medic.h"

using namespace std;
namespace mtm{
    Game::Game(int height, int width) :
            height(height), width(width) {
        if(height <= 0 || width <= 0){
            throw IllegalArgument();
        }
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                board[GridPoint(i,j)] = nullptr;
            }
        }
    }
    Game::Game(const Game& other) : height(other.height), width(other.width)
    {
        Game new_game(other.height, other.width);
        for(const it& cel : other.board)
        {
            if(cel.second != nullptr){
                new_game.board.at(cel.first) =  shared_ptr<Character>((cel.second->clone()));
            }
        }
        swap(board, new_game.board);
    }
    Game& Game::operator=(const Game& other)
    {
        Game new_game(other);
        width = other.width;
        height = other.height;
        swap(board, new_game.board);
        return *this;
    }

    void Game::addCharacter(const GridPoint& coordinates, shared_ptr<Character> character)
    {
        if(!checkInRange(coordinates)){
            throw IllegalCell();
        }
        if(board[coordinates] != nullptr){
            throw CellOccupied();
        }
        board[coordinates] = character;
    }
    shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health,
                                              units_t ammo, units_t range, units_t power)
    {
        if(health <= 0 ||  range < 0 || ammo < 0 || power < 0){
            throw IllegalArgument();
        }
        if(type == SOLDIER) {
            shared_ptr<Character> new_character(new Soldier(team, health, ammo, range, power));
            return new_character;
        }
        else if(type == MEDIC) {
            shared_ptr<Character> new_character(new Medic(team, health, ammo, range, power));
            return new_character;
        }
        shared_ptr<Character> new_character(new Sniper(team, health, ammo, range, power));
        return new_character;
    }
    void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        if(!checkInRange(src_coordinates) || !checkInRange(dst_coordinates)){
            throw IllegalCell();
        }
        if(board[src_coordinates] == nullptr){
            throw CellEmpty();
        }
        if(GridPoint::distance(src_coordinates, dst_coordinates) > board[src_coordinates]->getMaxMove()){
            throw MoveTooFar();
        }
        if(board[dst_coordinates] != nullptr){
            throw CellOccupied();
        }
        swap(board[src_coordinates],board[dst_coordinates]);
    }
    void Game::attack(const GridPoint& src_coordination, const GridPoint& dst_coordination)
    {
        if(!checkInRange(src_coordination) || !checkInRange(dst_coordination)){
            throw IllegalCell();
        }
        if(board[src_coordination] == nullptr){
            throw CellEmpty();
        }
        board[src_coordination]->checkTarget(src_coordination, dst_coordination, board.at(dst_coordination));
        board[src_coordination]->attack(board , src_coordination , dst_coordination);

    }
    void Game::reload(const GridPoint& coordinates)
    {
        if(!checkInRange(coordinates)){
            throw IllegalCell();
        }
        if(board[coordinates] == nullptr){
            throw CellEmpty();
        }
        board[coordinates]->reload();
    }
    bool Game::isOver(Team* winningTeam)
    {
        int num_crossfitters = 0, num_powerlifters = 0;
        for(const it& cel : board){
            if(cel.second != nullptr){{
                    if(cel.second->getTeam() == POWERLIFTERS) {
                        num_powerlifters++;
                        continue;
                    }
                    num_crossfitters++;
                }
            }
        }
        if((num_crossfitters == 0 && num_powerlifters == 0) ||
           (num_crossfitters > 0 && num_powerlifters > 0)){
            return false;
        }
        if(num_powerlifters > 0) {
            if (winningTeam != nullptr) {
                *winningTeam = POWERLIFTERS;
            }
        }
        else if(winningTeam != nullptr){
            *winningTeam = CROSSFITTERS;
        }
        return true;
    }
    ostream& operator<<(ostream &os, const Game &game) {
        vector<char> v;
        for(const it& cel : game.board)
        {
            if(cel.second == nullptr){
                v.push_back(' ');
            }
            else{
                v.push_back(cel.second->getType());
            }
        }
        v.push_back('X');
        return mtm::printGameBoard(os, &v[0], &v[v.size() - 1], game.width);
    }

    bool Game::checkInRange(const GridPoint& coordinates) const
    {
        if(coordinates.col < 0 || coordinates.row < 0 || coordinates.row >= height || coordinates.col >= width){
            return false;
        }
        return true;
    }

}
