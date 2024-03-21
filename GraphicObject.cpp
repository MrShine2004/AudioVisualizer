#include "GraphicObject.h"

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
void GraphicObject::setPosition(glm::vec3& position)
{
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
    position = this->position;
    /*modelMatrix[3][0] = position.x;
    modelMatrix[3][1] = position.y;
    modelMatrix[3][2] = position.z;*/
}

void GraphicObject::setPosition(float x)
{
    modelMatrix[3][1] = x;
}

glm::vec3 GraphicObject::getPosition()
{
    return position;
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
