#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ip_math_coding.h"


/* Function name: get_broadcast_address
*  Input: 1. ip_addr - string that contains the ip address. 
*         2. mask - contain a number between 0-32 for the mask
*         3. output_buffer - out parameter that contatins the broadcast ip address
*  Output: for 192.168.205.1/24 the output will be 192.168.205.255
*/
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer){
    unsigned char ip_str[4] = {0};
    //calculate how much bits to set
    int BitsToBeSet = 32-mask;
    //set those bits
    unsigned int mask_temp = ~(0xFFFFFFFF << BitsToBeSet);
    ParseIPStr(ip_addr, ip_str);

    //ip_hex |= mask_temp;
    //convert the result into string
    #if DEBUG
    printf("ip address : %d.%d.%d.%d\n",ip_str[0],ip_str[1],ip_str[2],ip_str[3]);
    #endif
    set_bits_ip_add(ip_str,BitsToBeSet,output_buffer);
}

void set_bits_ip_add(unsigned char ip[],int BitsToSet, char *output_buffer){
    // for each slot in array, check how many digits
    int set = 0x01;
    int j;
    for(int i=3, j=0; i >= 0 && BitsToSet; j++, set <<=1, BitsToSet--){  
        if(j == 8){
            j = 0;
            i--;
        }
        ip[i] |= set;
    }
    Byte2IPStr(output_buffer,ip);
}

int NumOfDigits(int num){
    if(num>=100)
        return 3;
    else if(num>=10)
        return 2;
    else
        return 1;
}

void Byte2IPStr(char *output_buffer, unsigned char byte[]){
    int i, j;
    for(i=0,j = 0; i < 4; i++){
        if(byte[i] >= 100){
            //3 digits
            output_buffer[j+2] = (byte[i] % 10) + '0';            
            output_buffer[j+1] = ((byte[i] / 10) % 10) + '0';
            output_buffer[j] = (byte[i] / 100) + '0';
            j += 3;

        }
        else if(byte[i] >= 10){
            //2 digits
            output_buffer[j+1] = (byte[i] % 10) + '0';
            output_buffer[j] = (byte[i] / 10) +'0';
            j += 2;
        }
        else{
            //1 digits
            output_buffer[j++] = byte[i] + '0';
        }
        if(i<3)
            output_buffer[j++] = '.';
    }
}

void ParseIPStr(char ip_str[], unsigned char ip_arr[]){
    int j, i = strlen(ip_str) - 1;
    for(j=3; j >= 0; j--){
        ip_arr[j] = Str2Int(ip_str, &i);
    }
}

unsigned char Str2Int(char str[], int *i){
    int length = strlen(str);
    int dec, index = *i;
    unsigned int res = 0;
    for(dec = 1;index >= 0; index--, dec *= 10){
        if(str[index] =='.'){
            index--;
            break;
        }
        res += dec*(str[index]-'0');
    }
    *i = index;
    return res;
}