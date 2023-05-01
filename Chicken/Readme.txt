        ########################################  CHICKEN INVADERS  ######################################################


### à propos  

	CHICKEN INVADERS est un jeu codé en c++ où vous incarnez l’un des derniers humains à bord d’un vaisseau spatial, qui doit défendre 	l’humanité d’une invasion de poulet de l’espace, pour ce faire votre faisceau est équipé d’un arsenal vous permettant de détruire la 	menace en leur tirant dessus. mais attention aux attaques des ennemis qui  vous laisseront aucun répit!! Le jeu se rapproche ainsi 	beaucoup de Star Defender par la manière de jouer. Sur un fond noir avec des étoiles, le joueur doit tirer sur les poulets ou qui 	arrivent du haut de l'écran . et cumule des points au fur et à mesure qu' il détruit les poulets,Son objectif est donc de ne pas se 	faire toucher par les tirs des poules, la partie s'arrête une fois que le joueur perd l’ensemble de ses vies, celle-ci se perd 	lorsque le joueur se fait toucher une fois
	regle: W S A D pour se deplacer le joueur doit detruitre 36 poulets pour faire apparaitre le boss, le joueur dispose de 3 vies il 	doit eviter les oeuf des poulet et aussi les poulet qui se deplace vers lui. on utilise "ENTER" pour revivre une fois toucher. il 	peut tirer avec "ESPACE" . Il peu recuperer des bonus/cadeau pour ameliorer ses tires ou changer le type de tirs.

### Dependance requise 

	- systeme exploitation linux (makfile) 
	- librairie graphique et audio pour l'affichage et le son  : SDL2
	
### Compilation et execution

	Donc pour utiliser ce code, il faut l'executer sur une machine Linux.
	Il faut préalablement installer les librairies SDL avec la commande "sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev".
	Rentrer a la racine du project par la commande "cd Chicken"
	Pour compiler chacun des executables, il faut lancer la commande "make".
	POUR effacer les .o et executable lancer "make clean"
 	pour executer le jeu ./bin/chicken
	pour executer le TEXTE MODE ./bin/txt
	pour executer le test regression pour les cores classe ./bin/testRegression 
	pour executer le test regression pour les classe sdl  ./bin/testRegressionSDL

### Organisation de l'archive 

	Ce répertoire contient les sous répertoires bin, src, obj, img, aud, 

	/bin contient les executables.
	/src contient les fichiers source de core, sdl2 et txt (.h et .cpp).
	/obj contient les fichiers objets (.o).
	/data contient les fichiers images et audio (.png, .jpeg et .mp3, .M4A).
	/doc contient chicken.doxy, le fichier html qui contient index.html, le diagramme de Gantt, le diagramme des classes UML et fichier PowerPoint de presentation
### Liste de fonctionalitées

	
- b -
Base() : Base
Boss() : Boss
BossSDL() : BossSDL
Bullet() : Bullet
BulletSDL() : BulletSDL

- c -
check_mouse_vs_item() : GameSDL
checkCollision() : GameSDL
Chicken() : Chicken
ChickenSDL() : ChickenSDL
clean() : Base, GameSDL
control() : PlayerSDL

- d -
decrease() : Boss, Chicken
decreaseHeart() : Player

- e -
Explode() : Explode
ExplodeSDL() : ExplodeSDL

- g -
GameLoop() : GameTXT
GameSDL() : GameSDL
GameTXT() : GameTXT
getBoss() : BossSDL
getBullet() : BulletSDL
getBulletDamage() : Player
getBulletList() : BossSDL, ChickenSDL, Player, PlayerSDL
getBulletType() : Bullet, Player
getChicken() : ChickenSDL
getComeBack() : Chicken, Gift
getFrame() : ExplodeSDL
getGift() : GiftSDL
getGiftType() : Gift
getHeart() : Boss, Chicken, Player
getMove() : Bullet, BulletSDL
getPlayer() : PlayerSDL
getRect() : Base
getRectFrame() : BossSDL, ChickenSDL, GiftSDL
getRunning() : GameSDL
getStatus() : Boss, Chicken, Player
getX() : Boss, Bullet, Chicken, Gift, Player
getY() : Boss, Bullet, Chicken, Gift, Player
Gift() : Gift
GiftSDL() : GiftSDL

- h -
handleBossBullet() : BulletSDL
handleBullet() : ChickenSDL, PlayerSDL
handleChickenBullet() : BulletSDL
HandleInput() : GameTXT
handlePlayerBullet() : BulletSDL

- i -
init() : GameSDL
initBullet() : BossSDL, ChickenSDL
InitGame() : GameTXT

- l -
loadImg() : Base
loadImgBullet() : BulletSDL
loadImgGift() : GiftSDL
loadShowText() : Text
- m -
makeBullet() : BossSDL
menu() : GameSDL
move() : BossSDL, ChickenSDL, GiftSDL, PlayerSDL
- p -
Player() : Player
PlayerSDL() : PlayerSDL
PrintBoard() : GameTXT
- r -
randomGift() : Gift
removeBullet() : ChickenSDL, PlayerSDL
render() : Base
- s -
setBoss() : BossSDL
setBullet() : BulletSDL
setBulletDamage() : Player
setBulletList() : Player
setBulletType() : Bullet, Player
setChicken() : ChickenSDL
setClip() : BossSDL, ChickenSDL, ExplodeSDL, GiftSDL
setColor() : Text
setComeBack() : Chicken, Gift
setFrame() : ExplodeSDL
setGift() : GiftSDL
setGiftType() : Gift
setHeart() : Boss, Chicken, Player
setHighScore() : GameSDL
setMove() : Bullet, BulletSDL
setPlayer() : PlayerSDL
setRect() : Base
setStatus() : Boss, Chicken, Player
setStatusRight() : Chicken
setText() : Text
setX() : Boss, Bullet, Chicken, Gift, Player
setY() : Boss, Bullet, Chicken, Gift, Player
show() : BossSDL, ChickenSDL, ExplodeSDL, GiftSDL, PlayerSDL
showHeartBoss() : BossSDL
- t -
testRegression() : Base, Boss, BossSDL, Bullet, BulletSDL, Chicken, ChickenSDL, ExplodeSDL, GameSDL, Gift, GiftSDL, Player, PlayerSDL, Text
- u -
UpdateBoard() : GameTXT
- ~ -
~Base() : Base
~Boss() : Boss
~BossSDL() : BossSDL
~Bullet() : Bullet
~BulletSDL() : BulletSDL
~Chicken() : Chicken
~ChickenSDL() : ChickenSDL
~Explode() : Explode
~ExplodeSDL() : ExplodeSDL
~GameSDL() : GameSDL
~GameTXT() : GameTXT
~Gift() : Gift
~GiftSDL() : GiftSDL
~Player() : Player
~PlayerSDL() : PlayerSDL
~Text() : Text
﻿


### Licence

	crée par: 
	p2208485 ANH DUY VU
	p2006707 TRAD NEDIM
