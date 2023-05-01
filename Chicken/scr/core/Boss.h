
/**
@file Boss.h
@brief Fichier d'en-tête de la classe Boss
*/
#ifndef BOSS_H_
#define BOSS_H_

#include <vector>
#include "Global.h"
#include "Bullet.h"
#include "Explode.h"

#define WIDTH_BOSS 200       /**< La largeur du boss */
#define HEIGHT_BOSS 117      /**< La hauteur du boss */
#define BOSS_SPEED 1         /**< La vitesse du boss */
#define BOSS_BULLET_SPEED 13 /**< La vitesse des balles du boss */
/**
@class Boss
@brief Représente le personnage du boss dans le jeu
La classe Boss contient des informations sur la position, le statut et la santé du boss. Il fournit également des méthodes pour mettre à jour la position et la santé du boss, ainsi que pour définir son statut.
*/
class Boss
{
public:
    /**
     * @brief Constructeur par défaut pour la classe Boss
     */
    Boss();
    /**
     * @brief Destructeur pour la classe Boss
     */
    ~Boss();

    /**
     * @brief  Définit la coordonnée x du boss
     * @param x La coordonnée x à définir
     */
    void setX(const int &x);
    /**
     * @brief Définit la coordonnée y du bossage
      * @param y La coordonnée y à définir
     */
    void setY(const int &y);
    /**
     * @brief Il obtient la valeur x de boss.
     * @return La valeur x du boss 
     */
    int getX() const;
    /**
     * @brief Obtient la valeur y de boss.
     * @return La y valeur de boss 
     */
    int getY() const;
    /**
     * @brief Définit le statut du boss. Ceci est appelé par StatusChicken
     * @param s le statut à définir
     */
    StatusChicken getStatus() const;
    /**
     * @brief Obtien le status de boss
     * @return le statut de boss comme une constante afin que vous puissiez l'utiliser comme une fonction à vos propres fins
     */
    void setStatus(const StatusChicken &s);
    /**
     * @brief Il met le coeur du boss.
     * @param h Le cœur du boss en float
     */
    void setHeart(const float &h);
    /**
     * @brief Obtien le coeur du boss.
     * @return  le coeur du boss en float
     */
    float getHeart() const;
    /**
     * @brief Réduit le cœur du boss par bullet damage de Player
     * @param bullet_damage Montant des dommages à diminuer
     */
    void decrease(const float &bullet_damage);

    /**
     * @brief Teste de régression des propriétés du boss.
     */
    void testRegression();

private:
    float heart;          /*!< coeur du boss */
    int xVal;             /*!< position X du boss */
    int yVal;             /*!< position Y du boss */
    StatusChicken status; /*!< status du boss */
};

#endif
