//==========원형 큐 코드===========
#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // time()
#define MAX_QUEUE_SIZE 5

typedef int element;
// typedef struct { 
//     int id;
//     int arrival_time;
//     int service_time;
// }element;   

typedef struct { //큐 타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

//오류 함수
void error(char* msg){
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
        error('queueIsFull');
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
    print("\n");
}
int main(void){
    int minutes = 60;
    int total_wait = 0;
    int total_customer = 0;
    int service_time = 0;
    int service_customer;
    QueueType queue;

    init_queue(&queue);

    srand(time(NULL));

    for(int clock=0; clock < minutes; clock++){
        printf("current time = %d\n", clock);
        
        //in
        if(rand() % 10 < 3) {
            element customer;
            customer.id = total_customer++;
            customer.arrival_time=clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&queue, customer);

            printf("customer: %d, arrival_time: %d, service_time: %d",
            customer.id, customer.arrival_time, customer.service_time);      
            }
        
        //service
        if(service_time > 0){
            printf("servicing customer: %d", service_customer);
            service_time--;
        }
        //free
        else {
            if(!is_empty(&queue)){
                element customer = dequeue(&queue);

                service_customer=customer.id;
                service_time = customer.service_time;
                printf("customer: %d, start_time: %d, wait_time: %d",
                customer.id, clock, clock-customer.arrival_time);
                total_wait += clock - customer.arrival_time;
            }
        }
    }
    printf("total wait time = %d\n", total_wait);
    return 0;
}