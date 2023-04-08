#include <box2d/box2d.h>
#include "Game.h"


int main()
{
    Game game(b2Vec2(0, 10));
    
	game.Initialize();

	while (game.IsRunning())
	{
		game.ProcessGameLoop();
	}
}