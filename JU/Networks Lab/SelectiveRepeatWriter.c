#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mesbuf{
	long type;
	char txt[100];
} message, ackmes, part;
int main(int argc, int **argv){
  key_t key, keyack, bufkey;
	int mid, aid,i,buf;
	key = 34;//ftok("progfile", 65);
	keyack = 45;//ftok("Acknowledgement",65);
	bufkey = 12;//ftok("Buffer",65);
	mid = msgget(key + argc, 0666 | IPC_CREAT);
	aid = msgget(keyack + argc, 0666 | IPC_CREAT);
	buf = msgget(bufkey + argc,0666 | IPC_CREAT);
	message.type=1;
	message.txt[0]='D';
	
	while(message.txt[0] != 'Q'){
		printf("Write Data : ");
		gets(message.txt);
		
		if(message.txt[0]=='Q'){
			part.txt[0]='Q';
			msgsnd(mid, &part, sizeof(part), 0);
			break;
		}
		int pos = 0;
		int len = strlen(message.txt);
		while(pos < len){
			part.type=1;
			for(i=0;i<20 ;i++){if(pos < len)part.txt[i] = message.txt[pos++]; else part.txt[i]='\0';}
			msgsnd(mid, &part, sizeof(part), 0);
			msgsnd(buf, &part, sizeof(part), 0);
			printf("Data Sent: %s\n",part.txt);
			int i=1,j;
			for(j=0;j<1000;j++)for(i=1;i<1000000;i++);
			msgrcv(aid, &ackmes, sizeof(ackmes), 1,IPC_NOWAIT);
			printf("%s\n",ackmes.txt);
			//	printf("FDFDFF");
			while(ackmes.txt[0] != 'S'){
				printf("Damage\n");
				msgsnd(mid, &part, sizeof(part), 0);
				msgsnd(buf, &part, sizeof(part), 0);
				printf("Data Sent: %s\n",part.txt);
				for(j=0;j<1000;j++)for(i=1;i<1000000;i++);
			msgrcv(aid, &ackmes, sizeof(ackmes), 1,IPC_NOWAIT);				
			}
				
			ackmes.txt[0]='D';
			
		}
		printf("Successful\n");
		
	}
	msgctl(mid, IPC_RMID, NULL);
	msgctl(aid, IPC_RMID, NULL);
	msgctl(buf, IPC_RMID, NULL);

	return 1;
}
