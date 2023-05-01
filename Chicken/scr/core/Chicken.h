/**
@file Chicken.h
@brief Le fichier d'en-tête Chicken
*/
#ifndef CHICKEN_H_
#define CHICKEN_H_

#include <vector>
#include "Global.h"
#include "Bullet.h"
#include "Explode.h"
/**

@brief La largeur du sprite de poulet.
Cette constante représente la largeur du sprite poulet dans le jeu. Il est utilisé pour définir la taille initiale du poulet et pour la détection de collision.
*/
#define WIDTH_CHICKEN 75
/**

@brief La hauteur du sprite de poulet.
Cette constante représente la hauteur du sprite poulet dans le jeu. Il est utilisé pour définir la taille initiale du poulet et pour la détection de collision.
*/
#define HEIGHT_CHICKEN 68
/**

@brief La vitesse de déplacement du poulet.
Cette constante représente la vitesse de déplacement du poulet dans le jeu. Il est utilisé pour mettre à jour la position du poulet à chaque image.
*/
#define CHICKEN_SPEED 1
/**

@brief La vitesse de déplacement des balles du poulet.
Cette constante représente la vitesse de déplacement des balles du poulet dans le jeu. Il est utilisé pour mettre à jour la position des balles du poulet à chaque image.
*/
#define CHICKEN_BULLET_SPEED 1
/**

@brief Le nombre de cœurs que possède le poulet.
Cette constante représente le nombre de cœurs que le poulet a dans le jeu. Lorsque le cœur du poulet atteint zéro, le poulet meurt.
*/
#define CHICKEN_HEART 2
/**

@class Chicken
@brief Représente le personnage de poulet dans le jeu.
La classe Poulet contient des informations sur la position, l'état et la santé du poulet. Il fournit également des méthodes pour mettre à jour la position et la santé du poulet, ainsi que pour définir son statut.
*/
class Chicken
{
private:
    float heart;          /* !< Les coeurs restants du poulet */
    int xVal;             /*!< L'abscisse du poulet */
    int yVal;             /*!< Coordonnée y du poulet */
    StatusChicken status; /*!< Statut actuel du poulet */
    bool comeBack;        /*!< Indique si le poulet revient actuellement à sa position de départ */
public:
    /**
     * @brief Constructeur pour la classe Chicken.
      *
      * Ce constructeur initialise la position et la santé du poulet.
      */
    Chicken();
    /**
     * @brief Destructeur pour la classe Chicken.
     */
    ~Chicken();
    /**
     * @brief Définissez la coordonnée x du poulet.
      * @param x La nouvelle coordonnée x pour le poulet.
      */
    void setX(const int &x);
    /**
     * @brief Définissez la coordonnée y du poulet.
      * @param y La nouvelle coordonnée y pour le poulet.
      */
    void setY(const int &y);
    /**
     * @brief Obtenez la coordonnée x du poulet.
      * @return La coordonnée x actuelle du poulet.
      */
    int getX() const;
    /**
     * @brief Obtenez la coordonnée y du poulet.
      * @return La coordonnée y actuelle du poulet.
      */
    int getY() const;
    /**
     * @brief Déposer les cœurs restants du poulet.
      * @param Heart Le nouveau nombre de cœurs pour le poulet.
      */
    void setHeart(const float &Heart);
    /**
     * @brief Obtenez les cœurs restants du poulet.
      * @return Le nombre actuel de cœurs que possède le poulet.
      */
    float getHeart() const;
    /**
     * @brief Diminuez les cœurs restants du poulet d'un montant donné.
      * @param bulletDamage La quantité de dégâts causés au poulet par la balle.
      */
    void decrease(const float &bulletDamage);
    /**
     * @brief Définissez si le poulet revient actuellement à sa position de départ.
      * @param comeback Vrai si le poulet recule, faux sinon.
      */
    void setComeBack(const bool &comeback);
    /**
     * @brief Déterminez si le poulet revient actuellement à sa position de départ.
      * @return Vrai si le poulet recule, faux sinon.
      */
    bool getComeBack() const;
    /**
     * @brief Définissez le statut du poulet sur "face à droite".
      *
      * Cette méthode est appelée lorsque le poulet change de direction pour faire face à droite.
      */
    void setStatusRight();
    /**
     * @brief Obtenez le statut actuel du poulet.
      * @return L'état actuel du poulet.
      */
    StatusChicken getStatus() const;
    /**
     * @brief Définissez l'état actuel du poulet.
      * @param s Le nouveau statut du poulet.
      */
    void setStatus(const StatusChicken &s);
    /**
     * @brief Effectuez un test de régression sur la classe Poulet.
      *
      * Cette méthode teste la classe Chicken en définissant ses attributs et en vérifiant que les valeurs sont correctement renvoyées par les getters de la classe.
      */
    void testRegression();
};

#endif