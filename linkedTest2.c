#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//리스트 Test2 값으로 list 찾기


typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* link;
}ListNode;

ListNode* search_list(ListNode *head, element x)
{
ListNode *p = head;

while (p != NULL) {
if (p->data == x) return p;
p = p->link;
}

return NULL;// 탐색 실패
}
ListNode* insert_first(ListNode* head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p; //head다음에 value가 저장된 노드를 추가한 것임.

    return head;
}
 

void print_list(ListNode* head)
{
    ListNode* p;
    for(p = head; p != NULL; p = p->link){
        printf("%d-> ", p->data );
    }
    printf("NULL \n");
}

//list 합치는 함수
ListNode* concat_list(ListNode *head1, ListNode *head2)

{

if (head1 == NULL) return head2;

else if (head2 == NULL) return head2;

else {
    ListNode *p;
    p = head1;

while (p->link != NULL)
    p = p->link;
    p->link = head2;
return head1;
}

}

//list를 역순으로 만드는 함수
ListNode* reverse(ListNode *head)
{
// 순회 포인터로 p, q, r을 사용
ListNode *p, *q, *r;
p = head;         // p는 역순으로 만들 리스트
q = NULL;        // q는 역순으로 만들 노드

while (p != NULL) {
r = q;          // r은 역순으로 된 리스트.    
// r은 q, q는 p를 차례로 따라간다.
q = p;
p = p->link;
q->link = r;      // q의 링크 방향을 바꾼다.
}

return q;
}

// 테스트 프로그램
int main(void)
{
ListNode *head = NULL;

head = insert_first(head, 10);
print_list(head);
head = insert_first(head, 20);
print_list(head);
head = insert_first(head, 30);
print_list(head);

if (search_list(head, 30) != NULL)
    printf("리스트에서 30을 찾았습니다. \n");
else
    printf("리스트에서 30을 찾지 못했습니다. \n");
return 0;
}