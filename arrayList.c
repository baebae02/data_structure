#include <stdio.h>
#include <stdlib.h>
//6장 연결리스트
#define MAX_LIST_SIZE 100// 리스트 최대 크기

typedef int element; //항목
typedef struct {
    element array[MAX_LIST_SIZE]; //배열 정의
    int size; // 현재 리스트 사이즈 (저장된 항목들 개수)
}ArrayListType;

//오류 처리
void error(char *message){
    fprintf(stderr,"%s\n", message); //err 와 errmsg 출력
    exit(1);
}

//리스트 초기화 
void init(ArrayListType *L){
    L->size = 0;
}

//리스트가 비어있으면 1, 그렇지 않으면 0을 반환
int is_empty(ArrayListType *L){
    return L -> size == 0;
}

//리스트가 가득차있으면 1, 그렇지 않으면 0을 반환
int is_full(ArrayListType *L){
    return L -> size == MAX_LIST_SIZE;
}

element get_entry (ArrayListType *L, int pos){
    if(pos<0 || pos >= L->size){
        error("위치 오류");
    }
    return L->array[pos];
}

//리스트 출력
void print_list(ArrayListType *L){
    int i;
    for(i=0; i<L->size; i++){
        printf("%d ->", L->array[i]);
    }
    printf("\n");
}

//리스트 마지막에 삽입
void insert_last(ArrayListType *L, element item){
    if(L->size >= MAX_LIST_SIZE){
        error("리스트 오버플로우");
    }
    L->array[L->size++] = item; //array의 구조체사이즈 ++ 자리에 item 삽입.
}

//원하는 자리에 리스트 삽입
void insert(ArrayListType *L, int pos, element item){
    if(!is_full(L) && (pos>=0) && (pos<=L->size)){
        for(int i=(L->size -1); i>=pos; i--){
            L->array[i+1]=L->array[i]; //pos 자리부터 L->size 까지 한칸씩 뒤로 밀어줌.
        }
        L->array[pos] = item; //원하는 pos에 item 삽입
        L->size++;
    }
}

//element 삭제
element delete(ArrayListType *L, int pos){
    element item;
    if(pos<0 || pos >= L->size){
        error("위치 오류");
    }
    item=L->array[pos];
    for(int i=pos; i<(L->size-1); i++){
        L->array[i] = L->array[i+1]; //한칸씩 땡겨줌.
    }
    L->size--;
    return item;
}

int main(void){
    //ArrayList를 생성하고 ArrayListType을 가르키는 포인터를 함수의 매개변수로 전달한다.
    ArrayListType list;
    init(&list);
    insert(&list, 0, 10); print_list(&list);//0번째 위치에 10 추가
    insert(&list, 0, 20); print_list(&list);//0번째 위치에 20 추가
    insert(&list, 0, 30); print_list(&list);//0번째 위치에 30 추가
    insert_last(&list, 40); print_list(&list);//맨 끝에 40 추가
    delete(&list,0); print_list(&list); //0번째 항목 삭제
    return 0;
}