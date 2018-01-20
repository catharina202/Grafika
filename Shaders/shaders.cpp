#include "shaders.h"

int Shaders::wysokoscOkna;
int Shaders::szerokoscOkna;


int main(int argc, char** argv)
{

	Shaders punkt(786, 1024, 100, 100);
	punkt.stworzenieOkna(argc, argv);
	punkt.inicjalizacjaGlew();
	punkt.stworzenieVAO();
	punkt.stworzenieVBO();
	glutDisplayFunc(punkt.wyswietl);
	std::cout << "Wersja GL: " << glGetString(GL_VERSION);
	punkt.stworzenieProgramu();

	glClearColor(0.4f, 0.6f, 0.5f, 0.9f);

	glutMainLoop();

	return 0;
}

Shaders::Shaders(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Shaders::Shaders()
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

void Shaders::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //bufory
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shaders");

}


void Shaders::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glPointSize(10);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();

}

int Shaders::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK) {
		std::cerr << "Ne udalo sie zainicjalizowac GLEW.Blad:" << glewGetErrorString(wynik) << std::endl;

		//system("pause");
		return 1;
		//system("pause");
	}
}

void Shaders::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Shaders::stworzenieVBO() {
	//Domyœlne, CounterClockWise
	GLfloat Wierzcholki[9] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	//wierzcholki rysowane CounterClockWise
	//GLfloat xCCW[3] = { -0.8, 0.8, 0.0 };
	//GLfloat yCCW[3] = { -0.8, -0.8, 0.8 };

	//glFrontFace() - funkcja do zmieniania tego czy wyœwietlaæ CCW czy CW(clock wise)
	//glFrontFace(GL_CW) - w³aœnie prze³¹czenie na wyœwietlanie CW
	//glCullFace() - funkcja do wy³¹czania wyœwietlania przodu figury czy nie, by móc u¿yæ trzeba odpaliæ glEnable(GL_CULL_FACE)



	glGenBuffers(1, &VBO); //generuje bufor
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);
}

void Shaders::stworzenieProgramu() {
	programZShaderami = glCreateProgram();

	if (programZShaderami == 0)
	{
		std::cerr << "B³¹d podczas tworzenia programu shaderów" << std::endl;

		system("pause");
		exit(1);
	}
	char * vertexShader =
		"#version 330\n"
		"layout(location =0) in vec3 polozenie;"
		"void main()"
		"{"
		"gl_Position = vec4(0.5 * polozenie.x, 0.5* polozenie.y, polozenie.z,1.0);"
		"};";

	char * fragmentShader =
		"#version 330\n"
		"out vec4 kolor;"
		"void main()"
		"{"
		"kolor= vec4(0.8,0.8,0.0,1.0);"
		"};";

	dodanieDoProgramu(programZShaderami, vertexShader, GL_VERTEX_SHADER);
	dodanieDoProgramu(programZShaderami, fragmentShader, GL_FRAGMENT_SHADER);

	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if (linkowanieOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector <GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);

		std::cerr << "B³¹d podczas linkowania programu shadera: " << std::endl;

		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}
	
	GLint walidacjaOK = 0;
	glValidateProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector <GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);

		std::cerr << "B³¹d podczas walidowania programu shadera: " << std::endl;

		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}
	glUseProgram(programZShaderami);
}

void Shaders::dodanieDoProgramu(GLuint programZShaderami, const char * tekstShadera, GLenum typShadera)
{
	GLuint shader = glCreateShader(typShadera);
	//35633 - > vertex shader, 35632 - > fragment
	GLchar * typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";
	if (shader == 0)
	{
		std::cerr << "B³¹d podczas tworzenia shadera: " <<typShaderaTekst<< std::endl;

		system("pause");
		exit(1);
	}



	const GLchar * tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);
	glCompileShader(shader);
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);
	if (kompilacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector <GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << "B³¹d podczas kompilacji shadera: " << typShaderaTekst << std::endl;

		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteShader(shader);
		system("pause");
		exit(1);
	}
	glAttachShader(programZShaderami, shader);
}