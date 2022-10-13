//
// Created by aribr on 11/06/2021.
//

#ifndef MTM_EX2_B_GAME_MEDIC_H
#define MTM_EX2_B_GAME_MEDIC_H

#include "Character.h"
#include "Game.h"
#include "Compare.h"

//note: Except for the documented all functions are documented at Character.h

namespace mtm {
    class Medic : public Character{
    public:
        static const char MEDIC_CROSSFITTER = 'm';
        static const char MEDIC_POWERLIFTER = 'M';
        static const int medic_move_range = 5;
        static const int reload_rate = 5;
        static const int attack_cost = 1;

        Medic(Team team , int health, int ammo, int range, int power);

        Medic(const Medic& medic) = default;

        void reload() override;

        /** checkTarget
        * all as documented at Character.h except for the following throw
        * @throws IllegalTarget() - if the target cell is empty or attacked == attacker
        */
        void checkTarget(const GridPoint& attacker ,const GridPoint& attacked,
                         std::shared_ptr<Character> attacked_character) const override;

        void attack(Map & board, const GridPoint& src,const GridPoint& dest) override;

        units_t getMaxMove() const override;

        Character* clone() const override;

        ~Medic() override = default;

        char getType() const override;
    };

}


#endif //MTM_EX2_B_GAME_MEDIC_H
