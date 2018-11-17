#ifndef PARSER_H
#define PARSER_H

typedef struct parameter{
    char * begin;
    char * end;
}parameter;
struct para_list_node{
    parameter* para_content;
    struct para_list_node* next;
};
typedef struct para_list_node para_list_node;
typedef struct func{
    char * name;
    para_list_node* my_para_head;
    parameter* me;    /*func itself is a parameter, to locate the begin & end site of the func*/
}func;

int judge_ABC(char * start);
parameter* parse_A(char * start);
parameter* parse_B(char * start);
func* parse_C(char * start);
int check_right_bracket(char* str);
int not_right_bracket(char* str);
char* extract_name(char * start);
char* skip_comma(char * str);
void list_add_node(func* foo, para_list_node* new_node);
void print_str(char* start,char* end);
void print_func(func* foo);
#endif
