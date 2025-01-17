#pragma once

#include "SpellPeriodic.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Warrior;

class DeepWounds: public SpellPeriodic, public TalentRequirer {
public:
    DeepWounds(Character* pchar);
    ~DeepWounds() override;

private:
    Warrior* warr;
    double wpn_percent {0.0};
    double previous_tick_rest {0.0};
    QVector<int> stacks;
    const QVector<double> talent_ranks;

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void tick_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
