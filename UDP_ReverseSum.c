//ReverseSum Server program
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    int s_sd, serv_len, num1, num2, sum, rev=0;
    struct sockaddr_in serv;
    s_sd = socket(AF_INET, SOCK_DGRAM, 0);
    serv_len = seizeof(serv);
    serv.sin_family = AF_INET;
    serv.sin_port = 8002;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(s_sd, (struct sockaddr *)&serv, serv_len);
    printf("Server is running and waiting for data...\n");

    while(1){
        recvfrom(s_sd, &num1, sizeof(num1), 0, (struct sockaddr *) &serv, &serv_len);
        recvfrom(s_sd, &num2, sizeof(num2), 0, (struct sockaddr *) &serv, &serv_len);
        sum = num1 + num2;
        // Reverse the sum
        int temp = sum;
        while(temp > 0) {
            rev = rev * 10 + (temp % 10);
            temp /= 10;
        }

        // Send the reversed sum back to the client
        sendto(s_sd, &sum, sizeof(sum), 0, (struct sockaddr *) &serv, &serv_len);
        sendto(s_sd, &rev, sizeof(rev), 0, (struct sockaddr *) &serv, &serv_len);
    }
    close(s_sd);
    return 0;
}

//Client side program
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    int c_sd, serv_len, num1, num2, sum, rev;
    struct sockaddr_in sock_address;
    c_sd = socket(AF_INET, SOCK_DGRAM, 0);
    serv_len = sizeof(sock_address);
    sock_address.sin_family = AF_INET;
    sock_address.sin_port = 8002;
    sock_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(c_sd, (struct sockaddr *)&sock_address, serv_len);

    while(1){
        printf("Enter the first number: ");
        scanf("%d", &num1);
        printf("Enter the second number: ");
        scanf("%d", &num2);
        sendto(c_sd, &num1, sizeof(num1), 0, (struct sockaddr *) &sock_address, serv_len);
        sendto(c_sd, &num2, sizeof(num2), 0, (struct sockaddr *) &sock_address, serv_len);
        recvfrom(c_sd, &sum, sizeof(sum), 0, (struct sockaddr *) &sock_address, &serv_len);
        recvfrom(c_sd, &rev, sizeof(rev), 0, (struct sockaddr *) &sock_address, &serv_len);
        printf("Sum: %d\n", sum);
        printf("Reversed Sum: %d\n", rev);
    }
    close(c_sd);
    return 0;
}