#pragma once
#include <windows.h>
#include "stdio.h"
#include "iostream"

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "Simulation.h"
#include "Display.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "Data.h"




extern HWAVEIN hWaveIn;
extern WAVEFORMATEX waveform;
extern WAVEHDR waveHdr;


extern void playAudioFromBuffer(WAVEHDR Buffer);
extern MMRESULT result;
// Инициализация структуры для буфера с аудиоданными
extern WAVEHDR waveOutHdr;
// Открытие устройства воспроизведения
extern HWAVEOUT hWaveOut;
// Определение структуры для воспроизведения звука
extern WAVEFORMATEX waveFormat;

extern bool Out;
void applyButterworthFilter(WAVEHDR& waveHdr, const std::vector<double>& bCoeffs, const std::vector<double>& aCoeffs);

void applyKIHFilter(WAVEHDR& waveHdr, const std::vector<double>& bCoeffs);