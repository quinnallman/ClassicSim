#ifndef MAGE_H
#define MAGE_H

#include "Class.h"

class Mage: public Class {
public:
    Mage(Race* race, Stats* stats, Engine* engine) : Class(race, stats, engine) {}

    std::string get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() const override;
    float global_cooldown() const override;

protected:
private:
};

#endif // MAGE_H
