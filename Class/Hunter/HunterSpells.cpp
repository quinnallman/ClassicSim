#include "HunterSpells.h"

#include "AimedShot.h"
#include "AspectOfTheHawk.h"
#include "AutoShot.h"
#include "Berserking.h"
#include "BestialWrath.h"
#include "Engine.h"
#include "ExposeWeaknessBuff.h"
#include "ExposeWeaknessProc.h"
#include "Hunter.h"
#include "HuntersMark.h"
#include "HuntersMarkBuff.h"
#include "MainhandAttack.h"
#include "MultiShot.h"
#include "OffhandAttack.h"
#include "OffhandMeleeHit.h"
#include "Pet.h"
#include "RaidControl.h"
#include "RangedHit.h"
#include "RapidFire.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->berserking = new Berserking(pchar, ResourceType::Mana, 130);
    add_spell_group({berserking});

    this->aimed_shot = new AimedShot(hunter, new_cooldown_control("Aimed Shot", 6.0));
    this->aspect_of_the_hawk = new AspectOfTheHawk(hunter);
    this->auto_shot = new AutoShot(hunter);
    this->bestial_wrath = new BestialWrath(hunter, "Cat");
    this->mh_attack = new MainhandAttack(hunter);
    this->multi_shot = new MultiShot(hunter, new_cooldown_control("Multi-Shot", 10.0));
    this->oh_attack = new OffhandAttack(hunter);
    this->rapid_fire = new RapidFire(hunter);

    auto* hunters_mark_buff = dynamic_cast<HuntersMarkBuff*>(pchar->get_raid_control()->get_shared_raid_buff("Hunter's Mark"));
    if (hunters_mark_buff == nullptr) {
        hunters_mark_buff = new HuntersMarkBuff(hunter);
        hunters_mark_buff->enable_buff();
    }
    this->hunters_mark = new HuntersMark(hunter, hunters_mark_buff);

    auto* expose_weakness_buff = dynamic_cast<ExposeWeaknessBuff*>(pchar->get_raid_control()->get_shared_raid_buff("Expose Weakness"));
    if (expose_weakness_buff == nullptr) {
        expose_weakness_buff = new ExposeWeaknessBuff(hunter);
        expose_weakness_buff->enable_buff();
    }
    this->expose_weakness_proc = new ExposeWeaknessProc(hunter, expose_weakness_buff);

    add_spell_group({aimed_shot});
    add_spell_group({aspect_of_the_hawk});
    add_spell_group({auto_shot});
    add_spell_group({bestial_wrath});
    add_spell_group({hunters_mark});
    add_spell_group({mh_attack});
    add_spell_group({multi_shot});
    add_spell_group({oh_attack});
    add_spell_group({rapid_fire});
}

HunterSpells::~HunterSpells() {
    delete expose_weakness_proc;
}

void HunterSpells::start_pet_attack() {
    hunter->get_pet()->start_attack();
}

void HunterSpells::add_next_ranged_attack() {
    if (attack_mode != AttackMode::RangedAttack)
        return;

    auto* new_event = new RangedHit(this, auto_shot->get_next_expected_use(), auto_shot->get_next_iteration());
    hunter->get_engine()->add_event(new_event);
}

void HunterSpells::ranged_auto_attack(const int iteration) {
    if (!auto_shot->attack_is_valid(iteration))
        return;

    if (!is_ranged_attacking())
        return;

    auto_shot->perform();

    add_next_ranged_attack();
}

void HunterSpells::add_next_oh_attack() {
    if (attack_mode != AttackMode::MeleeAttack)
        return;

    oh_attack->add_next_oh_attack();
}

void HunterSpells::oh_auto_attack(const int iteration) {
    if (!oh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    oh_attack->perform();

    add_next_oh_attack();
}

AimedShot* HunterSpells::get_aimed_shot() const {
    return this->aimed_shot;
}

AspectOfTheHawk* HunterSpells::get_aspect_of_the_hawk() const {
    return this->aspect_of_the_hawk;
}

AutoShot* HunterSpells::get_auto_shot() const {
    return this->auto_shot;
}

BestialWrath* HunterSpells::get_bestial_wrath() const {
    return this->bestial_wrath;
}

ExposeWeaknessProc* HunterSpells::get_expose_weakness_proc() const {
    return this->expose_weakness_proc;
}

MultiShot* HunterSpells::get_multi_shot() const {
    return this->multi_shot;
}

OffhandAttack* HunterSpells::get_oh_attack() const {
    return this->oh_attack;
}

RapidFire* HunterSpells::get_rapid_fire() const {
    return this->rapid_fire;
}
