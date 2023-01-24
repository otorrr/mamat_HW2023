#ifndef PORT_H
#define PORT_H
#include "generic-field.h"
#define SECTIONS_NUM_HYPHEN 2


class Port : public GenericField
{
    int Port_sections[SECTIONS_NUM_HYPHEN];
public:
    Port(String str);
    bool set_value(String value);
    bool match(String packet);
};

#endif 
