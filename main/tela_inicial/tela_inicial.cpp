#include "tela_inicial.h"

bool TelaInicial::run(CleytinEngine *engine, CleytinControls *controls) {
    this->engine = engine;
    this->controls = controls;

    this->screen();

    this->clean();
    return false;
}

void TelaInicial::clean() {
    this->engine->clear(true);
}

void TelaInicial::screen() {
    this->setupBackground();

    CEText *text = new CEText();
    text->setText("Pressione\n  START");
    text->setBaseColor({255, 255, 255});
    text->setSizeMultiplier(2);
    text->setPos(85, 90);
    text->setPriority(2);
    this->engine->addObject(text);

    this->engine->loopAndRender();
    cleytin_delay(500);
    while(!this->controls->getStart()) {
        this->engine->loopAndRender();
    }
}

void TelaInicial::setupBackground() {
    CEColorfulBitmap *bitmap = new CEColorfulBitmap();
    bitmap->setBuffer(sprite_color_bg_00);
    bitmap->setHeight(240);
    bitmap->setWidth(320);
    bitmap->setColisionEnabled(false);
    bitmap->setHasTransparency(false);
    this->engine->addObject(bitmap);
}
