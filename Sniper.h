//
// Created by aribr on 11/06/2021.
//

#ifndef MTM_EX2_B_GAME_SNIPER_H
#define MTM_EX2_B_GAME_SNIPER_H
#include "Character.h"

//note: Except for the documented all functions are documented at Character.h

namespace mtm {
    class Sniper : public Character{
    private:
        int attack_counter;
    public:
        static const char SNIPER_CROSSFITTER = 'n';
        static const char SNIPER_POWERLIFTER = 'N';
        static const int min_range_rate = 2;
        static const int time_for_good_shut = 2;
        static const int double_damage = 2;
        static const int sniper_move_range = 4;
        static const int reload_rate = 2;
        static const int attack_cost = 1;
        static const int good_shut = 3;
        Sniper(Team team , int health, int ammo,
               int range, int power);
        Sniper(const Sniper& medic) = default;
        void reload() override;
        void attack(Map & board, const GridPoint& src, const GridPoint& dest) override;

        /** checkTarget
        * all as documented at Character.h except for the following throw
        * @throws IllegalTarget() - if the target is an empty call or the character is
         * in the same team of the attacker
        */

        void checkTarget(const GridPoint& attacker ,const GridPoint& attacked,
                         std::shared_ptr<Character> attacked_character) const override;
        units_t getMaxMove() const override;

        Character* clone() const override;

        ~Sniper() override = default;

        char getType() const override;
    };

}


#endif //MTM_EX2_B_GAME_SNIPER_H
