#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mesbuf{
	long type;
	char txt[100];
} message, ackmes;
int main(int argc, int **argv){
	key_t key, keyack;
	int mid, aid;
	key = ftok("progfile",65);
	keyack = ftok("Acknowledgement",65);
	mid = msgget(key + argc, 0666 | IPC_CREAT);
	aid = msgget(keyack + argc, 0666 | IPC_CREAT);
	message.type=1;
	message.txt[0]='D';
	while(message.txt[0] != 'Q'){
		printf("Write Data : ");
		gets(message.txt);
		if(message.txt[0]=='Q')break;
		msgsnd(mid, &message, sizeof(message), 0);
		printf("Data Sent: %s\n",message.txt);
		sleep(100);
		msgrcv(mid, &ackmes, sizeof(message), 1,0);
		while(ackmes.txt[0] == 'D'){
			printf("Damage\n");
			msgsnd(mid, &message, sizeof(message), 0);
			printf("Data Sent: %s\n",message.txt);
			msgrcv(mid, &ackmes, sizeof(message), 1,0);
		}
		printf("Successful\n");
		
	}

	return 0;
}
