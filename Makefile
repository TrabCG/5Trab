CPP = g++
OPTS =-I"/include" -L"/lib" lib/libIrrKlang.so -pthread
GLUT = -lGL -lGLU -lglut
GAMB = && ./trabalhocg
TINY = tinyxml.cpp tinystr.cpp tinyxmlparser.cpp tinyxmlerror.cpp
all:
	$(CPP) ultimoFuckingTrab.cpp -o trabalhocg $(GLUT) $(GAMB)
clean:
	rm trabalhocg