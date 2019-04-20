#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ip_math_coding.h"
#include "general.h"


void clearBuffer();
void Case1Handler();
void Case2Handler();
void Case3Handler();
void Case4Handler();
void Case5Handler();


void PrintMenu(){
    printf("\n*******Menu*******\n");
    printf("0. Exit.\n");
    printf("1. Get broadcast address.\n");
    printf("2. Get equivalent ip address.\n");
    printf("3. Get A.B.C.D ip format.\n");
    printf("4. Get network id.\n");
    printf("5. Get network cardinality.\n");
    printf("\nPlease enter your choice:");
}

int main(){
    BOOL quit = FALSE;
    int input = 0;
    do{
        PrintMenu();
        scanf("%d", &input);
        switch (input){
            case 0:
                quit = TRUE;
                break;
            case 1:
                Case1Handler();
                break;
            case 2:
                Case2Handler();
                break; 
            case 3:
                Case3Handler();
                break;
            case 4:
                Case4Handler();
                break;    
            case 5:
                Case5Handler();
                break;    
            default:
                printf("Invalid input! please try again...\n");
                break;
        }
    }while(!quit);
    printf("Bye bye!!!\n");
}/*main end*/


void Case1Handler(){
    char ipadd_buffer[PREFIX_LEN] = {0};
    char ipadd[PREFIX_LEN] = {0};
    int mask;
    printf("Please enter an ip address:\n");
    clearBuffer();
    fgets(ipadd, PREFIX_LEN, stdin);
    FixIPStr(ipadd);
        //TODO - add ip correctness checking
    do{
        printf("Please enter a mask:\n");
        scanf("%d",&mask);
        if(mask<0 || mask >32)
            printf("invalid mask!!!\n");
    }while(mask<0 || mask >32);
    get_broadcast_address(ipadd, (char)mask, ipadd_buffer);
    printf("for ip address %s/%d the broadcast address is: %s\n",ipadd,mask,ipadd_buffer);
}

void Case2Handler(){
    char ipadd[PREFIX_LEN] = {0};
    unsigned int ip_result = 0;
    printf("Please enter an ip address:\n");
    clearBuffer();
    fgets(ipadd, PREFIX_LEN, stdin);
    FixIPStr(ipadd);
        //TODO - add ip correctness checking
    get_ip_integral_equivalent(ipadd, &ip_result);
    printf("for ip address %s: interger value is: %u, hex value is: 0x%X",ipadd ,ip_result,ip_result);
}

void Case3Handler(){
    char ipadd_buffer[PREFIX_LEN] = {0};
    unsigned int ip_addr = 0;
    printf("Please enter an ip address:\n");
    scanf("%u",&ip_addr);
        //TODO - add ip correctness checking
    get_ip_abcd_format(ip_addr, ipadd_buffer);
    printf("for ip address 0x%X: abcd format is: %s",ip_addr,ipadd_buffer);
}

void Case4Handler(){
    char ipadd_buffer[PREFIX_LEN] = {0};
    char ipadd[PREFIX_LEN] = {0};
    int mask;
    printf("Please enter an ip address:\n");
    clearBuffer();
    fgets(ipadd, PREFIX_LEN, stdin);
    FixIPStr(ipadd);
        //TODO - add ip correctness checking
    do{
        printf("Please enter a mask:\n");
        scanf("%d",&mask);
        if(mask<0 || mask >32)
            printf("invalid mask!!!\n");
    }while(mask<0 || mask >32);
    get_network_id(ipadd, (char)mask, ipadd_buffer);
    printf("for ip address %s/%d the network id is: %s\n",ipadd,mask,ipadd_buffer);
}


void Case5Handler(){
    unsigned int mask;
    do{
        printf("Please enter a mask:\n");
        scanf("%d",&mask);
        if(mask<0 || mask >32)
            printf("invalid mask!!!\n");
    }while(mask<0 || mask >32);
    printf("The network cardinality for mask %u is %u\n",mask, get_network_cardinality((char)mask));
}

void clearBuffer(){ 
      while ( getchar() != '\n' );
}

