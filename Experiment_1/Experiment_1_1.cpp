// 编译环境：Visual C++ 6.0，EasyX 20190219(beta)
// http://www.easyx.cn
//
#include <graphics.h>
#include <conio.h>
void Putpixel(int x,int y,int color,int wheel){
	
	for(int i=0 ; i<2*wheel+1 ; i++){
		for(int j=0 ; j<2*wheel+1 ; j++){
			putpixel(x-wheel+i,y-wheel+j,color);
		}
	}
	
}
void Any_slope_Put_pixel(int x0,int y0,int x1,int y1,int color,int wheel){
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
int main()
{
	// 初始化图形窗口
	initgraph(640, 480);

	MOUSEMSG m;		// 定义鼠标消息

	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		int x1,y1;
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
					// 记住起点
					x1=m.x;
					y1=m.y;
				break;

			case WM_LBUTTONUP:
				if(x1>m.x){
					Any_slope_Put_pixel(m.x,m.y,x1,y1,RED,m.wheel);
				}else{
					Any_slope_Put_pixel(x1,y1,m.x,m.y,RED,m.wheel);
				}
				// 鼠标左键弹起,记住终点并画线
				break;

			case WM_RBUTTONUP:
				cleardevice();	// 按鼠标右键清屏
				break;
				
			case WM_RBUTTONDBLCLK:
				return 0;	// 双击鼠标右键退出程序
				
			case WM_MOUSEWHEEL:
				m.wheel++;
		}
	}

	// 关闭图形窗口
	closegraph();
}

