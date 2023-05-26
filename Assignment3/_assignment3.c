#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

void addNode(listPointer *rear, int data)
{
	listPointer tmp;

	tmp = (listPointer)malloc(sizeof(listNode));
	tmp->data = data;
	tmp->link = (*rear)->link;
	(*rear)->link = tmp;
	*rear = tmp;
}

listPointer get_prev_node_by_data(listPointer rear, int target_data)
{
	listPointer tmp;

	tmp = rear->link;
	while (tmp->link->data != -1)
	{
		if (tmp->link->data == target_data)
			return (tmp);
		tmp = tmp->link;
	}
	return (0);
}

void cearse(listPointer *rear, listPointer front_of_target)
{
	listPointer target;

	if (front_of_target)
	{
		target = front_of_target->link;
		front_of_target->link = target->link;
		if (target->link->data == -1)
			*rear = front_of_target;
		if (target->data != -1)
			free(target);
	}
}

int main()
{
	listPointer rear, tmp;
	rear = (listPointer)malloc(sizeof(listNode));
	rear->data = -1;
	rear->link = rear;

	addNode(&rear, 10);
	addNode(&rear, 20);
	addNode(&rear, 30);
	addNode(&rear, 40);

	//printf("%p\n", getNode_by_data(rear, 20));
	cearse(&rear, get_prev_node_by_data(rear, 10));
	//cearse(&rear, get_prev_node_by_data(rear, 20));
	cearse(&rear, get_prev_node_by_data(rear, 30));
	//printf("%d & %d\n", get_prev_node_by_data(rear, 40)->data, get_prev_node_by_data(rear, 40)->link->link->data);
	cearse(&rear, get_prev_node_by_data(rear, 40));
	printf("rear:%d and %d\n", rear->data, rear->link->data);

	tmp = rear->link->link;
	while (tmp->data != -1) {
		printf("%d\n", tmp->data);
		tmp = tmp->link;
	}
	return 0;
}