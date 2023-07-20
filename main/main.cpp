#include "cleytin_engine.h"
#include "jng.h"

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    JNG *game = new JNG();

    game->run(engine);
}

}
