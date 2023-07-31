Ass4: Map.h Robot.h Game.h Map.o Robot.o Game.o runGame.o
	g++ Map.o Robot.o Game.o runGame.o -o Ass4

Map.o: Map.h
	g++ -c Map.cpp

Robot.o: Robot.h
	g++ -c Robot.cpp

Game.o: Map.h Robot.h Game.h
	g++ -c Game.cpp
	
runGame.o: Game.h
	g++ -c runGame.cpp

clean :
	rm -f *.o
