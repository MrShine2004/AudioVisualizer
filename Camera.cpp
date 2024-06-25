#include "Camera.h"

// КОНСТРУКТОР ПО УМОЛЧАНИЮ
Camera::Camera()
{
    position = vec3(1, 1, -2316);
    observationPoint = vec3(0, 0, -2316);
    dMove = vec3(0, 0, -216);
    distanceToTarget = 1000;
    vec3 v1 = position;
    vec3 v2 = vec3(v1.x, 0, v1.z);
    float cos_y = dot(normalize(v1), normalize(v2));
    float cos_x = dot(normalize(v2), vec3(1, 0, 0));
    verticalAngle = 90 - degrees(acos(cos_y));
    horizontalAngle = degrees(acos(cos_x));

    viewMatrix = lookAt(position, observationPoint, vec3(0, 1, 0));
    
}


// УСТАНОВИТЬ МАТРИЦУ ПРОЕКЦИИ
void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
    projectionMatrix = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

// ПОЛУЧИТЬ МАТРИЦУ ПРОЕКЦИИ
glm::mat4& Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

// ПОЛУЧИТЬ МАТРИЦУ ВИДА
glm::mat4& Camera::getViewMatrix()
{
    return viewMatrix;
}

// ПЕРЕДВИНУТЬ КАМЕРУ И ТОЧКУ НАБЛЮДЕНИЯ В ГОРИЗОНТАЛЬНОЙ ПЛОСКОСТИ (OXZ)
void Camera::move(float dx, float dz)
{
    dx = dx * moveSpeed;
    dz = dz * moveSpeed;
    float angle = radians(horizontalAngle);
    float angle2 = radians(90 + horizontalAngle);
    dMove += vec3(dx * cos(angle), 0, dx * sin(angle));
    dMove += vec3(dz * cos(angle2), 0, dz * sin(angle2));


    // Пересчитываем матрицу вида
    recalculateViewMatrix();
}

void Camera::move(float dy)
{
    dy = dy * moveSpeed;

    // Движение по вертикали (вдоль оси y)
    dMove += vec3(0, dy, 0);

    // Пересчитываем матрицу вида
    recalculateViewMatrix();
}


// ПОВЕРНУТЬ В ГОРИЗОНТАЛЬНОЙ И ВЕРТИКАЛЬНОЙ ПЛОСКОСТИ (УГОЛ ЗАДАЕТСЯ В ГРАДУСАХ)
void Camera::rotate(float horizAngle, float vertAngle)
{
    // Реализация поворота камеры
    // Пример:
    horizontalAngle += horizAngle * rotateSpeed;
    verticalAngle += vertAngle * rotateSpeed;

    if (verticalAngle < 1) {
        verticalAngle = 1;
    }
    if (verticalAngle > 179) {
        verticalAngle = 179;
    }
    // Пересчитываем матрицу вида
    recalculateViewMatrix();
}

void Camera::center()
{
    // Реализация поворота камеры
    // Пример:
    horizontalAngle = 90;
    verticalAngle = 90;

    if (verticalAngle < 1) {
        verticalAngle = 1;
    }
    if (verticalAngle > 179) {
        verticalAngle = 179;
    }
    // Пересчитываем матрицу вида
    recalculateViewMatrix();
}

// ПРИБЛИЗИТЬ/УДАЛИТЬ КАМЕРУ К/ОТ ТОЧКИ НАБЛЮДЕНИЯ
void Camera::zoom(float dR)
{
    // Реализация изменения расстояния от камеры до точки наблюдения
    // Пример:
    distanceToTarget += dR * zoomSpeed;
    if (distanceToTarget < 5) {
        distanceToTarget = 5;
    }

    // Пересчитываем матрицу вида
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

// ПРИВАТНЫЙ МЕТОД: ПЕРЕСЧИТАТЬ МАТРИЦУ ВИДА
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


