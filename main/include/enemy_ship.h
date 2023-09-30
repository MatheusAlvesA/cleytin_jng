#ifndef ENEMY_SHIP
#define ENEMY_SHIP

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "main_laser_beam.h"
#include "default_meteor.h"
#include "cleytin_audio_engine.h"
#include "audios.h"
#include <functional>

class EnemyShip : public CEColorfulBitmap {
public:
    EnemyShip(unsigned int id);
    ~EnemyShip();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void setOnShipDestroyed(std::function<void()> callback);

private:
    CleytinEngine *engine;
    void checkColisions();
    bool fire();
    uint64_t lastFire;
    unsigned int fireRate; // ms
    unsigned int id;
    std::function<void()> onShipDestroyed;
};

#endif
