bulletHell: main.o game.o character.o bullet.o bulletArray.o enemy.o enemyArray.o
	g++ main.o game.o character.o bullet.o bulletArray.o enemy.o enemyArray.o -o bulletHell -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

main.o: main.cpp
	g++ -c main.cpp
game.o: game.cpp
	g++ -c game.cpp
	
character.o: character.cpp
	g++ -c character.cpp
	
bullet.o: bullet.cpp
	g++ -c bullet.cpp
	
bulletArray.o: bulletArray.cpp
	g++ -c bulletArray.cpp
	
enemy.o: enemy.cpp
	g++ -c enemy.cpp

enemyArray.o: enemyArray.cpp
	g++ -c enemyArray.cpp
		
clean:
	rm *.o
	rm bulletHell