#include <stdio.h>
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
 typedef struct{
    char Name[30];
    orderedDrink drink[9];
    totalAmountSpent total;
} patron;
void getOrder(patron *temp,int m);//Get order from user
void invoice(patron *temp,int m);//Invoice the user

int main(){
    patron Patron[3];int i;

     printf("Welcome to John Google's Bar\nPlease state your Order from the list of available drinks.\n");
    printf("|ID|\tName       \t|Category|\tPrice\t|\n ");
    for(i=0;i<9;i++){
    printf("|%d|\t%s\t|%c       |\t%d   \t|\n",i,name[i],category[i],unitCost[i]);}
    getOrder(Patron,3);
    invoice(Patron,3);

    return 0;}
    void invoice(patron *temp,int m){
        int i,j;
     for(j=0;j<m;j++){
            printf("Here is your invoice,%s :\n",temp->Name);
            printf("No\tItem          \tQnty\tUnit Cost\tCost/No tax\tTax\tCost w/Tax\n");
        for(i=0;i<9;i++){
             if(temp->drink[i].quantity==0){break;}
             printf("\n%d\t%s\t%d  \t%d       \t%d         \t%d \t%d\n",i+1,temp->drink[i].dname,temp->drink[i].quantity,temp->drink[i].unit_cost,temp->drink[i].costNoTax,temp->drink[i].taxPerQunty,temp->drink[i].costWithTax);
        }
        printf("\nTotal amount spent:                        \t%d         \t%d \t%d\n",temp->total.totalNoTax,temp->total.totalTax,temp->total.Withtax);
            temp+=1;
    }

}
void getOrder(patron *temp,int m){
    int n,i,j,g,r;
    for(r=0;r<3;r++){
    printf("Enter your name:");
    scanf("%s",temp->Name);
    printf("How many types of drinks do you want?:");
    scanf("%d",&n);
    temp->total.totalNoTax=0;
    temp->total.totalTax=0;
    temp->total.Withtax=0;
    for(i=0;i<n;i++){
        printf("Enter drink ID:");
        scanf("%d",&m);
        strcpy(temp->drink[i].dname,name[m]);
        printf("Quantity:");
        scanf("%d",&g);
        temp->drink[i].quantity=g;
        temp->drink[i].unit_cost=unitCost[m];
        temp->drink[i].costNoTax=temp->drink[i].quantity*unitCost[m];
        temp->drink[i].taxPerQunty=(category[m]=='A')?temp->drink[i].costNoTax*0.15:temp->drink[i].costNoTax*0.1;
        temp->drink[i].costWithTax= temp->drink[i].costNoTax+temp->drink[i].taxPerQunty;
        temp->total.totalNoTax+=temp->drink[i].costNoTax;
        temp->total.totalTax+=temp->drink[i].taxPerQunty;
        temp->total.Withtax+=temp->drink[i].costWithTax;
        j=i+1;
    }
    for(i=j;i<9;i++){
        temp->drink[i].quantity=0;
    }
    temp++;}
}
