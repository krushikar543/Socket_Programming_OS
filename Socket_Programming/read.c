#include "user.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main(){
	int fd = open("Single_user_data",O_RDWR);
	struct single_user su;
	while(read(fd,&su,sizeof(struct single_user))){
		printf("%d\n",su.bal);
		printf("%s\n",su.email_id);
		printf("%d\n",su.flag);
		printf("%s\n",su.username);
		printf("%s\n",su.password);
		printf("%s\n",su.ph_no);
		printf("\n");
	}
	close(fd);
	return 0;
}
