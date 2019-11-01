/*2015253037 고휘찬*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node *type_ptr;
typedef struct node{
	char name[50]; // for name of a student
	int st_no; // student number
	float gpa; //  grade point
	char  phone[20]; // phone number
	char  province[30]; // the province of the student
	type_ptr link;
} NODE;
type_ptr search_ins_position(type_ptr node, char str[]);
type_ptr search_prev_delete(type_ptr head, char *dname, int *ptr_found);

int main(void){
	char str[50], call[20], country[30];
	char str1[50], str2[50];
	int num, res, found;
	float grade;
	char command[50];
	type_ptr head, np, prev;
	FILE *fp;
	fp = fopen("student.txt", "r");
	head = NULL;
	while (1){
		res = fscanf(fp, "%s  %d  %f  %s  %s", str, &num, &grade, call, country);
		if (res < 5)
			break;
		np = (type_ptr)malloc(sizeof(struct node));
		strcpy(np->name, str);
		np->st_no = num;
		np->gpa = grade;
		strcpy(np->phone, call);
		strcpy(np->province, country);

		if (!head){
			head = np;
			np->link = NULL;
		}
		else{
			prev = search_ins_position(head, str);
			if (!prev){
				np->link = head;
				head = np;
			}
			else{
				np->link = prev->link;
				prev->link = np;
			}
		}
	}
	np = head;
	while (np != NULL){
		printf("%s  %d  %f  %s  %s\n", np->name, np->st_no, np->gpa, np->phone, np->province);
		np = np->link;
	}
	printf("\n");
	while (1){
		//* 커맨드 입력 시작*//
		printf("Type command> ");
		scanf("%s", command);

		if (strcmp(command, "IN") == 0){
			scanf("%s  %d  %f  %s  %s", str, &num, &grade, call, country);
			printf("재정렬\n");
			np = (type_ptr)malloc(sizeof(struct node));
			strcpy(np->name, str);
			np->st_no = num;
			np->gpa = grade;
			strcpy(np->phone, call);
			strcpy(np->province, country);
			prev = search_ins_position(head, str);
			if (!prev){
				np->link = head;
				head = np;
			}
			else{
				np->link = prev->link;
				prev->link = np;
			}
		}

		else if (strcmp(command, "PP") == 0){
			scanf("%s %s", str1, str2);
			np = head;
			while (strcmp(np->name, str1) != 0)
				np = np->link;
			np = np->link;
			while (strcmp(np->name, str2) != 0){
				printf("%s  %d  %f  %s  %s\n", np->name, np->st_no, np->gpa, np->phone, np->province);
				np = np->link;
			}
		}

		else if (strcmp(command, "DE") == 0){
			scanf("%s", str);
			found = 0;
			prev = search_prev_delete(head, str, &found);
			if (!found)
				printf("Person %s does not exist.", str);
			else if (!prev){
				np = head;
				head = head->link;
				free(np);
			}
			else{
				np = prev->link;
				prev->link = np->link;
				free(np);
			}
			printf("\n");
		}

		else if (strcmp(command, "PT") == 0){
			scanf("%s", str);
			np = head;
			while (np != NULL){
				if (str[0] == np->phone[0] && str[1] == np->phone[1] && str[2] == np->phone[2])
					printf("%s  %d  %f  %s  %s\n", np->name, np->st_no, np->gpa, np->phone, np->province);
				np = np->link;
			}
			printf("\n");
		}

		else if (strcmp(command, "PA") == 0){
			np = head;
			while (np != NULL){
				printf("%s  %d  %f  %s  %s\n", np->name, np->st_no, np->gpa, np->phone, np->province);
				np = np->link;
			}
			printf("\n");
		}

		else if (strcmp(command, "EX") == 0)
			break;

		else
			printf("WRONG COMMAND\n\n");

	}
	fclose(fp);
	return 0;
}
type_ptr search_ins_position(type_ptr node, char str[]){
	if (strcmp(str, node->name)<0){
		return 0;
	}
	else{
		while (strcmp(str, node->name) >= 0 && node->link != NULL){
			if (strcmp(str, node->link->name)<0)
				break;
			node = node->link;
		}
		return node;
	}
}

type_ptr search_prev_delete(type_ptr head, char *dname, int *ptr_found){
	type_ptr prev, curr;
	curr = head;
	prev = NULL;
	while (curr != NULL){
		if (strcmp(curr->name, dname) == 0){
			*ptr_found = 1;
			return prev;
		}
		else{
			prev = curr;
			curr = curr->link;
		}
	}
	*ptr_found = 0;
	return NULL;
}