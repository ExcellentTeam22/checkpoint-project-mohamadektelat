#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

struct contact{
	char fname[31];
	char lname[31];
	char telep[15];
	char cellp[15];
	struct contact * _next_fname;
	struct contact * _next_lname;
	struct contact * _next_telep;
	struct contact * _next_cellp;
};

#define TOTAL_CONTACTS 1000
struct contact A[TOTAL_CONTACTS];
struct contact * root = NULL;
int counter = 0;

void clrscr(void);
bool if_exists_by_fname(char* fname);
bool if_exists_by_lname(char* lname);
bool if_exists_by_phonenumber(char* phoneNumber);
bool if_exists_by_cellularenumber(char* cellulareNumber);
void gotoxy(int x, int y);
void insert(void);
void insert_from_file(void);
void delet(void);
void edit(void);
void search(void);
void searchf(void);
void searchl(void);
void searchp(void);
void searchc(void);
void list(void);
void list2(void);
void sort(void);
void sortf(void);
void sortl(void);
void sortp(void);
void sortc(void);
void help(void);
int last;

int main()
{
	int count=1;
	char n;
	while(count) {
	clrscr();
	printf("\n|Phone Book12<::>Home|\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Welcome to PHONE BOOK2022!\nYou have inserted ( %d ) contacts.\n\n",last);
	printf("\t[1] |--> Insert\n");
	printf("\t[2] |--> Insert from File\n");
	printf("\t[3] |--> Delete\n");
	printf("\t[4] |--> Edit\n");
	printf("\t[5] |--> Search\n");
	printf("\t[6] |--> Show All\n");
	printf("\t[7] |--> Sort\n");
	printf("\t[8] |--> Help\n");
	printf("\t[9] |--> Exit\n");
	printf("\n\tPlease Enter Your Choice (1-8): ");
	n = getc(stdin);
	getc(stdin);
	 switch(n) {
		  case '1':
		  insert();
		  break;
		  case '2':
		  insert_from_file();
		  break;
		  case '3':
		  delet();
		  break;
		  case '4':
		  edit();
		  break;
		  case '5':
		  search();
		  break;
		  case '6':
		  list();
		  break;
		  case '7':
		  sort();
		  break;
		  case '8':
		  help();
		  break;
		  case '9':
		  exit(1);
		  break;
		  default:
		  printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-8!\nPress any key to continue...",n);
		  getc(stdin);
	      getc(stdin);
		  break;
	  }//End of swicth
	}
	exit(0);
}//End of main function!


struct contact * create_node(char * fname, char * lname, char * telep, char * cellp){
	struct contact * temp; // declare a node
    	temp = (struct contact*)malloc(sizeof(struct contact)); // allocate memory using malloc()
    	strncpy(temp->fname, fname, 31);
    	strncpy(temp->lname, lname, 31);
    	strncpy(temp->telep, telep, 15);
    	strncpy(temp->cellp, cellp, 15);
    	temp->_next_fname = NULL;// make next point to NULL
    	return temp;//return the new node
}

int get_input(char * dest, int max_size){
	size_t input_size = 0;
	size_t len = max_size;
	char * input = NULL;
	input = (char *)malloc(len * sizeof(char));
	input_size = getline(&input, &len, stdin);
	if(input[input_size - 1] == '\n'){
		input[input_size - 1] = '\0';
		input_size --;
	}
	if(input_size >= max_size){
		input[max_size -1] = '\0';
	}
	strcpy(dest, input);
	free(input);

}

void insert_from_file(void){

	FILE *fp;
	char * ch;
	char * line = NULL;
	size_t len;
	size_t len_size;
	char fname[31];
	char lname[31];
	char telep[15];
	char cellp[15];
   	fp = fopen("/home/mohamad/phonbook-students/phonebookFile", "r");
   	if (fp == NULL) {
        	printf("file can't be opened \n");
    	}
    	int counter = 0;
	// Use a while loop together with the getline() function to read the file line by line

	while ((len_size = getline(&line, &len, fp)) != -1) {
        	ch = strtok (line,"\t") ;
        	strcpy(fname, ch);
        	ch = strtok (NULL, "\t");
        	strcpy(lname, ch);
        	ch = strtok (NULL, "\t");
        	strcpy(telep, ch);
        	ch = strtok (NULL, "\t");
        	strcpy(cellp, ch);
        	struct contact * temp = NULL,*p=NULL;// declare two nodes temp and p
    		temp = create_node(fname, lname, telep, cellp);//createNode will return a new node with data = value and next pointing to NULL.
    		if(root == NULL){
    		    	root = temp;     //when linked list is empty
    		}
    		else{
        		p  = root;//assign head to p
        		while(p->_next_fname != NULL){
            			p = p->_next_fname;//traverse the list until p is the last node.The last node always points to NULL.
        		}
        		p->_next_fname = temp;//Point the previous last node to the new node created.
    		}
        	last++;
    	}
	fclose(fp);
}

void insert(void)
{
	char ans='y';
	int counter = 0;
	clrscr();
	char fname[31];
	char lname[31];
	char telep[15];
	char cellp[15];
    printf("\nPhone Book12<::>Insert Contacts");
    printf("\n--------------------------------------------------------------------------------");
	while(ans=='y'){
		printf("\n\nData of Contact %2.2d{\n",last+1);
		printf("\n\t  1-F.Name: ");
		get_input(fname, 31);


		printf("\t  2-L.Name: ");
		get_input(lname, 31);

		printf("\t  3-Tele.P: ");
		get_input(telep, 15);

		printf("\t  4-Cell.P: ");
		get_input(cellp, 15);

			//if((if_exists_by_fname(A[last].fname) && if_exists_by_lname(A[last].lname)) || (if_exists_by_phonenumber(A[last].telep)) || (if_exists_by_phonenumber(A[last].cellp))){
			//	printf("please make sure that you enter deffirent name or number!!");
			//	A[last] = B[0];
			//	break;
			//}
		struct contact * temp = NULL,*p=NULL;// declare two nodes temp and p
    		temp = create_node(fname, lname, telep, cellp);//createNode will return a new node with data = value and next pointing to NULL.
    		if(root == NULL){
    		    	root = temp;     //when linked list is empty
    		}
    		else{
        		p  = root;//assign head to p
        		while(p->_next_fname != NULL){
            			p = p->_next_fname;//traverse the list until p is the last node.The last node always points to NULL.
        		}
        		p->_next_fname = temp;//Point the previous last node to the new node created.
    		}

		printf("\n|-->Data Recorded!}");
		printf("\n\t\t\tNext Contact?(y/n) Answer:");
		ans = getc(stdin);
		getc(stdin);
		last++;
		counter ++;
	}
	printf("\n\nYou have inserted ( %d ) contact!\nPress a key to return main page & continue program|-->",last);
	getc(stdin);
}

bool if_exists_by_fname(char* fname){
for (int i = 0; i < last; i++) {
	if (strcmp (fname, A[i].fname) == 0)
		return true;
	}
	return false;
}
bool if_exists_by_lname(char* lname){
for (int i = 0; i < last; i++) {
	if (strcmp (lname, A[i].lname) == 0)
		return true;
	}
	return false;
}
bool if_exists_by_phonenumber(char* phoneNumber){
for (int i = 0; i < last; i++) {
	if (strcmp (phoneNumber,A[i].telep) == 0)
		return true;
	}
	return false;
}
bool if_exists_by_cellularenumber(char* cellulareNumber){
for (int i = 0; i < last; i++) {
	if (strcmp (cellulareNumber,A[i].cellp) == 0)
		return true;
	}
	return false;
}

void delet(void)
{
	char dfname_string[31],dlname_string[31];
	char *input = NULL;
	size_t len=0;
	size_t len_size=0;
	register int i,j,find=0;
	char ch;
	clrscr();
    printf("\nPhone Book12<::>Delete Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf ("\n::Enter data of the contact that you want delete it,please:");
	printf("\n\n  ::Enter first name: ");
	get_input(dfname_string, 31);

	printf("\n  ::Enter last name: ");
	get_input(dlname_string, 31);
    struct contact * curr = root;
    struct contact * prev= NULL;
    struct contact * next = NULL;
    while(curr != NULL){
        if(strcmp(dfname_string,curr->fname) == 0 && strcmp(dlname_string,curr->lname) == 0) {
            printf("\nContact was found! Details:");
            printf("\n\nCantact %2.2d{", i + 1);
            printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }", curr->fname, curr->lname,
                   curr->telep, curr->cellp);
            printf("\n\nAre you sure you want to delete this contact?(y/n)");
            ch = getc(stdin);
            getc(stdin);
            if (ch == 'y') {
                if(prev == NULL){
                    next = curr->_next_fname;
                    free(curr);
                    root = next;
                }
                else if(curr->_next_fname == NULL){
                    free(curr);
                    prev->_next_fname = NULL;
                }
                else {
                    next = curr->_next_fname;
                    free (curr);
                    prev->_next_fname = next;
                }
                last--;
                find = 1;
                break;
            }
        }
        prev = curr ;
        curr = curr->_next_fname;
	}
	if (find==0)
		if(ch == 'n'){
		printf("\t\t\n<<Target contact was not deleted from list!>>");
		}
		else{
		printf("\t\t\n<<This contact does not exist in this list or program can not delete it.>>");
		}
	else
		printf("\t\t\n<<Target contact was successfully deleted from list!>>");
	free(input);
	printf("\n\n\nPress a key to return main page & continue program|-->");
	getc(stdin);
}

void edit()
{
	char dfname[31] ,dlname[31];
	size_t len=0;
	size_t len_size=0;
	register int i,j,find=0;
	char ch;
	clrscr();
    printf("\nPhone Book12<::>Edit Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf ("\n::Enter data of the contact that you want edit it,please:");

	printf("\n\n  ::Enter first name: ");
	get_input(dfname, 31);
	printf("\n  ::Enter last name: ");
	get_input(dlname, 31);

	for (i=0; i < last; i++) {
	 if (strcmp (dfname, A[i].fname) == 0 && strcmp (dlname, A[i].lname) == 0 ) {
	 	printf("\nContact found! Details:");
		printf("\n\nCantact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",A[i].fname,A[i].lname,A[i].telep,A[i].cellp);
		printf("\n\nDo you want edit it?(y/n) ");
		ch = getc(stdin);
		getc(stdin);
		if(ch=='y'){
			printf("\n::Enter NEW data for this contact...");
			printf("\n >|Enter new first name: ");
			get_input(A[i].fname, 30);
			printf(" >|Enter new last name: ");
			get_input(A[i].lname, 30);
			printf(" >|Enter new telephone number: ");
			get_input(A[i].telep, 14);
			printf(" >|Enter new cellphone number: ");
			get_input(A[i].cellp, 14);

		   	find=1;
		    break;
		}
	 }
	}
	if (find==0){
		printf("\t\t\n<<This contact does not exist or you chose not to Edit it.>>");
	}
	else
	{
		printf("\t\t\n<<Target contact was successfully updated!>>");
	}
	printf("\n\n\n   ::Press a key to return main page & continue program|-->");
	getc(stdin);
	//free(dfname);
	//free(dlname);
}

void search(void)
{
	char ch;
	clrscr();
    printf("\nPhone Book12<::>$earch Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf("\nChoose search type,please:\n\n");
	printf("\t[1] |--> Search by first name\n");
	printf("\t[2] |--> Search by last name\n");
	printf("\t[3] |--> Search by phone number\n");
	printf("\t[4] |--> Search by cellphone number\n");
	printf("\t[5] |--> Main Menu\n");
	printf("\n\t::Enter a number (1-5): ");
	ch = getc(stdin);
	getc(stdin);
	printf("\n--------------------------------------------------------------------------------");
    switch(ch) {
		case '1':
		searchf();
	    break;
		case '2':
		searchl();
		break;
		case '3':
		searchp();
		break;
		case '4':
		searchc();
		break;
		case '5':
		default:
			return;
    }
}

void searchf(void)
{
	char fname[31];
	register int i,find=0;
	size_t len=0;
	size_t len_size=0;
	printf("Enter a first name to search:");
	get_input(fname, 31);
	struct contact * temp = root;
    //for(i = 0;i < last; i++)
    while(temp != NULL){
		if(strcmp(fname,temp->fname) == 0) {
			find=1;
			break;
		}
		temp = temp->_next_fname;
	}
	if(find==0)
		printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");
	else {
		printf("\t\n<<Target contact found! Details:>>");
		printf("\n\nCantact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
	}
	//free(fname);
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
}

void searchl(void)
{
	char lname[31];
	register int i,find=0;
	size_t len=0;
	size_t len_size=0;
	printf("\n::Enter a last name to search:");
    get_input(lname, 31);
    struct contact * temp = root;
    //for(i = 0;i < last; i++)
    while(temp != NULL){
        if(strcmp(lname,temp->lname) == 0) {
            find=1;
            break;
        }
        temp = temp->_next_fname;
    }
    if(find==0)
        printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");
    else {
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
    }
    //free(fname);
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void searchp(void)
{

	char phone[15];
	int i,find=0;
	size_t len=0;
	size_t len_size=0;
	printf("\n::Enter a phone number to search:");
    get_input(phone, 31);
    struct contact * temp = root;
    //for(i = 0;i < last; i++)
    while(temp != NULL){
        if(strcmp(phone,temp->telep) == 0) {
            find=1;
            break;
        }
        temp = temp->_next_fname;
    }
    if(find==0)
        printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");
    else {
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
    }
    //free(fname);
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void searchc(void)
{

	char phone[15];
	int i,find=0;
	size_t len=0;
	size_t len_size=0;
	printf("\n::Enter a cellphone number to search:");
    get_input(phone, 31);
    struct contact * temp = root;
    //for(i = 0;i < last; i++)
    while(temp != NULL){
        if(strcmp(phone,temp->cellp) == 0) {
            find=1;
            break;
        }
        temp = temp->_next_fname;
    }
    if(find==0)
        printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");
    else {
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
    }
    //free(fname);
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void sort(void)
{
	char ch;
	clrscr();
    printf("\nPhone Book12<::>$earch Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf("\nChoose sort type,please:\n\n");
	printf("\t[1] |--> Sort by first name\n");
	printf("\t[2] |--> Sort by last name\n");
	printf("\t[3] |--> Sort by phone number\n");
	printf("\t[4] |--> Sort by cellphone number\n");
	printf("\t[5] |--> Main Menu\n");
	printf("\n\t::Enter a number (1-5): ");
	ch = getc(stdin);
	getc(stdin);
	printf("\n--------------------------------------------------------------------------------");
    switch(ch){
		case '1':
		sortf();
	    break;
		case '2':
		sortl();
		break;
		case '3':
		sortp();
		break;
		case '4':
		sortc();
		break;
		case '5':
		default:
			return ;
    }
}

void sortf(void)
{
	struct contact B;
	register int i,j;
	for(i= last-1 ;i > 0; i--)
		for(j = 0; j < i; j++)
			 if(strcmp(A[j].fname, A[j+1].fname) > 0) {
			 	B = A[j];
				A[j] = A[j+1];
				A[j+1] = B;
			 }
	printf("\nplease wait... .Contacts will be sorted by first names.");
	list2();
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}

void sortl(void)
{
	struct contact B;
	register int i,j;
	for(i = last-1 ; i > 0; i--)
		for(j = 0; j < i ; j++)
			if(strcmp(A[j].lname,A[j+1].lname) > 0) {
				B = A[j];
				A[j] = A[j+1];
				A[j+1] = B;
			}
	printf("\nplease wait... .Contacts will be sorted by last names.");
	list2();
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}
void sortp(void)
{
	struct contact B;
	register int i,j;
	for(i = last-1; i > 0; i--)
		for(j = 0; j < i; j++)
			if(strcmp(A[j].telep,A[j+1].telep) > 0) {
				B = A[j];
		  	    A[j] = A[j+1];
		        A[j+1] = B;
			}
	printf("\nplease wait... .Contacts will be sorted by telephone numbers.");
	list2();
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}
void sortc(void)
{
	struct contact B;
	register int i,j;
	for(i = last-1; i > 0; i--)
		for(j = 0; j < i; j++)
			if(strcmp(A[j].cellp,A[j+1].cellp) > 0) {
				B = A[j];
				A[j] = A[j+1];
				A[j+1] = B;
			}
	printf("\nPlease wait... .Contacts will be sort by cellphone numbers.");
	list2();
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}

void list()
{
	struct contact * temp = root;
	int i;
	clrscr();
    printf("\nPhone Book12<::>All Contacts List");
    printf("\n--------------------------------------------------------------------------------");
	gotoxy(1,4);
	printf("Row");
	gotoxy(9,4);
	printf("First Name");
	gotoxy(27,4);
	printf("Last Name");
	gotoxy(44,4);
	printf("Telephone");
	gotoxy(60,4);
	printf("Cellphone");
	printf("\n--------------------------------------------------------------------------------");
	//for(i = 0; i < last; i++) {
	i = 0;
	while(temp != NULL){
		gotoxy(1,i+6);
		printf("%3.3d",i+1);
		gotoxy(9,i+6);
		printf("%s",temp->fname);
		gotoxy(28,i+6);
		printf("%s",temp->lname);
		gotoxy(44,i+6);
		printf("%s",temp->telep);
		gotoxy(60,i+6);
		printf("%s",temp->cellp);
		temp = temp->_next_fname;
		i ++;
	}

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n\t\t    **********End Of list!**********");
	printf("\n\n\n   ::Press a key to return main page & continue program.|-->");
	getc(stdin);
}

void list2(void)
{
	register int i;
    printf("\n--------------------------------------------------------------------------------");
	gotoxy(1,18);
	printf("Row");
	gotoxy(9,18);
	printf("First Name");
	gotoxy(27,18);
	printf("Last Name");
	gotoxy(44,18);
	printf("Telephone");
	gotoxy(60,18);
	printf("Cellphone");
	printf("\n--------------------------------------------------------------------------------");
	for(i = 0; i < last; i++) {
		gotoxy(1,i+21);
		printf("%3.3d",i+1);
		gotoxy(9,i+21);
		printf("%s",A[i].fname);
		gotoxy(27,i+21);
		printf("%s",A[i].lname);
		gotoxy(44,i+21);
		printf("%s",A[i].telep);
		gotoxy(60,i+21);
		printf("%s",A[i].cellp);
	}
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n\t\t    **********End Of list!**********");
}

void help(void)
{
	 clrscr();
	 gotoxy(26,1);
	 printf("--------------------------");
	 gotoxy(26,2);
	 printf("|Welcome To Phone Book12!|");
	 gotoxy(26,3);
	 printf("--------------------------");
	 gotoxy(1,5);
	 printf("PhoneBook12>>[Help & Instructions] \n");
	 printf("--------------------------------------------------------------------------------\n");
	 printf("\nAbout Phonebook12\n *Version: 2.5\n *Valence: 50 Contacts(MAX)\n  *By: Morteza Zakeri (2011-12)");
	 printf("\n\nThis program allows you to have a list of your contacts.\nIt also allows you to have your listing added or deleted from your list.\nOther features of this program include:\nSearch,edit,sort & list.\n\n   ::Press a key to return main page & continue program.|-->");
	 getc(stdin);
 }

 void clrscr()
 {
	 system("clear");
 }

 void gotoxy(int x, int y)
 {
	 printf("%c[%d;%df", 0x1B, y, x);
 }

