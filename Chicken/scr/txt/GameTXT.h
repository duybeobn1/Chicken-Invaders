/**
@file GameTXT.h
@brief Fichier d'en-tête pour la classe GameTXT, qui fournit un jeu textuel simple.
Ce fichier d'en-tête contient les déclarations de la classe GameTXT, qui fournit une simple
jeu basé sur du texte où le joueur peut se déplacer de gauche à droite et tirer des balles pour tuer des poulets
se déplaçant sur l'écran.
*/

#ifndef GAMETXT_H_
#define GAMETXT_H_

#include <iostream>
#include <ctime>
#include <unistd.h>
using namespace std;

const int BOARD_WIDTH = 40;            /**< Largeur du plateau de jeu */
const int BOARD_HEIGHT = 20;           /**< Hauteur du plateau de jeu */
const int PLAYER_Y = BOARD_HEIGHT - 1; /**< Coordonnée Y du joueur */
const int NUM_CHICKENS = 10;           /**< Nombre de poulets dans le jeu */
const int NUM_BULLETS = 3;             /**< Nombre de balles que le joueur peut tirer */

/**

@class GameTXT
@brief Un jeu textuel simple où le joueur peut se déplacer de gauche à droite et tirer des balles pour tuer des poulets.
La classe GameTXT fournit un jeu textuel simple où le joueur peut se déplacer de gauche à droite et tirer des balles
pour tuer les poulets se déplaçant à travers l'écran.
*/
class GameTXT
{

private:
    char board[BOARD_HEIGHT][BOARD_WIDTH]; /**< Le plateau de jeu */
    int playerX;                           /**< La coordonnée X du joueur */
    int score;                             /**< Le score du joueur */
    int chickenX[NUM_CHICKENS];            /**< La coordonnée X de chaque poulet */
    int chickenY[NUM_CHICKENS];            /**< La coordonnée Y de chaque poulet */
    bool chickenAlive[NUM_CHICKENS];       /**< Si chaque poulet est vivant ou non */
    int bulletX[NUM_BULLETS];              /**< La coordonnée X de chaque puce */
    int bulletY[NUM_BULLETS];              /**< La coordonnée Y de chaque puce */
    bool bulletAlive[NUM_BULLETS];         /**< Si chaque balle est vivante ou non */

public:
    /**
     * @brief Constructeur pour la classe GameTXT.
     *
     * Initialise le plateau de jeu, le joueur, les poulets, les balles et le score.
     *
     */
    GameTXT();

    /**
     * @brief Destructeur pour la classe GameTXT.
     *
     */
    ~GameTXT();

    /**
     * @brief Imprime le plateau de jeu sur la console.
     *
     * Boucle à travers le tableau de bord et imprime chaque caractère sur la console, avec une nouvelle ligne
     * après chaque ligne.
     *
     */
    void PrintBoard();

    /**
     * @brief Gère la saisie de l'utilisateur.
     *
     * Interroge le clavier pour l'entrée et met à jour la position du joueur ou tire une balle en conséquence.
     *
     */
    void HandleInput();

    /**
     * @brief Met à jour le plateau de jeu.
     *
     * Déplace les poulets sur le plateau, déplace les balles sur le plateau et vérifie
     * collisions entre poulets et balles ou entre poulets et le joueur.
     *
     */
    void UpdateBoard();

    /**
     * @brief Initialise le jeu.
     *
     * Appelle le constructeur, configure le plateau de jeu et affiche l'état initial du jeu.
     *
     */
    void InitGame();

    /**
     * @brief Exécute la boucle du jeu.
     *
     * Appelle HandleInput(), UpdateBoard() et PrintBoard() en boucle jusqu'à ce que le lecteur quitte ou
     * perd la partie.
     *
     */
    void GameLoop();
};

#endif