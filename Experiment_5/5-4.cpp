//////////////////////////
//程序名称：B样条曲面
//功    能：双击右键可退出程序

#include <math.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

double M[4][4]={{-1/6.0,3/6.0,-3/6.0,1/6.0},{3/6.0,-6/6.0,3/6.0,0},{-3/6.0,0,3/6.0,0},{1/6.0,4/6.0,1/6.0,0}};
double MT[4][4]={{-1/6.0,3/6.0,-3/6.0,1/6.0},{3/6.0,-6/6.0,0,4/6.0},{-3/6.0,3/6.0,3/6.0,1/6.0},{1/6.0,0,0,0}};
double P[4][4][2]={{{0,0},{360,740},{680,120},{340,90}},
{{400,210},{400,-90},{400,600},{40,210}},
{{20,-320},{400,490},{100,320},{440,330}},
{{200,170},{360,90},{-120,250},{-120,-250}}}; 

int Mouse_event();																	//	鼠标事件 
void initializer();																	//	界面初始化

double* S_u_w(double u,double w);													//	计算曲面上某点坐标
void Paint_curved_surface();														//	画曲面

int main(){
	initializer();
	
	Paint_curved_surface();
	
	if(!Mouse_event()) return 0;
	
	//停住
	getch();
	closegraph();
	return 0; 
}
void Paint_curved_surface(){
	double u,w;
	double* every_point;
	int x0,y0,x1,y1;
	int former_Points[51][2];
	for(int i=0 ; i<=30 ; i++){
		u=i/30.0;
		for(int j=0 ; j<=30 ; j++){
			w=j/30.0;
			every_point=S_u_w(u,w);
			if(i==0){
				former_Points[j][0]=int(every_point[0]);
				former_Points[j][1]=int(every_point[1]);
			}else{
				line(former_Points[j][0],former_Points[j][1],int(every_point[0]),int(every_point[1]));
				former_Points[j][0]=int(every_point[0]);
				former_Points[j][1]=int(every_point[1]);
			}
			if(j==0){
				x0=int(every_point[0]);
				y0=int(every_point[1]);
				putpixel(x0,y0,RED);
			}else{
				x1=int(every_point[0]);
				y1=int(every_point[1]);
				line(x0,y0,x1,y1);
				x0=x1;
				y0=y1;
			}
		}
	}
}
double* S_u_w(double u,double w){
	int i,j,k;
	double now[1][4];
	double U[1][4]={{1.0*u*u*u,1.0*u*u,u,1}};
	double W[1][4]={{w*w*w,w*w,w,1}};
	double WT[4][1]={{w*w*w},{w*w},{w},{1}};
	for(i=0 ; i<1 ; i++){
		for(j=0 ; j<4 ; j++){
			double sum=0;
			for(k=0 ; k<4 ; k++){
				sum+=U[i][k]*M[k][j];
			}
			now[i][j]=sum;
		}
	}
	double now1[1][4][2];
	for(i=0 ; i<1 ; i++){
		for(j=0 ; j<4 ; j++){
			double sum1=0,sum2=0;
			for(k=0 ; k<4 ; k++){
				sum1+=now[i][k]*P[k][j][0];
				sum2+=now[i][k]*P[k][j][1];
			}
			now1[i][j][0]=sum1;
			now1[i][j][1]=sum2;
		}
	}
	double now2[1][4][2];
	for(i=0 ; i<1 ; i++){
		for(j=0 ; j<4 ; j++){
			double sum1=0,sum2=0;
			for(k=0 ; k<4 ; k++){
				sum1+=now1[i][k][0]*MT[k][j];
				sum2+=now1[i][k][1]*MT[k][j];
			}
			now2[i][j][0]=sum1;
			now2[i][j][1]=sum2;
		}
	}
	double now3[1][1][2];
	for(i=0 ; i<1 ; i++){
		for(j=0 ; j<1 ; j++){
			double sum1=0,sum2=0;
			for(k=0 ; k<4 ; k++){
				sum1+=now2[i][k][0]*WT[k][j];
				sum2+=now2[i][k][1]*WT[k][j];
			}
			now3[i][j][0]=sum1;
			now3[i][j][1]=sum2;
		}
	}
	double* point=new double[2];
	point[0]=now3[0][0][0];
	point[1]=now3[0][0][1];
	return point;
}
void initializer(){
	initgraph(800, 640);

	setbkcolor(WHITE);
	setcolor(WHITE);
	fillrectangle(0,0,800,640);
	setcolor(BLACK);
	rectangle(0,0,799,639);
	setcolor(BLACK);
	line(0,80,800,80);

	RECT r1 = {0, 0, 800, 80};
	drawtext(_T("\n\n双击右键可退出程序"), &r1, DT_CENTER | DT_VCENTER );
	

	setcolor(BLACK);
	rectangle(0,0,800,640);
	setcolor(RED);
}
int Mouse_event(){
	MOUSEMSG m;		// 定义鼠标消息
	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				
				break;

			case WM_LBUTTONUP:
				
				break;

			case WM_MOUSEMOVE:
				
				break;
			
			case WM_RBUTTONDOWN:
				
				break;

			case WM_RBUTTONDBLCLK:
				return 0;	// 双击鼠标右键退出程序
				break;
				
		}
	}
}

