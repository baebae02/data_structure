// 1. implement stack data structure
// 2. example
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s){
    s->top = -1; // top을 초기화
}

int is_empty(StackType *s){
    return(s->top == -1); // empty면 1 반환
}

int is_full(StackType* s){
    return (s->top == (MAX_STACK_SIZE -1)); // full이면 1 반환
}

void push(StackType* s, element item){
    if(is_full(s)){
        printf("overflow\n");
    }
    else {
        s->data[++(s->top)] = item; // s의 top값을 증가시키고 맨 위에 item을 넣음
    }
}

element pop(StackType* s){
    if(is_empty(s)){
        printf("underflow\n");
        exit(1);
    }
    else {
        return s->data[(s->top)--]; // pop에 있는 걸 반환하고 top -- 
    }
}

element peek(StackType* s){
    if(is_empty(s)){
        printf("underflow\n");
        exit(1);
    }
    else {
        return s->data[(s->top)]; // pop에 있는 걸 반환하고 top의 값을 변경하진 않음
    }
}

int size(StackType* s){
    return s->top + 1; // top값 + 1
}


/*
    회문
    : 앞으로 읽어도, 뒤로 읽어도 같은 문자열
*/

int main(){
    char line[128];
    StackType s; // stack 선언

    init_stack(&s);
    printf("input string!\n");
    gets_s(line, 128);

    for(int i=0; i<(strlen(line)/2); i++){ // 반 잘라서 차레대로 stack에 넣음
        push(&s, line[i]);
    }

    for( int i=(int)(strlen(line) / 2.0+0.5); i<strlen(line); i++){ // line의 길이 나누기 2 더하기 0.5 를 정수형으로 바꿈 ==> 반으로 나눈 그다음 인덱스
        if(pop(&s) != line[i]){
            printf("NO\n");
            return -1;
        }
    }

    printf("Yes!\n");
    return 0;
}