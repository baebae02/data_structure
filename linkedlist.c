#include <stdio.h>
#include <stdlib.h> //이 안에 alloc
//6. 연결리스트
//단순연결리스트

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
}ListNode;

void error(char* message)
{
    printf("%s\n", message);
    exit(1);
}

ListNode *insert_first(ListNode *head, int value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p; //head다음에 value가 저장된 노드를 추가한 것임.

    return head;
}

//노드 pre 뒤에 새로운 노드 삽입
ListNode *insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link; //pre 다음으로 p를 추가
    pre->link = p;
    
    return head;
}

ListNode* insert_sorted(ListNode *head, element value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    ListNode* cur;
    p->data = value;
    p->link = NULL;
    
    if(head == NULL){
        head = p;
        return head;
    }

    cur = head; //cur을 head로 초기화
    while(cur->link != NULL && cur->link->data < p->data){ //why : 오름차순이니까.
        cur = cur->link; //다음 차례로 넘어감.
    }

    p->link = cur->link;
    cur->link = p;

    return head;

}

ListNode *delete_first(ListNode* head){
    ListNode *to_be_removed;

    if(head == NULL){
        return NULL;
    }
    to_be_removed = head;
    head = to_be_removed->link; //head 다음 노드가 삭제 
    free(to_be_removed); //메모리 반납

    return head;

}

//pre가 가르키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode *head, ListNode *pre)
{
    ListNode *to_be_removed;
    to_be_removed = pre->link;
    pre->link = to_be_removed->link;
    free(to_be_removed);
    return head; 
}

void print_list(ListNode* head)
{
    for(ListNode *p = head; p != NULL; p = p->link){
        printf("%d-> ", p->data );
    }
    printf("NULL \n");
}

int main() {
    ListNode* head = NULL;

    for(int i=0; i<5; i++){
        head = insert_first(head,i);
        print_list(head);
    }
    
    head = insert_sorted(head, 8);
    print_list(head);
    head = insert_sorted(head, 7);
    print_list(head);
    head = insert_sorted(head, 6);
    print_list(head);

    for(int i=0; i<5; i++){
        head = delete_first(head);
        print_list(head);
    }

    return 0;
}