#ifndef TELA_FINAL_JNG
#define TELA_FINAL_JNG

#include "cleytin_engine.h"
#include "sprites.h"
#include "ce_text.h"
#include "ce_colorful_bitmap.h"
#include "cleytin_audio_engine.h"
#include "ce_rectangle.h"
#include "ce_timer.h"
#include "audios.h"
#include "ce_text_reveal_animation.h"
#include <string>

class TelaFinal {
public:
    bool run(
        CleytinEngine *engine,
        CleytinAudioEngine *audioEngine,
        bool pacifist
    );

private:
    void setupBackground();
    void clean();
    void dialog();
    bool pacifist;
    CleytinEngine *engine;
    CleytinAudioEngine *audioEngine;
};

#endif