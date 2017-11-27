//#include "stdafx.h"
#include "punkt.h"

int Punkt::wysokoscOkna;
int Punkt::szerokoscOkna;

int main(int argc, char** argv)
{
	Punkt punkt(786, 1024, 100, 100);
	punkt.stworzenieOkna(argc, argv);
	glutDisplayFunc(punkt.wyswietl);

	glClearColor(1.0f, 0.8f, 0.9f, 0.0f);

	glutMainLoop();
	return 0;
}

Punkt::Punkt(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Punkt::Punkt()
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

void Punkt::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);
	glutCreateWindow("punkt");
}

void Punkt::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}

void Punkt::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK){
		std::cerr << "Nie udalo sie " << glewGetErrorString(wynik) << std::endl;
		system("pause");
		exit(1);
	}
}

void Punkt::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Punkt::stworzenieVBO()
{
	GLfloat Wierzcholki[3] = { 0.0f, 0.0f, 0.0f };
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);
}