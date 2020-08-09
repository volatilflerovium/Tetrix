# to run this file:
# $ make -f clock.mk
# $ make -f clock.mk clean

FLAGS = -c -std=c++11
#FLAGS = -c -std=c++1y

tetrix-app : base.o node.o board.o tetromino.o manager.o tetrix.o
	g++ base.o node.o board.o tetromino.o manager.o tetrix.o -o tetrix-app -lsfml-graphics -lsfml-window -lsfml-system

base.o : base.cpp
	g++ ${FLAGS} base.cpp

node.o : node.cpp
	g++ ${FLAGS} node.cpp

board.o : board.cpp
	g++ ${FLAGS} board.cpp

tetromino.o : tetromino.cpp
	g++ ${FLAGS} tetromino.cpp

manager.o : manager.cpp
	g++ ${FLAGS} manager.cpp

tetrix.o : tetrix.cpp
	g++ ${FLAGS} tetrix.cpp

clean :
	rm -f *~ *.o 
	