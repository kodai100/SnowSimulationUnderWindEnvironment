#ifndef MAIN_H
#define MAIN_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Particle.h"
#include "PointCloud.h"
#include "Grid.h"
#include "SimConstants.h"
#include "Shape.h"
#include "SnowSimulation.h"
#include "Scene.h"

#include "lbm.h"
#include "lbmparticles.h"

using namespace std;

bool showGrid = true;

int frame_count;
vector<Shape*> snow_shapes;
SnowSimulation* snow_simulator;

void start();
void update();
void render();

// GLFW
GLFWwindow* initGLFWContext();
static void error_callback(int, const char*);
void key_callback(GLFWwindow*, int, int, int, int);
void mouse_callback(GLFWwindow*, int, int, int);

// GL
void initGLContext();




#endif
