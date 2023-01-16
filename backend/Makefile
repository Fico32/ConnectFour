CXX = g++
CXXFLAGS = -std=c++2a -g -Wall -I./uWebSockets/uSockets/src -flto
OBJECTS = main.o gameboard.o row.o slot.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = connect

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ./uWebSockets/uSockets/*.o -lz -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
