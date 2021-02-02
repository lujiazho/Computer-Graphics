#include <graphics.h>
#include <conio.h>
#include <math.h>
void Putpixel(int x,int y,int color,int wheel){
	if(wheel==0){
		putpixel(x,y,color);
	}
	int i,j;
	for(i=0 ; i<2*wheel+1 ; i++){
		for(j=int(wheel/2) ; j<int(3/2*wheel) ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
	for(i=int(wheel/2) ; i<int(3/2*wheel) ; i++){
		for(j=0 ; j<2*wheel+1 ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
}
void graph_8(int r,int color,int yuan_x,int yuan_y,int wheel){				//实验1-8
	int x,y,d;
	x=0;
	y=r;
	d=5-4*r;
	Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	while(x<y){
		if(d<0){
			d+=8*x+12;
			x++;
		}else{
			d+=8*(x-y)+20;
			x++;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	d=5-8*r;
	while(y>0){
		if(d<0){
			d+=8*(x-y)+20;
			x++;
			y--;
		}else{
			d+=12-8*y;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	/**/
	x=r;
	y=0;
	d=5-4*r;
	while(x>-y){
		if(d<0){
			d+=12-8*y;
			y--;
		}else{
			d+=20-8*(x+y);
			x--;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	d=5-8*r;
	while(x>0){
		if(d<0){
			d+=20-8*(x+y);
			x--;
			y--;
		}else{
			d+=12-8*x;
			x--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	/**/
	x=0;
	y=r;
	d=5-4*r;
	while(y>-x){
		if(d<0){
			d+=-8*x+12;
			x--;
		}else{
			d+=-8*(x+y)+20;
			x--;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	d=5-8*r;
	while(y>0){
		if(d<0){
			d+=-8*(x+y)+20;
			x--;
			y--;
		}else{
			d+=-8*y+12;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	/**/
	x=-r;
	y=0;
	d=5-4*r;
	while(y>x){
		if(d<0){
			d+=-8*y+12;
			y--;
		}else{
			d+=-8*(y-x)+20;
			x++;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	d=5-8*r;
	while(x<0){
		if(d<0){
			d+=-8*(y-x)+20;
			x++;
			y--;
		}else{
			d+=+8*x+12;
			x++;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
}
void graph_8_2(int a,int b,int color,int yuan_x,int yuan_y,int wheel){				//实验1-8
	int xp,yp,d,x,y;
	xp=int(a*a/sqrt(a*a+b*b));
	yp=int(b*b/sqrt(a*a+b*b));
	x=0;
	y=b;
	
	d=int(b*b+(-b+0.25)*a*a);
	Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	while(x<xp){
		if(d<=0){
			d+=(2*x+3)*b*b;
			x++;
		}else{
			d+=(2*x+3)*b*b+(-2*y+2)*a*a;
			x++;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	d=int(b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b);
	while(y>0){
		if(d<=0){
			d+=(-2*y+3)*a*a+(2*x+2)*b*b;
			x++;
			y--;
		}else{
			d+=(-2*y+3)*a*a;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	/**/
	xp=int(-a*a/sqrt(a*a+b*b));
	yp=int(b*b/sqrt(a*a+b*b));
	x=0;
	y=b;
	
	d=int(b*b+(-b+0.25)*a*a);
	Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	while(x>xp){
		if(d<=0){
			d+=(-2*x+3)*b*b;
			x--;
		}else{
			d+=(-2*x+3)*b*b+(-2*y+2)*a*a;
			x--;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	} 
	d=int(b*b*(x-0.5)*(x-0.5)+a*a*(y-1)*(y-1)-a*a*b*b);
	while(y>0){
		if(d<=0){
			d+=(-2*y+3)*a*a+(-2*x+2)*b*b;
			x--;
			y--;
		}else{
			d+=(-2*y+3)*a*a;
			y--;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	/*下面是第四象限*/
	xp=int(a*a/sqrt(a*a+b*b));
	yp=int(-b*b/sqrt(a*a+b*b));
	x=0;
	y=-b;
	
	d=int(b*b+(-b+0.25)*a*a);
	Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	while(x<xp){
		if(d<=0){
			d+=(2*x+3)*b*b;
			x++;
		}else{
			d+=(2*x+3)*b*b+(2*y+2)*a*a;
			x++;
			y++;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	} 
	d=int(b*b*(x+0.5)*(x+0.5)+a*a*(y+1)*(y+1)-a*a*b*b);
	while(y<0){
		if(d<=0){
			d+=(2*y+3)*a*a+(2*x+2)*b*b;
			x++;
			y++;
		}else{
			d+=(2*y+3)*a*a;
			y++;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
	/*下面是第三象限*/
	xp=int(-a*a/sqrt(a*a+b*b));
	yp=int(-b*b/sqrt(a*a+b*b));
	x=0;
	y=-b;
	
	d=int(b*b+(-b+0.25)*a*a);
	Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	while(x>xp){
		if(d<=0){
			d+=(-2*x+3)*b*b;
			x--;
		}else{
			d+=(-2*x+3)*b*b+(2*y+2)*a*a;
			x--;
			y++;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	} 
	d=int(b*b*(x-0.5)*(x-0.5)+a*a*(y+1)*(y+1)-a*a*b*b);
	while(y<0){
		if(d<=0){
			d+=(2*y+3)*a*a+(-2*x+2)*b*b;
			x--;
			y++;
		}else{
			d+=(2*y+3)*a*a;
			y++;
		}
		Putpixel(x+yuan_x,y+yuan_y,color,wheel);
	}
}
int main()
{
	// 初始化图形窗口
	initgraph(640, 480);

	MOUSEMSG m;		// 定义鼠标消息
	
	int wheel_yuan=0;
	int wheel_tuo=0;
	int SHIFT=0;
	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		int x1,y1,r;
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				// 如果点左键的同时按下了 Ctrl 键
				if (m.mkCtrl)
					// 画一个大方块
					if(SHIFT%2==0){
						wheel_yuan++;
					}else{
						wheel_tuo++;
					}
					
				else if(m.mkShift)
					SHIFT++;
				else
					// 记住起点
					x1=m.x;
					y1=m.y;
				break;

			case WM_LBUTTONUP:
				r=int(sqrt( (m.x-x1)*(m.x-x1) + (m.y-y1)*(m.y-y1) ));
				if(SHIFT%2==0){
					graph_8(r,YELLOW,x1,y1,wheel_yuan);
				}else{
					graph_8_2(r,int(r*2/3),YELLOW,x1,y1,wheel_tuo);
				}
				

				// 鼠标左键弹起,记住终点并画圆圈
				break;

			case WM_RBUTTONUP:
				cleardevice();	// 按鼠标右键清屏
				break;
				
				
			case WM_RBUTTONDBLCLK:
				return 0;	// 双击鼠标右键退出程序
		}
		
	}

	// 关闭图形窗口
	closegraph();
}

