//=========큐의 응용==========
/*
1. is_customer_arrived 함수는 랜덤 숫자를 생성하여 시물레이션 파라미터 변수인 arrival_prov와 비교하여 작으면 
새로운 고객이 들어왔다고 판단. 
2. 고객의 아이디, 도착시간, 서비스 시간 등의 정보를 만들어 구조체에 복사하고 이 구조체를 파라미터로 하여
큐의 삽입 함수 enquene()을 호출한다. 
3. 고객이 필요로 하는 서비스 시간은 역시 랜덤 숫자를 이용하여 생성된다.
4. 지금 서비스 하고 있는 고객이 끝났는지 검사는, service_time == 0으로 판단한다. 
5. service_time이 0이면 큐에서 고객 구조체를 하나 꺼내어 서비스를 시작한다. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // time()
#define MAX_QUEUE_SIZE 5
 
typedef struct { 
    int id;
    int arrival_time;
    int service_time;
}element;   

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
    printf("\n");
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
