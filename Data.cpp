#include "Data.h"


float FrameTime = 0;
int FPS = 0;
float simulationTime, tempSimTime = 0;
int OldFPS;
vec4 MicroColor = vec4(0, 0, 0, 1);
const int sizeBox = 500;
float PositionsMicro[sizeBox];
int Mode = 0;
int SecondMode = 8;
bool OutputType = 0;

// используемый шейдер (пока только один)
Shader shader;
// ИСПОЛЬЗУЕМАЯ КАМЕРЫ
Camera camera;
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
vector<GraphicObject> graphicObjects;

void InitializingObjects() {
	vec4 color = vec4(1, 0, 0, 1);
	vec4 color2 = vec4(0, 0, 1, 1);
	float ang = 0;
	float y = 0;
	float r = sizeBox;
	for (int i = 0; i <= r; i++) {
		GraphicObject obj;
		vec3 pos = vec3(1,1,1);
		obj.setColor(color);
		pos = vec3(i, 1, 1);
		//R^2 = X^2+Y^2
		//vec3 pos = vec3((i%3)*2, 0, ((int)i/3)*2);
		obj.setPosition(pos);
		obj.setAngle(ang);
		graphicObjects.push_back(obj);
	}
}
// функция вывода кубика с ребрами единичной длины
// каждая координата (x, y, z) меняется от -0.5 до +0.5
void drawBox()
{
	// переменные для вывода объекта (прямоугольника из двух треугольников)
	static GLuint VAO_Index = 0; // индекс VAO-буфера
	static GLuint VBO_Index = 0; // индекс VBO-буфера
	static int VertexCount = 0; // количество вершин
	static bool init = true;
	if (init) {
		// создание и заполнение VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat Verteces[] = {
			// передняя грань (два треугольника)
			-0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5
			//// задняя грань (два треугольника)
			//+0.5, +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5,
			//-0.5, +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
			//// правая грань (два треугольника) 
			//+0.5, -0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5,
			//+0.5, +0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5,
			//// левая грань (два треугольника)
			//-0.5, +0.5, +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5,
			//-0.5, -0.5, +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5,
			//// верхняя грань (два треугольника)
			//-0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, -0.5,
			//+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
			//// нижняя грань (два треугольника)
			//-0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, +0.5,
			//+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);
		// создание VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// инициализация VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		int location = 0;
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);

		// "отвязка" буфера VAO на всякий случай, чтоб случайно не испортить
		glBindVertexArray(0);
		// указание количество вершин
		VertexCount = 6;
		init = false;
	}
	// вывод модели кубика на экран
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}
