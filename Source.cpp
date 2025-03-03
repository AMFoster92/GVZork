#include <iostream>
#include "Game.h"

int main()
{
	Game gvzork = Game();

	while (gvzork.getPlayGame())
	{
		gvzork.play({});
	}

	return 0;
}