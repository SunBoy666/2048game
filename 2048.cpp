#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
void show();//起始菜单页
void show2();//游戏说明界面
void show3();//游戏进行界面
void up();//向上移
void down();//向下移
void left();//向左移
void right();//向右移
int win();//判断是否成功
int lose();//判断是否失败
void start();//进入游戏，对游戏初始化
void random();
MOUSEMSG m;
IMAGE img[11];
IMAGE img0,img2,img4,img8,img16,img32,img64,img128,img256,img512,img1024,img2048;
int i,j;//i代表行，j代表列
int map[4][4];
int n,term,tmp;//n表示循环计数，term表示中间变量
char kb;//从键盘中敲的字符
int score,high;//游戏分数,游戏最高分
TCHAR str1[10],str2[10];
int main()//主函数
{
	FILE *p;
	initgraph(640,480);
	mciSendString(_T("open 音乐\\Horizon.mp3 Alias music"), NULL, 0, NULL); //加载音乐
	mciSendString(_T("play music from 0 repeat"), NULL, 0, NULL); //播放音乐
	p=fopen("最高分//最高分.txt","r");
	fscanf_s(p,"%d",&high);
	fclose(p);
	while(1)
	{
		show();
	}
}
void show()//起始菜单页
{
	cleardevice();
	loadimage(&img[0],_T("图片\\背景.jpg"),640,480);
	loadimage(&img[1],_T("图片\\2048p.jpg"));
	setbkcolor(RGB(245,243,237));//红绿蓝合成色
	settextcolor(RGB(150,124,106));
	settextstyle(30,0,_T("微软雅黑"));//设置字体大小，格式
	putimage(0,0,&img[0]);
	putimage(200,0,&img[1]);
	RECT r1={200,160,440,250};
	drawtext(_T("开始游戏"),&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//垂直居中
	RECT r2={200,250,440,340};
	drawtext(_T("游戏说明"),&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	RECT r3={200,340,440,430};
	drawtext(_T("退出游戏"),&r3,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	RECT r4={0,430,640,480};
	settextstyle(24,0,_T("微软雅黑"));
	drawtext(_T("作者：181870080 姜玉骅"),&r4,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	FlushMouseMsgBuffer();//清楚鼠标消息缓冲
	while(1)
	{
	m=GetMouseMsg();//获取鼠标信息
	if(m.uMsg==WM_LBUTTONDOWN&&m.x>=200&&m.x<=440&&m.y>=160&&m.y<=250)
		start();
	else if(m.uMsg==WM_LBUTTONDOWN&&m.x>=200&&m.x<=440&&m.y>=250&&m.y<=340)
		show2();
	else if(m.uMsg==WM_LBUTTONDOWN&&m.x>=200&&m.x<=440&&m.y>=340&&m.y<=430)
		exit(0);
	}
	_getch();
}
void start()//游戏进行函数
{
	FILE *p;
	score=0;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		   map[i][j]=0;
	random();
	random();
	show3();
	while(1)
	{
	  BeginBatchDraw();
	  kb=getch();
	  if(kb=='w'||kb=='W')//向上移
	     up();
	  else if(kb=='s'||kb=='S')//向下移
		 down();
	  else if(kb=='a'||kb=='A')
		 left();
	  else if(kb=='d'||kb=='D')
		 right();
	  if(tmp) 
	  {
		 random();
		 tmp=0;
	  }
	  show3(); 
	  EndBatchDraw();
	  if(kb=='t'||kb=='T'||lose()==1||win()==1)
	  {
		  if(score>high)
		  {
			  high=score;
			  p=fopen("最高分\\最高分.txt","w");
			  fprintf(p,"%d",high);
			  fclose(p);
		  }
		  break;
	  }
	}
	FlushMouseMsgBuffer();
	while(1)
	{
	  m=GetMouseMsg();
	  if(m.uMsg==WM_LBUTTONDOWN&&m.x>=590&&m.x<=640&&m.y>=430&&m.y<=480)
		show();
	  else if(m.uMsg==WM_LBUTTONDOWN&&m.x>=590&&m.x<=640&&m.y>=360&&m.y<=420)
		start();
	}
}
void show2()//游戏说明界面
{
	cleardevice();
	loadimage(&img[2],_T("图片\\背景.jpg"),640,480);
	loadimage(&img[3],_T("图片\\返回.jpg"),50,50);
	loadimage(&img[4],_T("图片\\游戏说明2.jpg"));
	putimage(0,0,&img[2]);
	putimage(590,430,&img[3]);
	putimage(23,50,&img[4]);
	while(1)
	{
	m=GetMouseMsg();
	if(m.uMsg==WM_LBUTTONDOWN&&m.x>=590&&m.x<=640&&m.y>=430&&m.y<=480)
		show();
	}

}
void show3()//游戏进行界面
{
	cleardevice();
	loadimage(&img[5],_T("图片\\背景.jpg"),640,480);
	loadimage(&img[6],_T("图片\\返回.jpg"),50,50);
	loadimage(&img[7],_T("图片\\重新开始.jpg"),50,50);
	loadimage(&img[8],_T("图片\\2048.gif"),150,100);
	putimage(0,0,&img[5]);
	putimage(590,430,&img[6]);
	putimage(590,360,&img[7]);
	putimage(50,10,&img[8]);
	setfillcolor(RGB(184,175,160));
	solidroundrect(320,10,470,100,15,15);
	solidroundrect(480,10,630,100,15,15);
	setbkcolor(RGB(184,175,160));//背景颜色
	settextcolor(RGB(248,247,241));//字体颜色
	settextstyle(38,0,_T("微软雅黑"));
	outtextxy(330,20,_T("当前得分"));
	outtextxy(490,20,_T("历史最高"));
	_stprintf(str1, _T("%d"), score);
	_stprintf(str2,_T("%d"),high);
	outtextxy(340,60,str1);
	outtextxy(500,60,str2);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			solidroundrect(150+85*i,130+85*j,230+85*i,210+85*j,5,5);
	loadimage(&img0,_T("图片\\0.jpg"),80,80);
	loadimage(&img2,_T("图片\\2.jpg"),80,80);
	loadimage(&img4,_T("图片\\4.jpg"),80,80);
	loadimage(&img8,_T("图片\\8.jpg"),80,80);
	loadimage(&img16,_T("图片\\16.jpg"),80,80);
	loadimage(&img32,_T("图片\\32.jpg"),80,80);
	loadimage(&img64,_T("图片\\64.jpg"),80,80);
	loadimage(&img128,_T("图片\\128.jpg"),80,80);
	loadimage(&img256,_T("图片\\256.jpg"),80,80);
	loadimage(&img512,_T("图片\\512.jpg"),80,80);
	loadimage(&img1024,_T("图片\\1024.jpg"),80,80);
	loadimage(&img2048,_T("图片\\2048.jpg"),80,80);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		switch(map[j][i])
		{
		case 0:putimage(150+85*i,130+85*j,&img0);break;
		case 2:putimage(150+85*i,130+85*j,&img2);break;
        case 4:putimage(150+85*i,130+85*j,&img4);break;
	    case 8:putimage(150+85*i,130+85*j,&img8);break;
		case 16:putimage(150+85*i,130+85*j,&img16);break;
		case 32:putimage(150+85*i,130+85*j,&img32);break;
		case 64:putimage(150+85*i,130+85*j,&img64);break;
		case 128:putimage(150+85*i,130+85*j,&img128);break;
        case 256:putimage(150+85*i,130+85*j,&img256);break;
	    case 512:putimage(150+85*i,130+85*j,&img512);break;
		case 1024:putimage(150+85*i,130+85*j,&img1024);break;
		case 2048:putimage(150+85*i,130+85*j,&img2048);break;
		}
}
void random()
{
	int x,y;
	while(1)
	{
	 x=rand()%4;
	 y=rand()%4;
	 term=rand()%5;
	 if(term==0)
		n=4;
	 else n=2;
	 if(map[x][y]==0)
	 {
		 map[x][y]=n;
		 break;
	 }
	 if(lose())
		 break;
	}

}
int win()
{
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(map[i][j]==2048)
			{
				loadimage(&img[9],_T("图片//胜利.jpg"),300,200);
				putimage(180,150,&img[9]);
				return 1;
			}
	return 0;
}
int lose()//失败界面
{
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(map[i][j]==0)
				return 0;
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			if(map[i][j]==map[i][j+1])
				return 0;
	for(j=0;j<4;j++)
		for(i=0;i<3;i++)
			if(map[i][j]==map[i+1][j])
				return 0;
	loadimage(&img[10],_T("图片//失败.jpg"),300,200);
	putimage(180,150,&img[10]);
	return 1;
}
void up()
{
	for(n=0,tmp=0;n<3;n++)  
		  for(i=1;i<4;i++)
			for(j=0;j<4;j++)
			if(map[i][j]!=0)
				if(map[i-1][j]==0)
				{
					map[i-1][j]=map[i][j];
					map[i][j]=0;
					tmp=1;
				}
	   for(i=1;i<4;i++)
		  for(j=0;j<4;j++)
			if(map[i][j]!=0&&map[i-1][j]==map[i][j])
			{
			  score=score+2*map[i][j];
			  map[i-1][j]=2*map[i][j];
			  map[i][j]=0;
			  tmp=1;
		    }
		for(n=0;n<3;n++)
		  for(i=1;i<4;i++)
			for(j=0;j<4;j++)
				if(map[i][j]!=0&&map[i-1][j]==0)
				{
					map[i-1][j]=map[i][j];
					map[i][j]=0;
				}
}
void down()
{
	for(n=0,tmp=0;n<3;n++)  
		  for(i=2;i>=0;i--)
			for(j=0;j<4;j++)
				if(map[i][j]!=0&&map[i+1][j]==0)
				{
					map[i+1][j]=map[i][j];
					map[i][j]=0;
					tmp=1;
				}
	   for(i=2;i>=0;i--)
		  for(j=0;j<4;j++)
			if(map[i][j]!=0&&map[i+1][j]==map[i][j])
			{
			  score=score+2*map[i][j];
			  map[i+1][j]=2*map[i][j];
			  map[i][j]=0;
			  tmp=1;
		    }
		for(n=0;n<3;n++)  
		  for(i=2;i>=0;i--)
			for(j=0;j<4;j++)
				if(map[i][j]!=0&&map[i+1][j]==0)
				{
					map[i+1][j]=map[i][j];
					map[i][j]=0;
				}
}
void left()
{
	for(n=0,tmp=0;n<3;n++)
			for(i=0;i<4;i++)
				for(j=1;j<4;j++)
					if(map[i][j]!=0&&map[i][j-1]==0)
					{
							map[i][j-1]=map[i][j];
							map[i][j]=0;
							tmp=1;
					}
		for(i=0;i<4;i++)
			for(j=1;j<4;j++)
				if(map[i][j]!=0&&map[i][j-1]==map[i][j])
					{
						score=score+2*map[i][j];
						map[i][j-1]=2*map[i][j];
						map[i][j]=0;
						tmp=1;
					}
		for(n=0;n<3;n++)
			for(i=0;i<4;i++)
				for(j=1;j<4;j++)
					if(map[i][j]!=0&&map[i][j-1]==0)
					{
							map[i][j-1]=map[i][j];
							map[i][j]=0;
					}
}
void right()
{
	for(n=0,tmp=0;n<3;n++)
			for(i=0;i<4;i++)
				for(j=2;j>=0;j--)
					if(map[i][j]!=0&&map[i][j+1]==0)
						{
							map[i][j+1]=map[i][j];
							map[i][j]=0;
							tmp=1;
						}
		for(i=0;i<4;i++)
			for(j=2;j>=0;j--)
				if(map[i][j]!=0&&map[i][j+1]==map[i][j])
				{
					score=score+2*map[i][j];
					map[i][j+1]=2*map[i][j];
					map[i][j]=0;
					tmp=1;
				}
		for(n=0;n<3;n++)
			for(i=0;i<4;i++)
				for(j=2;j>=0;j--)
					if(map[i][j]!=0&&map[i][j+1]==0)
						{
							map[i][j+1]=map[i][j];
							map[i][j]=0;
						}
}



