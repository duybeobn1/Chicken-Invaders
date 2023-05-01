/**
@file Player.h
@brief Le fichier d'en-tête de la classe Player.
*/
#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "Global.h"
#include "Bullet.h"

#define WIDTH_MAIN 70
#define HEIGHT_MAIN 57
#define MAIN_SPEED 6
#define MAIN_HEART 3

/**

@class Player
@brief La classe qui représente le joueur dans le jeu.
La classe Player contient des informations sur la position du joueur,
liste de balles, type de balle, statut, cœur et dégâts de balle.
*/
class Player
{
private:
    std::vector<Bullet *> bulletList; /**< La liste des balles tirées par le joueur. */
    int xVal;                         /**< La coordonnée X du joueur. */
    int yVal;                         /**< La coordonnée Y du joueur. */
    int bulletType;                   /**< Le type de balle utilisé par le joueur. */
    bool status;                      /**< Le statut du joueur, vrai s'il est vivant, faux s'il est mort. */
    int heart;                        /**< Le nombre de cœurs qu'il reste au joueur. */
    float bulletDamage;               /**< La quantité de dégâts infligés par les balles du joueur. */
public:
    /**

    @brief Enumération des vitesses pour différents types de balles.
    */
    enum BULLET_SPEED
    {
        BLASTER_SPEED = 12, /**< Vitesse de balle du blaster. */
        NEUTRON_SPEED = 18, /**< Vitesse de balle du neutron. */
        BORON_SPEED = 30    /**< Vitesse de balle du boron. */
    };
    /**
     * @brief Construit un nouvel objet Player.
     */
    Player();
    /**
     * @brief Détruit l'objet Player.
     */
    ~Player();

    /**
     * @brief Obtient la coordonnée X du joueur.
     * @return Un entier représentant la coordonnée X du joueur.
     */
    int getX() const;

    /**
     * @brief Obtient la coordonnée Y du joueur.
     * @return Un entier représentant la coordonnée Y du joueur.
     */
    int getY() const;

    /**
     * @brief Définit la coordonnée X du joueur.
     * @param x La nouvelle coordonnée X du joueur.
     */
    void setX(const int &x);

    /**
     * @brief Définit la coordonnée Y du joueur.
     * @param y La nouvelle coordonnée Y du joueur.
     */
    void setY(const int &y);

    /**
     * @brief Définit les dégâts de balle du joueur.
     * @param d Les nouveaux dégâts de balle du joueur.
     */
    void setBulletDamage(const float &d);

    /**
     * @brief Obtient la liste des balles tirées par le joueur.
     * @return Un vecteur de pointeurs vers des objets Bullet.
     */
    std::vector<Bullet *> getBulletList() { return bulletList; }

    /**
     * @brief Définit la liste des balles tirées par le joueur.
     * @param bullet_list Un vecteur de pointeurs vers des objets Bullet.
     */
    void setBulletList(std::vector<Bullet *> bullet_list) { bulletList = bullet_list; }

    /**
     * @brief Définit le type de balle utilisé par le joueur.
     * @param bullet_type Le type de balle utilisé par le joueur.
     */
    void setBulletType(const int &bullet_type);

    /**
     * @brief Obtient le type de balle utilisé par le joueur.
     * @return Un entier représentant le type de balle utilisé par le joueur.
     */
    int getBulletType() const;

    /**
     * @brief Définit le statut du lecteur.
     * @param Status Le nouveau statut du joueur.
     */
    void setStatus(const bool &Status);

    /**
     * @brief Obtient le statut du joueur.
     * @return Un entier représentant le statut du joueur.
     */
    int getStatus() const;

    /**
     * @brief Obtient les dégâts de balle du joueur.
     * @return Un flotteur représentant les dégâts de balle du joueur.
     */
    float getBulletDamage() const;

    /**
     * @brief Définit le nombre de cœurs qu'il reste au joueur.
     * @param Heart Le nouveau nombre de cœurs qu'il reste au joueur.
     */
    void setHeart(const int &Heart);
    /**
     * @brief Obtenez le cœur du joueur.
     * @return dans le coeur du joueur
     */
    int getHeart() const;
    /**
     *@brief Diminuez le cœur du joueur de 1.
     */
    void decreaseHeart();
    /**
     *@brief Une fonction pour tester la régression de la classe.
     */
    void testRegression();
};

#endif