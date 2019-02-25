# to run this file:
# $ make -f clock.mk
# $ make -f clock.mk clean

FLAGS = -c -std=c++11
#FLAGS = -c -std=c++1y

tetrix-app : base.o tetrix.o
	g++ base.o tetrix.o -o tetrix-app -lsfml-graphics -lsfml-window -lsfml-system

base.o : base.cpp
	g++ ${FLAGS} base.cpp

tetrix.o : tetrix.cpp
	g++ ${FLAGS} tetrix.cpp

clean :
	rm -f *~ tetrix.o base.o manager.o
	