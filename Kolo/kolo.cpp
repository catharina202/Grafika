#include "kolo.h"

int Kolo::wysokoscOkna;
int Kolo::szerokoscOkna;


int main(int argc, char** argv)
{

	Kolo kolo(786, 786, 100, 100, 0.5f);
	kolo.stworzenieOkna(argc, argv);
	kolo.inicjalizacjaGlew();
	kolo.stworzenieVAO();
	kolo.stworzenieVBO();
	glutDisplayFunc(kolo.wyswietl);

	glClearColor(0.4f, 0.5f, 0.3f, 0.0f);

	glutMainLoop();

	return 0;
}

Kolo::Kolo(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY, GLfloat promien)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
	this->promien=promien;
}

Kolo::Kolo()
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

void Kolo::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //bufory
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("kolo");

}


void Kolo::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glPointSize(20);
	glDrawArrays(GL_TRIANGLE_FAN, 0,ILOSC_BOKOW+2);

	glutSwapBuffers();

}

int Kolo::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK) {
		std::cerr << "Ne udalo sie zainicjalizowac GLEW.Blad:" << glewGetErrorString(wynik) << std::endl;
		return 1;
		//system("pause");
		//exit(1);
	}
}

void Kolo::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Kolo::stworzenieVBO() {
	GLfloat Wierzcholki[ILOSC_BOKOW+2][3]; 
	Wierzcholki[0][0]=0.0f;
	Wierzcholki[0][1]=0.0f;
	Wierzcholki[0][2]=0.0f;

	GLfloat dwaPI = M_PI *2.0f;
	for (int i=1; i<ILOSC_BOKOW+2;++i)
	{
		Wierzcholki[i][0]=promien*cos(i*dwaPI/ILOSC_BOKOW);
		Wierzcholki[i][1]=promien*sin(i*dwaPI/ILOSC_BOKOW);
		Wierzcholki[i][2]=0.0f;

	}
}
