#include <stdio.h>
#include <math.h>
#include "cmplx.h"


void main(){
	cmplx_t signal1[10];
	cmplx_t signal2[10];
	for(int i = 0; i < 10; i++){
		signal1[i][0] = i+3;
	//	signal1[i][1] = 10*i;
	}


	cmplx_dft(signal1, signal2, 10);

	for(int i = 0; i < 10; i++){
		printf("%.2f%+.2fi -> %.2f%+.2fi\n", signal1[i][0], signal1[i][1],
			signal2[i][0], signal2[i][1]);
	}
	printf("\n");


	cmplx_idft(signal2, signal1, 10);
	
	for(int i = 0; i < 10; i++){
		printf("%.2f%+.2fi -> %.2f%+.2fi\n", signal2[i][0], signal2[i][1],
			signal1[i][0], signal1[i][1]);
	} 


	return;
}