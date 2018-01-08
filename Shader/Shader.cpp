#include "Shader.h"

int Shader::wysokoscOkna;
int Shader::szerokoscOkna;


int main(int argc, char** argv)
{

	Shader shader(786, 1024, 100, 100);
	shader.stworzenieOkna(argc, argv);
	shader.inicjalizacjaGlew();
	shader.stworzenieVAO();
	shader.stworzenieVBO();
	glutDisplayFunc(shader.wyswietl);
	std::cout << "Wersja GL:" << glGetString(GL_VERSION);
	shader.stworzenieProgramu();

	glClearColor(0.0f, 0.5f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}

Shader::Shader(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Shader::Shader()
{
	wysokoscOkna = 768;
	szerokoscOkna = 768;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

void Shader::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //bufory
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("shader");

}


void Shader::wyswietl()
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

int Shader::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK) {
		std::cerr << "Ne udalo sie zainicjalizowac GLEW.Blad:" << glewGetErrorString(wynik) << std::endl;

		//system("pause");
		return 1;
		//system("pause");
	}
}

void Shader::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Shader::stworzenieVBO() {
	//Domyœlne, CounterClockWise
	GLfloat Wierzcholki[9] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &VBO); //generuje bufor
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);
}

void Shader::stworzenieProgramu(){
	programZShaderami = glCreateProgram();
	if (programZShaderami == 0){
		std::cerr << "Blad podczas tworzenia programu" << std::endl;
		system("pause");
		exit(1);
	}
	char* vertexShader =
		"#version 330\n"
		"layout(location=0) in vec3 polozenie;"
		"void main()"
		"{"
		"gl_Position=vec4(0.5*polozenie.x, 0,5*polozenie.y, polozenie.z, 1.0);"
		"}";

	char* fragmentShader =
		"#version 330\n"
		"out vec4 kolor"
		"void main()"
		"{"
		"kolor=vec4(0.8, 0.0, 1.0);"
		"}";
	dodanieDoProgramu(programZShaderami, vertexShader, GL_VERTEX_SHADER);
	dodanieDoProgramu(programZShaderami, fragmentShader, GL_FRAGMENT_SHADER);

	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if(linkowanieOK == GL_FALSE){
		GLint dlugoscLoga = 0;
		glGetShaderiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar>log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas linkowania programu shaderow"<< std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i){
			std::cerr << *i;
			std::cerr << std::endl;
			glDeleteProgram(programZShaderami);
			system("pause");
			exit(1);
		}
	}

	GLint walidacjaOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE){
		GLint dlugoscLoga = 0;
		glGetShaderiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar>log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas walidacji programu shaderow" << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i){
			std::cerr << *i;
			std::cerr << std::endl;
			glDeleteProgram(programZShaderami);
			system("pause");
			exit(1);
		}
	}
	glUseProgram(programZShaderami);
}

void Shader::dodanieDoProgramu(GLuint programZShaderami, const char* tekstShadera, GLenum typShadera){
	GLuint shader = glCreateShader(typShadera);
	GLchar* typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";
	if (shader == 0){
		std::cerr << "Blad podczas towrzenia " << typShaderaTekst << " shadera." << std::endl;
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
	if (kompilacjaOK == GL_FALSE){
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar>log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas kompilacji" << typShaderaTekst << "shadera." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i){
			std::cerr << *i;
			std::cerr << std::endl;
			glDeleteShader(shader);
			system("pause");
			exit(1);
		}
	}
	glAttachShader(programZShaderami,shader);
}