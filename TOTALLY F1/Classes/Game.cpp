#include "Game.h"

//CONSTRUCTORS
Game::Game() {}
/*
	Recieves window information and sets up controlKart and controlPersCam bools.
		- controlKart = true | Upon run, the user will be able to move the Kart by default
		- controlPersCam = true | By default the user will view the Kart through the perspective camera
*/
Game::Game(GLFWwindow* window, float windowWidth, float windowHeight) {
	this->window = window;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	
	isThirdPerson = true;
	stopCars = false;
	gameStart = false;
	isPrinted = false;
}

//FUNCTIONS
/*
*	Begins the program and continues game initialization.
*/
void Game::start() {
	// Removes the cursor to allow for better mouse input 
	glfwSetCursorPos(window, 0, 0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	initializePlayer(); // initializes all player-related variables
	initializeSkybox(); // initializes the skybox
	initializeModels(); // creates all game objects

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Source Factor
	runLoop(); // the actual game loop

	glfwTerminate();
}

void Game::initializePlayer() {
	///////////////////////////////// PLAYER KART /////////////////////////////////
		//KART LIVERY (Main body)
	setVAO(&kartVAOs[0], GENERATE);
	setVAO(&kartVAOs[0], BIND);
	player.addPlayerKart(
		new PlayerKart(
		"PLYR_KART1",					// Name of the object
		"3D/f1_2026.obj",			// File location of the 3D Object
		vec3(0.0),					// Object position
		vec3(0.6, 0.6, 0.6),		// Object scale
		vec3(0.0, 90.0, 0.0),		// Object rotation
		"Shaders/KartShader.vert",	// File path of the vertex shader
		"Shaders/KartShader.frag",	// File path of the fragment shader
		"Textures/f1_2026/Livery.png", // File path of the corresponding texture
		0.1f,						// Max Speed
		0.00003f,					// Acceleration Modifier
		1.0f,
		0.0f,						// Theta Turn
		0.75f						// Theta Turning Modifier
	));
	setVAO(&kartVAOs[0], UNBIND);

	//KART WHEELS
	setVAO(&kartVAOs[1], GENERATE);
	setVAO(&kartVAOs[1], BIND);
	player.addPlayerKart(new PlayerKart(
		"PLYR_KART2",
		"3D/f1_2026.obj",
		vec3(0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		0.1f,
		0.00003f,
		1.0f,
		0.0f,
		0.75f
	));
	setVAO(&kartVAOs[1], UNBIND);

	//KART WHEEL COVERS
	setVAO(&kartVAOs[2], GENERATE);
	setVAO(&kartVAOs[2], BIND);
	player.addPlayerKart(new PlayerKart(
		"PLYR_KART3",
		"3D/f1_2026.obj",
		vec3(0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		0.1f,
		0.00003f,
		1.0f,
		0.0f,
		0.75f
	));
	setVAO(&kartVAOs[2], UNBIND);

		//THIRD PERSON CAMERA
	player.addPlayerCamera(new Perspective(
		800.0f,                   // Window width
		800.0f,                   // Window height
		0.1f,                     // zNear
		500.0f,                   // zFar
		vec3(0.0f, 3.0f, 0.0f),   // Camera Position
		vec3(0.0f),               // Camera Center
		vec3(180.f, -30.0f, 0.0f),// Camera Rotation Modifier
		90.0f,                    // Field of view (FOV)
		0.008f,					  // Rotation Speed
		5.0f					  // Radius of camera rotation
	));

		//FIRST PERSON CAMERA
	player.addPlayerCamera(new Perspective(
		800.0f,
		800.0f,
		0.1f,
		500.0f,
		vec3(0.0f, 1.5f, 0.5f),
		vec3(0.0f),
		vec3(40.0f, 180.0f, 0.0f),
		80.0f,
		0.0f,
		0.0f
	));

	player.switchCam(THIRD_PERSON);
}

void Game::initializeSkybox() {
	//NIGHT SKYBOX
	string skyboxNight[] = {
		"Textures/skybox/night/night_rt.png",
		"Textures/skybox/night/night_lf.png",
		"Textures/skybox/night/night_up.png",
		"Textures/skybox/night/night_dn.png",
		"Textures/skybox/night/night_ft.png",
		"Textures/skybox/night/night_bk.png"
	};

	//MORNING SKYBOX
	string skyboxMorning[] = {
		"Textures/skybox/morning/morning_rt.png",
		"Textures/skybox/morning/morning_lf.png",
		"Textures/skybox/morning/morning_up.png",
		"Textures/skybox/morning/morning_dn.png",
		"Textures/skybox/morning/morning_ft.png",
		"Textures/skybox/morning/morning_bk.png"
	};

	setVAO(&skyboxVAO, GENERATE);
	setVAO(&skyboxVAO, BIND);
	skybox = new Skybox(
		skyboxNight,
		skyboxMorning,
		"Shaders/SkyboxShader.vert",
		"Shaders/SkyboxShader.frag"
	);
	setVAO(&skyboxVAO, UNBIND);
}

/*
	Reponsible for creating the objects present in the program.
		- allModels is a vector containing all of the models in the game
		- LightBall is a class for the ball of light which is a child of the Model3D class
		- Kart is also a child of Model3D which is for all of the parts of the car model
		- Calls each class's constructor and pushes the object into the allModels vector
		- When calling the class's constructor, it also generates and binds the corresponding VAO, and when it is finished it unbinds for clean up
*/
void Game::initializeModels() {
	///////////////////////////////// GHOST KART 1 - FAST /////////////////////////////////
		//KART LIVERY (Main body)
	allNPModels.push_back(new Kart(
		"KART1",					
		"3D/f1_2026.obj",			
		vec3(5.0, 0.0, 0.0),					
		vec3(0.6, 0.6, 0.6),		
		vec3(0.0, 90.0, 0.0),		
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/Livery.png",
		0.25f,
		0.00025f,
		0.3f
	));

	//KART WHEELS
	allNPModels.push_back(new Kart(
		"KART2",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		0.25f,
		0.00025f,
		0.3f
	));

	//KART WHEEL COVERS
	allNPModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		0.25f,
		0.00025f,
		0.3f
	));

	///////////////////////////////// GHOST KART 2 - SLOW /////////////////////////////////
	//KART LIVERY (Main body)
	allNPModels.push_back(new Kart(
		"KART1",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/Livery.png",
		0.075f,
		0.000008f,
		0.3f
	));

	//KART WHEELS
	allNPModels.push_back(new Kart(
		"KART2",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		0.075f,
		0.000008f,
		0.3f
	));

	//KART WHEEL COVERS
	allNPModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		0.075f,
		0.000008f,
		0.3f
	));

	///////////////////////////////// PLANE /////////////////////////////////
	setVAO(&roadVAO, GENERATE);
	setVAO(&roadVAO, BIND);
	allNPModels.push_back(new Object(
		"PLANE",
		"3D/plane.obj",
		vec3(0.0f, 0.0f, 0.0f),
		vec3(3000.f, 3000.f, 3000.f),
		vec3(90.0, 0.0f, 0.0f),
		"Shaders/PlaneShader.vert",
		"Shaders/PlaneShader.frag",
		vec3(0.15f)
	));
	setVAO(&roadVAO, UNBIND);

	///////////////////////////////// LIGHT BALL 1 /////////////////////////////////
	setVAO(&lightBallVAO, GENERATE);
	setVAO(&lightBallVAO, BIND);
	allNPModels.push_back(new Object(
		"LIGHT_BALL",
		"3D/light_ball.obj",
		vec3(1.75f, 3.5f, 3.0f),
		vec3(0.005f),
		vec3(0.0),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		vec3(0.0f)
	));
	setVAO(&lightBallVAO, UNBIND);

	///////////////////////////////// LIGHT BALL 2 /////////////////////////////////
	allNPModels.push_back(new Object(
		"LIGHT_BALL",
		"3D/light_ball.obj",
		vec3(0.0f, 3.5f, 3.0f),
		vec3(0.005f),
		vec3(0.0),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		vec3(0.0f)
	));

	///////////////////////////////// LIGHT BALL 3 /////////////////////////////////
	allNPModels.push_back(new Object(
		"LIGHT_BALL",
		"3D/light_ball.obj",
		vec3(-1.75f, 3.5f, 3.0f),
		vec3(0.005f),
		vec3(0.0),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		vec3(0.0f)
	));

	///////////////////////////////// FINISH LINE /////////////////////////////////
	allNPModels.push_back(new Object(
		"PLANE",
		"3D/plane.obj",
		vec3(0.0f, 1.0f, FINISH_LINE),
		vec3(1000.0f, 1.0f, 5.0f),
		vec3(0.0, 0.0f, 0.0f),
		"Shaders/PlaneShader.vert",
		"Shaders/PlaneShader.frag",
		vec3(9.0f, 0.1f, 0.1f)
	));

	///////////////////////////////// TOWNHOUSE /////////////////////////////////
	setVAO(&townhouseVAO, GENERATE);
	setVAO(&townhouseVAO, BIND);
	allNPModels.push_back(new Building(
		"TOWNHOUSE",
		"3D/townhouse.obj",
		vec3(-20.0f, 0.0f, 100.0f),
		vec3(3.0f),
		vec3(0.0),
		"Shaders/BuildingShader.vert",
		"Shaders/BuildingShader.frag",
		"Textures/townhouse/townhouse_color.png",
		"Textures/townhouse/townhouse_normal.png"
	));
	setVAO(&townhouseVAO, UNBIND);
}

/*
	Listens for player input and carries out the appropriate response
*/
void Game::checkInput() {
	if(gameStart){
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			player.moveInput(ACCELERATE);
			player.reverseKart(false);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
			player.moveInput(REVERSE);
			player.reverseKart(true);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			player.moveInput(STEER_L);
			spotLightL.spotSpin(LEFT);
			spotLightR.spotSpin(LEFT);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			player.moveInput(STEER_R);
			spotLightL.spotSpin(RIGHT);
			spotLightR.spotSpin(RIGHT);
		}
	}
	
	//Switch to third or first person perspective view
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && switchCamTimer >= 220) {
		isThirdPerson = !isThirdPerson;
		switchCamTimer = 0;

		if (isThirdPerson) player.switchCam(THIRD_PERSON);
		else player.switchCam(FIRST_PERSON);
	}

	//Morning and Night
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		skyboxTex = MORNING;
		dirLight.updateDirLight(MORNING);
		spotLightL.updatePointLight(NONE);
		spotLightR.updatePointLight(NONE);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { 
		skyboxTex = NIGHT; 
		dirLight.updateDirLight(NIGHT);
		spotLightL.updatePointLight(WHITE);
		spotLightR.updatePointLight(WHITE);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		player.rotateThirdPersKeys(DOWN);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		player.rotateThirdPersKeys(UP);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		player.rotateThirdPersKeys(LEFT);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		player.rotateThirdPersKeys(RIGHT);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && stopCarsTimer >= 300) {
		stopCars = !stopCars;
		stopCarsTimer = 0;
	}
	
	// Press escape to end the program (since cursor is disabled)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);
}

// Handles mouse rotation
void Game::mouseInput() {
	player.rotateThirdPersMouse(&prevMousePos, &currMousePos);
}

void Game::updateInputTimer() {
	switchCamTimer++;
	stopCarsTimer++;
	if(!gameStart) signalLights++;
}

void Game::updateSignalLights() {
	if(!gameStart){
		if (signalLights < 1200){
			signalLight.updatePointLight(NONE);
		}
		else if (signalLights == 1200){
			dynamic_cast<Object*>(allNPModels[LIGHT_BALL1])->setColor(vec3(1.0f, 0.0f, 0.0f));
			signalLight.updatePointLight(RED);
		}
		else if (signalLights == 2250) {
			dynamic_cast<Object*>(allNPModels[LIGHT_BALL2])->setColor(vec3(1.0f, 1.0f, 0.0f));
			signalLight.updatePointLight(YELLOW);
		}
		else if (signalLights == 3300){
			dynamic_cast<Object*>(allNPModels[LIGHT_BALL1])->setColor(vec3(0.0f, 1.0f, 0.0f));
			dynamic_cast<Object*>(allNPModels[LIGHT_BALL2])->setColor(vec3(0.0f, 1.0f, 0.0f));
			dynamic_cast<Object*>(allNPModels[LIGHT_BALL3])->setColor(vec3(0.0f, 1.0f, 0.0f));

			signalLight.updatePointLight(GREEN);

			for (PlayerKart* playerKart : player.getWholeKart())
				playerKart->setGO(true);
			for (int i = GST1_IDX_KL; i <= GST2_IDX_WC; i++)
				dynamic_cast<Kart*>(allNPModels[i])->setGO(true);

			gameStart = true;
			startTimer = glfwGetTime();
		}
	}
}

void Game::checkKarts() {
	//All three karts have to be false
	if (gameStart) {

		if (!(dynamic_cast<Kart*>(allNPModels[GST1_IDX_KL])->getGO()) && !(kartFastTime))
			kartFastTime = glfwGetTime();
		if (!(dynamic_cast<Kart*>(allNPModels[GST2_IDX_KL])->getGO()) && !(kartSlowTime))
			kartSlowTime = glfwGetTime();
		if (!(player.getKartPart(PLYR_IDX_KL)->getGO()) && !(playerKartTime))
			playerKartTime = glfwGetTime();

		if (!(dynamic_cast<Kart*>(allNPModels[GST1_IDX_KL])->getGO() ||
			dynamic_cast<Kart*>(allNPModels[GST2_IDX_KL])->getGO() ||
			player.getKartPart(PLYR_IDX_KL)->getGO()) && !isPrinted) {
			
			for (PlayerKart* kartPart : player.getWholeKart())
				kartPart->setSpeed(0);

			cout << "||-------- TIME --------||" << endl;
			cout << "Fast Kart: " << kartFastTime - startTimer << endl;
			cout << "   Player: " << playerKartTime - startTimer << endl;
			cout << "Slow Kart: " << kartSlowTime - startTimer << endl;
			cout << "||----------------------||" << endl;

			isPrinted = true;
			gameStart = false;
		}
	}
}


/*
	The main game loop.
*/
void Game::runLoop() {
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Updates input timers
		updateInputTimer();
		updateSignalLights();
		checkKarts();

		//Handles input checking for keys
		checkInput();
		glfwGetCursorPos(window, &currMousePos.x, &currMousePos.y);
		mouseInput(); // input checking for mouse

		setVAO(&skyboxVAO, BIND);
		skybox->draw(
			player.getActiveCam()->getView(), 
			player.getActiveCam()->getProjection(),
			skyboxTex);

		player.updateCameras();
			
		for (int i = 0; i < player.getWholeKart().size(); i++) {
			PLYR_KART_PARTS part;
			switch (i) {
			case 0: part = PLYR_IDX_KL;
				break;
			case 1: part = PLYR_IDX_WL;
				break;
			case 2: part = PLYR_IDX_WC;
				break;
			}

			glUseProgram(player.getKartPart(part)->getShader().getShaderProg());
			player.getActiveCam()->draw(player.getKartPart(part)->getShader().getShaderProg());
			
			signalLight.loadPoint(player.getKartPart(part)->getShader().getShaderProg(), "signal");
			dirLight.loadDir(player.getKartPart(part)->getShader().getShaderProg(), "dir");

			spotLightL.loadSpot(player.getKartPart(part)->getShader().getShaderProg(), "spotL");
			spotLightL.updateSpotPosDir(player.getKartPart(part)->getPosition(),
										player.getKartPart(part)->getDirection());

			spotLightR.loadSpot(player.getKartPart(part)->getShader().getShaderProg(), "spotR");
			spotLightR.updateSpotPosDir(player.getKartPart(part)->getPosition(),
				player.getKartPart(part)->getDirection());

			setVAO(&kartVAOs[part], BIND);

			glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
			glBlendEquation(GL_FUNC_ADD);

			player.getKartPart(part)->updatePlayer();
			player.getKartPart(part)->draw();
		}
		
		for (int i = 0; i < allNPModels.size(); i++) {
			Model3D* model = allNPModels[i];

			glUseProgram(model->getShader().getShaderProg());
			player.getActiveCam()->draw(model->getShader().getShaderProg());

			signalLight.loadPoint(model->getShader().getShaderProg(), "signal");
			dirLight.loadDir(model->getShader().getShaderProg(), "dir");

			spotLightL.loadSpot(model->getShader().getShaderProg(), "spotL");
			spotLightR.loadSpot(model->getShader().getShaderProg(), "spotR");

			// Sets the VAO to the corresponding kart
			if (i == GST1_IDX_KL || i == GST2_IDX_KL)
				setVAO(&kartVAOs[GST1_IDX_KL], BIND);
			else if (i == GST1_IDX_WL || i == GST2_IDX_WL)
				setVAO(&kartVAOs[GST1_IDX_WL], BIND);
			else if (i == GST1_IDX_WC || i == GST2_IDX_WC)
				setVAO(&kartVAOs[GST1_IDX_WC], BIND);
			else if (i == ROAD_PLANE || i == FINISH_PLANE)
				setVAO(&roadVAO, BIND);
			else if (i >= LIGHT_BALL1 && i <= LIGHT_BALL3)
				setVAO(&lightBallVAO, BIND);
			else if (i == TOWNHOUSE)
				setVAO(&townhouseVAO, BIND);

			if(!stopCars && gameStart){
				//FASTER KART
				if (i >= GST1_IDX_KL && i <= GST1_IDX_WC) {
					dynamic_cast<Kart*>(model)->setAcceleration(0.00025f);
					dynamic_cast<Kart*>(model)->update();
				}
				//SLOWER KART
				else if (i >= GST2_IDX_KL && i <= GST2_IDX_WC) {
					dynamic_cast<Kart*>(model)->setAcceleration(0.000008f);
					dynamic_cast<Kart*>(model)->update();
				}
			}
			else if (stopCars){
				if (i <= GST2_IDX_WC){
					dynamic_cast<Kart*>(model)->setAcceleration(0);
					dynamic_cast<Kart*>(model)->setSpeed(0);
				}
			}
			
			if(i <= GST2_IDX_WC)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			else 
				glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

			glBlendEquation(GL_FUNC_ADD);
			model->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

/* 
	Function for handling VAOs
		- Mainly for proper generation, binding, and clean up
*/
void Game::setVAO(GLuint* VAO, int type) {
	switch (type) {
		case UNBIND:	// Unbind VAO
			glBindVertexArray(0);
			break;
		case BIND:		// Bind VAO
			glBindVertexArray(*VAO);
			break;
		case GENERATE:  // Generate VAO
			glGenVertexArrays(1, VAO);
			break;
	}
}

//DECONSTRUCTOR
Game::~Game() {
	for (Model3D* model : allNPModels) {
		model->~Model3D();
		delete model;
	}

	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteVertexArrays(1, &kartVAOs[0]);
	glDeleteVertexArrays(1, &kartVAOs[1]);
	glDeleteVertexArrays(1, &kartVAOs[2]);
	glDeleteVertexArrays(1, &roadVAO);
	glDeleteVertexArrays(1, &lightBallVAO);
}