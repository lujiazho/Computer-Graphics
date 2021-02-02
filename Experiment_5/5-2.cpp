//////////////////////////
//程序名称：任意阶Bezier曲线
//功    能：单击左键布点,单击右键画Bezier,画一次后可继续布点再画,双击右键可退出程序

#include <math.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

int n=0;
double Points[100][2];

int Mouse_event();																	//	鼠标事件 
void initializer();																	//	界面初始化
double* Bezier(double t,int i,int k){												//	k阶Bezier 
	if(k==0){
		return Points[i];
	}
	double* now_point = new double[2];
	double* one=Bezier(t,i,k-1);
	double* two=Bezier(t,i+1,k-1);
	now_point[0]=(1.0-t)*one[0]+t*two[0];
	now_point[1]=(1.0-t)*one[1]+t*two[1];
	return now_point;
}
void PaintBezier(){
	double* x0;
	double* x1;
	for(int i=0 ; i<=50 ; i++){
		double t=i/50.0;
		if(i==0){
			x0=Bezier(t,0,n-1);
			putpixel(int(x0[0]),int(x0[1]),RED);
		}else{
			x1=Bezier(t,0,n-1);
			line(int(x0[0]),int(x0[1]),int(x1[0]),int(x1[1]));
			x0[0]=x1[0];
			x0[1]=x1[1];
		}
	}
}
void PaintPoints(){
	for(int i=0 ; i<n ; i++){
		circle(int(Points[i][0]),int(Points[i][1]),2);
	}
}
int main(){
	initializer();
	
	if(!Mouse_event()) return 0;
	
	//停住
	getch();
	closegraph();
	return 0; 
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
	drawtext(_T("\n单击左键布点\n单击右键画Bezier，画一次后可继续布点再画\n双击右键可退出程序"), &r1, DT_CENTER | DT_VCENTER );
	

	HRGN rgn = CreateRectRgn(1, 81, 799, 639);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);

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
				Points[n][0]=m.x;
				Points[n][1]=m.y;
				n++;
				BeginBatchDraw();
				clearcliprgn();
				PaintPoints();
				FlushBatchDraw();
				EndBatchDraw();
				break;

			case WM_MOUSEMOVE:
				
				break;
			
			case WM_RBUTTONDOWN:
				PaintBezier();
				break;

			case WM_RBUTTONDBLCLK:
				return 0;	// 双击鼠标右键退出程序
				break;
				
		}
	}
}

