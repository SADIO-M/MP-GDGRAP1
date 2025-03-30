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
		"KART1",					// Name of the object
		"3D/f1_2026.obj",			// File location of the 3D Object
		vec3(0.0),					// Object position
		vec3(0.6, 0.6, 0.6),		// Object scale
		vec3(0.0, 90.0, 0.0),		// Object rotation
		"Shaders/KartShader.vert",	// File path of the vertex shader
		"Shaders/KartShader.frag",	// File path of the fragment shader
		"Textures/f1_2026/Livery.png", // File path of the corresponding texture
		1.0f,						// Max Speed
		0.0002f,					// Acceleration Modifier
		0.0f,						// Theta Turn
		0.01f						// Theta Turning Modifier
	));
	setVAO(&kartVAOs[0], UNBIND);

	//KART WHEELS
	setVAO(&kartVAOs[1], GENERATE);
	setVAO(&kartVAOs[1], BIND);
	player.addPlayerKart(new PlayerKart(
		"KART2",
		"3D/f1_2026.obj",
		vec3(0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		1.0f,
		0.0002f,				
		0.0f,
		0.01f
	));
	setVAO(&kartVAOs[1], UNBIND);

	//KART WHEEL COVERS
	setVAO(&kartVAOs[2], GENERATE);
	setVAO(&kartVAOs[2], BIND);
	player.addPlayerKart(new PlayerKart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		1.0f,
		0.0002f,
		0.0f,
		0.01f
	));
	setVAO(&kartVAOs[2], UNBIND);

		//THIRD PERSON CAMERA
	player.addPlayerCamera(new Perspective(
		800.0f,                  // Window width
		800.0f,                  // Window height
		0.1f,                    // zNear
		500.0f,                  // zFar
		vec3(0.0f, 3.0f, -6.0f), // Camera Position
		vec3(0.0f),              // Camera Center
		vec3(0.0f),				 // Camera Position Modifier
		vec3(-10.0f, 0.0f, 0.0f),// Camera Rotation Modifier
		70.0f                    // Field of view (FOV)
	));

		//FIRST PERSON CAMERA
	player.addPlayerCamera(new Perspective(
		800.0f,
		800.0f,
		0.1f,
		500.0f,
		vec3(0.0f, 1.5f, 1.0f),
		vec3(0.0f),
		vec3(0.0f),
		vec3(40.0f, 180.0f, 0.0f),
		80.0f
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
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/Livery.png",
		2.0f,
		0.0005f
	));

	//KART WHEELS
	allNPModels.push_back(new Kart(
		"KART2",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		2.0f,
		0.0005f
	));

	//KART WHEEL COVERS
	allNPModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		2.0f,
		0.0005f
	));

	///////////////////////////////// GHOST KART 2 - SLOW /////////////////////////////////
	//KART LIVERY (Main body)
	allNPModels.push_back(new Kart(
		"KART1",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/Livery.png",
		0.5f,
		0.0002f
	));

	//KART WHEELS
	allNPModels.push_back(new Kart(
		"KART2",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		0.5f,
		0.0002f
	));

	//KART WHEEL COVERS
	allNPModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		0.5f,
		0.0002f
	));

	///////////////////////////////// PLANE /////////////////////////////////
	setVAO(&roadVAO, GENERATE);
	setVAO(&roadVAO, BIND);
	allNPModels.push_back(new Object(
		"PLANE",
		"3D/plane.obj",
		vec3(0.0f, -1.0f, 0.0f),
		vec3(0.5f, 0.5f, 10000.f),
		vec3(90.0, 0.0f, 0.0f),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		//vec3(0.2f, 0.2f, 0.2f)
		vec3(0.15f, 0.15f, 0.15f)
	));
	setVAO(&roadVAO, UNBIND);

	///////////////////////////////// LIGHT BALL 1 /////////////////////////////////
	setVAO(&lightBallVAO, GENERATE);
	setVAO(&lightBallVAO, BIND);
	allNPModels.push_back(new Object(
		"LIGHT_BALL",
		"3D/light_ball.obj",
		vec3(-1.5f, 4.0f, 0.0f),
		vec3(0.004f),
		vec3(0.0),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		vec3(0.5f)
	));
	setVAO(&lightBallVAO, UNBIND);

	///////////////////////////////// LIGHT BALL 2 /////////////////////////////////
	allNPModels.push_back(new Object(
		"LIGHT_BALL",
		"3D/light_ball.obj",
		vec3(0.0f, 4.0f, 0.0f),
		vec3(0.004f),
		vec3(0.0),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		vec3(0.5f)
	));

	///////////////////////////////// LIGHT BALL 3 /////////////////////////////////
	allNPModels.push_back(new Object(
		"LIGHT_BALL",
		"3D/light_ball.obj",
		vec3(1.5f, 4.0f, 0.0f),
		vec3(0.004f),
		vec3(0.0),
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		vec3(0.5f)
	));
}

/*
	Listens for player input and carries out the appropriate response
*/
void Game::checkInput() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		player.moveInput(ACCELERATE);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
		player.moveInput(REVERSE);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		player.moveInput(STEER_L);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		player.moveInput(STEER_R);
	
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
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { 
		skyboxTex = NIGHT; 
		dirLight.updateDirLight(NIGHT);
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		player.rotateThirdPersKeys(DOWN);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) 
		player.rotateThirdPersKeys(UP);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		player.rotateThirdPersKeys(LEFT);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
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
		//Handles input checking
		checkInput(); 

		//Mouse rotations
		glfwGetCursorPos(window, &currMousePos.x, &currMousePos.y);
		mouseInput();

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
			
			dirLight.loadDir(player.getKartPart(part)->getShader().getShaderProg(), "dir");

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
			dirLight.loadDir(model->getShader().getShaderProg(), "dir");

			// Sets the VAO to the corresponding kart
				 if (i == GST1_IDX_KL || i == GST2_IDX_KL)
				setVAO(&kartVAOs[GST1_IDX_KL], BIND);
			else if (i == GST1_IDX_WL || i == GST2_IDX_WL) 
				setVAO(&kartVAOs[GST1_IDX_WL], BIND);
			else if (i == GST1_IDX_WC || i == GST2_IDX_WC)
				setVAO(&kartVAOs[GST1_IDX_WC], BIND);
			else if (i == ROAD_PLANE)
				setVAO(&roadVAO, BIND);
			else if (i >= LIGHT_BALL1 && i <= LIGHT_BALL3)
				setVAO(&lightBallVAO, BIND);

			if(stopCars){
				//FASTER KART
				if (i >= GST1_IDX_KL && i <= GST1_IDX_WC) {
					dynamic_cast<Kart*>(model)->setAcceleration(0.0006f);
					dynamic_cast<Kart*>(model)->update();
				}
				//SLOWER KART
				else if (i >= GST2_IDX_KL && i <= GST2_IDX_WC) {
					dynamic_cast<Kart*>(model)->setAcceleration(0.0002f);
					dynamic_cast<Kart*>(model)->update();
				}
			}
			
			if(i <= GST2_IDX_WC)
				glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
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
}