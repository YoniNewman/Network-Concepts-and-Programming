#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ip_math_coding.h"
#include "general.h"


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
            set = 1;
        }
        ip[i] |= set;
    }
    Byte2IPStr(output_buffer,ip);
}

void clear_bits_ip_add(unsigned char ip[],int BitsToSet, char *output_buffer){
    // for each slot in array, check how many digits
    int set = 0xFE;
    int j;
    for(int i=3, j=0; i >= 0 && BitsToSet; j++, set >>=1, BitsToSet--){  
        if(j == 8){
            j = 0;
            i--;
            set = 1;
        }
        ip[i] &= set;
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

void FixIPStr(char ip[]){
    for(int i=0;ip[i];i++){
        if(ip[i]=='\n')
            ip[i] = 0;
    }
}

/* Function name: get_ip_integral_equivalent
*  Input: 1. ip_addr - string that contains the ip address. 
*         2. result - out parameter that contatins the value of the ip address
*  Output: for 192.168.205.1 the output will be 0xC0A8CD01
*/
void get_ip_integral_equivalent(char *ip_addr, unsigned int *result){
    unsigned char ip_str[4] = {0};
    unsigned int temp_result = 0;
    ParseIPStr(ip_addr, ip_str);
    for(int i=0;i<4;i++){
        temp_result |= ip_str[i];
        if(i<3)
            temp_result <<= 8;
    }

    *result = temp_result;   

}

/* Function name: get_ip_abcd_format
*  Input: 1. ip_addr - unsigned integer that contains a value of ip address. 
*         2. output_buffer - out parameter that contains the a.b.c.d format ip address.
*  Output: for 0xC0A8CD01 the output will be 192.168.205.1
*/
void get_ip_abcd_format(unsigned int ip_addr, char *output_buffer){
    unsigned char ip_arr[4] = {0};
    unsigned int temp_ip = ip_addr;
    //seperate ip address into chunks of bytes
    for(int i=3;i>=0;i--){
        ip_arr[i] = temp_ip & 0xFF;
        temp_ip >>= 8 ;
    }
    //convert bytes into string
    Byte2IPStr(output_buffer,ip_arr);
}


/* Function name: get_network_id
*  Input: 1. ip_addr - string that contains the ip address. 
*         2. mask - contain a number between 0-32 for the mask
*         3. output_buffer - out parameter that contatins the network id
*  Output: for 192.168.205.1/24 the output will be 192.168.205.0
*/
void get_network_id(char *ip_addr, char mask, char *output_buffer){
    unsigned char ip_str[4] = {0};
    //calculate how much bits to set off
    int BitsToBeSet = 32-mask;
    //clear those bits
    unsigned int mask_temp = ~(0xFFFFFFFF << BitsToBeSet);
    ParseIPStr(ip_addr, ip_str);
    clear_bits_ip_add(ip_str,BitsToBeSet,output_buffer);
}

/* Function name: get_network_cardinality
*  Input: 1. mask - contain a number between 0-32 for the mask 
*  Output: returns the number of ip address that can be assign to this network
*  For Example: for mask 24 the result will be 254 (1 for broadcast and 1 for netowk id).
*/
unsigned int get_network_cardinality(char mask){
    unsigned int BitsToBeShift = 32 - mask;
    unsigned int result = 1;
    if(BitsToBeShift == 32)
        return 0xFFFFFFFF-1;
    if(!BitsToBeShift)
        return 1;
    result <<= BitsToBeShift;
    return result - 2;
}
 
 /* Function name: check_ip_subnet_membership
 *  Input: 1. networkid - string that contains the network id. 
*          2. mask - contain a number between 0-32 for the mask
*          3. ipadd_check - string that contains the ip address to be checked
*  Output: true if the ip to be checked is a member of the network id, otherwise returns false.
*  For Example: for 192.168.205.1/24 the and network id of 192.168.205.0 the result will be true.
*/
int check_ip_subnet_membership(char *networkid, char mask, char *ipadd_check){
    //get ip's network id
    char ips_network_id[PREFIX_LEN] = {0};
    get_network_id(ipadd_check,mask,ips_network_id);
    //compare ip's address network id with inserted network id
    if(strcmp(ips_network_id,networkid))
        return FALSE;
    else
        return TRUE;
}