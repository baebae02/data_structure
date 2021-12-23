#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 43
#define filename "test_trace.txt"
#define MAX_SIZE 8192

int miss; /* 실패 횟수*/
int hit; /* 성공 횟수 */
int d_total;   /* 데이터 캐시 접근 횟수 및 miss 횟수, 메모리 쓰기 총 횟수 */
int queue_num; /*queue 개수*/

// typedef struct element{
// 	unsigned long key;
// } element;
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
//큐 구현
typedef unsigned long element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
	int length;
} ListNode;

void print_list(ListNode* head)
{
	ListNode* p;
	
	if (head == NULL) return;
	p = head->link;
	do {
		printf("%zu->", p->data);
		p = p -> link;
	} while (p != head);
	printf("%zu->\n", p->data); //Last node
} 

ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) return NULL;
	removed = head->link;
	head->link = removed->link;
    head->length--;
	free(removed);
	return head;
}


ListNode* insert_first(ListNode* head, element data)
{
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
		head->length = 1;
	}
	else {
		node->link = head->link;
		head->link = node;
		head->length ++;
	}
	return head;
}

ListNode* insert_last(ListNode* head, element data, struct list* ht[])
{
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
    
	if (head == NULL) {
		head = node;
		node->link = head;
		head->length = 1;
	}
	else {
        if(head->length == MAX_SIZE){
            hash_chain_delete(head->link->data, ht);
            delete_first(head);
            // printf("length= %d\n", head->length);
        }   
		node->link = head->link;
		head->link = node;
		node->length = head->length;
		head = node;
		head->length ++;
	}
	return head;
}


void get_length(ListNode* head)
{
	printf("\n%d\n", head->length);	
    // return head->length;
}

ListNode *search(ListNode *head, element data)
{
	ListNode *p;
	
	if (head == NULL) return NULL;
	p = head->link;
	do {
		if(p->data == data) 
			return p;
		p = p->link;
	} while (p != head);
	if(p->data == data) 
		return p;
	printf("found NULL");
	return NULL;
}
//======================================================================
#define SIZE 5
int main(void)
{
	element e;
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    unsigned long addr; /* 파일로부터 읽은 값을 저장하는 변수 */
    ListNode *head = NULL;

    //파일에서 값을 불러와서
    while(!feof(fp)){
        fscanf(fp, "%zu\n", &addr);
        e = addr;
        if(hash_chain_search(e, hash_table)){
            head=delete_first(head);
            head=insert_last(head,e, hash_table);
            d_total++;
            hit++;
            continue;
        }
        hash_chain_add(e, hash_table);
        miss++;
        head = insert_last(head, e, hash_table);
        d_total++;	/* 데이터 캐시 접근횟수를 늘린다. */
        // print_list(head);
    }
    // hash_chain_print(hash_table);
    printf("total access= %d \t hit=%d \t miss=%d \n", d_total, hit, miss);
    printf("hit ratio= %lf\n", (double)hit/(double)d_total);
    printf("miss ratio= %lf\n", (double)miss/(double)d_total);
    // hash_chain_print(hash_table);
	return 0;
}