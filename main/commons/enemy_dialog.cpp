#include "enemy_dialog.h"

EnemyDialog::EnemyDialog() {
    this->engine = NULL;
    this->timer = new CETimer(ENEMY_DIALOG_TIME);
    this->animation = new CETextRevealAnimation();
}

EnemyDialog::~EnemyDialog() {
    delete this->timer;
    delete this->animation;
}

void EnemyDialog::setup(CleytinEngine *engine) {
    this->setText("Você não precisa fazer isso\nPra você somos inimigos,\nmas para muitos somos esperança");
    this->setColisionEnabled(false);
    this->setBaseColor({255, 255, 255});
    this->setPos(50, 140);
    this->setPriority(10);
    this->engine = engine;
    this->timer->reset();

    this->animation->setObject(this);
    this->animation->setDuration(6000);
    this->animation->start();
}

void EnemyDialog::loop(CleytinEngine *engine) {
    if(this->timer->check()) {
        this->engine->markToDelete(this);
        return;
    }
    this->animation->loop();
}
