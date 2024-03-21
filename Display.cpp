#include "Data.h"
#include "Display.h"

void display()
{
	// ������� ������ �����
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��������� ����� ������� (�� ������ ������)
	glEnable(GL_DEPTH_TEST);
	// ����� ��������� � ���� ����� � ���������� ��������� ������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// ��������� ������� ��������
	mat4 projectionMatrix;
	projectionMatrix = camera.getProjectionMatrix();
	// ������������� ������� ������
	mat4 viewMatrix;
	// ������� ������
	viewMatrix = camera.getViewMatrix();

	// ������� ������
	// ��������� ������� 
	shader.activate();
	// ������������� uniform-���������� ��� ������ �������� � ���������� ������
	shader.setUniform("projectionMatrix", projectionMatrix);
	srand(time(0));
	int counter = 0;
	int max = 0;
	if (tempSimTime >= 0.0) {
		tempSimTime = 0;
		if (Mode == 1) {
			for (auto& grObj : graphicObjects) {
				// ��������� ������� ���������� ������
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(PositionsMicro[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();
				if (counter < sizeBox && PositionsMicro[counter] != NULL) {
					if (counter % 2 == 0) {
						counter++;
						continue;
					}
					for (int j = 0; j < (int)PositionsMicro[counter]; j++)
					{
						if (j % 2 != 0 && j % 3 == 0) {
							continue;
						}
						grObj.setPosition(j);
						float r = float(j) / float(PositionsMicro[counter]);
						//MicroColor = vec4(r, 1.0f, 1.0f, 1.0f);
						MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
						grObj.setColor(MicroColor);
						mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

						shader.setUniform("modelViewMatrix", modelViewMatrix);

						shader.setUniform("color", grObj.getColor());
						max = j;
						drawBox();
					}
					//cout << PositionsMicro[counter] << endl;
				}
				counter++;
			}
		}

	}
	
		
	
	if (Mode == 0) {
		for (auto& grObj : graphicObjects) {
			if (counter % 2 == 0) {
				//counter++;
				//continue;
			}
			// ��������� ������� ���������� ������
			//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
			//grObj.setPosition(PositionsMicro[counter]);
			//grObj.setColor(MicroColor);
			//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
			//shader.setUniform("modelViewMatrix", modelViewMatrix);

			//shader.setUniform("color", grObj.getColor());

			//drawBox();
			grObj.setPosition(PositionsMicro[counter]);
			float r = float(PositionsMicro[counter]) / 327.0f;
			MicroColor = vec4(r * 5, 1 - r * 10, 1, 1.0f);
			//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
			grObj.setColor(MicroColor);
			mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

			shader.setUniform("modelViewMatrix", modelViewMatrix);

			shader.setUniform("color", grObj.getColor());

			drawBox();
			counter++;
		}
	

		if (Mode == 3) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// ��������� ������� ���������� ������
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(PositionsMicro[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();
				grObj.setPosition(PositionsMicro[counter]);
				float r = float(PositionsMicro[counter]) / 327.0f;
				MicroColor = vec4(r * 5, 1 - r * 10, 1, 1.0f);
				//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());

				drawBox();
				counter++;
			}
		}
	

	// ����� ��������� � ������� �������
	glutSwapBuffers();
	// ���������� FPS � ��� ����� � ��������� ����
	char windowTitle[128];
	int FPS = getFps();
	sprintf_s(windowTitle, 128, "Laba_03 [%i FPS]", FPS);
	glutSetWindowTitle(windowTitle);
}

int getFps() {
	FrameTime += simulationTime;
	FPS++;
	if (FrameTime >= 1) {
		//std::stringstream ss;
		//ss << FPS << " FPS";
		//std::string fpsString = ss.str();
		//cout << "FPS = " << FPS << endl; 
		//glutSetWindowTitle(fpsString.c_str());
		OldFPS = FPS;
		FPS = 0;
		FrameTime = 0;
	}
	return OldFPS;
}
