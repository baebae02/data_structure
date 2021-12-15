//스레드 이진 트리
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
    int is_thread; //만약 오른쪽 링크가 스레드면 TRUE
}TreeNode;

//중위후속자를 찾는 함수 작성
TreeNode *find_successor(TreeNode *p){
    //q는 p의 오른쪽 포인터
    TreeNode *q = p->right;
    //만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환
    if(q==NULL || p->is_thread == TRUE){
        return q;
    }
    //만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
    while(q->left != NULL) q=q->left;
    return q;
}

void thread_inorder(TreeNode *t){
    TreeNode *q;
    q=t;
    while(q->left)q=q->left; //가장 왼쪽 노드로 간다. 
    do {
        printf("%c ", q->data); //데이터 출력
        q=find_successor(q); //후속자 함수 호출
    }while(q); //q가 NULL이 아니면
}

int main(void){
    TreeNode n1 = {'A', NULL, NULL, 1};
    TreeNode n2 = {'B', NULL, NULL, 1};
    TreeNode n3 = {'C', &n1, &n2, 1};
    TreeNode n4 = {'D', NULL, NULL, 1};
    TreeNode n5 = {'E', NULL, NULL, 1};
    TreeNode n6 = {'F', &n4, &n5, 1};
    TreeNode n7 = {'G', &n3, &n6, 1};
    TreeNode *exp = &n7;

    n1.right = &n3;
    n2.right = &n7;
    n4.right = &n6;

    thread_inorder(exp);
    return 0;
}