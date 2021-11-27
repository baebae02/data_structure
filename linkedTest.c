#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//리스트 Test Apple , Banana ....
typedef struct {
char name[100];
} element;
 
typedef struct ListNode {     // 노드 타입
element data;
struct ListNode *link;
} ListNode;

 

// 오류 처리 함수
void error(char *message)
{
fprintf(stderr, "%s\n", message);
exit(1);
}
ListNode* insert_first(ListNode *head, element value)
{
ListNode *p = (ListNode *)malloc(sizeof(ListNode));    //(1)
p->data = value;// (2)
p->link = head;// 헤드 포인터의 값을 복사    //(3)
head = p;// 헤드 포인터 변경        //(4)
return head;
}

void print_list(ListNode *head)
{
for (ListNode *p = head; p != NULL; p = p->link)
printf("%s->", p->data.name); //그냥 data하니까 이상한 코드로 나옴. main에서 data.name으로 넘겨줌.
printf("NULL \n");
}

// 테스트 프로그램

int main(void)
{
ListNode *head = NULL;
element data;

strcpy(data.name, "APPLE");
head = insert_first(head, data);
print_list(head);

strcpy(data.name, "KIWI");
head = insert_first(head, data);
print_list(head);

strcpy(data.name, "BANANA");
head = insert_first(head, data);
print_list(head);
return 0;
}