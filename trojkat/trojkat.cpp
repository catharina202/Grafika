#include "trojkat.h"

int Trojkat::wysokoscOkna;
int Trojkat::szerokoscOkna;


int main(int argc, char** argv)
{

	Trojkat trojkat(786, 1024, 100, 100);
	trojkat.stworzenieOkna(argc, argv);
	trojkat.inicjalizacjaGlew();
	trojkat.stworzenieVAO();
	trojkat.stworzenieVBO();
	glutDisplayFunc(trojkat.wyswietl);

	glClearColor(0.4f, 0.5f, 0.3f, 0.0f);

	glutMainLoop();

	return 0;
}

Trojkat::Trojkat(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Trojkat::Trojkat()
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

void Trojkat::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //bufory
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("trojkat");

}


void Trojkat::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glPointSize(20);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();

}

int Trojkat::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK) {
		std::cerr << "Ne udalo sie zainicjalizowac GLEW.Blad:" << glewGetErrorString(wynik) << std::endl;
		return 1;
		//system("pause");
		//exit(1);
	}
}

void Trojkat::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Trojkat::stworzenieVBO() {
	GLfloat Wierzcholki[9] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f
	};
	//WIERZCHOLKI RYSOWANE COUNTERCLOCKWISE
	GLfloat xCCW[3]={-0.8,0.8,0.0};
	GLfloat yCCW[3]={-0.8,-0.8,0.8};

	//a=1/2 suma do n-1 po i=0(x(i) * y (i+1 mod n) - x(i+1)modn* y(i) 
	//jeœli a> 0 figura PRZODEM
	//		a< 0 figura TY£EM
	// n=3
	GLfloat sumCCW=0;
	for(int i=0; i<2;++i)
	{
		sumCCW+=xCCW[i]*yCCW[(i+1)%3]-xCCW[(i+1)%3]*yCCW[i];
	}
	GLfloat aCCW = sumCW/2;

	glGenBuffers(4, &VBO); //generuje bufor
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);

	//PRZY TYCH USTAWIENIEACH TROJKAT NIE BEDZIE WYSWIETLANY 
	//glCullFace(GL_BACK); // BRAK WYSWIETLANIA PRZODU
	//glEnable(GL_CULL_FACE);
}
