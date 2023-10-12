#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
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

struct bill_item
{
	int bill_no;
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

void disp_bills()
{
	system("cls");
	int i;
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
            	
            printf("-----------Invoice-------------\n\n");
			printf("Bill Number : %d\n",t->bill_no);
			printf("Customer Name : %s\n",t->cust_name);
			printf("--------- Items ---------\n\n");
            for(i=0;i<t->items_count;i++)
            {	
            		printf("Item num - %d\t Price - %d\tQuantity - %d\n\n",t->items[i].item_no,t->items[i].price,t->items[i].quantity);
			}
		    printf("-----------------------\n\n");
			printf("Total Amount : Rs %d\n",t->total);	
			printf("--------------------------------\n\n");
            t = t->next;
        }	
        printf("\n\n");
    }	
    getch();
    system("cls");
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

struct bill_item *get_bill_item_address()
{
	struct bill_item *t;
	if(bhead == NULL)
    {
        bhead = (struct bill_item *)malloc(sizeof(struct bill_item));
        return bhead;
    }
    else
    {
        t = bhead;
        while(t->next != NULL)
        {
            t = t->next;
        }
        t->next = (struct bill_item *)malloc(sizeof(struct bill_item));
        return t;
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
	int itemno,c_flag,i=0,q,total=0;
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
		i++;
		printf("\n\nDo you want to add more items to the bill?\n1.yes\t2.no\n");
		scanf("%d",&c_flag);	
	}
	while(c_flag == 1);
	t->total = total;
	t->items_count = i;
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

int menu()
{
	int opt;
	printf("\n\n1. Generate Invoice\n2. Display Bills\n3. Admin Portal");
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
	for(ch=menu();ch!=3;ch=menu())
	{
		switch(ch)
		{
			case 1 : t=generate_invoice(t);
					 break;
//					 system("cls");
			case 2 : disp_bills();
					 break;
			case 3 : admin_portal();
					 break;
		    default : printf("\nWrong choice");
		    		 break;
		}
	}
}


