//
// Created by mm551 on 12/01/2023.
//
#include "ip.h"
#include "string.h"
#define MAX_IP_RANGE 255
#define MIN_IP_RANGE 0
#define MIN_DC_BITS_RANGE 0
#define MAX_DC_BITS_RANGE 32
#define ONE_BYTE 8
#define TWO_BYTES 16
#define THREE_BYTES 24
#define FOUR_BYTES 32
#define BYTE_1 3
#define BYTE_2 2
#define BYTE_3 1
#define BYTE_4 0
#define TWO 2
#define SLASH_NUM 1
#define DOTS_NUM 3
int Dont_Care(int num,int DC_bits) // Don't care the DC bits (Making them 0) by dividing by 2.
{
    int new_num=num;
    for(int i=0;i<DC_bits;i++){
        new_num/=TWO;
    }
    return new_num;
}


ip::ip(String str) {
	
for(int i=0;i<SECTIONS_NUM_DOTS;i++) {
        IP_sections[i] = 0;
    }
DC_bits=0;
}// initialization of IP

bool ip::set_value(String value) {
    String *ip_sections_dots;
    size_t str_dots_num;
    String *ip_sections_slash;
    size_t str_slash_num;
    value.split(".",&ip_sections_dots,&str_dots_num);
    value.split("/",&ip_sections_slash,&str_slash_num);
    if(ip_sections_dots ==NULL)
    	return false; // Failed.
    if(ip_sections_slash ==NULL)
    	return false; // Failed.
    // split the IP twice ; one according to dots and another one according to slash
    for(int i=0;i<SECTIONS_NUM_DOTS;i++) {

        if (ip_sections_dots[i].to_integer() > MAX_IP_RANGE || ip_sections_dots[i].to_integer() < MIN_IP_RANGE){
            delete[] ip_sections_dots;
            delete[] ip_sections_slash;
            return false;
        }
		
        this->IP_sections[i]=ip_sections_dots[i].to_integer();
    } // Checking ip sections if they are in the correct range of not (0-255).
      // Put the values in the IP_sections
	

        if ((ip_sections_slash[1].to_integer() > MAX_DC_BITS_RANGE) || (ip_sections_slash[1].to_integer() < MIN_DC_BITS_RANGE)){
            delete[] ip_sections_dots;
            delete[] ip_sections_slash;
            return false;
        }

        // Checking if the number of don't care bits are in the range or not

        this->DC_bits=(MAX_DC_BITS_RANGE-ip_sections_slash[1].to_integer());
    
        // Put the Don't Care bits in the CD_bits.
        delete [] ip_sections_slash;//check
        delete [] ip_sections_dots;
        
    return true;
}

bool ip::match(String packet) {
	
	char delem_equ = '=';
    int IP_check[SECTIONS_NUM_DOTS];
    for (int i = 0; i < SECTIONS_NUM_DOTS; i++) {
        IP_check[i] = this->IP_sections[i];
    }
    if (DC_bits == MAX_DC_BITS_RANGE) {
    
        return true; // Success
    }
    String *ip_sections_dot;///check if not deleted
    size_t str_dot_num;
    String *ip_packet_numbers;
    String packet_tmp=packet.trim();
  
    packet_tmp.split(&delem_equ,&ip_packet_numbers,&str_dot_num);
   
    ip_packet_numbers[1].split(".", &ip_sections_dot, &str_dot_num);
   
    delete[] ip_packet_numbers;
    
    
    int DC_check=(MAX_DC_BITS_RANGE- DC_bits)/ONE_BYTE;
  
    int DC_lst_bits=DC_bits%ONE_BYTE;
   
    
    
    for (int i = 0; i < DC_check; ++i) {
        if (ip_sections_dot[i].to_integer()!=IP_check[i]) {
            delete [] ip_sections_dot;
            return false;
        }
    }
    if (!DC_lst_bits) {
    	
        delete [] ip_sections_dot;
     
        return true;
    }
    if ( DC_check !=4 && (Dont_Care(ip_sections_dot[DC_check].to_integer(),DC_lst_bits) 
    == Dont_Care(IP_check[DC_check],DC_lst_bits))){
        delete[] ip_sections_dot;
        return true;
    }
    delete[] ip_sections_dot;
    return false;
}












