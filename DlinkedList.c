//이중연결리스트
#pragma waring(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
}DListNode; 

void init(DListNode* phead)
{ //phead는 head의 pointer를 뜻함
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(DListNode* before, element data){
    DListNode* newnode;
    newnode = (DListNode *)malloc(sizeof(DListNode));
    newnode->data = data;

    //4개의 pointer를 바꿔야 함
    //1. 새로 삽입될 두 포인터 변경
    newnode->llink = before;
    newnode->rlink = before->rlink;

    //2. 새로 삽입되는 노드를 가르키는 두 포인터 변경
    before->rlink->llink = newnode;
    before->rlink = newnode;

}

void ddelete(DListNode* phead, DListNode* removed){
    if(removed == phead){
        return;
    }
    //삭제될 노드를 가르키고 있던 두 포인터를 변경
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;

    free(removed);
}

//특정 값을 가지고 있는 노드를 검색해서 그 노드의 포인터를 반환하는 함수
DListNode *search(DListNode* phead, element data){
    DListNode* p;
    for(p=phead->rlink; p!=phead; p=p->rlink){
        if(p->data == data){
            return p;
        }
    }
    return NULL;
}
void print_dlist(DListNode* phead)
{
    DListNode* p;
    for(p=phead->rlink; p!=phead; p=p->rlink){
        printf("<- |%d| ->", p->data);
    }
    printf("\n");

    //while문을 쓴다면
    // p=phead->rlink;
    // while(p!=phead){
    //      printf("<- |%d| ->", p->data);
    //      p=p->rlink;
    // }
}
int main(){
    DListNode * head;
    element data;
    head = (DListNode *)malloc(sizeof(DListNode));

    init(head);
    dinsert(head, 1);
    dinsert(head, 2);
    dinsert(head, 3);
    print_dlist(head);

    printf("검색 값: ");
    scanf("%d", &data);

    if(search(head, data) != NULL){
        printf("%d is in list\n", data);
    }
    else{
        printf("%d is not in list\n", data);
    }
    return 0;
}