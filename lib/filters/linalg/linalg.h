

typedef struct {

	int xdim;
	int ydim;
	float** mat;

}matrix;

typedef matrix* Matrix;

	


Matrix zeros(int dimX, int dimY);




float dot_prod(float* a, float* b,size_t n);
