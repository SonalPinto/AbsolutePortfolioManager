#ifndef TRANSACTION
#define TRANSACTION
#include <stdio.h>
#include "portfolio.h"

#define BUY 	1
#define SELL 	2
#define BONUS  3
#define SPLIT  4
#define DIVID  5

#define NSE 	1
#define BSE		2

//~~~~~~~~~~~~~~~~~~~~~~~~~~~GLOBALS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char title[64];
char port_add[64];
char hold_add[64];
char divi_add[64];
char sett_add[64];
float STT;			// securities transaction tax (0.125% of buy or sell value, incl brokerage)
float SER;			// service tax (12.25% of brokerage)
float cash;
float brokrate;

char t_l=char(201);
char t_r=char(187);
char b_l=char(200);
char b_r=char(188);
char h=char(205);
char v=char(186);
char t_s=char(209);
char b_s=char(207);
char v_t=char(179);
char h_t=char(196);
char l_s=char(199);
char r_s=char(182);
char fs_t=char(197);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void Create_defaultSettings(char *settadd)
{
	fstream file(settadd, ios::out|ios::trunc);
   file<<"0.00125"<<endl<<"0.1225"<<endl<<"0"<<endl<<"0.65"<<endl;
   file.close();
}

int sizeoffile(char add[])
{
   char c='a';int count=0;
	fstream file(add, ios::in|ios::nocreate);
   if(!file)return 0;
   else
   {
      while(!file.eof())
      {
         file.get(c);
         count++;
      };
   }
   file.close();
   return count;
}

bool Date_formatcheck(char date[])
{
	bool flag=true;
   if(strlen(date)!=8)flag=false;
   else if(isdigit(date[0])==0 && isdigit(date[1])==0)flag=false;
   else if(isdigit(date[3])==0 && isdigit(date[4])==0)flag=false;
   else if(isdigit(date[6])==0 && isdigit(date[7])==0)flag=false;
   else if(date[2]!='-' && date[5]!='-')flag=false;

   return flag;
}
int date_compare(char d1[], char d2[])
{
	char a[2];
   int x[3],y[3];

   for(int i=0;i<3;i++)
   	{
      	a[0]=d1[i*3];
         a[1]=d1[(i*3)+1];
         x[i]=atoi(a);
         a[0]=d2[i*3];
         a[1]=d2[(i*3)+1];
         y[i]=atoi(a);
      }
   if(y[2]>x[2]) return 1;
   else if(y[2]==x[2])
   	{
      	if(y[1]>x[1]) return 1;
         else if(y[1]==x[1])
         	{
            	if(y[0]>x[0]) return 1;
               else if(y[0]==x[0]) return 0;
               else return -1;
            }
         else return -1;
      }
   else return -1;
}

void Render_Title(char title[], int col=YELLOW)
{
   textcolor(col);
	gotoxy(39-(strlen(title)/2), wherey());cprintf("%s",title);cout<<endl;
   int n=strlen(title);
   if(n%2!=0)
   {
      gotoxy((38-(n/2)), wherey());
      for(int i=0;i<(n+2);i++){cprintf("~");}
   }
   else
   {
      gotoxy((38-(n/2)), wherey());
      for(int i=0;i<(n+2);i++){cprintf("~");}
   }
   cout<<endl;
}

void Enter_command(int &op)
{
	cout<<"\n\n";
   textcolor(GREEN);
	cprintf("Enter Command: [ ]");
   gotoxy(wherex()-2,wherey());
   cin>>op;
}

void Create_batfile_NSE()
{
   dosdate_t temp;
   _dos_getdate(&temp);
   int year=temp.year;
   int month=(int)temp.month;
   int day=((int)temp.day);
   int day_week=((int)temp.dayofweek);
   char *mon;

   if(day_week==0)day-=2;
   else if(day_week==6)day-=1;

   ofstream file("tempEX.bat",ios::out|ios::trunc);
   file<<"curl -o bhavcopy_NSEtemp.csv http://www.nseindia.com/content/historical/EQUITIES/";
   file<<year<<"/";

   if(month==1)mon="JAN";
   else if(month==2)mon="FEB";
   else if(month==3)mon="MAR";
   else if(month==4)mon="APR";
   else if(month==5)mon="MAY";
   else if(month==6)mon="JUN";
   else if(month==7)mon="JUL";
   else if(month==8)mon="AUG";
   else if(month==9)mon="SEP";
   else if(month==10)mon="OCT";
   else if(month==11)mon="NOV";
   else if(month==12)mon="DEC";

   file<<mon<<"/cm";
   if(day>10)file<<day;
   else file<<"0"<<day;
   file<<mon<<year<<"bhav.csv\n";
   file.close();
}

void Create_batfile_BSE()
{
   dosdate_t temp;
   _dos_getdate(&temp);
   int year=temp.year;
   year-=2000;
   int month=(int)temp.month;
   int day=(int)temp.day;
   int day_week=((int)temp.dayofweek);
   if(day_week==0)day-=2;
   else if(day_week==6)day-=1;

   ofstream file("tempEX.bat",ios::out|ios::trunc);
   file<<"curl -o bhav_bse.zip http://www.bseindia.com/bhavcopy/eq";
   if(day<10)file<<"0"<<day;
   else file<<day;
   if(month<10)file<<"0"<<month;
   else file<<month;
   if(year<10) file<<"0"<<year;
   else file<<year;
   file<<"_csv.zip\n";

	file<<"unzip bhav_bse.zip\n";
   file<<"del bhav_bse.zip\n";
   file<<"ren EQ";
   if(day<10)file<<"0"<<day;
   else file<<day;
   if(month<10)file<<"0"<<month;
   else file<<month;
   if(year<10) file<<"0"<<year;
   else file<<year;
   file<<".CSV bhavcopy_BSE_tmp.csv\n";
   file.close();
}

int Download_Bhavcopy()
{
   int flag=0;
   Create_batfile_NSE();
   system("tempEX.bat");
   remove("tempEX.bat");
   if(sizeoffile("bhavcopy_NSEtemp.csv")<500){remove("bhavcopy_NSEtemp.csv");flag++;}
   else if(sizeoffile("bhavcopy_NSEtemp.csv")>=500)
   {
      remove("bhavcopy_NSE.csv");
      rename("bhavcopy_NSEtemp.csv", "bhavcopy_NSE.csv");
   }

   Create_batfile_BSE();
   system("tempEX.bat");
   remove("tempEX.bat");
   if(sizeoffile("bhavcopy_BSE_tmp.csv")>=500)
   {
   	remove("bhavcopy_BSE.csv");
      rename("bhavcopy_BSE_tmp.csv","bhavcopy_BSE.csv");
   }
   else
   {
   	remove("bhavcopy_BSE_tmp.csv");
   	flag++;
   }

   return flag;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


class Transaction
	{
      int exchange;
      int type;
      char name[15];
      char date[9];
      int quantity;
      float rate;
      float amount;
      float total;
      char ratio[5];
      float multiplier;

      public:

         Transaction()
         	{
            	total=0;
               amount=0;
               quantity=0;
               rate=0;
               brokrate=0;
               multiplier=0;
               exchange=NSE;
            }

         void Input()
         	{
               cout<<"\n\nEnter type of transaction:\t\t";
               cin>>type;
               if(type==1)
                	{
                     
                     cout<<"Enter stock exchange:\t\t\t";
                     cin>>exchange;
                     cout<<"Enter scrip name:\t\t\t";
               		gets(name);
               		strupr(name);
                   	cout<<"Enter quantity purchased:\t\t";
                     cin>>quantity;
               		cout<<"Enter date of purchase(dd-mm-yy):\t";
               		gets(date);
               		cout<<"Enter purchase rate:\t\t\t";
                     cin>>rate;
                  }
               else if(type==2)
               	{
                     cout<<"Enter stock exchange:\t\t\t";
                     cin>>exchange;
                     cout<<"Enter scrip name:\t\t\t";
               		gets(name);
               		strupr(name);
                   	cout<<"Enter quantity sold:\t\t\t";
               	  	cin>>quantity;
               		cout<<"Enter date of sale(dd-mm-yy):\t\t";
               		gets(date);
               		cout<<"Enter sale rate:\t\t\t";
                     cin>>rate;
                  }
               else if(type==3)
               	{
                  	cout<<"Enter scrip name:\t\t\t";
               		gets(name);
               		strupr(name);
                  	cout<<"Enter bonus ratio(x:y):\t\t\t";
                     gets(ratio);
                     cout<<"Enter date of bonus(dd-mm-yy):\t\t";
                     gets(date);
                     rate=0;
                     char ch1[3];
                     char ch2[3];
                     int i,j;
                     char q='a';
                     for(i=0;q!=':';i++)
                     	{
                           q=ratio[i];
                        	ch1[i]=ratio[i];
                        }
                     ch1[i-1]='\0';
                     for(j=0,q='a';q!='\0';i++,j++)
                     	{
                        	q=ratio[i];
                           ch2[j]=ratio[i];
                        }
                     ch2[j-1]='\0';
                     float x=atoi(ch1);
                     float y=atoi(ch2);
                     multiplier=x/y;
                  }
               else if(type==4)
               	{
                     cout<<"Enter scrip name:\t\t\t";
               		gets(name);
               		strupr(name);
                  	cout<<"Enter split ratio(x:y):\t\t\t";
                     gets(ratio);
                     cout<<"Enter date of split(dd-mm-yy):\t\t";
                     gets(date);
                     rate=0;
                     char ch1[3];
                     char ch2[3];
                     int i,j;
                     char q='a';
                     for(i=0;q!=':';i++)
                     	{
                           q=ratio[i];
                        	ch1[i]=ratio[i];
                        }
                     ch1[i-1]='\0';
                     for(j=0,q='a';q!='\0';i++,j++)
                     	{
                        	q=ratio[i];
                           ch2[j]=ratio[i];
                        }
                     ch2[j-1]='\0';
                     float x=atoi(ch1);
                     float y=atoi(ch2);
                     multiplier=y/x;
                  }
               if(type==1)
               	{
                     float SER_value,STT_value;
                     SER_value=rate*quantity*(brokrate/100)*SER;
                     STT_value=rate*quantity*(1+(brokrate/100))*STT;
                     total=(rate*quantity*(1+(brokrate/100)))+SER_value+STT_value;
                  }
               else if(type==2)
               	{
                     float SER_value,STT_value;
                     SER_value=rate*quantity*(brokrate/100)*SER;
                     STT_value=rate*quantity*(1-(brokrate/100))*STT;
                     total=(rate*quantity*(1-(brokrate/100)))-SER_value-STT_value;
                  }
            }
         int get_type()
         	{
            	return type;
            }
         int get_exchange()
         	{
            	return exchange;
            }
         char *get_date()
         	{
            	return date;
            }
         int get_quantity()
         	{
            	return quantity;
            }
         float get_rate()
         	{
            	return rate;
            }
         float multi()
         	{
            	return multiplier;
            }
         float get_total()
         	{
            	return total;
            }
         char *get_name()
         	{
            	return name;
            }
   };


class Holding
{
	char name[15];

   public:
            Holding()
            {
            }

   			Holding(char c[])
            {
             	strcpy(name,c);
            }

            char* Get_name()
            {
            	return name;
            }
};


class Dividend
{
	char name[15];
   char date[9];
   float amount;

   public:
            Dividend()
            {
            }

   			void Input()
            {
            	cout<<"\n\nEnter the scrip name:\t\t";gets(name);strupr(name);
               cout<<"Enter date(dd-mm-yy):\t\t";gets(date);
               cout<<"Enter dividend amount:\t\t";cin>>amount;
            }

            char* Get_name()
            {
            	return name;
            }

            char* Get_date()
            {
            	return date;
            }

            float Get_amount()
            {
            	return amount;
            }
};

#endif
