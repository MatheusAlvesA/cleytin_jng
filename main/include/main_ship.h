#ifndef MAIN_SHIP
#define MAIN_SHIP

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "main_laser_beam.h"

class MainShip : public CEColorfulBitmap {
public:
    MainShip();
    ~MainShip();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void setControls(CleytinControls *controls);

private:
    CleytinEngine *engine;
    CleytinControls *controls;
    CEMoveControls *moveControls;
    void handleControls();
    bool fire();
    uint64_t lastFire;
    unsigned int fireRate; // ms
};

#endif
