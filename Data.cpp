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

// ������������ ������ (���� ������ ����)
Shader shader;
// ������������ ������
Camera camera;
// ������ ����������� �������� ��� ������ �� �����
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
		// ��� ������ �������� counter
		float red = 1.0f - r * 5;          // ������� ���� ���������� �� 1 �� 0
		float green = r * 10;              // ������� ���� ���������� �� 0 �� 10
		float blue = 1.0f;                 // ����� ���� �������� 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	else {
		// ��� �������� �������� counter
		float red = r * 5;                 // ������� ���� ���������� �� 0 �� 5
		float green = 1 - r * 10;          // ������� ���� ���������� �� 1 �� -9
		float blue = 1.0f;                 // ����� ���� �������� 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	return MicroColor;
}

vec4 BackgroundColor() {
	// ��������� ������� ��������� ����� � ������
	float averageAmplitude = 0.0f;
	for (int i = 0; i < sizeBox; ++i) {
		averageAmplitude += std::abs(static_cast<float>(waveHdr.lpData[i]) / 127.0f);
	}
	averageAmplitude /= sizeBox;

	// ���������� ������� ��������� ��� ����������� ����� ����
	float red = averageAmplitude;
	float green = 0.0f;
	float blue = 0.2f + averageAmplitude * 0.3f;  // �����-����� ���

	// ������������� ����� ���� ������� ����
	return vec4(red, green, blue, 1.0f);
}

//vec4 BackgroundColor() {
//	// ��������� ������� ��������� ����� � ������
//	float averageAmplitude = 0.0f;
//	for (int i = 0; i < sizeBox; ++i) {
//		averageAmplitude += std::abs(static_cast<float>(waveHdr.lpData[i]) / 128.0f);
//	}
//	averageAmplitude /= sizeBox;
//
//	// ���������� ������� ��������� ��� ����������� ����� ����
//	float intensity = 1.0f - averageAmplitude; // ������������� ��������� ��� ������������� �����
//	vec4 backgroundColor = vec4(1-intensity, 1-intensity, 1-intensity, 1.0f); // ����� ��� � �������
//
//	return backgroundColor;
//}

vec4 SpaceColor(int counter)
{
	float r = float(waveHdr.lpData[counter]) / 327.0f;
	vec4 MicroColor;

	// ��������� ��������� ����� �����
	float brightPoint = fract(sin(dot(vec2(counter), vec2(12.9898, 78.233))) * 43758.5453);
	brightPoint = mix(0.0, 1.0, brightPoint * brightPoint);

	if (counter % 2 == 0 || waveHdr.lpData[counter + 1] == 127) {
		// ��� ������ �������� counter
		float blue = 0.1f + 0.4f * r;  // �������� �� �����-������ � �������
		MicroColor = vec4(0.0f, 0.0f, blue, 1.0f);
	}
	else {
		// ��� �������� �������� counter
		float black = 1.0f - r * 0.9f;  // ���������� ������������ � ������� ����
		MicroColor = vec4(black, black, black, 1.0f);
	}

	// ���������� ����� ����� �� ������ ����
	//
	// 
	// 
	// 
	// if (brightPoint > 0.9) {
	//	MicroColor += vec4(0.8, 0.8, 0.8, 0.0); // ����� �����
	//}

	return MicroColor;
}





vec4 Color2(int counter) {
	float r = float(waveHdr.lpData[counter]) / 327.0f;
	vec4 MicroColor;
	if (counter % 2 == 0) {
		// ��� ������ �������� counter
		float red = 1.0f;          // ������� ���� ���������� �� 1 �� 0
		float green = 1.0f;              // ������� ���� ���������� �� 0 �� 10
		float blue = 1.0f - r * 5;                 // ����� ���� �������� 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	else {
		// ��� �������� �������� counter
		float red = r * 5;                 // ������� ���� ���������� �� 0 �� 5
		float green = 1 - r * 10;          // ������� ���� ���������� �� 1 �� -9
		float blue = 1.0f;                 // ����� ���� �������� 1
		MicroColor = vec4(red, green, blue, 1.0f);
	}
	return MicroColor;
}
vec4 ColorRadian(int counter) {
	float x = counter;
	float r = float(waveHdr.lpData[counter]) / 327.0f;
    vec4 MicroColor;
    if (counter % 2 == 0) {
        // ��� ������ �������� counter
        float red = 1.0f - r * 10 *cos(x) * 5;          // ������� ���� ���������� �� 1 �� 0
        float green = r*10 * sin(x) * 10;              // ������� ���� ���������� �� 0 �� 10
        float blue = 1.0f;                 // ����� ���� �������� 1
        MicroColor = vec4(red, green, blue, 1.0f);
    }
    else {
        // ��� �������� �������� counter
        float red = r * 10 * cos(x) * 5;                 // ������� ���� ���������� �� 0 �� 5
        float green = 1 - r * 10 * sin(x) * 10;          // ������� ���� ���������� �� 1 �� -9
        float blue = 1.0f;                 // ����� ���� �������� 1
        MicroColor = vec4(red, green, blue, 1.0f);
    }
    return MicroColor;
}





// ������� ������ ������ � ������� ��������� �����
// ������ ���������� (x, y, z) �������� �� -0.5 �� +0.5
void drawBox()
{
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static GLuint VAO_Index = 0; // ������ VAO-������
	static GLuint VBO_Index = 0; // ������ VBO-������
	static int VertexCount = 0; // ���������� ������
	static bool init = true;
	if (init) {
		// �������� � ���������� VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat Verteces[] = {
			// �������� ����� (��� ������������)
			-1, +1, +1, -1, -1, +1, +1, +1, +1,
			+1, +1, +1, -1, -1, +1, +1, -1, +1,
			// ������ ����� (��� ������������)
			+1, +1, -1, +1, -1, -1, -1, +1, -1,
			-1, +1, -1, +1, -1, -1, -1, -1, -1,
			// ������ ����� (��� ������������) 
			+1, -1, +1, +1, -1, -1, +1, +1, +1,
			+1, +1, +1, +1, -1, -1, +1, +1, -1,
			// ����� ����� (��� ������������)
			-1, +1, +1, -1, +1, -1, -1, -1, +1,
			-1, -1, +1, -1, +1, -1, -1, -1, -1,
			// ������� ����� (��� ������������)
			-1, +1, -1, -1, +1, +1, +1, +1, -1,
			+1, +1, -1, -1, +1, +1, +1, +1, +1,
			// ������ ����� (��� ������������)
			-1, -1, +1, -1, -1, -1, +1, -1, +1,
			+1, -1, +1, -1, -1, -1, +1, -1, -1
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);
		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// ������������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		int location = 0;
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);

		// "�������" ������ VAO �� ������ ������, ���� �������� �� ���������
		glBindVertexArray(0);
		// �������� ���������� ������
		VertexCount = 6*6;
		init = false;
	}
	// ����� ������ ������ �� �����
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}
void drawBox(int length)
{
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static GLuint VAO_Index = 0; // ������ VAO-������
	static GLuint VBO_Index = 0; // ������ VBO-������
	static int VertexCount = 0; // ���������� ������
	static bool init = true;
	if (init) {
		// �������� � ���������� VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat Verteces[] = {
			// �������� ����� (��� ������������)
			-0.5f, -0.5f, -length, -0.5f, 0.5f, -length, 0.5f, -0.5f, -length,
			0.5f, -0.5f, -length, -0.5f, 0.5f, -length, 0.5f, 0.5f, -length,
			// ������ ����� (��� ������������)
			0.5f, -0.5f, length, 0.5f, 0.5f, length, -0.5f, -0.5f, length,
			-0.5f, -0.5f, length, 0.5f, 0.5f, length, -0.5f, 0.5f, length,
			// ������ ����� (��� ������������)
			0.5f, -0.5f, -length, 0.5f, -0.5f, length, 0.5f, 0.5f, -length,
			0.5f, 0.5f, -length, 0.5f, -0.5f, length, 0.5f, 0.5f, length,
			// ����� ����� (��� ������������)
			-0.5f, 0.5f, -length, -0.5f, 0.5f, length, -0.5f, -0.5f, -length,
			-0.5f, -0.5f, -length, -0.5f, 0.5f, length, -0.5f, -0.5f, length,
			// ������� ����� (��� ������������)
			-0.5f, -0.5f, length, -0.5f, -0.5f, -length, 0.5f, -0.5f, length,
			0.5f, -0.5f, length, -0.5f, -0.5f, -length, 0.5f, -0.5f, -length,
			// ������ ����� (��� ������������)
			-0.5f, 0.5f, -length, -0.5f, 0.5f, length, 0.5f, 0.5f, -length,
			0.5f, 0.5f, -length, -0.5f, 0.5f, length, 0.5f, 0.5f, length
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);
		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// ������������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		int location = 0;
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);

		// "�������" ������ VAO �� ������ ������, ���� �������� �� ���������
		glBindVertexArray(0);
		// �������� ���������� ������
		VertexCount = 6 * 6;
		init = false;
	}
	// ����� ������ ������ �� �����
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}