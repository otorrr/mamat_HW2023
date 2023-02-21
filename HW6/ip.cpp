#include <iostream>
#include "ip.h"
#include <cstring>
#include <bitset>
#define BYTE 8
#define DOT "."
#define TWO 2




ip::ip(String str) {
	
	this->str = String(str);
	DC_bit = 0;
	
	for (int i=0; i < BITS_NUM; i++)
	{
		sections[i] = 0 ; 
	}
	
}


void make_sections(int start, int x, int *arr);

bool ip::set_value(String value){

	String *splited;
	
	
	String the_value = String(value);
	
	char* del="./ ";
	
	size_t size;
	
	the_value.split("./ ", &splited, &size);
	
	int cnt;
	
	DC_bit = (splited + size - 1)->to_integer();

	for (size_t i = 0; i < size-1; i++){
	
		cnt = (splited + i)->to_integer();
		
		make_sections(((size-2-i)*BYTE), cnt, sections);
		
	}
	
	
	delete[] splited;
	return true;
	
};






bool ip::match(String packet) {
	
	
		
	String *pack;
	
	String the_packet = String(packet);
	
	size_t size;
	
	the_packet.split(" ,=", &pack, &size);
	
	String check;
	
	int iterator = -1;
	
	
	for (size_t i = 0; i < size; i++) {
	
        check =((pack+i)->trim());
        
	    if (check.equals(str) == 0){
	    
			iterator = i;
		}
		
	}
	
	
	if(iterator != -1){
	
		String *temp;
		int sections_temp[BITS_NUM];
	
		for(int i = 0; i<BITS_NUM; i++){
        	sections_temp[i]=0;
		}
	
    	size_t size1;
    
		(pack + iterator + 1)->split(DOT, &temp, &size1);
	
		for (size_t i = 0; i < size1; i++) {
	
       	int tmp_int = (temp+i)->to_integer();
       
       	make_sections( ((size1-i-1)*BYTE), tmp_int, sections_temp);
       
		}

		delete[] temp;
		delete[] pack;
	
		for (int i = BITS_NUM-1; i >= BITS_NUM-DC_bit; i--){

        	if (sections_temp[i] != sections[i]){

            	return false;
        		}
    		}
    	return true;
    }
    
    else {
    	delete[] pack;
        return false;
        }
};



void make_sections( int start, int x, int *arr){

	int i=start;
	while(x>0){
		arr[i++]=x%TWO;
		x/=TWO;
		}
}
	
	

