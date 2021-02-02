// 编译环境：Visual C++ 6.0，EasyX 20190219(beta)
// http://www.easyx.cn
//
#include <graphics.h>
#include <conio.h>
#include <math.h>
void graph_3(int r,int color,int yuan_x,int yuan_y){				//实验1-3
	int x,y,d;
	x=0;
	y=r;
	d=5-4*r;
	putpixel(x+yuan_x,y+yuan_y,color);
	while(x<y){
		if(d<0){
			d+=8*x+12;
			x++;
		}else{
			d+=8*(x-y)+20;
			x++;
			y--;
		}
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
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
		putpixel(x+yuan_x,y+yuan_y,color);
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
			case WM_LBUTTONDOWN:
				// 如果点左键的同时按下了 Ctrl 键
				if (m.mkCtrl)
					// 画一个大方块
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				else
					// 记住起点
					x1=m.x;
					y1=m.y;
				break;

			case WM_LBUTTONUP:
				r=int(sqrt( (m.x-x1)*(m.x-x1) + (m.y-y1)*(m.y-y1) ));
				graph_3(r,YELLOW,x1,y1);

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

