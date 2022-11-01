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

    // kreiranje signala F
    cmplx_t F[SAMPLE_SIZE];
    int fd = open("./bin/F.bin", O_RDONLY, 00666);
    for(int i = 0; i < SAMPLE_SIZE; i++){
        int re = read_word(fd);
        int im = read_word(fd);
        void *rep = (void *) &re;
        void *imp = (void *) &im;
        F[i][0] = *((float *) rep);
        F[i][1] = *((float *) imp);
    }
    close(fd);

    //originalni signal f
    cmplx_t f[SAMPLE_SIZE];
    for(int i = 0; i < SAMPLE_SIZE; i++){
        float t = i / F_SAMPLE;
        f[i][0] = sinf(2*M_PI * 50 * t);
        f[i][1] = 0;
    }

    // rekreiranje originalnog signala f pomocu idft
    cmplx_t f2[SAMPLE_SIZE];
    cmplx_idft(F, f2, SAMPLE_SIZE);

    //usporedba dobivenog signala (f2) i originalnog (f)
    for(int i = 0; i < SAMPLE_SIZE; i++){
        float re_dif = f2[i][0] - f[i][0];
        float im_dif = f2[i][1] - f[i][1];
        if(re_dif > ALLOWABLE_ERROR || im_dif > ALLOWABLE_ERROR){
            printf("Dobiveni signal nije isti!\n");
            return;
        }
    }

    //ako smo stigli do ovdje znaci da su signali isti
    printf("Dobiveni signal je isti.\n");

    return;
}