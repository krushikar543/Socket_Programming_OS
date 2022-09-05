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

void startpage(int c_fd);
void single_user_page(int c_fd){

    printf("\n\n1. Deposit Cash\n");
    printf("2. Withdraw cash\n");
    printf("3. Check Balance\n");
    printf("4. Change Password\n");
    printf("5. View Account Details\n");
    printf("0. Exit\n");
    printf("Enter a appropiate Choice : ");
    int ch,cash,opt,bal,bal1;
    char pw[20],email_id[50],ph_no[10],username[50];
    scanf("%d",&ch);
    switch(ch){
        case 1:
            printf("\nEnter the Amount of Cash you want to Deposit : ");
            scanf("%d",&cash);
            opt=11;
            send(c_fd,&opt,sizeof(opt),0);
            send(c_fd,&cash,sizeof(cash),0);
            printf("Amount Deposited in Bank Successfully");
            single_user_page(c_fd);
        case 2:
            printf("\nEnter the amount of Cash you want to withdraw : ");
            scanf("%d", &cash);
            opt = 12;
            //change little code
            send(c_fd,&opt,sizeof(opt),0);
            send(c_fd,&cash,sizeof(cash),0);
            recv(c_fd,&bal,sizeof(bal),0);
            if(bal > cash){
                recv(c_fd,&bal,sizeof(bal),0);
                printf("\nAmount Withdrawn : %d\n",cash);
                printf("Balance left : %d\n",bal);
            }
            else{
                recv(c_fd,&bal,sizeof(bal),0);
                printf("Can not Withdraw %d from bank as back balance is %d\n",cash,bal);
            }
            single_user_page(c_fd);
            break;
        case 3:
            opt = 13;
            send(c_fd,&opt,sizeof(opt),0);
            recv(c_fd,&bal,sizeof(bal),0);
            printf("\nBank Balance : %d\n",bal);
            single_user_page(c_fd);
            break;
        case 4:
            opt = 14;
            send(c_fd,&opt,sizeof(opt),0);
            printf("\nEnter New Password : ");
            scanf("%s",pw);
            send(c_fd,pw,sizeof(pw),0);
            printf("\nPassword Changed Successfully\n");
            single_user_page(c_fd);
            break;
        case 5:
            opt = 15;
            send(c_fd,&opt,sizeof(opt),0);
            recv(c_fd,username,sizeof(username),0);
            recv(c_fd,email_id,sizeof(email_id),0);
            recv(c_fd,ph_no,sizeof(ph_no),0);
            printf("\nDatails : \n");
            printf("Usename : %s\n",username);
            printf("email : %s\n",email_id);
            printf("Phone Number : %s\n",ph_no);
            single_user_page(c_fd);
            break;
        case 0:
            startpage(c_fd);
            break;
        default:
            printf("Enter Valid Choice\n");
            single_user_page(c_fd);
            break;

    }
}
void joint_user_page(int c_fd){
    printf("\n\n1. Deposit Cash\n");
    printf("2. Withdraw cash\n");
    printf("3. Check Balance\n");
    printf("4. Change Password\n");
    printf("5. View Account Details\n");
    printf("0. Exit\n");
    printf("Enter a appropiate Choice : ");
    int ch,cash,opt,bal,bal1;
    char pw[20],email_id[50],ph_no[10],username[50];
    scanf("%d",&ch);
    switch(ch){
        case 1:
            printf("\nEnter the Amount of Cash you want to Deposit : ");
            scanf("%d",&cash);
            opt=21;
            send(c_fd,&opt,sizeof(opt),0);
            send(c_fd,&cash,sizeof(cash),0);
            printf("\nAmount Deposited in Bank Successfully\n");
            joint_user_page(c_fd);
        case 2:
            printf("\nEnter the amount of Cash you want to withdraw : ");
            scanf("%d", &cash);
            opt = 22;
            
            send(c_fd,&opt,sizeof(opt),0);
            send(c_fd,&cash,sizeof(cash),0);
            recv(c_fd,&bal,sizeof(bal),0);
            if(bal >= cash){
                recv(c_fd,&bal,sizeof(bal),0);
                printf("\nAmount Withdrawn : %d\n",cash);
                printf("Balance left : %d\n",bal);
            }
            else{
                recv(c_fd,&bal,sizeof(bal),0);
                printf("\nCan not Withdraw %d from bank as back balance is %d\n",cash,bal);
            }
            joint_user_page(c_fd);
            break;
        case 3:
            opt = 23;
            send(c_fd,&opt,sizeof(opt),0);
            recv(c_fd,&bal,sizeof(bal),0);
            printf("Bank Balance : %d",bal);
            joint_user_page(c_fd);
            break;
        case 4:
            opt = 24;
            send(c_fd,&opt,sizeof(opt),0);
            printf("\nEnter New Password : ");
            scanf("%s",pw);
            send(c_fd,pw,sizeof(pw),0);
            printf("\nPassword Changed Successfully\n");
            joint_user_page(c_fd);
            break;
        case 5:
            opt = 25;
            send(c_fd,&opt,sizeof(opt),0);
            printf("\nDatails : ");
            
            for(int i=0;i<2;i++){
                recv(c_fd,username,sizeof(username),0);
                recv(c_fd,email_id,sizeof(email_id),0);
                recv(c_fd,ph_no,sizeof(ph_no),0);
                printf("\nUsename : %s\n",username);
                printf("email : %s\n",email_id);
                printf("Phone Number : %s\n",ph_no);
            }
            joint_user_page(c_fd);
            break;
        case 0:
            startpage(c_fd);
            break;
        default:
            printf("Enter Valid Choice\n");
            single_user_page(c_fd);
            break;

    }
}
void admin_page(int c_fd){
    printf("\n1. Add Single user Account\n");
    printf("2. Add Joint user Account\n");
    printf("3. Delete a Single user Account\n");
    printf("4. Delete a joint User Account\n");
    printf("0. Exit");
    
    printf("\nEnter a Valid Choice : ");
    int ch,opt;
    scanf("%d",&ch);
    struct single_user su;
    struct joint_user ju;
    char email[2][50],ph_no[2][10],username[2][50],password[2][20];
    switch(ch){
        case 1:
            opt = 31;
            send(c_fd,&opt,sizeof(opt),0);
            su.flag = 0;
            printf("\nEnter Username : ");
            scanf("%s",su.username);
            printf("\nEnter Password : ");
            scanf("%s",su.password);
            printf("\nEnter Email_id : ");
            scanf("%s",su.email_id);
            printf("\nEnter Phone Number : ");
            scanf("%s",su.ph_no);
            printf("\nEnter The money you are depositing : ");
            scanf("%d",&su.bal);
            send(c_fd,&su,sizeof(su),0);
            printf("New User(Account) has been added successfully");
            admin_page(c_fd);
            break;
        case 2:
            opt = 32;
            send(c_fd,&opt,sizeof(opt),0);
            ju.flag = 0;
            char email_id[2][50],ph_no[2][10],username[2][50],pass[2][20];
            printf("Enter Details of \n");
            for(int i=0;i<2;i++){
                printf("User%d\n",i);
                printf("\nEnter Username : ");
                scanf("%s",ju.u[i].username);
                printf("\nEnter Password");
                scanf("%s",ju.u[i].password);
                printf("\nEnter Email_id : ");
                scanf("%s",ju.u[i].email_id);
                printf("\nEnter Phone Number : ");
                scanf("%s",ju.u[i].ph_no);

            }
            printf("\nEnter Money to be deposited : ");
            scanf("%d",&ju.bal);
            ju.count = 2;
            send(c_fd,&ju,sizeof(ju),0);
            printf("\nJoint user Account Has been added Successfully\n");
            admin_page(c_fd);
            break;
        case 3:
            opt = 33;
            send(c_fd,&opt,sizeof(opt),0);
            printf("\nEnter Username of the Account you want to delete : ");
            scanf("%s",su.username);
            send(c_fd,su.username,sizeof(su.username),0);
            printf("\nSingle User Account Successfully deleted\n");
            admin_page(c_fd);
            break;
        case 4:
            opt = 34;
            send(c_fd,&opt,sizeof(opt),0);
            printf("\nEnter Username of the Account to be deleted:");
            scanf("%s",ju.u[0].username);
            send(c_fd,ju.u[0].username,sizeof(ju.u[0].username),0);
            printf("\nJoint User Account Successfully deleted\n");
            admin_page(c_fd);
            break;
        case 0:
            startpage(c_fd);
            break;
        default:
            printf("\nPlease Enter a Valid Option\n");
            admin_page(c_fd);
            break;
    }
}

void authenticate(int c_fd,int n){
    send(c_fd,&n,sizeof(n),0);
    char username[50],password[20];
    struct admin adm;
    printf("\nPlease Enter your UserName : ");
    scanf("%s",username);
    printf("\nEnter Password : ");
    scanf("%s",password);
    send(c_fd,username,sizeof(username),0);
    send(c_fd,password,sizeof(password),0);
    int check;
    recv(c_fd,&check,sizeof(check),0);
    if(check == 0){
        if(n == 1) single_user_page(c_fd);
        else if(n == 2) joint_user_page(c_fd);
        else if(n == 3) admin_page(c_fd);
    }
    else{
        printf("\nUsername does not exit / Incorrect Password\n");
        authenticate(c_fd,n);
    }
}

void startpage(int c_fd){
    printf("Welcome to the bank\n\nLogin as");

    printf("\n1. Single User\n");
    printf("2. Joint User\n");
    printf("3. Admin\n");
    printf("0. Exit\n");
    int ch;
    scanf("%d",&ch);
    switch(ch){
        case 1:
            authenticate(c_fd,1);
            break;
        case 2:
            authenticate(c_fd,2);
            break;
        case 3:
            authenticate(c_fd,3);
            break;
        case 0:
            exit(0);
        default:
            printf("Please enter a Valid Option\n");
            startpage(c_fd);
            break;
    }
}
int main(){
     int c_fd;
    if((c_fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("Socket Failed");
        exit(0);
    }

    printf("Starting Client\n");
    struct sockaddr_in str;
    str.sin_family = AF_INET;
    str.sin_port = htons(PORT);
    if(inet_pton(AF_INET,"127.0.0.1",&str.sin_addr) <= 0)
    {
        perror("IP Address Problem:");
        return 1;
    }
    if(connect(c_fd,(struct sockaddr*)&str,sizeof(str)) == -1)
    {
        perror("Connect Failed:");
        return 1;
    }
    startpage(c_fd);
    return 0;
}
