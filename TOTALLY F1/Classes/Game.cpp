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
	
	switchCam = true;
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
	initializeSkybox();
	initializeModels(); // creates all game objects
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Source Factor
	runLoop(); // the actual game loop

	glfwTerminate();
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

	///////////////////////////////// PLAYER KART /////////////////////////////////
	//KART LIVERY (Main body)
	setVAO(&kartVAOs[0], GENERATE);
	setVAO(&kartVAOs[0], BIND);
	allModels.push_back(new Player(
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
		&thirdPersCam
	));
	setVAO(&kartVAOs[0], UNBIND);
	
	//KART WHEELS
	setVAO(&kartVAOs[1], GENERATE);
	setVAO(&kartVAOs[1], BIND);
	allModels.push_back(new Player(	//The variables are the exact same as the kart livery, except for the texture
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
		&thirdPersCam
	));
	setVAO(&kartVAOs[1], UNBIND);

	//KART WHEEL COVERS
	setVAO(&kartVAOs[2], GENERATE);
	setVAO(&kartVAOs[2], BIND);
	allModels.push_back(new Player(
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
		&thirdPersCam
	));
	setVAO(&kartVAOs[2], UNBIND);
	///
	///
	///
	/// 
	///////////////////////////////// GHOST KART 1 - FAST /////////////////////////////////
		//KART LIVERY (Main body)
	allModels.push_back(new Kart(
		"KART1",					
		"3D/f1_2026.obj",			
		vec3(5.0, 0.0, 0.0),					
		vec3(0.6, 0.6, 0.6),		
		vec3(0.0, 90.0, 0.0),		
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/Livery.png",
		3.0f,
		0.0006f
	));

	//KART WHEELS
	allModels.push_back(new Kart(	//The variables are the exact same as the kart livery, except for the texture
		"KART2",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/TyreSoft.png",
		3.0f,
		0.0006f
	));

	//KART WHEEL COVERS
	allModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, 90.0, 0.0),
		"Shaders/GhostShader.vert",
		"Shaders/GhostShader.frag",
		"Textures/f1_2026/WheelCovers.png",
		3.0f,
		0.0006f
	));
	///
	///
	///
	/// 
	///////////////////////////////// GHOST KART 2 - SLOW /////////////////////////////////
	//KART LIVERY (Main body)
	allModels.push_back(new Kart(
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
	allModels.push_back(new Kart(	//The variables are the exact same as the kart livery, except for the texture
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
	allModels.push_back(new Kart(
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

	////LIGHT BALL
	//setVAO(&light_ballVAO, GENERATE);	// Generates the light ball VAO
	//setVAO(&light_ballVAO, BIND);		// Binds the corresponding VAO so the object's information is saved there
	//allModels.push_back(new LightBall(
	//	"LIGHT_BALL",				// Name of the object
	//	"3D/light_ball.obj",		// File location of the 3D Object
	//	vec3(-5, 0.5, 0.0),			// Object position
	//	vec3(0.004, 0.004, 0.004),	// Object scale
	//	vec3(0.0),					// Object rotation
	//	"Shaders/LightShader.vert", // File path of the vertex shader
	//	"Shaders/LightShader.frag", // File path of the fragment shader
	//	vec3(1.0),					// Color of the light ball
	//	vec3(0.0)					// Pivot point
	//));
	//setVAO(&light_ballVAO, UNBIND);		// Unbinds VAO for clean up
}

/*
	Listens for player input and carries out the appropriate response
*/
void Game::checkInput() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		dynamic_cast<Player*>(allModels[PLYR_IDX_KL])->moveInput('w');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WL])->moveInput('w');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WC])->moveInput('w');
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		dynamic_cast<Player*>(allModels[PLYR_IDX_KL])->moveInput('s');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WL])->moveInput('s');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WC])->moveInput('s');
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		dynamic_cast<Player*>(allModels[PLYR_IDX_KL])->moveInput('a');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WL])->moveInput('a');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WC])->moveInput('a');
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		dynamic_cast<Player*>(allModels[PLYR_IDX_KL])->moveInput('d');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WL])->moveInput('d');
		dynamic_cast<Player*>(allModels[PLYR_IDX_WC])->moveInput('d');
	}

	//Switch to third or first person perspective view
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && switchCamTimer >= 220) {
		if(switchCam){
			dynamic_cast<Player*>(allModels[PLYR_IDX_KL])->setKartCam(&thirdPersCam);
			dynamic_cast<Player*>(allModels[PLYR_IDX_WL])->setKartCam(&thirdPersCam);	
			dynamic_cast<Player*>(allModels[PLYR_IDX_WC])->setKartCam(&thirdPersCam);
		}
		else {
			dynamic_cast<Player*>(allModels[PLYR_IDX_KL])->setKartCam(&firstPersCam);
			dynamic_cast<Player*>(allModels[PLYR_IDX_WL])->setKartCam(&firstPersCam);
			dynamic_cast<Player*>(allModels[PLYR_IDX_WC])->setKartCam(&firstPersCam);
		}
		switchCam = !switchCam;
		switchCamTimer = 0;
	}

	//Morning and Night
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		skyboxTex = MORNING;
		dirLight.updateDirLight(
			vec3(5.0f, 15.0f, 20.0f),
			vec3(0.9f, 1.0f, 0.9f), 
			1.0f,                   
			5.0f,                   
			15.0f,                  
			1.0f,                   
			vec3(5.0f, 15.0f, 20.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { 
		skyboxTex = NIGHT; 
		dirLight.updateDirLight(
			vec3(-6.0f, 12.0f, 25.0f),
			vec3(1.0f, 1.0f, 1.0f),
			0.5f,
			2.0f,
			10.0f,
			0.6f,
			vec3(-6.0f, 12.0f, 25.0f));
	}

	// Keyboard rotation for the perspective camera, will only accept inputs when its being controlled
	if(switchCam){
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) thirdPersCam.rotateWithKeys('i');
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) thirdPersCam.rotateWithKeys('k');
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) thirdPersCam.rotateWithKeys('j');
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) thirdPersCam.rotateWithKeys('l');
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && stopCarsTimer >= 300) {
		stopCars = !stopCars;
		stopCarsTimer = 0;
	}

	// Press escape to end the program (since cursor is disabled)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);
}

// Handles mouse rotation
void Game::mouseInput() {
	thirdPersCam.rotateWithMouse(&prevMousePos, &currMousePos);
}

void Game::addToTimers() {
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

		addToTimers();
		checkInput(); // input handling

		/* Camera updating
			 - If the controlPersCam is true, it will use the perspective camera
			 - Else, it uses the orthographic camera
		*/
		setVAO(&skyboxVAO, BIND);

		if(switchCam){
			skybox->draw(thirdPersCam.getView(), thirdPersCam.getProjection(), skyboxTex);
			glfwGetCursorPos(window, &currMousePos.x, &currMousePos.y);
			mouseInput();
			thirdPersCam.update();
			thirdPersCam.checkCameraRotation();
		}
		else {
			skybox->draw(firstPersCam.getView(), firstPersCam.getProjection(), skyboxTex);
			firstPersCam.update();
			firstPersCam.checkCameraRotation();
		}
	
		for (int i = 0; i < allModels.size(); i++) {
			Model3D* model = allModels[i];
			glUseProgram(model->getShader().getShaderProg());

			if (switchCam)
				thirdPersCam.draw(model->getShader().getShaderProg());
			else
				firstPersCam.draw(model->getShader().getShaderProg());

			dirLight.loadDir(model->getShader().getShaderProg(), "dir");

			// Sets the VAO to the corresponding kart
			if (model->getName() == "KART1") {
				setVAO(&kartVAOs[PLYR_IDX_KL], BIND);
			}
			else if (model->getName() == "KART2") {
				setVAO(&kartVAOs[PLYR_IDX_WL], BIND);
			}
			else if (model->getName() == "KART3") {
				setVAO(&kartVAOs[PLYR_IDX_WC], BIND);
			}

			if (i >= GST1_IDX_KL && i <= GST2_IDX_WC)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			else
				glBlendFunc(GL_SRC_ALPHA, GL_ZERO);

			if (i >= PLYR_IDX_KL && i <= PLYR_IDX_WC) 
				dynamic_cast<Player*>(allModels[i])->updatePlayer();
			//FASTER KART
			if(!stopCars){
				if (i >= GST1_IDX_KL && i <= GST1_IDX_WC) {
					dynamic_cast<Kart*>(allModels[i])->setAcceleration(0.0006f);
					dynamic_cast<Kart*>(allModels[i])->update();
				}
				//SLOWER KART
				else if (i >= GST2_IDX_KL && i <= GST2_IDX_WC) {
					dynamic_cast<Kart*>(allModels[i])->setAcceleration(0.0002f);
					dynamic_cast<Kart*>(allModels[i])->update();
				}
			}
			
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
	for (Model3D* model : allModels) {
		model->~Model3D();
		delete model;
	}
}