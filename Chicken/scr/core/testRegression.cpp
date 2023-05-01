#include "Boss.h"
#include "Boss.h"
#include "Bullet.h"
#include "Chicken.h"
#include "Explode.h"
#include "Gift.h"
#include "Player.h"

int main() {
    Boss boss;
    Bullet bullet;
    Chicken chicken;
    Explode explode;
    Gift gift;
    Player player;
    cout << "Test core classes" << endl;
    boss.testRegression();
    bullet.testRegression();
    chicken.testRegression();
    gift.testRegression();
    player.testRegression();
    cout << "Test passed" << endl;
    return 0;
}