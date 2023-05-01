#include "Bullet.h"


Bullet::Bullet()
{
    x_val = 0;
    y_val = 0;
    is_move_ = false;
    bulletType = BLASTER;
}

Bullet::~Bullet()
{
}

void Bullet::setX(const int &xVal)
{
    x_val = xVal;
}

void Bullet::setY(const int &yVal)
{
    y_val = yVal;
}

int Bullet::getX() const
{
    return x_val;
}

int Bullet::getY() const
{
    return y_val;
}

void Bullet::setMove(const bool&isMove) {
    is_move_ = isMove;
}

bool Bullet::getMove() const {
    return is_move_;
}

void Bullet::setBulletType(const int &type) {
    bulletType = type;
}

int Bullet::getBulletType() const {
    return bulletType;
}

void Bullet::testRegression()
{
    Bullet bullet;
    assert(bullet.getX() == 0);
    assert(bullet.getY() == 0);
    assert(bullet.getMove() == false);
    assert(bullet.getBulletType() == BLASTER);
    // Test setting and getting x and y values
    bullet.setX(50);
    assert(bullet.getX() == 50);
    bullet.setY(100);
    assert(bullet.getY() == 100);
    // Test setting and getting move status
    bullet.setMove(true);
    assert(bullet.getMove() == true);
    bullet.setMove(false);
    assert(bullet.getMove() == false);
    // Test setting and getting bullet type
    bullet.setBulletType(1);
    assert(bullet.getBulletType() == 1);
    bullet.setBulletType(2);
    assert(bullet.getBulletType() == 2);
}
