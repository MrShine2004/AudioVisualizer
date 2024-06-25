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
#include "Audio.h"

#include <Mmsystem.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>

using namespace glm;
using namespace std;



// функция обработки вращения колесика мышки
void mouseWheel(int wheel, int direction, int x, int y)
{
    // определяем, на сколько необходимо приблизить/удалить камеру
    float delta = camera.getZoomSpeed() * -direction;// ...;
    camera.zoom(delta);
}

void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    switch (uMsg)
    {
    case WIM_DATA:
        // MicroColor = vec4(std::abs((float)waveHdr.lpData[0]) / 327.0f, std::abs((float)waveHdr.lpData[1]) / 327.0f, std::abs((float)waveHdr.lpData[2]) / 327.0f, 1);
        //cout << std::abs((float)waveHdr.lpData[0]) / 327.0f << " " << std::abs((float)waveHdr.lpData[1]) / 327.0f << " " << std::abs((float)waveHdr.lpData[2]) / 327.0f << endl;
        /*float max = 0;
        float min = 0;
        for (int i = 0; i < waveHdr.dwBytesRecorded; i++)
        {
            if (max < waveHdr.lpData[i])
                max = waveHdr.lpData[i];
            if (min > waveHdr.lpData[i])
                min = waveHdr.lpData[i];
        }
        cout << max << " " << min << endl;*/
        // Применяем фильтр ФВЧ к данным звукового буфера

               //waveHdr.lpData[i] = 0;//waveHdr.lpData[i-1];

        if (SecondMode == 8) 
        {

        }   
        if (SecondMode == 9) 
        {
            //applyButterworthFilter(cutFrq, 4);
            // Коэффициенты фильтра Баттерворта
            //std::vector<double> bCoeffs = { 0.6992, -5.5937, 19.5780, -39.1559, 48.9449, -39.1559, 19.5780, -5.5937, 0.6992 };
            //std::vector<double> aCoeffs = { 1.0000, -7.2852, 23.2495, -42.4501, 48.4994, -35.5033, 16.2615, -4.2607, 0.4889 };


            /*std::vector<double> bCoeffs = { 0.0016, 0.0065, 0.0097, 0.0065, 0.0016 };
            std::vector<double> aCoeffs = { 1.0000, -2.8072, 3.0833, -1.5484, 0.2982 };*/

            //std::vector<double> bCoeffs = { 0.0081, 0.0242, 0.0242, 0.0081 };
            //std::vector<double> aCoeffs = { 1.0000, -2.0870, 1.5466, -0.3950 };

            std::vector<double> bCoeffs = { 0.0016, 0.0065, 0.0097, 0.0065, 0.0016 };
            std::vector<double> aCoeffs = { 1.0000, -2.8072, 3.0833, -1.5484, 0.2982 };

            std::vector<double> bCoeffs2 = {
                0.0016, 0.0001, -0.0011, -0.0027, -0.0041, -0.0041, -0.0021, 0.0020, 0.0072, 0.0115, 0.0125,
                0.0082, -0.0015, -0.0148, -0.0273, -0.0331, -0.0270, -0.0056, 0.0305, 0.0765, 0.1239, 0.1631,
                0.1852, 0.1852, 0.1631, 0.1239, 0.0765, 0.0305, -0.0056, -0.0270, -0.0331, -0.0273, -0.0148,
                -0.0015, 0.0082, 0.0125, 0.0115, 0.0072, 0.0020, -0.0021, -0.0041, -0.0041, -0.0027, -0.0011,
                0.0001, 0.0016
            };


            // Применяем фильтр Баттерворта к входному сигналу
            if (filterMode == 0)
            {
                applyButterworthFilter(waveHdr, bCoeffs, aCoeffs);
            }

            if (filterMode == 1)
            {
                applyKIHFilter(waveHdr, bCoeffs2);
            }
            //applyHighPassFilterToBuffer(waveHdr.lpData, waveHdr.dwBytesRecorded, 44100, cutFrq);
        }
        for (int i = 0; i < waveHdr.dwBytesRecorded; ++i) {
            visualize[i] = waveHdr.lpData[i];
        }
        Pictured = 0;
        if (Out) {
            playAudioFromBuffer(waveHdr);
        }
        MMRESULT result = waveInAddBuffer(hwi, &waveHdr, sizeof(WAVEHDR));
        if (result != MMSYSERR_NOERROR) {
            
        }
        break;
    }
}



IAudioClient* pAudioClient = nullptr;

void CALLBACK AudioCaptureCallback(HRESULT hr, DWORD flags, DWORD64 devicePosition, DWORD64 systemPosition, void* userData)
{
    // Это ваша функция обратного вызова для обработки данных из буфера
    // В этой функции вы можете обрабатывать данные, записанные в буфер
    std::cout << "Buffer filled, process captured audio here..." << std::endl;
}



void reshape(int w, int h)
{
    // установить новую область просмотра, равную всей области окна
    glViewport(0, 0, w, h);
    // устанавливаем матрицу проекции
    camera.setProjectionMatrix(35.0f, (float)w / h, 1.0f, 50000.0f);
}

// основная функция
void main(int argc, char** argv)
{
    int audiochoise = 0;
    cout << "Choose audio output decice: ";
    cin >> audiochoise;
    // инициализация библиотеки GLUT
    glutInit(&argc, argv);
    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    // требования к версии OpenGL (версия 3.3 без поддержки обратной совместимости)
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    // устанавливаем верхний левый угол окна
    glutInitWindowPosition(300, 100);
    // устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // создание окна
    glutCreateWindow("laba_01");

    // инициализация GLEW 
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Glew error: %s\n", glewGetErrorString(err));
        return;
    }

    // определение текущей версии OpenGL
    printf("OpenGL Version = %s\n\n", glGetString(GL_VERSION));

    // загрузка шейдера
    shader.load("SHADER\\Example.vsh", "SHADER\\Example.fsh");

    InitializingObjects();


    if (audiochoise == 0)
    {
        // инициализация захвата аудио
        waveform.wFormatTag = WAVE_FORMAT_PCM;
        waveform.nChannels = 1;
        waveform.nSamplesPerSec = 48000;
        waveform.wBitsPerSample = 16;
        waveform.nBlockAlign = waveform.nChannels * waveform.wBitsPerSample / 8;
        waveform.nAvgBytesPerSec = waveform.nSamplesPerSec * waveform.nBlockAlign;
        waveform.cbSize = 0;


        result = waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD_PTR)&waveInProc, 0, CALLBACK_FUNCTION);
        if (result != MMSYSERR_NOERROR)
        {
            std::cerr << "Failed to open audio device." << std::endl;
            return;
        }

        // Начало захвата аудио
        waveHdr.lpData = new char[sizeBox];
        waveHdr.dwBufferLength = sizeBox;
        waveHdr.dwBytesRecorded = 0;
        waveHdr.dwUser = 0;
        waveHdr.dwFlags = 0;
        waveHdr.dwLoops = 0;

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
        //ВЫВОД!

        waveFormat.wFormatTag = WAVE_FORMAT_PCM;
        waveFormat.nChannels = 1; // Моно
        waveFormat.nSamplesPerSec = 48000; // Частота дискретизации
        waveFormat.wBitsPerSample = 16; // Разрядность звука
        waveFormat.nBlockAlign = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
        waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
        waveFormat.cbSize = 0;

        result = waveOutOpen(&hWaveOut, 0, &waveFormat, 0, 0, CALLBACK_NULL);
        if (result != MMSYSERR_NOERROR) {
            std::cerr << "Failed to open audio device for playback." << std::endl;
            return;
        }
    }
    // Создание события для сигнализации о готовности данных в буфере
    HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if(audiochoise == 1)
    {
        // Здесь захват звука из устрофства вывода по умолчанию
    }

    

    

    // Заполнение буфера с аудиоданными
// Например, используя waveHdr.lpData, которые вы уже получили из waveInProc


    cout << "\n\nTo change the Mode, press 2/1/0\n";

    cout << "\n\nTo change the Second Mode, press 8/9\n";

    //ф-я обратного вызова при вращении колеса мыши
    glutMouseWheelFunc(mouseWheel);
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);
    // устанавливаем функцию которая вызывается всякий раз, когда процессор простаивает
    glutIdleFunc(simulation);
    // основной цикл обработки сообщений ОС
    glutMainLoop();
    


    if (audiochoise == 0)
    {
        // Остановка захвата аудио при завершении программы
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
        delete[] waveHdr.lpData;
        // Освобождение ресурсов
        waveOutUnprepareHeader(hWaveOut, &waveOutHdr, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }
    if (audiochoise == 1)
    {
        // Освобождение памяти
    }

    return;
}
