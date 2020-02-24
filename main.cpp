#include "header/Game.h"
#include <cstdio>

int main() {
    Game game;
    if(game.initialize()) {
        game.runLoop();
    }
    game.shutdown();
    return 0;
}
