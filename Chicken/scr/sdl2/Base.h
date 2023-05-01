/**
@file Base.h
@brief Contient la définition de la classe de base et d'autres classes héritées telles que Text, GiftSDL, PlayerSDL, BossSDL, ChickenSDL,
ExplodeSDL, BulletSDL, ChickenSDL, GameSDL.
*/
#ifndef BASE_H_
#define BASE_H_
#include "../core/Global.h"
#include "string"
#include "../core/Gift.h"
#include "../core/Bullet.h"
#include "../core/Explode.h"
#include "../core/Chicken.h"
#include "../core/Boss.h"
#include "../core/Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <fstream>
#define NUM_HIGH_SCORES 5
/**

@class Base

@brief La classe Base représente l'objet de base qui peut être utilisé pour les éléments du jeu.

La classe Base charge et affiche des images d'éléments de jeu à l'aide de la bibliothèque SDL.

Il contient des méthodes pour définir la position et les dimensions de l'objet, charger des images,

rendu des images et nettoyage des ressources.
*/
class Base
{
public:
    /**

    @brief Construit un nouvel objet Base.
    */
    Base();
    /**

    @brief Détruit l'objet Base et libère toutes les ressources allouées.
    */
    ~Base();
    /**

    @brief Définit la position et les dimensions du rectangle de l'objet.
     @param x La coordonnée x du coin supérieur gauche du rectangle.
     @param y Coordonnée y du coin supérieur gauche du rectangle.
    */
    void setRect(const int &x, const int &y);
    /**

    @brief Renvoie le rectangle de l'objet.
     @return Le rectangle de l'objet.
    */
    SDL_Rect getRect() const;
    /**

    @brief Charge une image à partir d'un fichier et la définit comme texture de l'objet.
     @param filename Le nom du fichier image à charger.
     @param scr Le SDL_Renderer à utiliser pour charger l'image.
     @return Vrai si l'image a été chargée avec succès, faux sinon.
    */
    bool loadImg(std::string filename, SDL_Renderer *scr);
    /**

    @brief Restitue la texture de l'objet à l'écran.
     @param scr Le SDL_Renderer à utiliser pour le rendu de la texture.
     @param clip Le rectangle sur lequel découper la texture, ou NULL pour aucun découpage.
     */
    void render(SDL_Renderer *scr, const SDL_Rect *clip = NULL);
    /**

    @brief Libère toutes les ressources allouées pour la texture de l'objet.
     */
    void clean();
    /**
    @brief Effectue des tests de régression sur la classe de base.
     */
    void testRegression();

protected:
    SDL_Rect rect;      /**< Le rectangle représentant la position et les dimensions de l'objet. */
    SDL_Texture *objet; /**< La texture représentant l'image de l'objet. */
};

/**
@brief La classe Text représente un objet texte qui hérite de la classe Base, utilisé pour générer du texte dans le jeu
*/
class Text : public Base
{
public:
    /*
     * @brief Construire un nouvel objet Texte.
     *
     */
    Text();
    /**
     * @brief Détruisez l'objet Texte.
     *
     */
    ~Text();

    /**
     * @brief Une énumération des couleurs de texte disponibles.
     *
     */
    enum TEXT_COLOR
    {
        RED = 5,
        WHITE = 6,
        BLACK = 7,
    };

    /**
     * @brief Définit le texte de l'objet Text.
     *
     * @param txt Texte à définir.
     */
    void setText(const std::string &txt);

    /**
     * @brief Définit la couleur de l'objet Texte.
     *
     * @param type La couleur à définir.
     */
    void setColor(const int &type);

    /**
     * @brief Charge et affiche l'objet Text à l'aide d'une police et d'un moteur de rendu.
     *
     * @param font La police à utiliser.
     * @param scr Le moteur de rendu à utiliser.
     */
    void loadShowText(TTF_Font *font, SDL_Renderer *scr);

    /**
     * @brief Exécute un test de régression pour l'objet Texte.
     *
     */
    void testRegression();

private:
    std::string text;    /**< Le texte de l'objet Text. */
    SDL_Color textColor; /**< La couleur de l'objet Texte. */
};

/**

@class GiftSDL
@brief Représente un cadeau dans le jeu, hérité de la classe Base.
La classe GiftSDL gère le rendu, le mouvement et l'affichage d'un cadeau à l'écran.
Le cadeau est représenté par une image chargée à l'aide de la fonction loadImg() de la classe Base.
La classe GiftSDL gère également le découpage de l'image du cadeau à des fins d'animation et stocke les données du cadeau à l'aide de la classe Gift.
*/
class GiftSDL : public Base
{
private:
    SDL_Rect clip[25]; /**< Tableau de SDL_Rectangles pour gérer le découpage de l'image du cadeau. */
    int frame;         /**< L'image actuelle de l'animation du cadeau. */
    Gift *gift;        /**< Un pointeur vers l'objet Gift associé à l'image du cadeau. */
public:
    /**
     * @brief Construit un nouvel objet GiftSDL.
     */
    GiftSDL();
    /**
     * @brief Détruit l'objet GiftSDL.
     */
    ~GiftSDL();

    /**
     * @brief Obtient l'objet Gift associé à l'image du cadeau.
     * @return Un pointeur vers l'objet Gift.
     */
    Gift *getGift() const;

    /**
     * @brief Définit l'objet Gift associé à l'image du cadeau.
     * @param newGift Un pointeur vers l'objet Gift.
     */
    void setGift(Gift *newGift);

    /**
     * @brief Affiche l'image du cadeau à l'écran.
     * @param scr Un pointeur vers l'objet SDL_Renderer utilisé pour le rendu.
     */
    void show(SDL_Renderer *scr);

    /**
     * @brief Déplace l'image du cadeau sur l'écran.
     * @param x_border La bordure de l'écran sur l'axe des x.
     * @param y_border La bordure de l'écran sur l'axe y.
     */
    void move(const int &x_border, const int &y_border);

    /**
     * @brief Charge l'image du cadeau en utilisant la fonction loadImg() de la classe Base.
     * @param scr Un pointeur vers l'objet SDL_Renderer utilisé pour le rendu.
     */
    void loadImgGift(SDL_Renderer *scr);

    /**
     * @brief Définit les rectangles de découpage pour l'image du cadeau à des fins d'animation.
     */
    void setClip();

    /**
     * @brief Obtient le SDL_Rectangle de l'image actuelle de l'animation du cadeau.
     * @return Le SDL_Rectangle de l'image actuelle.
     */
    SDL_Rect getRectFrame();

    /**
     * @brief Exécute le test de régression pour la classe GiftSDL.
     */
    void testRegression();
};

/**

@class ExplodeSDL
@brief Une classe pour gérer l'animation d'explosion d'un poulet dans le jeu.
Cette classe hérite de la classe Base et ajoute des fonctionnalités pour gérer l'animation
de l'explosion lorsqu'un poulet est touché dans le jeu. Il contient une instance de l'Explode
class, un entier pour garder une trace de l'image d'animation actuelle et un tableau de SDL_Rect
objets pour définir la position et la taille de chaque image dans la feuille de sprites.
*/

class ExplodeSDL : public Base
{
private:
    Explode explode;                  /**< Une instance de la classe Explode pour stocker les données d'animation d'explosion */
    int frame;                        /**< L'image actuelle de l'animation d'explosion */
    SDL_Rect clip[NUMBER_OF_CHICKEN]; /**< Un tableau d'objets SDL_Rect pour stocker les coordonnées de chaque image de l'animation d'explosion */
public:
    /**
     * @brief Constructeur pour la classe ExplodeSDL.
     *
     */
    ExplodeSDL();

    /**
     * @brief Destructeur pour la classe ExplodeSDL.
     *
     */
    ~ExplodeSDL();

    /**
     * @brief Définit le clip pour chaque image de l'animation d'explosion.
     *
     */
    void setClip();

    /**
     * @brief Rend l'animation d'explosion à l'écran.
     *
     * @param scr Objet SDL_Renderer sur lequel effectuer le rendu de l'animation.
     */
    void show(SDL_Renderer *scr);

    /**
     * @brief Définit l'image actuelle de l'animation d'explosion.
     *
     * @param Frame Image à définir comme image actuelle.
     */
    void setFrame(const int &Frame);

    /**
     * @brief Obtient l'image actuelle de l'animation d'explosion.
     *
     * @return L'image actuelle de l'animation d'explosion.
     */
    int getFrame() const;

    /**
     * @brief Exécute des tests de régression sur la classe.
     *
     */
    void testRegression();
};
/**

@brief La classe BulletSDL hérite de Base et est responsable de la gestion des objets bullet dans le jeu.
Il contient une instance de la classe Bullet, un booléen pour garder une trace de la puce.
*/
class BulletSDL : public Base
{
    /**
     * @brief Pointeur vers l'objet Bullet associé à l'objet BulletSDL.
     */
    Bullet *bullet;

    /**
     * @brief Booléen indiquant si la balle est en mouvement.
     */
    bool is_move_;

public:
    /**
     * @brief Constructeur pour la classe BulletSDL.
     */
    BulletSDL();
    /**
     * @brief Destructeur pour la classe BulletSDL.
     */
    ~BulletSDL();

    /**
     * @brief Getter pour la variable is_move_.
     * @return Vrai si la balle bouge, faux sinon.
     */
    bool getMove() const { return is_move_; }

    /**
     * @brief Setter pour la variable is_move_.
     * @param s La valeur booléenne à définir pour is_move_.
     */
    void setMove(const bool &s);

    /**
     * @brief Getter pour la variable de puce.
     * @return L'objet Bullet.
     */
    Bullet *getBullet() const;

    /**
     * @brief Setter pour la variable de balle.
     * @param bull L'objet Bullet à définir pour bullet.
     */
    void setBullet(Bullet *bull);

    /**
     * @brief Gère le mouvement et la collision des balles du joueur.
     */
    void handlePlayerBullet();

    /**
     * @brief Gère le mouvement et la collision des balles de poulet.
     */
    void handleChickenBullet();

    /**
     * @brief Gère le mouvement et la collision de la balle du boss.
     * @param xBorbder La limite x pour le patron.
     * @param yBorbder La limite y pour le patron.
     */
    void handleBossBullet(const int &xBorbder, const int &yBorbder);

    /**
     * @brief Charge l'image de puce.
     * @param scr Le SDL_Renderer pour rendre l'image.
     * @param bulletLevel Le niveau de la puce.
     * @param bulletType Le type de puce.
     */
    void loadImgBullet(SDL_Renderer *scr, int bulletLevel, int bulletType);

    /**
     * @brief Exécute un test de régression sur la classe BulletSDL.
     */
    void testRegression();
};

/**

@class ChickenSDL
@brief Une classe pour gérer l'objet Chicken dans l'environnement SDL.
Cette classe fournit des méthodes de gestion de l'objet Chicken dans l'environnement SDL telles que
déplacer le poulet, montrer le poulet à l'écran, initialiser et manipuler les balles,
etc. Il contient également un vecteur d'objets BulletSDL qui sont utilisés pour le tir par le poulet.
*/
class ChickenSDL : public Base
{
private:
    Chicken *chicken;                    /**< Un pointeur vers l'objet Chicken. */
    int frame;                           /**< L'image actuelle de l'animation du poulet. */
    SDL_Rect clip[18];                   /**< Un tableau d'objets SDL_Rect représentant les clips des images d'animation du poulet. */
    std::vector<BulletSDL *> bulletList; /**< Un vecteur de pointeurs BulletSDL représentant les balles du Chicken. */
public:
    /**
     * @brief Constructeur pour la classe ChickenSDL.
     */
    ChickenSDL();
    /**
     * @brief Destructeur pour la classe ChickenSDL.
     */
    ~ChickenSDL();

    /**
     * @brief Renvoie le vecteur des pointeurs BulletSDL représentant les balles du poulet.
     * @return Un vecteur de pointeurs BulletSDL.
     */
    std::vector<BulletSDL *> getBulletList() const;

    /**
     * @brief Supprime une puce du vecteur des pointeurs BulletSDL représentant les puces du poulet.
     * @param idx L'index de la puce à supprimer.
     */
    void removeBullet(const int &idx);

    /**
     * @brief Renvoie un pointeur vers l'objet Chicken.
     * @return Un pointeur vers l'objet Chicken.
     */
    Chicken *getChicken() const;

    /**
     * @brief Définit l'objet Chicken à utiliser par l'objet ChickenSDL.
     * @param chic Un pointeur vers l'objet Chicken.
     */
    void setChicken(Chicken *chic);

    /**
     * @brief Déplace l'objet Poulet.
     * @param chicken Un pointeur vers l'objet Chicken.
     */
    void move(Chicken *chicken);

    /**
     * @brief Rend le poulet à l'écran.
     * @param scr Un pointeur vers l'objet SDL_Renderer représentant l'écran.
     * @param chicken Un pointeur vers l'objet Chicken.
     */
    void show(SDL_Renderer *scr, Chicken *chicken);

    /**
     * @brief Définit les clips des images d'animation du poulet.
     */
    void setClip();

    /**
     * @brief Renvoie l'objet SDL_Rect représentant l'image actuelle de l'animation du poulet.
     * @return Un objet SDL_Rect représentant l'image courante de l'animation du poulet.
     */
    SDL_Rect getRectFrame();

    /**
     * @brief Initialise un objet BulletSDL à utiliser par le Chicken.
     * @param pBullet Un pointeur vers l'objet BulletSDL.
     * @param chicken Un pointeur vers l'objet ChickenSDL.
     * @param scr Un pointeur vers l'objet SDL_Renderer représentant l'écran.
     */
    void initBullet(BulletSDL *pBullet, ChickenSDL *chicken, SDL_Renderer *scr);

    /**
     * @brief Manipule les balles tirées par le Poulet.
     * @param scr Un pointeur vers l'objet SDL_Renderer représentant l'écran.
     * @param chicken Un pointeur vers l'objet Chicken.
     */
    void handleBullet(SDL_Renderer *scr, Chicken *chicken);

    /**
     * @brief Effectue des tests de régression sur la classe ChickenSDL.
     *
     * Cette fonction teste les différentes fonctionnalités de la classe ChickenSDL pour s'assurer qu'elles fonctionnent correctement. Il peut lever une exception si un test échoue.
     */
    void testRegression();
};

/**

@brief La classe BossSDL représente l'interface graphique du Boss dans le jeu.
La classe BossSDL hérite de la classe Base et contient les méthodes nécessaires à l'affichage et à la gestion de l'objet Boss.
Il contient également un vecteur d'objets BulletSDL pour gérer les balles du Boss.
*/
class BossSDL : public Base
{
private:
    Boss *boss;                          /**< Un pointeur vers l'objet Boss. */
    int frame;                           /**< L'image actuelle de l'animation du Boss. */
    SDL_Rect clip[10];                   /**< Un tableau d'objets SDL_Rect représentant les régions de découpage des images d'animation du Boss. */
    std::vector<BulletSDL *> bulletList; /**< Un vecteur d'objets BulletSDL représentant les balles du Boss. */
    bool is_move_;                       /**< Une valeur booléenne indiquant si le Boss est actuellement en mouvement ou non. */
public:
    /**
     * @brief Construisez un nouvel objet BossSDL.
     *
     */
    BossSDL();
    /**
     * @brief Détruisez l'objet BossSDL.
     *
     */
    ~BossSDL();
    /**
     * @brief Obtenez le vecteur des objets BulletSDL représentant les balles du Boss.
     *
     * @return std::vector<BulletSDL*> Le vecteur des objets BulletSDL représentant les balles du Boss.
     */
    std::vector<BulletSDL *> getBulletList() const;

    /**
     * @brief Obtenez un pointeur vers l'objet Boss.
     *
     * @return Boss* Un pointeur vers l'objet Boss.
     */
    Boss *getBoss() const;

    /**
     * @brief Définissez l'objet Boss.
     *
     * @param pBoss Un pointeur vers l'objet Boss à définir.
     */
    void setBoss(Boss *pBoss);

    /**
     * @brief Déplacez l'objet Boss.
     *
     * Cette méthode met à jour la position du Boss en fonction de sa vitesse et de sa direction actuelles.
     */
    void move();

    /**
     * @brief Affichez l'objet Boss à l'écran.
     *
     * Cette méthode affiche l'objet Boss à l'écran.
     *
     * @param scr Un pointeur vers l'objet SDL_Renderer.
     */
    void show(SDL_Renderer *scr);

    /**
     * @brief Définissez les régions de découpage pour les images d'animation du Boss.
     *
     */
    void setClip();

    /**
     * @brief Obtenez l'objet SDL_Rect représentant l'image actuelle de l'animation du Boss.
     *
     * @return SDL_Rect L'objet SDL_Rect représentant l'image courante de l'animation du Boss.
     */
    SDL_Rect getRectFrame();

    /**
     * @brief Initialisez un objet BulletSDL pour le Boss.
     *
     * @param p_bullet Un pointeur vers l'objet BulletSDL à initialiser.
     * @param scr Un pointeur vers l'objet SDL_Renderer.
     * @param boss Un pointeur vers l'objet BossSDL.
     */
    void initBullet(BulletSDL *p_bullet, SDL_Renderer *scr, BossSDL *boss);

    /**
     * @brief Créez une nouvelle puce pour le Boss et ajoutez-la au vecteur bulletList.
     *
     * @param scr Un pointeur vers l'objet SDL_Renderer.
     * @param boss Un pointeur vers l'objet Boss.
     */
    void makeBullet(SDL_Renderer *scr, Boss *boss);
    /**
     * @brief Affiche le cœur du boss à l'écran à la position et à la taille données.
     *
     * @param scr Le moteur de rendu à utiliser pour le rendu du cœur.
     * @param x La coordonnée x du coin supérieur gauche de la boîte englobante du cœur.
     * @param y Coordonnée y du coin supérieur gauche de la boîte englobante du cœur.
     * @param w La largeur de la boîte englobante du cœur.
     * @param h La hauteur de la boîte englobante du cœur.
     */
    void showHeartBoss(SDL_Renderer *scr, int x, int y, int w, int h);

    /**
     * @brief Effectue des tests de régression sur la classe BossSDL.
     *
     * Cette fonction teste les différentes fonctionnalités de la classe BossSDL pour s'assurer qu'elles fonctionnent correctement. Il peut lever une exception si un test échoue.
     */
    void testRegression();
};

/**

@brief La classe PlayerSDL, dérivée de la classe Base, représente l'objet Player dans l'implémentation SDL.
*/
class PlayerSDL : public Base
{
private:
    Player *player;                      /**< Un pointeur vers l'objet Player. */
    std::vector<BulletSDL *> bulletList; /**< Un vecteur de pointeurs vers des objets BulletSDL représentant les balles du joueur. */
public:
    /**
     * @brief Construisez un nouvel objet PlayerSDL.
     *
     */
    PlayerSDL();
    /**
     * @brief Détruisez l'objet PlayerSDL.
     *
     */
    ~PlayerSDL();
    /**
     * @brief Supprimer une puce de la liste des puces.
     *
     * @param idx L'index de la puce à supprimer.
     */
    void removeBullet(const int &idx);

    /**
     * @brief Obtenez la liste à puces du joueur.
     *
     * @return std::vector<BulletSDL *> Le vecteur des pointeurs vers les objets BulletSDL.
     */
    std::vector<BulletSDL *> getBulletList() const;
    /**
     * @brief Obtenez l'objet Player.
     *
     * @return Player* Un pointeur vers l'objet Player.
     */
    Player *getPlayer() const;

    /**
     * @brief Définissez l'objet Player.
     *
     * @param p Un pointeur vers l'objet Player.
     */
    void setPlayer(Player *p);
    /**
     * @brief Gère les entrées de l'utilisateur et contrôle les mouvements et les tirs de balles du joueur.
     *
     * @param event L'objet événement contenant des informations sur l'entrée utilisateur.
     * @param scr Le SDL_Renderer utilisé pour rendre le jeu.
     * @param bulletSound Un tableau de pointeurs Mix_Chunk représentant les différents sons de tir de balle.
     * @param bulletLevel Le niveau actuel des balles du joueur.
     * @param gSoundLevelUp L'effet sonore joué lorsque le niveau de balle du joueur augmente.
     * @param player L'objet Player contrôlé.
     */
    void control(SDL_Event event, SDL_Renderer *scr, Mix_Chunk *bulletSound[4], int bulletLevel, Mix_Chunk *gSoundLevelUp, Player *player);

    /**
     * @brief Déplace le vaisseau du joueur.
     *
     * @param player L'objet Player déplacé.
     */
    void move(Player *player);

    /**
     * @brief Rend le vaisseau du joueur.
     *
     * @param scr Le SDL_Renderer utilisé pour rendre le jeu.
     * @param player L'objet Player en cours de rendu.
     */
    void show(SDL_Renderer *scr, Player *player);

    /**
     * @brief Gère la logique pour tirer les balles du joueur.
     *
     * @param scr Le SDL_Renderer utilisé pour rendre le jeu.
     * @param player L'objet PlayerSDL tirant les balles.
     */
    void handleBullet(SDL_Renderer *scr, PlayerSDL *player);

    /**
     * @brief Exécute un test de régression pour la classe PlayerSDL.
     */
    void testRegression();
};

/**

@brief Classe pour contrôler la logique du jeu et le rendu à l'aide de la bibliothèque SDL.
*/

class GameSDL : public Base
{
private:
    int highScores[NUM_HIGH_SCORES];          ///< Tableau des meilleurs scores
    bool isRunning;                           ///< Drapeau indiquant si le jeu est en cours d'exécution
    int bullet_level;                         ///< Le niveau de la balle du joueur
    int kill;                                 ///< Nombre de poulets tués par le joueur
    float scrolling;                          ///< La vitesse de défilement du fond
    int time_end_game;                        ///< L'heure à laquelle le jeu se termine
    int count_num_exp;                        ///< Le nombre d'explosions
    int menu_number;                          ///< Le nombre d'éléments de menu
    std::vector<ChickenSDL *> p_chicken_list; ///< Liste des poulets
    SDL_Window *gWindow;                      ///< La fenêtre de jeu
    SDL_Renderer *gRenderer;                  ///< Le moteur de rendu du jeu
    SDL_Event gEvent;                         ///< L'événement du jeu
    Mix_Chunk *gSoundBullet[3];               ///< Tableau de sons de balles
    Mix_Chunk *gSoundExp[3];                  ///< Gamme de sons d'explosion
    Mix_Chunk *gSoundChickenHit[3];           ///< Tableau de sons de frappe de poulet
    Mix_Chunk *gSoundLevelUp;                 ///< Son joué lorsque le joueur monte de niveau
    Mix_Music *gMusicStart;                   ///< Musique jouée au début du jeu
    TTF_Font *gFontText;                      ///< Police utilisée pour le texte
    TTF_Font *gFontMenu;                      ///< Police utilisée pour les éléments de menu
    TTF_Font *gFontEndGame;                   ///< Police utilisée pour le texte de fin de partie
    Base *background;                         ///< Le fond du jeu
    Text *kill_text;                          ///< Le texte affichant le nombre de victimes
    Base *support;                            ///< Le support du jeu
    Text *heart_text;                         ///< Le texte affichant le nombre de coeurs
    Text *lighting_text;                      ///< Le texte affichant le nombre d'allumages
    Text *hint;                               ///< Le texte de l'indice
    Text *end_game;                           ///< Le texte de fin de partie
    PlayerSDL *spaceship;                     ///< Le vaisseau spatial du joueur
    ExplodeSDL *exp;                          ///< L'explosion
    ExplodeSDL *exp_boss;                     ///< L'explosion pour le boss
    GiftSDL *gift;                            ///< L'objet cadeau
    BossSDL *boss;                            ///< L'objet patron
public:
    /**
     * @brief Construire un nouvel objet GameSDL
     *
     */
    GameSDL();
    /**
     * @brief Détruire l'objet GameSDL
     *
     */
    ~GameSDL();

    /**
     * @brief Obtenir l'état de fonctionnement du jeu
     *
     * @return true si le jeu est en cours d'exécution, false sinon
     */
    bool getRunning() const;

    /**
     * @briefInitialiser la fenêtre de jeu, le moteur de rendu et les polices
     *
     * @param title Le titre de la fenêtre de jeu
     */
    void init(std::string title);

    /**
     * @brief Nettoyez les ressources du jeu et quittez SDL
     *
     */
    void clean();

    /**
     * @brief Afficher le menu du jeu et gérer les entrées de l'utilisateur
     *
     * @param item L'élément de menu sélectionné par l'utilisateur
     */
    void menu(const std::string &item);
    /**

    @brief Vérifie si deux SDL_Rectangles se croisent.
     @param objet1 Le premier SDL_Rectangle à vérifier.
     @param objet2 Le deuxième SDL_Rectangle à vérifier.
     @return true si les deux SDL_Rectangles se croisent, false sinon.
     */
    bool checkCollision(const SDL_Rect &objet1, const SDL_Rect &objet2);
    /**

    @brief Vérifie si un point entre en collision avec un SDL_Rectangle.
     @param x La coordonnée x du point.
     @param y La coordonnée y du point.
     @param rect Le SDL_Rectangle à vérifier.
     @return true si le point entre en collision avec le SDL_Rectangle, false sinon.
     */
    bool check_mouse_vs_item(const int &x, const int &y, const SDL_Rect &rect);
    /**
     @brief Définit les meilleurs scores pour le jeu.
     */
    void setHighScore();
    /**
    @brief Exécute des tests de régression sur la classe GameSDL.
     */
    void testRegression();
};

#endif