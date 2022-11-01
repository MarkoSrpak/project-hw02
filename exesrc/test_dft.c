#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "cmplx.h"
#include "io.h"

#define T_MAX 10      //vrijeme trajanja signala u sec
#define F_SAMPLE 200  //frekvencija otipkavanja signala u Hz
#define SAMPLE_SIZE ((T_MAX) * (F_SAMPLE))
#define ALLOWABLE_ERROR 0.01f   //dopustena pogreska


void main(){

    // kreiranje signala f
    cmplx_t f[SAMPLE_SIZE];
    for(int i = 0; i < SAMPLE_SIZE; i++){
        float t = i / F_SAMPLE;
        f[i][0] = sinf(2*M_PI * 50 * t);
        f[i][1] = 0;
    }

    // kreiranje transformiranog signala F
    cmplx_t F[SAMPLE_SIZE];
    cmplx_dft(f, F, SAMPLE_SIZE);

    //spremanje signala F u datoteku
    int fd = open("./bin/F.bin", O_WRONLY | O_CREAT, 00666);
    for(int i = 0; i < SAMPLE_SIZE; i++){
        void *rep = (void *) &(F[i][0]);
        void *imp = (void *) &(F[i][1]);
        int re = *((int *) rep);
        int im = *((int *) imp);
        write_word(fd, re);
        write_word(fd, im);
    }
    close(fd);

    return;
}