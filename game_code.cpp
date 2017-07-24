
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"Winmm.lib")


#define Height 20
#define Width 15
#define Wall 1
#define Road 0
#define Money 2
#define Bomb -1
#define Capsule 3


#define Up1 1
#define Down1 2
#define Left1 3
#define Right1 4
#define Up2 5
#define Down2 6
#define Left2 7
#define Right2 8
#define Esc 9
#define Find1 10
#define Remove1 11
#define Find2 12
#define Remove2 13
#define Donebomb1 14
#define Donebomb2 15

IMAGE image[11];
IMAGE imageshow[8];


int map[Height+2][Width+2];
int sum1=0;
int sum2=0;
int life1=5;
int life2=5;
int removetime1=3;
int removetime2=3;
int bombtime1=10;
int bombtime2=10;
int bombnum1=0;
int bombnum2=0;
int ti=20;
int TIME=1;

char str1[40],str2[40],str3[40];



void hidden()
{
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
GetConsoleCursorInfo(hOut,&cci);
cci.bVisible=0;
SetConsoleCursorInfo(hOut,&cci);
}

void outshu(int x,int y,int f,long int data)
{ int i=0,j;
int shu_w=0;
int k=1;
if(data==0)
outtextxy(x,y, "0");
while(data/k>=1)
{ shu_w++; k=k*10; }
k=k/10;
for(j=0;j<shu_w;j++)
{ switch(data/k) {
case 1: outtextxy(x+i,y, "1");i=i+f;break;
case 2: outtextxy(x+i,y, "2");i=i+f;break;
case 3: outtextxy(x+i,y, "3");i=i+f;break;
case 4: outtextxy(x+i,y, "4");i=i+f;break;
case 5: outtextxy(x+i,y, "5");i=i+f;break;
case 6: outtextxy(x+i,y, "6");i=i+f;break;
case 7: outtextxy(x+i,y, "7");i=i+f;break;
case 8: outtextxy(x+i,y, "8");i=i+f;break;
case 9: outtextxy(x+i,y, "9");i=i+f;break;
case 0: outtextxy(x+i,y, "0");i=i+f;break;
}
 data=data%k; k=k/10;
 }
}

void copy_img(IMAGE* img1,IMAGE* img2)
{
IMAGE* now_working = GetWorkingImage();
Resize(img1, img2->getwidth(), img2->getheight());
SetWorkingImage(img2);
getimage(img1,0,0,img1->getwidth(),img1->getheight());
SetWorkingImage(now_working);
}

void my_putimg(int X,int Y,IMAGE *img,int tp)
int R,G,B;
if(tp<0)
{tp=0;
}
else if(tp>100)
{tp=100;
}
IMAGE screen;
IMAGE tempimg;
copy_img(&tempimg,img);
SetWorkingImage(NULL);
getimage(&screen,X,Y,img->getwidth(),img->getheight());
DWORD* pMem = GetImageBuffer(&tempimg);
DWORD* bj_pMem = GetImageBuffer(&screen);
for(y=0;y<img->getheight();y++)
{
for(x=0;x<img->getwidth();x++)
{
num = y*img->getwidth()+x;
R=GetRValue(pMem[num]);
G=GetGValue(pMem[num]);
B=GetBValue(pMem[num]);
pMem[num] = RGB((R*tp+GetRValue(bj_pMem[num])*(100-tp))/100 , (G*tp+GetGValue(bj_pMem[num])*(100-tp))/100 , (B*tp+GetBValue(bj_pMem[num])*(100-tp))/100 );
}
}
putimage(X,Y,&tempimg);
}

int change(char str[])
{char *a=str;int x=0;
	a=a+11;
while(*a!=' ')
{x=x*10+*a-48;
a++;
}
return x;
}
void getranking()
{
FILE *fp;
if((fp=fopen("rank.txt","r"))==NULL)
return;
fgets(str1,40,fp);
fgets(str2,40,fp);
fgets(str3,40,fp);
fclose(fp);
}



void loadimage(int x)
{if(x==1)
{loadimage(&image[0], "materials//01.bmp");
loadimage(&image[1], "materials//02.bmp");
loadimage(&image[2], "materials//03.bmp");
loadimage(&image[3], "materials//04.bmp");
loadimage(&image[4], "materials//05.bmp");
loadimage(&image[5], "materials//06.bmp");
loadimage(&image[6], "materials//07.bmp");
}
else if(x==2)
{loadimage(&image[0], "materials//11.bmp");
loadimage(&image[1], "materials//12.bmp");
loadimage(&image[2], "materials//13.bmp");
loadimage(&image[3], "materials//14.bmp");
loadimage(&image[4], "materials//15.bmp");
loadimage(&image[5], "materials//16.bmp");
loadimage(&image[6], "materials//17.bmp");
}
else if(x==3)
{loadimage(&image[0], "materials//18.bmp");
loadimage(&image[1], "materials//19.bmp");
loadimage(&image[2], "materials//20.bmp");
loadimage(&image[3], "materials//21.bmp");
loadimage(&image[4], "materials//22.bmp");
loadimage(&image[5], "materials//23.bmp");
loadimage(&image[6], "materials//24.bmp");
}
else if(x>=4)
{loadimage(&image[0], "materials//沙漠.jpg");
loadimage(&image[1], "materials//沙漠6.jpg");
loadimage(&image[2], "materials//沙漠1.jpg");
loadimage(&image[3], "materials//沙漠5.jpg");
loadimage(&image[4], "materials//沙漠4.jpg");
loadimage(&image[5], "materials//沙漠2.jpg");
loadimage(&image[6], "materials//沙漠3.jpg");
}
loadimage(&image[7], "materials//08.bmp");
loadimage(&image[8], "materials//09.bmp");
loadimage(&image[10],"materials//0.bmp");
}

void loadimageshow(void)
{loadimage(&imageshow[0], "game_page//背景.jpg");
loadimage(&imageshow[1], "game_page//标题.jpg");
loadimage(&imageshow[2], "game_page//游戏说明.jpg");
loadimage(&imageshow[3], "game_page//排行榜.jpg");
loadimage(&imageshow[4], "game_page//结束.jpg");
loadimage(&imageshow[5], "game_page//开始.bmp");
}
void makershow()
{int i;
putimage(0,0,&imageshow[5]);
settextcolor(WHITE);
settextstyle(50,0,"方正粗倩简体");
settextstyle(30,0,"方正粗倩简体");
outtextxy(240,300,"Yun Chen");
outtextxy(240,400,"Bowen Li");
Sleep(3000);
for(i=0;i<=20;i++)
{my_putimg(0,0,&imageshow[0],i);
Sleep(100);
}
}

void playgameshow1()
{putimage(0,0,&imageshow[0]);
setbkmode(TRANSPARENT);
settextcolor(BLACK);
settextstyle(50,0,"宋体");
outtextxy(130,150," 单 人 游 戏 ");
outtextxy(130,275," 双 人 游 戏 ");
outtextxy(130,400," 游 戏 说 明 ");
outtextxy(130,525," 退 出 游 戏 ");
}
void playgameshow2()
{putimage(0,0,&imageshow[0]);
setbkmode(TRANSPARENT);
settextcolor(BLACK);
settextstyle(50,0,"宋体");
outtextxy(130,150," 简 单 模 式 ");
outtextxy(130,275," 普 通 模 式 ");
outtextxy(130,400," 困 难 模 式 ");
outtextxy(130,525," 返 回 菜 单 ");
}
void playgameshow3()
{
	putimage(0,0,&imageshow[0]);
setbkmode(TRANSPARENT);
settextcolor(BLACK);
settextstyle(50,0,"宋体");
outtextxy(130,175," 回 合 模 式 ");
outtextxy(130,335," 自 由 模 式 ");
outtextxy(130,495," 返 回 菜 单 ");
}
void playgameshow4()
{
putimage(0,0,&imageshow[0]);
setbkmode(TRANSPARENT);
settextcolor(BLACK);
settextstyle(50,0,"宋体");
outtextxy(130,150," 绿 草 地 ");
outtextxy(130,275," 粉 水 晶 ");
outtextxy(130,400," 蓝 天 空 ");
outtextxy(130,525," 灰 沙 漠 ");
}

void playgameshow5(int a)
{
	putimage(0,0,&imageshow[4]);
setbkmode(TRANSPARENT);
settextcolor(YELLOW);
settextstyle(50,0,"宋体");
outtextxy(130,405,"  排 行 榜 ");
outtextxy(130,485,"  再 玩 一 次");
outtextxy(130,565,"  退 出 游 戏");
settextstyle(30,0,"宋体");
if(a==2)
{outtextxy(120,140,"玩家1收集到的金币:");
outshu(390,140,18,sum1);
outtextxy(120,190,"玩家1剩余的血量  :");
outshu(390,190,15,life1);
outtextxy(120,240,"玩家2收集到的金币:");
outshu(390,240,18,sum2);
outtextxy(120,290,"玩家2剩余的血量  :");
outshu(390,290,15,life2);
if(life1==0||sum2==10)
outtextxy(120,340,"玩家1输了 玩家2赢了");
if(life2==0||sum1==10)
outtextxy(120,340,"玩家2输了 玩家1赢了");
}
if(a==1)
{outtextxy(120,150,"玩家1剩余的血量  :");
outshu(390,150,15,life1);
outtextxy(120,210,"玩家1收集到的金币:");
outshu(390,210,18,sum1);
getranking();
}
}

void rankingshow()
{
putimage(0,0,&imageshow[3]);
setbkmode(TRANSPARENT);
settextcolor(GREEN);
settextstyle(40,0,"黑体");
outtextxy(110,240,str1);
outtextxy(110,370,str2);
outtextxy(110,500,str3);
settextstyle(40,0,"宋体");
outtextxy(750,610,"返回主菜单");
}


void playerinformation(int x)
{if(x==1)
{setbkmode(TRANSPARENT);
setcolor(BLACK);
settextstyle(25,0,"宋体");
putimage(880,0,&image[10]);
putimage(885,5,&image[7]);
outtextxy(890,200,"当前血量");
outtextxy(890,295,"消除次数");
outtextxy(890,390,"附近雷数");
outtextxy(890,485,"获得宝石");
}
else if(x==2)
{setbkmode(TRANSPARENT);
setcolor(BLACK);
settextstyle(20,0,"宋体");
putimage(880,0,&image[10]);
putimage(885,5,&image[7]);
outtextxy(890,190,"当前血量");
outtextxy(890,220,"消除(L)");
outtextxy(890,250,"埋雷(J)");
outtextxy(890,280,"探雷(k)");
outtextxy(890,310,"收集宝石");
putimage(885,340,&image[8]);
outtextxy(890,530,"当前血量");
outtextxy(890,560,"消除(r)");
outtextxy(890,590,"埋雷(q)");
outtextxy(890,620,"探雷(e)");
outtextxy(890,650,"收集宝石");
}
}

void playerinformation1(int x)
{if(x==1)
{setcolor(BLACK);
settextstyle(60,0,"宋体");
outshu(900,230,40,life1);
outshu(900,325,40,removetime1);
outshu(900,420,40,bombnum1);
outshu(900,515,40,sum1);
}
if(x==2)
{setcolor(BLACK);
settextstyle(20,0,"宋体");
outshu(970,190,7,life1);
outshu(970,220,7,removetime1);
outshu(970,250,7,bombtime1);
outshu(970,280,7,bombnum1);
outshu(970,310,7,sum1);
outshu(970,530,7,life2);
outshu(970,560,7,removetime2);
outshu(970,590,7,bombtime2);
outshu(970,620,7,bombnum2);
outshu(970,650,7,sum2);
}
}

void cover1(int a,int b,int c,int s)
{setcolor(WHITE);
outshu(900,230,40,a);
outshu(900,325,40,b);
outshu(900,420,40,c);
outshu(900,515,40,s);
}

void cover2(int a,int b,int c,int s,int r)
{setcolor(WHITE);
outshu(970,190,7,a);
outshu(970,220,7,b);
outshu(970,250,7,r);
outshu(970,280,7,c);
outshu(970,310,7,s);
}
void cover3(int a,int b,int c,int s,int r)
{setcolor(WHITE);
outshu(970,530,7,a);
outshu(970,560,7,b);
outshu(970,590,7,r);
outshu(970,620,7,c);
outshu(970,650,7,s);
}



void paint(int x,int y)
{  switch(map[x][y])
{
   case Bomb:
   putimage(40*x,40*y,&image[4]);break;
   case Wall:
   putimage(40*x,40*y,&image[1]);break;
   case Road:
   putimage(40*x,40*y,&image[0]);break;
   case Money:
   putimage(40*x,40*y,&image[2]);break;
   case Capsule:
   putimage(40*x,40*y,&image[3]);break;
}
}

void createwall(void)
{ int i,j,t;
  for(i=0;i<Height+2;i++)
      for(j=0;j<Width+2;j++)
	      map[i][j]=Road;
  for(i=0;i<Height+2;i++)
  {map[i][0]=Wall;
   map[i][Width+1]=Wall;
  }
  for(j=0;j<Width+2;j++)
  {map[0][j]=Wall;
   map[Height+1][j]=Wall;
  }
   srand(time(0));
   for(t=0;t<100;t++)
   {i=rand()%18+2;
    j=rand()%13+2;
    map[i][j]=Wall;
   }
}

void createcapsule(int a)
{ int i,j,t;
   if(a==1)
   a=3;
   else if(a==2)
   a=5;
   else if(a==3)
   a=5;
   srand(time(0));
    for(t=1;t<=a;t++)
	{i=rand()%18+2;
     j=rand()%13+2;
     map[i][j]=Capsule;
    }
}

void createmoney(int a,int b)
{  int i,j,t,i1,j1,t1;
    b++;
	if(a==1)
		a=10;
	else if(a==2)
		a=19;
    srand(time(0));
   for(t=0;t<a;t++)
   {i=rand()%18+2;
    j=rand()%13+2;
     t1=1;
     if(i==20&&j==15)
	 {t--;
	 continue;
	 }
	 if(map[i][j]==Money)
	 {t--;
	 continue;
	 }
	 while(t1<=b)
	{i1=rand()%3;
     j1=rand()%3;
	 if(map[i-1+i1][j-1+j1]==Road)
	 map[i-1+i1][j-1+j1]=Bomb;
     t1++;

	 }
   	map[i][j]=Money;
    paint(i,j);
    }
}

void createmap(void)
{int i,j;
 initgraph(1000,680);
map[1][1]=Road;
  for(i=0;i<Height+2;i++)
     for(j=0;j<Width+2;j++)
     paint(i,j);
 }

void recreate(int k,int a)
{int i,j;
	for(i=0;i<Height+2;i++)
     for(j=0;j<Width+2;j++)
		 if(map[i][j]==Bomb)
			 map[i][j]=Road;
if(k<5)
 if(k%2==0)
	 createcapsule(1);
else if(k>5)
 if(k%3==0)
     createcapsule(a);
createmoney(1,a);
removetime1++;
}


int get_key()
{
char c;
while(c=getch())
{
if(c==27) return Esc; //Esc
else if(c==72) return Up1;
else if(c==80) return Down1;
else if(c==75) return Left1; //←
else if(c==77) return Right1; //→
else if(c==119) return Up2; //w
else if(c==115) return Down2; //s
else if(c==97) return Left2; //a
else if(c==100) return Right2; //d
else if(c==106) return Donebomb1;//j
else if(c==107) return Find1;//k
else if(c==108) return Remove1;//
else if(c==113) return Donebomb2;//q
else if(c==101) return Find2;//e
else if(c==114) return Remove2;//r
}
return 0;
}

int counterbomb(int x,int y)//
{ int i,j,t=0;
  for(i=x-1;i<x+2;i++)
	for(j=y-1;j<y+2;j++)
	{if(i>=0&&i<20)
		if(j>=0&&j<15)
		   if(map[i][j]==Bomb)
		      t++;
	}
	mciSendString("play mu4 from 0",NULL,0,NULL);
	return t;
}

void explode(int x,int y)//
{int i,j;
  for(i=x-1;i<=x+1;i++)
    for(j=y-1;j<=y+1;j++)
	{   if(i>=1&&i<20)
		   if(j>=1&&j<15)
		     if(map[i][j]==Wall)
			 {map[i][j]=Road;
		      paint(i,j);
		      }
	}

	mciSendString("play mu1 from 0",NULL,0,NULL);

}

void player1move(int x,int y)//
{if(map[x][y]==Money)
{sum1++;
}
else if(map[x][y]==Bomb)
{mciSendString("play mu2 from 0",NULL,0,NULL);
life1--;
}
else if(map[x][y]==Capsule)
life1++;
map[x][y]=Road;
paint(x,y);
}

void player1explode(int x,int y)//
{if(removetime1>0)
{explode(x,y);
	removetime1--;
}
}
void burybomb1(int x,int y)//1
{if(bombtime1>0)
	map[x][y]=Bomb;
bombtime1--;
}
void player2move(int x,int y)//
{if(map[x][y]==Money)
{sum2++;
}
else if(map[x][y]==Bomb)
{life2--;
mciSendString("play mu2 from 0",NULL,0,NULL);
}
else if(map[x][y]==Capsule)
life2++;
map[x][y]=Road;
paint(x,y);
}

void player2explode(int x,int y)//
{if(removetime2>0)
{explode(x,y);
	removetime2--;
}
}

void burybomb2(int x,int y)//2
{if(bombtime2>0)
	map[x][y]=Bomb;
bombtime2--;
}


void rankingchange()//
{int score1,score2,score3,i,j;
FILE *fp;
score1=change(str1);//
score2=change(str2);
score3=change(str3);
setbkmode(TRANSPARENT);
settextcolor(WHITE);

if(sum1<10)//
{outtextxy(100,270,"  抱歉==没有完成任务");
return;
}
else
{fp=fopen("rank.txt","w+");//
char str4[10];//
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime );
timeinfo = localtime ( &rawtime );
IMAGE tmp;
getimage(&tmp, 110, 300, 300,30 );
outtextxy(100,270,"完成任务 请输入昵称(英文小写10个以内):");
for(i=0;i<10;i++)
{str4[i]=getch();
if(str4[i]=='\b')
{i=i-2;putimage(110,300,&tmp);
for(j=0;j<=i;j++)
outtextxy(110+j*15,300,str4[j]);
continue;}
if(str4[i]=='\r'&&i!=0)
break;
if(str4[i]>122||str4[i]<97)
{i--;continue;
}

outtextxy(110+i*15,300,str4[i]);
}
for(i=0;i<10;i++)
if(str4[i]>122||str4[i]<97)
str4[i]=' ';
if(sum1>score1)//
{for(i=0;i<10;i++)
  putc(str4[i],fp);
fprintf(fp," %d %s",sum1,asctime (timeinfo));
fprintf(fp,"%s",str1);
fprintf(fp,"%s",str2);
}
else if(sum1>score2)
{fprintf(fp,"%s",str1);
for(i=0;i<10;i++)
  putc(str4[i],fp);
fprintf(fp," %d %s",sum1,asctime (timeinfo));
fprintf(fp,"%s",str2);
}
else if(sum1>score3)
{fprintf(fp,"%s",str1);
fprintf(fp,"%s",str2);
for(i=0;i<10;i++)
  putc(str4[i],fp);
fprintf(fp," %d %s",sum1,asctime (timeinfo));
}
fclose(fp);
}


}
void replay()//
{ sum1=0;//
 sum2=0;//
 life1=5;//
life2=5;//
 removetime1=3;//
removetime2=3;//
 bombtime1=10;//
 bombtime2=10;//
TIME=1;
ti=20;//
}

DWORD WINAPI ThreadProc1( LPVOID lpParam ) //
{setbkmode(TRANSPARENT);
setcolor(BLACK);
while(TIME)
{setcolor(BLACK);
settextstyle(60,0,"宋体");
outshu(900,610,40,ti);
Sleep(1000);
setcolor(WHITE);
outshu(900,610,40,ti);
ti--;
if(ti==0)
TIME=ti;
}
life1=0;
return 0;
}

void game1(int i)//
{   int x=1,y=1,k=0; //
    int l=0,r=0,b=0,s=0; //
    int c; //
    CreateThread( NULL,0,ThreadProc1,NULL,0,NULL);   //
    while(life1>0&&ti>0&&sum1<10)//
	{   putimage(40*x,40*y,&image[5]); //
           if(l!=life1||r!=removetime1||b!=bombnum1||s!=sum1)//
		   {cover1(l,r,b,s);
            l=life1,r=removetime1,b=bombnum1,s=sum1;
            playerinformation1(1);
		   }
    c=get_key();//
    switch(c)//
	 {case Up1: //1
	{      if(map[x][y-1]!=Wall)
	{            player1move(x,y-1);
                   if(map[x][y]!=Bomb)
				    map[x][y]=Road;
	                paint(x,y);
				   y--;
	}
	}
      break;
      case Down1: //1
		 {if(map[x][y+1]!=Wall)
		 {   player1move(x,y+1);
              if(map[x][y]!=Bomb)
               map[x][y]=Road;
                paint(x,y);
			  y++;
		 }
		 }
      break;
      case Left1: //1
		  {if(map[x-1][y]!=Wall)
		  {   player1move(x-1,y);
                if(map[x][y]!=Bomb)
                  map[x][y]=Road;
                paint(x,y);
				x--;
		  }
		  }
      break;
      case Right1: //1
		  {if(map[x+1][y]!=Wall)
		  {   player1move(x+1,y);
                if(map[x][y]!=Bomb)
                  map[x][y]=Road;
                 paint(x,y);
				x++;
		  }
		  }
       break;
       case Find1:
		   {bombnum1=counterbomb(x,y);
           }
		   break;
       case Remove1:
       player1explode(x,y);
        break;
	 }
  if(sum1%10==0&&sum1>k)//
  {recreate(k,i);
	  k=sum1;}
  }
TIME=0;//
}

void game2(int a)//两人游戏
{
  int x1=1,y1=1,x2=20,y2=15,t1,t2,t=10000; //
  int a1,a2,l1,l2,b1,b2,s1,s2,r1,r2;
  int c; //
  if(a==1)//
  t=1;
   while(sum1<10&&sum2<10&&life1>0&&life2>0)//
   {putimage(40*x1,40*y1,&image[5]); //
    putimage(40*x2,40*y2,&image[6]); //
 if(l1!=life1||r1!=removetime1||b1!=bombnum1||s1!=sum1||a1!=bombtime1)//
		   {cover2(l1,r1,b1,s1,a1);
             l1=life1,r1=removetime1,b1=bombnum1,s1=sum1,a1=bombtime1;
 }
	if(l2!=life2||r2!=removetime2||b2!=bombnum2||s2!=sum2||a2!=bombtime2)//
		   {cover3(l2,r2,b2,s2,a2);
             l2=life2,r2=removetime2,b2=bombnum2,s2=sum2,a2=bombtime2;
 }
	playerinformation1(2);
       c=get_key();
        if(t<6||t>20) //
		{switch(c)
		{case Up1: //1
		{if(map[x1][y1-1]!=Wall)
		{         player1move(x1,y1-1);
                  if(t1==1)
				  {paint(x1,y1);
                   t1=0;
				  }
                  else
				  {map[x1][y1]=Road;
		          paint(x1,y1);
				  }
				  y1--;
		}
              t++;
		}
          break;
       case Down1: //1
		   {if(map[x1][y1+1]!=Wall)
		   {player1move(x1,y1+1);
               if(t1==1)
				  {paint(x1,y1);
                   t1=0;
				  }
                  else
				  {map[x1][y1]=Road;
		          paint(x1,y1);
				  }
              y1++;
		   }
		   t++;
		   }
          break;
            case Left1: //1
				{if(map[x1-1][y1]!=Wall)
				{player1move(x1-1,y1);
                     if(t1==1)
				  {paint(x1,y1);
                   t1=0;
				  }
                  else
				  {map[x1][y1]=Road;
		          paint(x1,y1);
				  }
                       x1--;
				}
                      t++;
				}
                break;
            case Right1: //1
				{if(map[x1+1][y1]!=Wall)
				{player1move(x1+1,y1);
                   if(t1==1)
				  {paint(x1,y1);
                   t1=0;
				  }
                  else
				  {map[x1][y1]=Road;
		          paint(x1,y1);
				  }
				   x1++;
				}
                 t++;
				}
                    break;
           case Find1:
        bombnum1=counterbomb(x1,y1);
             break;
          case Remove1:
             player1explode(x1,y1);
                  break;
          case Donebomb1:
			  {
	             burybomb1(x1,y1);
                 t1=1;
			  }
           break;
		}
		}
            if(t==6)
            t=12;
            if(t==7)
            t=1;
           if(t>7||t>20)
		   {  switch(c)
		   {case Up2: //1
		   {if(map[x2][y2-1]!=Wall)
		   {    player2move(x2,y2-1);
                 if(t2==1)
				  {paint(x2,y2);
                   t1=0;
				  }
                  else
				  {map[x2][y2]=Road;
		          paint(x2,y2);
				  }
         y2--;
		   }
          t--;
		   }
           break;
       case Down2: //1
		   {if(map[x2][y2+1]!=Wall)
		   {player2move(x2,y2+1);
               if(t2==1)
				  {paint(x2,y2);
                   t1=0;
				  }
                  else
				  {map[x2][y2]=Road;
		          paint(x2,y2);
				  }
              y2++;
		   }
		   t--;
		   }
       break;
        case Left2: //1
			{if(map[x2-1][y2]!=Wall)
			{player2move(x2-1,y2);
             if(t2==1)
				  {paint(x2,y2);
                   t1=0;
				  }
                  else
				  {map[x2][y2]=Road;
		          paint(x2,y2);
				  }
                        x2--;
			}
                  t--;
			}
                  break;
            case Right2: //1
				{if(map[x2+1][y2]!=Wall)
				{player2move(x2+1,y2);
                 if(t2==1)
				  {paint(x2,y2);
                   t1=0;
				  }
                  else
				  {map[x2][y2]=Road;
		          paint(x2,y2);
				  }
                      x2++;
				}
                   t--;
				}
              break;
           case Find2:
           	bombnum2=counterbomb(x2,y2);
            break;
          case Remove2:
         player2explode(x2,y2);
            break;
         case Donebomb2:
			 {
	          burybomb2(x2,y2);
             t2=1;
			 }
           break;
		   }
		   }
}
}


void game()
{	int i,t,j=2,h,a,b=0,x1=0,x2=0,x3=0,x4=0;
MOUSEMSG m;
hidden();
PlaySound(TEXT("music//开始.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
mciSendString("open music//消除.mp3 alias mu1",NULL,0,NULL);
mciSendString("open music//探索.mp3 alias mu4",NULL,0,NULL);
mciSendString("open music//爆炸.mp3 alias mu2",NULL,0,NULL);
playgameshow1();
IMAGE img;
m=GetMouseMsg();
while(1)//
	  {
		      m=GetMouseMsg();

              if(m.x>=130&&m.x<=480&&m.y>=150&&m.y<=205&&m.uMsg == WM_LBUTTONDOWN)
			  {i=1;

                break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=275&&m.y<=330&&m.uMsg == WM_LBUTTONDOWN)
			  {i=2;
				  playgameshow3();

                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=400&&m.y<=455&&m.uMsg == WM_LBUTTONDOWN)
			  {  i=3;
				  putimage(0,0,&imageshow[2]);


                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=525&&m.y<=580&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  exit(0);
                  break;
			  }
			  //1
			if(m.x>=130&&m.x<=480&&m.y>=150&&m.y<=205)
			  {  if(b==0)
			  {getimage(&img,90,145,350,55);my_putimg(90,145,&imageshow[1],40);
	           b++;x1=1;continue;
			  }
			  }

			 if(b==1&&x1==1)
			  if(m.x<130||m.x>480||m.y<150||m.y>205)
			 {putimage(90,145,&img);
			  b--;x1=0;continue;
			 }
			  //2
if(m.x>=130&&m.x<=480&&m.y>=275&&m.y<=330)
			  {  if(b==0)
			  {getimage(&img,90,270,350,55);my_putimg(90,270,&imageshow[1],40);
	           b++;x2=1;continue;
			  }
			  }

			 if(b==1&&x2==1)
			  if(m.x<130||m.x>480||m.y<275||m.y>330)
			 {putimage(90,270,&img);
			  b--;x2=0;continue;
			 }
			  //3
				if(m.x>=130&&m.x<=480&&m.y>=400&&m.y<=455)
			  {  if(b==0)
			  {getimage(&img,90,395,350,55);my_putimg(90,395,&imageshow[1],40);
	           b++;x3=1;continue;
			  }
			  }

			 if(b==1&&x3==1)
			  if(m.x<130||m.x>480||m.y<400||m.y>455)
			 {putimage(90,395,&img);
			  b--;x3=0;continue;
			 }
			  //4
				if(m.x>=130&&m.x<=480&&m.y>=525&&m.y<=580)
			  {  if(b==0)
			  {getimage(&img,90,520,350,55);my_putimg(90,520,&imageshow[1],40);
	           b++;x4=1;continue;
			  }
			  }

			 if(b==1&&x4==1)
			  if(m.x<130||m.x>480||m.y<525||m.y>580)
			 {putimage(90,520,&img);
			  b--;x4=0;continue;
			 }
		}


  //
if(i==1){   b=0;
			playgameshow2();
			while(1)
				{
		      m=GetMouseMsg();

              if(m.x>=130&&m.x<=480&&m.y>=150&&m.y<=205&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  j=1;playgameshow4();
                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=275&&m.y<=330&&m.uMsg == WM_LBUTTONDOWN)
			  {j=2;
				  playgameshow4();

                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=400&&m.y<=455&&m.uMsg == WM_LBUTTONDOWN)
			  {  j=3;
				   playgameshow4();


                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=525&&m.y<=580&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  game();
                  break;
			  }
			  //1
			  if(m.x>=130&&m.x<=480&&m.y>=150&&m.y<=205)
			  {  if(b==0)
			  {getimage(&img,90,145,350,55);my_putimg(90,145,&imageshow[1],40);
	           b++;x1=1;continue;
			  }
			  }

			 if(b==1&&x1==1)
			  if(m.x<130||m.x>480||m.y<150||m.y>205)
			 {putimage(90,145,&img);
			  b--;x1=0;continue;
			 }
			  //2
if(m.x>=130&&m.x<=480&&m.y>=275&&m.y<=330)
			  {  if(b==0)
			  {getimage(&img,90,270,350,55);my_putimg(90,270,&imageshow[1],40);
	           b++;x2=1;continue;
			  }
			  }

			 if(b==1&&x2==1)
			  if(m.x<130||m.x>480||m.y<275||m.y>330)
			 {putimage(90,270,&img);
			  b--;x2=0;continue;
			 }
			  //3
				if(m.x>=130&&m.x<=480&&m.y>=400&&m.y<=455)
			  {  if(b==0)
			  {getimage(&img,90,395,350,55);my_putimg(90,395,&imageshow[1],40);
	           b++;x3=1;continue;
			  }
			  }

			 if(b==1&&x3==1)
			  if(m.x<130||m.x>480||m.y<400||m.y>455)
			 {putimage(90,395,&img);
			  b--;x3=0;continue;
			 }
			  //4
				if(m.x>=130&&m.x<=480&&m.y>=525&&m.y<=580)
			  {  if(b==0)
			  {getimage(&img,90,520,350,55);my_putimg(90,520,&imageshow[1],40);
	           b++;x4=1;continue;
			  }
			  }

			 if(b==1&&x4==1)
			  if(m.x<130||m.x>480||m.y<525||m.y>580)
			 {putimage(90,520,&img);
			  b--;x4=0;continue;
			 }

				}


		}

//
else if(i==2)
{  b=0,x1=0,x2=0,x3=0;
	while(1)
	  {
		      m=GetMouseMsg();

              if(m.x>=130&&m.x<=480&&m.y>=175&&m.y<=230&&m.uMsg == WM_LBUTTONDOWN)
			  {      h=1;
				  playgameshow4();

                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=335&&m.y<=390&&m.uMsg == WM_LBUTTONDOWN)
			  {      h=2;
			  playgameshow4();


                  break;
			  }
					if(m.x>=130&&m.x<=480&&m.y>=495&&m.y<=550&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  replay();game();

                  break;
			  }
					//1
					if(m.x>=130&&m.x<=480&&m.y>=175&&m.y<=230)
			  {  if(b==0)
			  {getimage(&img,90,170,350,55);my_putimg(90,170,&imageshow[1],40);
	           b++;x1=1;continue;
			  }
			  }

			 if(b==1&&x1==1)
			  if(m.x<130||m.x>480||m.y<175||m.y>230)
			 {putimage(90,170,&img);
			  b--;x1=0;continue;
			 }
			  //2
						if(m.x>=130&&m.x<=480&&m.y>=335&&m.y<=390)
			  {  if(b==0)
			  {getimage(&img,90,330,350,55);my_putimg(90,330,&imageshow[1],40);
	           b++;x2=1;continue;
			  }
			  }

			 if(b==1&&x2==1)
			  if(m.x<130||m.x>480||m.y<335||m.y>390)
			 {putimage(90,330,&img);
			  b--;x2=0;continue;
			 }
			  //3
			  	if(m.x>=130&&m.x<=480&&m.y>=495&&m.y<=550)
			  {  if(b==0)
			  {getimage(&img,90,490,350,55);my_putimg(90,490,&imageshow[1],40);
	           b++;x3=1;continue;
			  }
			  }

			 if(b==1&&x3==1)
			  if(m.x<130||m.x>480||m.y<495||m.y>550)
			 {putimage(90,490,&img);
			  b--;x3=0;continue;
			 }


}
}
else if(i==3)
{

	while(1)
	  {
		      m=GetMouseMsg();

              if(m.x>=208&&m.x<=385&&m.y>=584&&m.y<=616&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  replay();game();
			  }

	}



}
//
b=0,x1=0,x2=0,x3=0,x4=0;
while(1)
	  {
		      m=GetMouseMsg();

              if(m.x>=130&&m.x<=480&&m.y>=150&&m.y<=205&&m.uMsg == WM_LBUTTONDOWN)
			  {a=1;

                break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=275&&m.y<=330&&m.uMsg == WM_LBUTTONDOWN)
			  {a=2;


                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=400&&m.y<=455&&m.uMsg == WM_LBUTTONDOWN)
			  {  a=3;



                  break;
			  }
			  if(m.x>=130&&m.x<=480&&m.y>=525&&m.y<=580&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  a=4;
				  break;
			  }
			  //1
			  if(m.x>=130&&m.x<=480&&m.y>=150&&m.y<=205)
			  {  if(b==0)
			  {getimage(&img,90,145,350,55);my_putimg(90,145,&imageshow[1],40);
	           b++;x1=1;continue;
			  }
			  }

			 if(b==1&&x1==1)
			  if(m.x<130||m.x>480||m.y<150||m.y>205)
			 {putimage(90,145,&img);
			  b--;x1=0;continue;
			 }
			  //2
if(m.x>=130&&m.x<=480&&m.y>=275&&m.y<=330)
			  {  if(b==0)
			  {getimage(&img,90,270,350,55);my_putimg(90,270,&imageshow[1],40);
	           b++;x2=1;continue;
			  }
			  }

			 if(b==1&&x2==1)
			  if(m.x<130||m.x>480||m.y<275||m.y>330)
			 {putimage(90,270,&img);
			  b--;x2=0;continue;
			 }
			  //3
				if(m.x>=130&&m.x<=480&&m.y>=400&&m.y<=455)
			  {  if(b==0)
			  {getimage(&img,90,395,350,55);my_putimg(90,395,&imageshow[1],40);
	           b++;x3=1;continue;
			  }
			  }

			 if(b==1&&x3==1)
			  if(m.x<130||m.x>480||m.y<400||m.y>455)
			 {putimage(90,395,&img);
			  b--;x3=0;continue;
			 }
			  //4
				if(m.x>=130&&m.x<=480&&m.y>=525&&m.y<=580)
			  {  if(b==0)
			  {getimage(&img,90,520,350,55);my_putimg(90,520,&imageshow[1],40);
	           b++;x4=1;continue;
			  }
			  }

			 if(b==1&&x4==1)
			  if(m.x<130||m.x>480||m.y<525||m.y>580)
			 {putimage(90,520,&img);
			  b--;x4=0;continue;
			 }
}
//
loadimage(a);
system("cls");
createwall();
createcapsule(j);
createmap();
createmoney(i,j);
playerinformation(i);
PlaySound(TEXT("music//战斗.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
if(i==1)
{game1(i);
Sleep(1000);
playgameshow5(i);
rankingchange();
b=0,x1=0,x2=0,x3=0,x4=0;
while(1)
	  {
		      m=GetMouseMsg();
				//1
			  if(m.x>=130&&m.x<=480&&m.y>=405&&m.y<=460)
			  {  if(b==0)
			  {getimage(&img,90,400,350,55);my_putimg(90,400,&imageshow[1],40);
	           b++;x1=1;continue;
			  }
			  }

			 if(b==1&&x1==1)
			  if(m.x<130||m.x>480||m.y<405||m.y>460)
			 {putimage(90,400,&img);
			  b--;x1=0;continue;
			 }
			  //2
if(m.x>=130&&m.x<=480&&m.y>=485&&m.y<=540)
			  {  if(b==0)
			  {getimage(&img,90,480,350,55);my_putimg(90,480,&imageshow[1],40);
	           b++;x2=1;continue;
			  }
			  }

			 if(b==1&&x2==1)
			  if(m.x<130||m.x>480||m.y<485||m.y>540)
			 {putimage(90,480,&img);
			  b--;x2=0;continue;
			 }
			  //3
				if(m.x>=130&&m.x<=480&&m.y>=565&&m.y<=620)
			  {  if(b==0)
			  {getimage(&img,90,560,350,55);my_putimg(90,560,&imageshow[1],40);
	           b++;x3=1;continue;
			  }
			  }

			 if(b==1&&x3==1)
			  if(m.x<130||m.x>480||m.y<565||m.y>620)
			 {putimage(90,560,&img);
			  b--;x3=0;continue;
			 }

              if(m.x>=130&&m.x<=480&&m.y>=405&&m.y<=460&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  t=1;


                  break;
			  }
if(m.x>=130&&m.x<=480&&m.y>=485&&m.y<=540&&m.uMsg == WM_LBUTTONDOWN)
			  {replay();
				  game();



			  }
				if(m.x>=130&&m.x<=480&&m.y>=565&&m.y<=620&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  exit(0);


			  }
		}
if(t==1)
{         rankingshow();
	while(1)
	{m=GetMouseMsg();

              if(m.x>=750&&m.x<=1000&&m.y>=610&&m.y<=680&&m.uMsg == WM_LBUTTONDOWN)
			  {replay();game();}
	}
}


}
else
{ replay();
	game2(h);
playgameshow5(i);
b=0,x1=0,x2=0,x3=0,x4=0;
while(1)
	  {
		      m=GetMouseMsg();
				//1
			  if(m.x>=130&&m.x<=480&&m.y>=405&&m.y<=460)
			  {  if(b==0)
			  {getimage(&img,90,400,350,55);my_putimg(90,400,&imageshow[1],40);
	           b++;x1=1;continue;
			  }
			  }

			 if(b==1&&x1==1)
			  if(m.x<130||m.x>480||m.y<405||m.y>460)
			 {putimage(90,400,&img);
			  b--;x1=0;continue;
			 }
			  //2
if(m.x>=130&&m.x<=480&&m.y>=485&&m.y<=540)
			  {  if(b==0)
			  {getimage(&img,90,480,350,55);my_putimg(90,480,&imageshow[1],40);
	           b++;x2=1;continue;
			  }
			  }

			 if(b==1&&x2==1)
			  if(m.x<130||m.x>480||m.y<485||m.y>540)
			 {putimage(90,480,&img);
			  b--;x2=0;continue;
			 }
			  //3
				if(m.x>=130&&m.x<=480&&m.y>=565&&m.y<=620)
			  {  if(b==0)
			  {getimage(&img,90,560,350,55);my_putimg(90,560,&imageshow[1],40);
	           b++;x3=1;continue;
			  }
			  }

			 if(b==1&&x3==1)
			  if(m.x<130||m.x>480||m.y<565||m.y>620)
			 {putimage(90,560,&img);
			  b--;x3=0;continue;
			 }
              if(m.x>=130&&m.x<=480&&m.y>=405&&m.y<=460&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  t=1;


                  break;
			  }
if(m.x>=130&&m.x<=480&&m.y>=485&&m.y<=540&&m.uMsg == WM_LBUTTONDOWN)
			  {replay();
				  game();



			  }
				if(m.x>=130&&m.x<=480&&m.y>=565&&m.y<=620&&m.uMsg == WM_LBUTTONDOWN)
			  {
				  exit(0);


			  }
		}
if(t==1)
{         getranking();rankingshow();
	while(1)
	{m=GetMouseMsg();

              if(m.x>=750&&m.x<=1000&&m.y>=610&&m.y<=680&&m.uMsg == WM_LBUTTONDOWN)
			  {replay();game();}
	}
}
}
}


int main()
{ loadimageshow();
initgraph(1000,680);
makershow();
	game();

}











