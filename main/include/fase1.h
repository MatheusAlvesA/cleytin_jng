#ifndef FASE_1_JNG
#define FASE_1_JNG

#include "cleytin_engine.h"
#include "sprites.h"
#include "ce_text.h"
#include "ce_container.h"
#include "ce_colorful_bitmap.h"
#include "main_ship.h"
#include "cleytin_controls.h"
#include "default_meteor.h"
#include "cleytin_audio_engine.h"
#include "ce_rectangle.h"
#include <string>

#define METEOR_SPAWN_INTERVAL 1500
#define SCORE_TO_PASS 20

class FASE1 {
public:
    FASE1();
    bool run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine);
    void onMeteorDestroyed();
    void onMainShipDestroyed();
    void updateScoreDisplay();
    void gameOver();

private:
    void spawnMeteor();
    void setupBackground(bool withScore);
    void setupMainShip();
    void clean();
    void opening();
    uint64_t lastMeteorSpawn;
    unsigned int score;
    bool mainShipDestroyed;
    CEText *scoreText;
    CleytinEngine *engine;
    CleytinAudioEngine *audioEngine;
    CleytinControls *controls;
};

#endif
