#include <iostream>
#include "input.h"
#include "string.h"
#include "ip.h"
#include "port.h"
#define DELE_NUM 2


int main(int argc, char ** argv)
{	

	 int x=check_args(argc,argv);
     if(x!=0)
      return 1; // Failed.
	//printf("hello\n");
    String str= String(argv[1]);
    String str_trim=String();
    str_trim=str.trim();
    

    char delemiters[DELE_NUM];
    delemiters[0]='=';
    delemiters[1]= ',';
    String *sections;
    size_t sec_num=0;
    str_trim.split(delemiters,&sections,&sec_num);



    if(sections[0].equals("src-ip"))
    {
    	
        ip src_ip("src-ip");
        
        src_ip.set_value(sections[1]);
        //printf("hello world\n");
        parse_input(src_ip);
        //printf("hello\n");
        
    }

    if(sections[0].equals("dst-ip"))
    {
        ip dst_ip("dst-ip");
        dst_ip.set_value(sections[1]);
        parse_input(dst_ip);
        
    }

    if(sections[0].equals("src-port"))
    {
        Port src_port("src-port");
        src_port.set_value(sections[1]);
        parse_input(src_port);
        
    }

    if(sections[0].equals("dst-port"))
    {
        Port dst_port("dst-port");
        dst_port.set_value(sections[1]);
        parse_input(dst_port);
       
    }

    return 0;
    
}
