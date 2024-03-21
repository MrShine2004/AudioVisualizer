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

// ����� ��� ������ � �������
class Camera
{
public:
	// ����������� �� ���������
	Camera();
	// ���������� ������� ��������
	void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
	// �������� ������� ��������
	glm::mat4& getProjectionMatrix();
	// �������� ������� ����
	glm::mat4& getViewMatrix();
	// ����������� ������ � ����� ���������� � �������������� ��������� (OXZ)
	void move(float dx, float dz);
	// ��������� � �������������� � ������������ ��������� (���� �������� � ��������)
	void rotate(float horizAngle, float vertAngle);
	// ����������/������� ������ �/�� ����� ����������
	void zoom(float dR);
	float getZoomSpeed();
	float getMoveSpeed();
	vec3 getPosition();
	void setMoveSpeed(float d);
private:
	// ����������� ������� ����
	void recalculateViewMatrix();
private:
	glm::mat4 projectionMatrix;  // ������� ��������
	glm::mat4 viewMatrix;        // ������� ����

	glm::vec3 position;          // ������� ������
	glm::vec3 target;            // �����, �� ������� ���������� ������
	glm::vec3 up;                // ����������� "�����" ������

	float horizontalAngle;       // �������������� ���� ������
	float verticalAngle;         // ������������ ���� ������

	vec3 observationPoint;
	vec3 dMove;


	float zoomSpeed = 5;             // �������� ��������� ����
	float moveSpeed = 5;             // �������� �������� ������
	float rotateSpeed = 1;


	float distanceToTarget;      // ���������� �� ������ �� ���� (����� ����������)
};


