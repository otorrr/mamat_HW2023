#include "port.h"
#include "string.h"
#include <stddef.h>
#define MAX_PORT_RANGE 65535
#define MIN_PORT_RANGE 0
using namespace std;
#define TWO 2


Port::Port(String str)
{
	this->str=String(str);
    for(int i=0;i<SECTIONS_NUM_HYPHEN;i++)
        Port_sections[i]=0;
    
}
// initialization of Port




bool Port::set_value(String value)
{
	
    String *port_sections_hyphen;
    size_t str_hyphen_num;
    
    String value_tmp=value.trim();
    value_tmp.split("-",&port_sections_hyphen,&str_hyphen_num);
    
    if(port_sections_hyphen == NULL)
    {
        return false;
    }
    if ( str_hyphen_num != TWO){
        delete[] port_sections_hyphen;
        return false;
    }

    Port_sections[0]=port_sections_hyphen[0].to_integer();
    Port_sections[1]=port_sections_hyphen[1].to_integer();

    if(port_sections_hyphen[0].to_integer()<MIN_PORT_RANGE || port_sections_hyphen[0].to_integer()>MAX_PORT_RANGE
       ||port_sections_hyphen[1].to_integer()<MIN_PORT_RANGE ||port_sections_hyphen[1].to_integer()>MAX_PORT_RANGE )///check if 1>2
    {
        delete[] port_sections_hyphen;
        return false;
    }
    delete[] port_sections_hyphen;
    return true;
}

bool Port::match(String packet)
{
	String* check;
	size_t tmp;
	String new_packet=String(packet);
	new_packet.split(",=",&check,&tmp);
	int in_array=-1;
	for(size_t i=0; i< tmp; i++){
		String string1=check[i].trim();
		if(string1.equals(this->str)==0)
			in_array=i;
	}
	/*if(in_array== -1){
		delete[] check;
		return false;
	}*/
	
	if(in_array!=1){
    	int num_in_range= check[in_array+1].to_integer();
    	if ((num_in_range >= this->Port_sections[0]) && (num_in_range <= Port_sections[1])){
    		delete[] check;
    	
        	return true;
        	}
        	delete[] check;
        }
        
     else{
     		delete[] check;
			return false;
		}
        
        
    return false;
}
