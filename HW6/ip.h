#ifndef IP_H
#define IP_H

#include "generic-field.h"
#include "string.h"

#define BITS_NUM 32

class ip : public GenericField {
	private:
		String str;

	public:
		int sections[BITS_NUM]; //array of bits for ip
		int DC_bit;
		ip (String temp);
   		bool set_value(String value);
   		bool match(String packet) ;

};

#endif


