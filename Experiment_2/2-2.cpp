#include <graphics.h>
#include <conio.h>
void Putpixel(int x,int y,int color,int wheel){
	if(wheel==0){
		putpixel(x,y,color);
	}
	int i,j; 
	for(i=0 ; i<2*wheel+1 ; i++){
		for(j=int(wheel/2) ; j<2*wheel ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
	for(i=int(wheel/2) ; i<2*wheel ; i++){
		for(j=0 ; j<2*wheel+1 ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
}
void Any_slope_Put_pixel(int x0,int y0,int x1,int y1,int color,int wheel=0){
	int a,b,delta1,delta2,d,x,y;		/*	delta1代表d>0	delta2代表d<0	*/
	a=y0-y1;
	b=x1-x0;
	
	x=x0;
	y=y0;
	Putpixel(x,y,color,wheel);
	
	if(-a==0){
		while(x<x1){
			x++;
			Putpixel(x,y,color,wheel);
		}
		while(x>x1){
			x--;
			Putpixel(x,y,color,wheel);
		}
	}else if(b==0){
		while(y<y1){
			y++;
			Putpixel(x,y,color,wheel);
		}
		while(y>y1){
			y--;
			Putpixel(x,y,color,wheel);
		}
	}
	
	if(-a>0 && b>0){					/*第一象限*/
		if(-a-b>=0){					/*斜率大于等于1*/
			d=a+2*b;
			delta1=2*(a+b);
			delta2=2*b;
			while(y<y1){
				if(d<0){
					y++;
					d+=delta2;
				}else{
					x++;
					y++;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}else{							/*斜率小于1大于0*/ 
			d=2*a+b;
			delta1=2*a;
			delta2=2*(a+b);
			while(x<x1){
				if(d<0){
					x++;
					y++;
					d+=delta2;
				}else{
					x++;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}
	}else if(-a<0 && b>0){				/*第四象限*/
		if(-a+b<=0){					/*斜率小于等于-1*/
			d=a-2*b;
			delta1=-2*b;
			delta2=2*a-2*b;
			while(y>y1){
				if(d<0){
					x++;
					y--;
					d+=delta2;
				}else{
					y--;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}else{							/*斜率大于-1小于0*/ 
			d=2*a-b;
			delta1=2*a-2*b;
			delta2=2*a;
			while(x<x1){
				if(d<0){
					x++;
					d+=delta2;
				}else{
					x++;
					y--;
					d+=delta1;
				}
				Putpixel(x,y,color,wheel);
			}
		}
	}
	
}

int XL,XR,YB,YT;
double Max(double m,double n){
	if(m>n){
		return m;
	}
	return n;
}
double Min(double m,double n){
	if(m<n){
		return m;
	}
	return n;
}
int Liang_Barsky(int x1,int y1,int x2,int y2){
	int p1,p2,p3,p4,q1,q2,q3,q4;
	double u1,u2,u3,u4;
	p1=-(x2-x1);
	p2=x2-x1;
	p3=-(y2-y1);
	p4=y2-y1;
	q1=x1-XL;
	q2=XR-x1;
	q3=y1-YB;
	q4=YT-y1;
	u1=1.0*q1/p1;
	u2=1.0*q2/p2;
	u3=1.0*q3/p3;
	u4=1.0*q4/p4;
	
	double u_max,u_min;
	if(p2==0){						//	竖线 
	
		if(q1<0 || q2<0){				//窗外 
			return 0;
		}else{							//窗内 
			if(p3<0){
				u_max=Max(0,u3);
				u_min=Min(1,u3);
			}else if(p4<0){
				u_max=Max(0,u4);
				u_min=Min(1,u4);
			}
		}
		if(u_max>u_min){
			return 0;
		}else{
			if(y2>y1){
				y2=int(y1+u_min*(p4)); 
				x2=int(x1+u_min*(p2));
				x1=int(x1+u_max*(p2));
				y1=int(y1+u_max*(p4));
			}else{
				y2=int(y1+u_max*(p4)); 
				x2=int(x1+u_max*(p2));
				x1=int(x1+u_min*(p2));
				y1=int(y1+u_min*(p4));
			}
		}
		
	}else if(p4==0){				//	横线 
		
		if(q3<0 || q4<0){				//窗外 
			return 0;
		}else{							//窗内 
			if(p1<0){
				u_max=Max(0,u1);
				u_min=Min(1,u1);
			}else if(p2<0){
				u_max=Max(0,u2);
				u_min=Min(1,u2);
			}
		}
		if(u_max>u_min){
			return 0;
		}else{
			x2=int(x1+u_min*(p2));
			y2=int(y1+u_min*(p4));
			x1=int(x1+u_max*(p2));
			y1=int(y1+u_max*(p4));
		}
		
	}else {							//	斜线 
		if(p1<0 && p3<0){
			u_max=0;
			u_min=1;
			if(u1>u_max){
				u_max=u1;
			}
			if(u3>u_max){
				u_max=u3;
			}
			if(u2<u_min){
				u_min=u2;
			}
			if(u4<u_min){
				u_min=u4;
			}
		}else if(p1<0 && p4<0){
			u_max=0;
			u_min=1;
			if(u1>u_max){
				u_max=u1;
			}
			if(u4>u_max){
				u_max=u4;
			}
			if(u2<u_min){
				u_min=u2;
			}
			if(u3<u_min){
				u_min=u3;
			}
		}
		if(u_max>u_min){
			return 0;
		}else{
			x2=int(x1+u_min*(p2));
			y2=int(y1+u_min*(p4)); 
			
			x1=int(x1+u_max*(p2));
			y1=int(y1+u_max*(p4));

		}
	}
	Any_slope_Put_pixel(x1,y1,x2,y2,RED);
	return 0; 
}

void Repaint(int LINE[300][4],int LINE_NUM){
	setcolor(BLACK);
	rectangle(LINE[0][0],LINE[0][1],LINE[0][2],LINE[0][3]);
	setcolor(RED);

	for(int i=1 ; i<LINE_NUM ; i++){
		Liang_Barsky(LINE[i][0],LINE[i][1],LINE[i][2],LINE[i][3]);
	}
}
int main()
{
	// 初始化图形窗口
	initgraph(800, 640);
	setbkcolor(WHITE);
	setcolor(WHITE);
	fillrectangle(0,0,800,640);
	setcolor(BLACK);
	rectangle(0,0,799,639);
	setcolor(BLACK);
	line(0,80,800,80);

	RECT r = {0, 0, 800, 80};
	drawtext(_T("\n此为Liang_Barsky裁剪算法\n单击右键清屏，可重画裁剪框\n双击右键退出程序"), &r, DT_CENTER | DT_VCENTER);

	HRGN rgn = CreateRectRgn(1, 81, 799, 639);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);

	MOUSEMSG m;		// 定义鼠标消息
	int mount=0;	//第一次画一个方块，作为裁剪边界 
	int LINE[300][4]; 
	int LINE_NUM=0;
	bool LBUTTONDOWN=false;
	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		int x1,y1;
		
		switch(m.uMsg)
		{		
			case WM_LBUTTONDOWN:
				LBUTTONDOWN=true;
				// 记住起点
				x1=m.x;
				y1=m.y;
				circle(x1,y1,5);
				break;

			case WM_LBUTTONUP:
				LBUTTONDOWN=false;
				if(mount==0){
					if(x1<m.x){
						XL=x1;
						XR=m.x;
					}else{
						XL=m.x;
						XR=x1;
					}
					if(y1<m.y){
						YT=m.y;
						YB=y1;
					}else{
						YT=y1;
						YB=m.y;
					}
					
					setcolor(BLACK);
					if(YT<=81){
						YT=81;
					}
					if(YB<=81){
						YB=81;
					}
					
					rectangle(XL,YT,XR,YB);
					setcolor(RED);
					LINE[0][0]=XL;
					LINE[0][1]=YT;
					LINE[0][2]=XR;
					LINE[0][3]=YB;
					LINE_NUM++;
					mount++;
				}else{
					if(x1>m.x){
						LINE[LINE_NUM][0]=m.x;
						LINE[LINE_NUM][1]=m.y;
						LINE[LINE_NUM][2]=x1;
						LINE[LINE_NUM][3]=y1;
					/*	Cohen_Sutherla(m.x,m.y,x1,y1);*/
						LINE_NUM++;
					}else{
						LINE[LINE_NUM][0]=x1;
						LINE[LINE_NUM][1]=y1;
						LINE[LINE_NUM][2]=m.x;
						LINE[LINE_NUM][3]=m.y;
					/*	Cohen_Sutherla(x1,y1,m.x,m.y);*/
						LINE_NUM++;
					}
				}
				
				// 鼠标左键弹起,记住终点并画线
				break;
			case WM_MOUSEMOVE:
				if(LBUTTONDOWN==true){
					if(LINE_NUM!=0){
						BeginBatchDraw();
						clearcliprgn();
						Repaint(LINE,LINE_NUM);
						if(x1>m.x){
							circle(x1,y1,5);
							Liang_Barsky(m.x,m.y,x1,y1);
							circle(m.x,m.y,5);
						}else{
							circle(x1,y1,5);
							Liang_Barsky(x1,y1,m.x,m.y);
							circle(m.x,m.y,5);
						}
						FlushBatchDraw();
						EndBatchDraw();
					}else{
						clearcliprgn();
						if(x1<m.x){
							XL=x1;
							XR=m.x;
						}else{
							XL=m.x;
							XR=x1;
						}
						if(y1<m.y){
							YT=m.y;
							YB=y1;
						}else{
							YT=y1;
							YB=m.y;
						}
						setcolor(BLACK);
						if(YT<=81){
							YT=81;
						}
						if(YB<=81){
							YB=81;
						}
						rectangle(XL,YT,XR,YB);
						setcolor(RED);
					}
				}
				break;
			
			case WM_RBUTTONDOWN:
				clearcliprgn();	// 按鼠标右键清屏
				LINE_NUM=0;
				mount=0; 
				break;
				
				
			case WM_RBUTTONDBLCLK:
				return 0;	// 双击鼠标右键退出程序
				
		}
	}

	// 关闭图形窗口
	closegraph();
}

