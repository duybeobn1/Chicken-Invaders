#include "Boss.h"


Boss::Boss()
{

    xVal = 0;
    yVal = 0;
    status.turn_down = 0;
    status.turn_up = 0;
    status.turn_left = 1;
    status.turn_right = 0;
    heart = 0;
}


Boss::~Boss()
{
}

void Boss::setX(const int &x) {
    xVal = x;
}


void Boss::setY(const int &y) {
    yVal = y;
}

int Boss::getX() const {
    return xVal;
}

int Boss::getY() const {
    return yVal;
}

void Boss::setStatus(const StatusChicken &s) {
    status.turn_down = s.turn_down;
    status.turn_up = s.turn_up;
    status.turn_left = s.turn_left;
    status.turn_right = s.turn_right;
}

StatusChicken Boss::getStatus() const {
    return status;
}


void Boss::setHeart(const float &h) {
    heart = h;
}

float Boss::getHeart() const {
    return heart;
}

void Boss::decrease(const float &bullet_damage) {
    heart -= bullet_damage;
}


void Boss::testRegression()
{
    Boss boss;
    assert(boss.getX() == 0);
    assert(boss.getY() == 0);
    assert(boss.getStatus().turn_down == 0);
    assert(boss.getStatus().turn_up == 0);
    assert(boss.getStatus().turn_left == 1);
    assert(boss.getStatus().turn_right == 0);
    assert(boss.getHeart() == 0);

    boss.setX(100);
    assert(boss.getX() == 100);
    boss.setY(50);
    assert(boss.getY() == 50);

    StatusChicken s;
    s.turn_down = 1;
    s.turn_up = 1;
    s.turn_left = 1;
    s.turn_right = 1;

    boss.setStatus(s);
    assert(boss.getStatus().turn_down == 1);
    assert(boss.getStatus().turn_up == 1);
    assert(boss.getStatus().turn_left == 1);
    assert(boss.getStatus().turn_right == 1);


    boss.setHeart(50.0);
    assert(boss.getHeart() == 50.0);
    boss.decrease(10.0);
    assert(boss.getHeart() == 40.0);

}
