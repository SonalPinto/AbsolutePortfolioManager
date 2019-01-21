#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iomanip.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <dos.h>
#include <ctype.h>
#include <graphics.h>

int f_style[]={SOLID_FILL,  HATCH_FILL, INTERLEAVE_FILL, XHATCH_FILL };


void main()
{
   int gdr=DETECT;int gmd;
   initgraph(&gdr,&gmd,"");

   float inv,netinv=0;
   float stangle=0;
   float endangle;
   char str[64];
   char name[15];
   char num[20];
   int i,j,n=0,m=0;

   rectangle(0,0,640,480);
   floodfill(1,1,WHITE);

   ifstream file("pietemp.txt");
   file.getline(str,64);
   while(!file.eof())
   {
      for(i=0;str[i]!=':';i++)
      {
         name[i]=str[i];
      }
      name[i]='\0';
      i++;
      for(j=0;str[i]!='\0';i++, j++)
      {
      	num[j]=str[i];
      }
      num[j]='\0';
      netinv+=atof(num);
      file.getline(str,64);
      n++;
   };

   file.close();


   setcolor(WHITE);
   settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
   int col=9;
   int f=0;
   int x=10,y=10;
   float perc;
   int perc_x,perc_y;

   ifstream tempp("pietemp.txt");
   tempp.getline(str,64);
   while(!tempp.eof())
   {
      for(i=0;str[i]!=':';i++)
      {
         name[i]=str[i];
      }
      name[i]='\0';
      i++;
      for(j=0;str[i]!='\0';i++, j++)
      {
      	num[j]=str[i];
      }
      num[j]='\0';

      inv=atof(num);
      perc=inv/netinv*100.0;
      if((int)perc==0)perc++;
      char percentage[4];
      itoa((int)perc, percentage, 10);

      setfillstyle(f_style[f], col);
      endangle=stangle+(inv/netinv*360.0);
      m++;
      if(m==n)endangle=360;
      //if(endangle-(int)endangle>=0.5 && endangle<=360)endangle++;
      pieslice(380,240,stangle,endangle,150);

      setcolor(BLACK);
      outtextxy(x,y,name);
      float radians=((stangle+endangle)/2.0)*3.14/180;
      perc_x=380+(cos(radians)*175);
      perc_y=240-(sin(radians)*175);
      outtextxy(perc_x, perc_y, percentage);outtextxy(perc_x+17, perc_y,"%");
      bar(x+98, y-3, x+123, y+7);
      y+=15;
      setcolor(WHITE);
      col++;

      stangle=endangle;
      tempp.getline(str,64);

      if(col>=WHITE)
      {
      	col=BLACK;
         if((f+1)<sizeof(f_style))f++;
      }
   };
   tempp.close();
   getch();
   remove("pietemp.txt");
}
