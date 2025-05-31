#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100]; //To get the message from the user
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();

int main(){
    printf("Enter first prime number: ");
    scanf("%ld", &p);
    flag = prime(p);
    if(flag == 0 || p == 1){
        printf("Not a prime number.\n");
        exit(1);
    }
    printf("Enter second prime number: ");
    scanf("%ld", &q);
    flag = prime(q);
    if(flag == 0 || q == 1 || p==q){//two prime numbers should not be equal
        printf("Not a prime number.\n");
        exit(1);
    }
    printf("Enter message: ");
    scanf(" %[^\n]s", msg);
    for(int i=0; i<strlen(msg); i++){
        m[i] = msg[i];
    }
    n = p*q; // n is the modulus for the public key and the private keys
    t = (p-1)*(q-1); // t is the totient
    ce(); // Function call to calculate e
    encrypt(); // Function call to encrypt the message
    decrypt(); // Function call to decrypt the message
    return 0;
}

int prime(long int pr){
    if(pr == 1) return 0;
    for(i=2; i<sqrt(pr); i++){
        if(pr % i == 0) return 0; // Not a prime number
    }
    return 1;
}
// Function call to calculate e
void ce(){
    int k=0;
    for(int i=2; i<t; i++){
        if(t%i == 0) continue; // i is not coprime with t
        flag = prime(i);
        if(flag == 1 && i != p && i != q){ // i is a prime number and not equal to p or q
            e[k] = i; // Store the value of e
            flag = cd(e[k]); // Calculate d
            if(flag > 0){
                d[k] = flag; // Store the value of d
                k++;
            }
            if(k == 99) break; // Limit the number of e and d values
        }
    }
}

long int cd(long int x){
    long int k = 1;
    while(1){
        k += t; // Increment k by t
        if(k % x == 0) return (k / x); // Return d if k is divisible by x
    }
}

void encrypt(){
    long int pt, ct, kry = e[0], k, len;
    len = strnlen(msg, 1024); // Get the length of the message
    i = 0;
    while(i < len){
        pt = m[i];
        pt = pt-96; // Convert character to number (assuming 'a' = 1, 'b' = 2, ..., 'z' = 26)
        k = 1;
        for(j = 0; j < kry; j++){
            k = (k * pt) % n; // Encrypt the message using the formula c = (m^e) mod n
        }
        temp[i] = k;
        ct += k+96;
        en[i] = ct;
        i++;
    }
    en[i] = -1; // Mark the end of the encrypted message
    printf("Encrypted message: ");
    for(i = 0; en[i] != -1; i++){
        printf("%c ", (char)en[i]); // Print the encrypted message
    }
}

void decrypt(){
    long int pt, ct, key = d[0], k;
    i = 0;
    while(en[i] != -1){
        ct = temp[i];
        k = 1;
        for(j=0; j<key; j++){
            k = (k * ct) % n; // Decrypt the message using the formula m = (c^d) mod n
        }
        pt = k + 96; // Convert number back to character
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    printf("\n thE DECRYPTED MESSAGE: ");
    for(i=0; m[i] != -1; i++){
        printf("%c", (char)m[i]); // Print the decrypted message
    }
}