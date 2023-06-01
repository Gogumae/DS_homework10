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
		printf("             [----- [������] [2019068057] -----]	     		 \n");
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
	while(1) {  //���� �ݺ�
		while(node != NULL) {  //node�� NULL�� �ƴҶ����� Stack�� push �� ���� child�� �̵�
			push(node);
			node = node->left;
		}
		node = pop();  //Stack���� pop

		if(!node) {  //���� ��尡 NULL�� �Ǹ� �ݺ��� Ż��
			break;
		}

		printf(" [%d] ", node->key);  //pop�� ����� key�� ���

		node = node->right;  //node�� ������ child�� �̵�
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

	while((now != NULL) && (now->key) != key) {  //������ key���� ���� ��带 ã�� �ݺ���
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

	/* ������ ��尡 ���� ����� ��� */
	if(now->left == NULL && now->right == NULL) {
		if(parent != NULL) {  //�θ� ��忡�� child���� ���� ����
			if(parent->left = now) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {  //parent�� NULL�̸� root ����� ���̹Ƿ� ��� ��忡�� root ��� ���� ����
			head->left = NULL;
		}

		free(now);  //��� �޸� ��ȯ
		return 0;
	}

	/* ������ ��尡 1���� �ڽ� ��带 ������ �� */
	if(now->left == NULL || now->right == NULL) {

		Node* child;  //������ ����� �θ� ���� �����ų ������ ����� �ڽ� ��带 child�� ����
		if(now->left != NULL) {  //�����̳� �����ʿ� �����ϴ� �ڽ� ��带 child�� ����
			child = now->left;
		}
		else {
			child = now->right;
		}

		if(parent != NULL) {
			if(parent->left == now) {  //���� ������ ��尡 �θ� ����� ���� �ڽ��̾�����
				parent->left = child;  //������ child ��带 �θ� ����� ���� �ڽ����� ����
			}
			else {  //�ݴ�� ���������� ����
				parent->right = child;
			}
		}
		else {  //�θ� ��尡 NULL�̸� root ����̹Ƿ� child ��带 root ���� ����
			root = child;
		}

		free(now);  //��� �޸� ��ȯ
		return 0;
	}

	/* ������ ��尡 2���� �ڽ� ��带 ������ �� */
	if(now->left != NULL && now->right != NULL) {

		Node* child = now->right;  //���� ����� ������ �ڽ� ���
		parent = now;  //�θ� ��带 ���� ����

		while(child->left != NULL) {  //�ڽ� ����� ���� �ڽ� ��尡 NULL�� �Ǳ� ������
			parent = child;  //�θ� ��� ��ġ�� �ű�� ���� �ڽ� ���� Ʈ�� �̵�
			child = child->left;
		}

		if(parent->right == child) {  //�θ� ����� ������ �ڽ� ��尡 child�� �Ǹ�
			parent->right = child->right;  //�θ� ����� ������ ��带 child�� ������ �ڽ� ����
		}
		else {  //�ݴ��� ��� ���� ��带 child�� ������ �ڽ� ����
			parent->left = child->right;
		}

		now->key = child->key;  //now�� key�� child�� key�� �ٲ� ��

		free(child);  //child �޸� ��ȯ
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
	if(top < 0) {  //������ ��������� NULL�� ����
		return NULL;
	}

	return stack[top--];  //pop�� �ؼ� ������ top ���� ���δ�
}

void push(Node* aNode)
{
	stack[++top] = aNode;  //aNode�� ������ top�� 1 ���� ���� �ִ´�
}



Node* deQueue()
{
	if(front == rear) {  //ť�� ��������� NULL ��ȯ
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;  //front�� �� ĭ �̵���Ű��
	return queue[front];  //ť�� front ��ȯ
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;  //rear�� �� ĭ �̵�
	if(front == rear) {  //���� ť�� �� �������� ����
		return;
	}

	queue[rear] = aNode;   //ť�� rear�� aNode�� �ִ´�
}




