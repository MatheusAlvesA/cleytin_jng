#ifndef FASE_3_JNG
#define FASE_3_JNG

#include "cleytin_engine.h"
#include "sprites.h"
#include "ce_text.h"
#include "ce_container.h"
#include "ce_colorful_bitmap.h"
#include "main_ship.h"
#include "cleytin_controls.h"
#include "cleytin_audio_engine.h"
#include "ce_rectangle.h"
#include "enemy_ship.h"
#include "ce_timer.h"
#include "enemy_dialog.h"
#include <string>

class FASE3 {
public:
    FASE3();
    bool run(
        CleytinEngine *engine,
        CleytinControls *controls,
        CleytinAudioEngine *audioEngine,
        bool pacifist
    );
    void onEnemyDestroyed();
    void onMainShipDestroyed();
    void gameOver();

private:
    void setupBackground();
    void setupMainShip();
    void clean();
    void opening();
    bool pacificPass();
    bool mainShipDestroyed;
    bool pacifist;
    CleytinEngine *engine;
    CleytinAudioEngine *audioEngine;
    CleytinControls *controls;
    CETimer *timerToPass;
};

#endif
