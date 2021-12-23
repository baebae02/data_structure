#include <stdio.h>
#include <stdlib.h>

/* 파일 이름 */
#define filename "test_trace.txt"
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

int time_count; /* LRU를 구현하기 위한 시간 */
int d_total;   /* 데이터 캐시 접근 횟수 및 miss 횟수, 메모리 쓰기 총 횟수 */
int miss; /* 실패 횟수*/
int hit; /* 성공 횟수 */
int tree_num; /*tree 개수*/
int queue_num; /*queue 개수*/



 

//======================================================================
//Binary Searcch Tree
typedef struct cache_buffer {
    unsigned long blkno;
    struct cache_buffer *next, *prev;
}cache_buffer;

//오른쪽으로 회전 
cache_buffer *rotateRight(cache_buffer *parent)
{
	cache_buffer *child = parent->prev;
	parent->prev = child->next;
	child->next = parent;
	
	return child;
}

//왼쪽으로 회전 
cache_buffer *rotateLeft(cache_buffer *parent)
{
	cache_buffer *child = parent->next;
	parent->next = child->prev;
	child->prev = parent;
	
	return child;
}

//트리 높이 구하기 
int getHeight(cache_buffer *root)
{
	int height = 0;
	if(root != NULL) 
		height = 1 + max(getHeight(root->prev), getHeight(root->next));
	return height;
}

//트리 균형도 구하기 
int getBalance(cache_buffer *node)
{
	if(node == NULL) return 0;
	return getHeight(node->prev) - getHeight(node->next);
}

//탐색 연산 (순환적인 방법)
cache_buffer *search(cache_buffer *node, unsigned long blkno){
    if(node == NULL) return NULL;
    if(blkno == node->blkno) return node;
    else if(blkno < node->blkno){
        return search(node->prev, blkno);
    }
    else{
        return search(node->next, blkno);
    }
}

//새로운 노드 생성
cache_buffer *new_node(unsigned long blkno){
    cache_buffer *temp = (cache_buffer *)malloc(sizeof(cache_buffer));
    temp->blkno = blkno;
    temp->prev = temp->next = NULL;
    // tree_num++;
    return temp;
}

// 노드 삽입
cache_buffer *insert_node(cache_buffer *node, unsigned long blkno){
    //트리가 공백이면 새로운 노드를 반환한다. 
    if(node == NULL) return new_node(blkno);
    
    //그렇지 않으면 순환적으로 트리를 내려간다. 
    if(blkno <node->blkno){
        node->prev = insert_node(node->prev, blkno);
    }
    else if(blkno > node->blkno){
        node->next = insert_node(node->next, blkno);
    }
    else	
		return node; //중복을 허용하지 않는다 
    
    //노드들의 균형인수 재계산
	int balance = getBalance(node);
	
	//LL 타입 처리
	if(balance > 1 && blkno < node->prev->blkno) 
		return rotateRight(node);
		
	//RR 타입 처리 
	if(balance < -1 && blkno > node->next->blkno)
		return rotateLeft(node);
		
	//LR 타입 처리
	if (balance > 1 && blkno > node->prev->blkno) {
		node->prev = rotateLeft(node->prev);
		return rotateRight(node);
	}
	
	//RL 타입 처리
	if (balance < -1 && blkno < node->next->blkno) {
		node->next = rotateRight(node->next);
		return rotateLeft(node);
	}
    //변경된 루트 포인터를 반환한다. 
    return node;
}

//주어진 노드 아래에서 최소 키값을 가지는 노드를 반환
cache_buffer *min_value_node(cache_buffer *node) {
	cache_buffer *current = node;

    //맨 왼쪽 단말 노드를 찾으러 내려감
	while(current->prev != NULL) {
		current = current->prev;
	}
	return current;
} 

//노드 삭제
cache_buffer *delete_node(cache_buffer *root, unsigned long blkno){
    if(root==NULL) return root;
    
    //만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임. 
    if(blkno<root->blkno){
        root->prev=delete_node(root->prev, blkno);
    }

    //만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if(blkno> root->blkno){
        root->next = delete_node(root->next, blkno);
    }

    //키가 루트와 같으면 이 노드를 삭제하면 됨
    else {
        //첫번째나 두번째 경우
        //즉 삭제하려는 노드가 단말노드이거나 하나의 서브트리를 갖고 있는 경우
        if(root->prev == NULL){
            cache_buffer *temp = root->next; 
            //왼쪽 자식이 비어있으면 temp에 오른쪽 자식을 저장하고 반환
            free(root);
            return temp;
        }
        else if(root->next == NULL){
            cache_buffer *temp = root->prev;
            //오른쪽 자식이 비어있으면 temp에 왼쪽 자식을 저장하고 반환
            free(root);
            return temp;
        }
        // 번째 경우
        //즉 삭제하려는 노드가 두개의 서브트리를 갖고 있는 경우
        cache_buffer *temp = min_value_node(root->next);

        //중외순회시 후계노드를 복사한다. 
        root->blkno = temp->blkno;
        //후계노드를 삭제한다. 
        root->next = delete_node(root->next, temp->blkno);
    }
    return root;
}

//중위 순회
void inorder(cache_buffer *tree) {
	if (tree !=  NULL) {
		inorder(tree->prev);
		printf("[%zu]-> ", tree->blkno);
		inorder(tree->next);
	}
}

//======================================================================
//큐 구현
typedef unsigned long element; 
typedef struct ListNode {
    element data;
    struct ListNode* link;
}ListNode;

typedef struct Queue {
	ListNode *front, *rear;
} Queue;

void init(Queue *q) {
	q->front = q->rear = NULL;
}

int isEmpty(Queue *q) {
	return (q->front == NULL);
}

int isFull(Queue *q) {
    if(queue_num == 8192){
        return -1;
    }
	return 0;
}

void printQueue(Queue *q) {
	ListNode *node = q->front;
	while(node != NULL)	{
		printf("%zu -> ", node->data);
		node = node->link;
	}
	printf("\n");
}

element dequeue(Queue *q) {
	if(isEmpty(q)) {
		fprintf(stderr, "QUEUE IS EMPTY!!!");
	}
	ListNode *node = q->front;
	element data = node->data;
	q->front = q->front->link;
	free(node);
    queue_num--;
	return data;
}

void enqueue(Queue *q, element data, cache_buffer *tree) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	node->link = NULL;
	if(isEmpty(q)) {
		q->front = q->rear = node;
	} 
    if(isFull(q)){
        dequeue(q);
        delete_node(tree,data);
    }
    q->rear->link = node;
    q->rear = node;	
    queue_num++;
}

//======================================================================

int main(){
	FILE *fp = NULL;
    fp = fopen(filename, "r");
    unsigned long addr; /* 파일로부터 읽은 값을 저장하는 변수 */
    cache_buffer *tree = NULL;
    Queue *queue = (Queue *)malloc(sizeof(Queue));
	init(queue);

    //파일에서 값을 불러와서
    while(!feof(fp)){
        fscanf(fp, "%zu\n", &addr);
        if(search(tree, addr)){
            d_total++;
            hit++;
            continue;
        }
        enqueue(queue, addr, tree);
        tree = insert_node(tree, addr);
        d_total++;	/* 데이터 캐시 접근횟수를 늘린다. */
        miss++;
    }
    // printf("이진 탐색 트리 중위 순회 결과\n");
    // inorder(tree);
    // printf("\n\n");
    // printf("큐 결과\n");
    // printQueue(queue);
    printf("total access= %d \t hit=%d \t miss=%d \n", d_total, hit, miss);
    // printf("time=%d\n", time_count);
    printf("hit ratio= %lf\n", (double)hit/(double)d_total);
    printf("miss ratio= %lf\n", (double)miss/(double)d_total);
    // printf("queue_num= %d\n", queue_num);
    // printf("tree_num= %d\n", tree_num);
    return 0;
}



