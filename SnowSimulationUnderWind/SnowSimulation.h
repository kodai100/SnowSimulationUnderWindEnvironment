#ifndef SNOWSIM_H
#define	SNOWSIM_H

#include "PointCloud.h"
#include "Grid.h"
#include <stdlib.h>
#include "Particle.h"
#include "PointCloud.h"
#include "Grid.h"
#include "SimConstants.h"
#include "Shape.h"
#include "Scene.h"

#include "lbm.h"

class SnowSimulation {
public:
	int frameCount;
	Grid* grid;
	PointCloud* snow;

	CellType flag[NX*NY];

	SnowSimulation(Scene* scene);
	SnowSimulation(const SnowSimulation& orig);
	virtual ~SnowSimulation();

	void update(CellType* flag, LatticeBoltzmann* boltzmann);
};


#endif