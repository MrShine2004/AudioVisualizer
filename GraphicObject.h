#pragma once

#include <windows.h>
#include "stdio.h"
#include "iostream"

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ����� ��� ������ � ����������� ��������
class GraphicObject
{
public:
	// ����������� �� ���������
	GraphicObject();
	// ���������� ���� �������
	void setColor(glm::vec4& color);
	// ���������� ������� �������
	void setPosition(glm::vec3& position);
	void setPosition(float x);
	glm::vec3 getPosition();
	// ���������� ���� �������� � �������� ������������ ��� OY �� ������� �������
	void setAngle(float degree);
	// �������� ��������� ���������
	glm::vec4& getColor();
	glm::mat4& getModelMatrix();
	void setSphearePosition(float a, float b);
	void setSphearePosition2(float a, float b);
	void setSphearePosition3(float a, float b);
	void setPolarPosition(float x, float y);
	void recalculateModelMatrix();
private:
	// ���� �������
	glm::vec3 position;
	glm::vec4 color;
	// ������� ������ (������ ������� � ����������)
	glm::mat4 modelMatrix;
};