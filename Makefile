all: spacemonkeys

spacemonkeys: main.o button.o star_cluster.o level.o star_system.o particle.o auxiliary_functions.o
	g++ main.o button.o star_cluster.o level.o star_system.o particle.o auxiliary_functions.o -o spacemonkeys -lsfml-graphics -lsfml-window -lsfml-system -no-pie

main.o: main.cpp button.cpp star_cluster.cpp level.cpp star_system.cpp particle.cpp
	g++ -c main.cpp button.cpp star_cluster.cpp level.cpp star_system.cpp particle.cpp

button.o: button.cpp button.h
	g++ -c button.cpp

star_cluster.o: star_cluster.cpp star_system.cpp auxiliary_functions.cpp star_cluster.h
	g++ -c star_cluster.cpp star_system.cpp auxiliary_functions.cpp

level.o: level.cpp particle.cpp auxiliary_functions.cpp level.h
	g++ -c level.cpp particle.cpp auxiliary_functions.cpp

star_system.o: star_system.cpp star_system.h
	g++ -c star_system.cpp

particle.o: particle.cpp particle.h
	g++ -c particle.cpp

auxiliary_functions.o: auxiliary_functions.cpp auxiliary_functions.h
	g++ -c auxiliary_functions.cpp

clean:
	rm -f *.o spacemonkeys
