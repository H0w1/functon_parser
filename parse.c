#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>
#include "parse.h" 
/* 
A is a struct like abbbb
B is a struct like [qwe***8]
C is a struct like aaa(A or B or C,..)
*/

int judge_ABC(char * start){
    /*
    judge the next object to be A, B or C
    */
    if (*start == ','){
        return 0;
    }
    while(*start != ',' && *start != ')'){ /* suppose: a bad ) will be interrupt by [ */
        if (*start == '['){           
            return 2;
        }
        if (*start == '(' ){
            return 3;
        }
        ++start;
    }
    return 1;
    /* 
    if A return 1
       B       2
       C       3
       error   0
    */
};
/*
parse functions : start from the first byte of the object , parse it then return the end of it  
*/
parameter* parse_A(char * start){
    /*check , then go to the end*/
    /*return the end of the object*/
    parameter* res = (parameter*) malloc(sizeof(parameter));
    res->begin = start;
    char* worker = start;
    while(*worker != ',' && *worker != ')'){
        ++worker;
    }
    if(--worker < start){
        printf("parse_A(): A len < 0 \n");
        return NULL;
    }
    res->end = worker;
    return res;
};
parameter* parse_B(char * start){
    /*check a [ , then go for the ] directly*/
    /*return the end of the object*/
    parameter* res = (parameter*) malloc(sizeof(parameter));
    while(*start != '['){
        ++start;
    }
    res->begin = start;
    while(*start != ']'){
        ++start;
    }
    res->end = start;
    return res;
};

func* parse_C(char * start){
    // printf("parseC start %s\n", start);
    char * worker = start;
    char * end = NULL; /*be created to point to the end of the function object*/    
    func* res = (func*) malloc(sizeof(func));
    // printf("HELLO:%d\n", __LINE__);
    res->name = extract_name(start);
    res->me = (parameter*) malloc(sizeof(parameter));
    res->me->begin = start;
    res->me->end = NULL; 
    res->my_para_head = NULL;
    while(*worker != '('){
        ++worker;
    }/*now worker points to (*/
    ++worker;
    while (not_right_bracket(worker)){
        /*initial a new parameter node*/
        parameter* tmp_para = (parameter*)malloc(sizeof(parameter));
        tmp_para->begin = worker;
        para_list_node* tmp_node = (para_list_node* )malloc(sizeof(para_list_node));
        tmp_node->para_content = tmp_para;
        tmp_node->next = NULL;

        int name = judge_ABC(worker);
        switch(name){
            case 1:
                end = parse_A(worker)->end;
                break;
            case 2:
                end = parse_B(worker)->end;
                break;
            case 3:
                end = parse_C(worker)->me->end;
                break;
            default :/* else error */
                printf(" judge_ABC == 0 \n");
                return NULL;
        }
        worker = end;
        tmp_para->end = end;
        // printf("para is ");
        // print_str(tmp_node->para_content->begin,tmp_node->para_content->end);
        // printf("\n");
        
        list_add_node(res, tmp_node);
        worker = skip_comma(worker); /*skip ",", points to the next parameter,check ')'*/
    }
    end = worker;/*now should point to one )*/
    res->me->end = end;
    // printf("HELLO:%d", __LINE__);
    if (check_right_bracket(end)){ /*feel better to check it , $end should point to one )*/
        // printf("fffff");
        // print_func(res);        
        return res;
    }else{
        printf("There is no ) but parse_c end. \n");
        return NULL;
    }    
}

int check_right_bracket(char* str){
    /*return 1 if is ) , return 0 if not*/
    if (*str == ')'){
       return 1;
    }
    return 0;
}; 
int not_right_bracket(char* str){
    return !check_right_bracket(str);
};

char* extract_name(char * start){
    char* worker = start;
    while(*worker != '('){
        ++worker;
    }
    if(--worker < start){
        printf("extract_name(): name len < 0 \n");
        return NULL;
    }
    int len = (worker - start) + 1;
    char* res = (char*)malloc(len+1);
    strncpy(res,start,len);
    res[len] = '\0';
    return res;
}
// char * check_and_skip_left_bracket(char* str){};
char* skip_comma(char * str){ 
    /*
    check , if ','then skip to next parameter ,if ')'then return
    */
    if (*(++str)==')'){ 
        return str; /*if there is no other parameter*/
    }
    while(*str!=','){
        ++str;
    }
    return ++str;
};
void list_add_node(func* foo, para_list_node* new_node){
    
    if(foo->my_para_head == NULL){
        foo->my_para_head = new_node;
        return;
    }
    para_list_node* tmp = foo->my_para_head;
    while(tmp->next){
        // print_str(tmp->para_content->begin, tmp->para_content->end);
        // printf("\n");
        tmp = tmp->next;
    }
    tmp->next = new_node;
}


void print_str(char* start,char* end){
    if(start > end){
        printf("error in print_str, start > end.\n");
        return;
    }
    while(start<=end){
        printf("%c",*start);
        ++start;
    }
    return;
}
void print_func(func* foo){
    printf("********** my name is %s *********** \n",foo->name);
    if (foo->my_para_head == NULL){
        printf("********* no parameters *********** \n");
        return;
    }
    int num = 1;
    para_list_node* worker = foo->my_para_head;
    while(worker){
        printf("**** para %d is ",num);
        print_str(worker->para_content->begin,worker->para_content->end);
        printf("**** \n");
        ++num;
        worker = worker->next;
    }
    printf("********* %s end ********* \n",foo->name);
}


int main(){
    char *code = "fun1(1234,qwe , [3334)],fun2(),fun3(1,[2],3),abc)";
    printf("code: %s\n", code);
    /* start from struct C */
    char * worker = code;
    print_func(parse_C(worker));
    return 0;
}
