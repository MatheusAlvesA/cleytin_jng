#ifndef FASE_2_JNG
#define FASE_2_JNG

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
#include <string>

#define FASE_2_ENEMY_SPAWN_INTERVAL 3000
#define FASE_2_SCORE_TO_PASS 5

class FASE2 {
public:
    FASE2();
    bool run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine);
    void onEnemyDestroyed();
    void onMainShipDestroyed();
    void updateScoreDisplay();
    void gameOver();

private:
    void spawnEnemy();
    void setupBackground(bool withScore);
    void setupMainShip();
    void clean();
    void opening();
    unsigned int enemiesSpawned;
    uint64_t lastEnemySpawn;
    unsigned int score;
    bool mainShipDestroyed;
    CEText *scoreText;
    CleytinEngine *engine;
    CleytinAudioEngine *audioEngine;
    CleytinControls *controls;
};

#endif
