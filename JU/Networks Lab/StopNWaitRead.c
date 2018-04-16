#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>
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
	ackmes.type=1;
	message.txt[0]='D';
	while(message.txt[0] != 'Q'){
		msgrcv(mid, &message, sizeof(message), 1,0);
		int dd = (int)rand()%5;
		if(dd == 1){
			printf("Frame Damaged\n");
			ackmes.txt[0]='D';
			msgsnd(aid, &ackmes, sizeof(ackmes), 0);
		}
		else{
			printf("Data Received: %s\n", message.txt);
			ackmes.txt[0]='S';
			msgsnd(aid, &ackmes, sizeof(ackmes), 0);
		}		
	}
	msgctl(mid, IPC_RMID, NULL);
	
	return 1;
}
