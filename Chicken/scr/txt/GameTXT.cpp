#include "GameTXT.h"

GameTXT::GameTXT()
{
}
GameTXT::~GameTXT()
{
}

void GameTXT::PrintBoard()
{
    system("clear"); /// Vide la console

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }

    cout << "Score: " << score << endl;
}

void GameTXT::HandleInput()
{
/// simule les appuis sur les touches fléchées gauche et droite
    if (rand() % 2 == 0 && playerX > 0)
    {
        playerX--;
    }
    if (rand() % 2 == 0 && playerX < BOARD_WIDTH - 1)
    {
        playerX++;
    }

/// simule l'appui sur la touche de la barre d'espace
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        if (!bulletAlive[i] && rand() % 10 == 0)
        {
            bulletX[i] = playerX;
            bulletY[i] = PLAYER_Y - 1;
            bulletAlive[i] = true;
            break; 
        }
    }
}


void GameTXT::UpdateBoard()
{
    /// Vider le tableau
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = ' ';
        }
    }

    /// Dessine le vaisseau spatial du joueur
    board[PLAYER_Y][playerX] = '^';

    // Dessine le poulet
    for (int i = 0; i < NUM_CHICKENS; i++)
    {
        if (chickenAlive[i])
        {
            board[chickenY[i]][chickenX[i]] = '@';
        }
    }

    /// Dessine les balles
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        if (bulletAlive[i])
        {
            board[bulletY[i]][bulletX[i]] = '|';
        }
    }
}

void GameTXT::InitGame()
{
    /// Initialise la carte
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = ' ';
        }
    }

    //// Initialise le spaceship
    playerX = BOARD_WIDTH / 2;

    // Initialize the chickens
    for (int i = 0; i < NUM_CHICKENS; i++)
    {
        chickenX[i] = rand() % BOARD_WIDTH;
        chickenY[i] = rand() % (BOARD_HEIGHT / 2);
        chickenAlive[i] = true;
    }

    /// Initialise les balles
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        bulletAlive[i] = false;
    }

    /// Initialise le score
    score = 0;
}


void GameTXT::GameLoop()
{
    /// Initialise le jeu
    InitGame();

    /// Lancer la boucle du jeu
    while (true)
    {
        /// Gérer l'entrée
        HandleInput();

        /// Mettre à jour le tableau
        UpdateBoard();

        /// Imprimer le tableau
        PrintBoard();

        /// Vérifier les collisions entre les balles et les poulets
        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (bulletAlive[i])
            {
                for (int j = 0; j < NUM_CHICKENS; j++)
                {
                    if (chickenAlive[j] && bulletX[i] == chickenX[j] && bulletY[i] == chickenY[j])
                    {
                        /// Une balle a touché un poulet
                        bulletAlive[i] = false;
                        chickenAlive[j] = false;
                        score++;
                    }
                }
            }
        }

        /// Déplacez les poulets vers le bas
        for (int i = 0; i < NUM_CHICKENS; i++)
        {
            if (chickenAlive[i])
            {
                chickenY[i]++;
                if (chickenY[i] >= BOARD_HEIGHT)
                {
                	int posX = chickenX[i];
                    chickenAlive[i] = false;
                    chickenX[i] = posX;
                    chickenY[i] = BOARD_HEIGHT / 2 - 5;
                    chickenAlive[i] = true;
                }
                if (chickenY[i] == PLAYER_Y && chickenX[i] == playerX)
                {
                    chickenAlive[i] = false;
                    cout << "Game over" << endl;
                    return;
                }
            }
        }
        

        // Déplacez les poulets vers le haute
        for (int i = 0; i < NUM_BULLETS; i++)
        {
            if (bulletAlive[i])
            {
                bulletY[i]--;
                if (bulletY[i] < 0)
                {
                    /// Une balle atteint le haut de l'écran
                    bulletAlive[i] = false;
                }
            }
        }

        /// Faire apparaître de nouveaux poulets
         for (int i = 0; i < NUM_CHICKENS; i++)
         {
             if (!chickenAlive[i])
             {
                 chickenX[i] = rand() % BOARD_WIDTH;
                 chickenY[i] = rand() % (BOARD_HEIGHT / 2);
                 chickenAlive[i] = true;
             }
         }

        /// Veille un court moment pour ralentir le jeu
        usleep(100000);
    }
}
