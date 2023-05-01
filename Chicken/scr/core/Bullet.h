/**
@file Bullet.h
@brief Le fichier d'en-tête Bullet
*/
#ifndef BULLET_H_
#define BULLET_H_
#include "Global.h"
#include "string"
/**
@class Bullet
@brief Représente la variable bullet dans le jeu.
La classe Bullet contient des informations sur la position de la puce, son type et son statut. Il fournit également des méthodes pour mettre à jour la position de la puce, son type ainsi que pour définir son statut.
*/
class Bullet
{
private:
    int x_val;
    int y_val;
    bool is_move_;
    int bulletType;
public:
/**
* @brief si l'objet Bullet est dans le cache, il sera utilisé. autrement, un nouvel objet Bullet sera créé
* @param creer objet Bullet
*/
    Bullet();
    /**
* @brief Detruit l'objet bullet
* @param Detruit objet Bullet
*/
    ~Bullet();
/**
* @brief Définit la coordonnée x bullet, qui est utilisée pour définir la position de bullet
* @param xVal La nouvelle coordonnée x de la balle en pixels
*/
    void setX(const int &xVal);
    /**
* @brief Définit la coordonnée y bullet, qui est utilisée pour définir la position de bullet
* @param yVal La nouvelle coordonnée x de la balle en pixels
*/
    void setY(const int &yVal);
    /**
* @brief Il obtient la coordonnée x de bullet.
* @return La coordonnée x de bullet 
*/
    int getX() const;
/**
* @brief Il obtient la coordonnée y de bullet.
* @return La coordonnée y de bullet 
*/
    int getY() const;
    /**
* @brief Définit la existant de bullet
* @param isMove la nouvelle booléen variable pour definir si bullet est encore en jeu
*/
    void setMove(const bool &isMove);
    /**
* @brief Il obtient la variable is_move_.
* @return variable is_move_ de Bullet
*/
    bool getMove() const;
    /**
* @brief Définit le type de bullet 
* @param Le type de balle 0 - 3 pour Player
*/
    void setBulletType(const int &type);
    /**
* @brief Retourne le type bullet.
* @return type de bullet
*/
    int getBulletType()const;
    /**
* @brief Tests de régression des méthodes de mise en place de Bullet.
*/
    void testRegression();


};
#endif