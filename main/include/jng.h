#ifndef FASE_1_JNG
#define FASE_1_JNG

#include "cleytin_engine.h"
#include "ce_text.h"
#include "ce_container.h"
#include "ce_colorful_bitmap.h"
#include "main_ship.h"
#include "cleytin_controls.h"
#include "default_meteor.h"

#define METEOR_SPAWN_INTERVAL 1000

class JNG {
public:
    void run(CleytinEngine *engine);

private:
    void spawnMeteor(CleytinEngine *engine);
    uint64_t lastMeteorSpawn = 0;
};

#endif
