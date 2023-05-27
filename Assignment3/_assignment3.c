#include <stdio.h>
#include <stdlib.h>

typedef enum _Job {
	H = -1,
	A = 0,
	B = 1,
	C = 2
} Job;

typedef struct listNode *listPointer;
typedef struct listNode {
	Job data;
	listPointer link;
} listNode;

char get_char_job(Job job)
{
	switch (job)
	{
		case A:
			return 'A';
		case B:
			return 'B';
		case C:
			return 'C';
		default:
			return 'H';
	}
}

void addNode(listPointer *rear, Job data)
{
	listPointer tmp;

	tmp = (listPointer)malloc(sizeof(listNode));
	tmp->data = data;
	tmp->link = (*rear)->link;
	(*rear)->link = tmp;
	*rear = tmp;
}

listPointer get_prev_node_by_data(listPointer rear, Job target_data)
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
		if (target->link->data == H)
			*rear = front_of_target;
		if (target->data != H)
			free(target);
	}
}

int main()
{
	listPointer rear, tmp;
	rear = (listPointer)malloc(sizeof(listNode));
	rear->data = H;
	rear->link = rear;

	addNode(&rear, A);
	addNode(&rear, B);
	addNode(&rear, B);
	addNode(&rear, B);
	addNode(&rear, C);
	addNode(&rear, C);
	addNode(&rear, C);
	addNode(&rear, B);
	addNode(&rear, C);
	addNode(&rear, C);
	addNode(&rear, A);

	//printf("%p\n", getNode_by_data(rear, 20));
	cearse(&rear, get_prev_node_by_data(rear, A));
	//cearse(&rear, get_prev_node_by_data(rear, 20));
	cearse(&rear, get_prev_node_by_data(rear, B));
	//printf("%d & %d\n", get_prev_node_by_data(rear, 40)->data, get_prev_node_by_data(rear, 40)->link->link->data);
	cearse(&rear, get_prev_node_by_data(rear, C));
	printf("rear:%c and %c\n", get_char_job(rear->data), get_char_job(rear->link->data));

	tmp = rear->link->link;
	while (tmp->data != -1) {
		printf("%c\n", get_char_job(tmp->data));
		tmp = tmp->link;
	}
	return 0;
}