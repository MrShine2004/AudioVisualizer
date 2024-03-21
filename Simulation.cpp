#include "Simulation.h"



POINT previousMouseXY;
POINT currentMouseXY;

float getSimulationTime()
{
	static LARGE_INTEGER oldtime;
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	LARGE_INTEGER delta;
	delta.QuadPart = time.QuadPart - oldtime.QuadPart;
	LARGE_INTEGER ticks;
	QueryPerformanceFrequency(&ticks);

	//QueryPerformanceCounter(&ticks);
	oldtime = time;
	return (double)delta.QuadPart / (double)ticks.QuadPart;
}


// функция вызывается когда процессор простаивает, т.е. максимально часто
void simulation()
{
	// определение времени симуляции
	simulationTime = getSimulationTime();
	// вызываем принудительную перерисовку окна
	tempSimTime = tempSimTime + simulationTime;
	cameraSimulation();
	// передвижение камеры
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};

void cameraSimulation() {
	float dx = 0;
	float dz = 0;
	float rx = 0;
	float ry = 0;

	keyboard(dx, dz);
	mouse(rx, ry);
	camera.move(dx * simulationTime, dz * simulationTime);
	//mouse(rx, ry);
	// определяем необходимость вращения камеры
	camera.rotate(rx, -ry);
}

void keyboard(float& dx, float& dz) {
	if (GetAsyncKeyState(VK_UP))
	{
		dx -= camera.getMoveSpeed();
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		dx += camera.getMoveSpeed();
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		dz += camera.getMoveSpeed();
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		dz -= camera.getMoveSpeed();
	}
	if (GetAsyncKeyState(VK_RSHIFT))
	{
		camera.setMoveSpeed(camera.getMoveSpeed()/100);
	}
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		camera.setMoveSpeed(-camera.getMoveSpeed()/100);
		cout << camera.getPosition().x << " " << camera.getPosition().y << " " << camera.getPosition().z << " \n";
	}
	if (GetAsyncKeyState(48))
	{
		Mode = 0;
		cout << "Mode: " << Mode << " \n";
	}
	if (GetAsyncKeyState(49))
	{
		Mode = 1;
		cout << "Mode: " << Mode << " \n";
	}

	if (GetAsyncKeyState(50))
	{
		Mode = 2;
		cout << "Mode: " << Mode << " \n";
	}
	if (GetAsyncKeyState(56))
	{
		SecondMode = 8;
		cout << "Second Mode (Module Off): " << SecondMode << " \n";
	}

	if (GetAsyncKeyState(57))
	{
		SecondMode = 9;
		cout << "Second Mode (Module On): " << SecondMode << " \n";
	}
}

void mouse(float& rx, float& ry) {
	if (!GetAsyncKeyState(VK_RBUTTON)) {
		if (GetCursorPos(&currentMouseXY)) {
			previousMouseXY = currentMouseXY;
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON)) {
		if (GetCursorPos(&currentMouseXY)) {
			//cout << currentMouseXY.x << " | " << currentMouseXY.y << "\n";
			if ((currentMouseXY.x != previousMouseXY.x) || (currentMouseXY.y != previousMouseXY.y)) {
				rx = currentMouseXY.x - previousMouseXY.x;
				ry = currentMouseXY.y - previousMouseXY.y;
				previousMouseXY = currentMouseXY;
				//cout << rx << " | " << ry << "\n";
			}
		}
	}
}