#include <iostream>
#include <ctime>
#include <unistd.h>
#include "GameTXT.h"
using namespace std;

int main()
{
    GameTXT game;
    srand(time(0));
    game.GameLoop();
    return 0;
}
