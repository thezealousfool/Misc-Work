#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>
struct mesbuf{
	long type;
	char txt[100];
} message, ackmes;
int main(){
	key_t key, keyack;
	int mid, aid;
	key = 12; //ftok("Buffer", 65);
	mid = msgget(key, 0666 | IPC_CREAT);
	ackmes.type=1;
	message.txt[0]='D'; msgctl(mid, IPC_RMID, NULL);
	while(message.txt[0] != 'Q'){
	  int i = 1;
	  for(;i<1000000;i++);
	  	msgrcv(mid, &message, sizeof(message), 1,0);
	  //	msgsnd(aid, &message, sizeof(message), 0);
	  	printf("%s Forwarded\n",message);		
	}
	msgctl(mid, IPC_RMID, NULL);
	
	return 1;
}
