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

#include "Simulation.h"
#include "Data.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"
extern void display();
extern int getFps();