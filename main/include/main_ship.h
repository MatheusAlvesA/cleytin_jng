#ifndef MAIN_SHIP
#define MAIN_SHIP

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "main_laser_beam.h"
#include "default_meteor.h"
#include "cleytin_audio.h"
#include "audios.h"
#include <functional>

class MainShip : public CEColorfulBitmap {
public:
    MainShip();
    ~MainShip();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void setControls(CleytinControls *controls);
    void setAudioInterface(CleytinAudio *interface);
    void setOnMainShipDestroyed(std::function<void()> callback);

private:
    CleytinEngine *engine;
    CleytinControls *controls;
    CEMoveControls *moveControls;
    CleytinAudio *audioInterface;
    void handleControls();
    void checkColisions(CleytinEngine *engine);
    bool fire();
    uint64_t lastFire;
    unsigned int fireRate; // ms
    std::function<void()> onMainShipDestroyed;
};

#endif
