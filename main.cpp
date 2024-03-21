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
#include "Display.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"

#include <Mmsystem.h>
#include <iostream>

using namespace glm;
using namespace std;

HWAVEIN hWaveIn;
WAVEFORMATEX waveform;
WAVEHDR waveHdr;


// ������� ��������� �������� �������� �����
void mouseWheel(int wheel, int direction, int x, int y)
{
    // ����������, �� ������� ���������� ����������/������� ������
    float delta = camera.getZoomSpeed() * -direction;// ...;
    camera.zoom(delta);
}

void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    switch (uMsg)
    {
    case WIM_DATA:
        // ������ ������
        // �� ������ ����� ������������ ������ � waveHdr.lpData
        // MicroColor = vec4(std::abs((float)waveHdr.lpData[0]) / 327.0f, std::abs((float)waveHdr.lpData[1]) / 327.0f, std::abs((float)waveHdr.lpData[2]) / 327.0f, 1);
        //cout << std::abs((float)waveHdr.lpData[0]) / 327.0f << " " << std::abs((float)waveHdr.lpData[1]) / 327.0f << " " << std::abs((float)waveHdr.lpData[2]) / 327.0f << endl;
        if (SecondMode == 8) {
            for (int i = 0; i < sizeBox; i++) {
                PositionsMicro[i] = ((float)waveHdr.lpData[i]);
            }
        }
        if (SecondMode == 9) {
            for (int i = 0; i < sizeBox; i++) {
                PositionsMicro[i] = abs((float)waveHdr.lpData[i]);
            }
        }
        // ��������� ����� ������� � ������� ������� �����
        MMRESULT result = waveInAddBuffer(hwi, &waveHdr, sizeof(WAVEHDR));
        if (result != MMSYSERR_NOERROR) {
            // ��������� ������
        }
        break;
    }
}

void reshape(int w, int h)
{
    // ���������� ����� ������� ���������, ������ ���� ������� ����
    glViewport(0, 0, w, h);
    // ������������� ������� ��������
    camera.setProjectionMatrix(35.0f, (float)w / h, 1.0f, 50000.0f);
}

// �������� �������
void main(int argc, char** argv)
{
    // ������������� ���������� GLUT
    glutInit(&argc, argv);
    // ������������� ������� (������ ������)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    // ���������� � ������ OpenGL (������ 3.3 ��� ��������� �������� �������������)
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    // ������������� ������� ����� ���� ����
    glutInitWindowPosition(300, 100);
    // ������������� ������ ����
    glutInitWindowSize(800, 600);
    // �������� ����
    glutCreateWindow("laba_01");

    // ������������� GLEW 
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Glew error: %s\n", glewGetErrorString(err));
        return;
    }

    // ����������� ������� ������ OpenGL
    printf("OpenGL Version = %s\n\n", glGetString(GL_VERSION));

    // �������� �������
    shader.load("SHADER\\Example.vsh", "SHADER\\Example.fsh");

    InitializingObjects();

    // ������������� ������� �����
    waveform.wFormatTag = WAVE_FORMAT_PCM;
    waveform.nChannels = 1;
    waveform.nSamplesPerSec = 5000;
    waveform.wBitsPerSample = 16;
    waveform.nBlockAlign = waveform.nChannels * waveform.wBitsPerSample / 8;
    waveform.nAvgBytesPerSec = waveform.nSamplesPerSec * waveform.nBlockAlign;
    waveform.cbSize = 0;

    /*
    waveform.wFormatTag = WAVE_FORMAT_PCM;
    waveform.nChannels = 1;
    waveform.nSamplesPerSec = 44100;
    waveform.wBitsPerSample = 16;
    waveform.nBlockAlign = waveform.nChannels * waveform.wBitsPerSample / 8;
    waveform.nAvgBytesPerSec = waveform.nSamplesPerSec * waveform.nBlockAlign;
    waveform.cbSize = 0;
    */


    MMRESULT result = waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD_PTR)&waveInProc, 0, CALLBACK_FUNCTION);
    if (result != MMSYSERR_NOERROR)
    {
        std::cerr << "Failed to open audio device." << std::endl;
        return;
    }

    // ������ ������� �����
    waveHdr.lpData = new char[sizeBox];
    waveHdr.dwBufferLength = sizeBox;
    waveHdr.dwBytesRecorded = 0;
    waveHdr.dwUser = 0;
    waveHdr.dwFlags = 0;
    waveHdr.dwLoops = 0;

    /*
    waveHdr.lpData = new char[4096];
    waveHdr.dwBufferLength = 4096;
    waveHdr.dwBytesRecorded = 0;
    waveHdr.dwUser = 0;
    waveHdr.dwFlags = 0;
    waveHdr.dwLoops = 0;
    */

    result = waveInPrepareHeader(hWaveIn, &waveHdr, sizeof(WAVEHDR));
    if (result != MMSYSERR_NOERROR)
    {
        std::cerr << "Failed to prepare audio header." << std::endl;
        waveInClose(hWaveIn);
        delete[] waveHdr.lpData;
        return;
    }

    result = waveInAddBuffer(hWaveIn, &waveHdr, sizeof(WAVEHDR));
    if (result != MMSYSERR_NOERROR)
    {
        std::cerr << "Failed to add buffer to audio device." << std::endl;
        waveInClose(hWaveIn);
        delete[] waveHdr.lpData;
        return;
    }

    result = waveInStart(hWaveIn);
    if (result != MMSYSERR_NOERROR)
    {
        std::cerr << "Failed to start audio capture." << std::endl;
        waveInClose(hWaveIn);
        delete[] waveHdr.lpData;
        return;
    }

    cout << "\n\nTo change the Mode, press 2/1/0\n";

    cout << "\n\nTo change the Second Mode, press 8/9\n";

    //�-� ��������� ������ ��� �������� ������ ����
    glutMouseWheelFunc(mouseWheel);
    // ������������� �������, ������� ����� ���������� ��� ����������� ����
    glutDisplayFunc(display);
    // ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
    glutReshapeFunc(reshape);
    // ������������� ������� ������� ���������� ������ ���, ����� ��������� �����������
    glutIdleFunc(simulation);
    // �������� ���� ��������� ��������� ��
    glutMainLoop();

    // ��������� ������� ����� ��� ���������� ���������
    result = waveInStop(hWaveIn);
    if (result != MMSYSERR_NOERROR)
    {
        std::cerr << "Failed to stop audio capture." << std::endl;
    }

    result = waveInUnprepareHeader(hWaveIn, &waveHdr, sizeof(WAVEHDR));
    if (result != MMSYSERR_NOERROR)
    {
        std::cerr << "Failed to unprepare audio header." << std::endl;
    }

    waveInClose(hWaveIn);
    cout << "I here" << endl;
    delete[] waveHdr.lpData;
    cout << "And here" << endl;

    return;
}
