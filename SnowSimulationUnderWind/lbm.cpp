#include "lbm.h"


LatticeBoltzmann::LatticeBoltzmann() {

	// �S�i�q��df�������v�Z����
	for (int j = 0; j < NX*NY; j++)
		for (int k = 0; k < 9; k++) {
			//df[0][j][k] = df[1][j][k] = w[k];
			float rho = 1.0;
			float ux = 0.0;
			float uy = 0.0;

			df[0][j][k] = df[1][j][k] = w[k] * rho * (1.0f - (3.0f / 2.0f) * (ux*ux + uy*uy) + 3.0f * (ex[k] * ux + ey[k] * uy) + (9.0f / 2.0f) * (ex[k] * ux + ey[k] * uy) * (ex[k] * ux + ey[k] * uy));
		}

}

LatticeBoltzmann::LatticeBoltzmann(const LatticeBoltzmann& orig) {}

LatticeBoltzmann::~LatticeBoltzmann() {}

void LatticeBoltzmann::createObstacle(CellType* f) {

	for (int j = 0; j < NX*NY; j++)
		f[j] = FLUID;

	// obstacle
	int R2 = 10;
	for (int i = (NX - R2) / 4; i < (NX - R2) / 4 + 5; i++)
		for (int j = 0; j < (NY - R2) / 3 + R2; j++)
			f[i + j * NX] = OBSTACLE;

}

// we use BGK single relaxation time model with no relaxation on the bounceback nodes Zou, He, 1997
void LatticeBoltzmann::update(const CellType* flag) {

	// swap buffer
	static int c = 1;
	c = 1-c;

	// ���t���[��MPM�̊i�q�̃t���O���Q�Ƃ���

	// �S�i�q�ɂ���
	for(int i = 0 ; i < NX; i++)
		for (int j = 0; j < NY; j++) {

			float relaxation = 1.95;

			// ���̊i�q�̂݌v�Z
			if (flag[i + j * NX] == FLUID) {
				float rho = 0, ux = 0, uy = 0;

				// calculate density and velocity using neighbor cell
				for (int k = 0; k < 9; k++) {
					rho += df[c][i + j*NX][k];			// ------- (1)
					ux += df[c][i + j*NX][k] * ex[k];		// ------- (2)
					uy += df[c][i + j*NX][k] * ey[k];
				}

				ux /= rho;
				uy /= rho;

				
				// Boundary
				if (i == 0 || i == NX - 1) {
					rho = 1.0;
					ux = 0.03;
					uy = 0.0;
					relaxation = 1;
				}

				// Boundary
				if (j == 0 || j == NY - 1) {
					rho = 1.0;
					ux = 0;
					uy = 0.0;
					relaxation = 1;
				}

				U[i + j*NX][0] = ux;
				U[i + j*NX][1] = uy;
				R[i + j*NX] = rho;

				//ux = ux + fx;

				// update neighbor df
				for (int k = 0; k < 9; k++) {
					int ip = (i + ex[k] + NX) % (NX);
					int jp = (j + ey[k] + NY) % (NY);

					// collision + streaming
					if (flag[ip + jp * NX] == OBSTACLE) {
						// Reflect
						// BGK model
						df[1 - c][i + j*NX][inv[k]] = (1 - relaxation) * df[c][i + j*NX][k] + relaxation* w[k] * rho * (1.0f - (3.0f / 2.0f) * (ux*ux + uy*uy) + 3.0f * (ex[k] * ux + ey[k] * uy) + (9.0f / 2.0f) * (ex[k] * ux + ey[k] * uy) * (ex[k] * ux + ey[k] * uy));
					}
					else
						df[1 - c][ip + jp*NX][k] = (1 - relaxation) * df[c][i + j*NX][k] + relaxation* w[k] * rho * (1.0f - (3.0f / 2.0f) * (ux*ux + uy*uy) + 3.0f * (ex[k] * ux + ey[k] * uy) + (9.0f / 2.0f) * (ex[k] * ux + ey[k] * uy) * (ex[k] * ux + ey[k] * uy));
				}
			}
			else {
				U[i + j*NX][0] = 0;
				U[i + j*NX][1] = 0;
				R[i + j*NX] = 1.0;
			}
		}
}


void LatticeBoltzmann::draw(const CellType* flag) {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	for (int i = 0; i < NX; i++)
		for (int j = 0; j < NY; j++) {

			//if(flag[i + j * NX] == OBSTACLE) glColor4f(0, 0, 1, 1);
			/*else*/ glColor4f(U[i + j*NX][0]*100, U[i + j*NX][1]*100, 0, 1);

			glBegin(GL_POLYGON);
			glVertex2d(WIN_METERS_X * (i / (float)NX), (j / (float)NY));
			glVertex2d(WIN_METERS_X * (i / (float)NX), ((j + 1) / (float)NY));
			glVertex2d(WIN_METERS_X * ((i + 1) / (float)NX), ((j + 1) / (float)NY));
			glVertex2d(WIN_METERS_X * ((i + 1) / (float)NX), (j / (float)NY));
			glEnd();

		}
	
}


