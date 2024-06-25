#pragma once

#include <windows.h>
#include "stdio.h"
#include "iostream"

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// КЛАСС ДЛЯ РАБОТЫ С ГРАФИЧЕСКИМ ОБЪЕКТОМ
class GraphicObject
{
public:
	// конструктор по умолчанию
	GraphicObject();
	// установить цвет объекта
	void setColor(glm::vec4& color);
	// установить позицию объекта
	void setPosition(glm::vec3& position);
	void setPosition(float x);
	glm::vec3 getPosition();
	// установить угол поворота в градусах относительно оси OY по часовой стрелке
	void setAngle(float degree);
	// получить различные параметры
	glm::vec4& getColor();
	glm::mat4& getModelMatrix();
	void setSphearePosition(float a, float b);
	void setSphearePosition2(float a, float b);
	void setSphearePosition3(float a, float b);
	void setPolarPosition(float x, float y);
	void recalculateModelMatrix();
private:
	// цвет объекта
	glm::vec3 position;
	glm::vec4 color;
	// матрица модели (задает позицию и ориентацию)
	glm::mat4 modelMatrix;
};