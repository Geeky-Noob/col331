#include<stdio.h>
#include<stdlib.h>
int main() {
	int* x = (int*) malloc(100*sizeof(int));
	free(x+5);
	x[23] = 3;
}
