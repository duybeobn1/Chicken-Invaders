#include "Chicken.h"

Chicken::Chicken()
{

    xVal = 0;
    yVal = 0;
    status.turn_down = 0;
    status.turn_up = 0;
    status.turn_left = 0;
    status.turn_right = 1;
    heart = 0;
    comeBack = true;
}

Chicken::~Chicken() {}

void Chicken::setX(const int &x)
{
    xVal = x;
}
void Chicken::setY(const int &y)
{
    yVal = y;
}
int Chicken::getX() const
{
    return xVal;
}
int Chicken::getY() const
{
    return yVal;
}

void Chicken::setHeart(const float &Heart)
{
    heart = Heart;
}
float Chicken::getHeart() const
{
    return heart;
}
void Chicken::decrease(const float &bulletDamage)
{
    heart -= bulletDamage;
}

void Chicken::setComeBack(const bool &back)
{
    comeBack = back;
}
bool Chicken::getComeBack() const
{
    return comeBack;
}

void Chicken::setStatusRight()
{
    status.turn_down = 0;
    status.turn_up = 0;
    status.turn_left = 0;
    status.turn_right = 1;
}
void Chicken::setStatus(const StatusChicken &s)
{
    status.turn_down = s.turn_down;
    status.turn_up = s.turn_up;
    status.turn_left = s.turn_left;
    status.turn_right = s.turn_right;
}

StatusChicken Chicken::getStatus() const
{
    return status;
}
void Chicken::testRegression()
{
    Chicken chicken;
    assert(chicken.getX() == 0);
    assert(chicken.getY() == 0);
    assert(chicken.getHeart() == 0);
    assert(chicken.getComeBack() == true);
    assert(chicken.getStatus().turn_down == 0);
    assert(chicken.getStatus().turn_up == 0);
    assert(chicken.getStatus().turn_left == 0);
    assert(chicken.getStatus().turn_right == 1);
    // Test setter and getter functions
    chicken.setX(10);
    chicken.setY(20);
    assert(chicken.getX() == 10);
    assert(chicken.getY() == 20);
    //
    chicken.setHeart(5.0);
    assert(chicken.getHeart() == 5);
    //
    chicken.decrease(2.3);
    assert(chicken.getHeart() == float(2.7));

    //
    chicken.setComeBack(false);
    assert(chicken.getComeBack() == false);
    //
    StatusChicken s;
    s.turn_down = 1;
    s.turn_up = 1;
    s.turn_left = 1;
    s.turn_right = 1;
    
    chicken.setStatus(s);
    assert(chicken.getStatus().turn_down == 1);
    assert(chicken.getStatus().turn_up == 1);
    assert(chicken.getStatus().turn_left == 1);
    assert(chicken.getStatus().turn_right == 1);
}