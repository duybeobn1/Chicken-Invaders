/**
@file Global.h
@brief Contains the variable of the width, height, the bullets number, gift, experience, number of chicken, damage, ...
*/
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <vector>
#include <string.h>
#include <math.h>
#include <cassert>
#include <iostream>
using namespace std;
const int BACKGROUND_WIDTH = 1200; /*!< Background width valeur */
const int BACKGROUND_HEIGHT = 3840;  /*!<  Background height valeur */
const int SCREEN_WIDTH = 1200;  /*!<  screen width valeur */
const int SCREEN_HEIGHT = 760;  /*!<  screen height valeur */
const float SCREEN_SPEED = 0.3;    /*!<  screen scroll vitesse valeur */

const int COLOR_KEY_R = 170;    /*!<  couleur cle pour rouge */
const int COLOR_KEY_G = 170;/*!<  couleur cle pour vert */
const int COLOR_KEY_B = 170;/*!<  couleur cle pour bleu */
const int RENDER_DRAW_COLOR = 255;/*!<  render couleur variable */

const int NUMBER_OF_CHICKEN = 36;/*!<  nombres de poulets dans jeu */
const int ONE_TURN_GIFT = 14;/*!<  gift valeur  */
const int NUMBER_OF_EXP = 3; /*!<  experience valeur */
const int BOSS_HEART = 3;/*!<  coeur de boss */
const int DISTANCE_BETWEEN_CHICKENS = 100;/*!<  distance entre des poulets */
const int NUMBER_OF_CHICKEN_PER_ROW = 12;/*!<  nombres de poulet chaque row */
const float BULLET_DAMAGE_LEVEL_UP = 0.5;/*!<  damage de tire lorsque level up */
const int BLASTER = 0 ; /*!<  tire blaster */
const int NEUTRON = 1; /*!<  tire neutron */
const int BORON = 2 ; /*!< tire boron */
const int LEVEL_UP = 3; /*!<  tire maximum level */

/**

@brief Structure représentant l'état du mouvement d'un objet Chicken ou Boss
*/
struct StatusChicken
{
int turn_left; /**< Variable for turning left. */
int turn_right; /**< Variable for turning right. */
int turn_up; /**< Variable for moving up. */
int turn_down; /**< Variable for moving down. */
};

#endif