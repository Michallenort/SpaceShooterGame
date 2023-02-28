#define _CRTDBG_MAP_ALLOC

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Textbox.h"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Game* game = new Game();
    game->run();
    delete game;
    
    return 0;
}

