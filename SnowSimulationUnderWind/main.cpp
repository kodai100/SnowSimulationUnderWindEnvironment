#include "main.h"

float framerate = 60;
float secPerFrame = 1 / framerate;

LatticeBoltzmann* wind_simulator;
LBMParticle* lbm_particle;
CellType flag[NX*NY];

void update(void)
{
	cout << "Frame: " << frame_count << endl;
	snow_simulator->update(flag, wind_simulator);

	//if (frame_count % 1000 == 0) {
		wind_simulator->update(flag);
		lbm_particle->update(1);
	//}
	
}

void render(void) 
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	if(showGrid) wind_simulator->draw(flag);
	//lbm_particle->draw();								// DRAW PARTICLES


														// Draw grid
	//snow_simulator->grid->draw();

	// Draw snow
	snow_simulator->snow->draw();
}

void start(void)
{

	wind_simulator = new LatticeBoltzmann();
	lbm_particle = new LBMParticle(wind_simulator);


	//Scene* scene = Scene::olaf();
	Scene* scene = Scene::snowman();
	//Scene* scene = Scene::snowmanSmash();
	//Scene* scene = Scene::snowballSmash();
	//Scene* scene = Scene::highspeedSnowballSmash();

	snow_simulator = new SnowSimulation(scene);
}


void exit() {
	delete wind_simulator;
	delete lbm_particle;
}














int main(int argc, char** argv) {

	srand(time(NULL));

	GLFWwindow* window = initGLFWContext();
	initGLContext();

	start();

	frame_count = 0;

	double prevTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {

		// skip frames
		//if (glfwGetTime() - prevTime < secPerFrame) continue;
		prevTime = glfwGetTime();

		update();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		frame_count++;
	}

	//Exit
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	exit();

	return 0;
}

void initGLContext() {
	
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 1280, 640);
	glOrtho(0, WIN_METERS_X, 0, WIN_METERS_Y, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


GLFWwindow* initGLFWContext() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(1280, 640, "Lattice Boltzmann", NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	return window;
}

//Print all errors to console
static void error_callback(int error, const char* description) {
	printf("\nError: %s", description);
}

//Key listener
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_RELEASE)
		return;
	switch (key) {
	case GLFW_KEY_ENTER:
		showGrid = !showGrid;
		break;
	}
}

//Mouse listener
void mouse_callback(GLFWwindow* window, int btn, int action, int mods) {
}