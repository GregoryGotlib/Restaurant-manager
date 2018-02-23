#ifndef Header_file
#define Header_file
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define TABLES 15
typedef struct {
	char *Product_Name;
	float Price;
	int Quantity;
	int Ordered;
	struct kitchen *next;
}kitchen, *Pkitchen,*Pkitchen_Gluten;

typedef struct{
	int Table_Number;
	char *Product_Name;
	int Quantity;
	float Price;
	struct table *next, *prev;
}Table, *Ptable;


int CreateProduct(Pkitchen *,Ptable *, char *, float, int);
int AddItems(Pkitchen *, char *, int);
int OrderItem(Pkitchen , Ptable ** ,int ,char *, int );
int RemoveItem(Pkitchen,Pkitchen_Gluten,Ptable **,int,char *,int);
int Happy_Moment(Pkitchen,int *);
int ChangeTable(Ptable **,Pkitchen, int );
int RemoveTable( Ptable **, int);
int RemoveTableWithDiscount(Ptable **, int table_number,int [],char *);
void Error_msg(char *);//print error 
int Check1(Pkitchen, char *);//check if the product name exists
int Check2(Ptable, char *);//check if the dish is on the table
void Delete_Tables(Ptable *);//remove table
void Delete_Product(Pkitchen );//remove product
Ptable Delete_Node(Ptable, Ptable);//remove specific node
void Discount(Ptable *head, char *,int arr[]);//check who deserves discount
#endif