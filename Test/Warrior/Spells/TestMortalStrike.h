#ifndef TESTMORTALSTRIKE_H
#define TESTMORTALSTRIKE_H

#include "TestSpellWarrior.h"

class TestMortalStrike: public TestSpellWarrior {
public:
    TestMortalStrike(EquipmentDb *equipment_db);

    void test_all();

    MortalStrike* mortal_strike();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();
    void test_dodge_applies_overpower_buff();

    void when_mortal_strike_is_performed();

private:
};

#endif // TESTMORTALSTRIKE_H