#include "Player.h"

Player::Player()
{
    xVal = 0;
    yVal = 0;
    bulletType = BLASTER;
    status = true;
    bulletDamage = 0;
    heart = MAIN_HEART;
}
Player::~Player()
{
}

int Player::getX() const
{
    return xVal;
}

int Player::getY() const
{
    return yVal;
}

void Player::setX(const int &x)
{
    xVal = x;
}

void Player::setY(const int &y)
{
    yVal = y;
}
void Player::setBulletType(const int &type) {
    bulletType = type;
}
int Player::getBulletType() const {
    return bulletType;
}
void Player::setStatus(const bool &s) {
    status = s;
}
int Player::getStatus() const {
    return status;
}

float Player::getBulletDamage() const {
    return bulletDamage;
}
void Player::setBulletDamage(const float &d) {
    bulletDamage = d;
}
void Player::setHeart(const int &h) {
    heart = h;
}
int Player::getHeart() const {
    return heart;
}

void Player::decreaseHeart() {
    heart--;
}


void Player::testRegression()
{
    // Create a player object and check its initial state
    Player player;
    assert(player.getX() == 0);
    assert(player.getY() == 0);
    assert(player.getBulletType() == BLASTER);
    assert(player.getStatus() == true);
    assert(player.getBulletDamage() == 0);
    assert(player.getHeart() == 3);
    // Test setting and getting player position
    player.setX(100);
    player.setY(200);
    assert(player.getX() == 100);
    assert(player.getY() == 200);

    // Test setting and getting player bullet type
    player.setBulletType(NEUTRON);
    assert(player.getBulletType() == NEUTRON);

    // Test setting and getting player status
    player.setStatus(false);
    assert(player.getStatus() == false);

    player.setBulletDamage(2);
    assert(player.getBulletDamage() == 2);
    // Test setting and getting player heart count
    player.setHeart(2);
    assert(player.getHeart() == 2);

    // Test decreasing player heart count
    player.decreaseHeart();
    assert(player.getHeart() == 1);
}