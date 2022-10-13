//
// Created by aribr on 11/06/2021.
//

#ifndef MTM_EX2_B_GAME_SOLDIER_H
#define MTM_EX2_B_GAME_SOLDIER_H
#include "Character.h"

//note: Except for the documented all functions are documented at Character.h

namespace mtm {
    class Soldier : public Character{

    public:
        static const char SOLDIER_CROSSFITTER = 's';
        static const char SOLDIER_POWERLIFTER = 'S';
        static const int non_target_damage_rate = 2;
        static const int attack_radios_rate = 3;
        static const int soldier_move_range = 3;
        static const int reload_rate = 3;
        static const int attack_cost = 1;

        Soldier(Team team , int health, int ammo,
                int range, int power);

        Soldier(const Soldier& medic) = default;

        void reload() override;

        /** checkTarget
         * all as documented at Character.h except for the following throw
         * @throws IllegalTarget() - if the target is not at the same row and not in the same col
         */

        void checkTarget(const GridPoint& attacker ,const GridPoint& attacked,
                         std::shared_ptr<Character> attacked_character) const override ;

        units_t getMaxMove() const override;

        void attack(Map & board, const GridPoint& src, const GridPoint& dest) override;

        /**
         * attackWithinTheTargetRadius - function that reduce health from all characters
         * in the "damage" radios of the attacker that are not in the attackers' team
         * (except for the target itself)
         * @param board - the game board
         * @param dest - the target destination
         */

        void attackWithinTheTargetRadius(Map & board ,const GridPoint& dest);

        Character* clone() const override;

        ~Soldier() override = default;

        char getType() const override;
    };

}

#endif //MTM_EX2_B_GAME_SOLDIER_H
