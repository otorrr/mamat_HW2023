//
// Created by mm551 on 09/01/2023.
//
#include "string.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#define BIG_ENOUGH 100


String::String() {
    data=new char[1];
    data[0] ='\0';
    length = 1;
}



String::String(const String &str) {
    data= new char[str.length];
    strcpy(data,str.data);
    data[str.length-1]='\0';
    length=str.length;
}



String::String(const char *str) {
    data=new char[strlen(str)+1];
    strcpy(data,str);
    data[strlen(str)]='\0';
    length=strlen(str)+1;
}



String::~String() {
    delete [] data;
}



String &String::operator=(const String &rhs) {
    if(this->data==rhs.data)
        return *this;

    delete [] this->data;
    data=new char [rhs.length];
    strcpy(data,rhs.data);
    this->length= strlen(rhs.data)+1;
    data[length-1]='\0';
    return *this;

}



String &String::operator=(const char *str) {
    if(this->data==str)
        return *this;

    delete [] this->data;
    data=new char[strlen(str)+1];
    this->length=strlen(str)+1;
    strcpy(data,str);
    data[length-1]='\0';
    return *this;
}



bool String::equals(const String &rhs) const {
    if(this->length != rhs.length)
        return false;
    if(strcmp(this->data,rhs.data)!=0)
        return false;

    return true;
}



bool String::equals(const char *rhs) const {
    if(strcmp(this->data,rhs)!=0)
        return false;

    return true;
}



int String::to_integer() const {
    return atoi(this->data);
}



String String::trim() const {
    
    
    String rhs;
    
    rhs = String(this->data);
    
    for(int i=0;i<(int)this->length;++i){
    
        if(rhs.data[i] == ' '){
            for (int m=i,r=i+1;r<(int)this->length; ++r,++m) {
                rhs.data[m] = rhs.data[r];
            }
            
            rhs.length = rhs.length - 1;
            i=i-1;
        }
        
    }
    
    return rhs;

}



void String::split(const char *delimiters, String **output, size_t *size) const {

    if(this->data == NULL)
    {
        *output = NULL;
        *size = 0;
        return;
    }
    if(delimiters == NULL)
    {
        return;
    }
    if(size == NULL)
    {
        return;
    }

    *size=1; // The number of the sub-strings=num of delimitrs+1
    size_t string_length = this->length;
    size_t delim_num = strlen(delimiters);
    for(size_t i=0;i<delim_num;i++)
    {
        for(size_t j=0;j<string_length;j++)
        {
            if(delimiters[i]==this->data[j])
                (*size)++;

        }
    }// Found the number of sub-strings
    if(output==NULL) {

        return;

    }

    (*output)= new String[(*size)];
    for (size_t i=0; i< (*size); i++)
    	(*output)[i]=String();
    char * tmp= new char[BIG_ENOUGH];
    int iterator=0;
    int section_number=0;
    int flag=1;
    for(size_t k=0;k<string_length;k++)
    {
        for (size_t i = 0; i < delim_num; ++i) {
            if (delimiters[i]== data[k]){
                tmp[iterator]='\0';
                (*output)[section_number]=String(tmp);
                section_number++;
                iterator=0;
                flag=0;
            }
        }
        if (flag){
            tmp[iterator]=data[k];
            iterator++;
        }
        flag=1;
        if (k == string_length-1)
            (*output)[section_number]=String(tmp);
    }

}









