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
    this->creditos1();
    this->creditos2();
    this->creditos3();

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

void TelaFinal::creditos1() {
    CERectangle *rect = new CERectangle();
    rect->setBaseColor({0, 0, 0});
    rect->setHeight(240);
    rect->setWidth(320);
    rect->setPos(0, 0);
    rect->setFilled(true);
    this->engine->addObject(rect);

    this->generateText("Artes de sprites (Open Game Art)", 20, 10, 1);
    this->generateText("FunwithPixels", 40, 30, 2);
    this->generateText("Irmandito", 40, 60, 2);
    this->generateText("Deepfold", 40, 90, 2);
    this->generateText("Buch", 40, 120, 2);
    this->generateText("Sogomn", 40, 150, 2);
    this->generateText("arin48", 40, 180, 2);
    this->generateText("Jerom", 40, 210, 2);

    CETimer timer(5000);
    while(!timer.check()) {
        this->engine->loopAndRender();
    }

    this->engine->clear(true);
}


void TelaFinal::creditos2() {
    CERectangle *rect = new CERectangle();
    rect->setBaseColor({0, 0, 0});
    rect->setHeight(240);
    rect->setWidth(320);
    rect->setPos(0, 0);
    rect->setFilled(true);
    this->engine->addObject(rect);

    this->generateText("Desenvolvido pelo", 20, 60, 2);
    this->generateText("Matheus", 60, 110, 3);

    CETimer timer(3000);
    while(!timer.check()) {
        this->engine->loopAndRender();
    }

    this->engine->clear(true);
}

void TelaFinal::creditos3() {
    CERectangle *rect = new CERectangle();
    rect->setBaseColor({0, 0, 0});
    rect->setHeight(240);
    rect->setWidth(320);
    rect->setPos(0, 0);
    rect->setFilled(true);
    this->engine->addObject(rect);

    this->generateText("Obrigado por Jogar!", 10, 90, 2);

    CETimer timer(5000);
    while(!timer.check()) {
        this->engine->loopAndRender();
    }

    this->engine->clear(true);
}


void TelaFinal::generateText(const char* text, int x, int y, uint8_t size) {
    CEText *textObj = new CEText();
    textObj->setText(text);
    textObj->setBaseColor({255, 255, 255});
    textObj->setPos(x, y);
    textObj->setPriority(2);
    textObj->setSizeMultiplier(size);
    this->engine->addObject(textObj);
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
