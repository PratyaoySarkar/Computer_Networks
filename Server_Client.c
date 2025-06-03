//Server Side

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/msg.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    struct msgbuf{
        char mtext[100];
        long mtype;
    }send, rcv;

    int qid, len;
    qid = msgget((key_t)25, IPC_CREAT|0666);
    if(qid < 0){
        perror("msgget failed");
        exit(1);
    }

    printf("Enter message for TTY-2: ");
    scanf(" %[^\n]s", send.mtext);
    send.mtype = 1;
    len = sizeof(send.mtext);
    if(msgsnd(qid, &send, len, 0 == -1)){
        perror("msgsnd failed");
        exit(1);
    }
    if(msgrcv(qid, &rcv, 100, 2, 0) == -1){
        perror("msgrcv failed");
        exit(1);
    }
    printf("Recieved message from TTY-2: %s\n", rcv.mtext);
}

//Client Side
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/msg.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    struc msgbuf{
        long mtype;
        char mtext[100];
    }send, rcv;
    int qid, len;
    qid = msgget((key_t)25, IPC_CREAT | 0666);
    if(qid < 0){
        perror("msgget failed");
        exit(1);
    }
    if(msgrcv(qid, &rcv, 100, 1, 0) == -1){
        perror("msgrcv failed");
        exit(1);
    }
    printf("Received message from TTY-1: %s\n", rcv.mtext);
    printf("Enter message for TTY-1: ");
    scanf(" %[^\n]s", send.mtext);
    send.mtype = 2;
    len = sizeof(send.mtext);
    if(msgsnd(qid, &send, len, 0) == -1){
        perror("msgsnd failed");
        exit(1);
    }
}