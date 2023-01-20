//
// Created by mm551 on 12/01/2023.
//

#ifndef IP_H
#define IP_H
#include "generic-field.h"
#define SECTIONS_NUM_DOTS 4



class ip : public GenericField {
private:
    int DC_bits;
    int IP_sections[SECTIONS_NUM_DOTS];
public:
     ip(String str);
    bool match(String packet);
    bool set_value(String value);


};
#endif





















