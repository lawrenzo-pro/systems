#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){ 
    //replace these with your respective paths.
    char *read_file = "/home/lawrence/Projects/systems/hello_syscalls/hello_world.txt";
    char *write_file = "/home/lawrence/Projects/systems/hello_syscalls/goodbye_world.txt";
    int readfd = open(read_file,O_RDONLY);
    if(readfd == -1){
        printf("An error occured!: readfd\n");
        return -1;
    }
    const int bytes = 100;
    char buff[bytes];
    ssize_t retval = read(readfd,buff,bytes);
    if(retval == -1){
        printf("An error occured: read\n");
        return -1;
    }
    if(retval == 0){
        printf("Reached end of file!\n");
        return 0;
    }
    printf("%s\n",buff);//Adding the write routine messes up the output.Will fix later.
    close(readfd);
    int writefd = open(write_file,O_WRONLY|O_CREAT,0644);//forgetting the file permissions leads to interesting errors
    if(writefd == -1){
        printf("An error occurred: writefd\n");
        return -1;
    }
    char *w_buff = "Goodbye,lonely world!";
    ssize_t write_ret = write(writefd,w_buff,strlen(w_buff));
    if(write_ret == -1){
        printf("Error writing to file!\n");
        return 0;
    }
    close(writefd);

    int testfd = open(write_file, O_RDONLY);
    if(testfd == -1){
        printf("Error opening the file.\n");
        return -1;
    }
    char goodbye[100];
    ssize_t read_ret = read(testfd,goodbye,bytes);
    if(read_ret == -1){
        printf("Error reading from file descriptor!\n");
        return -1;
    }
    printf("%s\n", goodbye);
    close(testfd);
    return 0;
}