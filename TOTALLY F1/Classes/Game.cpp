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
	
	controlKart = true;
	controlPersCam = true;
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
	allModels.push_back(new Kart(
		"KART1",					// Name of the object
		"3D/f1_2026.obj",			// File location of the 3D Object
		vec3(0.0),					// Object position
		vec3(0.6, 0.6, 0.6),		// Object scale
		vec3(0.0, -90.0, 0.0),		// Object rotation
		"Shaders/KartShader.vert",	// File path of the vertex shader
		"Shaders/KartShader.frag",	// File path of the fragment shader
		"Textures/f1_2026/Livery.png" // File path of the corresponding texture
	));
	setVAO(&kartVAOs[0], UNBIND);
	
	//KART WHEELS
	setVAO(&kartVAOs[1], GENERATE);
	setVAO(&kartVAOs[1], BIND);
	allModels.push_back(new Kart(	//The variables are the exact same as the kart livery, except for the texture
		"KART2",
		"3D/f1_2026.obj",
		vec3(0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0), 
		"Shaders/KartShader.vert", 
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png"
	));
	setVAO(&kartVAOs[1], UNBIND);

	//KART WHEEL COVERS
	setVAO(&kartVAOs[2], GENERATE);
	setVAO(&kartVAOs[2], BIND);
	allModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0),
		"Shaders/KartShader.vert", 
		"Shaders/KartShader.frag", 
		"Textures/f1_2026/WheelCovers.png"
	));
	setVAO(&kartVAOs[2], UNBIND);
	///
	///
	///
	/// 
	///////////////////////////////// GHOST KART 1 /////////////////////////////////
		//KART LIVERY (Main body)
	allModels.push_back(new Kart(
		"KART1",					
		"3D/f1_2026.obj",			
		vec3(5.0, 0.0, 0.0),					
		vec3(0.6, 0.6, 0.6),		
		vec3(0.0, -90.0, 0.0),		
		"Shaders/KartShader.vert",	
		"Shaders/KartShader.frag",	
		"Textures/f1_2026/Livery.png" 
	));

	//KART WHEELS
	allModels.push_back(new Kart(	//The variables are the exact same as the kart livery, except for the texture
		"KART2",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png"
	));

	//KART WHEEL COVERS
	allModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/WheelCovers.png"
	));
	///
	///
	///
	/// 
	///////////////////////////////// GHOST KART 2 /////////////////////////////////
	//KART LIVERY (Main body)
	allModels.push_back(new Kart(
		"KART1",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/Livery.png"
	));

	//KART WHEELS
	allModels.push_back(new Kart(	//The variables are the exact same as the kart livery, except for the texture
		"KART2",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/TyreSoft.png"
	));

	//KART WHEEL COVERS
	allModels.push_back(new Kart(
		"KART3",
		"3D/f1_2026.obj",
		vec3(-5.0, 0.0, 0.0),
		vec3(0.6, 0.6, 0.6),
		vec3(0.0, -90.0, 0.0),
		"Shaders/KartShader.vert",
		"Shaders/KartShader.frag",
		"Textures/f1_2026/WheelCovers.png"
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
	/*
		Change control to and from light ball
			- internalTime is a variable to enforce a cooldown on switching controls so that one input is not registered multiple times
	*/
	/*
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && internalTime >= 300) {
				if (controlKart) { // If the player is currently controlling the cart and toggles control, will change the light's color to indicate the change
					dynamic_cast<LightBall*>(allModels[0])->setColor(vec3(0.5f, 1.0f, 0.3f));
					pointLight.updateColor(vec3(0.5f, 1.0f, 0.3f));
				}
				else { // The light ball's color will return to white when not being controlled
					dynamic_cast<LightBall*>(allModels[0])->setColor(vec3(1.0f));
					pointLight.updateColor(vec3(1.0f));
				}
				controlKart = !controlKart; //toggles controlKart variable
				internalTime = 0; // resets internalTime once space is pressed
			}
	*/

	// Gets movement inputs
	/* allModels[0]-> Light Ball | allModels[1 - 3]-> Kart parts
									- allModels[1] : Kart Livery (main body)
									- allModels[2] : Kart Wheels
									- allModels[3] : Kart Wheel Covers
	*/
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (controlKart) {
			allModels[PLYR_IDX_KL]->updateRotation('w');
			allModels[PLYR_IDX_WL]->updateRotation('w');
			allModels[PLYR_IDX_WC]->updateRotation('w');
		}
		else {
			allModels[0]->updateRotation('w');
			pointLight.rotateLight('w');
		}
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (controlKart) {
			allModels[PLYR_IDX_KL]->updateRotation('s');
			allModels[PLYR_IDX_WL]->updateRotation('s');
			allModels[PLYR_IDX_WC]->updateRotation('s');
		}								  
		else {							  
			allModels[0]->updateRotation('s');
			pointLight.rotateLight('s');
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (controlKart) {
			allModels[PLYR_IDX_KL]->updateRotation('a');
			allModels[PLYR_IDX_WL]->updateRotation('a');
			allModels[PLYR_IDX_WC]->updateRotation('a');
		}								  
		else {							  
			allModels[0]->updateRotation('a');
			pointLight.rotateLight('a');
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (controlKart) {
			allModels[PLYR_IDX_KL]->updateRotation('d');
			allModels[PLYR_IDX_WL]->updateRotation('d');
			allModels[PLYR_IDX_WC]->updateRotation('d');
		}								  
		else {							  
			allModels[0]->updateRotation('d');
			pointLight.rotateLight('d');
		}
	}

	//Morning and Night
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) skyboxTex = MORNING;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) skyboxTex = NIGHT;

	// Keyboard rotation for the perspective camera, will only accept inputs when its being controlled
	if(controlPersCam){
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) persCam.rotateWithKeys('i');
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) persCam.rotateWithKeys('k');
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) persCam.rotateWithKeys('j');
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) persCam.rotateWithKeys('l');
	}

	// Controls for the light brightness for both the point and direction light
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)	  pointLight.adjustBrightness(UP);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  pointLight.adjustBrightness(DOWN);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)  dirLight.adjustBrightness(LEFT);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) dirLight.adjustBrightness(RIGHT);

	// Switch camera view: true (key 1) for perspective camera, false (key 2) for orthographic camera
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) controlPersCam = true;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) controlPersCam = false;

	// Press escape to end the program (since cursor is disabled)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);
}

// Handles mouse rotation
void Game::mouseInput() {
	persCam.rotateWithMouse(&prevMousePos, &currMousePos);
}

/*
	The main game loop.
*/
void Game::runLoop() {
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		internalTime++; // variable for cooldown on toggling

		checkInput(); // input handling

		/* Camera updating
			 - If the controlPersCam is true, it will use the perspective camera
			 - Else, it uses the orthographic camera
		*/
		setVAO(&skyboxVAO, BIND);

		if (controlPersCam) {
			skybox->draw(persCam.getView(), persCam.getProjection(), skyboxTex);
			glfwGetCursorPos(window, &currMousePos.x, &currMousePos.y);
			persCam.update();
			mouseInput();
			persCam.checkCameraRotation();
		} 
		else {
			skybox->draw(orthoCam.getView(), orthoCam.getProjection(), skyboxTex);
			orthoCam.update();
		}

		// Draws each model with their appropriate shaders and textures
		for (Model3D* model : allModels) {
			// Gets the shader program of the model and uses it
			glUseProgram(model->getShader().getShaderProg());

			// Changes camera depending on which one is selected
			if(controlPersCam) persCam.draw(model->getShader().getShaderProg());
			else orthoCam.draw(model->getShader().getShaderProg());
			
			// If the model is the kart, load the corresponding information
		    if (model->getName() != "LIGHT_BALL") {
				// Loads the lights
				dirLight.loadDir(model->getShader().getShaderProg(), "dir");
				pointLight.loadPoint(model->getShader().getShaderProg(), "point");

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
			}
			// If the model is the light ball, set active VAO to the light ball VAO
			else if (model->getName() == "LIGHT_BALL"){
				setVAO(&light_ballVAO, BIND);
			}

			// Draw the model
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