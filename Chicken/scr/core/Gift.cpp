#include "Gift.h"

Gift::Gift()
{
    giftType = 0;
    comeBack = false;
}
Gift::~Gift()
{
}
void Gift::setX(const int &x) {
    xVal = x;
}
void Gift::setY(const int &y) {
    yVal = y;
}
int Gift::getX() const {
     return xVal; 
}
int Gift::getY() const {
     return yVal; 
}

void Gift::setGiftType(const int &type){
    giftType = type;
}

int Gift::getGiftType() const { 
    return giftType;
}
void Gift::setComeBack(const bool &back){
    comeBack = back;
}
bool Gift::getComeBack() const {
    return comeBack;
}
int Gift::randomGift() const
{
    int randGiftType = rand() % 25;
    randGiftType = randGiftType < 3 ? randGiftType : 3;
    return randGiftType;
}
void Gift::testRegression()
{
    // create a new gift object
    Gift gift;
    assert(gift.getGiftType() == 0);
    assert(gift.getComeBack() == false);
    // test getX() and getY() methods
    gift.setX(100);
    gift.setY(200);
    assert(gift.getX() == 100);
    assert(gift.getY() == 200);
    // test setGiftType() and getGiftType() methods
    gift.setGiftType(2);
    assert(gift.getGiftType() == 2);
    // test setComeBack() and getComeBack() methods
    gift.setComeBack(true);
    assert(gift.getComeBack() == true);
    // test randomGift() method
    int randGiftType = gift.randomGift();
    assert(randGiftType >= 0 && randGiftType <= 3);
}