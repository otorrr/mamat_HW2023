#include "port.h"
#include "string.h"
#include <stddef.h>
#define MAX_PORT_RANGE 65535
#define MIN_PORT_RANGE 0
using namespace std;


Port::Port(String str)
{
    for(int i=0;i<SECTIONS_NUM_HYPHEN;i++)
        Port_sections[i]=0;
}
// initialization of Port



bool Port::set_value(String value)
{
	
    String *port_sections_hyphen;
    size_t str_hyphen_num;
    String *port_split_equal;
    String value_tmp=value.trim();
    value_tmp.split("=",&port_split_equal,&str_hyphen_num);
    port_split_equal[1].split("-",&port_sections_hyphen ,&str_hyphen_num);
    delete [] port_split_equal;
    if(port_sections_hyphen == NULL)
    {
        return false;
    }
    if ( str_hyphen_num != 2){
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
    int num_in_range= (packet.trim()).to_integer();
    if ((num_in_range >= this->Port_sections[0]) && (num_in_range <= Port_sections[1]))
        return true;
    return false;
}







