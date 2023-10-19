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
#include "ce_timer.h"
#include "enemy_dialog.h"
#include <string>

#define FASE_2_ENEMY_SPAWN_INTERVAL 2000
#define FASE_2_SCORE_TO_PASS 5
#define FASE_2_MAX_ENEMIES_ON_SCREEN 2
#define FASE_2_TIME_TO_PASS 20000
#define FASE_2_SHOW_PACIFIST_DIALOG 8000

class FASE2 {
public:
    FASE2();
    bool run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine, bool *pacifist);
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
    void checkPacifistDialog();
    bool pacificPass();
    unsigned int enemiesSpawned;
    unsigned int score;
    bool mainShipDestroyed;
    bool pacifistDialogShown;
    CEText *scoreText;
    CleytinEngine *engine;
    CleytinAudioEngine *audioEngine;
    CleytinControls *controls;
    CETimer *timerToPass;
    CETimer *enemySpawnTimer;
};

#endif
