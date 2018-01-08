#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>


GLuint VAO;
GLuint VBO;

class Shader
{
private:

	static int wysokoscOkna;
	static int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;
	GLuint programZShaderami;

public:
	Shader(void);
	Shader(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	//~Shader(void);
	void stworzenieOkna(int argc, char** argv);
	int inicjalizacjaGlew();
	static void wyswietl();
	void stworzenieVAO();
	void stworzenieVBO();
	void stworzenieProgramu();
	void dodanieDoProgramu(GLuint programZShaderami, const char* teksrShadera, GLenum typShadera);
};

#endif/*SHADER_H*/