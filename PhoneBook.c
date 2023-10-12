#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <conio.h>

#include <ctype.h>

typedef struct list add;

struct list

{
    char name[40];
    char num[20];
    char gmail[40];
    add* next;
};

add* head=NULL;
int i=1,size=0;

void Insert()

{
    add *temp=(add *)malloc(sizeof(add));
    printf("\n\n\nContact name : ");
    gets(temp->name);
    system("cls");
    printf("\n\n\nContact Name : ");
    gets(temp->name);
    system("cls");
    printf("\n\n\nMobile Number : ");
    gets(temp->num);
    system("cls");
    printf("\n\n\nGmail id : ");
    gets(temp->gmail);
    system("cls");
    system("cls");
    temp->next = NULL;
    size++;
    
    if(size == 5)
    {
        system("cls");
        printf("\n\n\nPhone Memory is full!!!");
        printf("\nIf you want to add more contact,You have to delete some contact from your list...\n\n\n");
        return;

    }
    else
    {
        if(head == NULL)
        {
            head = temp;
            system("cls");
            printf("\n\nDone!!!Head\n\n");
            return;
        }
        else
        {
            add* p = head;
            while(p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
            system("cls");
            printf("\nDone!!!\n\n");
        }
        return;
    }
}

void Search()

{
    char ch[40];
	int i, flag=0;
    
    if(head == NULL)
    {
        system("cls");
        printf("\n\n\n\t\tNo Contact exists in this Phone Book List!!!\n\n");
        return;
    }
    else
    {
    	printf("\n\n\nContact name : ");
    	scanf(" %[^\n]",ch);
    	system("cls");

        add*p = head;

        while(p != NULL)

        {
			char lowercaseQuery[50];
        	char lowercaseName[50];
        	strcpy(lowercaseQuery, ch);
        	strcpy(lowercaseName, p->name);
        	for (i = 0; lowercaseQuery[i]; i++)  //loop ends when the value becomes '\0'.because it equates to 0 wwhhich is false
			{
        	    lowercaseQuery[i] = tolower(lowercaseQuery[i]);
        	}
        	for (i = 0; lowercaseName[i]; i++) 
			{
        	    lowercaseName[i] = tolower(lowercaseName[i]);
        	}
        	if (strstr(lowercaseName, lowercaseQuery) != NULL) 
			{
				flag = 1;
                printf("\n\t%s",p->name);
                printf("\n-------------------------");
                printf("\nNumber : %s",p->num);
                printf("\nGmail ID : %s",p->gmail);
        	}
        	p = p->next;
         }
        
    }
        if(flag == 0)
        	printf("Contact Not Found!");
}

void Delete()

{
    char ch[40];
    printf("\nContact name : ");
    gets(ch);
    system("cls");
    printf("\nContact name : ");
    gets(ch);
    system("cls");
    
    if(head == NULL)
    {
        system("cls");
        printf("\nNo Contact exists in this Phone Book List!\n\n");
        return;
    }
    else
    {
        if(strcmp(((head)->name),ch) == 0)
        {
            add*p=head;
            head = (head)->next;
            free(p);
            printf("\nDone!!!\n\n\n\n");
            return;
        }
        else
        {

            add*p = head;
            while(p->next != NULL)
            {
                if(strcmp((p->next->name),ch) == 0)
                {
                    p->next = p->next->next;
                    size--;
                    printf("\nDone!!!\n\n\n\n");
                    return;
                }
                p = p->next;
            }
            system("cls");
            printf("\n\t\t\t\t\tInvalid Contact!!!\n\n");
        }
    }
}

void Display()

{

    if(head == NULL)
    {
        system("cls");
        printf("\n\n\n\t\tNo Contact exists in this Phone Book List!");
        return;
    }

    else

    {
        add*p = head;
        while(p != NULL)
        {
            printf("\n\n%d.%c%s",i,32,p->name);
            printf("\n-------------------------");
            printf("\nNumber : %s",p->num);
            printf("\nGmail ID : %s",p->gmail);
            p = p->next;
            i++;
        }
    i=1;
    return;
    }

}

int main()

{
     char c[40];
                mainhome:

                system("cls");

                printf("\n|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|");

                printf("\n|                  !!!!!!!!!!!!!!!!!!!!!!!!!!!!                 |");

                printf("\n|!!!!!!!!!!!!!!!!!!! WELCOME TO OUR PHONE BOOK !!!!!!!!!!!!!!!!!|");

                printf("\n|                  !!!!!!!!!!!!!!!!!!!!!!!!!!!!                 |");

                printf("\n|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n\n\n");

    while(1)

    {

        printf("\n\nMenu");

        printf("\n-------------------------------------------------");

        printf("\n1)Create A Contact\t\t2)Remove A Contact");

        printf("\n3)Show The Contact List\t\t4)Find A Contact");

        printf("\n5)Quit");

        int ch;

        scanf("%d",&ch);

        if(ch == 5)
        {
            break;
        }
        else
        {
             switch(ch)
            {
                case 1 :system("cls");
                        Insert();
                        break;
                        
                case 2 :system("cls");
                        Delete();
                        break;
                        
                case 3 :system("cls");
                        Display();
                        break;

                case 4 :system("cls");
                        Search();
                        break;

                default :printf("\n\t\tInvalid Choice!Try again!!!");
                         break;

            }
        }
    }
}

