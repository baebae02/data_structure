#include <stdio.h>
#include <stdlib.h>
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

//AVL 트리 노드 정의
typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
} Node; 

//오른쪽으로 회전 
Node *rotateRight(Node *parent)
{
	Node *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

//왼쪽으로 회전 
Node *rotateLeft(Node *parent)
{
	Node *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

//트리 높이 구하기 
int getHeight(Node *root)
{
	int height = 0;
	if(root != NULL) 
		height = 1 + max(getHeight(root->left), getHeight(root->right));
	return height;
}

//트리 균형도 구하기 
int getBalance(Node *node)
{
	if(node == NULL) return 0;
	return getHeight(node->left) - getHeight(node->right);
}

//노드 생성 
Node *createNode(int key)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//노드 삽입 
Node *insertNode(Node *node, int key)
{
	if(node == NULL) return createNode(key);
	if(key < node->key)
		node->left = insertNode(node->left, key);
	else if(key > node->key)
		node->right = insertNode(node->right, key);
	else	
		return node; //중복을 허용하지 않는다 
		
	//노드들의 균형인수 재계산
	int balance = getBalance(node);
	
	//LL 타입 처리
	if(balance > 1 && key < node->left->key) 
		return rotateRight(node);
		
	//RR 타입 처리 
	if(balance < -1 && key > node->right->key)
		return rotateLeft(node);
		
	//LR 타입 처리
	if (balance > 1 && key > node->left->key) {
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	
	//RL 타입 처리
	if (balance < -1 && key < node->right->key) {
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	return node;
}