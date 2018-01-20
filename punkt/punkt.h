#ifndef PUNKT_H
#define PUNKT_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

GLuint VAO;
GLuint VBO;
GLuint wielkoscPunktu = 10;

class Punkt
{
private:
	int wysokoscOkna;
	int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;

public:
	Punkt();
	Punkt(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	~Punkt(void);
	void stworzenieOkna(int argc, char** argv);
	void inicjalizacjaGlew();
	static void wyswietl();
	void stworzenieVAO();
	void stworzenieVBO();
};

#endif /* PUNKT_H */