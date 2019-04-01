#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PREFIX_LEN 16
#define DEBUG 1

//Q1
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer);
unsigned int Str2Int(char str[]);
void Int2Str(char *output_buffer, int *start_indx, unsigned char byte);
void ctreate_ip_string(unsigned int ip, char *output_buffer);

int main(){
    char ipadd_buffer[PREFIX_LEN] = {0};
    char ipadd[] = {"192.168.205.1"};
    char mask = 24;
    get_broadcast_address(ipadd,mask,ipadd_buffer);
    printf("for ip address %s/%d the broadcast address is: %s\n",ipadd,mask,ipadd_buffer);
}/*main end*/

/* Function name: get_broadcast_address
*  Input: 1. ip_addr - string that contains the ip address. 
*         2. mask - contain a number between 0-32 for the mask
*         3. output_buffer - out parameter that contatins the broadcast ip address
*  Output: for 192.168.205.1/24 the output will be 192.168.205.255
*/
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer){
    //calculate how much bits to set
    int BitsToBeSet = 32-mask;
    unsigned int ip_hex = Str2Int(ip_addr);
    //set those bits
    unsigned int mask_temp = ~(0xFFFFFFFF << BitsToBeSet);
    ip_hex |= mask_temp;
    //convert the result into string
    #if DEBUG
        printf("ip address : 0x%X\n",ip_hex);
    #endif
    ctreate_ip_string(ip_hex,output_buffer);
}

void ctreate_ip_string(unsigned int ip, char *output_buffer)
{
    unsigned char msb; //least significant byte
    unsigned int mask_temp = 0xFF000000;
    int index = 0;
    for(int i=0;i<4;i++){
        msb = mask_temp & ip;
        mask_temp >>= 8;
        #if DEBUG   
            printf("debbug:ip = %0xX, msb = %d\n",ip,msb);
        #endif
        Int2Str(output_buffer,&index, msb);
        if(i<3)
            output_buffer[index++] = '.';
        #if DEBUG
            printf("debbug: %s\n",output_buffer);
        #endif
    }
}

void Int2Str(char *output_buffer, int *start_indx, unsigned char byte){
    if(byte >= 100){
        // 3 digits required
        output_buffer[*start_indx+2] = byte % 10 + '0';
        byte /= 10;
        output_buffer[*start_indx+1] = byte % 10 + '0';
        byte /= 10;
        output_buffer[*start_indx] = byte + '0';
        *start_indx += 3;
    }
    else if(byte >=10){
        // 2 digits required
        output_buffer[*start_indx+1] = byte % 10 + '0';
        byte /= 10;
        output_buffer[*start_indx] = byte + '0';
        *start_indx += 2;
    }
    else{
        output_buffer[*start_indx++] = byte +'0';
    }
}


unsigned int Str2Int(char str[]){
    int length = strlen(str);
    int i,dec;
    unsigned int res = 0;
    for(i=strlen(str)-1,dec = 1;i>0;i--,dec *= 10){
        if(str[i] =='.')
            i--;
        res += dec*(str[i]-'0');
    }
    return res;
}