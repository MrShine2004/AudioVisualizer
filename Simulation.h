#pragma once
#include <windows.h>
#include "stdio.h"
#include "iostream"

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Data.h"
#include "Display.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"

extern void simulation();// функция вызывается когда процессор простаивает, т.е. максимально часто
extern float getSimulationTime();
extern void keyboard(float& dx, float& dz);
extern void cameraSimulation();
extern POINT previousMouseXY;
extern POINT currentMouseXY;
extern void mouse(float& rx, float& ry);