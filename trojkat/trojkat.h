#ifndef TROJKAT_H
#define TROJKAT_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>


GLuint VAO;
GLuint VBO;

class Trojkat
{
private:

	static int wysokoscOkna;
	static int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;

public:
	Trojkat(void);
	Trojkat(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	//~Trojkat(void);
	void stworzenieOkna(int argc, char** argv);
	int inicjalizacjaGlew();
	static void wyswietl();
	void stworzenieVAO();
	void stworzenieVBO();
};

#endif/*TROJKAT_H*/