#include "Camera.h"

// ����������� �� ���������
Camera::Camera()
{
    position = vec3(1, 1, -216);
    observationPoint = vec3(250, 40, -116);
    dMove = vec3(250, 20, -116);
    distanceToTarget = 700;
    vec3 v1 = position;
    vec3 v2 = vec3(v1.x, 0, v1.z);
    float cos_y = dot(normalize(v1), normalize(v2));
    float cos_x = dot(normalize(v2), vec3(1, 0, 0));
    verticalAngle = 90 - degrees(acos(cos_y));
    horizontalAngle = degrees(acos(cos_x));

    viewMatrix = lookAt(position, observationPoint, vec3(0, 1, 0));
    
}


// ���������� ������� ��������
void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
    projectionMatrix = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

// �������� ������� ��������
glm::mat4& Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

// �������� ������� ����
glm::mat4& Camera::getViewMatrix()
{
    return viewMatrix;
}

// ����������� ������ � ����� ���������� � �������������� ��������� (OXZ)
void Camera::move(float dx, float dz)
{
    dx = dx * moveSpeed;
    dz = dz * moveSpeed;
    float angle = radians(horizontalAngle);
    float angle2 = radians(90 + horizontalAngle);
    dMove += vec3(dx * cos(angle), 0, dx * sin(angle));
    dMove += vec3(dz * cos(angle2), 0, dz * sin(angle2));


    // ������������� ������� ����
    recalculateViewMatrix();
}

// ��������� � �������������� � ������������ ��������� (���� �������� � ��������)
void Camera::rotate(float horizAngle, float vertAngle)
{
    // ���������� �������� ������
    // ������:
    horizontalAngle += horizAngle * rotateSpeed;
    verticalAngle += vertAngle * rotateSpeed;

    if (verticalAngle < 1) {
        verticalAngle = 1;
    }
    if (verticalAngle > 179) {
        verticalAngle = 179;
    }
    // ������������� ������� ����
    recalculateViewMatrix();
}

// ����������/������� ������ �/�� ����� ����������
void Camera::zoom(float dR)
{
    // ���������� ��������� ���������� �� ������ �� ����� ����������
    // ������:
    distanceToTarget += dR * zoomSpeed;
    if (distanceToTarget < 5) {
        distanceToTarget = 5;
    }

    // ������������� ������� ����
    recalculateViewMatrix();
}

float Camera::getZoomSpeed()
{
    return zoomSpeed;
}

float Camera::getMoveSpeed()
{
    return moveSpeed;
}
vec3 Camera::getPosition()
{
    return dMove;
}
void Camera::setMoveSpeed(float d) {
    moveSpeed = moveSpeed+d;
}

// ��������� �����: ����������� ������� ����
void Camera::recalculateViewMatrix()
{
    float rad_v = radians(verticalAngle);
    float rad_h = radians(horizontalAngle);

    position.x = distanceToTarget * sin(rad_v) * cos(rad_h);
    position.y = distanceToTarget * cos(rad_v);
    position.z = distanceToTarget * sin(rad_v) * sin(rad_h);
    position += dMove;
    observationPoint = dMove;
    viewMatrix = lookAt(position, observationPoint, vec3(0, 1, 0));
}


