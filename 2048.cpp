#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
void show();//��ʼ�˵�ҳ
void show2();//��Ϸ˵������
void show3();//��Ϸ���н���
void up();//������
void down();//������
void left();//������
void right();//������
int win();//�ж��Ƿ�ɹ�
int lose();//�ж��Ƿ�ʧ��
void start();//������Ϸ������Ϸ��ʼ��
void random();
MOUSEMSG m;
IMAGE img[11];
IMAGE img0,img2,img4,img8,img16,img32,img64,img128,img256,img512,img1024,img2048;
int i,j;//i�����У�j������
int map[4][4];
int n,term,tmp;//n��ʾѭ��������term��ʾ�м����
char kb;//�Ӽ������õ��ַ�
int score,high;//��Ϸ����,��Ϸ��߷�
TCHAR str1[10],str2[10];
int main()//������
{
	FILE *p;
	initgraph(640,480);
	mciSendString(_T("open ����\\Horizon.mp3 Alias music"), NULL, 0, NULL); //��������
	mciSendString(_T("play music from 0 repeat"), NULL, 0, NULL); //��������
	p=fopen("��߷�//��߷�.txt","r");
	fscanf_s(p,"%d",&high);
	fclose(p);
	while(1)
	{
		show();
	}
}
void show()//��ʼ�˵�ҳ
{
	cleardevice();
	loadimage(&img[0],_T("ͼƬ\\����.jpg"),640,480);
	loadimage(&img[1],_T("ͼƬ\\2048p.jpg"));
	setbkcolor(RGB(245,243,237));//�������ϳ�ɫ
	settextcolor(RGB(150,124,106));
	settextstyle(30,0,_T("΢���ź�"));//���������С����ʽ
	putimage(0,0,&img[0]);
	putimage(200,0,&img[1]);
	RECT r1={200,160,440,250};
	drawtext(_T("��ʼ��Ϸ"),&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//��ֱ����
	RECT r2={200,250,440,340};
	drawtext(_T("��Ϸ˵��"),&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	RECT r3={200,340,440,430};
	drawtext(_T("�˳���Ϸ"),&r3,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	RECT r4={0,430,640,480};
	settextstyle(24,0,_T("΢���ź�"));
	drawtext(_T("���ߣ�181870080 ������"),&r4,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	FlushMouseMsgBuffer();//��������Ϣ����
	while(1)
	{
	m=GetMouseMsg();//��ȡ�����Ϣ
	if(m.uMsg==WM_LBUTTONDOWN&&m.x>=200&&m.x<=440&&m.y>=160&&m.y<=250)
		start();
	else if(m.uMsg==WM_LBUTTONDOWN&&m.x>=200&&m.x<=440&&m.y>=250&&m.y<=340)
		show2();
	else if(m.uMsg==WM_LBUTTONDOWN&&m.x>=200&&m.x<=440&&m.y>=340&&m.y<=430)
		exit(0);
	}
	_getch();
}
void start()//��Ϸ���к���
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
	  if(kb=='w'||kb=='W')//������
	     up();
	  else if(kb=='s'||kb=='S')//������
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
			  p=fopen("��߷�\\��߷�.txt","w");
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
void show2()//��Ϸ˵������
{
	cleardevice();
	loadimage(&img[2],_T("ͼƬ\\����.jpg"),640,480);
	loadimage(&img[3],_T("ͼƬ\\����.jpg"),50,50);
	loadimage(&img[4],_T("ͼƬ\\��Ϸ˵��2.jpg"));
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
void show3()//��Ϸ���н���
{
	cleardevice();
	loadimage(&img[5],_T("ͼƬ\\����.jpg"),640,480);
	loadimage(&img[6],_T("ͼƬ\\����.jpg"),50,50);
	loadimage(&img[7],_T("ͼƬ\\���¿�ʼ.jpg"),50,50);
	loadimage(&img[8],_T("ͼƬ\\2048.gif"),150,100);
	putimage(0,0,&img[5]);
	putimage(590,430,&img[6]);
	putimage(590,360,&img[7]);
	putimage(50,10,&img[8]);
	setfillcolor(RGB(184,175,160));
	solidroundrect(320,10,470,100,15,15);
	solidroundrect(480,10,630,100,15,15);
	setbkcolor(RGB(184,175,160));//������ɫ
	settextcolor(RGB(248,247,241));//������ɫ
	settextstyle(38,0,_T("΢���ź�"));
	outtextxy(330,20,_T("��ǰ�÷�"));
	outtextxy(490,20,_T("��ʷ���"));
	_stprintf(str1, _T("%d"), score);
	_stprintf(str2,_T("%d"),high);
	outtextxy(340,60,str1);
	outtextxy(500,60,str2);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			solidroundrect(150+85*i,130+85*j,230+85*i,210+85*j,5,5);
	loadimage(&img0,_T("ͼƬ\\0.jpg"),80,80);
	loadimage(&img2,_T("ͼƬ\\2.jpg"),80,80);
	loadimage(&img4,_T("ͼƬ\\4.jpg"),80,80);
	loadimage(&img8,_T("ͼƬ\\8.jpg"),80,80);
	loadimage(&img16,_T("ͼƬ\\16.jpg"),80,80);
	loadimage(&img32,_T("ͼƬ\\32.jpg"),80,80);
	loadimage(&img64,_T("ͼƬ\\64.jpg"),80,80);
	loadimage(&img128,_T("ͼƬ\\128.jpg"),80,80);
	loadimage(&img256,_T("ͼƬ\\256.jpg"),80,80);
	loadimage(&img512,_T("ͼƬ\\512.jpg"),80,80);
	loadimage(&img1024,_T("ͼƬ\\1024.jpg"),80,80);
	loadimage(&img2048,_T("ͼƬ\\2048.jpg"),80,80);
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
				loadimage(&img[9],_T("ͼƬ//ʤ��.jpg"),300,200);
				putimage(180,150,&img[9]);
				return 1;
			}
	return 0;
}
int lose()//ʧ�ܽ���
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
	loadimage(&img[10],_T("ͼƬ//ʧ��.jpg"),300,200);
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



