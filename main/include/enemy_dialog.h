#ifndef ENEMY_DIALOG
#define ENEMY_DIALOG

#include "cleytin_engine.h"
#include "ce_text.h"
#include "ce_timer.h"
#include "ce_text_reveal_animation.h"

#define ENEMY_DIALOG_TIME 7000

class EnemyDialog : public CEText {
public:
    EnemyDialog();
    ~EnemyDialog();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CleytinEngine *engine;
    CETextRevealAnimation *animation;
    CETimer *timer;
};

#endif
