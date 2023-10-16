#include "tela_final.h"

bool TelaFinal::run(CleytinEngine *engine, CleytinAudioEngine *audioEngine, bool pacifist) {
    this->engine = engine;
    this->audioEngine = audioEngine;
    this->pacifist = pacifist;

    CleytinAudio *audio = NULL;
    this->audioEngine->createAudio(wav_bin_musica_fundo, &audio);
    audio->setLoop(true);
    audio->play();

    this->dialog();

    this->clean();
    return false;
}

void TelaFinal::clean() {
    this->engine->clear(true);
    this->audioEngine->clear();
}

void TelaFinal::dialog() {
    this->setupBackground();

    CEColorfulBitmap *face = new CEColorfulBitmap();
    face->setBuffer(this->pacifist ? sprite_color_woman_face : sprite_color_man_face);
    face->setHeight(44);
    face->setWidth(31);
    face->setPos(20, 76);
    face->setPriority(2);
    face->setSizeMultiplier(2);
    face->setAlphaColor(0xF8);
    this->engine->addObject(face);

    CEText *text = new CEText();
    text->setText(
        this->pacifist
        ? "Você fez a\nescolha certa\n"
          "Não são todos\nque fazem isso"
        : "Muito bem\nsoldado!\n"
          "Você cumpriu\no seu dever."
    );
    text->setBaseColor({255, 255, 255});
    text->setSizeMultiplier(2);
    text->setPos(85, 80);
    text->setPriority(2);

    CETextRevealAnimation animation;
    animation.setObject(text);
    animation.setDuration(7000);
    animation.start();

    this->engine->addObject(text);

    CETimer timer(10000);
    while(!timer.check()) {
        animation.loop();
        this->engine->loopAndRender();
    }

    this->engine->clear(true);
}

void TelaFinal::setupBackground() {
    CEColorfulBitmap *bitmap = new CEColorfulBitmap();
    bitmap->setBuffer(this->pacifist ? sprite_color_bg_02 : sprite_color_bg_03);
    bitmap->setHeight(240);
    bitmap->setWidth(320);
    bitmap->setColisionEnabled(false);
    bitmap->setHasTransparency(false);
    this->engine->addObject(bitmap);
}
