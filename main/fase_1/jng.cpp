#include "jng.h"

void JNG::run(CleytinEngine *engine) {
    MainShip *mainShip = new MainShip();
    CleytinControls *controls = new CleytinControls();

    controls->init();
    mainShip->setControls(controls);
    engine->addObject(mainShip);

    while(1) { // Essa 'fase' do game nunca termina
        engine->loop();
        engine->render();
    }
}
