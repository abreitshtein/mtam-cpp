//
// Created by aribr on 11/06/2021.
//
#include "Sniper.h"
#include "Exceptions.h"
namespace mtm{
    Sniper::Sniper(Team team, int health, int ammo, int range, int power) :
            Character(team, health, ammo, range, power),attack_counter(0) {}

    void Sniper::reload() {
        ammo += reload_rate;
    }

    void Sniper::checkTarget(const GridPoint &attacker, const GridPoint &attacked,
                             std::shared_ptr<Character> attacked_character) const {
        int distance = GridPoint::distance(attacker , attacked);
        if(distance > range || std::ceil((double) range / min_range_rate ) > distance){
            throw OutOfRange();
        }
        if(ammo < attack_cost){
            throw OutOfAmmo();
        }
        if(attacked_character == nullptr || attacked_character->getTeam() == team){

            throw IllegalTarget();
        }
    }

    Character* Sniper::clone() const {
        return new Sniper(*this);
    }
    void Sniper::attack(Map& board, const GridPoint& src, const GridPoint& dest) {
        ammo -= attack_cost;
        if(attack_counter % good_shut == time_for_good_shut) {
            if (board.at(dest)->reduceHealth(power * double_damage)) {
                board.at(dest)= nullptr;
            }
        }
        else {
            if (board.at(dest)->reduceHealth(power)) {
                board.at(dest) = nullptr;
            }
        }
        attack_counter++;
        attack_counter = attack_counter % good_shut;
    }
    units_t Sniper::getMaxMove() const {
        return sniper_move_range;
    }
    char Sniper::getType() const {
        if(team == CROSSFITTERS){
            return SNIPER_CROSSFITTER;
        }
        return SNIPER_POWERLIFTER;
    }
}
