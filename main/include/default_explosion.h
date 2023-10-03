#ifndef DEFAULT_EXPLOSION_H
#define DEFAULT_EXPLOSION_H

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "ce_color_bitmap_sprite_animation.h"

class DefaultExplosion : public CEColorfulBitmap {
public:
    DefaultExplosion();
    ~DefaultExplosion();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CEColorBitmapSpriteAnimation *animation;
};

#endif
