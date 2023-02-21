#include "string.h"
#include <cstring>
#include <iostream>
static char* copy(const char *str, int size);
static int sub(char *str, int length, const char *delimiters);
	






String::String(){
	data=new char[1];
    data[0] ='\0';
    length = 0;
};



String::String(const String &str) {
	data= new char[str.length+1];
    strcpy(data,str.data);
    data[str.length]='\0';
    length=str.length;
};


 String::String(const char *str){
	 data=new char[strlen(str)+1];
    strcpy(data,str);
    data[strlen(str)]='\0';
    length=strlen(str);
 };


 String::~String(){ 
 	delete[] data;
 	
 }; 


 String& String::operator=(const String &rhs){
 	if(this == &rhs)
        return *this;

    delete [] this->data;
    data=new char [rhs.length+1];
    strcpy(data,rhs.data);
    this->length= strlen(rhs.data);
    data[length]='\0';
    return *this;
 };
 
 

 String& String::operator=(const char *str){
 	delete [] this->data;
    data=new char[strlen(str)+1];
    this->length=strlen(str);
    strcpy(data,str);
    data[length]='\0';
    return *this;
 };



 bool String::equals(const String &rhs) const {
    if(strcmp(this->data,rhs.data))
        return true;

    return false;
 }; 
 
 

 bool String::equals(const char *rhs) const{
 	if(strcmp(this->data,rhs))
        return true;

    return false;
 };
 
 
 int String::to_integer() const{
 	 return atoi(this->data);
 };





 void String::split(const char *delimiters,String **output, size_t *size)const{
 	
 	int iterator = sub(this->data , this->length, delimiters);
 	*size = iterator;
 	if ( output == NULL) {
 	 return;
    }
 	*output = new String[iterator];
 	char *str_copy =copy(this->data, this->length);
	char *token = str_copy;
	token = strtok(str_copy, delimiters);

	while( token != NULL ){
		String splited = String(token);
		**output = splited;
		(*output)++;
		token = strtok(NULL , delimiters);
	}
	
	delete[] str_copy;
	*output = *output - iterator;
 };



 


String String::trim()const{
    int left = 0;
    int right = length-1;
    while ((data[left] == ' ') && (left!=right))
        left++;
    while ((data[right] == ' ') && (left!=right))
        right--;
    int new_length = right-left+1 ;
    char *new_data = new char[new_length];
    strncpy(new_data, data + left, new_length);
    String trimmed = String(new_data);
    delete[] new_data;
    return trimmed;
}







static char* copy(const char *str, int size)
	{
		return strcpy(new char[size+1], str);
	}




static int sub(char *str, int length, const char *delim)
{
		char *str_copy = copy(str, length);
		int ctr = 0;
		char *token = strtok(str_copy, delim);
		while( token != NULL ){
			ctr++;
			token = strtok(NULL , delim);
		}
		delete[] str_copy;
		return ctr;
}



