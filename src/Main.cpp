#include "GameEngine.hpp"

int main()
{
    GameEngine game("assets/assets.txt", "assets/levelconfig.txt");
    game.run();

    return 0;
}