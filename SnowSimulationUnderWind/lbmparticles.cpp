
#include <math.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "lbm.h"
#include "lbmparticles.h"

LBMParticle::LBMParticle(LatticeBoltzmann* boltzmann)
{

	this->boltzmann = boltzmann;

	par = new Vector2f[nparmax];
	dispPar = new Vector2f[nparmax];

	for ( int k=0; k<nparmax; k++)
	{
		while (true) {
			float x = rand() / float(RAND_MAX);
			float y = rand() / float(RAND_MAX);

			//if (boltzmann->FLAG[(int)(x * NX) + (int)(y*NY) * NX] == OBSTACLE) continue;

			par[k][0] = x;
			par[k][1] = y;

			dispPar[k][0] = x;
			dispPar[k][1] = y;

			break;
		}
	}
}

LBMParticle::~LBMParticle() {
	delete[] par;
	delete[] dispPar;
}

const float LBMParticle::BilinearInterpolation(float x,float y,int x1,int x2,int y1,int y2,float f11,float f21,float f22,float f12) const{
	// @Numerical Recipes
	float t = (x-x1) / (x2 - x1);
	float u = (y-y1) / (y2 - y1);
	return (1-t)*(1-u)*f11 + t*(1-u)*f21 + t*u*f22 + (1-t)*u*f12;
}

void LBMParticle::update(float dt)
{
	int i,j,k;
	int ip,jp;
	float x,y;

	for ( k=0; k<nparmax; k++)
	{

		x = par[k][0];
		y = par[k][1];
		
		i = int(x * (NX -1) + NX) % (NX);	// x=0 => i = 0, x=1 => L-2
		j = int(y * (NY -1) + NY) % (NY);
		
		ip = int(x * (NX -1) + NX + 1 ) % (NX);
		jp = int(y * (NY -1)+ NY + 1 ) % (NY);
		
		x = x + BilinearInterpolation(x*(NX-1),y*(NY -1), i,ip, j,jp, boltzmann->U[ i+j*NX ][0], boltzmann->U[ip+j*NX][0], boltzmann->U[ip+jp*NX][0], boltzmann->U[i+jp*NX][0]) * dt;
		y = y + BilinearInterpolation(x*(NX-1),y*(NY -1), i,ip, j,jp, boltzmann->U[ i+j*NX ][1], boltzmann->U[ip+j*NX][1], boltzmann->U[ip+jp*NX][1], boltzmann->U[i+jp*NX][1]) * dt;
		
		
		if (x > 1 || y > 1 || x < 0 || y < 0) {
			x = x - 1;
			y = rand() / float(RAND_MAX);
		}

		par[k][0]	= x;
		par[k][1]	= y;

		dispPar[k][0] = WIN_METERS_X * x;
		dispPar[k][1] = WIN_METERS_Y * y;
		
	}
}

void LBMParticle::draw(void)
{
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_POINT_SMOOTH);
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);

	glPointSize(2);
	glColor4f(0,1,1,1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0, dispPar);
	glDrawArrays(GL_POINTS,0,nparmax);
	glDisableClientState(GL_VERTEX_ARRAY);
}
