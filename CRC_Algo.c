#include<stdio.h>
char data[20], div[20], temp[4], total[100];
int i, j, datalen, divlen, len, flag=1;
void check(){
    for(j=0; j<datalen; j++){
        data[j] = total[j];
    }
    while(j<=len){
        if(data[0] == '1'){
            for(i=1; i<divlen; i++){
                data[i] = (data[i] == div[i]) ? '0' : '1'; // XOR operation
            }
        }
        for(i=0; i<divlen-1; i++){
            data[i] = data[i+1]; // Shift left
        }
        data[i] = total[j++]; // Bring down the next bit
    }
}

int main(){
    printf("Enter the data bits:");
    scanf("%d",&datalen);
    printf("Enter total bits of the divisor: ");
    scanf("%d",&divlen);
    len = datalen + divlen - 1;//Total length of the codeword
    printf("Enter the data: ");
    scanf("%s", data);
    printf("Enter the divisor: ");
    scanf("%s", div);
    for(i = 0; i < datalen; i++){
        total[i] = data[i];
        temp[i] = data[i];
    }
    for(i=datalen; i<len; i++){
        total[i] = '0';//Padded with zeros corresponding to the length of the divisor
    }
    check();
    for(i=0; i<divlen; i++){
        temp[i+datalen] = data[i];
    }
    printf("\nTransmitted codeword: %s", temp);
    printf("\nEnter the received codeword: ");
    scanf("%s", total);
    check();
    for(i=0; i<divlen-1; i++){
        if(data[i] == '1'){//Checkig if the remainder bit is all zero or not
            flag = 0;
            break;
        }
    }
    if(flag == 1){
        printf("\nNo error in the received codeword.");
    } else {
        printf("\nError in the received codeword.");
    }
    return 0;
}