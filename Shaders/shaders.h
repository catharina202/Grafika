#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>


GLuint VAO;
GLuint VBO;

class Shaders
{
private:

	static int wysokoscOkna;
	static int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;
	GLuint programZShaderami;

public:
	Shaders(void);
	Shaders(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	//~Punkt(void);
	void stworzenieOkna(int argc, char** argv);
	int inicjalizacjaGlew();
	static void wyswietl();
	void stworzenieVAO();
	void stworzenieVBO();
	void stworzenieProgramu();
	void dodanieDoProgramu(GLuint programZShaderami, const char * tekstShadera, GLenum typShadera);
};

#endif/*SHADERS_H*/