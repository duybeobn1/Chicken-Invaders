#include "Base.h"

int main(int argc, char *argv[])
{
    cout << "Test SDL Classes" << endl;
    Base base;
    base.testRegression();
    Text text;
    text.testRegression();
    GiftSDL gift;
    gift.testRegression();
    BulletSDL bullet;
    bullet.testRegression();
    ExplodeSDL explode;
    explode.testRegression();
    ChickenSDL chicken;
    chicken.testRegression();
    BossSDL boss;
    boss.testRegression();
    PlayerSDL player;
    player.testRegression();
    cout << "Test passed" << endl;
    return 0;
}