#include "Visualizer.h"

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void Visualizer::run() {
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MusicVisualizer", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		exit(-1);
	}

	Shader shader = Shader("ShaderVertex.glsl", "ShaderFragment.glsl");

	// create meshes
	int barNum = 10;
	Mesh *meshes = new Mesh[barNum];

	for (int idx = 0; idx < barNum; idx++) {
		meshes[idx].setVertices(idx, barNum); // set x coordinate
		meshes[idx].setupMesh();
		meshes[idx].loadTexture("../blue.jpg");
	}

	MusicManager player;
	player.loadMusic("../sample.mp3");
	player.playMusic();

	// initialize spectrum
	int size = player.initSpectrum(12);
	float *frequencies = new float[size]();

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		// get frequency
		player.getFrequency(frequencies);

		for (int i = 0; i < barNum; i++) {
			float yCoordinate = frequencies[i];
			float corr = yCoordinate * pow(2, i);
			meshes[i].draw(shader, corr);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	
	delete[] meshes;
	delete[] frequencies;
}
