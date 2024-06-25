#include "Data.h"


float FrameTime = 0;
int FPS = 0;
float simulationTime, tempSimTime = 0;
int OldFPS;
vec4 MicroColor = vec4(0, 0, 0, 1);
int Mode = -1;
int SecondMode = 0;
bool OutputType = 0;
int Recalculate = -1;
const int sizeBox = 4800;
double cutFrq = 1000;
int filterMode = 0;
bool Pictured = 0;
vector<char> visualize(sizeBox);

// используемый шейдер (пока только один)
Shader shader;
// ИСПОЛЬЗУЕМАЯ КАМЕРЫ
Camera camera;
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
vector<GraphicObject> graphicObjects;

void InitializingObjects() 
{
	vec4 color = vec4(1, 0, 0, 1);
	vec4 color2 = vec4(0, 0, 1, 1);
	float ang = 0;
	float y = 0;
	float r = sizeBox;
	for (int i = 0; i < r; i++) {
		GraphicObject obj;
		vec3 pos = vec3(1,1,1);
		obj.setColor(color);
		pos = vec3(-sizeBox/2+i, 1, 1);
		//R^2 = X^2+Y^2
		//vec3 pos = vec3((i%3)*2, 0, ((int)i/3)*2);
		obj.setPosition(pos);
		obj.setAngle(ang);
		graphicObjects.push_back(obj);
	}
}

vec4 Color(int counter) {
	float r = float(waveHdr.lpData[counter]) / 327.0f;
	vec4 MicroColor;
	if (counter % 2 == 0) {
		// Для четных значений counter
		float red = 1.0f - r * 5;          // Красный цвет изменяется от 1 до 0
		float green = r * 10;              // Зеленый цвет изменяется от 0 до 10
		float blue = 1.0f;                 // Синий цвет остается 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	else {
		// Для нечетных значений counter
		float red = r * 5;                 // Красный цвет изменяется от 0 до 5
		float green = 1 - r * 10;          // Зеленый цвет изменяется от 1 до -9
		float blue = 1.0f;                 // Синий цвет остается 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	return MicroColor;
}

vec4 BackgroundColor() {
	// Вычисляем среднюю амплитуду звука в буфере
	float averageAmplitude = 0.0f;
	for (int i = 0; i < sizeBox; ++i) {
		averageAmplitude += std::abs(static_cast<float>(waveHdr.lpData[i]) / 127.0f);
	}
	averageAmplitude /= sizeBox;

	// Используем среднюю амплитуду для определения цвета фона
	float red = averageAmplitude;
	float green = 0.0f;
	float blue = 0.2f + averageAmplitude * 0.3f;  // Темно-синий фон

	// Устанавливаем новый цвет заднего фона
	return vec4(red, green, blue, 1.0f);
}

//vec4 BackgroundColor() {
//	// Вычисляем среднюю амплитуду звука в буфере
//	float averageAmplitude = 0.0f;
//	for (int i = 0; i < sizeBox; ++i) {
//		averageAmplitude += std::abs(static_cast<float>(waveHdr.lpData[i]) / 128.0f);
//	}
//	averageAmplitude /= sizeBox;
//
//	// Используем среднюю амплитуду для определения цвета фона
//	float intensity = 1.0f - averageAmplitude; // Инвертировать амплитуду для интенсивности цвета
//	vec4 backgroundColor = vec4(1-intensity, 1-intensity, 1-intensity, 1.0f); // Белый фон к черному
//
//	return backgroundColor;
//}

vec4 SpaceColor(int counter)
{
	float r = float(waveHdr.lpData[counter]) / 327.0f;
	vec4 MicroColor;

	// Генерация случайных ярких точек
	float brightPoint = fract(sin(dot(vec2(counter), vec2(12.9898, 78.233))) * 43758.5453);
	brightPoint = mix(0.0, 1.0, brightPoint * brightPoint);

	if (counter % 2 == 0 || waveHdr.lpData[counter + 1] == 127) {
		// Для четных значений counter
		float blue = 0.1f + 0.4f * r;  // Градиент от темно-синего к черному
		MicroColor = vec4(0.0f, 0.0f, blue, 1.0f);
	}
	else {
		// Для нечетных значений counter
		float black = 1.0f - r * 0.9f;  // Постепенно изменяющийся к черному цвет
		MicroColor = vec4(black, black, black, 1.0f);
	}

	// Добавление ярких точек на черном фоне
	//
	// 
	// 
	// 
	// if (brightPoint > 0.9) {
	//	MicroColor += vec4(0.8, 0.8, 0.8, 0.0); // Яркая точка
	//}

	return MicroColor;
}





vec4 Color2(int counter) {
	float r = float(waveHdr.lpData[counter]) / 327.0f;
	vec4 MicroColor;
	if (counter % 2 == 0) {
		// Для четных значений counter
		float red = 1.0f;          // Красный цвет изменяется от 1 до 0
		float green = 1.0f;              // Зеленый цвет изменяется от 0 до 10
		float blue = 1.0f - r * 5;                 // Синий цвет остается 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	else {
		// Для нечетных значений counter
		float red = r * 5;                 // Красный цвет изменяется от 0 до 5
		float green = 1 - r * 10;          // Зеленый цвет изменяется от 1 до -9
		float blue = 1.0f;                 // Синий цвет остается 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	return MicroColor;
}
vec4 ColorRadian(int counter) {
	float x = counter;
	float r = float(waveHdr.lpData[counter]) / 327.0f;
    vec4 MicroColor;
    if (counter % 2 == 0) {
        // Для четных значений counter
        float red = 1.0f - r * 10 *cos(x) * 5;          // Красный цвет изменяется от 1 до 0
        float green = r*10 * sin(x) * 10;              // Зеленый цвет изменяется от 0 до 10
        float blue = 1.0f;                 // Синий цвет остается 1
        MicroColor = vec4(red, green, blue, 1.0f);
    }
    else {
        // Для нечетных значений counter
        float red = r * 10 * cos(x) * 5;                 // Красный цвет изменяется от 0 до 5
        float green = 1 - r * 10 * sin(x) * 10;          // Зеленый цвет изменяется от 1 до -9
        float blue = 1.0f;                 // Синий цвет остается 1
        MicroColor = vec4(red, green, blue, 1.0f);
    }
    return MicroColor;
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
			-1, +1, +1, -1, -1, +1, +1, +1, +1,
			+1, +1, +1, -1, -1, +1, +1, -1, +1,
			// задняя грань (два треугольника)
			+1, +1, -1, +1, -1, -1, -1, +1, -1,
			-1, +1, -1, +1, -1, -1, -1, -1, -1,
			// правая грань (два треугольника) 
			+1, -1, +1, +1, -1, -1, +1, +1, +1,
			+1, +1, +1, +1, -1, -1, +1, +1, -1,
			// левая грань (два треугольника)
			-1, +1, +1, -1, +1, -1, -1, -1, +1,
			-1, -1, +1, -1, +1, -1, -1, -1, -1,
			// верхняя грань (два треугольника)
			-1, +1, -1, -1, +1, +1, +1, +1, -1,
			+1, +1, -1, -1, +1, +1, +1, +1, +1,
			// нижняя грань (два треугольника)
			-1, -1, +1, -1, -1, -1, +1, -1, +1,
			+1, -1, +1, -1, -1, -1, +1, -1, -1
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
		VertexCount = 6*6;
		init = false;
	}
	// вывод модели кубика на экран
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}
void drawBox(int length)
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
			// Передняя грань (два треугольника)
			-0.5f, -0.5f, -length, -0.5f, 0.5f, -length, 0.5f, -0.5f, -length,
			0.5f, -0.5f, -length, -0.5f, 0.5f, -length, 0.5f, 0.5f, -length,
			// Задняя грань (два треугольника)
			0.5f, -0.5f, length, 0.5f, 0.5f, length, -0.5f, -0.5f, length,
			-0.5f, -0.5f, length, 0.5f, 0.5f, length, -0.5f, 0.5f, length,
			// Правая грань (два треугольника)
			0.5f, -0.5f, -length, 0.5f, -0.5f, length, 0.5f, 0.5f, -length,
			0.5f, 0.5f, -length, 0.5f, -0.5f, length, 0.5f, 0.5f, length,
			// Левая грань (два треугольника)
			-0.5f, 0.5f, -length, -0.5f, 0.5f, length, -0.5f, -0.5f, -length,
			-0.5f, -0.5f, -length, -0.5f, 0.5f, length, -0.5f, -0.5f, length,
			// Верхняя грань (два треугольника)
			-0.5f, -0.5f, length, -0.5f, -0.5f, -length, 0.5f, -0.5f, length,
			0.5f, -0.5f, length, -0.5f, -0.5f, -length, 0.5f, -0.5f, -length,
			// Нижняя грань (два треугольника)
			-0.5f, 0.5f, -length, -0.5f, 0.5f, length, 0.5f, 0.5f, -length,
			0.5f, 0.5f, -length, -0.5f, 0.5f, length, 0.5f, 0.5f, length
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
		VertexCount = 6 * 6;
		init = false;
	}
	// вывод модели кубика на экран
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}