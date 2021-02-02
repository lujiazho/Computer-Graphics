// 编译环境：Visual C++ 6.0，EasyX 20190219(beta)
// http://www.easyx.cn
//
#include <graphics.h>
#include <conio.h>
#include <math.h>
void graph_4(int a,int b,int color,int yuan_x,int yuan_y){				//实验1-4
	int xp,yp,d,x,y;
	xp=int(a*a/sqrt(a*a+b*b));
	yp=int(b*b/sqrt(a*a+b*b));
	x=0;
	y=b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x<xp){
		if(d<=0){
			d+=(2*x+3)*b*b;
			x++;
		}else{
			d+=(2*x+3)*b*b+(-2*y+2)*a*a;
			x++;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	/**/
	xp=int(-a*a/sqrt(a*a+b*b));
	yp=int(b*b/sqrt(a*a+b*b));
	x=0;
	y=b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x>xp){
		if(d<=0){
			d+=(-2*x+3)*b*b;
			x--;
		}else{
			d+=(-2*x+3)*b*b+(-2*y+2)*a*a;
			x--;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	/*下面是第四象限*/
	xp=int(a*a/sqrt(a*a+b*b));
	yp=int(-b*b/sqrt(a*a+b*b));
	x=0;
	y=-b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x<xp){
		if(d<=0){
			d+=(2*x+3)*b*b;
			x++;
		}else{
			d+=(2*x+3)*b*b+(2*y+2)*a*a;
			x++;
			y++;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
	}
	/*下面是第三象限*/
	xp=int(-a*a/sqrt(a*a+b*b));
	yp=int(-b*b/sqrt(a*a+b*b));
	x=0;
	y=-b;
	
	d=int(b*b+(-b+0.25)*a*a);
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x>xp){
		if(d<=0){
			d+=(-2*x+3)*b*b;
			x--;
		}else{
			d+=(-2*x+3)*b*b+(2*y+2)*a*a;
			x--;
			y++;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
	}
}
int main()
{
	// 初始化图形窗口
	initgraph(640, 480);

	MOUSEMSG m;		// 定义鼠标消息

	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		int x1,y1,r;
		switch(m.uMsg)
		{
			/*case WM_MOUSEMOVE:
				// 鼠标移动的时候画红色的小点
				putpixel(m.x, m.y, RED);
				break;
			*/
			case WM_LBUTTONDOWN:
					// 记住起点
					x1=m.x;
					y1=m.y;
				break;

			case WM_LBUTTONUP:
				r=int(sqrt( (m.x-x1)*(m.x-x1) + (m.y-y1)*(m.y-y1) ));
				graph_4(r,int(r*2/3),YELLOW,x1,y1);

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

