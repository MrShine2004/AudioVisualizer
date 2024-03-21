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
#include "Display.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"

extern float FrameTime;
extern int FPS;
extern float simulationTime, tempSimTime ;
extern int OldFPS;
extern vec4 MicroColor; 
extern const int sizeBox;
extern float PositionsMicro[500];
extern int Mode;
extern int SecondMode;
extern bool OutputType;


// ������������ ������ (���� ������ ����)
extern Shader shader;
// ������������ ������
extern Camera camera;
// ������ ����������� �������� ��� ������ �� �����
extern vector<GraphicObject> graphicObjects;
// ������� ��� ������ �������� � ������� ������� ������� (�� -0.5 �� +0.5)
extern void drawBox();
extern void InitializingObjects();


