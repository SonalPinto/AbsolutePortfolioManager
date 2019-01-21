#ifndef INTERFACE
#define INTERFACE

#include "portfolio.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Create_Portfolio();
void View_Portfolio(char *title);
void Delete_Portfolio();
void Run_dividend(Portfolio &p);
void Backup_Portfolio(char *title, int flg=0);
void Restore_Portfolio(char *title);


void Run_program()
{
	int option;
   do
   {
      clrscr();
      Render_Title("Absolute Portfolio Manager");
      Render_Title("Main Menu");
      cout<<"\n\n";
      textcolor(LIGHTCYAN);
      cprintf("1.Create new Portfolio");cout<<"\n";
      cprintf("2.Select Portfolio");cout<<"\n";
      cprintf("3.Delete Portfolio");cout<<"\n\n";
      cprintf("4.Update EOD Prices");cout<<"\n\n";
      cprintf("5.Backup Portfolio");cout<<"\n";
      cprintf("6.Restore Portfolio");cout<<"\n\n";
      cprintf("7.ReadMe");cout<<"\n";
      cprintf("8.About");cout<<"\n\n";
      cprintf("0.Exit");
      Enter_command(option);

      clrscr();
      Render_Title("Absolute Portfolio Manager");

      if(option==1)
      {
      	Create_Portfolio();
      }
      else if(option==2)
      {
         int menuflag=0;
         do
         {
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("Select Portfolio");

            textcolor(LIGHTGREEN);
            cout<<"\n\n\n\n";
            cprintf("Enter the Portfolio Name: ");gets(title);
            strupr(title);
            cout<<"\n\n\n";
            textcolor(LIGHTCYAN);
            cprintf("1.Continue");cout<<endl;
            cprintf("2.Re-enter Data");cout<<endl;
            cprintf("0.Cancel");
            Enter_command(menuflag);
         }while(menuflag==2);

         if(menuflag==1)
         {
            View_Portfolio(title);
            Backup_Portfolio(title,1);
         }
      }
      else if(option==3)
      {
      	Delete_Portfolio();
      }
      else if(option==4)
      {
      	  clrscr();
           Render_Title("Absolute Portfolio Manager");
           Download_Bhavcopy();
           textcolor(LIGHTGREEN);
           cout<<"\n\n\n";
           cprintf("Press any key to continue...");
           getch();
      }
      else if(option==5)
      {
      	int menuflag=0;
         do
         {
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("Select Portfolio");

            textcolor(LIGHTGREEN);
            cout<<"\n\n\n\n";
            cprintf("Enter the Portfolio Name: ");gets(title);
            strupr(title);
            cout<<"\n\n\n";
            textcolor(LIGHTCYAN);
            cprintf("1.Continue");cout<<endl;
            cprintf("2.Re-enter Data");cout<<endl;
            cprintf("0.Cancel");
            Enter_command(menuflag);
         }while(menuflag==2);

         if(menuflag==1)
         {
               Backup_Portfolio(title);
         }
      }
      else if (option==6)
      {
      	int menuflag=0;
         do
         {
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("Select Portfolio");

            textcolor(LIGHTGREEN);
            cout<<"\n\n\n\n";
            cprintf("Enter the Portfolio Name: ");gets(title);
            strupr(title);
            cout<<"\n\n\n";
            textcolor(LIGHTCYAN);
            cprintf("1.Continue");cout<<endl;
            cprintf("2.Re-enter Data");cout<<endl;
            cprintf("0.Cancel");
            Enter_command(menuflag);
         }while(menuflag==2);

         if(menuflag==1)
         {
               Restore_Portfolio(title);
         }
      }
      else if(option==7)
      {
      	  system("start Readme\\ReadMe.htm");
      }
      else if(option==8)
      {
      	Render_Title("Absolute Portfolio Manager");
         cout<<"\n\n\n";
         textcolor(LIGHTGREEN);

			cprintf("It is a DOS32 application that helps one to manage his portfolio containing");
         cout<<endl;
         cprintf("the stocks traded on NSE and BSE.");cout<<endl;
			cprintf("Program created using Borland C++ v.5.02");cout<<"\n\n";

			cprintf("Created By :");cout<<"\n\t";
    		cprintf("*Leaf cutter");cout<<"\n\t";
         cprintf("*The Dark Knight");cout<<"\n\n";
         cprintf("Special Thanks to the programmers of Curl & Unzip and Mr. SHT for");
         cout<<endl;
         cprintf("his technical assistance.");
         getch();
      }
      else if(option==0)
      {
           clrscr();
           Render_Title("Absolute Portfolio Manager");
           char q;
           textcolor(LIGHTRED);
           cout<<"\n\n\n\n";cprintf("Do you really wish to exit?(Y/N): ");
           cin>>q;
           if(q=='y' || q=='Y')option=0;
           else option=-1;
      }
   }while(option!=0);
}

void Backup_Portfolio(char *title, int flg)
{
	int interflag=0;
   char add[64]="Data\\";
   char backup_add[64];
   char backup_hol[64];
   strcat(add,title);
   strcpy(port_add, add);
   strcpy(hold_add, add);

   strcat(port_add,"_t.dat");
   strcat(hold_add,"_h.dat");

   fstream f1(port_add, ios::binary|ios::nocreate);
   fstream f2(hold_add, ios::binary|ios::nocreate);

   if(!f1 && !f2)interflag=1;
   f1.close();
   f2.close();

   if(sizeoffile(port_add)!=0 && sizeoffile(hold_add))interflag=0;

   if(interflag==0)
   {
		strcpy(backup_add,port_add);
      strcat(backup_add,".bak");
      strcpy(backup_hol,hold_add);
      strcat(backup_hol,".bak");
      Transaction t;
      Holding h;
      ifstream file(port_add,ios::binary);
      ifstream fileh(hold_add,ios::binary);
      ofstream fob(backup_add,ios::binary);
      ofstream fobh(backup_hol,ios::binary);
      file.read((char*)&t,sizeof(Transaction));
      while(!file.eof())
      {
         fob.write((char*)&t,sizeof(Transaction));
      	file.read((char*)&t,sizeof(Transaction));
      }
      fileh.read((char*)&h,sizeof(Holding));
      while(!fileh.eof())
      {
         fobh.write((char*)&h,sizeof(Holding));
      	fileh.read((char*)&h,sizeof(Holding));
      }
      file.close();
      fileh.close();
      fob.close();
      fobh.close();
      if(flg==0)
      {
         clrscr();
         Render_Title("Absolute Portfolio Manager");cout<<"\n\n\n";
         cprintf("Backup Created!!");
         getch();
      }
   }
   else
   {
      if(flg==0)
      {
         cout<<"\n\n";cprintf("Portfolio not found!!");
         cout<<"\n\n";cprintf("Press a key to return to main menu");
         getch();
      }
   }
}

void Restore_Portfolio(char *title)
{
	int interflag=0;
   char add[64]="Data\\";
   char backup_add[64];
	char backup_hol[64];
   strcat(add,title);
   strcpy(port_add, add);
   strcpy(hold_add, add);

   strcat(port_add,"_t.dat");
   strcat(hold_add,"_h.dat");

   fstream f1(port_add, ios::binary|ios::nocreate);
   fstream f2(hold_add, ios::binary|ios::nocreate);

   if(!f1 && !f2)interflag=1;
   f1.close();
   f2.close();

   if(sizeoffile(port_add)!=0 && sizeoffile(hold_add))interflag=0;

   if(interflag==0)
   {
		strcpy(backup_add,port_add);
      strcat(backup_add,".bak");
      strcpy(backup_hol,hold_add);
      strcat(backup_hol,".bak");
      clrscr();
     	Render_Title("Absolute Portfolio Manager");
    	char q;
      textcolor(LIGHTRED);
      cout<<"\n\n\n\n";cprintf("Do you really wish to restore this portfolio?(Y/N): ");
      cin>>q;
      if(q=='y' || q=='Y')
      {
      	remove(port_add);
         remove(hold_add);
	      rename(backup_add,port_add);
         rename(backup_hol,hold_add);
         clrscr();
	     	Render_Title("Absolute Portfolio Manager");cout<<"\n\n\n";
         cprintf("Portfolio Restored!!");
         getch();
      }
	}
   else
   {
      cout<<"\n\n";cprintf("Portfolio not found!!");
      cout<<"\n\n";cprintf("Press a key to return to main menu");
      getch();
   }
}


void Create_Portfolio()
{
	int menuflag=0;
   do
   {
      clrscr();
      Render_Title("Absolute Portfolio Manager");
      Render_Title("New Portfolio");

      textcolor(LIGHTRED);
      cout<<"\n\n\n\n";
      cprintf("Enter the Portfolio Name: ");gets(title);
      strupr(title);
      cout<<"\n\n\n";
      textcolor(LIGHTCYAN);
      cprintf("1.Continue");cout<<endl;
      cprintf("2.Re-enter Data");cout<<endl;
      cprintf("0.Cancel");
      Enter_command(menuflag);
	}while(menuflag==2);

	if(menuflag==1)
   {
   	char add[64]="Data\\";
      strcat(add,title);
      strcpy(port_add, add);
      strcpy(hold_add, add);
      strcpy(divi_add, add);
      strcpy(sett_add, add);

      strcat(port_add,"_t.dat");
      strcat(hold_add,"_h.dat");
      strcat(divi_add,"_d.dat");
      strcat(sett_add,"_s.txt");

      fstream f1(port_add, ios::binary|ios::out|ios::trunc);
      fstream f2(hold_add, ios::binary|ios::out|ios::trunc);
      fstream f3(divi_add, ios::binary|ios::out|ios::trunc);
      fstream f4(sett_add, ios::out|ios::trunc);

      f1.close();
      f2.close();
      f3.close();
      f4.close();
      Create_defaultSettings(sett_add);
      View_Portfolio(title);
   }
}


void Delete_Portfolio()
{
	int menuflag=0;
   do
   {
      clrscr();
      Render_Title("Absolute Portfolio Manager");
      Render_Title("Delete Portfolio");

      textcolor(LIGHTGREEN);
      cout<<"\n\n\n\n";
      cprintf("Enter the Portfolio Name to delete: ");gets(title);
      strupr(title);
      cout<<"\n\n\n";
      textcolor(LIGHTCYAN);
      cprintf("1.Continue");cout<<endl;
      cprintf("2.Re-enter Data");cout<<endl;
      cprintf("0.Cancel");
      Enter_command(menuflag);
	}while(menuflag==2);

   if(menuflag==1)
   {
      int interflag=0;
   	char add[64]="Data\\";
      strcat(add,title);
      strcpy(port_add, add);
      strcpy(hold_add, add);
		strcpy(divi_add, add);
      strcpy(sett_add, add);

      strcat(port_add,"_t.dat");
      strcat(hold_add,"_h.dat");
      strcat(divi_add,"_d.dat");
      strcat(sett_add,"_s.txt");

      fstream f1(port_add, ios::binary|ios::nocreate);
      fstream f2(hold_add, ios::binary|ios::nocreate);
      fstream f3(divi_add, ios::binary|ios::nocreate);
      fstream f4(sett_add, ios::nocreate);

      if(!f1 && !f2 && !f3 && !f4)interflag=1;
      f1.close();
      f2.close();
      f3.close();
      f4.close();
      if(sizeoffile(port_add)!=0 && sizeoffile(hold_add)!=0 && sizeoffile(divi_add)!=0)interflag=0;

      clrscr();
      Render_Title("Absolute Portfolio Manager");
      Render_Title("Delete Portfolio");
      cout<<"\n\n\n\n";
      textcolor(LIGHTRED);
      if(interflag==0)
      {
         char ch;
         cout<<"\n\n";
         cprintf("Are you sure you want to DELETE portfolio?(Y/N): ");
         cin>>ch;
         if(ch=='y' || ch=='Y')
         {
            remove(port_add);
            remove(hold_add);
            remove(divi_add);
            remove(sett_add);
            cout<<"\n\n";cprintf("Portfolio deleted!!");
            cout<<"\n\n";cprintf("Press a key to return to main menu");
            getch();
         }
      }
      else
      {
         cout<<"\n\n";cprintf("Portfolio not found!!");
         cout<<"\n\n";cprintf("Press a key to return to main menu");
         getch();
      }
   }
}

void View_Portfolio(char *title)
{
   	int interflag=0;
   	char add[64]="Data\\";
      strcat(add,title);
      strcpy(port_add, add);
      strcpy(hold_add, add);
      strcpy(divi_add, add);
      strcpy(sett_add, add);

      strcat(port_add,"_t.dat");
      strcat(hold_add,"_h.dat");
      strcat(divi_add,"_d.dat");
      strcat(sett_add,"_s.txt");

      fstream f1(port_add, ios::binary|ios::nocreate);
      fstream f2(hold_add, ios::binary|ios::nocreate);
      fstream f3(divi_add, ios::binary|ios::nocreate);
      fstream f4(sett_add, ios::nocreate);

      if(!f1 && !f2 && !f3 && !f4)interflag=1;
      f1.close();
      f2.close();
      f3.close();
      f4.close();
      if(sizeoffile(port_add)!=0 && sizeoffile(hold_add)!=0)interflag=0;

      if(interflag==0)
      {
         int interflag1=0;
         do
         {
            Portfolio port(port_add, hold_add,divi_add,sett_add);
            port.Load_Settings();
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title(title);
            port.Output_portfolio();

            textcolor(LIGHTCYAN);
            cout<<"\n\n\n";
            cprintf("1.Add Transaction");cout<<endl;
            cprintf("2.View Transaction History");cout<<endl;
            cprintf("3.Dividend");cout<<endl;
            cprintf("4.View Portfolio Percentage");cout<<endl;
            cprintf("5.Settings");cout<<endl;
            cprintf("0.Back to Main Menu");
            Enter_command(interflag1);

            if(interflag1==1)
            {
               Transaction t;
               int interflag2;

            	do
               {
                  clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("New Transaction");
                  cout<<"\n\n";
                  cprintf("Transaction Type");cout<<"\t";cprintf("Stock Exchange");cout<<"\n";
                  textcolor(LIGHTGREEN);
                  cprintf("1.Buy");cout<<"\t\t\t";cprintf("1.NSE");cout<<endl;
                  cprintf("2.Sell");cout<<"\t\t\t";cprintf("2.BSE");cout<<endl;
                  cprintf("3.Bonus");cout<<endl;
                  cprintf("4.Split");cout<<endl;
                  t.Input();
                  textcolor(LIGHTCYAN);
                  cout<<"\n\n";
                  cprintf("1.Continue");cout<<endl;
                  cprintf("2.Re-enter Data");cout<<endl;
                  cprintf("0.Cancel");
                  Enter_command(interflag2);
               }while(interflag2==2);

               if(interflag2==1)
               {
                  clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("New Transaction");
                  textcolor(LIGHTRED);
               	int errorflag=0;
                  if(t.get_type()<1 || t.get_type()>4){cprintf("Input Error: Incorrect TRANSACTION TYPE entered");cout<<endl;errorflag++;}
                  if(t.get_exchange()!=1 && t.get_exchange()!=2){cprintf("Input Error: Incorrect STOCK EXCHANGE entered");cout<<endl;errorflag++;}
                  if(t.get_type()==3 || t.get_type()==4)
                  	if(port.Check_holding(t.get_name())!=0)
                     	{cprintf("Input Error: Entered Scrip name is not a current holding");cout<<endl;errorflag++;}

                  if(port.Get_cmp_n(t.get_name(),5)==0 && port.Get_cmp_b(t.get_name(),7)==0)
                              	{cprintf("Input Error: Entered Scrip name does not exist");cout<<endl;errorflag++;}
                  if(Date_formatcheck(t.get_date())==false){cprintf("Input Error: Date has incorrect format");cout<<endl;errorflag++;}

                  if(t.get_type()==1 && t.get_total()>cash){cprintf("Input Error: Insufficient Balance");cout<<endl;errorflag++;}
                  if(errorflag==0)port.Input(t);
                  else
                  {
                     cout<<"\n\n\n";
                  	cprintf("Press any key to continue");
                     getch();
                  }
               }
            }

            else if(interflag1==2)
            {
            	char name[64];
               int interflag2=0;
               do
               {
                  clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("Transaction History");
                  cout<<"\n\n\n\n";
                  textcolor(LIGHTGREEN);
                  cprintf("Enter the scrip name: ");
                  gets(name);
                  cout<<"\n\n\n";
                  textcolor(LIGHTCYAN);
                  cprintf("1.Continue");cout<<endl;
                  cprintf("2.Re-enter Data");cout<<endl;
                  cprintf("0.Cancel");
                  Enter_command(interflag2);
               }while(interflag2==2);

               if(interflag2==1)
               {
                  int interflag3=0;
                  int total_tr=0;
                  strupr(name);
                  do
                  {
                     clrscr();
                     Render_Title("Absolute Portfolio Manager");
                     Render_Title("Transaction History");
                     cout<<"\n\n";
                     total_tr=port.Output_transaction_history(name);
                     if(total_tr==0)
                     {
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Transaction History");
                        cout<<"\n\n\n\n";
                        textcolor(LIGHTRED);
                        cprintf("Transaction History unavailable for <%s>!!", name);
                        cout<<"\n\n";
                        cprintf("Press any key to continue...");
                        getch();
                        interflag3=0;
                     }
                     else
                     {
                        cout<<"\n\n\n";
                        textcolor(LIGHTCYAN);
                        cprintf("1.Edit");cout<<endl;
                        cprintf("2.Delete");cout<<endl;
                        cprintf("0.Back");
                        Enter_command(interflag3);
                     }

                     if(interflag3==1 && total_tr>0)
                     {
                        Transaction t;
                        int sln, interflag4=0;
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Transaction History");
                        cout<<"\n\n";
                        port.Output_transaction_history(name);
                        cout<<"\n\n\n";

                        textcolor(LIGHTGREEN);
                        cprintf("Enter the serial number(as above): ");
                        cin>>sln;

                        if(sln>0 && sln<=total_tr)
                        {
                           do
                           {
                              clrscr();
                              Render_Title("Absolute Portfolio Manager");
                              Render_Title("Transaction History");
                              cprintf("Transaction Type");cout<<"\t";cprintf("Stock Exchange");cout<<"\n";
                              textcolor(LIGHTGREEN);
                              cprintf("1.Buy");cout<<"\t\t\t";cprintf("1.NSE");cout<<endl;
                              cprintf("2.Sell");cout<<"\t\t\t";cprintf("2.BSE");cout<<endl;
                              cprintf("3.Bonus");cout<<endl;
                              cprintf("4.Split");cout<<endl;
                              t.Input();
                              cout<<"\n\n\n";
                              textcolor(LIGHTCYAN);
                              cprintf("1.Continue");cout<<endl;
                              cprintf("2.Re-enter Data");cout<<endl;
                              cprintf("0.Cancel");
                              Enter_command(interflag4);
                           }while(interflag4==2);

                           if(interflag4==1)
                           {
                              clrscr();
                              Render_Title("Absolute Portfolio Manager");
                              Render_Title("Transaction History");
                              textcolor(LIGHTRED);
                              int errorflag=0;
                              if(t.get_type()<1 || t.get_type()>4){cprintf("Input Error: Incorrect TRANSACTION TYPE entered");cout<<endl;errorflag++;}
                              if(t.get_exchange()!=1 && t.get_exchange()!=2){cprintf("Input Error: Incorrect STOCK EXCHANGE entered");cout<<endl;errorflag++;}
                              if(t.get_type()==3 || t.get_type()==4)
                              if(port.Check_holding(t.get_name())!=0)
                                 {cprintf("Input Error: Entered Scrip name is not a current holding");cout<<endl;errorflag++;}

                              if(port.Get_cmp_n(t.get_name(),5)==0 && port.Get_cmp_b(t.get_name(),7)==0)
                              	{cprintf("Input Error: Entered Scrip name does not exist");cout<<endl;errorflag++;}
                              if(Date_formatcheck(t.get_date())==false){cprintf("Input Error: Date has incorrect format");cout<<endl;errorflag++;}

                              if(errorflag==0)port.Replace_transaction(t,name,sln);
                              else
                              {
                                 cout<<"\n\n\n";
                                 cprintf("Press any key to continue");
                                 getch();
                              }
                           }
                        }

                        else
                        {
                           clrscr();
                           Render_Title("Absolute Portfolio Manager");
                           Render_Title("Transaction History");
                           textcolor(LIGHTRED);
                           cout<<"\n\n\n\n";
                           cprintf("Serial number out of bounds!!");
                           cout<<"\n\n";
                           cprintf("Press any key to continue...");
                           getch();
                        }
                     }

                     if(interflag3==2 && total_tr>0)
                     {
                        Transaction t;
                        int sln;
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Transaction History");
                        cout<<"\n\n";
                        port.Output_transaction_history(name);
                        cout<<"\n\n\n";

                        textcolor(LIGHTGREEN);
                        cprintf("Enter the serial number(as above): ");
                        cin>>sln;

                        if(sln>0 && sln<=total_tr)
                        {
                           clrscr();
                           Render_Title("Absolute Portfolio Manager");
                           Render_Title("Transaction History");
                           cout<<"\n\n";

                           textcolor(LIGHTRED);
                           char ch;
                           cout<<"\n\n";
                           cprintf("Are you sure you want to DELETE transaction?(Y/N): ");
                           cin>>ch;
                           if(ch=='y' || ch=='Y')
                           {
                              int tiny_flag;
                              tiny_flag=port.Delete_transaction(name, sln);
                              if(tiny_flag==0)interflag3=0;
                           }
                        }

                        else
                        {
                           clrscr();
                           Render_Title("Absolute Portfolio Manager");
                           Render_Title("Transaction History");
                           textcolor(LIGHTRED);
                           cout<<"\n\n\n\n";
                           cprintf("Serial number out of bounds!!");
                           cout<<"\n\n";
                           cprintf("Press any key to continue...");
                           getch();
                        }
                     }
                  }while(interflag3!=0);
					}
            }
            else if(interflag1==3)Run_dividend(port);
            else if(interflag1==4)
            {
               port.Output_portfolio_pie();
               system("start piechart.exe");
            }
            else if(interflag1==5)
            {
               int settingflag;
               float temp;
            	do
               {
                  clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("Settings");
                  textcolor(LIGHTGREEN);
                  cout<<"\n\n\n\n";
                  cprintf("1.Securities Transaction Tax");cout<<endl;
                  cprintf("2.Service Tax");cout<<endl;
                  cprintf("3.Brokerage Rate");cout<<endl;
                  cprintf("4.Cash Deposit");cout<<endl;
                  cprintf("5.Cash Withdrawal");cout<<endl;
                  cprintf("0.Back");
                  Enter_command(settingflag);

                  if(settingflag==1)
                  {
                     int interflag;
                     do
                     {
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Securities Transaction Tax");
                        cout<<"\n\n\n";
                        cprintf("Current STT: %.5f",STT);cout<<"\n\n";
                        cprintf("Enter the new tax rate:  ");
                        cin>>temp;
                        textcolor(LIGHTCYAN);
                        cout<<"\n\n\n";
                        cprintf("1.Continue");cout<<endl;
                        cprintf("2.Re-enter Data");cout<<endl;
                        cprintf("0.Cancel");
                        Enter_command(interflag);
                     }while(interflag==2);

                     if(interflag==1)
                     {
                     	STT=temp;
                        port.Rewrite_Settings();
                     }
                  }

                  else if(settingflag==2)
                  {
                     int interflag;
                     do
                     {
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Service Tax");
                        cout<<"\n\n\n";
                        cprintf("Current SER: %.5f",SER);cout<<"\n\n";
                        cprintf("Enter the new tax rate:  ");
                        cin>>temp;
                        textcolor(LIGHTCYAN);
                        cout<<"\n\n\n";
                        cprintf("1.Continue");cout<<endl;
                        cprintf("2.Re-enter Data");cout<<endl;
                        cprintf("0.Cancel");
                        Enter_command(interflag);
                     }while(interflag==2);

                     if(interflag==1)
                     {
                     	SER=temp;
                        port.Rewrite_Settings();
                     }
                  }

                  else if(settingflag==3)
                  {
                     int interflag;
                     do
                     {
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Brokerage Rate");
                        cout<<"\n\n\n";
                        cprintf("Current Brokerage rate: %.5f",brokrate);cout<<"\n\n";
                        cprintf("Enter the new brokerage rate(perc):  ");
                        cin>>temp;
                        textcolor(LIGHTCYAN);
                        cout<<"\n\n\n";
                        cprintf("1.Continue");cout<<endl;
                        cprintf("2.Re-enter Data");cout<<endl;
                        cprintf("0.Cancel");
                        Enter_command(interflag);
                     }while(interflag==2);

                     if(interflag==1)
                     {
                     	brokrate=temp;
                        port.Rewrite_Settings();
                     }
                  }

                  else if(settingflag==4)
                  {
                     int interflag,temp;
                     do
                     {
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Cash Deposit");
                        cout<<"\n\n\n";
                        cprintf("Current Deposit: %.5f",cash);cout<<"\n\n";
                        cprintf("Enter the amount you wish to deposit:  ");
                        cin>>temp;
                        textcolor(LIGHTCYAN);
                        cout<<"\n\n\n";
                        cprintf("1.Continue");cout<<endl;
                        cprintf("2.Re-enter Data");cout<<endl;
                        cprintf("0.Cancel");
                        Enter_command(interflag);
                     }while(interflag==2);

                     if(interflag==1)
                     {
                        cash+=temp;
                        port.Rewrite_Settings();
                     }
                  }

                  else if(settingflag==5)
                  {
                     int interflag,temp;
                     do
                     {
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Cash Withdrawal");
                        cout<<"\n\n\n";
                        cprintf("Current Deposit: %.5f",cash);cout<<"\n\n";
                        cprintf("Enter the amount you wish to withdraw:  ");
                        cin>>temp;
                        textcolor(LIGHTCYAN);
                        cout<<"\n\n\n";
                        cprintf("1.Continue");cout<<endl;
                        cprintf("2.Re-enter Data");cout<<endl;
                        cprintf("0.Cancel");
                        Enter_command(interflag);
                     }while(interflag==2);

                     if(interflag==1)
                     {
                        cash+=temp;
                        port.Rewrite_Settings();
                        port.Load_Settings();
                     }
                  }

               }while(settingflag!=0);

            }
         }while(interflag1!=0);
      }

      else
      {
         clrscr();
      	Render_Title("Absolute Portfolio Manager");
         textcolor(LIGHTRED);
         cout<<"\n\n\n\n";cprintf("Portfolio not found!!");
         cout<<"\n\n";cprintf("Press a key to return to main menu");
         getch();
      }

}

void Run_dividend(Portfolio &p)
{
   int menuflag=0;
   do
   {
      clrscr();
   	Render_Title("Absolute Portfolio Manager");
   	Render_Title("Dividends");
      textcolor(LIGHTCYAN);
      cout<<"\n\n\n";
      cprintf("1.Add Dividend");cout<<endl;
      cprintf("2.View Dividend History(scrip)");cout<<endl;
      cprintf("3.View Dividend History(time period)");cout<<endl;
      cprintf("4.View All Dividends");cout<<endl;
      cprintf("0.Back");
      Enter_command(menuflag);

      if(menuflag==1)
      {
         Dividend div;
         int interflag=0;
         do
         {
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("New Dividend");
            textcolor(GREEN);
            cprintf("Enter the details for new Dividend: ");
            div.Input();
            cout<<"\n\n\n";
            textcolor(LIGHTCYAN);
            cprintf("1.Continue");cout<<endl;
            cprintf("2.Re-enter Data");cout<<endl;
            cprintf("0.Cancel");
            Enter_command(interflag);
         }while(interflag==2);

         if(interflag==1)
         {
            int errorflag=0;
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("New Dividend");
            textcolor(LIGHTRED);
            if(p.Get_cmp_n(div.Get_name(),5)==0 && p.Get_cmp_b(div.Get_name(),7)==0){cprintf("Input Error: Entered Scrip name does not exist");cout<<endl;errorflag++;}
            if(Date_formatcheck(div.Get_date())==false){cprintf("Input Error: Date has incorrect format");cout<<endl;errorflag++;}

            if(errorflag==0)p.Input(div);
            else
            {
               cout<<"\n\n\n";
               cprintf("Press any key to continue");
               getch();
            }
         }
      }

      else if(menuflag==2)
      {
         char name[64];
         int interflag=0;
         do
         {
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("Dividend History");
            cout<<"\n\n\n\n";
            textcolor(LIGHTGREEN);
            cprintf("Enter the scrip name: ");
            gets(name);
            cout<<"\n\n\n";
            textcolor(LIGHTCYAN);
            cprintf("1.Continue");cout<<endl;
            cprintf("2.Re-enter Data");cout<<endl;
            cprintf("0.Cancel");
            Enter_command(interflag);
         }while(interflag==2);

         if(interflag==1)
         {
            int interflag1=0;
            int total_div=0;
            strupr(name);
            do
            {
               clrscr();
               Render_Title("Absolute Portfolio Manager");
               Render_Title("Dividend History");
               cout<<"\n\n";
               total_div=p.Output_dividend_history(name);
               if(total_div==0)
               {
               	clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("Dividend History");
                  cout<<"\n\n\n\n";
                  textcolor(LIGHTRED);
                  cprintf("Dividend History unavailable for <%s>!!", name);
                  cout<<"\n\n";
                  cprintf("Press any key to continue...");
                  getch();
                  interflag1=0;
               }
               else
               {
                  cout<<"\n\n\n";
                  textcolor(LIGHTCYAN);
                  cprintf("1.Edit");cout<<endl;
                  cprintf("2.Delete");cout<<endl;
                  cprintf("0.Back");
                  Enter_command(interflag1);
               }

               if(interflag1==1 && total_div>0)
               {
                  Dividend div;
                  int sln, interflag2=0;
                  clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("Dividend History");
                  cout<<"\n\n";
                  p.Output_dividend_history(name);
                  cout<<"\n\n\n";

                  textcolor(LIGHTGREEN);
                  cprintf("Enter the serial number(as above): ");
                  cin>>sln;

                  if(sln>0 && sln<=total_div)
                  {
                  	do
                  	{
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Dividend History");
                        textcolor(GREEN);
                        cprintf("Enter the details for new Dividend: ");
                        div.Input();
                        cout<<"\n\n\n";
                        textcolor(LIGHTCYAN);
                        cprintf("1.Continue");cout<<endl;
                        cprintf("2.Re-enter Data");cout<<endl;
                        cprintf("0.Cancel");
                        Enter_command(interflag2);
                     }while(interflag2==2);

                  	if(interflag2==1)
                  	{
                        int errorflag=0;
                        clrscr();
                        Render_Title("Absolute Portfolio Manager");
                        Render_Title("Dividend History");
                        textcolor(LIGHTRED);
                        if(p.Get_cmp_n(div.Get_name(),5)==0 && p.Get_cmp_b(div.Get_name(),7)==0){cprintf("Input Error: Entered Scrip name does not exist");cout<<endl;errorflag++;}
                        if(Date_formatcheck(div.Get_date())==false){cprintf("Input Error: Date has incorrect format");cout<<endl;errorflag++;}

                        if(errorflag==0)p.Replace_dividend(div,name,sln);
                        else
                        {
                           cout<<"\n\n\n";
                           cprintf("Press any key to continue");
                           getch();
                        }
                  	}
               	}

               	else
               	{
               		clrscr();
                     Render_Title("Absolute Portfolio Manager");
                     Render_Title("Dividend History");
                     textcolor(LIGHTRED);
                     cout<<"\n\n\n\n";
                     cprintf("Serial number out of bounds!!");
                     cout<<"\n\n";
                     cprintf("Press any key to continue...");
                     getch();
               	}
					}

               if(interflag1==2 && total_div>0)
               {
                  Dividend div;
                  int sln;
                  clrscr();
                  Render_Title("Absolute Portfolio Manager");
                  Render_Title("Dividend History");
                  cout<<"\n\n";
                  p.Output_dividend_history(name);
                  cout<<"\n\n\n";

                  textcolor(LIGHTGREEN);
                  cprintf("Enter the serial number(as above): ");
                  cin>>sln;

                  if(sln>0 && sln<=total_div)
                  {
                     clrscr();
                     Render_Title("Absolute Portfolio Manager");
                     Render_Title("Dividend History");
                     cout<<"\n\n";

                     textcolor(LIGHTRED);
                     char ch;
                     cout<<"\n\n";
                     cprintf("Are you sure you want to DELETE dividend?(Y/N): ");
                     cin>>ch;
                     if(ch=='y' || ch=='Y')
                     {
                     	int tiny_flag;
                        tiny_flag=p.Delete_dividend(name, sln);
                        if(tiny_flag==0)interflag1=0;
                     }
                  }

                  else
                  {
                     clrscr();
                     Render_Title("Absolute Portfolio Manager");
                     Render_Title("Dividend History");
                     textcolor(LIGHTRED);
                     cout<<"\n\n\n\n";
                     cprintf("Serial number out of bounds!!");
                     cout<<"\n\n";
                     cprintf("Press any key to continue...");
                     getch();
                  }
               }
            }while(interflag1!=0);
         }
      }

   	else if(menuflag==4)
   	{
         clrscr();
         Render_Title("Absolute Portfolio Manager");
         Render_Title("All Dividends");
         cout<<"\n\n";
         p.Output_dividend_all();
         cout<<"\n\n\n";
         textcolor(LIGHTRED);
         cprintf("Press any key to return to previous menu...");
         getch();
      }

   	else if(menuflag==3)
   	{
      	int interflag2=0;
         char d1[9],d2[9];
         do
         {
         	clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("Dividend History");
            cout<<"\n\n\n\n";
            textcolor(LIGHTGREEN);
            cprintf("Enter start date(dd-mm-yy): ");
            gets(d1);
            cprintf("Enter end date(dd-mm-yy): ");
            gets(d2);
            cout<<"\n\n\n";
            textcolor(LIGHTCYAN);
            cprintf("1.Continue");cout<<endl;
            cprintf("2.Re-enter Data");cout<<endl;
            cprintf("0.Cancel");
            Enter_command(interflag2);
         }while(interflag2==2);

         if(interflag2==1)
         {
            clrscr();
            Render_Title("Absolute Portfolio Manager");
            Render_Title("Dividend History");
            cout<<"\n\n";
            p.Output_dividend_date(d1,d2);
            cout<<"\n\n\n";
            textcolor(LIGHTRED);
            cprintf("Press any key to return to previous menu...");
            getch();
         }
      }

   }while(menuflag!=0);

}


#endif

