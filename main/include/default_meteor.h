#ifndef DEFAULT_METEOR_H
#define DEFAULT_METEOR_H

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "ce_linear_move_animation.h"
#include "main_laser_beam.h"
#include <functional>

class DefaultMeteor : public CEColorfulBitmap {
public:
    DefaultMeteor();
    ~DefaultMeteor();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void setOnDestroyed(std::function<void()> callback);
    bool checkColisions(CleytinEngine *engine);
    void despawn(CleytinEngine *engine);

private:
    CELinearMoveAnimation *animation;
    std::function<void()> onDestroyed = NULL;
};

#endif
