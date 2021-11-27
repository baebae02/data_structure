typedef struct ListNode { // 노드 타입
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

 

// 연결 리스트 헤더
typedef struct ListType { // 리스트 헤더 타입
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

 

// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//  리스트 헤더 생성 함수
ListType* create()
{
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

 

// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수,
// expon는 지수
void insert_last(ListType* plist, int coef, int expon)
{
    ListNode* temp =
    (ListNode *)malloc(sizeof(ListNode));

    if (temp == NULL) error("메모리 할당 에러");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    if (plist->tail == NULL) {
    plist->head = plist->tail = temp;
    }

else {
    plist->tail->link = temp;
    plist->tail = temp;
}
plist->size++;
}

// list3 = list1 + list2

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
ListNode* a = plist1->head;
ListNode* b = plist2->head;
int sum;

 

while (a && b) {
if (a->expon == b->expon) {   // a의 차수 > b의 차수
sum = a->coef + b->coef;
if (sum != 0) insert_last(plist3, sum, a->expon);
a = a->link; b = b->link;
}

else if (a->expon > b->expon) {  // a의 차수 == b의 차수
insert_last(plist3, a->coef, a->expon);
a = a->link;
}

else {// a의 차수 < b의 차수
insert_last(plist3, b->coef, b->expon);
b = b->link;
}

}