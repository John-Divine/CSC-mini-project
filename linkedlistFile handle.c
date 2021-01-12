#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 const char name[9][15]={{"Martini       "},
                           {"Campari       "},
                           {"Johnnie Walker"},
                           {"Tuborg        "},
                           {"Amstel        "},
                           {"Orange Juice  "},
                           {"Apple Juice   "},
                           {"Coke          "},
                           {"Water         "}};
   const char category[10]={'A','A','A','A','A','N','N','N','N'};
   const int unitCost[9]={1500,1750,1500,1000,750,500,500,400,300};
   typedef struct{
    char dname[15];
    int quantity;
    int unit_cost;
    int costNoTax;
    int taxPerQunty;
    int costWithTax;
} orderedDrink;
typedef struct{
    int totalNoTax;
    int totalTax;
    int Withtax;
} totalAmountSpent;
typedef struct PatronNode *Link;
 struct PatronNode{
    char Name[30];
    orderedDrink drink[9];
    totalAmountSpent total;
    Link next;
};
void listPopulate_add(Link *head,FILE *fp);
void printList(Link head);

int main()
{
    int i;Link h;
    h=NULL;char filename[15];
    FILE *orderslip;
    printf("Welcome to John Google's Bar\nPlease state your Order from the list of available drinks.\n");
    printf("|ID|\tName       \t|Category|\tPrice\t|\n ");
    for(i=0;i<9;i++){
    printf("|%d|\t%s\t|%c      |\t%d   \t|\n",i,name[i],category[i],unitCost[i]);}
    printf("Please enter name of orderslip:");
    scanf("%s",&filename);
    if((orderslip=fopen(filename,"r"))!=NULL){
        listPopulate_add(&h,orderslip);
        printList(h);
    }
    else{exit(1);}
    return 0;
}
void listPopulate_add(Link *head,FILE *fp){
    Link temp;int i,m,j;char buff[40];


    while(fgets(buff,40,fp)!=NULL){
             if((temp=malloc(sizeof(*temp)))==NULL){
        printf("\nNot enough memory\n");
        exit(1);
    }
      temp->total.totalNoTax=0;
    temp->total.totalTax=0;
    temp->total.Withtax=0;
            printf("%s",buff);
        i=0;
    for(m=0;m<18;m+=2){

        temp->drink[i].quantity=(int)buff[m]-48;
        strcpy(temp->drink[i].dname,name[i]);
        temp->drink[i].unit_cost=unitCost[i];
        temp->drink[i].costNoTax=temp->drink[i].quantity*unitCost[i];
        temp->drink[i].taxPerQunty=(category[i]=='A')?temp->drink[i].costNoTax*0.15:temp->drink[i].costNoTax*0.1;
        temp->drink[i].costWithTax= temp->drink[i].costNoTax+temp->drink[i].taxPerQunty;
        temp->total.totalNoTax+=temp->drink[i].costNoTax;
        temp->total.totalTax+=temp->drink[i].taxPerQunty;
        temp->total.Withtax+=temp->drink[i].costWithTax;
        i+=1;
    }
    j=0;
    for(i=18;i<40;i++){
        if(buff[i]=='\n'){break;}
        temp->Name[j]=buff[i];
        j+=1;
    }
    temp->next=*head;
    *head=temp;
    }
}
void printList(Link head){
    Link temp=head;int i;

     while(temp!=NULL){
            printf("Here is your invoice,%s :\n",temp->Name);
            printf("No\tItem          \tQnty\tUnit Cost\tCost/No tax\tTax\tCost w/Tax\n");
        for(i=0;i<9;i++){
                if(temp->drink[i].quantity==0){continue;}
             printf("\n%d\t%s\t%d  \t%d       \t%d         \t%d \t%d\n",i+1,temp->drink[i].dname,temp->drink[i].quantity,temp->drink[i].unit_cost,temp->drink[i].costNoTax,temp->drink[i].taxPerQunty,temp->drink[i].costWithTax);
        }
        printf("\nTotal amount spent:                        \t%d         \t%d \t%d\n",temp->total.totalNoTax,temp->total.totalTax,temp->total.Withtax);
             temp=temp->next;
     }
}

