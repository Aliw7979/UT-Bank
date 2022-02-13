#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Header.h"
int check_which_command_function(char inputcommand[40]) { // this function is for deciding between commands and return number for each command
	if (strcmp(inputcommand, "add_user") == 0) {
		return 1;
	}
	else if (strcmp(inputcommand, "deposit") == 0) {
		return 2;
	}
	else if (strcmp(inputcommand, "withdraw") == 0) {
		return 3;
	}
	else if (strcmp(inputcommand, "view") == 0) {
		return 4;
	}
	else if (strcmp(inputcommand, "delete") == 0) {
		return 5;
	}
	else if (strcmp(inputcommand, "transfer") == 0) {
		return 6;
	}
	else if (strcmp(inputcommand, "login") == 0) {
		return 7;
	}
	else if (strcmp(inputcommand, "logout") == 0) {
		return 8;
	}
	else if (strcmp(inputcommand, "exit") == 0) {
		return 9;
	}
	printf("command not found\n");
	return -1;
}
int add_user(double amount, int operation, char *name, char *pass, char *telnum, struct user**head) {
	struct user *current = (*head);
	for (int i = 0; current != NULL; i++) {
		if (strcmp(current->username, name) == 0) {//check for unique id
			printf("Oops! duplicate account\n");
			return 0;
		}
		current = current->next;
	}
	current = (*head);
	for (int i = 0; current != NULL; i++) {
		if (strcmp(current->telnumber, telnum) == 0) {//check for unique tel number
			printf("Oops! tel number duplicate \n");
			return 0;
		}
		current = current->next;
	}
	struct user*new_user = (struct user*)malloc(sizeof(struct user));//create space for new member
	new_user->next = (*head);
	strcpy(new_user->username, name);
	strcpy(new_user->password, pass);
	strcpy(new_user->telnumber, telnum);
	new_user->unique = rand() % 1000;
	new_user->leftmoney = amount;
	new_user->operation_quantity = operation;
	new_user->next_oper = NULL;
	(*head) = new_user;
	printf("User that you mentioned has created successfully my admin\n");
	return 1;
}
int view(char*name, struct user**head) {
	struct user *current = (*head);
	struct operation *current_operation;
	int i = 0;
	for (i; current != NULL; i++) {
		if (strcmp(current->username, name) == 0) {
			printf("user has found\n");
			printf("%s\n", current->username);
			printf("%s\n", current->telnumber);
			printf("Amount of money=%lf\n", current->leftmoney);
			printf("Quantity of operations=%d\n", current->operation_quantity);
			if (current->operation_quantity > 0) {
				current_operation = current->next_oper;
				for (i = 0; current_operation != NULL; i++) {
					printf("amount=%lf kind=%s\n", current_operation->amount, current_operation->kind_of_operation);
					current_operation = current_operation->next_op;
				}
			}
			return 1;
		}
		current = current->next;
	}
	printf("user not found\n");
	return 0;

}
int delete_user(char*name, struct user**head) {
	struct user *current = (*head);
	struct user *before;
	struct operation *current_operation;
	struct operation *after_operation;
	int i = 0;
	for (i; current != NULL; i++) {
		if (strcmp(current->username, name) == 0) {
			if (i == 0) {
				(*head) = current->next;
			}
			else {
				before->next = current->next;
			}
			current_operation = current->next_oper;
			for (i = 0; current_operation != NULL; i++) {
				after_operation = current_operation->next_op;
				free(current_operation);//free every operation
				current_operation = after_operation;

			}
			free(current);//free the member and delete it
			printf("User deleted successfully\n");
			return 1;
		}
		else {
			before = current;
			current = current->next;
		}
	}
	printf("User not found\n");
	return 0;
}
int deposit(char *name, struct user **head, double amount) {
	struct user *current = (*head);
	int i = 0;
	for (i; current != NULL; i++) {
		if (strcmp(current->username, name) == 0) {
			current->leftmoney += amount;
			current->operation_quantity += 1;
			struct operation *new_operation = (struct operation*)malloc(sizeof(struct operation));
			new_operation->amount = amount;
			strcpy(new_operation->kind_of_operation, "deposited");
			new_operation->next_op = current->next_oper;
			current->next_oper = new_operation;
			printf("operation was successfull\n");
			return 1;
		}
		else
			current = current->next;
	}
	printf("user not found\n");
	return 0;
}
int withdraw(char *name, struct user**head, double amount) {
	struct user *current = (*head);
	int i = 0;
	for (i; current != NULL; i++) {
		if (strcmp(current->username, name) == 0) {
			if (current->leftmoney < amount) {//check if user has enough money to withdraw or not
				printf("user doesnt enough money\n");
				break;
			}
			current->leftmoney -= amount;
			current->operation_quantity += 1;
			struct operation *new_operation = (struct operation*)malloc(sizeof(struct operation));
			new_operation->amount = amount;
			strcpy(new_operation->kind_of_operation, "withdraw");
			new_operation->next_op = current->next_oper;
			current->next_oper = new_operation;
			printf("operation was successfull\n");
			return 1;
		}
		else
			current = current->next;
	}
	printf("user not found\n");
	return 0;
}
int transfer(char *recievename, char*sendername, struct user **head, double amount) {
	struct user *current = (*head);
	int i = 0;
	for (i; current != NULL; i++) {
		if (strcmp(current->username, sendername) == 0) {
			if (current->leftmoney < amount) {
				printf("you dont have enough money\n");
				return 0;
			}
			else           //first of all we have to withdraw money from sender
			{
				current->leftmoney -= amount;
				current->operation_quantity += 1;
				struct operation *new_operation = (struct operation*)malloc(sizeof(struct operation));
				new_operation->amount = amount;
				strcpy(new_operation->kind_of_operation, "transfer(send)");
				new_operation->next_op = current->next_oper;
				current->next_oper = new_operation;
				break;
			}
		}
		else
		{
			current = current->next;
		}
	}
	if (current == NULL) {
		printf("sender not found\n");
		return 0;
	}
	current = (*head);
	i = 0;                         //then give it to reciever
	for (i; current != NULL; i++) {
		if (strcmp(current->username, recievename) == 0) {
			current->leftmoney += amount;
			current->operation_quantity += 1;
			struct operation *new_operation = (struct operation*)malloc(sizeof(struct operation));
			new_operation->amount = amount;
			strcpy(new_operation->kind_of_operation, "transfer(recieve)");
			new_operation->next_op = current->next_oper;
			current->next_oper = new_operation;
			printf("operation was successfull\n");
			return 1;
		}
		else
		{
			current = current->next;
		}
	}
	printf("user not found\n");
	return 0;

}
int adminfunc(struct user**head, char*pass) {
	if (strcmp(pass, "123") != 0)//admin password
	{
		printf("My admin,I think you forgot your password\n");
		return 0;
	}
	else
		printf("Thank you sir , now you logged in\n");
	char command[40];

	char name[20];
	char telnum[12];

	double amount;

	while (1)
	{
		printf("nice! Now it is our honor to obey your commands\n");
		scanf("%s", command);

		int checkcommand = check_which_command_function(command);//a function for checking commands
		if (checkcommand == 1) {
			scanf(" %s %s %s", name, pass, telnum);
			add_user(0, 0, name, pass, telnum, head);
			save_all(head);//save every single change in program
		}
		else if (checkcommand == 2) {
			scanf(" %s %lf", name, &amount);
			deposit(name, head, amount);
			save_all(head);//save every single change in program
		}
		else if (checkcommand == 3) {
			scanf(" %s %lf", name, &amount);
			withdraw(name, head, amount);
			save_all(head);//save every single change in program
		}
		else if (checkcommand == 4) {
			scanf(" %s", name);
			view(name, head);
		}
		else if (checkcommand == 5) {
			scanf(" %s", name);
			delete_user(name, head);
			save_all(head);//save every single change in program
		}

		else if (checkcommand == 8) {
			printf("You logged out\n");
			return 0;
		}
		else if (checkcommand == 9) {
			printf("farewell...\n");
			exit(0);
		}

	}
}
int userfunc(char*name, char*pass, struct user**head) {
	char command[40];
	double amount;
	char recname[20];

	struct user *current = (*head);
	for (int i = 0; current != NULL; i++) {
		if (strcmp(current->username, name) == 0) {
			if (strcmp(current->password, pass) == 0) {
				break;
			}
			else {
				printf("password is wrong , try again\n");
				return 0;
			}
		}
		else {
			current = current->next;
			continue;
		}
	}
	if (current == NULL) {
		printf("user not found\n");
		return 0;
	}
	printf("welcome sir you what you want\n");
	while (1) {
		scanf("%s", command);
		int checkcommand = check_which_command_function(command);//check for commands
		if (checkcommand == 1) {
			printf("access denied!\n");
		}
		else if (checkcommand == 2) {
			scanf(" %lf", &amount);
			deposit(name, head, amount);
			save_all(head);
		}
		else if (checkcommand == 3) {
			scanf(" %lf", &amount);
			withdraw(name, head, amount);
			save_all(head);
		}
		else if (checkcommand == 4) {
			printf("you can just see yourself sir\n");
			view(name, head);
		}
		else if (checkcommand == 5) {
			printf("access denied!\n");
		}
		else if (checkcommand == 6) {
			scanf(" %s %lf", recname, &amount);
			transfer(recname, name, head, amount);
			save_all(head);
		}
		else if (checkcommand == 8) {
			printf("You logged out\n");
			return 0;
		}
		else if (checkcommand == 9) {
			printf("farewell...\n");
			exit(0);
		}

	}

}
void login(struct user**head) {
	char who[10];
	char command[10];
	char pass[4];
	char check[] = "admin"; //it is for check to decide between user and admin
	printf("\t\t\t\t\t\t Welcome to the UT Bank\n");
	printf("first of all you have to say who you are :D\n");
	while (1)
	{
		scanf("%s", command);
		if (check_which_command_function(command) == 7) {// if it was admin continue
			scanf(" %s %s", who, pass);
			if (strcmp(check, who) == 0) {
				adminfunc(head, pass);
			}
			else
				userfunc(who, pass, head);//else it is user
		}
		else {
			continue;
		}
	}
}
int save_all(struct user **head) {
	struct user* current = (*head);

	FILE * fp;
	int i;
	/* open the file for writing*/
	fp = fopen("save.txt", "w");

	/* write 10 lines of text into the file stream*/
	for (i = 0; current != NULL; i++) {
		fprintf(fp, "%s\n", current->username);
		fprintf(fp, "%lf\n", current->leftmoney);
		fprintf(fp, "%s\n", current->telnumber);
		fprintf(fp, "%d\n", current->operation_quantity);
		fprintf(fp, "%s\n", current->password);
		current = current->next;
	}

	/* close the file*/
	fclose(fp);
	return 0;
}
int recovery(struct user ** head) {
	FILE* ptr = fopen("save.txt", "r");
	int count = 0;
	char c;
	char pass[40];
	char name[20];
	char telnum[30];
	char quantity[20];
	char money[40];
	if (ptr == NULL) {
		return 0;
	}
	for (c = getc(ptr); c != EOF; c = getc(ptr)) {
		if (c == '\n') { // Increment count if this character is newline 
			count = count + 1;
		}
	}
	fclose(ptr);
	ptr = fopen("save.txt", "r");
	int counter = count / 5;
	int i = 0;
	while (i<counter) {
		i++;
		fscanf(ptr, "%s", name);
		fscanf(ptr, "%s", money);
		fscanf(ptr, "%s", telnum);
		fscanf(ptr, "%s", quantity);
		fscanf(ptr, "%s", pass);
		double left = atof(money);
		int ope = atoi(quantity);
		add_user(left, ope, name, pass, telnum, head);
	}
	printf("accounts recovered\n");
	fclose(ptr);
	return 1;
}