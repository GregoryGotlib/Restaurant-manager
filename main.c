#include "header.h"

int main()
{
	Ptable *Table_Array;
	Pkitchen head = NULL;
	Pkitchen_Gluten head_g = NULL;
	int op = 0, i, flag,flag2, Quantity, table_number, orders = 0, Dis_array[TABLES] = { 0 },check_happy=0,G=0,max,max_g;
	char Productname[256], happy[256],Gluten,happy_g[256];
	float Price;
	Table_Array = (Ptable*)malloc(TABLES*sizeof(Ptable));
	if (!(Table_Array = (Ptable*)malloc(TABLES*sizeof(Ptable))))
	{
		printf("Sorry,there is not enough memory..\n");
		exit(1);
	}
	for (i = 0; i < TABLES; i++)//all the pointers equal to null
		Table_Array[i] = NULL;
	printf("<<Welcome to our Restaurant>>\n");
	printf("This is managment program, Please select one of the options below:\n");
	printf("Our tables numbered from 0-14.\n\n");
	printf("*****************************************************\n");
	printf("Option 1-> Create Product.                          *\n");
	printf("Option 2-> Add Product.                             *\n");
	printf("Option 3-> Order Product.                           *\n");
	printf("Option 4-> Cancel Product.                          *\n");
	printf("Option 5-> Move Table.                              *\n");
	printf("Option 6-> Close Table-check,ordered products.      *\n");
	printf("Option 7->'Happy Moment' the most popular dish.     *\n");
	printf("For exit press '8'.                                 *\n");
	printf("*****************************************************\n");
	printf("NOTE* To chose one of the options press the number.\nFor exampel, for option number 1 push 1 button on your keyborad.\n\n");
	while (1)//loop depends on user decision 
	{
		flag = 0;
		op = getch();
		if (op == '1')
		{
			printf("You have selected option number 1\nOption in progress..\n\n");
			printf("For gluten free products press 'g' else press enter\n");
			Gluten = getch();
			printf("Please enter product name:"); 
			scanf("%s", Productname);
			printf("Please enter product price:");
			scanf("%f",&Price);
			printf("Please enter product quantity:");
			scanf("%d",&Quantity);
			if (Gluten != 'g')
				flag = CreateProduct(&head,Table_Array,Productname,Price,Quantity);
			else
				flag = CreateProduct(&head_g, Table_Array, Productname, Price, Quantity);
			if (!flag)
				printf("There was a problem with option number 1..\nPlease try again!\n\n");
			else
			{
				printf("The product-> %s Price:%.2f Quantity:%d has been created\n\n",Productname,Price,Quantity);
				printf("Done with option 1, please select again\n");
				printf("To see the manu again press '9'\n");
				printf("For exit press '8'.\n\n");
			}
		}
		if (op == '2')
		{
			printf("You have selected option number 2\nOption in progress..\n\n");
			printf("For gluten free products press 'g' else press enter\n");
			Gluten = getch();
			printf("Please enter product name:");
			scanf("%s", Productname);
			printf("Please enter product quantity:");
			scanf("%d", &Quantity);
			if (Gluten != 'g')
				flag = AddItem(&head, Productname, Quantity);
			else
				flag = AddItem(&head_g, Productname, Quantity);
			if (!flag)
				printf("There was a problem with option number 2..\nPlease try again!\n\n");
			else
			{
				printf("Done with option number 2, please select again\n");
				printf("To see the manu again press '9'\n");
				printf("For exit press '8'.\n\n");
			}
		}
		if (op == '3')
		{
			printf("You have selected option number 3\nOption in progress..\n\n");
			printf("For gluten free products press 'g' else press enter\n");
			Gluten = getch();
			printf("Please enter table number:");
			scanf("%d", &table_number);
			printf("Please enter desirable dish:");
			scanf("%s", Productname);
			printf("Please enter quantity:");
			scanf("%d", &Quantity);
			if (Gluten != 'g')
				flag = OrderItem(head, &Table_Array, table_number, Productname, Quantity);
			else
			{
				flag = OrderItem(head_g, &Table_Array, table_number, Productname, Quantity);
				G = 1;
			}
			if (!flag)
				printf("There was a problem with option number 3..\nPlease try again!\n\n");
			else
			{
				orders = 1;
				printf("Table number %d ordered %d dishes of %s\n\n", table_number, Quantity, Productname);
				printf("Done with option number 3, please select again\n");
				printf("To see the manu again press '9'\n");
				printf("For exit press '8'.\n\n");
			}
		}
		if (op == '4')
		{
			printf("You have selected option number 4\nOption in progress..\n\n");
			printf("Please enter table number:");
			scanf("%d", &table_number);
			printf("Please enter product name:");
			scanf("%s", Productname);
			printf("Please enter quantity:");
			scanf("%d", &Quantity);
			flag = RemoveItem(head,head_g,&Table_Array, table_number, Productname, Quantity);
				if (!flag)
				printf("There was a problem with option number 4..\nPlease try again!\n\n");
			else
			{
				printf("%d Item have been removed from %s\n\n", Quantity, Productname);
				printf("Done with option number 4, please select again\n");
				printf("To see the manu again press '9'\n");
				printf("For exit press '8'.\n\n");
			}
		}
		if (op == '5')
		{
			if (orders)
			{
				printf("You have selected option number 5\nOption in progress..\n\n");
				strcpy(happy, Happy_Moment(head,&max));
				strcpy(happy_g, Happy_Moment(head_g,&max_g));
				if (max > max_g)
				{
					Discount(Table_Array, happy, Dis_array);
					check_happy = 1;
					printf("%s is the most popular dish for this moment!\n", happy);
					printf("All the tables who had ordered this dish above ^ getting 25 precent discount!\n\n");
					printf("Done with option number 5, please select again\n");
					printf("To see the manu again press '9'\n");
					printf("For exit press '8'.\n\n");
				}
				else
				{
					Discount(Table_Array, happy_g, Dis_array);
					check_happy = 1;
					printf("%s is the most popular dish for this moment!\n", happy_g);
					printf("All the tables who had ordered this dish above ^ getting 25 precent discount!\n\n");
					printf("Done with option number 5, please select again\n");
					printf("To see the manu again press '9'\n");
					printf("For exit press '8'.\n\n");
				}
			}
			else printf("There are no reservations yet!\n\n");
		}
		if (op == '6')
		{
			if (orders)
			{
				printf("You have selected option number 6\nOption in progress..\n\n");
				printf("Please enter table number:");
				scanf("%d", &table_number);
				flag = ChangeTable(&Table_Array, head, table_number);

				if (!flag)
					printf("There was a problem with option number 6..\nPlease try again!\n\n");
				else
				{
					printf("Table number %d moved to table number %d\n\n", table_number, (flag-1));
					printf("Done with option number 6, please select again\n");
					printf("To see the manu again press '9'\n");
					printf("For exit press '8'.\n\n");
				}
			}
			else printf("There are no reservations yet!\n\n");
		}
		if (op == '7')
		{
			if (orders)
			{
				printf("You have selected option number 7\nOption in progress..\n\n");
				printf("Please enter table number:");
				scanf("%d", &table_number);
				if (check_happy)
				{
					if (max>max_g)
						flag = RemoveTableWithDiscount(&Table_Array, table_number, Dis_array, happy);
					else
						flag = RemoveTableWithDiscount(&Table_Array, table_number, Dis_array, happy_g);
				}
				else
					flag = RemoveTable(&Table_Array, table_number);
				if (!flag)
					printf("There was a problem with option number 7..\nPlease try again!\n\n");
				else
				{
					printf("Done with option number 7, please select again\n");
					printf("To see the manu again press '9'\n");
					printf("For exit press '8'.\n\n");
				}
			}
			else printf("There are no reservations yet!\n\n");
		}
		if (op == '8')
		{
			printf("You have selected option number 8\nOption in progress..\n\n");
			printf("Deleting information..\nThank you,Goodbye!\n\nPress any button to exit..");
			break;
		}
		if (op == '9')
		{
			printf("<<Welcome to our Restaurant>>\n");
			printf("This is managment program, Please select one of the options below:\n");
			printf("Our tables numbered from 0-14.\n\n");
			printf("*****************************************************\n");
			printf("Option 1-> Create Product.                          *\n");
			printf("Option 2-> Add Product.                             *\n");
			printf("Option 3-> Order Product.                           *\n");
			printf("Option 4-> Cancel Product.                          *\n");
			printf("Option 5-> Move Table.                              *\n");
			printf("Option 6-> Close Table-check,ordered products.      *\n");
			printf("Option 7->'Happy Moment' the most popular dish.     *\n");
			printf("For exit press '8'.                                 *\n");
			printf("*****************************************************\n");
			printf("NOTE* To chose one of the options press the number.\nFor exampel, for option number 1 push 1 botton on your keyborad.\n\n");
		}
	}
	Delete_Product(head);
	Delete_Product(head_g);
	Delete_Tables(Table_Array);
	getch();
	return 0;
}