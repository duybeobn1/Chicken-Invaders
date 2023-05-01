all : chicken testRegression txt testRegressionSDL
txt : GameTXT.o Text.o
	g++ obj/GameTXT.o obj/Text.o -o bin/txt
testRegressionSDL : Global.o Player.o Gift.o Explode.o Chicken.o Bullet.o Boss.o Base.o testRegressionSDL.o 
	g++ obj/Global.o obj/Player.o obj/Gift.o obj/Explode.o obj/Chicken.o obj/Bullet.o obj/Boss.o obj/Base.o obj/testRegressionSDL.o -o bin/testRegressionSDL -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
chicken : Global.o Player.o Gift.o Explode.o Chicken.o Bullet.o Boss.o Base.o main.o 
	g++ obj/Global.o obj/Player.o obj/Gift.o obj/Explode.o obj/Chicken.o obj/Bullet.o obj/Boss.o obj/Base.o obj/main.o -o bin/chicken -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
testRegression : testRegression.o Global.o Player.o Gift.o Explode.o Chicken.o Bullet.o Boss.o
	g++ obj/Global.o obj/Player.o obj/Gift.o obj/Explode.o obj/Chicken.o obj/Bullet.o obj/Boss.o obj/testRegression.o -o bin/testRegression 
Global.o : scr/core/Global.h scr/core/Global.cpp
	g++ -Wall -c scr/core/Global.cpp -g -o obj/Global.o
Player.o : scr/core/Player.h scr/core/Player.cpp scr/core/Bullet.h scr/core/Global.h
	g++ -Wall -c scr/core/Player.cpp -g -o obj/Player.o
Gift.o : scr/core/Gift.cpp scr/core/Gift.h scr/core/Global.h
	g++ -Wall -c scr/core/Gift.cpp -g -o obj/Gift.o
Explode.o : scr/core/Explode.h scr/core/Explode.cpp scr/core/Global.h
	g++ -Wall -c scr/core/Explode.cpp -g -o obj/Explode.o
Chicken.o : scr/core/Chicken.h scr/core/Chicken.cpp scr/core/Global.h scr/core/Bullet.h scr/core/Explode.h
	g++ -Wall -c scr/core/Chicken.cpp -g -o obj/Chicken.o
Bullet.o : scr/core/Bullet.h scr/core/Bullet.cpp scr/core/Global.h
	g++ -Wall -c scr/core/Bullet.cpp -g -o obj/Bullet.o
Boss.o : scr/core/Boss.h scr/core/Boss.cpp scr/core/Bullet.h scr/core/Global.h scr/core/Explode.h
	g++ -Wall -c scr/core/Boss.cpp -g -o obj/Boss.o
Base.o : scr/sdl2/Base.h scr/sdl2/Base.cpp scr/core/Boss.h scr/core/Bullet.h scr/core/Chicken.h scr/core/Explode.h scr/core/Gift.h scr/core/Global.h scr/core/Player.h
	g++ -Wall -c scr/sdl2/Base.cpp -g -o obj/Base.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
main.o : scr/sdl2/main.cpp scr/sdl2/Base.h
	g++ -Wall -c scr/sdl2/main.cpp -g -o obj/main.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
testRegression.o : scr/core/testRegression.cpp scr/core/Boss.h scr/core/Bullet.h scr/core/Chicken.h scr/core/Explode.h scr/core/Gift.h scr/core/Global.h scr/core/Player.h
	g++ -Wall -c scr/core/testRegression.cpp -g -o obj/testRegression.o
testRegressionSDL.o : scr/sdl2/testRegressionSDL.cpp scr/sdl2/Base.h
	g++ -Wall -c scr/sdl2/testRegressionSDL.cpp -g -o obj/testRegressionSDL.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
Text.o : scr/txt/Text.cpp scr/txt/GameTXT.h
	g++ -Wall -c scr/txt/Text.cpp -g -o obj/Text.o
GameTXT.o : scr/txt/GameTXT.cpp scr/txt/GameTXT.h
	g++ -Wall -c scr/txt/GameTXT.cpp -g -o obj/GameTXT.o 
clean: 
	rm obj/* bin/* 