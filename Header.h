struct user {
	char username[20];
	char password[4];
	char telnumber[12];
	long int unique;
	double leftmoney;
	int operation_quantity;
	struct user *next;
	struct operation *next_oper;
};
struct operation
{
	double amount;
	char kind_of_operation[40];
	struct operation *next_op;
};
int add_user(double amount, int operation, char *name, char *pass, char *telnum, struct user**head);
int userfunc(char*name, char*pass, struct user**head);
int check_which_command_function(char inputcommand[40]);
int delete_user(char*name, struct user**head);
int view(char*name, struct user**head);
void login(struct user**head);
int adminfunc(struct user**head, char*pass);
int deposit(char *name, struct user **head, double amount);
int withdraw(char *name, struct user**head, double amount);
int transfer(char *recievename, char*sendername, struct user **head, double amount);
int save_all(struct user **head);
int recovery(struct user ** head);