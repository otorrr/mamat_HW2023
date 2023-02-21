
#include <iostream>
#include <cstring>
#include "input.h"
#include "string.h"
#include "generic-field.h"
#include "ip.h"
#include "port.h"




int main(int argc, char **argv) {

    if(check_args( argc, argv) != 0) 
        return 1;
    

    String str = String(argv[1]);

    String *str_matrix;
    
    size_t str_num;
    
    GenericField *f;
    
    str.split(" ,""=" , &str_matrix , &str_num);

   
    if(!(str_matrix[0].equals("src-port")) )
    {
        f = new Port(str_matrix[0]);
        f->set_value(str_matrix[1]);
    	parse_input(*f);
    	delete[] str_matrix;
    	delete f;
    }
    
    
    
    if(!(str_matrix[0].equals("dst-port")))
    {
        f = new Port(str_matrix[0]);
        f->set_value(str_matrix[1]);
    	parse_input(*f);
    	delete[] str_matrix;
    	delete f;
    }
    
    
    
    if(!(str_matrix[0].equals("src-ip")))
    {
        f = new ip(str_matrix[0]);
        f->set_value(str_matrix[1]);
    	parse_input(*f);
    	delete[] str_matrix;
    	delete f;
    }
    
    
    
    if(!(str_matrix[0].equals("dst-ip")) )
    {
        f = new ip(str_matrix[0]);
        f->set_value(str_matrix[1]);
    	parse_input(*f);
    	delete[] str_matrix;
    	delete f;
    }
    

    return 0;

}
