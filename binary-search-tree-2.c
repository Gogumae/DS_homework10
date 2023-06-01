/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;


/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;



int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("             [----- [이찬희] [2019068057] -----]	     		 \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	while(1) {  //무한 반복
		while(node != NULL) {  //node가 NULL이 아닐때까지 Stack에 push 후 왼쪽 child로 이동
			push(node);
			node = node->left;
		}
		node = pop();  //Stack에서 pop

		if(!node) {  //만약 노드가 NULL이 되면 반복문 탈출
			break;
		}

		printf(" [%d] ", node->key);  //pop한 노드의 key를 출력

		node = node->right;  //node의 오른쪽 child로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(!ptr) {
		return;
	}

	enQueue(ptr);

	for(;;) {
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);
			if(ptr->left) {
				enQueue(ptr->left);
			}
			if(ptr->right) {
				enQueue(ptr->right);
			}
		}
		else {
			break;
		}
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if(head == NULL || head->left == NULL) {
		printf("nothing to delete");
		return 0;
	}

	Node* root = head->left;
	Node* parent = NULL;
	Node* now = root;

	while((now != NULL) && (now->key) != key) {  //삭제할 key값을 가진 노드를 찾는 반복문
		if(now->key != key) {
			parent = now;

			if(now->key > key) {
				now = now->left;
			}
			else {
				now = now->right;
			}
		}
	}

	if(now == NULL) {
		printf("No node for key");
		return 0;
	}

	/* 삭제할 노드가 리프 노드일 경우 */
	if(now->left == NULL && now->right == NULL) {
		if(parent != NULL) {  //부모 노드에서 child로의 연결 해제
			if(parent->left = now) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {  //parent가 NULL이면 root 노드라는 뜻이므로 헤드 노드에서 root 노드 연결 해제
			head->left = NULL;
		}

		free(now);  //노드 메모리 반환
		return 0;
	}

	/* 삭제할 노드가 1개의 자식 노드를 가졌을 때 */
	if(now->left == NULL || now->right == NULL) {

		Node* child;  //삭제할 노드의 부모 노드와 연결시킬 삭제할 노드의 자식 노드를 child에 저장
		if(now->left != NULL) {  //왼쪽이나 오른쪽에 존재하는 자식 노드를 child에 저장
			child = now->left;
		}
		else {
			child = now->right;
		}

		if(parent != NULL) {
			if(parent->left == now) {  //만약 삭제할 노드가 부모 노드의 왼쪽 자식이었으면
				parent->left = child;  //저장한 child 노드를 부모 노드의 왼쪽 자식으로 연결
			}
			else {  //반대면 오른쪽으로 연결
				parent->right = child;
			}
		}
		else {  //부모 노드가 NULL이면 root 노드이므로 child 노드를 root 노드로 설정
			root = child;
		}

		free(now);  //노드 메모리 반환
		return 0;
	}

	/* 삭제할 노드가 2개의 자식 노드를 가졌을 때 */
	if(now->left != NULL && now->right != NULL) {

		Node* child = now->right;  //현재 노드의 오른쪽 자식 노드
		parent = now;  //부모 노드를 현재 노드로

		while(child->left != NULL) {  //자식 노드의 왼쪽 자식 노드가 NULL이 되기 전까지
			parent = child;  //부모 노드 위치를 옮기고 왼쪽 자식 노드로 트리 이동
			child = child->left;
		}

		if(parent->right == child) {  //부모 노드의 오른쪽 자식 노드가 child가 되면
			parent->right = child->right;  //부모 노드의 오른쪽 노드를 child의 오른쪽 자식 노드로
		}
		else {  //반대의 경우 왼쪽 노드를 child의 오른쪽 자식 노드로
			parent->left = child->right;
		}

		now->key = child->key;  //now의 key를 child의 key로 바꾼 후

		free(child);  //child 메모리 반환
		return 0;
	}
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if(top < 0) {  //스택이 비어있으면 NULL을 리턴
		return NULL;
	}

	return stack[top--];  //pop을 해서 스택의 top 값을 줄인다
}

void push(Node* aNode)
{
	stack[++top] = aNode;  //aNode를 스택의 top에 1 높은 곳에 넣는다
}



Node* deQueue()
{
	if(front == rear) {  //큐가 비어있으면 NULL 반환
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;  //front를 한 칸 이동시키고
	return queue[front];  //큐의 front 반환
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;  //rear를 한 칸 이동
	if(front == rear) {  //만약 큐가 꽉 차있으면 리턴
		return;
	}

	queue[rear] = aNode;   //큐의 rear에 aNode를 넣는다
}




