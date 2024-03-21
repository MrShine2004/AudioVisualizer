#include "Shader.h"
#include <iostream>

using namespace std;
using namespace glm;

//��������� ������

bool Shader::load(std::string veftexShaderFilename, std::string fragmentShaderFilename)
{
	//�������� ���������� ���������� �������
	GLuint vsh = createShaderObject(GL_VERTEX_SHADER, veftexShaderFilename);
	if (vsh == -1) return false;
	//�������� ������������ ���������� �������
	GLuint fsh = createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename);
	if (fsh == -1) return false;

	//�������� ��������� ��������� � ��������
	program = glCreateProgram();
	glAttachShader(program, vsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);

	//�������� ���������� �������� � ����� ��������� �� ������, ���� ����������
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		GLuint count;
		char errorLog[1024];
		glGetProgramInfoLog(program, 1024, (GLsizei*)&count, errorLog);
		cout << "Shader program link error for files \"" << veftexShaderFilename << "\" and \"" << fragmentShaderFilename << "\":" << endl;
		cout << errorLog << endl;

		return false;
	}

	cout << "Shader program link for files \"" << veftexShaderFilename << "\" and \"" << fragmentShaderFilename << "\":" << "has been created with id = " << program << endl;

	return true;
}

//�������������� ������ (������� �������)
void Shader::activate()
{
	glUseProgram(program);
}

//��������� ������ (������������ ������� ��������� ���������)
void Shader::deactivate()
{
	glUseProgram(0);
}


GLuint Shader::createShaderObject(GLenum shaderType, std::string filename)
{
	// ����� ��� �������������
	const int max_buffer_size = 1024 * 10;
	char buffer[max_buffer_size];
	// ��������� ����
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "File \"" << filename << "\" can not be found" << endl;
		return -1;
	}
	// ��������� ���������� �����
	file.getline(buffer, max_buffer_size, 0);
	// �������� �������
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		cout << "Shader object can't be created" << endl;
		return -1;
	}
	// �������� ������ �������
	const char* source_pointer[] = { buffer };
	glShaderSource(shader, 1, source_pointer, 0);
	//cout << buffer;
	// �������������� ��������
	glCompileShader(shader);
	// �������� ���������� �������������� � ����� ���������
	//�� ������, ���� ����������
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		GLuint count;
		glGetShaderInfoLog(shader, max_buffer_size,
			(GLsizei*)&count, buffer);
		cout << "Shader object for file \"" << filename << "\" was compiled with error:" << endl;
		cout << buffer << endl;
		return -1;
	}

	// ���� ��� ���������, ���������� ������������� �������
	return shader;
}

GLuint Shader::getUniformLocation(std::string name)
{
	// ��������, ���� �� ������ � ����
	auto it = uniforms.find(name);
	if (it != uniforms.end())
	{
		// ������ ��� ��� ������ �����, ���������� ���
		return it->second;
	}

	// ������ �� ������ � ����, ����������� OpenGL
	GLuint location = glGetUniformLocation(program, name.c_str());

	// �������� �� ���������� �������
	if (location == GL_INVALID_INDEX)
	{
		std::cerr << "Warning: Uniform variable '" << name << "' not found in shader." << std::endl;
	}
	else
	{
		// ��������� ������ � ���� ��� �������� �������������
		uniforms[name] = location;
	}

	return location;
}

// ����������� ����������� ���������� ������
GLuint Shader::currentProgram = 0;


// ���������� ������ setUniform ��� int
void Shader::setUniform(std::string name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

// ���������� ������ setUniform ��� float
void Shader::setUniform(std::string name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

// ���������� ������ setUniform ��� glm::vec2
void Shader::setUniform(std::string name, glm::vec2& value)
{
	glUniform2fv(getUniformLocation(name), 1, &value[0]);
}

// ���������� ������ setUniform ��� glm::vec4
void Shader::setUniform(std::string name, glm::vec4& value)
{
	glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

// ���������� ������ setUniform ��� glm::mat4
void Shader::setUniform(std::string name, glm::mat4& value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
