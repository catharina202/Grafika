#include "Kwadrat.h"

int Kwadrat::wysokoscOkna;
int Kwadrat::szerokoscOkna;


int main(int argc, char** argv)
{

	Kwadrat punkt(786, 1024, 100, 100);
	punkt.stworzenieOkna(argc, argv);
	punkt.inicjalizacjaGlew();
	punkt.stworzenieVAO();
	punkt.stworzenieVBO();
	glutDisplayFunc(punkt.wyswietl);

	glClearColor(0.0f, 0.5f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}

Kwadrat::Kwadrat(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Kwadrat::Kwadrat()
{
	wysokoscOkna = 768;
	szerokoscOkna = 768;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

void Kwadrat::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //bufory
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("punkt");

}


void Kwadrat::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//glPointSize(10);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutSwapBuffers();

}

int Kwadrat::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK) {
		std::cerr << "Ne udalo sie zainicjalizowac GLEW.Blad:" << glewGetErrorString(wynik) << std::endl;

		//system("pause");
		return 1;
		//system("pause");
	}
}

void Kwadrat::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Kwadrat::stworzenieVBO() {
	//Domyœlne, CounterClockWise
	GLfloat Wierzcholki[18] = {
		0.8f, 0.8f, 0.0f,
		0.8f, -0.8f, -0.0f,
		-0.8f, 0.8f, 0.0f,

		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		-0.8f, 0.8f, 0.0f,
	};

	glGenBuffers(1, &VBO); //generuje bufor
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);
}
