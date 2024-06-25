#include "Data.h"
#include "Display.h"

void display()
{
	// очистка буфера кадра
	//glClearColor(1- float(waveHdr.lpData[0]) / 327.0f,
	//	0,
	//	float(waveHdr.lpData[0]) / 327.0f,
	//	1.0);// vec4(r * 5, 1 - r * 10, 1, 1.0f);
	/*glClearColor(BackgroundColor().x,
		BackgroundColor().y,
		BackgroundColor().z,
		BackgroundColor()[3]);*/// vec4(r * 5, 1 - r * 10, 1, 1.0f);
	glClearColor(0,
		0,
		0,
		1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включение теста глубины (на всякий случай)
	glEnable(GL_DEPTH_TEST);
	// вывод полигонов в виде линий с отсечением нелицевых граней
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// формируем матрицу проекции
	mat4 projectionMatrix;
	projectionMatrix = camera.getProjectionMatrix();
	// генерирование матрицы камеры
	mat4 viewMatrix;
	// матрица камеры
	viewMatrix = camera.getViewMatrix();

	// матрица модели
	// активация шейдера 
	shader.activate();
	// устанавливаем uniform-переменные для матриц проекции и наблюдения модели
	shader.setUniform("projectionMatrix", projectionMatrix);
	srand(time(0));
	int counter = 0;
	int max = 0;

	
		
	if (!Pictured) {

		Pictured = 1;
	}
	if (Mode == 1) {
		for (auto& grObj : graphicObjects) {
			// âû÷èñëÿåì ìàòðèöó íàáëþäåíèÿ ìîäåëè
			//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
			//grObj.setPosition(visualize[counter]);
			//grObj.setColor(MicroColor);
			//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
			//shader.setUniform("modelViewMatrix", modelViewMatrix);

			//shader.setUniform("color", grObj.getColor());

			//drawBox();
			if (counter < sizeBox && visualize[counter] != NULL) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				for (int j = 0; j < abs((int)visualize[counter]); j++)
				{
					if (j % 2 != 0 && j % 3 == 0) {
						continue;
					}
					grObj.setPosition(j);
					float r = float(j) / float(abs(visualize[counter]));
					//MicroColor = vec4(r, 1.0f, 1.0f, 1.0f);
					MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
					grObj.setColor(MicroColor);
					mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

					shader.setUniform("modelViewMatrix", modelViewMatrix);

					shader.setUniform("color", grObj.getColor());
					max = j;
					drawBox();
				}
				//if (visualize[counter] > 0)
				//{
				//	for (int j = 0; j < (int)visualize[counter]; j++)
				//	{
				//		if (j % 2 != 0 && j % 3 == 0) {
				//			continue;
				//		}
				//		grObj.setPosition(j);
				//		float r = float(j) / float(visualize[counter]);
				//		//MicroColor = vec4(r, 1.0f, 1.0f, 1.0f);
				//		MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				//		grObj.setColor(MicroColor);
				//		mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				//		shader.setUniform("modelViewMatrix", modelViewMatrix);

				//		shader.setUniform("color", grObj.getColor());
				//		max = j;
				//		drawBox();
				//	}
				//}
				//else
				//{
				//	for (int j = (int)visualize[counter]; j < 0; j++)
				//	{
				//		if (j % 2 != 0 && j % 3 == 0) {
				//			continue;
				//		}
				//		grObj.setPosition(j);
				//		float r = float(j) / float(visualize[counter]);
				//		//MicroColor = vec4(r, 1.0f, 1.0f, 1.0f);
				//		MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				//		grObj.setColor(MicroColor);
				//		mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				//		shader.setUniform("modelViewMatrix", modelViewMatrix);

				//		shader.setUniform("color", grObj.getColor());
				//		max = j;
				//		drawBox();
				//	}
				//}
				//cout << visualize[counter] << endl;
			}
			counter++;
		}
	}
	if (Mode == 0) {
		for (auto& grObj : graphicObjects) {
			if (counter % 2 == 0) {
				//counter++;
				//continue;
			}
			// вычисляем матрицу наблюдения модели
			//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
			//grObj.setPosition(visualize[counter]);
			//grObj.setColor(MicroColor);
			//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
			//shader.setUniform("modelViewMatrix", modelViewMatrix);

			//shader.setUniform("color", grObj.getColor());

			//drawBox();

			if (Recalculate == 1) {
				grObj.recalculateModelMatrix();
			}


			grObj.setPosition(visualize[counter]);
			
			MicroColor = Color(counter);
			grObj.setColor(MicroColor);
			mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

			shader.setUniform("modelViewMatrix", modelViewMatrix);

			shader.setUniform("color", grObj.getColor());

			drawBox();
			counter++;
		}
	}

		if (Mode == 2) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// вычисляем матрицу наблюдения модели
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(visualize[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();
				
				//vec3 PositionThis = vec3(100 * sin(visualize[counter]) * cos(visualize[counter]), 100 * sin(visualize[counter]) * sin(visualize[counter]), 100 * cos(visualize[counter]));
				//grObj.setPosition(PositionThis);
				grObj.setSphearePosition((float)visualize[counter] / 128.0 * 3.14, (float)counter / (float)sizeBox * 3.14);
				//cout << 'a ' << (float)visualize[counter] / 128.0 * 3.14 << endl;
				//cout << 'b ' << (float)counter / (float)sizeBox * 3.14 << endl;
				MicroColor = Color(counter);
				//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());

				drawBox();
				counter++;
			}
		}

		if (Mode == 3) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// вычисляем матрицу наблюдения модели
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(visualize[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();

				//vec3 PositionThis = vec3(100 * sin(visualize[counter]) * cos(visualize[counter]), 100 * sin(visualize[counter]) * sin(visualize[counter]), 100 * cos(visualize[counter]));
				//grObj.setPosition(PositionThis);
				grObj.setSphearePosition2((float)counter / (float)sizeBox * 120 + 10, (float)visualize[counter] / 128.0 * 3.14);
				//cout << 'a ' << (float)visualize[counter] / 128.0 * 3.14 << endl;
				//cout << "radius " << (float)counter / (float)sizeBox * 120 << endl;
				MicroColor = Color(counter);
				//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());


				drawBox(visualize[counter]/2);
				counter++;
			}
		}

		if (Mode == 4) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// вычисляем матрицу наблюдения модели
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(visualize[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();

				//vec3 PositionThis = vec3(100 * sin(visualize[counter]) * cos(visualize[counter]), 100 * sin(visualize[counter]) * sin(visualize[counter]), 100 * cos(visualize[counter]));
				//grObj.setPosition(PositionThis);
				grObj.setSphearePosition((float)counter / (float)sizeBox * 120 + 10, (float)visualize[counter] / 128.0 * 3.14);
				//cout << 'a ' << (float)visualize[counter] / 128.0 * 3.14 << endl;
				//cout << "radius " << (float)counter / (float)sizeBox * 120 << endl;
				MicroColor = Color(counter);
				//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());

				drawBox();
				counter++;
			}
		}

		if (Mode == 5) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// вычисляем матрицу наблюдения модели
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(visualize[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();

				//vec3 PositionThis = vec3(100 * sin(visualize[counter]) * cos(visualize[counter]), 100 * sin(visualize[counter]) * sin(visualize[counter]), 100 * cos(visualize[counter]));
				//grObj.setPosition(PositionThis);
				grObj.setSphearePosition((float)counter / (float)sizeBox * 3.14, (float)visualize[counter] / 128.0 * 3.14);
				//cout << 'a ' << (float)visualize[counter] / 128.0 * 3.14 << endl;
				//cout << 'b ' << (float)counter / (float)sizeBox * 3.14 << endl;
				MicroColor = Color(counter);
				//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());

				drawBox();
				counter++;
			}
		}
		if (Mode == 6) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// вычисляем матрицу наблюдения модели
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(visualize[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();

				//vec3 PositionThis = vec3(100 * sin(visualize[counter]) * cos(visualize[counter]), 100 * sin(visualize[counter]) * sin(visualize[counter]), 100 * cos(visualize[counter]));
				//grObj.setPosition(PositionThis);
				grObj.setSphearePosition3((float)visualize[counter] * 60 + 10, 
					(float)counter / (float)sizeBox / 128.0 * 3.14);
				MicroColor = Color2(counter);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());

				drawBox((float)visualize[counter]);
				counter++;
			}
		}
		if (Mode == 7) {
			for (auto& grObj : graphicObjects) {
				if (counter % 2 == 0) {
					//counter++;
					//continue;
				}
				// вычисляем матрицу наблюдения модели
				//vec4 color = vec4(float(rand() % (100 - 0 + 1) + 0)/100, float(rand() % (100 - 0 + 1) + 0) / 100, float(rand() % (100 - 0 + 1) + 0) / 100, 1);
				//grObj.setPosition(visualize[counter]);
				//grObj.setColor(MicroColor);
				//mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
				//shader.setUniform("modelViewMatrix", modelViewMatrix);

				//shader.setUniform("color", grObj.getColor());

				//drawBox();

				//vec3 PositionThis = vec3(100 * sin(visualize[counter]) * cos(visualize[counter]), 100 * sin(visualize[counter]) * sin(visualize[counter]), 100 * cos(visualize[counter]));
				//grObj.setPosition(PositionThis);
				grObj.setPolarPosition((float)counter / (float)sizeBox * 3.14, 
					(float)visualize[counter]);
				//cout << 'a ' << (float)visualize[counter] / 128.0 * 3.14 << endl;
				//cout << 'b ' << (float)counter / (float)sizeBox * 3.14 << endl;
				MicroColor = Color2(counter);
				//MicroColor = vec4(r, 1 - r * 5, 1, 1.0f);
				grObj.setColor(MicroColor);
				mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();

				shader.setUniform("modelViewMatrix", modelViewMatrix);

				shader.setUniform("color", grObj.getColor());

				drawBox();
				counter++;
			}
		}
	

	// смена переднего и заднего буферов
	glutSwapBuffers();
	// вычисление FPS и его вывод в заголовок окна
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
