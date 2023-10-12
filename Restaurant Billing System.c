#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

struct menu
{
	int item_no;
	char name[30];
	int price;
	struct menu *next;
};

struct menu_items
{
	int item_no;
	int quantity;
	int price;
};

struct date
{
    int dd;
    int mm;
    int yy;
};

struct bill_item
{
	int bill_no;
	struct date d;
	char cust_name[20];
	struct menu_items items[10];
	int total;
	int items_count;
	struct bill_item *next;
};


struct menu* head=NULL;
struct bill_item *bhead=NULL;
int item_num = 101,bill_num=1001;

void disp_menu()
{
    struct menu *t;
    if(head == NULL)
    {
        printf("\nMenu is empty!!!\n\n");
    }
    else
    {
        t=head;
        printf("\n");
        while(t!=NULL)
        {
            printf("Item no: %d\tItem name : %s\tPrice : %d\n\n",t->item_no,t->name,t->price);
            t = t->next;
        }
        printf("\n\n");
    }
}

struct date get_date()
{
	struct date d;
	time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    
    d.dd=current_time->tm_mday;
    d.mm=current_time->tm_mon + 1;
    d.yy=current_time->tm_year + 1900;
    
    return d;
}

void date_print(struct date d) 
{
    printf("%d-%d-%d\n", d.dd, d.mm, d.yy);
} 

int date_cmp(struct date d1, struct date d2) {
	if (d1.dd == d2.dd && d1.mm == d2.mm && d1.yy ==d2.yy)
    	return 0;
 	else if (d1.yy > d2.yy || d1.yy == d2.yy && d1.mm > d2.mm || d1.yy == d2.yy && d1.mm == d2.mm && d1.dd > d2.dd)
    	return 1;
 	else 
	 	return -1;
}
void print_bill(struct bill_item *t)
{
	int i;
	printf("-----------Invoice-------------\n\n");
	printf("Bill Number : %d\n",t->bill_no);
	printf("Customer Name : %s\n",t->cust_name);
	printf("Bill date : ");
	date_print(t->d);
	printf("--------- Items ---------\n\n");
    for(i=0;i<t->items_count;i++)
    {	
    	printf("Item num - %d\t Price - %d\tQuantity - %d\n\n",t->items[i].item_no,t->items[i].price,t->items[i].quantity);
	}
	printf("-----------------------\n\n");
	printf("Total Amount : Rs %d\n",t->total);	
	printf("--------------------------------\n\n\n");
}
 
void disp_bills()
{
	system("cls");
    struct bill_item *t;
    if(bhead == NULL)
    {
        printf("\nBills  empty!!!\n\n");
    }
    else
    {
        t=bhead;
        printf("\n");
        while(t!=NULL)
        {
            print_bill(t);
            t = t->next;
        }
    }	
    getch();
    
}	

disp_date_bills()
{
	system("cls");
    struct bill_item *t;
    struct date d;
    int flag=0;
    if(bhead == NULL)
    {
        printf("\nBills  empty!!!\n\n");
    }
    else
    {
        t=bhead;
        printf("\n");
        printf("Enter date in dd-mm-yyyy format : ");
    	scanf("%d-%d-%d",&d.dd,&d.mm,&d.yy);
    	printf("\n\n");
        while(t!=NULL)
        {
        	if(date_cmp(d,t->d) == 0)
        	{
        		flag=1;
        		print_bill(t);
			}
            t = t->next;
        }
		if(flag==0)
        	printf("No bills found in this date");	
    }	
    getch();
    
}

disp_between_dates_bills()
{
	system("cls");
    struct bill_item *t;
    struct date d1,d2;
    int flag=0;
    if(bhead == NULL)
    {
        printf("\nBills  empty!!!\n\n");
    }
    else
    {
        t=bhead;
        printf("\n");
        printf("Enter start date in dd-mm-yyyy format : ");
    	scanf("%d-%d-%d",&d1.dd,&d1.mm,&d1.yy);
    	printf("\n");
    	printf("Enter end date in dd-mm-yyyy format : ");
    	scanf("%d-%d-%d",&d2.dd,&d2.mm,&d2.yy);
    	printf("\n\n");
        while(t!=NULL)
        {
        	if((date_cmp(d1,t->d) <= 0) && (date_cmp(d2,t->d) >= 0))
        	{
        		flag=1;
        		print_bill(t);
			}
            t = t->next;
        }
        if(flag==0)
        	printf("No bills found between these dates");
    }	
    getch();
}

struct menu *search_item(int itemno)
{	
    struct menu *t;
    int index = 0,flag=0;
    if(head == NULL)
    {
        printf("\nLinked List is empty!!!\n\n");
        return NULL;
    }
    else
    {
        t=head;
        while(t!= NULL)
        {
            if(t->item_no == itemno)
            {
                flag = 1;
                return t;
            }
            t=t->next;
            index++;
        }
        if(flag == 0){
            printf("Item not found\n");
            return NULL;
    	}
        printf("\n");
    }
}

struct bill_item *readBills(){
    int i;
    struct bill_item *temp = (struct bill_item *)malloc(sizeof(struct bill_item));;
	struct bill_item *last; // points to the first node of the linked list in the file
    FILE* file;
    file = fopen ("bills.txt", "rb");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    while(fread(temp, sizeof(struct bill_item), 1, file))
    {
    	
        if(bhead==NULL)
        {
            bhead = last = (struct bill_item *)malloc(sizeof(struct bill_item));
        }
        else
        {
            last->next = (struct bill_item *)malloc(sizeof(struct bill_item));
            last = last->next;
        }
       
            last->items_count=temp->items_count;
            last->bill_no=temp->bill_no;
            last->d = temp->d;
	        last->total = temp->total;
	        strcpy(last->cust_name, temp->cust_name);
	        bill_num=last->bill_no+1;       
        for(i=0;i<temp->items_count;i++)
        {
        	last->items[i].item_no = temp->items[i].item_no;
        	last->items[i].price = temp->items[i].price;
        	last->items[i].quantity = temp->items[i].quantity;
		}
        last->next = NULL;
    }
    fclose(file);																										
    return last;
}

void write_to_bills_file()
{
	struct bill_item *t = bhead;
	struct bill_item *temp = (struct bill_item *)malloc(sizeof(struct bill_item));
    FILE* file;
    file = fopen("bills.txt", "wb");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    int i;	
	while(t!=NULL)
    {    
        fwrite(t, sizeof(struct bill_item), 1, file);
        t = t->next;
    }
    if(fwrite != 0)
        printf("Data stored in the file successfully\n");
    else
        printf("Error While Writing\n");    
    fclose(file);
}

struct bill_item *generate_invoice(struct bill_item *t)
{
	int itemno,c_flag=1,i=0,q,total=0;
	if(bhead == NULL)
	{
		bhead=t;
	}
	else{
		t->next = (struct bill_item *)malloc(sizeof(struct bill_item));;
		t=t->next;
	}
	
	printf("Enter customer name : ");
	scanf(" %[^\n]",t->cust_name);
	disp_menu();
	t->bill_no = bill_num++;
	do
	{
		printf("\nEnter item number : ");
		scanf("%d",&itemno);
		struct menu *m1;
		m1 = search_item(itemno);
		if(m1!=NULL)
		{
			t->items[i].item_no=itemno;
			printf("Enter the quantity : ");
			scanf("%d",&q);
			t->items[i].quantity = q;
			t->items[i].price = q * m1->price;
			total = total + t->items[i].price;
		}
		else
			continue;
		i++;
		printf("\n\nDo you want to add more items to the bill?\n1.yes\t2.no\n");
		scanf("%d",&c_flag);	
	}
	while(c_flag == 1);
	t->total = total;
	t->items_count = i;
	t->d = get_date();
	t->next = NULL;
	write_to_bills_file();
	return t;
}

void write_to_menu_file()
{
	struct menu *temp = head;
    FILE* file;
    file = fopen ("menu_list.txt", "wb");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // writing all the nodes of the linked list to the file
    while(temp!=NULL)
    {
        fwrite(temp, sizeof(struct menu), 1, file);
        temp = temp->next;
    }
    if(fwrite != 0)
        printf("Linked List stored in the file successfully\n");
    else
        printf("Error While Writing\n");    
    fclose(file);
}

void insert_menu_item()
{
	struct menu *t;
	char tname[30];
	int tprice;
	printf("Enter the item name : ");
	scanf(" %[^\n]",&tname);
	printf("Enter the item price : ");
	scanf("%d",&tprice);
	if(head == NULL)
    {
        head = (struct menu *)malloc(sizeof(struct menu));
        head->item_no = item_num++;
        head->price = tprice;
        strcpy(head->name,tname);
        head->next = NULL;
    }
    else
    {
        t = head;
        while(t->next != NULL)
        {
            t = t->next;
        }
        t->next = (struct menu *)malloc(sizeof(struct menu));
        t->next->item_no=item_num++;
        t->next->price = tprice;
        strcpy(t->next->name,tname);
        t->next->next = NULL;
    }
    write_to_menu_file();
}

void readLinkedList(){
    
    struct menu* temp = (struct menu *)malloc(sizeof(struct menu));;
    
	struct menu* last; // points to the first node of the linked list in the file
    FILE* file;
    file = fopen ("menu_list.txt", "rb");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct menu), 1, file))
    {
        if(head==NULL)
        {
            head = last = (struct menu *)malloc(sizeof(struct menu));
        }
        else
        {
            last->next = (struct menu *)malloc(sizeof(struct menu));
            last = last->next;
        }
        last->item_no = temp->item_no;
        last->price = temp->price;
        strcpy(last->name, temp->name);
        last->next = NULL;
        item_num=last->item_no+1;
    }
    fclose(file);
}

search_bill_by_no()
{
	struct bill_item *t;
	int bno;
    int index = 0,flag=0;
    system("cls");
    printf("\n\n");
    if(bhead == NULL)
    {
        printf("\nBills empty!!!\n\n");
    }
    else
    {
    	printf("Enter the bill number to search : ");
    	scanf("%d",&bno);
    	printf("\n\n");
        t=bhead;
        while(t!= NULL)
        {
            if(t->bill_no == bno)
            {
                flag = 1;
                print_bill(t);
                break;
            }
            t=t->next;
            index++;
        }
        if(flag == 0)
        	printf("No Bills found\n");
    }
    getch();
}

search_bill_by_cname()
{
	struct bill_item *t;
	char cname[20],lower_cname[20],lower_cust_name[20];
    int index = 0,flag=0,i;
    system("cls");
    printf("\n\n");
    if(bhead == NULL)
    {
        printf("\nBills empty!!!\n\n");
    }
    else
    {
    	printf("Enter the Customer Name to search : ");
    	scanf(" %[^\n]",cname);
    	for (i = 0; cname[i]; i++)
		{
        	lower_cname[i] = tolower(cname[i]);
        }
    	printf("\n\n");
        t=bhead;
        while(t!= NULL)
        {
        	for (i = 0; t->cust_name[i]; i++) 
			{
        	    lower_cust_name[i] = tolower(t->cust_name[i]);
        	}
        	if (strstr(lower_cust_name, lower_cname) != NULL) 
			{
                flag = 1;
                print_bill(t);
            }
            t=t->next;
            index++;
        }
        if(flag == 0)
        	printf("No Bills found\n");
    }
    getch();
}

bill_display_menu()
{
	int ch;
	do
	{
		system("cls");
		printf("\n\n1. Display all Bills\n2. Display Bills of a particular date\n3. Display Bills between two dates\n4. Go back to Main Menu\n");
		printf("\nEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: disp_bills();
					break;
			case 2: disp_date_bills();
					break;
			case 3: disp_between_dates_bills();
					break;
			case 4: break;
			default : printf("Wrong Choice!");
					getch();
					break;
		};
	system("cls");
	}while(ch!=4);
}

bill_search_menu()
{
	int ch;
	do
	{
		system("cls");
		printf("\n\n1. Search by Bill Number\n2. Search by Customer Name\n3. Go back to Main Menu\n");
		printf("\nEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: search_bill_by_no();
					break;
			case 2: search_bill_by_cname();
					break;
			case 3: break;
			default : printf("Wrong Choice!");
					getch();
					break;
		};
	system("cls");
	}while(ch!=3);
}
int menu()
{
	int opt;
	printf("\n\n1. Generate Invoice\n2. Display Bills\n3. Search Bills\n4. Admin Portal\n5. Exit");
	printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    return opt;
}

int admin_menu()
{
	int ch;
	system("cls");
	printf("\n\n1.Add Menu Item\n2. Display Menu Items\n3. Logout");
	printf("\n\nYour choice:\t");
    scanf("%d",&ch);
    return ch;
}

void admin_portal()
{
	int ch;
	for(ch=admin_menu();ch!=3;ch=admin_menu())
	{
		switch(ch)
		{
			case 1 : insert_menu_item();
					  break;
			case 2 : disp_menu();
					 getch();
					  break;
			default : printf("\nWrong choice");
		    		 break;
		}
	}
}
void main()
{
	int ch;
	readLinkedList();
	struct bill_item *t;
	t=readBills();
	for(ch=menu();ch!=5;ch=menu())
	{
		switch(ch)
		{
			case 1 : t=generate_invoice(t);
					 break;
			case 2 : bill_display_menu();
					 break;
			case 3 : bill_search_menu();
					 break;
			case 4 : admin_portal();
					 break;
		    default : printf("\nWrong choice");
		    		 break;
		}
	}
}


