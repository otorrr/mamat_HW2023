//
//  main.c
//  Created by Usman and Otor on 9/12/2022.
//

#include "linked-list.h"
#include "grades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAIL 1
#define SUCCESS 0


typedef struct course{
    int course_grade;
    char *course_name;
} Course;

typedef struct student{
    int id;
    char *student_name;
    struct list* list_course;
} Student;

typedef struct grades{
    struct list* students;
} *Grade;


int copy_course(Course *from, Course **to){ //not sure about the "*"
    Course* tmp_copy= malloc(sizeof(Course));
    tmp_copy->course_grade = from->course_grade;
    tmp_copy->course_name = (char*)malloc(strlen(from->course_name)+1);
    strcpy(tmp_copy->course_name,from->course_name);
    *to=tmp_copy;
    return 0;
}
void destroy_course(Course *a_course);
void destroy_student(Student *a_student);


int  copy_student(Student *from, Student **to){//still not finished
    Student* tmp_copy= malloc(sizeof(Student));
    tmp_copy->id = from->id;
    tmp_copy->student_name = (char*)malloc((strlen(from->student_name) + 1));
    strcpy(tmp_copy->student_name,from->student_name);
    tmp_copy->list_course= list_init((element_clone_t)copy_course,
                                     (element_destroy_t) destroy_course );
    struct iterator *from_it = list_begin(from->list_course);
    struct iterator *tmp_it = list_begin(tmp_copy->list_course);
    Course *from_course=list_get(from_it);
    int tmp_size=(int)list_size(from->list_course);
    if(tmp_size) {
        list_push_front(tmp_copy->list_course, from_course);
        tmp_it = list_begin(tmp_copy->list_course);
    }
    for (int i = 0; i < tmp_size-1; ++i) {
        from_it = list_next(from_it);
        from_course = list_get(from_it);
        list_insert(tmp_copy->list_course,tmp_it,from_course);
        tmp_it = list_next(tmp_it);
    }
    *to=tmp_copy;
    return 0;

}


void destroy_course(Course *a_course){ 
    free(a_course->course_name);
    free(a_course);
}

void destroy_student(Student *a_student){ 
    list_destroy(a_student->list_course);
    //free(a_student->list_course);
    free(a_student->student_name);
    free(a_student);
}


void grades_destroy(struct grades *grades)
{
    list_destroy(grades->students);
    // free(grades->students);
    free(grades);
}

struct grades* grades_init(){
    struct grades* gradesManager= (Grade)malloc(sizeof (gradesManager));
    element_clone_t ptr = (element_clone_t) copy_student;
    element_destroy_t ptr2 = (element_destroy_t) destroy_student;
    gradesManager->students= list_init(ptr, ptr2);
    return gradesManager;
}



int grades_add_student(struct grades *grades, const char *name, int id)
{
    if(!grades)
        return FAIL;
    if(!name)
        return FAIL;
    if(id<=0)
        return FAIL;        
    int name_length = (int)strlen(name) + 1;
    struct iterator *Itr =list_begin(grades->students);
    Student *curr_student;
    while(Itr)
    {
        curr_student=list_get(Itr);
        if(curr_student->id==id)
        {
            return  FAIL;//failed;
        }
        Itr=list_next(Itr);
    }
    Student *new_student=(struct student*)malloc(sizeof(Student));
    new_student->student_name=(char*)malloc(name_length);
    if(new_student == NULL)
        return FAIL;
    new_student->id=id;
    strcpy(new_student->student_name,name);
    new_student ->list_course = list_init((element_clone_t)copy_course,
                                          (element_destroy_t)destroy_course);
    if(!list_push_back(grades->students, new_student)){
        free(new_student->student_name);
        list_destroy(new_student->list_course);
        // free(new_student->list_course);
        free(new_student);

        return SUCCESS;
    }

    free(new_student->student_name);
    list_destroy(new_student->list_course);
    // free(new_student->list_course);
    free(new_student);
    return FAIL;
}

//Add grade
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade)
   {                  
    if(grades == NULL) return  FAIL;
    if(!name) return  FAIL;
    if(grade > 100)
        return FAIL;
    if(grade <0 )
        return FAIL;

    int name_length = (int)strlen(name)+1;
    struct iterator *iterator = list_begin(grades->students);
    Student *curr_student;
    Course *curr_course;
    while(iterator)
    {
        curr_student = list_get(iterator);
        if(curr_student->id == id)
        {
            iterator = list_begin(curr_student->list_course);
            while(iterator)
            {
                curr_course = list_get(iterator);
                if(!strcmp(curr_course->course_name,name)) //checks if the course exist
                    return FAIL;
                else
                {
                    iterator = list_next(iterator);
                }
            }
            struct course *new_course =(struct course*)malloc(sizeof(new_course));
            new_course->course_grade = grade;
            new_course->course_name = (char*)malloc(name_length);
            strcpy(new_course->course_name,name);
            list_push_back(curr_student->list_course,new_course);
            free(new_course->course_name);
            free(new_course);
            return SUCCESS;
        }
        else
        {
            iterator = list_next(iterator);
        }
    }
    return FAIL;
}
// Calc avg
float grades_calc_avg(struct grades *grades, int id, char **out){
    if(id <=0) {
        *out = NULL;
        return -1;
        }
    if(grades == NULL) {
        *out = NULL;
        return -1;
            
    }
    struct iterator *Itr_student =list_begin(grades->students);
    struct iterator *Itr_course;
    Course *curr_course;
    Student *curr_student;
    int counter=0,sum=0;
    while (Itr_student) {
        curr_student = list_get(Itr_student);
        if(curr_student->id==id){
            *out = (char *)malloc((strlen(curr_student->student_name)+1));
            strcpy(*out,curr_student->student_name);
            Itr_course = list_begin(curr_student->list_course);
            while(Itr_course){
                curr_course = list_get(Itr_course);
                Itr_course = list_next(Itr_course);
                sum+=(curr_course->course_grade);
                counter++;
            }
            if(counter == 0) {
                return 0;
            }
            return ((float)sum/(float)counter);
        }
        else{
            Itr_student = list_next(Itr_student);
        }
    }
    *out = NULL;
    return -1;

}

//Print student
int grades_print_student(struct grades *grades, int id)
{
    if(grades == NULL || id <=0)
        return FAIL;
    struct iterator *iterator = list_begin(grades->students);
    Student *curr_student;
    Course *curr_course;
    while(iterator)
    {
        curr_student = list_get(iterator);
        if(curr_student->id == id)
        {
            printf("%s %d:",curr_student->student_name,curr_student->id);
            iterator = list_begin(curr_student->list_course);
            if(iterator){
                curr_course = list_get(iterator);
                printf(" %s %d",curr_course->course_name,curr_course->course_grade);
                iterator = list_next(iterator);
            }
            while(iterator)
            {
                printf(",");
                curr_course = list_get(iterator);
                printf(" %s %d",curr_course->course_name,curr_course->course_grade);
                iterator = list_next(iterator);
            }
            printf("\n");
            return SUCCESS;
        }
        else
        {
            iterator = list_next(iterator);
        }
    }
    return FAIL;
}

//Print all
int grades_print_all(struct grades *grades){
    if(grades == NULL)return FAIL;
    struct iterator *Itr_student =list_begin(grades->students);
    Student *curr_student;
    while (Itr_student) {
        curr_student = list_get(Itr_student);
        grades_print_student(grades, curr_student->id);
        Itr_student = list_next(Itr_student);
    }
    return SUCCESS;
}
