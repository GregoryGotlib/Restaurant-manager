#include "header.h"

int CreateProduct(Pkitchen *kit,Ptable *table, char *p_name, float prc, int qnt)
{
	kitchen *temp=*kit, *next = *kit, *prev = NULL;
	
	while (temp)//if the product name exists
	{
		if (strcmp(temp->Product_Name, p_name) == 0)
		{
			Error_msg("Sorry,this product is already exists!\n");
			return 0;
		}
		temp = temp->next;
	}
	if (prc <= 0)//if the price is negetive number
	{
		Error_msg("The product price have to be positive!\n");
		return 0;
	}
	if (qnt <= 0)//if the quantity is negetive number
	{
		Error_msg("The quantity value have to be a positive number!\n");
		return 0;
	}
	if (!(temp = (Pkitchen)malloc(sizeof(kitchen))))//allocating memory
	{
		Delete_Product(kit);
		Delete_Tables(table);
		Error_msg("Sorry,there is not enough memory..\n");
		return 0;
	}
	if (!(temp->Product_Name = (char*)malloc((strlen(p_name)+1)*sizeof(char))))//allocating memory
	{
		Delete_Product(kit);
		Delete_Tables(table);
		Error_msg("Sorry,there is not enough memory..\n");
		return 0;
	}
	//inserting data
	strcpy(temp->Product_Name, p_name);
	temp->Price = prc;
	temp->Quantity = qnt;
	temp->Ordered = 0;

	if (*kit == NULL)//if the node is empty
	{
		*kit = temp;
		temp->next = NULL;
	}
	else
	{
		while (strcmp(temp->Product_Name, next->Product_Name) > 0)//until the name is bigger
		{
			if (next->next == NULL)//if its the last node
			{
				next->next = temp;
				temp->next = NULL;
				return 1;
			}
			prev = next;
			next = next->next;
		}
		if (prev == NULL)//if its in the head of the node
		{
			temp->next = *kit;
			*kit = temp;
			return 1;
		}
		prev->next = temp;
		temp->next = next;
	}
	return 1;
}

void Error_msg(char *str)
{
	printf("\n%s", str);
}



int AddItem(Pkitchen *kit, char *p_name, int qnt)
{
	kitchen *temp=*kit;
	int cnt = 0;
	if (qnt <= 0)//if the quantity is not a positive number
		Error_msg("The quantity value have to be a positive number!\n");
	while (temp)
	{
		if (strcmp(temp->Product_Name , p_name)==0)//if it is the desirable product
		{
			cnt++;
			temp->Quantity += qnt;
			break;
		}
		temp = temp->next;
	}
	if (!cnt){// if the product name does not exists
		Error_msg("This product not exists!\n");
		return 0;
	}
	printf("%d Items were added to %s.\n", qnt, temp->Product_Name);
	printf("Now you have %d %s left!\n\n", temp->Quantity, temp->Product_Name);
	return 1;
}

int Check1(Pkitchen kit, char *Productname)
{
	while (kit)
	{
		if (strcmp(kit->Product_Name, Productname) == 0)
			return 1;
		kit = kit->next;
	}
	return 0;
}


int Check2(Ptable table,char *Productname)
{
	int i = TABLES;
	while (table)
	{
		if (strcmp(table->Product_Name, Productname) == 0)
			return 1;
		table = table->next;
	}
	return 0;
}


int OrderItem(Pkitchen kit, Ptable **tbl, int tbl_num, char *p_name, int qnt)
{
	Pkitchen temp = kit;
	Ptable t1, t2;
	if (!Check1(kit, p_name))//if the product exists in our kitchen
	{
		Error_msg("The product not exists!\n");
		return 0;
	}
	if (tbl_num<0 || tbl_num>TABLES)//if the table number not exists
	{
		Error_msg("There is no such table\n");
		return 0;
	}
	if (qnt <= 0)
	{
		Error_msg("The quantity value have to be a positive number!\n");
		return 0;
	}
	while (strcmp(temp->Product_Name, p_name) != 0)//moving to the right product node
		temp = temp->next;
	if (qnt > temp->Quantity)
	{
		Error_msg("There is not enough Products left in the kitchen for your reservation.\n");
		return 0;
	}
	if (*((*tbl) + tbl_num) == NULL || Check2(*((*tbl) + tbl_num), p_name) == NULL)//in case the table not exists yet or the product not exists yet
	{
		t1 = (Ptable)malloc(sizeof(Table));//allocating memory for new table
		if (!t1)
		{
			Delete_Product(kit);
			Delete_Tables(*tbl);
			Error_msg("Sorry,there is not enough memory..\n");
			return 0;
		}
		t1->Product_Name = (char*)malloc((strlen(p_name) + 1)*sizeof(char));//allocating memory for product name
		if (!t1->Product_Name)
		{
			Delete_Product(kit);
			Delete_Tables(*tbl);
			Error_msg("Sorry,there is not enough memory..\n");
			return 0;
		}
		strcpy(t1->Product_Name, p_name);
		t1->Quantity = qnt;
		t1->Price = temp->Price;
		t1->Table_Number = tbl_num;
		temp->Quantity -= qnt;
		temp->Ordered += qnt;
	}
	if (*((*tbl) + tbl_num) == NULL)//new order for the table
	{
		t1->next = NULL;
		t1->prev = NULL;
		*((*tbl) + tbl_num) = t1;
	}
	else
	{
		if (Check2(*((*tbl) + tbl_num), p_name) == 1)//in case the product is already ordered to the table
		{
			t1 = *((*tbl) + tbl_num);
			while (strcmp(t1->Product_Name, p_name) != 0)
				t1 = t1->next;
			t1->Quantity += qnt;
			temp->Quantity -= qnt;
		}
		else //Product not have been ordered yet
		{
			t2 = *((*tbl) + tbl_num);
			while (t2->next)
				t2 = t2->next;
			t2->next = t1;
			t1->next = NULL;
			t1->prev = t2;
		}
	}
	if (temp->Quantity)
		printf("NOTE* After this reservation there is only %d portion(s) of %s left!\n", temp->Quantity,temp->Product_Name);
	else printf("NOTE* There is no more %s!\n", temp->Product_Name);
	return 1;
}

	
int RemoveItem(Pkitchen kit,Pkitchen_Gluten gluten, Ptable **table, int tbl_num, char *p_name, int qnt)
{
	Pkitchen temp = kit;
	Pkitchen_Gluten temp2 = gluten;
	Ptable t1 = *((*table) + tbl_num);
	//checking inputs

	if (!(Check1(temp, p_name))&&!(Check1(temp2,p_name)))
	{
		Error_msg("There is no such product in our kitchen!\n");
		return 0;
	}
	if (!Check2(t1, p_name))
	{
		Error_msg("There is no such product in this table resevation\n");
		return 0;
	}
	if (qnt <= 0)
	{
		Error_msg("The quantity value have to be a positive number!\n");
		return 0;
	}
	if (tbl_num < 0 || tbl_num > TABLES)
	{
		Error_msg("There is no such table here!\n");
		return 0;
	}
	while (strcmp(t1->Product_Name, p_name) != 0)
		t1 = t1->next;
	if (t1->Quantity < qnt)
	{
		Error_msg("You have ordered less of this product than you want to cancel!\n");
		return 0;
	}
	//
	if (qnt < t1->Quantity)
		t1->Quantity -= qnt;
	else//in case the quantity we want to remove and the quantity that have been ordered are equal, we have to delete this node.
		*((*table) + tbl_num) = Delete_Node(*((*table) + tbl_num), t1);
	return 1;
}

int Happy_Moment(Pkitchen kit,int *num)
{
	Pkitchen temp=kit;
	char name[256];
	int max=0;
	while (temp)
	{
		if (max < (temp->Ordered))
		{
			strcpy(name, temp->Product_Name);
			max = temp->Ordered;
		}
		temp = temp->next;
	}
	*num = max;
	return name;
}

int ChangeTable(Ptable **table, Pkitchen kit, int crnt_table)
{
	Ptable newtable;
	int i = TABLES;
	//checking inputs
	if (crnt_table > TABLES || crnt_table < 0)
	{
		Error_msg("There is no such table in here!\n");
		return 0;
	}
	if (!(*((*table) + crnt_table)))
	{
		Error_msg("There is no orders for this table!\n");
		return 0;
	}
	//
	//Memory allocation + inserting new data

	while (i)
	{
		if (!*((*table) + (i-1)))
		{
			newtable = (Ptable)malloc(sizeof(Table));
			if (!newtable)
			{
				Delete_Product(kit);
				Delete_Tables(*table);
				Error_msg("Sorry,there is not enough memory..\n");
				return 0;
			}
			newtable->Product_Name = (char*)malloc((strlen((*((*table) + crnt_table))->Product_Name) + 1)*sizeof(char));
			if (!newtable->Product_Name)
			{
				Delete_Product(kit);
				Delete_Tables(*table);
				Error_msg("Sorry,there is not enough memory..\n");
				return 0;
			}
			newtable = *((*table) + crnt_table);
			*((*table) + (i-1)) = newtable;
			*((*table) + crnt_table) = NULL;
			break;
		}
		i--;
	}
	if (i == 0)
		printf("Sorry,there are no available tables!\n");
	return i;
}

int RemoveTable(Ptable **table,int table_number)
{
	Ptable temp2;
	float total_price=0;
	//checking input
	if (table_number < 0 || table_number > TABLES)
	{
		Error_msg("There is no such table here!\n");
		return 0;
	}
	if (!(*((*table) + table_number)))
	{
		Error_msg("There is no orders for this table!\n");
		return 0;
	}
	//

	printf("\nTable number %d report:\n", table_number);
	while (*((*table) + table_number))
	{
		printf("*Dish name:%s\n*Dish Quantity:%d\n*Singel dish price:%.2f\n\n", (*((*table) + table_number))->Product_Name, (*((*table) + table_number))->Quantity, (*((*table) + table_number))->Price);
		total_price += (*((*table) + table_number))->Price*((*((*table) + table_number))->Quantity);
		temp2 = (*((*table) + table_number));
		(*((*table) + table_number)) = (*((*table) + table_number))->next;
		free(temp2->Product_Name);
		free(temp2);
	}
	printf("Table number %d total check is--> %.2f\n\n", table_number,(float)total_price);
	return 1;
}

void Delete_Tables(Ptable *table)
{
	Ptable temp;
	int i;
	for (i = 0; i < TABLES; i++)
		while (table[i])
		{
			free(table[i]->Product_Name);
			temp = table[i];
			table[i] = table[i]->next;
			table[i]->prev = NULL;
			free(temp);
		}
	free(table);
}

void Delete_Product(Pkitchen kit)
{
	Pkitchen temp;
	int i;
	while (kit)
	{
		free(kit->Product_Name);
		temp = kit;
		kit = kit->next;
		free(temp);
	}
}


Ptable Delete_Node(Ptable main, Ptable node)
{
	Ptable temp, temp2;
	if (node->next == NULL&&node->prev == NULL)//its the only node
	{
		free(node->Product_Name);
		free(node);
		return NULL;//pointing back to NULL
	}
	if (node->next != NULL&&node->prev == NULL)//if its the head of the node
	{
		temp = node;
		main = main->next;
		main->prev = NULL;
		free(temp->Product_Name);
		free(temp);
		return main;
	}
	if (node->next == NULL)//if its the last node
	{
		temp = node;
		node = node->prev;
		node->next = NULL;
		free(temp->Product_Name);
		free(temp);
		return main;
	}
	if (node->next != NULL&&node->prev != NULL)//if its somewhere in the middle
	{
		temp = node->prev;
		temp2 = node->next;
		free(node->Product_Name);
		free(node);
		temp->next = temp2;
		temp2->prev = temp;
		return main;
	}
}

void Discount(Ptable *head, char *p_name,int arr[])
{
	Ptable temp = *head;
	int i;
	for (i = 0; i < TABLES; i++)
	{
		if (*head)
			while (temp)
			{
				if (strcmp(temp->Product_Name ,p_name) == 0)
				{
					arr[i]++;
					break;
				}
				temp = temp->next;
			}
		head++;
	}
}



int RemoveTableWithDiscount(Ptable **table, int table_number,int arr[],char *p_name)
{
	Ptable temp2;
	float total_price = 0;
	//checking input
	if (table_number < 0 || table_number > TABLES)
	{
		Error_msg("There is no such table here!\n");
		return 0;
	}
	if (!(*((*table) + table_number)))
	{
		Error_msg("There is no orders for this table\n");
		return 0;
	}
	//

	printf("Table number %d report:\n\n", table_number);
	while ((*((*table) + table_number)))
	{
		printf("*Dish name:%s\n*Dish Quantity:%d\n*Singel dish price:%.2f\n", (*((*table) + table_number))->Product_Name, (*((*table) + table_number))->Quantity, (*((*table) + table_number))->Price);
		if (strcmp((*((*table) + table_number))->Product_Name, p_name) == 0 && arr[table_number] != 0)//looking for the right product to get the discount
		{
			(*((*table) + table_number))->Price -= ((*((*table) + table_number))->Price * 25 / 100);
			printf("*Singel dish price(AFTER DISCOUNT):%.2f\n", (*((*table) + table_number))->Price);
		}
		total_price += ((*((*table) + table_number))->Price*(*((*table) + table_number))->Quantity);
		temp2 = (*((*table) + table_number));
		(*((*table) + table_number)) = (*((*table) + table_number))->next;
		free(temp2->Product_Name);
		free(temp2);
		printf("\n");
	}
	printf("Table number %d total check is--> %.2f\n*NOTE This check is with a discount for %s\n\n", table_number, (float)total_price,p_name);
	return 1;
}






























































































