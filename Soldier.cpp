//
// Created by aribr on 11/06/2021.
//

#include "Soldier.h"
#include "Exceptions.h"

namespace mtm{
    Soldier::Soldier(Team team, int health, int ammo, int range, int power) :
            Character(team, health, ammo, range, power) {}

    void Soldier::reload() {
        ammo += reload_rate;
    }
    void Soldier::checkTarget(const GridPoint& attacker ,const GridPoint& attacked,
                              std::shared_ptr<Character> attacked_character) const {
        int distance = GridPoint::distance(attacker, attacked);
        if(distance > range){
            throw OutOfRange();
        }
        if(ammo < attack_cost){
            throw OutOfAmmo();
        }
        if(attacked.col != attacker.col && attacked.row != attacker.row){
            throw IllegalTarget();
        }
    }
    void Soldier::attack(Map &board, const GridPoint &src, const GridPoint &dest)
    {
        attackWithinTheTargetRadius(board , dest);
        ammo -= attack_cost;
        if(board.at(dest) != nullptr && board.at(dest)->getTeam() != team){
            if(board.at(dest)->reduceHealth(power)){
                board.at(dest) = nullptr;
            }
        }
    }
    Character * Soldier::clone() const {
        return new Soldier(*this);
    }
    units_t Soldier::getMaxMove() const {
        return soldier_move_range;
    }
    void Soldier::attackWithinTheTargetRadius(Map &board, const GridPoint &dest) {
        for (it & it : board) {

            if (it.second == nullptr || it.first == dest || it.second->getTeam() == this->team ||
                GridPoint::distance(it.first , dest)> ceil((double) this->range/attack_radios_rate)){
                continue;
            }

            if (it.second->reduceHealth(ceil((double) this->power/non_target_damage_rate))){
                it.second = nullptr;
            }
        }
    }
    char Soldier::getType() const {
        if(team == CROSSFITTERS){
            return SOLDIER_CROSSFITTER;
        }
        return SOLDIER_POWERLIFTER;
    }
}
