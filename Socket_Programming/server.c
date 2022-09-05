#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#define PORT 2000

int balance_single(char uname[],char pass[]);
int balance_joint(char uname[],char pass[]);

int verify_user(char uname[],char pass[]){
    int fd = open("Single_user_data",O_RDWR);
    struct single_user su;
    while(read(fd,&su,sizeof(struct single_user))){
        if(strcmp(uname,su.username) == 0 && strcmp(pass,su.password) == 0 && su.flag == 0){
            close(fd);
            return 0;
        }
    }
    close(fd);
    return 1;
}
int verify_joint_user(char uname[],char pass[]){
    int fd = open("Joint_user_data",O_RDWR);
    struct joint_user ju;
    while(read(fd,&ju,sizeof(struct joint_user))){
        for(int i=0;i<2;i++){
            if(strcmp(uname,ju.u[i].username) == 0 && strcmp(pass,ju.u[i].password) == 0 && ju.flag == 0){
                close(fd);
                return 0;
            }
        }
    }
    close(fd);
    return 1;
}
int verify_admin(char uname[],char pass[]){
    int fd = open("admin_data",O_RDWR);
    struct admin adm;
    while(read(fd,&adm,sizeof(struct admin))){
        if(strcmp(uname,adm.username) == 0 && strcmp(pass,adm.password) == 0 && adm.flag == 0){
            close(fd);
            return 0;
        }
    }
    close(fd);
    return 1;
}
int deposit_money_to_user(char uname[],char pass[], int cash){
    int fd = open("Single_user_data",O_RDWR);
    struct single_user su;
    while(read(fd,&su,sizeof(struct single_user))){
        if(strcmp(uname,su.username) == 0 && strcmp(pass,su.password) == 0 && su.flag == 0){
            su.bal+=cash;
            lseek(fd,-1*sizeof(su),SEEK_CUR);
            write(fd,&su,sizeof(su));
            close(fd);
            return 0;
        }
    }
}
void deposit_money_to_joint_user(char uname[],char pass[], int cash){
    int fd = open("Joint_user_data",O_RDWR);
    struct joint_user ju;
    while(read(fd,&ju,sizeof(struct joint_user))){
        for(int i=0;i<2;i++){
            if(strcmp(uname,ju.u[i].username) == 0 && strcmp(pass,ju.u[i].password) == 0 && ju.flag == 0){
                struct flock lock;
                lock.l_type=F_WRLCK;
                lock.l_whence=SEEK_CUR;
                lock.l_start=-1*sizeof(struct joint_user);
                lock.l_len=sizeof(struct joint_user);
                lock.l_pid=getpid();
                fcntl(fd,F_SETLKW,&lock);
                ju.bal+=cash;
                lseek(fd,-1*sizeof(struct joint_user),SEEK_CUR);
                write(fd,&ju,sizeof(ju));
                lock.l_type = F_UNLCK;
                fcntl(fd,F_SETLK,&lock);
                close(fd);
                return;
            }
        }
    }
}
int balance_single(char uname[],char pass[]){
    int fd = open("Single_user_data",O_RDWR);
    struct single_user su;
    int cash;
    while(read(fd,&su,sizeof(struct single_user))){
        if(strcmp(uname,su.username) == 0 && strcmp(pass,su.password) == 0 && su.flag == 0){
            cash = su.bal;
            close(fd);
            return cash;
        }
    }
}
int balance_joint(char uname[],char pass[]){
    int fd = open("Joint_user_data",O_RDWR);
    struct joint_user ju;
    int cash;
    while(read(fd,&ju,sizeof(struct joint_user))){
        for(int i=0;i<2;i++){
            if(strcmp(uname,ju.u[i].username) == 0 && strcmp(pass,ju.u[i].password) == 0 && ju.flag == 0){
                cash = ju.bal;
                close(fd);
                return cash;
            }
        }
    }
}
int passwd_change_user(char uname[],char pass[],char newpass[]){
    int fd = open("Single_user_data",O_RDWR);
    struct single_user su;
    while(read(fd,&su,sizeof(struct single_user))){
        if(strcmp(uname,su.username) == 0 && strcmp(pass,su.password) == 0 && su.flag == 0){
            strcpy(su.password,newpass);
            lseek(fd,-1*sizeof(su),SEEK_CUR);
            write(fd,&su,sizeof(su));
            close(fd);
            return 0;
        }    
    }
}
void passwd_change_joint_user(char uname[],char pass[], char newpass[]){
    int fd = open("Joint_user_data",O_RDWR);
    struct joint_user ju;
    while(read(fd,&ju,sizeof(struct joint_user))){
        for(int i=0;i<2;i++){
            if(strcmp(uname,ju.u[i].username) == 0 && strcmp(pass,ju.u[i].password) == 0 && ju.flag == 0){
                struct flock lock;
                lock.l_type=F_WRLCK;
                lock.l_whence=SEEK_CUR;
                lock.l_start=-1*sizeof(struct joint_user);
                lock.l_len=sizeof(struct joint_user);
                lock.l_pid=getpid();
                fcntl(fd,F_SETLKW,&lock);
                strcpy(ju.u[i].password,newpass);
                lseek(fd,-1*sizeof(struct joint_user),SEEK_CUR);
                write(fd,&ju,sizeof(ju));
                lock.l_type = F_UNLCK;
                fcntl(fd,F_SETLK,&lock);
                close(fd);
                return;
            }
        }
    }
}
struct single_user details_of_user(char uname[],char pass[]){
    int fd = open("Single_user_data",O_RDWR);
    struct single_user su;
    while(read(fd,&su,sizeof(struct single_user))){
        if(strcmp(uname,su.username) == 0 && strcmp(pass,su.password) == 0 && su.flag == 0){
            close(fd);
            return su;
        }    
    }
}
struct joint_user details_of_joint_user(char uname[],char pass[]){
    int fd = open("Joint_user_data",O_RDWR);
    struct joint_user ju;
    while(read(fd,&ju,sizeof(struct joint_user))){
        for(int i=0;i<2;i++){
            if(strcmp(uname,ju.u[i].username) == 0 && strcmp(pass,ju.u[i].password) == 0 && ju.flag == 0){
                close(fd);
               return ju; 
            }
        }
    }
}
void add_user(struct single_user su){
    int fd = open("Single_user_data",O_RDWR);
    lseek(fd,0,SEEK_END);
    write(fd,&su,sizeof(su));
    close(fd);
}
void delete_user(char uname[]){
    int fd = open("Single_user_data",O_RDWR);
    struct single_user su;
     while(read(fd,&su,sizeof(struct single_user))){
        if(strcmp(uname,su.username) == 0 && su.flag == 0){
            su.flag = 1;
            lseek(fd,-1*sizeof(su),SEEK_CUR);
            write(fd,&su,sizeof(su));
            close(fd);
            return;
        }
    }
    
}
void add_joint_user(struct joint_user ju){
    int fd = open("Joint_user_data",O_RDWR);
    lseek(fd,0,SEEK_END);
    write(fd,&ju,sizeof(ju));
    close(fd);
}
void delete_joint_user(char uname[]){
    int fd = open("Joint_user_data",O_RDWR);
    struct joint_user ju;
    while(read(fd,&ju,sizeof(struct joint_user))){
        for(int i=0;i<2;i++){
            if(strcmp(uname,ju.u[i].username) == 0 && ju.flag == 0){
                ju.flag = 1;
                lseek(fd,-1*sizeof(ju),SEEK_CUR);
                write(fd,&ju,sizeof(ju));
                close(fd);
                return;
            }
        }
    }
}
void request(int client_socket){
    while(1){
        char uname[50],pass[20];
        int ch;
        recv(client_socket,&ch,sizeof(ch),0);
        if(ch == 1){
            recv(client_socket,uname,sizeof(uname),0);
            recv(client_socket,pass,sizeof(pass),0);
            int v = verify_user(uname,pass);
            send(client_socket,&v,sizeof(v),0);
        }
        else if(ch == 2){
            recv(client_socket,uname,sizeof(uname),0);
            recv(client_socket,pass,sizeof(pass),0);
            int v = verify_joint_user(uname,pass);
            send(client_socket,&v,sizeof(v),0);
        }
        else if(ch == 3){
            recv(client_socket,uname,sizeof(uname),0);
            recv(client_socket,pass,sizeof(pass),0);
            int v = verify_admin(uname,pass);
            send(client_socket,&v,sizeof(v),0);
        }
        else if(ch == 11){
            int cash;
            recv(client_socket,&cash,sizeof(cash),0);
            deposit_money_to_user(uname,pass,cash);
        }
        else if(ch == 12){
            int cash;
            recv(client_socket,&cash,sizeof(cash),0);
            int bal = balance_single(uname,pass);
            send(client_socket,&bal,sizeof(bal),0);
            if(bal >= cash){
                cash = -1*cash;
                deposit_money_to_user(uname,pass,cash);
                bal = balance_single(uname,pass);
                send(client_socket,&bal,sizeof(bal),0);
            }
            else{
                bal = balance_single(uname,pass);
                send(client_socket,&bal,sizeof(bal),0);
            }
            
        }
        else if(ch == 13){
            int bal = balance_single(uname,pass);
            send(client_socket,&bal,sizeof(bal),0);
        }
        else if(ch == 14){
            char  newpass[20];
            recv(client_socket,newpass,sizeof(newpass),0);
            passwd_change_user(uname,pass,newpass);
            strcpy(pass,newpass);
        }
        else if (ch == 15){
            struct single_user su;
            su = details_of_user(uname,pass);
            send(client_socket,su.username,sizeof(su.username),0);
            send(client_socket,su.email_id,sizeof(su.email_id),0);
            send(client_socket,su.ph_no,sizeof(su.ph_no),0);



        }
        else if(ch == 21){
            int cash;
            recv(client_socket,&cash,sizeof(cash),0);
            deposit_money_to_joint_user(uname,pass,cash);

        }
        else if(ch == 22){
            int cash;
            recv(client_socket,&cash,sizeof(cash),0);
            int bal = balance_joint(uname,pass);
            send(client_socket,&bal,sizeof(bal),0);
            if(bal >= cash){
                cash = -1*cash;
                deposit_money_to_joint_user(uname,pass,cash);
                bal = balance_joint(uname,pass);
                send(client_socket,&bal,sizeof(bal),0);
            }
            else{
                bal = balance_joint(uname,pass);
                send(client_socket,&bal,sizeof(bal),0);
            }
        }
        else if(ch == 23){
            int bal = balance_joint(uname,pass);
            send(client_socket,&bal,sizeof(bal),0);
        }
        else if(ch == 24){
            char newpass[20];
            recv(client_socket,newpass,sizeof(newpass),0);
            passwd_change_joint_user(uname,pass,newpass);
            strcpy(pass,newpass);
        }
        else if (ch == 25){
            struct joint_user ju;
            ju = details_of_joint_user(uname,pass);
            for(int i=0;i<2;i++){
                send(client_socket,ju.u[i].username,sizeof(ju.u[i].username),0);
                send(client_socket,ju.u[i].email_id ,sizeof(ju.u[i].email_id),0);
                send(client_socket,ju.u[i].ph_no,sizeof(ju.u[i].ph_no),0);
            }
        }
        else if(ch == 31){
            struct single_user su;
            recv(client_socket,&su,sizeof(su),0);
            add_user(su);
        }
        else if(ch == 32){
            struct joint_user ju;
            recv(client_socket,&ju,sizeof(ju),0);
            add_joint_user(ju);
        }
        else if(ch == 33){
            struct single_user su;
            recv(client_socket,su.username,sizeof(su.username),0);
            delete_user(su.username);

        }
        else if(ch == 34){
            struct joint_user ju;
            recv(client_socket,ju.u[0].username,sizeof(ju.u[0].username),0);
            delete_joint_user(ju.u[0].username);

        }
    }
}
int main()
{

    int s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd == 0)
    {
        perror("Socket Failed:");
        return 1;
    }
    printf("Starting Server\n");
    struct sockaddr_in str;
    str.sin_addr.s_addr = INADDR_ANY;
    str.sin_family = AF_INET;
    str.sin_port = htons(PORT);
    int size = sizeof(str);
    if (bind(s_fd, (struct sockaddr *)&str, size) == -1)
    {
        perror("Bind Failed:");
        return 1;
    }
    if (listen(s_fd, 3) == -1)
    {
        perror("Listen Failed:");
        return 1;
    }
    while (1)
    {
        int client_socket = accept(s_fd, (struct sockaddr *)&str, (socklen_t *)&size);
        if(fork()){
            close(client_socket);
        }
        else{
            close(s_fd);
            request(client_socket);
            return 0;
        }
    }

    return 0;
}
