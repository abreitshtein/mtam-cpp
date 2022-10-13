//
// Created by aribr on 11/06/2021.
//
#include "Medic.h"
#include "Exceptions.h"

using std::vector;
namespace mtm {
    Medic::Medic(Team team, int health, int ammo, int range, int power) :
            Character(team, health, ammo, range, power) {}

    void Medic::reload() {
        ammo += reload_rate;
    }

    void Medic::checkTarget(const GridPoint& attacker ,const GridPoint& attacked,
                            std::shared_ptr<Character> attacked_character) const {
        int distance = GridPoint::distance(attacker , attacked);
        if(distance > range){
            throw OutOfRange();
        }
        if(attacked_character != nullptr && attacked_character->getTeam() != team && ammo < attack_cost){
            throw OutOfAmmo();
        }
        if(attacked_character == nullptr || attacked == attacker){
            throw IllegalTarget();
        }
    }
    void Medic::attack(Map& board, const GridPoint& src, const GridPoint& dest)
    {
        if(board.at(dest)->getTeam() != team){
            ammo -= attack_cost;
            if(board.at(dest)-> reduceHealth(power)){
                board.at(dest) = nullptr;
            }
            return;
        }
        board.at(dest)->addHealth(power);

    }
    Character* Medic::clone() const {
        return new Medic(*this);
    }
    units_t Medic::getMaxMove() const {
        return medic_move_range;
    }
    char Medic::getType() const {
        if(team == CROSSFITTERS){
            return MEDIC_CROSSFITTER;
        }
        return MEDIC_POWERLIFTER;
    }
}