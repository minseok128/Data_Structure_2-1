#define _CRT_SECURE_NO_WARNINGS
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
	int id; // 고객 ID
	Job job_data; // 고객이 원하는 작업 유형
	listPointer link; // 다음 노드를 가리키는 링크
} listNode;

void		init_system();
void		start_system();
void		receive_new_customer();
void		ready_repairman();
void		assign_service();
void		view_state();
char		get_char_job(Job job);
void		attach(listPointer *rear, int num, Job job_data);
listPointer	get_prev_node(listPointer rear, Job target_job);
void		delete(listPointer *rear, listPointer front_of_target);

int			repairman_state[3];
listPointer	rear;

int main()
{
	init_system();
	start_system();	
	return 0;
}

void init_system()
{
	for (int i = 0; i < 3; i++)
		repairman_state[i] = 0;
	rear = (listPointer)malloc(sizeof(listNode)); // Header node 만들기
	rear->job_data = H;
	rear->link = rear;
}

void start_system()
{
	int command = 0;

	while (command != 5)
	{
		printf("\n┌──────────────────────────────────────────");
		printf("──────────────────────────────────────────┐\n");
		printf("├ 1: 신규 고객 접수 │ 2: 기사 준비 │ 3: 서비스 배당 │ 4: 현황 확인 │ 5: 종료\n");
		printf("┼ Enter your command(1~5) >> ");
		scanf("%d", &command);
		printf("┼\n");

		if (command == 1)
			receive_new_customer();
		else if (command == 2)
			ready_repairman();
		else if (command == 3)
			assign_service();
		else if (command == 4)
			view_state();
		else if (command == 5)
			printf("├ 서비스를 종료합니다.\n");
		else
			printf("├ 잘못된 입력입니다.\n");

		printf("└──────────────────────────────────────────");
		printf("──────────────────────────────────────────┘\n");
	}
}

void receive_new_customer()
{
	int id;
	char job;

	printf("┼ 신규 고객의 ID를 입력하세요(숫자) >> ");
	scanf("%d", &id);
	printf("┼ ID:%d 고객이 원하는 작업을 입력하세요(A, B, C) >> ", id);
	scanf(" %c", &job);
	if (job == 'A' || job == 'B' || job == 'C')
	{
		attach(&rear, id, job - 'A');
		printf("├ ID:%d 고객의 %c 작업이 예약 되었습니다.\n", id, job);
		view_state();
	}
	else
		printf("├ 잘못된 입력입니다.\n");
}

void ready_repairman()
{
	char repairman_kind;

	printf("┼ 준비 상태로 변환할 기사의 번호를 입력하세요(A, B, C) >> ");
	scanf(" %c", &repairman_kind);
	if (repairman_kind >= 'A' && repairman_kind <= 'C')
	{
		if (!repairman_state[repairman_kind - 'A'])
		{
			repairman_state[repairman_kind - 'A'] = 1;
			printf("├ %c 기사가 준비 상태로 변환되었습니다.\n", repairman_kind);
			view_state();
		}
		else
			printf("├ 이미 준비 상태입니다.\n");
	}
	else
		printf("├ 잘못된 입력입니다.\n");
}

void assign_service()
{
	listPointer tmp;

	for (int i = 0; i < 3; i++)
	{
		
		if (repairman_state[i] == 1)
		{
			tmp = get_prev_node(rear, i);
			if (tmp)
			{
				repairman_state[i] = 0;
				printf("├ %c 기사가 ID:%d 고객의 서비스를 수행합니다.\n", \
					get_char_job(i), tmp->link->id);
				delete(&rear, tmp);
			}
			else
				printf("├ %c 기사는 준비되었지만, 해당 작업을 원하는 고객이 없습니다.\n", \
					get_char_job(i));
		}
		else
			printf("├ %c 기사는 준비되지 않았습니다.\n", get_char_job(i));
	}
	view_state();
}

void view_state()
{
	listPointer tmp;

	printf("│\n├ ");
	for (int i = 0; i < 3; i++)
	{
		if (repairman_state[i] == 1)
			printf("%c 기사: 준비 ", get_char_job(i));
		else
			printf("%c 기사: 준비되지 않음 ", get_char_job(i));
		if (i != 2)
			printf("│ ");
	}
	printf("\n");
	tmp = rear->link->link;
	while (tmp->job_data != -1)
	{
		printf("├ ID:%-11d 고객: %c\n", tmp->id, get_char_job(tmp->job_data));
		tmp = tmp->link;
	}
}

char get_char_job(Job job)
{
	switch (job)
	{
		case A: return ('A');
		case B: return ('B');
		case C: return ('C');
		default: return ('H');
	}
}

/* 헤더가 있는 원형 연결 리스트 관련 함수들 */
void attach(listPointer *rear, int num, Job job_data)
{
	listPointer tmp;

	tmp = (listPointer)malloc(sizeof(listNode));
	tmp->job_data = job_data;
	tmp->id = num;
	tmp->link = (*rear)->link;
	(*rear)->link = tmp;
	*rear = tmp;
}

listPointer get_prev_node(listPointer rear, Job target_job)
{
	listPointer tmp;

	tmp = rear->link;
	while (tmp->link->job_data != -1)
	{
		if (tmp->link->job_data == target_job)
			return (tmp);
		tmp = tmp->link;
	}
	return (0);
}

void delete(listPointer *rear, listPointer front_of_target)
{
	listPointer target;

	if (front_of_target)
	{
		target = front_of_target->link;
		front_of_target->link = target->link;
		if (target->link->job_data == H)
			*rear = front_of_target;
		if (target->job_data != H)
			free(target);
	}
}
