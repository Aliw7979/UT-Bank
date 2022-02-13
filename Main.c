#include "Header.h"
#include<stdio.h>
int main() {
	
	struct user *head = NULL;
	recovery(&head); //recovery for accounts
	login(&head); //going for login
	return 0;
}
