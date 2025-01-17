#include "BerserkerRage.h"

#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "StatisticsResource.h"
#include "Warrior.h"

BerserkerRage::BerserkerRage(Character* pchar) :
    Spell("Berserker Rage", "Assets/spell/Spell_nature_ancestralguardian.png", pchar, new CooldownControl(pchar, 30.0), RestrictedByGcd::No, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Berserker Rage", 2, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    statistics_resource(nullptr),
    talent_ranks({0, 5, 10})
{}

SpellStatus BerserkerRage::is_ready_spell_specific() const {
    if (warr->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warr->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    return SpellStatus::Available;
}

BerserkerRage::~BerserkerRage() {
    delete cooldown;
}

void BerserkerRage::spell_effect() {
    cooldown->add_spell_cd_event();

    unsigned rage_before_gain = warr->get_resource_level(ResourceType::Rage);
    warr->gain_rage(rage_gain);
    unsigned delta = warr->get_resource_level(ResourceType::Rage) - rage_before_gain;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, rage_gain);
}

void BerserkerRage::increase_talent_rank_effect(const QString&, const int curr) {
    rage_gain = talent_ranks[curr];
}

void BerserkerRage::decrease_talent_rank_effect(const QString&, const int curr) {
    rage_gain = talent_ranks[curr];
}

void BerserkerRage::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
