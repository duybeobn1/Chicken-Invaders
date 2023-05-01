#include "Base.h"
Base::Base()
{
    objet = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

Base::~Base()
{
    clean();
}

void Base::setRect(const int &x, const int &y)
{
    rect.x = x;
    rect.y = y;
}

SDL_Rect Base::getRect() const
{
    return rect;
}

bool Base::loadImg(std::string filename, SDL_Renderer *scr)
{
    clean();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadSurface = IMG_Load(filename.c_str());

    if (loadSurface)
    {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(scr, loadSurface);
        if (newTexture)
        {
            rect.w = loadSurface->w;
            rect.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    objet = newTexture;
    return objet != NULL;
}

void Base::render(SDL_Renderer *scr, const SDL_Rect *clip)
{
    SDL_Rect renderTemp = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(scr, objet, clip, &renderTemp);
}
void Base::clean()
{
    if (objet != NULL)
    {
        SDL_DestroyTexture(objet);
        objet = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}

void Base::testRegression()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    bool result = loadImg("data//image//menu2.png", renderer);
    if (!result)
    {
        fprintf(stderr, "Failed to load image! SDL_Error: %s\n", IMG_GetError());
        exit(1);
    }

    setRect(100, 100);
    SDL_Rect r = getRect();
    assert(r.x == 100 && r.y == 100);

    SDL_RenderClear(renderer);
    render(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Text::Text()
{
    rect.x = 0;
    rect.y = 0;
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
};

Text::~Text() {}

void Text::setColor(const int &type)
{
    switch (type)
    {
    case RED:
        textColor = {255, 0, 0};
        break;
    case WHITE:
        textColor = {255, 255, 255};
        break;
    case BLACK:
        textColor = {0, 0, 0};
        break;
    }
}

void Text::setText(const std::string &txt)
{
    text = txt;
}
void Text::loadShowText(TTF_Font *font, SDL_Renderer *scr)
{
    clean();
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface)
    {
        objet = SDL_CreateTextureFromSurface(scr, textSurface);
        if (objet)
        {
            rect.w = textSurface->w;
            rect.h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    render(scr, nullptr);
}

void Text::testRegression()
{
    SDL_Window *window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("data//font//font1.ttf", 24);
    assert(font == NULL);

    setText("Hello World!");
    setColor(Text::RED);
    assert(loadImg("data//image//background.png", renderer));
    loadShowText(font, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

GiftSDL::GiftSDL() : gift()
{
    frame = 0;
}
GiftSDL::~GiftSDL() {}

Gift *GiftSDL::getGift() const
{
    return gift;
}
void GiftSDL::setGift(Gift *newGift)
{
    gift = newGift;
}
void GiftSDL::show(SDL_Renderer *scr)
{
    if (gift->getGiftType() == 3)
    {
        if (gift->getComeBack())
        {
            frame++;
            if (frame / 3 >= 25)
            {
                frame = 0;
            }
            SDL_Rect renderTemp = {rect.x, rect.y, WIDTH_LEVEL_UP, HEIGHT_LEVEL_UP};
            SDL_RenderCopy(scr, objet, &clip[frame / 3], &renderTemp);
        }
    }
    else if (gift->getGiftType() < 3)
    {
        if (gift->getComeBack())
        {
            render(scr, nullptr);
        }
    }
}

void GiftSDL::move(const int &x_border, const int &y_border)
{
    if (gift->getComeBack())
    {
        rect.y += gift->getY();
        if (rect.y > y_border)
        {
            gift->setComeBack(false);
            rect.x = -GIFT_WIDTH;
            rect.y = -GIFT_HEIGHT;
        }
    }
}

void GiftSDL::loadImgGift(SDL_Renderer *scr)
{

    if (gift->getGiftType() == BLASTER)
    {
        loadImg("data//image//gift1.png", scr);
    }
    else if (gift->getGiftType() == NEUTRON)
    {
        loadImg("data//image//gift2.png", scr);
    }
    else if (gift->getGiftType() == BORON)
    {
        loadImg("data//image//gift3.png", scr);
    }
    else if (gift->getGiftType() == LEVEL_UP)
    {
        loadImg("data//image//level_up_1225.png", scr);
    }
}

void GiftSDL::setClip()
{
    for (int i = 0; i < 25; i++)
    {
        clip[i].x = i * WIDTH_LEVEL_UP;
        clip[i].y = 0;
        clip[i].w = WIDTH_LEVEL_UP;
        clip[i].h = HEIGHT_LEVEL_UP;
    }
}

SDL_Rect GiftSDL::getRectFrame()
{
    SDL_Rect rectTemp;
    rectTemp.x = rect.x;
    rectTemp.y = rect.y;
    rectTemp.w = WIDTH_LEVEL_UP;
    rectTemp.h = HEIGHT_LEVEL_UP;
    return rectTemp;
}
void GiftSDL::testRegression()
{
    GiftSDL *gift = new GiftSDL();
    Gift *newGift = new Gift();
    gift->setGift(newGift);
    SDL_Window *window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);
    gift->loadImgGift(renderer);
    assert(objet == NULL);
    SDL_Rect tempRect = getRectFrame();
    assert(tempRect.x == rect.x && tempRect.y == rect.y && tempRect.w == WIDTH_LEVEL_UP && tempRect.h == HEIGHT_LEVEL_UP);
    SDL_DestroyRenderer(renderer);
}

ExplodeSDL::ExplodeSDL()
{
    Explode explode;
    frame = 16;
}

ExplodeSDL::~ExplodeSDL()
{
}

void ExplodeSDL::setClip()
{
    for (int i = 0; i < frame; i++)
    {
        clip[i].x = i * WIDTH_FRAME_EXP;
        clip[i].y = 0;
        clip[i].w = WIDTH_FRAME_EXP;
        clip[i].h = HEIGHT_FRAME_EXP;
    }
}
void ExplodeSDL::testRegression()
{
    // Create an SDL_Window and SDL_Renderer for testing
    SDL_Window *window = SDL_CreateWindow("ExplodeSDL Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Test loading the explosion image
    loadImg("data//image//exp.png", renderer);
    assert(objet != NULL);
    // Test setting the clip rectangles
    setClip();
    assert(clip[0].x == 0 && clip[0].y == 0 && clip[0].w == WIDTH_FRAME_EXP && clip[0].h == HEIGHT_FRAME_EXP && "Failed to set clip rectangles");
    // Test showing the explosion animation
    show(renderer);
    assert(frame == 17);
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void ExplodeSDL::show(SDL_Renderer *scr)
{
    frame++;
    SDL_Rect renderTemp = {rect.x, rect.y, WIDTH_FRAME_EXP, HEIGHT_FRAME_EXP};
    SDL_RenderCopy(scr, objet, &clip[frame / 2], &renderTemp);
}

void ExplodeSDL::setFrame(const int &newFrame)
{
    frame = newFrame;
}
int ExplodeSDL::getFrame() const
{
    return frame;
}
BulletSDL::BulletSDL() : bullet()
{
    is_move_ = false;
}
BulletSDL::~BulletSDL() {}

void BulletSDL::setMove(const bool &s)
{
    is_move_ = s;
}
void BulletSDL::loadImgBullet(SDL_Renderer *scr, int bulletLevel, int bulletType)
{
    Bullet *bullet = new Bullet();
    if (bulletType == BLASTER)
    {
        std::string blaster = "data//image//blaster" + std::to_string(bulletLevel) + ".png";
        if (!loadImg(blaster, scr))
        {
            std::cerr << "Error loading image " << blaster << std::endl;
            return;
        }
    }
    if (bulletType == NEUTRON)
    {
        std::string neutron = "data//image//neutron" + std::to_string(bulletLevel) + ".png";
        if (!loadImg(neutron, scr))
        {
            std::cerr << "Error loading image " << neutron << std::endl;
            return;
        }
    }
    if (bulletType == BORON)
    {
        std::string boron = "data//image//boron" + std::to_string(bulletLevel) + ".png";
        if (!loadImg(boron, scr))
        {
            std::cerr << "Error loading image " << boron << std::endl;
            return;
        }
    }
    delete bullet;
}

void BulletSDL::handlePlayerBullet()
{
    rect.y += bullet->getY();
    if (rect.y < -rect.h)
    {
        is_move_ = false;
    }
}

void BulletSDL::handleChickenBullet()
{
    int y_val = bullet->getY();
    rect.y += y_val;
    if (rect.y > SCREEN_HEIGHT)
    {
        is_move_ = false;
    }
}
void BulletSDL::handleBossBullet(const int &xBorder, const int &yBorder)
{
    int y_val = bullet->getY();
    rect.y += y_val;
    if (rect.y > xBorder)
    {
        is_move_ = false;
    }
}
Bullet *BulletSDL::getBullet() const
{
    return bullet;
}

void BulletSDL::setBullet(Bullet *bull)
{
    bullet = bull;
}
void BulletSDL::testRegression()
{
    // Test loading bullet image
    SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);
    loadImgBullet(renderer, 1, 0);
    assert(objet != NULL);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Test handling player bullet movement
    Bullet playerBullet;
    playerBullet.setY(-10);
    bullet = &playerBullet;
    rect.y = 50;
    handlePlayerBullet();
    assert(rect.y == 40);
    playerBullet.setY(0);
    handlePlayerBullet();
    assert(rect.y == 40);
    playerBullet.setY(20);
    handlePlayerBullet();
    assert(rect.y == 60);
    // Test handling chicken bullet movement
    Bullet chickenBullet;
    chickenBullet.setY(10);
    bullet = &chickenBullet;
    rect.y = SCREEN_HEIGHT - 50;
    handleChickenBullet();
    assert(rect.y == SCREEN_HEIGHT - 40);
    chickenBullet.setY(0);
    handleChickenBullet();
    assert(rect.y == SCREEN_HEIGHT - 40);
    chickenBullet.setY(20);
    handleChickenBullet();
    assert(rect.y == SCREEN_HEIGHT - 20);
    // Test handling boss bullet movement
    Bullet bossBullet;
    bossBullet.setY(10);
    bullet = &bossBullet;
    rect.y = SCREEN_HEIGHT;
    handleBossBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(rect.y == SCREEN_HEIGHT + 10);
    bossBullet.setY(0);
    handleBossBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(rect.y == SCREEN_HEIGHT + 10);
    bossBullet.setY(20);
    handleBossBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(rect.y == SCREEN_HEIGHT + 30);
}

ChickenSDL::ChickenSDL() : chicken()
{
    rect.x = SCREEN_WIDTH;
    rect.y = SCREEN_HEIGHT;
    frame = 0;
}

ChickenSDL::~ChickenSDL() {}

SDL_Rect ChickenSDL::getRectFrame()
{
    SDL_Rect rectTemp;
    rectTemp.x = rect.x;
    rectTemp.y = rect.y;
    rectTemp.w = WIDTH_CHICKEN;
    rectTemp.h = HEIGHT_CHICKEN;
    return rectTemp;
}
void ChickenSDL::setClip()
{
    for (int i = 0; i < 18; i++)
    {
        clip[i].x = i * WIDTH_CHICKEN;
        clip[i].y = i * 0;
        clip[i].w = WIDTH_CHICKEN;
        clip[i].h = HEIGHT_CHICKEN;
    }
}

std::vector<BulletSDL *> ChickenSDL::getBulletList() const
{
    return bulletList;
}
Chicken *ChickenSDL::getChicken() const
{
    return chicken;
}
void ChickenSDL::setChicken(Chicken *ch)
{
    chicken = ch;
}
void ChickenSDL::show(SDL_Renderer *scr, Chicken *chicken)
{
    bool comeBack = chicken->getComeBack();
    if (comeBack)
    {
        frame++;
        if (frame / 5 >= 18)
        {
            frame = 0;
        }
        SDL_Rect renderTemp = {rect.x, rect.y, WIDTH_CHICKEN, HEIGHT_CHICKEN};
        SDL_RenderCopy(scr, objet, &clip[frame / 5], &renderTemp);
    }
}
void ChickenSDL::handleBullet(SDL_Renderer *scr, Chicken *chicken)
{
    for (int i = 0; i < (int)bulletList.size(); i++)
    {
        BulletSDL *pBullet = bulletList.at(i);
        if (pBullet)
        {
            if (pBullet->getMove())
            {
                pBullet->render(scr, nullptr);
                pBullet->handleChickenBullet();
            }
            else
            {
                pBullet->setRect(this->rect.x + WIDTH_CHICKEN / 2 - pBullet->getRect().w / 2, this->rect.y + HEIGHT_CHICKEN);
                pBullet->setMove(true);
            }
        }
    }
}

void ChickenSDL::initBullet(BulletSDL *pBullet, ChickenSDL *chicken, SDL_Renderer *scr)
{
    if (pBullet)
    {
        if (pBullet->loadImg("data//image//egg.png", scr))
        {
            Bullet *bullet = new Bullet();
            bullet->setY(CHICKEN_BULLET_SPEED);
            pBullet->setBullet(bullet);
            pBullet->setMove(true);
            pBullet->setRect(this->rect.x + WIDTH_CHICKEN / 2 - pBullet->getRect().w / 2, this->rect.y + HEIGHT_CHICKEN);
            bulletList.push_back(pBullet);
        }
    }
}
void ChickenSDL::move(Chicken *chicken)
{
    bool comeBack = chicken->getComeBack();
    int xVal = chicken->getX();
    int yVal = chicken->getY();
    StatusChicken status = chicken->getStatus();
    if (comeBack)
    {
        rect.y += yVal;
        if (status.turn_left)
        {
            rect.x -= xVal;
        }
        if (status.turn_right)
        {
            rect.x += xVal;
        }
        if (status.turn_up)
        {
            rect.y -= 2 * yVal;
        }
        if (rect.y > SCREEN_HEIGHT)
        {
            status.turn_up = 1;
            status.turn_down = 0;
            chicken->setStatus(status);
        }
        else if (rect.y + HEIGHT_CHICKEN < 0)
        {
            status.turn_down = 1;
            status.turn_up = 0;
            chicken->setStatus(status);
        }
        if (rect.x + WIDTH_CHICKEN * 3 <= 0)
        {
            status.turn_right = 1;
            status.turn_left = 0;
            chicken->setStatus(status);
        }
        else if (rect.x >= SCREEN_WIDTH + 3 * WIDTH_CHICKEN)
        {
            status.turn_left = 1;
            status.turn_right = 0;
            chicken->setStatus(status);
        }
    }
}

void ChickenSDL::removeBullet(const int &idx)
{
    if (idx >= 0 && idx < (int)bulletList.size())
    {
        BulletSDL *pBullet = bulletList.at(idx);
        bulletList.erase(bulletList.begin() + idx);
        if (pBullet)
        {
            delete pBullet;
            pBullet = NULL;
        }
    }
}
void ChickenSDL::testRegression()
{
    ChickenSDL chickenSDL;
    assert(chickenSDL.getBulletList().empty());
    Chicken* chicken = new Chicken();
    chickenSDL.setChicken(chicken);
    chickenSDL.setClip();
    SDL_Rect clip0 = {0, 0, WIDTH_CHICKEN, HEIGHT_CHICKEN};
    assert(memcmp(&chickenSDL.clip[0], &clip0, sizeof(clip0)) == 0);

    chicken->setComeBack(true);
    int initX = chickenSDL.rect.x;
    int initY = chickenSDL.rect.y;
    chickenSDL.move(chicken);
    assert(chickenSDL.rect.x == initX - chicken->getX() && chickenSDL.rect.y == initY + chicken->getY());

    BulletSDL *pBullet = new BulletSDL();
    SDL_Renderer *renderer = nullptr; // mock renderer
    chickenSDL.initBullet(pBullet, &chickenSDL, renderer);
    assert(chickenSDL.getBulletList().size() == 0);

    pBullet->setMove(true);
    int bulletY = pBullet->getRect().y;
    chickenSDL.handleBullet(renderer, chicken);
    assert(pBullet->getRect().y == bulletY);

    chickenSDL.removeBullet(0);
    assert((int)chickenSDL.getBulletList().size() == 0);
    delete chicken;
}
BossSDL::BossSDL() : boss()
{
    frame = 0;
    rect.x = SCREEN_WIDTH;
    rect.y = SCREEN_HEIGHT / 2;
}

BossSDL::~BossSDL()
{
}
std::vector<BulletSDL *> BossSDL::getBulletList() const
{
    return bulletList;
}
SDL_Rect BossSDL::getRectFrame()
{
    SDL_Rect rectTemp;
    rectTemp.x = rect.x;
    rectTemp.y = rect.y;
    rectTemp.w = WIDTH_BOSS;
    rectTemp.h = HEIGHT_BOSS;
    return rectTemp;
}

void BossSDL::setClip()
{
    for (int i = 0; i < 10; i++)
    {
        clip[i].x = i * WIDTH_BOSS;
        clip[i].y = 0;
        clip[i].w = WIDTH_BOSS;
        clip[i].h = HEIGHT_BOSS;
    }
}

void BossSDL::show(SDL_Renderer *screen)
{
    frame++;
    if (frame / 5 >= 10)
    {
        frame = 0;
    }
    SDL_Rect renderTemp = {rect.x, rect.y, WIDTH_BOSS, HEIGHT_BOSS};
    SDL_RenderCopy(screen, objet, &clip[frame / 5], &renderTemp);
}

void BossSDL::makeBullet(SDL_Renderer *scr, Boss *boss)
{
    for (int i = 0; i < (int)bulletList.size(); i++)
    {
        BulletSDL *p_bullet = bulletList.at(i);
        if (p_bullet)
        {
            if (p_bullet->getMove())
            {
                p_bullet->render(scr, nullptr);
                p_bullet->handleBossBullet(SCREEN_WIDTH, SCREEN_HEIGHT + this->rect.y);
            }
            else
            {
                p_bullet->setRect(this->rect.x + WIDTH_BOSS / 2 - p_bullet->getRect().w / 2, this->rect.y + HEIGHT_BOSS);
                p_bullet->setMove(true);
            }
        }
    }
}

void BossSDL::setBoss(Boss *pBoss)
{
    boss = pBoss;
}

Boss *BossSDL::getBoss() const
{
    return boss;
}
void BossSDL::initBullet(BulletSDL *pBullet, SDL_Renderer *scr, BossSDL *boss)
{
    if (pBullet != NULL)
    {
        if (pBullet->loadImg("data//image//egg_boss.png", scr))
        {
            Bullet *bullet = new Bullet();
            bullet->setMove(true);
            bullet->setY(BOSS_BULLET_SPEED);
            pBullet->setBullet(bullet);
            pBullet->setRect(this->rect.x + WIDTH_BOSS / 2 - pBullet->getRect().w / 2, this->rect.y + HEIGHT_BOSS);
            bulletList.push_back(pBullet);
            ;
        }
    }
}
void BossSDL::move()
{
    int xVal = boss->getX();
    int yVal = boss->getY();
    StatusChicken status = boss->getStatus();
    rect.y += yVal;
    if (status.turn_left)
    {
        rect.x -= xVal;
    }
    if (status.turn_right)
    {
        rect.x += xVal;
    }
    if (status.turn_up)
    {
        rect.y -= 2 * yVal;
    }

    if (rect.y > SCREEN_HEIGHT - HEIGHT_BOSS)
    {
        status.turn_up = 1;
        status.turn_down = 0;
        boss->setStatus(status);
    }
    else if (rect.y < 0)
    {
        status.turn_down = 1;
        status.turn_up = 0;
        boss->setStatus(status);
    }
    if (rect.x <= 0)
    {
        status.turn_right = 1;
        status.turn_left = 0;
        boss->setStatus(status);
    }
    else if (rect.x >= SCREEN_WIDTH - WIDTH_BOSS)
    {
        status.turn_left = 1;
        status.turn_right = 0;
        boss->setStatus(status);
    }
}
void BossSDL::showHeartBoss(SDL_Renderer *scr, int x, int y, int w, int h)
{
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(scr, 255, 0, 0, 255);
    SDL_RenderFillRect(scr, &fillRect);
}
void BossSDL::testRegression()
{
        // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }

    // Create SDL window and renderer
    SDL_Window *window = SDL_CreateWindow("BossSDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    BossSDL bossSDL;

    std::vector<BulletSDL *> bulletList = bossSDL.getBulletList();
    assert(bulletList.empty());

    SDL_Rect rect = bossSDL.getRectFrame();
    assert(rect.x == 1200 && rect.y == 380);

    bossSDL.setClip();
    for (int i = 0; i < 10; i++) {
        assert(bossSDL.clip[i].x == i * WIDTH_BOSS);
    }

    bossSDL.show(renderer);

    BulletSDL *bulletSDL = new BulletSDL();
    Boss* newBoss = new Boss();
    bossSDL.setBoss(newBoss);
    bossSDL.initBullet(bulletSDL, renderer, &bossSDL);
    bulletList = bossSDL.getBulletList();
    assert(!bulletList.empty());

    bossSDL.move();
    rect = bossSDL.getRectFrame();
    assert(rect.x >= 0 && rect.x == SCREEN_WIDTH);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

PlayerSDL::PlayerSDL() : player()
{
    rect.x = SCREEN_WIDTH / 2;
    rect.y = SCREEN_HEIGHT - HEIGHT_MAIN;
    rect.w = WIDTH_MAIN;
    rect.h = HEIGHT_MAIN;
}
PlayerSDL::~PlayerSDL()
{
}

void PlayerSDL::control(SDL_Event event, SDL_Renderer *scr, Mix_Chunk *bulletSound[4], int bulletLevel, Mix_Chunk *gSoundLevelUp, Player *player)
{
    int xVal = player->getX();
    int yVal = player->getY();
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            yVal -= MAIN_SPEED;
            player->setY(yVal);
            break;
        case SDLK_s:
            yVal += MAIN_SPEED;
            player->setY(yVal);
            break;
        case SDLK_d:
            xVal += MAIN_SPEED;
            player->setX(xVal);
            break;
        case SDLK_a:
            xVal -= MAIN_SPEED;
            player->setX(xVal);
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            yVal += MAIN_SPEED;
            player->setY(yVal);
            break;
        case SDLK_s:
            yVal -= MAIN_SPEED;
            player->setY(yVal);
            break;
        case SDLK_d:
            xVal -= MAIN_SPEED;
            player->setX(xVal);
            break;
        case SDLK_a:
            xVal += MAIN_SPEED;
            player->setX(xVal);
            break;
        }
    }
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            if (player->getStatus() == true)
            {
                BulletSDL *bullet = new BulletSDL();
                Bullet *bul = new Bullet();
                bul->setBulletType(player->getBulletType());
                bullet->setBullet(bul);
                if (player->getBulletType() == BLASTER)
                {
                    Mix_PlayChannel(-1, bulletSound[0], 0);
                    bul->setY(-(player->BLASTER_SPEED));
                    bullet->setBullet(bul);
                    player->setBulletDamage(1);
                }
                else if (player->getBulletType() == NEUTRON)
                {
                    Mix_PlayChannel(-1, bulletSound[1], 0);
                    bul->setY(-(player->NEUTRON_SPEED));
                    bullet->setBullet(bul);
                    player->setBulletDamage(2);
                }
                else if (player->getBulletType() == BORON)
                {
                    Mix_PlayChannel(-1, bulletSound[2], 0);
                    bul->setY(-(player->BORON_SPEED));
                    bullet->setBullet(bul);
                    player->setBulletDamage(1.5);
                }
                bullet->loadImgBullet(scr, bulletLevel, bullet->getBullet()->getBulletType());
                bullet->setRect(this->rect.x + this->rect.w / 2 - bullet->getRect().w / 2, this->rect.y - bullet->getRect().h);
                bullet->setMove(true);
                bulletList.push_back(bullet);
            }
        }
        if (event.key.keysym.sym == SDLK_RETURN)
        {
            if (player->getHeart() > 0)
            {
                if (player->getStatus() == false)
                {
                    Mix_PlayChannel(-1, gSoundLevelUp, 0);
                    player->setStatus(true);
                    rect.x = SCREEN_WIDTH / 2;
                    rect.y = SCREEN_HEIGHT - HEIGHT_MAIN;
                }
            }
        }
    }
}

void PlayerSDL::show(SDL_Renderer *scr, Player *player)
{
    if (player->getStatus())
    {
        render(scr, nullptr);
    }
}
void PlayerSDL::move(Player *player)
{
    if (player->getStatus())
    {
        rect.x += player->getX();
        if (rect.x < 0 || rect.x + WIDTH_MAIN > SCREEN_WIDTH)
        {
            rect.x -= player->getX();
        }
        rect.y += player->getY();
        if (rect.y < 0 || rect.y + HEIGHT_MAIN > SCREEN_HEIGHT)
        {
            rect.y -= player->getY();
        }
    }
}

void PlayerSDL::handleBullet(SDL_Renderer *scr, PlayerSDL *player)
{
    for (int i = 0; i < (int)bulletList.size(); i++)
    {
        BulletSDL *p_bullet = bulletList.at(i);
        if (p_bullet)
        {
            if (p_bullet->getMove())
            {
                p_bullet->render(scr, nullptr);
                p_bullet->handlePlayerBullet();
            }
            else
            {
                if (p_bullet)
                {
                    bulletList.erase(bulletList.begin() + i);
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}
void PlayerSDL::removeBullet(const int &idx)
{
    for (int i = 0; i < (int)bulletList.size(); i++)
    {
        if (idx < (int)bulletList.size())
        {
            BulletSDL *p_bullet = bulletList.at(idx);
            bulletList.erase(bulletList.begin() + idx);

            if (p_bullet)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
    }
}

std::vector<BulletSDL *> PlayerSDL::getBulletList() const
{
    return bulletList;
}

Player *PlayerSDL::getPlayer() const
{
    return player;
}

void PlayerSDL::setPlayer(Player *p) { player = p; }

void PlayerSDL::testRegression()
{
    // Test constructor
    PlayerSDL *playerSDL = new PlayerSDL();
    assert(playerSDL->rect.x == SCREEN_WIDTH / 2);
    assert(playerSDL->rect.y == SCREEN_HEIGHT - HEIGHT_MAIN);
    assert(playerSDL->rect.w == WIDTH_MAIN);
    assert(playerSDL->rect.h == HEIGHT_MAIN);
    // Test control function
    SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.repeat = 0;
    event.key.keysym.sym = SDLK_w;
    Mix_Chunk *bulletSound[4];
    Mix_Chunk *gSoundLevelUp = new Mix_Chunk();
    Player *player = new Player();
    playerSDL->setPlayer(player);
    playerSDL->control(event, renderer, bulletSound, 1, gSoundLevelUp, playerSDL->getPlayer());
    assert(playerSDL->player->getY() == -MAIN_SPEED);
    event.type = SDL_KEYUP;
    event.key.keysym.sym = SDLK_w;
    playerSDL->control(event, renderer, bulletSound, 1, gSoundLevelUp, playerSDL->getPlayer());
    assert(playerSDL->player->getY() == 0);

    // Test move function
    playerSDL->rect.x = SCREEN_WIDTH / 2;
    playerSDL->rect.y = SCREEN_HEIGHT - HEIGHT_MAIN;
    playerSDL->player->setX(1);
    playerSDL->move(playerSDL->getPlayer());
    assert(playerSDL->rect.x == SCREEN_WIDTH / 2 + 1);
    playerSDL->player->setX(-1);
    playerSDL->move(playerSDL->getPlayer());
    assert(playerSDL->rect.x == SCREEN_WIDTH / 2);
    // Test handleBullet function
    playerSDL->player->setBulletType(BLASTER);
    playerSDL->player->getBulletList().clear();
    Bullet *bullet = new Bullet();
    std::vector<Bullet *> bulletList2 = player->getBulletList();
    bulletList2.push_back(bullet);
    player->setBulletList(bulletList2);
    playerSDL->handleBullet(renderer, playerSDL);
    assert(playerSDL->player->getBulletList().size() != 0);
    delete bullet;
    delete player;
    delete playerSDL;
}

GameSDL::GameSDL()
{
    isRunning = true;
    bullet_level = 0;
    kill = 0;
    scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
    time_end_game = 0;
    count_num_exp = 0;
    menu_number = 0;
}

GameSDL::~GameSDL()
{
}
bool GameSDL::getRunning() const
{
    return isRunning;
}

bool GameSDL::checkCollision(const SDL_Rect &objet1, const SDL_Rect &objet2)
{
    int left_a = objet1.x;
    int right_a = objet1.x + objet1.w;
    int top_a = objet1.y;
    int bottom_a = objet1.y + objet1.h;

    int left_b = objet2.x;
    int right_b = objet2.x + objet2.w;
    int top_b = objet2.y;
    int bottom_b = objet2.y + objet2.h;

    if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b)
    {
        return false;
    }
    return true;
}

bool GameSDL::check_mouse_vs_item(const int &x, const int &y, const SDL_Rect &rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

void GameSDL::menu(const std::string &item)
{
    Base *menu = new Base();
    Base *menu2 = new Base();
    Base *menu3 = new Base();
    if (!menu->loadImg("data//image//menu.png", gRenderer))
    {
        isRunning = false;
        return;
    }
    if (!menu2->loadImg("data//image//menu2.png", gRenderer))
    {
        isRunning = false;
        return;
    }
    if (!menu3->loadImg("data//image//background.png", gRenderer))
    {
        isRunning = false;
        return;
    }

    const int number_of_item = 5;
    SDL_Rect pos_arr[number_of_item];
    Text *text_menu = new Text[number_of_item];

    // menu main
    text_menu[0].setText(item);
    text_menu[0].setColor(Text::BLACK);
    text_menu[0].loadShowText(gFontMenu, gRenderer);
    pos_arr[0].x = SCREEN_WIDTH / 2 - text_menu[0].getRect().w / 2;
    pos_arr[0].y = SCREEN_HEIGHT - 400;
    text_menu[0].setRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].setText("Information");
    text_menu[1].setColor(Text::BLACK);
    text_menu[1].loadShowText(gFontMenu, gRenderer);
    pos_arr[1].x = SCREEN_WIDTH / 2 - text_menu[1].getRect().w / 2;
    pos_arr[1].y = SCREEN_HEIGHT - 300;
    text_menu[1].setRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].setText("High Score");
    text_menu[2].setColor(Text::BLACK);
    text_menu[2].loadShowText(gFontMenu, gRenderer);
    pos_arr[2].x = SCREEN_WIDTH / 2 - text_menu[2].getRect().w / 2;
    pos_arr[2].y = SCREEN_HEIGHT - 200;
    text_menu[2].setRect(pos_arr[2].x, pos_arr[2].y);

    text_menu[3].setText("Quit !");
    text_menu[3].setColor(Text::BLACK);
    text_menu[3].loadShowText(gFontMenu, gRenderer);
    pos_arr[3].x = SCREEN_WIDTH / 2 - text_menu[3].getRect().w / 2;
    pos_arr[3].y = SCREEN_HEIGHT - 100;
    text_menu[3].setRect(pos_arr[3].x, pos_arr[3].y);

    text_menu[4].setText("Back !");
    text_menu[4].setColor(Text::BLACK);
    text_menu[4].loadShowText(gFontMenu, gRenderer);
    pos_arr[4].x = 10;
    pos_arr[4].y = 10;
    text_menu[4].setRect(pos_arr[4].x, pos_arr[4].y);

    int xm = 0;
    int ym = 0;
    Mix_PlayMusic(gMusicStart, -1);
    bool quit = true;

    while (quit)
    {
        if (menu_number == 0)
        {
            menu->render(gRenderer);
            for (int i = 0; i < number_of_item - 1; i++)
            {
                text_menu[i].loadShowText(gFontMenu, gRenderer);
            }
        }
        else if (menu_number == 1)
        {
            menu2->render(gRenderer);
            text_menu[4].loadShowText(gFontMenu, gRenderer);
        }
        else if (menu_number == 2)
        {
            menu3->render(gRenderer);
            text_menu[4].loadShowText(gFontMenu, gRenderer);

            Text *text = new Text[5];
            SDL_Rect pos_text[5];

            setHighScore();
            text[0].setText("TOP 1 : " + std::to_string(highScores[0]));
            text[0].setColor(Text::BLACK);
            pos_text[0].x = SCREEN_WIDTH / 2 - text[0].getRect().w / 2 - 200;
            pos_text[0].y = SCREEN_HEIGHT - 550;
            text[0].setRect(pos_text[0].x, pos_text[0].y);

            text[1].setText("TOP 2 : " + std::to_string(highScores[1]));
            text[1].setColor(Text::BLACK);
            pos_text[1].x = SCREEN_WIDTH / 2 - text[1].getRect().w / 2 - 200;
            pos_text[1].y = SCREEN_HEIGHT - 450;
            text[1].setRect(pos_text[1].x, pos_text[1].y);

            text[2].setText("TOP 3 : " + std::to_string(highScores[2]));
            text[2].setColor(Text::BLACK);
            pos_text[2].x = SCREEN_WIDTH / 2 - text[2].getRect().w / 2 - 200;
            pos_text[2].y = SCREEN_HEIGHT - 350;
            text[2].setRect(pos_text[2].x, pos_text[2].y);

            text[3].setText("TOP 4 : " + std::to_string(highScores[3]));
            text[3].setColor(Text::BLACK);
            pos_text[3].x = SCREEN_WIDTH / 2 - text[3].getRect().w / 2 - 200;
            pos_text[3].y = SCREEN_HEIGHT - 250;
            text[3].setRect(pos_text[3].x, pos_text[3].y);

            text[4].setText("TOP 5 : " + std::to_string(highScores[4]));
            text[4].setColor(Text::BLACK);
            pos_text[4].x = SCREEN_WIDTH / 2 - text[4].getRect().w / 2 - 200;
            pos_text[4].y = SCREEN_HEIGHT - 150;
            text[4].setRect(pos_text[4].x, pos_text[4].y);

            text[0].loadShowText(gFontMenu, gRenderer);
            text[1].loadShowText(gFontMenu, gRenderer);
            text[2].loadShowText(gFontMenu, gRenderer);
            text[3].loadShowText(gFontMenu, gRenderer);
            text[4].loadShowText(gFontMenu, gRenderer);
        }
        while (SDL_PollEvent(&gEvent) != 0)
        {
            Player *player = new Player();
            PlayerSDL *spaceship = new PlayerSDL();
            spaceship->setPlayer(player);
            spaceship->control(gEvent, gRenderer, gSoundBullet, bullet_level, gSoundLevelUp, spaceship->getPlayer());
            if (gEvent.type == SDL_QUIT)
            {
                isRunning = false;
                quit = false;
            }
            else if (gEvent.type == SDL_MOUSEMOTION)
            {
                xm = gEvent.motion.x;
                ym = gEvent.motion.y;

                for (int i = 0; i < number_of_item; i++)
                {
                    if (check_mouse_vs_item(xm, ym, text_menu[i].getRect()))
                    {
                        text_menu[i].setColor(Text::WHITE);
                    }
                    else
                    {
                        text_menu[i].setColor(Text::BLACK);
                    }
                }
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                xm = gEvent.button.x;
                ym = gEvent.button.y;

                for (int i = 0; i < number_of_item; i++)
                {
                    if (menu_number == 0)
                    {
                        if (check_mouse_vs_item(xm, ym, text_menu[i].getRect()))
                        {
                            if (i == 0)
                            {
                                isRunning = true;
                                quit = false;
                            }
                            else if (i == 1)
                            {
                                menu_number = 1;
                            }
                            else if (i == 2)
                            {
                                menu_number = 2;
                            }
                            else if (i == 3)
                            {
                                isRunning = false;
                                quit = false;
                            }
                            Mix_PlayChannel(-1, gSoundLevelUp, 0);
                        }
                    }
                    else if (menu_number == 1)
                    {
                        if (check_mouse_vs_item(xm, ym, text_menu[4].getRect()))
                        {
                            menu_number = 0;
                            Mix_PlayChannel(-1, gSoundLevelUp, 0);
                        }
                    }
                    else if (menu_number == 2)
                    {
                        if (check_mouse_vs_item(xm, ym, text_menu[4].getRect()))
                        {
                            menu_number = 0;
                            Mix_PlayChannel(-1, gSoundLevelUp, 0);
                        }
                    }
                }
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    Mix_PauseMusic();
}

void GameSDL::clean()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

void GameSDL::init(std::string title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        isRunning = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            isRunning = false;
        }
        else
        {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                isRunning = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    isRunning = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    isRunning = false;
                }

                gSoundBullet[0] = Mix_LoadWAV("data//sound//blaster.wav");
                gSoundBullet[1] = Mix_LoadWAV("data//sound//neutron.wav");
                gSoundBullet[2] = Mix_LoadWAV("data//sound//boron.wav");
                gSoundExp[0] = Mix_LoadWAV("data//sound//exp.wav");
                gSoundExp[1] = Mix_LoadWAV("data//sound//exp_uco.wav");
                gSoundChickenHit[0] = Mix_LoadWAV("data//sound//ChickenHit.wav");
                gSoundChickenHit[1] = Mix_LoadWAV("data//sound//ChickenHit2.wav");
                gSoundChickenHit[2] = Mix_LoadWAV("data//sound//ChickenHit3.wav");
                gSoundLevelUp = Mix_LoadWAV("data//sound//level_up.wav");
                gMusicStart = Mix_LoadMUS("data//sound//start.mp3");

                if (gSoundBullet[0] == NULL || gSoundBullet[1] == NULL || gSoundBullet[2] == NULL || gSoundExp[0] == NULL || gSoundExp[1] == NULL || gSoundChickenHit[0] == NULL || gSoundChickenHit[1] == NULL || gSoundChickenHit[2] == NULL || gSoundLevelUp == NULL || gMusicStart == NULL)
                {
                    isRunning = false;
                }
                if (TTF_Init() < 0)
                {
                    isRunning = false;
                }
                gFontText = TTF_OpenFont("data//font//font1.ttf", 24);
                gFontMenu = TTF_OpenFont("data//font//font1.ttf", 50);
                gFontEndGame = TTF_OpenFont("data//font//font1.ttf", 60);
                if (gFontText == NULL || gFontMenu == NULL || gFontEndGame == NULL)
                {
                    isRunning = false;
                }
            }
        }
    }
    // init background and main_objet
    Base *background = new Base();
    background->loadImg("data//image//background.png", gRenderer);
    PlayerSDL *spaceship = new PlayerSDL();
    spaceship->loadImg("data//image//spacecraft.png", gRenderer);
    Player *player_sub = new Player();
    spaceship->setPlayer(player_sub);
    // boss
    BossSDL *boss = new BossSDL();
    boss->loadImg("data//image//boss.png", gRenderer);
    boss->setClip();
    boss->setRect(-WIDTH_BOSS, -HEIGHT_BOSS);
    Boss *newBoss = new Boss();
    newBoss->setX(BOSS_SPEED);
    newBoss->setY(BOSS_SPEED * 3);
    newBoss->setHeart(BOSS_HEART);
    boss->setBoss(newBoss);
    BulletSDL *p_bullet = new BulletSDL();
    boss->initBullet(p_bullet, gRenderer, boss);

    // init chicken
    int t = 0;
    int y_row = 0;
    for (int c = 0; c < NUMBER_OF_CHICKEN; c++)
    {
        ChickenSDL *p_chicken = new ChickenSDL();
        Chicken *chick = new Chicken();
        p_chicken->setChicken(chick);
        if (chick)
        {
            p_chicken->loadImg("data//image//chicken_red.png", gRenderer);
            p_chicken->setClip();
        }
        if (t % NUMBER_OF_CHICKEN_PER_ROW == 0)
        {
            y_row -= DISTANCE_BETWEEN_CHICKENS;
            t = 0;
        }
        p_chicken->setRect(10 + t * DISTANCE_BETWEEN_CHICKENS, y_row);
        chick->setY(CHICKEN_SPEED);
        chick->setX(CHICKEN_SPEED);
        chick->setHeart(CHICKEN_HEART);
        p_chicken->setChicken(chick);
        int random = rand() % 8;
        if (random < 2)
        {
            BulletSDL *p_bullet = new BulletSDL();
            p_chicken->initBullet(p_bullet, p_chicken, gRenderer);
        }
        p_chicken_list.push_back(p_chicken);
        t++;
    }
    // init exp
    ExplodeSDL *exp = new ExplodeSDL();
    exp->loadImg("data//image//exp.png", gRenderer);
    exp->setClip();

    ExplodeSDL *exp_boss = new ExplodeSDL();
    exp_boss->loadImg("data//image//exp.png", gRenderer);
    exp_boss->setClip();
    GiftSDL *gift = new GiftSDL();
    Gift *sub_gift = new Gift();
    gift->setClip();
    gift->setGift(sub_gift);

    // init support
    Base *support = new Base();
    support->loadImg("data//image//support.png", gRenderer);
    support->setRect(-20, 10);

    Text *kill_text = new Text();
    Text *heart_text = new Text();
    Text *lighting_text = new Text();
    Text *hint = new Text();
    Text *end_game = new Text();

    kill_text->setColor(Text::WHITE);
    heart_text->setColor(Text::WHITE);
    lighting_text->setColor(Text::WHITE);
    hint->setColor(Text::WHITE);
    end_game->setColor(Text::WHITE);

    isRunning = true;

    menu("Start");

    while (isRunning)
    {

        while (SDL_PollEvent(&gEvent))
        {
            if (gEvent.type == SDL_QUIT)
            {
                isRunning = false;
            }
            spaceship->control(gEvent, gRenderer, gSoundBullet, bullet_level, gSoundLevelUp, spaceship->getPlayer());
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        scrolling += SCREEN_SPEED;
        if (scrolling < 0)
        {
            background->render(gRenderer);
            background->setRect(0, scrolling);
        }
        else
        {
            background->render(gRenderer);
            background->setRect(0, 0);
        }
        // handle player
        spaceship->move(spaceship->getPlayer());
        spaceship->show(gRenderer, spaceship->getPlayer());
        spaceship->handleBullet(gRenderer, spaceship);

        // handle chicken

        if (kill < NUMBER_OF_CHICKEN * 2)
        {
            for (int ck = 0; ck < (int)p_chicken_list.size(); ck++)
            {
                ChickenSDL *chicken = p_chicken_list.at(ck);
                if (chicken)
                {
                    chicken->move(chicken->getChicken());
                    chicken->show(gRenderer, chicken->getChicken());
                    chicken->handleBullet(gRenderer, chicken->getChicken());
                }
                // check spacecraft with chicken_bullet
                bool Col1 = false;
                std::vector<BulletSDL *> bullet_list = chicken->getBulletList();
                for (int b = 0; b < (int)bullet_list.size(); b++)
                {
                    BulletSDL *p_bullet = bullet_list.at(b);
                    if (p_bullet)
                    {
                        Col1 = checkCollision(p_bullet->getRect(), spaceship->getRect());
                        if (Col1 == true)
                        {
                            chicken->removeBullet(b);
                            break;
                        }
                    }
                }
                bool Col2 = checkCollision(spaceship->getRect(), chicken->getRectFrame());
                if (Col1 || Col2)
                {
                    Mix_PlayChannel(-1, gSoundExp[0], 0);

                    // set exp
                    int x_pos = (spaceship->getRect().x + WIDTH_MAIN / 2) - WIDTH_FRAME_EXP / 2;
                    int y_pos = (spaceship->getRect().y + HEIGHT_MAIN / 2) - HEIGHT_FRAME_EXP / 2;

                    exp->setRect(x_pos, y_pos);
                    exp->setFrame(0);

                    spaceship->setRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
                    player_sub->setStatus(false);
                    player_sub->decreaseHeart();
                    spaceship->setPlayer(player_sub);
                    if (player_sub->getHeart() >= 0)
                    {
                        bullet_level = bullet_level < 2 ? 0 : (bullet_level - 1);
                    }
                }
                // check main_object_bullet with chicken
                std::vector<BulletSDL *> s_bullet_list = spaceship->getBulletList();
                for (int sb = 0; sb < (int)s_bullet_list.size(); sb++)
                {
                    BulletSDL *p_bullet = s_bullet_list.at(sb);
                    if (p_bullet != NULL)
                    {
                        bool Col3 = checkCollision(p_bullet->getRect(), chicken->getRectFrame());
                        if (Col3)
                        {
                            Chicken *p_chicken = chicken->getChicken();
                            p_chicken->decrease((spaceship->getPlayer()->getBulletDamage()) + bullet_level * BULLET_DAMAGE_LEVEL_UP);
                            chicken->setChicken(p_chicken);
                            Mix_PlayChannel(-1, gSoundChickenHit[rand() % 2], 0);
                            spaceship->removeBullet(sb);

                            if (p_chicken->getHeart() <= 0)
                            {
                                p_chicken->setHeart(CHICKEN_HEART);
                                kill++;
                                Mix_PlayChannel(-1, gSoundChickenHit[2], 0);
                                chicken->setChicken(p_chicken);

                                chicken->setRect(chicken->getRect().x, -3 * SCREEN_HEIGHT);
                                if (kill > NUMBER_OF_CHICKEN)
                                {
                                    p_chicken->setComeBack(false);
                                    chicken->setChicken(p_chicken);
                                }

                                if (kill % ONE_TURN_GIFT == 0)
                                {
                                    sub_gift = gift->getGift();
                                    sub_gift->setGiftType(sub_gift->randomGift());
                                    sub_gift->setY(GIFT_SPEED);
                                    sub_gift->setComeBack(true);
                                    gift->setGift(sub_gift);
                                    gift->loadImgGift(gRenderer);
                                    gift->setRect((rand() % (SCREEN_WIDTH - 2 * GIFT_WIDTH) + GIFT_WIDTH), -GIFT_HEIGHT);
                                }
                            }
                        }
                    }
                }
            }
        }
        // handle boss

        if (kill >= NUMBER_OF_CHICKEN * 2 && boss->getBoss()->getHeart() >= 0)
        {
            boss->showHeartBoss(gRenderer, 420, 20, newBoss->getHeart(), 6);
            boss->move();
            boss->show(gRenderer);
            boss->makeBullet(gRenderer, boss->getBoss());
            // check spacecraft with boss
            bool Col1 = false;
            std::vector<BulletSDL *> boss_bullet_list = boss->getBulletList();
            for (int b = 0; b < (int)boss_bullet_list.size(); b++)
            {
                BulletSDL *p_bullet = boss_bullet_list.at(b);
                if (p_bullet)
                {
                    Col1 = checkCollision(p_bullet->getRect(), spaceship->getRect());
                }
            }

            // check spacecraft with boss
            bool Col2 = checkCollision(spaceship->getRect(), boss->getRectFrame());
            if (Col1 || Col2)
            {
                Mix_PlayChannel(-1, gSoundExp[0], 0);

                // set exp
                int x_pos = (spaceship->getRect().x + WIDTH_MAIN / 2) - WIDTH_FRAME_EXP / 2;
                int y_pos = (spaceship->getRect().y + HEIGHT_MAIN / 2) - HEIGHT_FRAME_EXP / 2;
                exp->setRect(x_pos, y_pos);
                exp->setFrame(0);

                spaceship->setRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
                player_sub->setStatus(false);
                player_sub->decreaseHeart();
                spaceship->setPlayer(player_sub);
                if (player_sub->getHeart() >= 0)
                {
                    bullet_level = bullet_level < 2 ? 0 : (bullet_level - 1);
                }
            }
            // check main_object_bullet with chicken
            std::vector<BulletSDL *> s_bullet_list = spaceship->getBulletList();
            for (int sb = 0; sb < (int)s_bullet_list.size(); sb++)
            {
                BulletSDL *p_bullet = s_bullet_list.at(sb);
                if (p_bullet != NULL)
                {
                    bool Col3 = checkCollision(p_bullet->getRect(), boss->getRectFrame());
                    if (Col3)
                    {
                        Boss *sub_boss = boss->getBoss();
                        sub_boss->decrease((spaceship->getPlayer()->getBulletDamage()) + bullet_level * BULLET_DAMAGE_LEVEL_UP);
                        boss->setBoss(sub_boss);
                        Mix_PlayChannel(-1, gSoundChickenHit[rand() % 2], 0);
                        spaceship->removeBullet(sb);
                        if (sub_boss->getHeart() < 0)
                        {
                            kill++;
                            // set exp
                            int x_pos = (boss->getRect().x + WIDTH_BOSS / 2) - WIDTH_FRAME_EXP / 2;
                            int y_pos = (boss->getRect().y + HEIGHT_BOSS / 2) - HEIGHT_FRAME_EXP / 2;
                            exp_boss->setRect(x_pos, y_pos);
                            exp_boss->setFrame(0);
                            boss->setRect(SCREEN_WIDTH / 2, -SCREEN_HEIGHT);
                            Mix_PlayChannel(-1, gSoundExp[0], 0);
                        }
                    }
                }
            }
        }

        // //show exp
        if (exp->getFrame() < NUMBER_OF_FRAME * 2)
        {
            exp->show(gRenderer);
        }
        if (exp_boss->getFrame() < NUMBER_OF_FRAME * 2)
        {
            exp_boss->show(gRenderer);
            if (exp_boss->getFrame() >= NUMBER_OF_FRAME * 2 && count_num_exp < NUMBER_OF_EXP)
            {
                Mix_PlayChannel(-1, gSoundExp[0], 0);
                exp_boss->setFrame(0);
                count_num_exp++;
            }
        }

        // game over
        if (spaceship->getPlayer()->getHeart() == 0)
        {
            if (time_end_game < 300)
            {
                time_end_game++;
                end_game->setText("Game Over !");
                end_game->setRect(430, SCREEN_HEIGHT / 5 + 200);
                end_game->loadShowText(gFontEndGame, gRenderer);
            }
            else
            {
                menu("Play Again");
                // resetGame();
                bullet_level = 0;
                kill = 0;
                count_num_exp = 0;
                scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
                time_end_game = 0;
                spaceship->setPlayer(player_sub);
                player_sub->setBulletType(BLASTER);
                player_sub->setStatus(true);
                player_sub->setHeart(3);
                spaceship->setPlayer(player_sub);
                spaceship->setRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT - HEIGHT_MAIN);

                newBoss->setHeart(BOSS_HEART);
                boss->setBoss(newBoss);
                boss->setRect(-WIDTH_BOSS, -HEIGHT_BOSS);
                for (int i = 0; i < (int)boss->getBulletList().size(); i++)
                {
                    BulletSDL *p_bullet = boss->getBulletList().at(i);
                    if (p_bullet)
                    {
                        p_bullet->setRect(boss->getRect().x + WIDTH_BOSS / 2, boss->getRect().y + HEIGHT_BOSS);
                    }
                }
                int t = 0;
                int y_row = -DISTANCE_BETWEEN_CHICKENS;
                for (int c = 0; c < NUMBER_OF_CHICKEN; c++)
                {
                    ChickenSDL *p_chicken = p_chicken_list.at(c);
                    Chicken *chicken = p_chicken->getChicken();
                    p_chicken->setChicken(chicken);
                    if (t % NUMBER_OF_CHICKEN_PER_ROW == 0)
                    {
                        y_row -= DISTANCE_BETWEEN_CHICKENS;
                        t = 0;
                    }
                    chicken->setComeBack(true);
                    chicken->setHeart(CHICKEN_HEART);
                    chicken->setStatusRight();
                    p_chicken->setChicken(chicken);
                    p_chicken->setRect(10 + t * DISTANCE_BETWEEN_CHICKENS, y_row);
                    t++;
                    for (int i = 0; i < (int)p_chicken->getBulletList().size(); i++)
                    {
                        BulletSDL *p_bullet = p_chicken->getBulletList().at(i);
                        if (p_bullet)
                        {
                            p_bullet->setRect(p_chicken->getRect().x + WIDTH_CHICKEN / 2 - p_bullet->getRect().w / 2, p_chicken->getRect().y + HEIGHT_CHICKEN);
                        }
                    }
                }
            }
        }
        else
        {
            if (spaceship->getPlayer()->getStatus() == false)
            {
                hint->setText("Press 'ENTER' to revive !");
                hint->setRect(220, SCREEN_HEIGHT / 4 + 150);
                hint->loadShowText(gFontEndGame, gRenderer);
            }
        }
        // game win
        if (boss->getBoss()->getHeart() <= 0)
        {
            if (time_end_game < 300)
            {
                time_end_game++;
                end_game->setText("Win Game !");
                end_game->setRect(430, SCREEN_HEIGHT / 5 + 200);
                end_game->loadShowText(gFontEndGame, gRenderer);
            }
            else
            {
                menu("Play Again");
                // resetGame();
                bullet_level = 0;
                kill = 0;
                count_num_exp = 0;
                scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
                time_end_game = 0;
                spaceship->setPlayer(player_sub);
                player_sub->setBulletType(BLASTER);
                player_sub->setStatus(true);
                player_sub->setHeart(3);
                spaceship->setPlayer(player_sub);
                spaceship->setRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT - HEIGHT_MAIN);

                newBoss->setHeart(BOSS_HEART);
                boss->setBoss(newBoss);
                boss->setRect(-WIDTH_BOSS, -HEIGHT_BOSS);
                for (int i = 0; i < (int)boss->getBulletList().size(); i++)
                {
                    BulletSDL *p_bullet = boss->getBulletList().at(i);
                    if (p_bullet)
                    {
                        p_bullet->setRect(boss->getRect().x + WIDTH_BOSS / 2, boss->getRect().y + HEIGHT_BOSS);
                    }
                }
                int t = 0;
                int y_row = -DISTANCE_BETWEEN_CHICKENS;
                for (int c = 0; c < NUMBER_OF_CHICKEN; c++)
                {
                    ChickenSDL *p_chicken = p_chicken_list.at(c);
                    Chicken *chicken = p_chicken->getChicken();
                    p_chicken->setChicken(chicken);
                    if (t % NUMBER_OF_CHICKEN_PER_ROW == 0)
                    {
                        y_row -= DISTANCE_BETWEEN_CHICKENS;
                        t = 0;
                    }
                    chicken->setComeBack(true);
                    chicken->setHeart(CHICKEN_HEART);
                    chicken->setStatusRight();
                    p_chicken->setChicken(chicken);
                    p_chicken->setRect(10 + t * DISTANCE_BETWEEN_CHICKENS, y_row);
                    t++;
                    for (int i = 0; i < (int)p_chicken->getBulletList().size(); i++)
                    {
                        BulletSDL *p_bullet = p_chicken->getBulletList().at(i);
                        if (p_bullet)
                        {
                            p_bullet->setRect(p_chicken->getRect().x + WIDTH_CHICKEN / 2 - p_bullet->getRect().w / 2, p_chicken->getRect().y + HEIGHT_CHICKEN);
                        }
                    }
                }
            }
        }

        // handle gift
        gift->move(SCREEN_WIDTH, SCREEN_HEIGHT);
        gift->show(gRenderer);
        sub_gift = gift->getGift();
        player_sub = spaceship->getPlayer();
        bool Col4 = checkCollision(spaceship->getRect(), sub_gift->getGiftType() < LEVEL_UP ? gift->getRect() : gift->getRectFrame());
        if (Col4)
        {
            gift->setRect(-GIFT_WIDTH, -GIFT_HEIGHT);
            if (bullet_level < 3 && ((sub_gift->getGiftType() == player_sub->getBulletType()) || sub_gift->getGiftType() == LEVEL_UP))
            {
                bullet_level++;
            }
            Mix_PlayChannel(-1, gSoundLevelUp, 0);
            if (sub_gift->getGiftType() < LEVEL_UP)
            {
                player_sub->setBulletType(sub_gift->getGiftType());
                spaceship->setPlayer(player_sub);
            }

            sub_gift->setComeBack(false);
            gift->setGift(sub_gift);
        }

        // show support
        support->render(gRenderer);
        heart_text->setText(std::to_string(spaceship->getPlayer()->getHeart()));
        heart_text->setRect(195, 15);
        heart_text->loadShowText(gFontText, gRenderer);
        kill_text->setText(std::to_string(kill));
        kill_text->setRect(50, 15);
        kill_text->loadShowText(gFontText, gRenderer);
        lighting_text->setText(std::to_string(bullet_level));
        lighting_text->setRect(280, 15);
        lighting_text->loadShowText(gFontText, gRenderer);

        SDL_RenderPresent(gRenderer);
    }
}

void GameSDL::setHighScore()
{

    // Load the high scores from a file
    std::ifstream file("data//highscores.txt");
    if (file.is_open())
    {
        for (int i = 0; i < NUM_HIGH_SCORES && !file.eof(); i++)
        {
            file >> highScores[i];
        }
        file.close();
    }
    // sort
    int i, j, temp;
    for (i = 1; i < 5; i++)
    {
        j = i - 1;
        temp = highScores[i];
        while (highScores[j] < temp && j >= 0)
        {
            highScores[j + 1] = highScores[j];
            j--;
        }
        highScores[j + 1] = temp;
    }

    if (highScores[0] < kill)
    {
        highScores[4] = highScores[3];
        highScores[3] = highScores[2];
        highScores[2] = highScores[1];
        highScores[1] = highScores[0];
        highScores[0] = kill;
    }
    else if (highScores[0] > kill && kill > highScores[1])
    {
        highScores[4] = highScores[3];
        highScores[3] = highScores[2];
        highScores[2] = highScores[1];
        highScores[1] = kill;
    }
    else if (highScores[1] > kill && kill > highScores[2])
    {
        highScores[4] = highScores[3];
        highScores[3] = highScores[2];
        highScores[2] = kill;
    }
    else if (highScores[2] > kill && kill > highScores[3])
    {
        highScores[4] = highScores[3];
        highScores[3] = kill;
    }
    else if (highScores[3] > kill && kill > highScores[4])
    {
        highScores[4] = kill;
    }

    // Save the high scores to a file when the game is over
    std::ofstream outfile("data//highscores.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < NUM_HIGH_SCORES; i++)
        {
            outfile << highScores[i] << std::endl;
        }
        outfile.close();
    }
}
