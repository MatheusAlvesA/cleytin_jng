#ifndef TELA_INICIAL_JNG
#define TELA_INICIAL_JNG

#include "cleytin_engine.h"
#include "sprites.h"
#include "ce_text.h"
#include "ce_colorful_bitmap.h"
#include "cleytin_controls.h"

class TelaInicial {
public:
    bool run(CleytinEngine *engine, CleytinControls *controls);

private:
    void setupBackground();
    void clean();
    void screen();
    CleytinEngine *engine;
    CleytinControls *controls;
};

#endif
