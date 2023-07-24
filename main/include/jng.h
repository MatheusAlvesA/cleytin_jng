#ifndef FASE_1_JNG
#define FASE_1_JNG

#include "cleytin_engine.h"
#include "ce_text.h"
#include "ce_container.h"
#include "ce_colorful_bitmap.h"
#include "main_ship.h"
#include "cleytin_controls.h"
#include "default_meteor.h"
#include "ce_text.h"
#include <string>

#define METEOR_SPAWN_INTERVAL 1000

class JNG {
public:
    void run(CleytinEngine *engine);
    void onMeteorDestroyed();
    void onMainShipDestroyed();
    void updateScoreDisplay(CleytinEngine *engine);
    void gameOver(CleytinEngine *engine, CleytinControls *controls);

private:
    void spawnMeteor(CleytinEngine *engine);
    uint64_t lastMeteorSpawn = 0;
    unsigned int score = 0;
    bool mainShipDestroyed = false;
    CEText *scoreText = NULL;
};

#endif
