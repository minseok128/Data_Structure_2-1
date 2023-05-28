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
	int num;
	Job data;
	listPointer link;
} listNode;

char get_char_job(Job job)
{
	switch (job)
	{
		case A:
			return ('A');
		case B:
			return ('B');
		case C:
			return ('C');
		default:
			return ('H');
	}
}

void addNode(listPointer *rear, int num, Job data)
{
	listPointer tmp;

	tmp = (listPointer)malloc(sizeof(listNode));
	tmp->data = data;
	tmp->num = num;
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

void start_system()
{
	int command, num = 1;
	int repairman_state[3] = {1, 1, 1};
	listPointer rear, tmp;

	rear = (listPointer)malloc(sizeof(listNode));
	rear->data = H;
	rear->link = rear;

	while (1)
	{
		printf("\n1: 신규 고객 접수, 2: 기사 준비, 3: 고객 서비스 배당, 4: 고객 리스트 확인, 5: 종료\n");
		printf("Enter your command(1~4) >> ");
		scanf("%d", &command);

		if (command == 1)
		{
			char job;

			printf("%d번째 고객이 원하는 작업을 입력하세요(A, B, C) >> ", num);
			scanf(" %c", &job);
			if (job == 'A' || job == 'B' || job == 'C')
				addNode(&rear, num++, job - 'A');
			else
				printf("잘못된 입력입니다.\n");
		}
		else if (command == 2)
		{
			char repairman_kind;

			printf("준비 상태로 변환할 기사의 번호를 입력하세요(A, B, C) >> ");
			scanf(" %c", &repairman_kind);
			if (repairman_kind >= 'A' && repairman_kind <= 'C')
			{
				if (repairman_state[repairman_kind - 'A'] == 1)
				{
					repairman_state[repairman_kind - 'A'] = 1;
					printf("%c 기사가 준비 상태로 변환되었습니다.\n", repairman_kind);
				}
				else
					printf("이미 준비 상태입니다.\n");
			}
			else
				printf("잘못된 입력입니다.\n");
		}
		else if (command == 3)
		{
			listPointer tmp;

			for (int i = 0; i < 3; i++)
			{
				
				if (repairman_state[i] == 1)
				{
					tmp = get_prev_node_by_data(rear, i);
					if (tmp)
					{
						repairman_state[i] = 0;
						printf("%c 담당 기사가 %d번째 고객의 서비스를 수행합니다.\n", get_char_job(i), tmp->link->num);
						cearse(&rear, tmp);
					}
					else
						printf("%c 담당 기사는 준비되었지만, 해당 작업을 원하는 고객이 없습니다.\n", get_char_job(i));
				}
				else
					printf("%c 담당 기사는 준비되지 않았습니다.\n", get_char_job(i));
			}
		}
		else if (command == 4)
		{
			listPointer tmp;

			tmp = rear->link->link;
			while (tmp->data != -1) {
				printf("%d번째 고객:%c\n", tmp->num, get_char_job(tmp->data));
				tmp = tmp->link;
			}
		}
		else if (command == 5)
		{
			printf("서비스를 종료합니다.\n");
			break;
		}
		else
		{
			printf("잘못된 입력입니다.\n");
		}
	}
}

int main()
{
	start_system();	
	return 0;
}