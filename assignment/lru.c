#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 113
#define filename "test_trace.txt"
#define MAX_SIZE 8192

int miss; /* 실패 횟수*/
int hit; /* 성공 횟수 */
int d_total;   /* 데이터 캐시 접근 횟수 및 miss 횟수, 메모리 쓰기 총 횟수 */
int queue_num; /*queue 개수*/


typedef unsigned long element;
typedef struct list
{
	element item;
	struct list *link;
}list;

struct list *hash_table[TABLE_SIZE];
//제산 함수를 사용한 해싱 함수
int hash_function(int key)
{
	return key % TABLE_SIZE;
}

//체인법을 이용하여 테이블에 키를 삽입
void hash_chain_add(element item, struct list *ht[])
{
	int hash_value = hash_function(item);
	list *ptr;
	list *node_before = NULL, *node = ht[hash_value];
	for (; node; node_before = node, node = node->link) {
		if (node->item == item) {
			// fprintf(stderr, "이미 탐색 키가 저장되었음.\n");
			return;
		}
	}
	ptr = (list *)malloc(sizeof(list));
	ptr->item = item;
	ptr->link = NULL;
	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
}

//체인법을 이용하여 테이블에 저장된 키를 탐색
int hash_chain_search(element item, struct list *ht[])
{
	struct list *node;

	int hash_value = hash_function(item);
	for (node = ht[hash_value]; node; node = node->link) {
		if (node->item == item) {
			// fprintf(stderr, "탐색 %zu 성공 \n", item.key);
			return 1;
		}
	}
	// printf("키를 찾지 못했음\n");
    return 0;
}

//테이블에 저장된 키 삭제
void hash_chain_delete(element item, list *ht[])
{
    list *delNode = (list *)malloc(sizeof(list));
    int hash_value = hash_function(item);
    if(hash_chain_search(item, ht)){
        if(ht[hash_value]->item == item){
            delNode = ht[hash_value];
            ht[hash_value] = ht[hash_value]->link;
        }
        else{
            list* node = ht[hash_value];
            list* nextnode = node->link;
            while (nextnode)
            {
                if (nextnode->item == item)
                {
                    node->link = nextnode->link;
                    delNode = nextnode;
                    break;
                }
                node = nextnode;
                nextnode = node->link; 
            }
        }
    }
    free(delNode); 
}


void hash_chain_print(struct list *ht[])
{
	struct list *node;
	int i;
	printf("\n===============================\n");
	for (i = 0; i<TABLE_SIZE; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%zu->", node->item);
		}
		printf("\n");
	}
	printf("===============================\n");
}

//======================================================================
//큐 구현 (double list)
typedef struct QueueNode {    // 큐의 노드의 타입
    element data;
    struct QueueNode *link;
} QueueNode;


typedef struct {        // 큐 ADT 구현
    QueueNode *front, *rear;
    int length;
} LinkedQueueType;
// 공백 상태 검출 함수

int is_empty(LinkedQueueType *s)
{
    return (s->front == NULL);
}

// 포화 상태 검출 함수
int is_full(LinkedQueueType *s)
{
    return(s->length >= MAX_SIZE);
}

void enqueue(LinkedQueueType *q, element data)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = data; // 데이터 저장
    temp->link = NULL;         // 링크 필드를 NULL
    if (is_empty(q)) {         // 큐가 공백이면
        q->front = temp;
        q->rear = temp; 
    }
    else { // 큐가 공백이 아니면
    q->rear->link = temp;  // 순서가 중요
    q->rear = temp;
    }
}
element dequeue(LinkedQueueType *q)
{

    QueueNode *temp =q-> front;
    element data;
    if (is_empty(q)) {        // 공백상태
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }   
    else {
        data = temp->data; // 데이터를 꺼낸다.
        q->front = q->front->link; // front로 다음노드
        if (q->front == NULL) // 공백 상태
        q->rear = NULL;
        free(temp); // 동적메모리 해제
        return data;         // 데이터 반환
    }
}
//======================================================================
#define SIZE 5
int main(void)
{
	element e;
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    unsigned long addr; /* 파일로부터 읽은 값을 저장하는 변수 */
    LinkedQueueType *head;
    head=(LinkedQueueType *)malloc(sizeof(LinkedQueueType));

    //파일에서 값을 불러와서
    while(!feof(fp)){
        fscanf(fp, "%zu\n", &addr);
        e = addr;
         
        if(hash_chain_search(e, hash_table)){
            enqueue(head, e);
            dequeue(head);
            d_total++;
            hit++;
           
            continue;
        }
        if(head->length == MAX_SIZE){
            element data = dequeue(head);
            hash_chain_delete(data, hash_table);
        }

        enqueue(head, e);
        hash_chain_add(e, hash_table);
        miss++;
        d_total++;	/* 데이터 캐시 접근횟수를 늘린다. */
    }
    // hash_chain_print(hash_table);
    printf("total access= %d \t hit=%d \t miss=%d \n", d_total, hit, miss);
    printf("hit ratio= %lf\n", (double)hit/(double)d_total);
    printf("miss ratio= %lf\n", (double)miss/(double)d_total);
	return 0;
}