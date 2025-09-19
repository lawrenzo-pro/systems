#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    int file_descrptor = open("/home/lawrence/Projects/systems/hello_syscalls/hello_world.txt",O_RDONLY);
    if(file_descrptor == -1){
        printf("An error occured!: fd\n");
        return -1;
    }
    const int bytes = 100;
    char buff[bytes];
    ssize_t retval = read(file_descrptor,buff,bytes);
    if(retval == -1){
        printf("An error occured: read \n");
        return -1;
    }
    printf("%s\n",buff);
    return 0;
}