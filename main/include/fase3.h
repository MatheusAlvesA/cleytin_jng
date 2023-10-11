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
#include "mothership.h"
#include <string>

#define FASE_3_TIME_TO_PASS 20000

class FASE3 {
public:
    FASE3();
    bool run(
        CleytinEngine *engine,
        CleytinControls *controls,
        CleytinAudioEngine *audioEngine,
        bool *pacifist
    );
    void onEnemyDestroyed();
    void onMainShipDestroyed();
    void gameOver();

private:
    void setupBackground();
    void setupShips();
    void clean();
    void opening();
    bool pacificPass();
    bool mainShipDestroyed;
    bool mothershipDestroyed;
    bool pacifist;
    CleytinEngine *engine;
    CleytinAudioEngine *audioEngine;
    CleytinControls *controls;
    CETimer *timerToPass;
};

#endif
