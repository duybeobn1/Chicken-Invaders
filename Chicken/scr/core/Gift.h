/**
@file Gift.h
@brief Le fichier d'en-tête de Gift
*/
#ifndef GIFT_H_
#define GIFT_H_
#include "Global.h"
#define GIFT_WIDTH 49
#define GIFT_HEIGHT 58
#define WIDTH_LEVEL_UP 49
#define HEIGHT_LEVEL_UP 41
#define GIFT_SPEED 2
/**
 * @brief Classe représentant un cadeau dans le jeu.
 */
class Gift
{
private:
    int xVal;      /*!< La coordonnée x de la position du cadeau. */
    int yVal;      /*!< La coordonnée y de la position du cadeau. */
    int giftType;  /*!< Le type de cadeau. */
    bool comeBack; /*!< Indique si le cadeau revient actuellement à sa position de départ. */
public:
    /**
     * @brief Constructeur par défaut pour un objet Gift.
     */
    Gift();

    /**
     * @brief Destructeur d'un objet Gift.
     */
    ~Gift();

    /**
     * @brief Définissez la coordonnée x de la position du cadeau.
     * @param x La nouvelle coordonnée x.
     */
    void setX(const int &x);

    /**
     * @brief Définissez la coordonnée y de la position du cadeau.
     * @param y La nouvelle coordonnée y.
     */
    void setY(const int &y);

    /**
     * @brief Obtenez la coordonnée x actuelle de la position du cadeau.
     * @return La coordonnée x actuelle.
     */
    int getX() const;

    /**
     * @brief Obtenez la coordonnée y actuelle de la position du cadeau.
     * @return La coordonnée y actuelle.
     */
    int getY() const;

    /**
     * @brief Définissez le type de cadeau.
     * @param type Le nouveau type de cadeau.
     */
    void setGiftType(const int &type);

    /**
     * @brief Obtenez le type de cadeau.
     * @return Le type de cadeau actuel.
     */
    int getGiftType() const;

    /**
     * @brief Définissez si le cadeau revient actuellement à sa position de départ.
     * @param retour Vrai si le cadeau recule, faux sinon.
     */
    void setComeBack(const bool &back);

    /**
     * @brief Détermine si le cadeau revient actuellement à sa position de départ.
     * @return Vrai si le cadeau recule, faux sinon.
     */
    bool getComeBack() const;

    /**
     * @briefChoisissez un type de cadeau au hasard parmi les options disponibles.
     * @return Un entier représentant le type de cadeau sélectionné au hasard.
     */
    int randomGift() const;

    /**
     * @brief Effectuez un test de régression sur la classe Gift.
     *
     * Cette méthode teste la classe Gift en définissant ses attributs et en vérifiant que les valeurs sont correctement renvoyées par les getters de la classe.
     */
    void testRegression();
};

#endif