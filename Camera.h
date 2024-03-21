#pragma once

#include <windows.h>
#include "stdio.h"
#include "iostream"

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>

using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class Camera
{
public:
	// конструктор по умолчанию
	Camera();
	// установить матрицу проекции
	void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
	// получить матрицу проекции
	glm::mat4& getProjectionMatrix();
	// получить матрицу вида
	glm::mat4& getViewMatrix();
	// передвинуть камеру и точку наблюдения в горизонтальной плоскости (OXZ)
	void move(float dx, float dz);
	// повернуть в горизонтальной и вертикальной плоскости (угол задается в градусах)
	void rotate(float horizAngle, float vertAngle);
	// приблизить/удалить камеру к/от точки наблюдения
	void zoom(float dR);
	float getZoomSpeed();
	float getMoveSpeed();
	vec3 getPosition();
	void setMoveSpeed(float d);
private:
	// пересчитать матрицу вида
	void recalculateViewMatrix();
private:
	glm::mat4 projectionMatrix;  // Матрица проекции
	glm::mat4 viewMatrix;        // Матрица вида

	glm::vec3 position;          // Позиция камеры
	glm::vec3 target;            // Точка, на которую направлена камера
	glm::vec3 up;                // Направление "вверх" камеры

	float horizontalAngle;       // Горизонтальный угол обзора
	float verticalAngle;         // Вертикальный угол обзора

	vec3 observationPoint;
	vec3 dMove;


	float zoomSpeed = 5;             // Скорость изменения зума
	float moveSpeed = 5;             // Скорость движения камеры
	float rotateSpeed = 1;


	float distanceToTarget;      // Расстояние от камеры до цели (точки наблюдения)
};


