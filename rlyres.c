#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "conio2.h"
#include "rlyres.h"
#include<ctype.h>
int enterchoice()
{

    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("-");
    printf("\nSelect an option");
    printf("\n1-View Trains");
    printf("\n2-Book Ticket");
    printf("\n3-View Ticket");
    printf("\n4-Search Ticket No");
    printf("\n5-View All Bookings");
    printf("\n6-View Train Bookings");
    printf("\n7-Cancel Ticket");
    printf("\n8-Cancel Train");
    printf("\n9-Quit");
    printf("\n\nEnter choice:");
    scanf("%d",&choice);
    return choice;

}
void add_trains()
{
    FILE * fp;
    fp = fopen("c:\\Namnesh\\Cprojects\\database\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
       fp= fopen("c:\\Namnesh\\Cprojects\\database\\alltrains.dat","wb");
       fwrite(alltrains,4*sizeof(Train),1,fp);
       printf("File saved successfully\n");
       fclose(fp);
    }
    else{
        printf("File already present\n");
        fclose(fp);
    }

}
void view_trains(){
            int i;
            printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
            for(i=1;i<=80;i++)
            printf("-");
            FILE *fp;
            fp= fopen("c:\\Namnesh\\Cprojects\\database\\alltrains.dat","rb");
            Train tr;
            while(fread(&tr,sizeof(tr),1,fp)==1)
            {
               printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
            }
              printf("\n\n\n\n");
              fclose(fp);
           }
int check_train_no(char *train_no){
    FILE * fp = fopen("c:\\Namnesh\\Cprojects\\database\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp))
    {
        if(strcmp(tr.train_no,train_no)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int check_mobile_no(char *p_mob)
{

    if(strlen(p_mob)!=10)
    return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            {
                return 0;
            }
        p_mob++;
    }
    return 1;
}
Passenger * get_passenger_details() // passenger structure ka base address return krega hmko passenger ki details chhaye thi or wo structure m rhegi
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("PRESS 0 TO EXIT");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn; // static qki function khtm hone k bad bhi return krna h static ni bnaenge to destroy ho jayega ; ya to dyanamically malloc ki help se bhi bna skte the apn
    printf("ENTER PASSENGER NAME:");
    fflush(stdin);//qki buffer m enter choice k karn aaya wla enter abhi bhi pda hua h usko clear krne k lie;
    fgets(psn.p_name,20,stdin);// fgets ek \n dalta h null char k phle jse n|a|m|n|e|s|h|\n|\0
    char * pos;
    pos = strchr(psn.p_name,'\n');
    *pos='\0'; // jha tk \0 rhe wha tk hi read krega.
    if(strcmp(psn.p_name,"0")==0)//yha p 0 as a string compare krenge qki nam m zero enter krege to bhi exit hona chhaye or wo as a string rhega.
    {
        textcolor(RED);
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    int valid;
    printf("Enter Gender (M/F):");
    do{
        valid =1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;

        }
        if(psn.gender!='M'&&psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR GENDER SHOULD BE M/F (IN UPPERCASE) ");
            valid = 0;
            getch();
            gotoxy(20,2);
            printf(" \b");// 19 ki definate string h hmko pta h hm last m mtlb 19 p jak ek bar space denge jisse ip mit jaega or \b ki help se wps whi aa jeyaega.
            textcolor(YELLOW);
        }

    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");//purane gender error messege ki mitane k lie ni to purana error msg shi dalne k bad bhi aate hi rhega.
    gotoxy(1,3);
    printf("ENTER TRAIN NUMBER:");
    do{
        fflush(stdin);
        scanf("%s",psn.train_no);
    if(strcmp(psn.train_no,"0")==0)
       {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;

       }
      valid = check_train_no(psn.train_no);
      if(valid==0)
      {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR! INVALID TRAIN NUMBER ");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(20,3);
            printf(" \b");
            textcolor(YELLOW);
      }

    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,4);
    printf("ENTER TRAVELLING CLASS (FIRST AC: F , SECOND AC: S ):");
     do{
        valid =1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;

        }
        if(psn.p_class!='F'&&psn.p_class!='S')
            {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR! CLASS SHOULD BE S/F (IN UPPERCASE) ");
            valid = 0;
            getch();
            gotoxy(54,4);
            printf(" \b");// 19 ki definate string h hmko pta h hm last m mtlb 19 p jak ek bar space denge jisse ip mit jaega or \b ki help se wps whi aa jeyaega.
            textcolor(YELLOW);
            }
     }while(valid==0);
          gotoxy(1,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(1,5);
    printf("ENTER ADDRESS:");
    fflush(stdin);
    fgets(psn.address,20,stdin);
    *pos='\0'; // jha tk \0 rhe wha tk hi read krega.
    if(strcmp(psn.address,"0")==0)
    {
        textcolor(RED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    printf("ENTER YOUR AGE:");
    do{
        valid =1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.age<0||psn.age>125)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR! AGE SHOULD BE POSITIVE AND VALID ");
            valid = 0;
            getch();
            gotoxy(16,6);
            printf("\t\t\t\t\t\t");
            gotoxy(16,6);
            textcolor(YELLOW);

        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t\t\t");
    gotoxy(1,7);
    printf("ENTER MOBILE NO:");
    do{
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos = strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos = '\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(RED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_mobile_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR! INVALID MOBILE NUMBER ");
            getch();
            gotoxy(17,7);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(17,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
     printf("\t\t\t\t\t\t\t\t");
     gotoxy(1,8);
    return &psn;
}
int get_booked_ticket_count(char *train_no,char tc)
{
    Passenger pr;
    static int count;
    printf("train no of passenger is %s",pr.train_no);
    getch();
    printf("the no recieved is %s",train_no);
    getch();
    printf("Im in the begining of booked ticket count");
    getch();
    FILE *fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    if(fp == NULL)
        {
            printf("i cant open file in get booked ticket count");
            getch();
            return 0;
        }
      printf("i can open file in get booked ticket count");
      getch();
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
         printf("i can enter in while loop in get booked ticket count");
         getch();
        if(strcmp(pr.train_no,train_no)==0 &&(pr.p_class==tc)){
                  printf("i can enter in if of get booked ticket count before inc");
                  getch();
                  ++count;
                  printf("i can enter in if of get booked ticket count after inc");
                  getch();
        }
        else{
            printf("i m in else");
            getch();
        }

    }
    fclose(fp);
    printf("Im in the end of booked ticket count");
    getch();
    printf("i return count in booked ticket count as %d",count);
    getch();
    return count;

}
int last_ticket_no()
{
    FILE *fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    printf("Im in the begining of last ticket no\n");
    getch();
    if(fp == NULL)
    return 0;
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    printf("Im in the end of last ticket no");
    getch();
    return pr.ticket_no;

}
//above 2 functions are called by this fumction book_ticket()

int book_ticket(Passenger p)
{
    int ticket_count;
    int ticket_no;
    printf("\nIm in the begining of book ticket");
    getch();
    ticket_count  = get_booked_ticket_count(p.train_no,p.p_class);
    printf("\nticket no this time is %d",ticket_count);
    if(ticket_count==3)
    {
        textcolor(LIGHTRED);
        printf("All seats in train no %s in class %c are full !",p.train_no,p.p_class);
        return -1;
    }

    //now check last ticket no konsa h
    ticket_no = last_ticket_no()+1;
    p.ticket_no = ticket_no;
    //now booking write krne wli file open krege
    FILE *fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","ab");
    if(fp == NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;

    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    printf("\nIm in the end of booked ticket\n");
    getch();
    return ticket_no;

}
int accept_ticket_no()
{
    int ticket_no,valid;
    printf("Enter a valid ticket no");
    fflush(stdin);
    scanf("%d",&ticket_no);
    do{
        valid = 1;
        if(ticket_no == 0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input....!");
            getch();
            textcolor(LIGHTGREEN);
            clrscr();
            return 0;
        }
        if(ticket_no < 0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Ticket number should be positive!");
            getch();
            valid = 0;
            getch();
            gotoxy(24,1);
            printf("\t\t\t\t\t\t\t");
            gotoxy(24,1);
            textcolor(LIGHTGREEN);
        }
    }while(valid==0);
    return ticket_no;
}
void view_ticket(int ticket_no)
{
     FILE * fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");

     if(fp==NULL)
     {
        textcolor(LIGHTRED);
        printf("NO bOOKINGS DONE YET");
        return ;
     }
     Passenger p;
     int found=0;
     while(fread(&p,sizeof(p),1,fp)==1)
     {
        if(p.ticket_no == ticket_no)
        {
           printf("\nNAME:%s\nGENDER:%c\nTRAVELLING CLASS:%c\nAGE:%d\nADDRESS:%sMOBILE NO:%s\nTICKET NO:%d\nTRAIN NO:%s",p.p_name,p.gender,p.p_class,p.age,p.address,p.mob_no,p.ticket_no,p.train_no);
           printf("\n\n");
           found=1;
           break;
        }

     }
     if(found==0)
     {
        textcolor(LIGHTRED);
        printf("\nNo details of the ticket no %d found",ticket_no);
     }
     fclose(fp);
     return ;
}
char * accept_mob_no()
{
    static char mob_no[12];
    char * pos;
    int valid;
    printf("enter valid mobile no:");
    do{
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos = strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos = '\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(RED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf(" Cancelling Input !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_mobile_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR! INVALID MOBILE NUMBER ");
            getch();
            gotoxy(27,1);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(27,1);
            textcolor(YELLOW);
        }
         }while(valid==0);
         clrscr();
         return mob_no;
}
int * get_ticket_no(char * p_mob_no)
{
    int count = 0;
    FILE * fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("SORRY FILE CAN'T BE OPENED");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(p_mob_no,pr.mob_no)==0)
        {
            ++count;
        }
    }
    if(!count)
    {
        fclose(fp);
        return NULL;
    }
   int *p = (int*)malloc((count+1)*sizeof(int));
    rewind(fp);
    int i = 0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(p_mob_no,pr.mob_no)==0)
        {
         *(p+i)=pr.ticket_no;
           i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
void view_all_tickets(char * pmob_no,int * pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(RED);
        printf("Sorry ! THERE ARE NO TICKETS BOOKED ANGAIST THIS NO.");
        textcolor(WHITE);
        printf("\n press any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are the tickets booked for the mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NUMBERS\n");
    printf("---------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        printf("\n%d",*(pticket_no+i));
    }
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}
char * accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("PRESS 0 TO EXIT");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("ENTER TRAIN NUMBER:");
    do{
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Canceling input..!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid = check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR! INVALID TRAIN NUMBER ");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}

void view_bookings(char * train_no)
{
    int found = 0;
    FILE * fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("SORRY FILE CAN'T BE OPENED");
        return ;
    }
    Passenger pr;
    int i;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1;i<=80;i++)
    {
      printf("-");
    }
    int row = 3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(train_no,pr.train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticket_no,pr.p_class,pr.p_name);//nam ki length or tab k karn  prblm n ho
            gotoxy(41,row); // console p heading ki calculation krk drct name k neeche cursor le aaenge.
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found = 1;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNO DETAILS OF BOOKING IN TRAIN NI %s IS FOUND",train_no);
    }
    textcolor(WHITE);
    printf("\n\nPRESS ANY KEY TO EXIT");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}


int cancel_ticket(int ticket_no)
{
    int result;
    FILE * fp1 = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("NO BOOKINGS DONE YET");
        return -1;
    }
    FILE * fp2 = fopen("c:\\Namnesh\\Cprojects\\database\\temp.txt","wb");
    Passenger pr;
    int found = 0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticket_no==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("c:\\Namnesh\\Cprojects\\database\\temp.txt");
    }
    else
    {
        result = remove("c:\\Namnesh\\Cprojects\\database\\allbookings.txt");
        if(result!=0)
            return 2;
        result = rename("c:\\Namnesh\\Cprojects\\database\\temp.txt","c:\\Namnesh\\Cprojects\\database\\allbookings.txt");
        if(result!=0)
            return 2;
    }
    return found;
}
int cancel_train(char * train_no)
{
    int result;
    FILE * fp1;
    fp1 = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("NO BOOKINGS DONE YET");
        return -1;
    }
    FILE * fp2 = fopen("c:\\Namnesh\\Cprojects\\database\\temp.txt","wb");
    Passenger pr;
    int found = 0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(!found)
    {
        remove("c:\\Namnesh\\Cprojects\\database\\temp.txt");
    }
     else
    {
        result = remove("c:\\Namnesh\\Cprojects\\database\\allbookings.txt");
        if(result!=0)
            return 2;
        result = rename("c:\\Namnesh\\Cprojects\\database\\temp.txt","c:\\Namnesh\\Cprojects\\database\\allbookings.txt");
        if(result!=0)
            return 2;
    }
        return found;
}

void view_all_bookings()
{
    textcolor(LIGHTGREEN);
    int i;
    FILE *fp = fopen("c:\\Namnesh\\Cprojects\\database\\allbookings.txt","rb");
    if(fp == NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry ! File cannot be opened");
        return;
    }
    Passenger p;
    printf("TICKET NO\tTRAIN\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1;i<=80;i++)
        printf("-");
    int row =5;
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        printf("%d\t\t%s\t%c\t%s",p.ticket_no,p.train_no,p.p_class,p.p_name);
        gotoxy(41,row);
        printf("\t%c\t%d\t%s\n",p.gender,p.age,p.mob_no);
        row++;
    }
    fclose(fp);
    return ;
}
