//==========원형 큐 코드===========
#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // time()
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct { //큐 타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

//오류 함수
void error(char msg[]){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

//q를 초기화
void init_queue(QueueType* q){
    q->front = q->rear = 0;
}

//공백 상태 검출
int is_empty(QueueType* q){
    return (q->front == q->rear);
}

//포화 상태 검출
int is_full(QueueType* q){
    return ((q->rear+1) % MAX_QUEUE_SIZE == q->front);
}

//삽입 함수, is_full 아니면 끝에 item 추가
void enqueue(QueueType* q, element item){
    if(is_full(q)){
        error("F");
    }
    q->rear = (q->rear +1 % MAX_QUEUE_SIZE);
    q->data[q->rear] = item;
}

//삭제 함수, is_empty 아니면 끝 item 삭제 & 반환
element dequeue(QueueType* q){
    if(is_empty(q)){
        error("queueIsEmpty");
    }
    q->front = (q->front+1)% MAX_QUEUE_SIZE;
    return q->data[q->front];
}

//원형 큐 출력함수
void queue_print(QueueType *q){
    printf("QUEUE(front=%d rear=%d) =", q->front, q->rear);
    if(!is_empty(q)){
        int i = q->front;
        do {
            i = (i+1)%(MAX_QUEUE_SIZE);
            printf("%d |", q->data[i]);
            if(i==q->rear)
                break;
        }while(i!= q->front);
    }
    printf("\n");
}
int main(void){
    QueueType queue;
    int element;

    init_queue(&queue);
    printf("--데이터 추가 단계 --\n");
    while(!is_full(&queue)){
        printf("정수를 입력하시오:");
        scanf("%d", &element);
        enqueue(&queue, element);
        queue_print(&queue);
    }
    printf("큐는 포화상태입니다.\n\n");
    printf("--데이터 삭제 단계 --\n");
    while(!is_empty(&queue)){
        element = dequeue(&queue);
        printf("꺼내진 정수 : %d\n", element);
        queue_print(&queue);
    }
    printf("큐는 공백상태입니다.\n");
    return 0;
}