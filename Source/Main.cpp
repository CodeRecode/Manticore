#include "Precompiled.h"
#include "Core.h"

int main(int argc, char **argv) {
    Core core;
	core.StartGame();
    while (!core.quit) 
	{
        core.UpdateGame();
	}
	core.EndGame();
    return 0;
}