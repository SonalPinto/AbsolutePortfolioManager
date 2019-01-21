#ifndef PORTFOLIO
#define PORTFOLIO

#include "transaction.h"

class Portfolio
	{
   	float buyvalue;
      float sellrate;
      float change;
      int netquantity;
      int buyquantity;
      float value;
      float gain;
      float gainperc;
      float curval;
      char *port_file;
      char *hold_file;
      char *divi_file;
      char *sett_file;

   	public:
         Portfolio()
         	{
            	buyvalue=0;
               value=0;
               sellrate=0;
               netquantity=0;
               buyquantity=0;
               gain=0;
               gainperc=0;
               curval=0;
            }

         Portfolio(char *portfolio, char *holdings, char *dividend, char *settings)
         	{
               divi_file=dividend;
            	port_file=portfolio;
            	hold_file=holdings;
               sett_file=settings;
            	buyvalue=0;
               value=0;
               sellrate=0;
               netquantity=0;
               buyquantity=0;
               gain=0;
               gainperc=0;
               curval=0;
         	}

         void Input(Transaction t)
         {
            Transaction tmp;
            int flag=1;

            if(t.get_type()==1){cash-=t.get_total();Rewrite_Settings();}
            if(t.get_type()==2){cash+=t.get_total();Rewrite_Settings();}

            fstream file(port_file,ios::binary|ios::in);
            fstream tfile("temp.dat",ios::binary|ios::out);
            if(!file)
               tfile.write((char*)&t,sizeof(Transaction));
            else
               {
                  file.read((char*)&tmp,sizeof(Transaction));
                  while(!file.eof())
                  {
                     if(date_compare(t.get_date(), tmp.get_date())==1 && flag!=0)
                     {
                        tfile.write((char*)&t,sizeof(Transaction));
                        flag=0;
                     }
                     tfile.write((char*)&tmp,sizeof(Transaction));
                     file.read((char*)&tmp,sizeof(Transaction));
                  };

                  if(flag==1)tfile.write((char*)&t,sizeof(Transaction));
               }

            file.close();
            tfile.close();

            remove(port_file);
            rename("temp.dat",port_file);

            Update_holdings(t.get_name());
         }

         void Input(Dividend d)
         {
            Dividend tmp;
            int flag=1;
            fstream file(divi_file,ios::binary|ios::in);
            fstream tfile("temp.dat",ios::binary|ios::out);
            if(!file)
            	tfile.write((char*)&d,sizeof(Dividend));
            else
            	{
               	file.read((char*)&tmp,sizeof(Dividend));
                  while(!file.eof())
                  {
                     if(date_compare(d.Get_date(), tmp.Get_date())==1 && flag!=0)
                     {
                     	tfile.write((char*)&d,sizeof(Dividend));
                        flag=0;
                     }
                     tfile.write((char*)&tmp,sizeof(Dividend));
                  	file.read((char*)&tmp,sizeof(Dividend));
                  };

                  if(flag==1)tfile.write((char*)&d,sizeof(Dividend));
               }

            file.close();
            tfile.close();

            remove(divi_file);
            rename("temp.dat",divi_file);
         }

      	int Output_transaction_history(char scripname[])
         	{
               float cmp=Get_cmp_n(scripname, 5);
               float cmp_b=Get_cmp_b(scripname,7);
               Transaction t;
               int sln=0;
            	fstream file(port_file,ios::binary|ios::in);
               file.read((char*)&t,sizeof(Transaction));
               cout<<"Transaction History <"<<scripname<<"> :\n\n";
               textcolor(LIGHTBLUE);textbackground(BLUE);
               cprintf("%c",t_l);
               for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",t_s);
               for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",t_s);
               for(int i=1;i<11;i++)cprintf("%c",h); cprintf("%c",t_s);
               for(int i=1;i<13;i++)cprintf("%c",h); cprintf("%c",t_s);
               for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",t_s);
               for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",t_s);
               for(int i=1;i<11;i++)cprintf("%c",h); cprintf("%c",t_r);
               cprintf("%c",v);
               textcolor(LIGHTCYAN);
               cprintf(" SL_NO ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
               cprintf("   DATE    ");textcolor(LIGHTBLUE);cprintf("%c",v_t); textcolor(LIGHTCYAN);
               cprintf(" QUANTITY ");textcolor(LIGHTBLUE);cprintf("%c",v_t); textcolor(LIGHTCYAN);
               cprintf("  BUY RATE  ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
               cprintf(" SALE RATE ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
               cprintf(" EOD PRICE ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
               cprintf("   GAIN   ");textcolor(LIGHTBLUE);cprintf("%c",v);
               cprintf("%c",l_s);
               for(int i=1;i<8;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
               for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
               for(int i=1;i<11;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
               for(int i=1;i<13;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
               for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
               for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
               for(int i=1;i<11;i++)cprintf("%c",h_t); cprintf("%c",r_s);
               while(!file.eof())
               	{
                  	if(strcmp(t.get_name(),scripname)==0)
                     	{
                           float gain;
                           sln++;
                        	cprintf("%c",v);
                           for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v);
                           gotoxy(wherex(),wherey()-1);

                           textcolor(YELLOW);gotoxy(4,wherey());cprintf("%d",sln);
                           cprintf("(");
                           if(t.get_exchange()==1) cprintf("N");
                           else cprintf("B");
                           textcolor(YELLOW);cprintf(")");
                           textcolor(YELLOW);gotoxy(11,wherey());cprintf("%s",t.get_date());

                           if(t.get_type()==BUY)
                           	{
                                 textcolor(YELLOW);gotoxy(25,wherey());cprintf("%d",t.get_quantity());
                                 textcolor(WHITE);gotoxy(34,wherey());cprintf("%.2f",t.get_rate());
                                 textcolor(WHITE);gotoxy(47,wherey());cprintf("---");
                                 netquantity+=t.get_quantity();
                                 buyquantity+=t.get_quantity();
                                 buyvalue+=t.get_total();
                                 value=buyvalue/buyquantity;
                                 if(t.get_exchange()==1)gain=(cmp-t.get_rate())*t.get_quantity();
                                 else gain=(cmp_b-t.get_rate())*t.get_quantity();
                              }
                           else if(t.get_type()==SELL)
                           	{
                                 textcolor(YELLOW);gotoxy(25,wherey());cprintf("%d",t.get_quantity());
                                 netquantity-=t.get_quantity();
                                 textcolor(WHITE);gotoxy(34,wherey());cprintf("%.2f",value);
                                 textcolor(WHITE);gotoxy(47,wherey());cprintf("%.2f",t.get_rate());
                                 gain=(t.get_rate()-value)*t.get_quantity();
                                 if(netquantity!=0)
                                 	value=((buyvalue/buyquantity*netquantity)-(t.get_total()-(buyvalue/buyquantity*t.get_quantity())))/netquantity;
                                 else value=0;
                                 buyquantity-=t.get_quantity();
                                 buyvalue=value*netquantity;
                              }
                           else if(t.get_type()==BONUS)
                           	{
                                 int qty=0;
                                 qty=t.multi()*netquantity;
                                 netquantity+=qty;
                                 buyquantity+=qty;
                                 value=buyvalue/buyquantity;
                                 if(t.get_exchange()==1)gain=(cmp-t.get_rate())*qty;
                                 else gain=(cmp_b-t.get_rate())*qty;
                                 textcolor(YELLOW);gotoxy(25,wherey());cprintf("%d",qty);
                                 textcolor(WHITE);gotoxy(34,wherey());cprintf("%.2f",t.get_rate());
                                 textcolor(WHITE);gotoxy(47,wherey());cprintf("---");
                              }
                           else if(t.get_type()==SPLIT)
                           	{
                                 int qty=0;
                                 qty=t.multi()*netquantity;
                                 if(t.get_exchange()==1) gain=(cmp-t.get_rate())*(qty-netquantity);
                                 else gain=(cmp_b-t.get_rate())*(qty-netquantity);
                                 netquantity=qty;
                                 buyquantity=qty;
                                 value=buyvalue/buyquantity;
                                 textcolor(YELLOW);gotoxy(25,wherey());cprintf("%d",qty);
                              	textcolor(WHITE);gotoxy(34,wherey());cprintf("%.2f",t.get_rate());
                                 textcolor(WHITE);gotoxy(47,wherey());cprintf("---");
                              }
                           textcolor(YELLOW);gotoxy(59,wherey());
                           if(t.get_exchange()==1) cprintf("%.2f",cmp);
                           else cprintf("%.2f",cmp_b);
                           if(gain>=0)textcolor(LIGHTGREEN);
                           else textcolor(LIGHTRED);
                           gotoxy(71,wherey());cprintf("%.2f",gain);
                           textcolor(LIGHTBLUE);
                           cout<<endl;
                           cprintf("%c",v);
                           for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                           for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v);
                        }
                     file.read((char*)&t,sizeof(Transaction));
               	};
                  cprintf("%c",b_l);
                  for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",b_s);
                  for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",b_s);
                  for(int i=1;i<11;i++)cprintf("%c",h); cprintf("%c",b_s);
                  for(int i=1;i<13;i++)cprintf("%c",h); cprintf("%c",b_s);
                  for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",b_s);
                  for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",b_s);
                  for(int i=1;i<11;i++)cprintf("%c",h); cprintf("%c",b_r);
               file.close();
               textbackground(BLACK);
               return sln;
            }

         float Get_cmp_n(char scripname[], int val)
         {
            fstream file("bhavcopy_NSE.csv", ios::in);
            char q='a';
            char c[100];
            char tname[15];
            char tcmp[15];
            float cmp=0;

            int i;
            while(!file.eof())
            {  file.getline(c,100);
               q='a';
               for(i=0;q!=',';i++)
               {
                  q=c[(i+1)];
                  tname[i]=c[i];
               }
               tname[i]='\0';
               if(strcmp(tname,scripname)==0)
               {
                  q='a';i=0;
                  for(int j=0;j<val;j++,q='a')
                    for(;q!=',';i++)
                        q=c[i];
                  q='a';
                  for(int j=0;q!=',';i++,j++)
                  {
                     q=c[(i+1)];
                     tcmp[j]=c[i];
                  }
                  cmp=atof(tcmp);
               }
            };
            file.close();
            return cmp;
         }

         float Get_cmp_b(char Scripname[], int val)
         {
            fstream file("bhavcopy_BSE.csv", ios::in);
            int flag=0;
            char q='a';
            char c[100];
            char tname[13];
            char	scripname[13];
            strcpy(scripname, Scripname);
            for(int x=strlen(scripname);x<13;x++)scripname[x]=' ';
            char tcmp[13];
            float cmp=0;
            int i,j;

            while(!file.eof())
            {
               file.getline(c,100);
               q='a';
               for(i=0;q!=',';i++)
                  q=c[i];
               q='a';
               j=0;
               for(;q!=',';i++,j++)
               {
                  q=c[i+1];
                  tname[j]=c[i];
               }
               tname[strlen(scripname)]='\0';

               flag=0;
               for(int s=0;s<12;s++)
               {
               	if(tname[s]!=scripname[s]){flag=1;break;}
               }
               if(flag==0)
               {
                  q='a';i=0;
                  for(int j=0;j<val;j++,q='a')
                    for(;q!=',';i++)
                        q=c[i];
                  q='a';
                  for(int j=0;q!=',';i++,j++)
                  {
                     q=c[(i+1)];
                     tcmp[j]=c[i];
                  }
                  cmp=atof(tcmp);
               }
            };
            file.close();
            return cmp;
         }

         int Output_holding(float cmp, float cmp_b, Holding h, float &inv, float &today_gain, float &today_value)
            {
               Transaction t;
               buyvalue=0;
               value=0;
               sellrate=0;
               netquantity=0;
               buyquantity=0;
               gain=0;
               gainperc=0;
               curval=0;

               float tgain=0;
               fstream fob(port_file,ios::binary|ios::in);
               fob.read((char*)&t,sizeof(Transaction));
               while(!fob.eof())
               {
                  if(strcmp(t.get_name(),h.Get_name())==0)
                     {
                        if(t.get_type()==BUY)
                           {
                              netquantity+=t.get_quantity();
                              buyquantity+=t.get_quantity();
                              buyvalue+=t.get_total();
                              value=buyvalue/buyquantity;
                              if(t.get_exchange()==1) tgain=(cmp-t.get_rate())*t.get_quantity();
                              else tgain=(cmp_b-t.get_rate())*t.get_quantity();
                              if(t.get_exchange()==1)
                              {
                              	today_gain+=t.get_quantity()*(Get_cmp_n(h.Get_name(),5)- Get_cmp_n(h.Get_name(),7));
                                 today_value+=t.get_quantity()*Get_cmp_n(h.Get_name(),5);
                              }
                              else
                              {
                              	today_gain+=t.get_quantity()*(Get_cmp_b(h.Get_name(),7)- Get_cmp_b(h.Get_name(),9));
                                 today_value+=t.get_quantity()*Get_cmp_b(h.Get_name(),7);
                              }
                           }
                        else if(t.get_type()==SELL)
                           {
                              netquantity-=t.get_quantity();
                              tgain=(t.get_rate()-value)*t.get_quantity();
                              if(netquantity!=0)
                                 value=((buyvalue/buyquantity*netquantity)-(t.get_total()-(buyvalue/buyquantity*t.get_quantity())))/netquantity;
                              else value=0;
                              buyquantity-=t.get_quantity();
                              buyvalue=value*netquantity;
                              if(t.get_exchange()==1)
                              {
                              	today_gain-=t.get_quantity()*(Get_cmp_n(h.Get_name(),5)- Get_cmp_n(h.Get_name(),7));
                                 today_value-=t.get_quantity()*Get_cmp_n(h.Get_name(),5);
                              }
                              else
                              {
                              	today_gain-=t.get_quantity()*(Get_cmp_b(h.Get_name(),7)- Get_cmp_b(h.Get_name(),9));
                                 today_value-=t.get_quantity()*Get_cmp_b(h.Get_name(),7);
                              }
                           }
                        else if(t.get_type()==BONUS)
                           	{
                                 int qty=0;
                                 qty=t.multi()*netquantity;
                                 netquantity+=qty;
                                 buyquantity+=qty;
                                 value=buyvalue/buyquantity;
                                 if(t.get_exchange()==1) tgain=(cmp-t.get_rate())*qty;
                                 else tgain=(cmp_b-t.get_rate())*qty;
                                 if(t.get_exchange()==1)
                                 {
                                    today_gain+=t.get_quantity()*(Get_cmp_n(h.Get_name(),5)- Get_cmp_n(h.Get_name(),7));
                                    today_value+=t.get_quantity()*Get_cmp_n(h.Get_name(),5);
                                 }
                                 else
                                 {
                                    today_gain-=t.get_quantity()*(Get_cmp_b(h.Get_name(),7)- Get_cmp_b(h.Get_name(),9));
                                    today_value+=t.get_quantity()*Get_cmp_b(h.Get_name(),7);
                                 }
                              }
                           else if(t.get_type()==SPLIT)
                           	{
                                 int qty=0;
                                 qty=t.multi()*netquantity;
                                 if(t.get_exchange()==1) tgain=(cmp-t.get_rate())*(qty-netquantity);
                                 else tgain=(cmp_b-t.get_rate())*(qty-netquantity);
                                 if(t.get_exchange()==1)
                                 {
                                    today_gain+=(qty-netquantity)*(Get_cmp_n(h.Get_name(),5)- Get_cmp_n(h.Get_name(),7));
                                    today_value+=(qty-netquantity)*Get_cmp_n(h.Get_name(),5);
                                 }
                                 else
                                 {
                                    today_gain-=(qty-netquantity)*(Get_cmp_b(h.Get_name(),7)- Get_cmp_b(h.Get_name(),9));
                                    today_value+=(qty-netquantity)*Get_cmp_b(h.Get_name(),7);
                                 }
                                 netquantity=qty;
                                 buyquantity=qty;
                                 value=buyvalue/buyquantity;
                              }
                     }
                  fob.read((char*)&t,sizeof(Transaction));
               };
               if(t.get_exchange()==1) {gain=(cmp-value)*netquantity;/*l_ex=NSE;*/}
               else {gain=(cmp_b-value)*netquantity;/*l_ex=BSE;*/}
               if(netquantity!=0 && value!=0)gainperc=(gain/(value*netquantity))*100;
               if(netquantity==0)
               	gain=tgain;
               curval=cmp*netquantity;
               inv+=netquantity*value;
               textcolor(LIGHTBLUE);
               cprintf("%c",v);
               for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v);
               gotoxy(wherex(),wherey()-1);
               textcolor(YELLOW);gotoxy(3,wherey());cprintf("%s",h.Get_name());
               textcolor(YELLOW);gotoxy(17,wherey());cprintf("%d",netquantity);
               textcolor(WHITE);gotoxy(27,wherey());cprintf("%.2f",value);
               textcolor(LIGHTGRAY);gotoxy(38,wherey());
               if(t.get_exchange()==1) cprintf("%.2f",cmp);
               else cprintf("%.2f",cmp_b);
               if(gain<0)
               {
                 textcolor(LIGHTRED);
                 gotoxy(49,wherey());cprintf("%.2f",gain);
                 gotoxy(60,wherey());
                 if(netquantity!=0) cprintf("%.1f",gainperc);
                 else
                 	{
                     gotoxy(61,wherey());
                  	cprintf("---");
                  }
               }
               else
               {
                 textcolor(LIGHTGREEN);
                 gotoxy(50,wherey());cprintf("%.2f",gain);
                 gotoxy(61,wherey());
                 if(netquantity!=0) cprintf("%.1f",gainperc);
                 else cprintf("---");
               }
               textcolor(LIGHTGRAY);gotoxy(70,wherey());cprintf("%.2f",curval);
               cout<<endl;
               textcolor(LIGHTBLUE);
               cprintf("%c",v);
               for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<11;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v);
               fob.close();

               return netquantity;
            }

         void Output_portfolio()
         {
            Holding h;
            float today_gain=0,today_value=0, investment=0, last_ex;
            int qty;
            fstream file(hold_file,ios::binary|ios::in);
            textcolor(LIGHTBLUE);textbackground(BLUE);
            cprintf("%c",t_l);
            for(int i=1;i<13;i++)cprintf("%c",::h); cprintf("%c",t_s);
            for(int i=1;i<11;i++)cprintf("%c",::h); cprintf("%c",t_s);
            for(int i=1;i<11;i++)cprintf("%c",::h); cprintf("%c",t_s);
            for(int i=1;i<12;i++)cprintf("%c",::h); cprintf("%c",t_s);
            for(int i=1;i<11;i++)cprintf("%c",::h); cprintf("%c",t_s);
            for(int i=1;i<8;i++)cprintf("%c",::h); cprintf("%c",t_s);
            for(int i=1;i<13;i++)cprintf("%c",::h); cprintf("%c",t_r);
            cprintf("%c",v);
            textcolor(LIGHTCYAN);
            cprintf("   STOCK    ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf(" QUANTITY ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf(" AVG RATE ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf(" EOD PRICE ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("   GAIN   ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf(" GAIN% "); textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("LATEST VALUE");textcolor(LIGHTBLUE);cprintf("%c",v);
            cprintf("%c",l_s);
            for(int i=1;i<13;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<11;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<11;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<11;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<8;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<13;i++)cprintf("%c",h_t); cprintf("%c",r_s);

            file.read((char*)&h,sizeof(Holding));
            while(!file.eof())
            {
               qty=Output_holding(Get_cmp_n(h.Get_name(), 5),Get_cmp_b(h.Get_name(), 7), h, investment, today_gain, today_value);
               file.read((char*)&h,sizeof(Holding));
            };
            textcolor(LIGHTBLUE);
            cprintf("%c",b_l);
            for(int i=1;i<13;i++)cprintf("%c",::h); cprintf("%c",b_s);
            for(int i=1;i<11;i++)cprintf("%c",::h); cprintf("%c",b_s);
            for(int i=1;i<11;i++)cprintf("%c",::h); cprintf("%c",b_s);
            for(int i=1;i<12;i++)cprintf("%c",::h); cprintf("%c",b_s);
            for(int i=1;i<11;i++)cprintf("%c",::h); cprintf("%c",b_s);
            for(int i=1;i<8;i++)cprintf("%c",::h); cprintf("%c",b_s);
            for(int i=1;i<13;i++)cprintf("%c",::h); cprintf("%c",b_r);
            textbackground(BLACK);

            if(today_value!=0 && investment!=0)
            {
               textcolor(WHITE);
               cout<<"\n\n\n";
               cprintf("Unrealised Gain Today   : ");
               if(today_gain>=0)textcolor(LIGHTGREEN);
               else textcolor(RED);
               cprintf("%.2f",today_gain);
               gotoxy(50,wherey());
               cprintf( "%.2f%%",((today_gain/today_value)*100) );
               cout<<endl;

               textcolor(WHITE);
               cprintf("Portfolio Value Today   : ");
               textcolor(LIGHTGREEN);
               cprintf("%.2f",today_value);
               gotoxy(50,wherey());
               cprintf( "%.2f%%",(((today_value/investment)*100)-100) );
               cout<<endl;

               Load_Settings();
               textcolor(WHITE);
               cprintf("Balance Amount          : ");
               textcolor(LIGHTGREEN);
               cprintf("%.2f",cash);
            }
            file.close();
            textbackground(BLACK);
         }

         float Output_holding_pie(float cmp, float cmp_b, Holding h, float &port_perc)
         {
            Transaction t;
            netquantity=0;
            float scrip_perc=0;

            fstream fob(port_file,ios::binary|ios::in);
            fob.read((char*)&t,sizeof(Transaction));
            while(!fob.eof())
            {
               if(strcmp(t.get_name(),h.Get_name())==0)
                  {
                     if(t.get_type()==BUY)
                        {
                           netquantity+=t.get_quantity();
                           if(t.get_exchange()==NSE)scrip_perc+=t.get_quantity()*Get_cmp_n(t.get_name(), 5);
                           else scrip_perc+=t.get_quantity()*Get_cmp_b(t.get_name(), 7);
                        }
                     else if(t.get_type()==SELL)
                        {
                           netquantity-=t.get_quantity();
                           if(t.get_exchange()==NSE)scrip_perc-=t.get_quantity()*Get_cmp_n(t.get_name(), 5);
                           else scrip_perc-=t.get_quantity()*Get_cmp_b(t.get_name(), 7);
                        }
                     else if(t.get_type()==BONUS)
                           {
                              int qty=0;
                              qty=t.multi()*netquantity;
                              netquantity+=qty;
                              if(t.get_exchange()==NSE)scrip_perc+=qty*Get_cmp_n(t.get_name(), 5);
                           	else scrip_perc+=qty*Get_cmp_b(t.get_name(), 7);

                           }
                        else if(t.get_type()==SPLIT)
                           {
                              int qty=0;
                              qty=t.multi()*netquantity;
                              if(t.get_exchange()==NSE)scrip_perc+=(qty-netquantity)*Get_cmp_n(t.get_name(), 5);
                           	else scrip_perc+=(qty-netquantity)*Get_cmp_b(t.get_name(), 7);
                              netquantity=qty;
                           }
                  }
               fob.read((char*)&t,sizeof(Transaction));
            };

            port_perc+=scrip_perc;
            fob.close();
            return scrip_perc;
         }

         void Output_portfolio_pie()
         {
            Holding h;
            int n=0;
            float port_perc=0;
            fstream file(hold_file,ios::binary|ios::in);
            ofstream fob("pietemp.txt");
            file.read((char*)&h,sizeof(Holding));
            while(!file.eof())
            {
               if(Output_holding_pie2(h)>0)
               {
                  fob<<h.Get_name()<<":";
                  fob<<Output_holding_pie(Get_cmp_n(h.Get_name(), 5),Get_cmp_b(h.Get_name(), 7), h, port_perc);
                  fob<<'\n';
               }
               file.read((char*)&h,sizeof(Holding));
               n++;
            };

            file.close();
            fob.close();
         }

         int Output_holding_pie2(Holding h)
            {
               Transaction t;
               netquantity=0;
               buyquantity=0;

               fstream fob(port_file,ios::binary|ios::in);
               fob.read((char*)&t,sizeof(Transaction));
               while(!fob.eof())
               {
                  if(strcmp(t.get_name(),h.Get_name())==0)
                     {
                        if(t.get_type()==BUY)
                           {
                              netquantity+=t.get_quantity();
                              buyquantity+=t.get_quantity();
                           }
                        else if(t.get_type()==SELL)
                           {
                              netquantity-=t.get_quantity();
                              buyquantity-=t.get_quantity();
                           }
                        else if(t.get_type()==BONUS)
                        {
                           int qty=0;
                           qty=t.multi()*netquantity;
                           netquantity+=qty;
                           buyquantity+=qty;
                        }
                        else if(t.get_type()==SPLIT)
                        {
                           int qty=0;
                           qty=t.multi()*netquantity;
                           netquantity=qty;
                           buyquantity=qty;
                        }
                     }
                  fob.read((char*)&t,sizeof(Transaction));
               };
               fob.close();

               return netquantity;
            }

         void Update_holdings(char c[])
         {
            int flag=1;
            fstream file(hold_file,ios::binary|ios::in);

            if(!file)
            {
               file.close();
               Holding h(c);
               fstream fob(hold_file,ios::binary|ios::out);
               fob.write((char*)&h,sizeof(Holding));
               fob.close();
            }
            else
            {
               Holding h;
               file.read((char*)&h,sizeof(Holding));
               while(!file.eof())
               {
                  if(strcmp(h.Get_name(), c)==0){flag=0;break;}
                  file.read((char*)&h,sizeof(Holding));
               };
               file.close();
               if(flag!=0)
               {
                  Holding q(c);
                  fstream fob(hold_file,ios::binary|ios::app);
                  fob.write((char*)&q,sizeof(Holding));
                  fob.close();
               }
            }
         }

         int Delete_transaction(char *scripname, int sl_no=-1)
         {
            ifstream file(port_file, ios::binary);
            ofstream tfile("temp.dat", ios::binary|ios::trunc);
            Transaction t;
            int sln=0, flag=0, f=0, count=0;
            file.read((char*)&t,sizeof(Transaction));
            while(!file.eof())
            {
               f=0;
               if(strcmp(t.get_name(),scripname)==0)count++;
               if(strcmp(t.get_name(),scripname)==0 && flag==0)
               {
                  sln++;
                  if(sl_no==-1){f=1;}
                  else if(sln==sl_no){flag=1;f=1;}
               }
               if(f==0)tfile.write((char*)&t,sizeof(Transaction));
               file.read((char*)&t,sizeof(Transaction));
            };

            file.close();
            tfile.close();

            remove(port_file);
            rename("temp.dat",port_file);
            if(sl_no==-1 || count==1){Delete_holding(scripname);return 0;}
            else return 1;
         }

         void Delete_holding(char *scripname)
         {
         	ifstream file(hold_file, ios::binary);
            ofstream tfile("temp.dat", ios::binary|ios::trunc);
            Holding h;
            int flag=0;
            file.read((char*)&h, sizeof(Holding));
            while(!file.eof())
            {
               flag=0;
            	if(strcmp(h.Get_name(),scripname)==0){flag=1;}
               if(flag==0)tfile.write((char*)&h, sizeof(Holding));
               file.read((char*)&h, sizeof(Holding));
            };

            file.close();
            tfile.close();

            remove(hold_file);
            rename("temp.dat",hold_file);
         }

         void Replace_transaction(Transaction tmp, char *scripname, int sl_no)
         {
            Delete_transaction(scripname, sl_no);
            Input(tmp);
         }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DIVIDENDS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

         void Replace_dividend(Dividend tmp, char *scripname, int sl_no)
         {
            Delete_dividend(scripname, sl_no);
            Input(tmp);
         }

         int Delete_dividend(char *scripname, int sl_no=-1)
         {
            ifstream file(divi_file, ios::binary);
            ofstream tfile("temp.dat", ios::binary|ios::trunc);
            Dividend d;
            int sln=0, flag=0, f=0, count=0;
            file.read((char*)&d,sizeof(Dividend));
            while(!file.eof())
            {
               f=0;
               if(strcmp(d.Get_name(),scripname)==0)count++;
               if(strcmp(d.Get_name(),scripname)==0 && flag==0)
               {
                  sln++;
                  if(sl_no==-1){f=1;}
                  else if(sln==sl_no){flag=1;f=1;}
               }
               if(f==0)tfile.write((char*)&d,sizeof(Dividend));
               file.read((char*)&d,sizeof(Dividend));
            };

            file.close();
            tfile.close();

            remove(divi_file);
            rename("temp.dat",divi_file);
            if(sl_no==-1 || count==1){Delete_holding(scripname);return 0;}
            else return 1;
         }

         float Get_dividend(char *scripname)
         {
            float sum=0;
            Dividend d;
            ifstream file(divi_file, ios::binary);

            file.read((char*)&d, sizeof(Dividend));
            while(!file.eof())
            {
               if(strcmp(scripname,d.Get_name())==0)
               {
                  sum+=d.Get_amount();
               }
               file.read((char*)&d, sizeof(Dividend));
            };

            file.close();
            return sum;
         }

         float Get_dividend()
         {
            float sum=0;
            Dividend d;
            ifstream file(divi_file, ios::binary);

            file.read((char*)&d, sizeof(Dividend));
            while(!file.eof())
            {
            	sum+=d.Get_amount();
               file.read((char*)&d, sizeof(Dividend));
            };

            file.close();
            return sum;
         }

         int Output_dividend_history(char scripname[])
         {
            Dividend d;
            int sln=0;
            ifstream file(divi_file, ios::binary);

            cout<<"Dividend History <"<<scripname<<"> :\n\n";

            textcolor(LIGHTBLUE);textbackground(BLUE);
            cprintf("%c",t_l);
            for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<16;i++)cprintf("%c",h); cprintf("%c",t_r);
            cout<<endl;
            cprintf("%c",v);
            textcolor(LIGHTCYAN);
            cprintf(" SL_NO ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("   DATE    ");textcolor(LIGHTBLUE);cprintf("%c",v_t); textcolor(LIGHTCYAN);
            cprintf("     AMOUNT    ");textcolor(LIGHTBLUE);cprintf("%c",v);
            cout<<endl;
            cprintf("%c",v);
            for(int i=1;i<8;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<16;i++)cprintf("%c",h_t); cprintf("%c",v);
            cout<<endl;

            file.read((char*)&d, sizeof(Dividend));
            while(!file.eof())
            {
               if(strcmp(d.Get_name(),scripname)==0)
               {
                  sln++;
                  textcolor(LIGHTBLUE);
                  cprintf("%c",v);
                  for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<16;i++)cprintf(" "); cprintf("%c",v);

                  textcolor(YELLOW);gotoxy(4,wherey());cprintf("%d",sln);
                  textcolor(YELLOW);gotoxy(11,wherey());cprintf("%s",d.Get_date());
                  textcolor(LIGHTGREEN);gotoxy(26,wherey());cprintf("%.2f",d.Get_amount());

                  cout<<endl;
                  textcolor(LIGHTBLUE);
                  cprintf("%c",v);
                  for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<16;i++)cprintf(" "); cprintf("%c",v);
                  cout<<endl;
               }
               file.read((char*)&d, sizeof(Dividend));
            };
            textcolor(LIGHTBLUE);
            cprintf("%c",b_l);
            for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<16;i++)cprintf("%c",h); cprintf("%c",b_r);
            cout<<"\n\n";

            file.close();
            textbackground(BLACK);
            textcolor(GREEN);cprintf("Total Dividend: %.2f", Get_dividend(scripname));

            return sln;
         }

         void Output_dividend_date(char d1[],char d2[])
         {
            int sln=0;
            float total=0;
            Dividend d;
         	ifstream file(divi_file,ios::binary);

            cout<<"Dividend History:\n\n";

            textcolor(LIGHTBLUE);textbackground(BLUE);
            cprintf("%c",t_l);
            for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<13;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<16;i++)cprintf("%c",h); cprintf("%c",t_r);
            cout<<endl;
            cprintf("%c",v);
            textcolor(LIGHTCYAN);
            cprintf(" SL_NO ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("   STOCK    ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("   DATE    ");textcolor(LIGHTBLUE);cprintf("%c",v_t); textcolor(LIGHTCYAN);
            cprintf("     AMOUNT    ");textcolor(LIGHTBLUE);cprintf("%c",v);
            cout<<endl;
            cprintf("%c",v);
            for(int i=1;i<8;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<13;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<16;i++)cprintf("%c",h_t); cprintf("%c",v);
            cout<<endl;

            file.read((char*)&d,sizeof(Dividend));
            while(!file.eof())
            {
               if((date_compare(d1,d.Get_date())>=0)&&(date_compare(d2,d.Get_date())<=0))
               {
               	sln++;
                  total+=d.Get_amount();
                  textcolor(LIGHTBLUE);
                  cprintf("%c",v);
                  for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<16;i++)cprintf(" "); cprintf("%c",v);

                  textcolor(YELLOW);gotoxy(4,wherey());cprintf("%d",sln);
                  textcolor(YELLOW);gotoxy(10,wherey());cprintf("%s",d.Get_name());
                  textcolor(YELLOW);gotoxy(24,wherey());cprintf("%s",d.Get_date());
                  textcolor(LIGHTGREEN);gotoxy(41,wherey());cprintf("%.2f",d.Get_amount());

                  cout<<endl;
                  textcolor(LIGHTBLUE);
                  cprintf("%c",v);
                  for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
                  for(int i=1;i<16;i++)cprintf(" "); cprintf("%c",v);
                  cout<<endl;
               }

               file.read((char*)&d, sizeof(Dividend));
            };

            textcolor(LIGHTBLUE);
            cprintf("%c",b_l);
            for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<13;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<16;i++)cprintf("%c",h); cprintf("%c",b_r);
            cout<<"\n\n";

            file.close();
            textbackground(BLACK);
            textcolor(GREEN);cprintf("Total Dividend: %.2f", total);

            cout<<"\n\n\n";
            if(sln==0)
            cprintf("No Dividend records during this period!");
         }

			void Output_dividend_all()
         {
         	Dividend d;
            int sln=0;
            ifstream file(divi_file,ios::binary);
            cout<<"All Dividends:\n\n";

            textcolor(LIGHTBLUE);textbackground(BLUE);
            cprintf("%c",t_l);
            for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<13;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",t_s);
            for(int i=1;i<16;i++)cprintf("%c",h); cprintf("%c",t_r);
            cout<<endl;
            cprintf("%c",v);
            textcolor(LIGHTCYAN);
            cprintf(" SL_NO ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("   STOCK    ");textcolor(LIGHTBLUE);cprintf("%c",v_t);textcolor(LIGHTCYAN);
            cprintf("   DATE    ");textcolor(LIGHTBLUE);cprintf("%c",v_t); textcolor(LIGHTCYAN);
            cprintf("     AMOUNT    ");textcolor(LIGHTBLUE);cprintf("%c",v);
            cout<<endl;
            cprintf("%c",v);
            for(int i=1;i<8;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<13;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<12;i++)cprintf("%c",h_t); cprintf("%c",fs_t);
            for(int i=1;i<16;i++)cprintf("%c",h_t); cprintf("%c",v);
            cout<<endl;

            file.read((char*)&d, sizeof(Dividend));
            while(!file.eof())
            {
               sln++;
               textcolor(LIGHTBLUE);
               cprintf("%c",v);
               for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<16;i++)cprintf(" "); cprintf("%c",v);

               textcolor(YELLOW);gotoxy(4,wherey());cprintf("%d",sln);
               textcolor(YELLOW);gotoxy(10,wherey());cprintf("%s",d.Get_name());
               textcolor(YELLOW);gotoxy(24,wherey());cprintf("%s",d.Get_date());
               textcolor(LIGHTGREEN);gotoxy(41,wherey());cprintf("%.2f",d.Get_amount());

               cout<<endl;
               textcolor(LIGHTBLUE);
               cprintf("%c",v);
               for(int i=1;i<8;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<13;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<12;i++)cprintf(" "); cprintf("%c",v_t);
               for(int i=1;i<16;i++)cprintf(" "); cprintf("%c",v);
               cout<<endl;

               file.read((char*)&d, sizeof(Dividend));
            };
            textcolor(LIGHTBLUE);
            cprintf("%c",b_l);
            for(int i=1;i<8;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<13;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<12;i++)cprintf("%c",h); cprintf("%c",b_s);
            for(int i=1;i<16;i++)cprintf("%c",h); cprintf("%c",b_r);
            cout<<"\n\n";

            file.close();
            textbackground(BLACK);
            textcolor(GREEN);cprintf("Total Dividend: %.2f", Get_dividend());
         }

         void Load_Settings()
         {
            fstream file(sett_file, ios::in);
            char str[64];

            file.getline(str,64);
            STT=atof(str);
            file.getline(str,64);
            SER=atof(str);
            file.getline(str,64);
            cash=atof(str);
            file.getline(str,64);
            brokrate=atof(str);

            file.close();
         }

         void Rewrite_Settings()
         {
            fstream file(sett_file, ios::out|ios::trunc);
            file<<STT<<endl<<SER<<endl<<cash<<endl<<brokrate<<endl;
         	file.close();
         }

         int Check_holding(char c[])
         {
            Holding h;
            int flag=1;
         	ifstream file(hold_file, ios::binary);
            if(file)
            {
            	file.read((char*)&h, sizeof(Holding));
               while(!file.eof())
               {
               	if(strcmp(h.Get_name(),c)==0){flag=0;break;}
                  file.read((char*)&h, sizeof(Holding));
               };
            }
            file.close();
            return flag;
         }
   };

#endif
