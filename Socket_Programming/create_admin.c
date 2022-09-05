#include "user.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    int fd = open("admin_data",O_CREAT|O_RDWR,0744);
    struct admin adm;
    strcpy(adm.username,"admin1");
    strcpy(adm.password,"passwd");
    adm.flag = 0;
    write(fd,&adm,sizeof(adm));
    int fd1 = open("Joint_user_data",O_CREAT|O_RDWR,0744);
    int fd2 = open("Single_user_data",O_CREAT|O_RDWR,0744);
    close(fd);
    close(fd1);
    close(fd2);
}