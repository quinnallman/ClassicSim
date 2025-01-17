#include "Berserking.h"

#include "BerserkingBuff.h"
#include "Character.h"
#include "CooldownControl.h"
#include "Race.h"

Berserking::Berserking(Character* pchar, const ResourceType resource_type, const unsigned resource_cost) :
    Spell("Berserking", "Assets/races/Racial_troll_berserk.png", pchar, new CooldownControl(pchar, 180.0), RestrictedByGcd::Yes, resource_type, resource_cost),
    buff(new BerserkingBuff(pchar))
{
    this->enabled = false;
}

Berserking::~Berserking() {
    delete buff;
    delete cooldown;
}

void Berserking::spell_effect() {
    buff->apply_buff();

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();
}

void Berserking::enable_spell_effect() {
    buff->enable_buff();
}

void Berserking::disable_spell_effect() {
    buff->disable_buff();
}
