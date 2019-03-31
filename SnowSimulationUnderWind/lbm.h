#ifndef LBM_H
#define LBM_H

#include <GLFW/glfw3.h>
#include "SimConstants.h"
#include "Vector2f.h"

enum CellType { OBSTACLE, FLUID };

class LatticeBoltzmann {
public:

	const int ex[9] = { 0,  1,0,-1, 0,  1,-1,-1, 1 };
	const int ey[9] = { 0,  0,1, 0,-1,  1, 1,-1,-1 };
	const int inv[9] = { 0, 3,4, 1, 2,  7, 8, 5, 6 };
	const float w[9] = { 4.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 36.0f, 1.0f / 36.0f, 1.0f / 36.0f, 1.0f / 36.0f };

	float df[2][NX*NY][9];	// double buffer

	Vector2f U[NX*NY];
	float R[NX*NY];

	float fx = 0.000014;

	LatticeBoltzmann();
	LatticeBoltzmann(const LatticeBoltzmann& orig);
	~LatticeBoltzmann();

	static void createObstacle(CellType* flag);
	void update(const CellType* flag);
	void draw(const CellType* flag);
};
#endif

