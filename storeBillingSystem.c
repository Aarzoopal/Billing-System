#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct items{      //struct is the user defined data type which can store multiple data type in it;
char item[20];
float price;
int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int numOfItem;
     struct items itm[50];
};
void generateBillHeader(char name[50] , char date[30])
{
   printf("\n\n");
   printf("\t\t  365 store" );
   printf("\nDate:%s",date);
   printf("\nInvoice To:%s",name);
   printf("\n");
   printf("---------------------------------------------\n");
   printf("Items\t\t");
   printf("qty\t\t");
   printf("Total\t\t");
   printf("\n--------------------------------------------");
   printf("\n\n");
}
void generateBillBody(char item[30], int qty,float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float gst=0.09*netTotal,grandtotal=netTotal+gst;
    printf("---------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
     printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
     printf("\n\t\t\t\t-------");
     printf("\nNet Total\t\t\t%.2f",netTotal);
     printf("\nGST @9\t\t\t\t%.2f","%",gst);
     printf("\n--------------------------------------------");
     printf("\nGrand Total\t\t\t%.2f",grandtotal);
     printf("\n-------------------------------------------\n");
}
int main()
{
    float total;
    int opt,n,invoiceFound=0;
    struct orders ord;
    char saveBill ='y',continueflag='y';
    char name[50];
    FILE *fp;
    struct orders order;
    while (continueflag=='y')
    {
        int total=0;
        float invoiceFound=0;

    
    
    printf("\t====================365 STORE===================");
    printf("\n");
    printf("\n\n Please select option accordingly: \t");
    printf("\n1.generate Invoice");
    printf("\n2.show all Inoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\n Your choice: \t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch (opt)
    {
        case 1:
        system("clear");
        printf("please enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);          // problem with fget it also attaching slash at end to solve this =>
        ord.customer[strlen(ord.customer)-1]=0;  //strlen gives the length of the customer and by minus 1 it removes the slash from the end
        strcpy(ord.date,__DATE__);            // standard string function to copy the string from one variable to another variable 
        printf("\nplease enter the no of items:\t");
        scanf("%d",&n);
        ord.numOfItem=n;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("please enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf(" please enter quantity :\t");
            scanf("%d",&ord.itm[i].qty);
            printf("please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total+=ord.itm[i].qty*ord.itm[i].price;
        }

        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItem;i++)
        {
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);

        }
        generateBillFooter(total);
        printf("\n Do you want to save the bill?[y/n] \t");
        scanf("%s",&saveBill);
        if(saveBill=='y')
        {
            fp= fopen("365storeBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            {
                printf("\n Succesfully saved");
            }
            else{
                printf("\n error saving");
               
            }
             fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp=fopen("365storeBill.dat","r");
        printf("\n ******Invoices******");
        while (fread(&order,sizeof(struct orders),1,fp))
        {
            float tot=0;
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItem;i++)
            {
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("\n Enter the name of the customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1]=0;
         system("clear");
         
        fp=fopen("365storeBill.dat","r");
        printf("\n ******Invoices of %s******",name);
        while (fread(&order,sizeof(struct orders),1,fp))
        {
            float tot=0;
            if(!strcmp(order.customer,name))
            {
                 generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItem;i++)
            {
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound=1;
            }
           
        }
        if(!invoiceFound)
        {
            printf("Invoice for %s does not exist",name);
        }
        fclose(fp);
        break;
        case 4:
        printf("\n\t\t Thank You");
        exit(0);
        break;

        default:
        printf("\n Sorry invalid option");
        break;

        

    }
    printf("\n do you want to continue[y/n: \t");
    scanf("%s",&continueflag);
    }

    
 
    
     return 0;
}