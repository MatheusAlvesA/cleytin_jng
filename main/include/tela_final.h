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
    bool run(CleytinEngine *engine, bool pacifist);

private:
    void setupBackground();
    void dialog();
    void creditos1();
    void creditos2();
    void creditos3();
    void creditos4();
    void generateText(const char* text, int x, int y, uint8_t size);
    bool pacifist;
    CleytinEngine *engine;
};

#endif
