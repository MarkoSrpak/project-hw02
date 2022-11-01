#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "io.h"


void main(){
    int fd = open("./bin/file1.bin", O_WRONLY | O_CREAT, 00666);
    int a = 0x12345678;
    write_word(fd, a);
    write_word(fd, a);
    close(fd);
    
    fd = open("./bin/file1.bin", O_RDONLY, 00666);
    int b = read_word(fd);
    printf("%d\n", b);
    close(fd);
    return;
}