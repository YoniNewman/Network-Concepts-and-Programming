#ifndef _IP_MATH_CODING_H
#define _IP_MATH_CODING_H

void get_broadcast_address(char *ip_addr, char mask, char *output_buffer);
void get_ip_integral_equivalent(char *ip_addr, unsigned int *result);
void get_ip_abcd_format(unsigned int ip_addr, char *output_buffer);
unsigned char Str2Int(char str[], int *i);
void Byte2IPStr(char *output_buffer, unsigned char byte[]);
void set_bits_ip_add(unsigned char ip[],int BitsToSet, char *output_buffer);
void ParseIPStr(char ip_str[], unsigned char ip_arr[]);
int NumOfDigits(int num);
void FixIPStr(char []);

#endif