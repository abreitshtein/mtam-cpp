

#include "Character.h"

namespace mtm {

    void Character::addHealth(int points) {
        health += points;
    }
    bool Character::reduceHealth(int points) {
        health-=points;
        if(health <= min_health) {
            return true;
        }
        return false;
    }
    Team Character::getTeam() const {
        return team;
    }

}
