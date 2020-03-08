#include <stdio.h>
//#include <math.h>
#include "linalg.h"
#include <stdlib.h>
#include <errno.h>



static Matrix alloc_mat(int x,int y){
	
	//x:rows,y:cols
	Matrix retMat = malloc(sizeof(Matrix));
	retMat->xdim = x;
	retMat->ydim = y;
	retMat->mat = malloc(x*sizeof(float*));
	if(retMat->mat == NULL){
		fprintf(stderr,"out of mem\n");
		exit(0);
	}
	for(int i=0;i<x;i++){
		retMat->mat[i] = malloc(y*sizeof(float));
		if(retMat->mat[i] == NULL){
			fprintf(stderr,"out of mem\n");
			exit(0);
		}
	}
	
	return retMat;
}

Matrix zeros(int dimX, int dimY){

	Matrix retMat = alloc_mat(dimX,dimY); 

	for (int x=0;x<dimX;x++){
		for (int y=0;y<dimY;y++){
			retMat->mat[x][y] = 0;
	
		}
	}
	return retMat;
}


Matrix eye(int dim){

	Matrix retMat = zeros(dim,dim);
	for(int i=0;i<dim;i++){
		retMat->mat[i][i] = 1;
	}
	return retMat;

}



float dot_prod(float* a, float* b, size_t n){

	float sum = 0.0;
	for (size_t i=0;i<n;i++){
		sum += a[i]*b[i];
	}
	return sum;

}

void printMatrix(Matrix a){

	int x = a->xdim;
	int y = a->ydim;

	for (int i=0;i<x;i++){
		for (int j=0;j<y;j++){
			printf("%f ",a->mat[i][j]);

		}
		printf("\n");
	}	
	printf("Matrix Shape: [%d,%d]\n",x,y);
}

void freeMatrix(Matrix a){
	int x = a->xdim;
	int y = a->ydim;


	for (int i=0;i<x;i++){
		free(a->mat[i]);
	}
	free(a);	

}

int main(){

	Matrix test = zeros(5,5);	
	printMatrix(test);
	Matrix diag = eye(5);
	printMatrix(diag);
	free(diag);
	free(test);
}
