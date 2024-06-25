#include "GraphicObject.h"
using namespace glm;
// Реализация конструктора по умолчанию
GraphicObject::GraphicObject()
{
    // Инициализация цвета и матрицы модели
    color = glm::vec4(1.0f); // Белый цвет по умолчанию
    modelMatrix = glm::mat4(1.0f); // Единичная матрица по умолчанию
}

// Реализация метода setColor
void GraphicObject::setColor(glm::vec4& color)
{
    this->color = color;
}

// Реализация метода setPosition
void GraphicObject::setPosition(glm::vec3& pos)
{
    modelMatrix = glm::translate(glm::mat4(1.0f), pos);
    position = pos;
    /*modelMatrix[3][0] = position.x;
    modelMatrix[3][1] = position.y;
    modelMatrix[3][2] = position.z;*/
}

void GraphicObject::setPosition(float x)
{
    //modelMatrix = glm::translate(glm::mat4(1.0f), vec3(x, position.y, position.z));
    modelMatrix[3][1] = x;
}

glm::vec3 GraphicObject::getPosition()
{
    return position;
}

void GraphicObject::setSphearePosition(float a, float b)
{
    float radius = 300;
    glm::vec3 PositionThis = glm::vec3(
        radius * sin(a) * cos(b),
        radius * sin(a) * sin(b),
        radius * cos(a)
    );
    modelMatrix = glm::translate(glm::mat4(1.0f), PositionThis);
    //glm::mat4 r = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
    //modelMatrix = t * s * r;
    //return position;
}
void GraphicObject::setSphearePosition2(float a, float b)
{
    float radius = 3;
    glm::vec3 PositionThis = glm::vec3(
        a * radius * sin(b) * cos(a),
        a * radius * sin(b) * sin(a),
        a * radius * cos(b)
    );
    modelMatrix = glm::translate(glm::mat4(1.0f), PositionThis);
    //glm::mat4 r = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
    //modelMatrix = t * s * r;
    //return position;
}

void GraphicObject::setSphearePosition3(float a, float b)
{
    float radius = 3;
    glm::vec3 PositionThis = glm::vec3(
        a * radius * sin(b) * cos(a),
        a * radius * sin(b) * sin(a),
        0//b*10000//0//a * radius * cos(b)
    );
    modelMatrix = glm::translate(glm::mat4(1.0f), PositionThis);
    //glm::mat4 r = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
    //modelMatrix = t * s * r;
    //return position;
}

void GraphicObject::setPolarPosition(float x, float y) {
    //float radius = sqrt(x * x + y * y); // Рассчитываем радиус как расстояние от начала координат до точки (x, y)
    //float theta = atan2(y, x); // Рассчитываем угол theta как арктангенс отношения y к x

    // Теперь у нас есть радиус и угол, определяющие положение точки в полярной системе координат.
    // Можно использовать эти значения для установки позиции объекта.

    // Пример кода для установки позиции объекта в полярной системе координат:
    // Так как в задании используется переменная a для радиуса (обычно используется для угла), здесь назовем переменные по-другому:
    glm::vec3 position = glm::vec3(
        y*10*cos(x), // x координата в декартовой системе
        y*10*sin(x), // y координата в декартовой системе
        0.0f // z координата, поскольку мы работаем в 2D
    );
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
}

// Реализация метода setAngle
void GraphicObject::setAngle(float degree)
{
    //modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix[0][0] = cos(degree);
    modelMatrix[0][2] = sin(degree);
    modelMatrix[2][0] = -sin(degree);
    modelMatrix[2][2] = cos(degree);
}

// Реализация метода getColor
glm::vec4& GraphicObject::getColor()
{
    return color;
}

// Реализация метода getModelMatrix
glm::mat4& GraphicObject::getModelMatrix()
{
    return modelMatrix;
}

void GraphicObject::recalculateModelMatrix()
{
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
}
