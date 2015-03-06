#include "Precompiled.h"
#include "Core.h"

int main(int argc, char **argv) {
    Core core;
    while (!core.quit) {
        core.UpdateGame();
    }
    return 0;
}