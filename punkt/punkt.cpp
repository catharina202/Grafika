#include "punkt.h"

Punkt::Punkt()
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

Punkt::Punkt(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Punkt::~Punkt()
{
	//glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &VAO);
}

void Punkt::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);
	glutCreateWindow("punkt");
}

void Punkt::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)
	{
		std::cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << std::endl;
		system("pause");
		exit(1);
	}
}

void  Punkt::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glPointSize(wielkoscPunktu);
	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void Punkt::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	// sprawdzenie nadanego id (nadawane automatycznie)
	std::cout << "VAO: " << VAO << std::endl;
	glBindVertexArray(VAO);
}

void Punkt::stworzenieVBO()
{
	GLfloat Wierzcholki[3] = { 0.0f, 0.0f, 0.0f };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// sprawdzenie nadanego id (nadawane automatycznie)
	std::cout << "VBO: " << VBO << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
	Punkt punkt(786, 1024, 100, 100);

	punkt.stworzenieOkna(argc, argv);
	punkt.inicjalizacjaGlew();
	punkt.stworzenieVAO();
	punkt.stworzenieVBO();
	glutDisplayFunc(punkt.wyswietl);
	// po zamknieciu okna kontrola wraca do programu
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0.2f, 0.1f, 0.0f, 0.0f);

	glutMainLoop();

	//bez glutSetOption() to nie zadziala, nie wejdzie tez program do destruktora
	//system("pause");
	return 0;
}
