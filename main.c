#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include"rlyres.h"
int main(){
  int choice,ticket_no,result;
  char * pmob_no,*ptrain_no;
  int * pticket_no;
  Passenger * ptr;
  add_trains();
  while(1)
  {
      choice=enterchoice();
      clrscr();
      if(choice==9)
        exit(0);
      switch(choice){
      case 1:
           view_trains();
           getch();
           clrscr();
           break;
      case 2:
           ptr = get_passenger_details();
           clrscr();
           if(ptr!=NULL)
           {
             ticket_no = book_ticket(*ptr);

           if(ticket_no == -1)
           {
               textcolor(LIGHTRED);
               printf("BOOKING FAILED");
               getch();
           }
           else{
            textcolor(LIGHTGREEN);
            printf("TICKER BOOKED SUCCESSFULLY BOOKED\nYOUR TICKET NO IS %d\n",ticket_no);
            getch();
           }
           textcolor(WHITE);
           printf("PRESS ANY KEY TO RETURN TO MAIN SCREEN");
           getch();
           clrscr();
           }
           break;
      case 3:
           clrscr();
           ticket_no=accept_ticket_no();
           if(ticket_no!=0)
           view_ticket(ticket_no);
           textcolor(WHITE);
           printf("\nPress any key to go back to the main screen");
           getch();
           clrscr();
           break;
      case 4:
            clrscr();
            pmob_no = accept_mob_no();
            if(pmob_no!=NULL)
            {
              pticket_no=get_ticket_no(pmob_no);
              view_all_tickets(pmob_no,pticket_no);
            }
            clrscr();
           break;
      case 5:
           clrscr();
                gotoxy(28,1);
                textcolor(YELLOW);
                printf("View All Bookings\n");
                textcolor(LIGHTGREEN);
                for(int i=1;i<=80;i++)
                    printf("-");
                view_all_bookings();
                textcolor(WHITE);
                    printf("\nPress any key to go back to the main screen.................");
                getch();
                clrscr();
                break;
      case 6:
             clrscr();
             ptrain_no = accept_train_no();
             if(ptrain_no!=NULL)
             {
                 view_bookings(ptrain_no);
             }
             getch();
             clrscr();
             break;
      case 7:
            clrscr();
            ticket_no = accept_ticket_no();
            if(ticket_no!=0)
            {
               result = cancel_ticket(ticket_no);
               if(result == 0)
               {
                   textcolor(LIGHTRED);
                   printf("sorry no tickets booked against ticket no %d",ticket_no);
               }
               else if(result==1)
               {
                   textcolor(LIGHTRED);
                   printf("Ticket no is %d is successfully canceled",ticket_no);
               }
               else if(result == 2)
               {
                   textcolor(LIGHTRED);
                   printf("Sorry ! error in cancellation try again");
               }
                   textcolor(WHITE);
                   printf("\n\nPress any key to go back to main screen");
            }
                getch();
                clrscr();
                break;
      case 8:

                clrscr();
                ptrain_no = accept_train_no();
                if(ptrain_no!=NULL)
                {
                   result = cancel_train(ptrain_no);
                   if(result == 0)
                   {
                       textcolor(LIGHTRED);
                       printf("sorry no tickets booked in train no %s",ptrain_no);
                   }
                   else if(result==1)
                   {
                       textcolor(LIGHTRED);
                       printf("Train no %s is successfully canceled",ptrain_no);
                   }
                   else if(result == 2)
                   {
                       textcolor(LIGHTRED);
                       printf("Sorry ! error in cancellation try again");
                   }
                       textcolor(WHITE);
                       printf("\n\nPress any key to go back to main screen");
                }
                    getch();
                    clrscr();
                    break;


      default:
             textcolor(LIGHTRED);
             printf("Wrong Choice! Try Again\n");
             getch();
             clrscr();
      }
  }
}
