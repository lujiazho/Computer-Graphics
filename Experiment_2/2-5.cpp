#include <iostream> 
#include <graphics.h>
#include <conio.h>
using namespace std; 

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
int XL=150,XR=540,YB=174,YT=449;
int encode(int x, int y, int *code){
	int c; 
	c=0;
	if(x<XL){
		c=c|LEFT;
	}else if(x>XR){
		c=c|RIGHT;
	}
	if(y<YB){
		c=c|BOTTOM;
	}else if(y>YT){
		c=c|TOP;
	}
	
	*code=c;
	return 0;
}
int Cohen_Sutherla(int x1,int y1,int x2,int y2){
	int code1,code2,code;
	int x,y;
	encode(x1,y1,&code1);
	encode(x2,y2,&code2);
	while(code1!=0 || code2!=0){
		if( (code1 & code2)!=0 ){
			return 0;
		}
		code=code1;
		if(code1==0){
			code=code2;
		}
		if( (LEFT & code)!=0 ){
			x=XL;
 			y=y1+(y2-y1)*(XL-x1)/(x2-x1);
		}else if( (RIGHT & code)!=0 ){
			x=XR;
			y=y1+(y2 -y1)*(XR-x1)/(x2-x1);
		}else if ((BOTTOM & code) != 0){
			y=YB;
			x=x1+(x2-x1)*(YB-y1)/(y2-y1);
		}else if ((TOP & code) != 0){
			y=YT;
			x=x1+(x2-x1)*(YT-y1)/(y2-y1);
		}
		if (code==code1){
			x1=x; y1=y; encode(x1,y1, &code1);
		}else{
			x2=x; y2=y; encode(x2,y2, &code2);
		}
	}
	line(x1,y1,x2,y2);
	return 0; 
}
int Mouse_event();
void order(int* shuzu,int num);
void Find_intersections(int poly_points[][2], int& poly_size);
bool IsWithin(int x,int y,int poly_points[][2],int poly_size);

int poly_size = 0;
int poly_size_backup = 0;
int poly_points[50][2] = {{50,60},{70,90},{90,60},{160,60},{160,160},{2,160},{2,60}};
int poly_points_backup[50][2] = {{50,60},{70,90},{90,60},{160,60},{160,160},{2,160},{2,60}};

void initializer(){
	initgraph(800, 640);
	
	setbkcolor(WHITE);
	setcolor(WHITE);
	fillrectangle(0,0,800,640);
	setcolor(BLACK);
	rectangle(0,0,799,639);
	setcolor(BLACK);
	line(0,80,800,80);

	RECT r = {0, 0, 800, 80};
	drawtext(_T("\n左键点击任意9个点作为多边形的顶点\n第一个点和最后一个不必重合\n双击右键退出程序，单击右键重置"), &r, DT_CENTER | DT_VCENTER );

	HRGN rgn = CreateRectRgn(1, 81, 799, 639);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);

	setcolor(BLACK);
	rectangle(XL,YT,XR,YB);
}
void clipping(){
	//计算出交点
	Find_intersections(poly_points, poly_size);
	
	//四边形边上交点分类
	int i,j;
	int L_point[20],B_point[20],R_point[20],T_point[20];
	int L_num=0,B_num=0,R_num=0,T_num=0;
	for(i=0 ; i<poly_size ; i++){
		if(poly_points[i][0]==XL && poly_points[i][1]!=YB && poly_points[i][1]!=YT){	//左 
			L_point[L_num]=poly_points[i][1];
			L_num++;
		}
		if(poly_points[i][1]==YB && poly_points[i][0]!=XL && poly_points[i][0]!=XR){	//下 
			B_point[B_num]=poly_points[i][0];
			B_num++;
		}
		if(poly_points[i][0]==XR && poly_points[i][1]!=YB && poly_points[i][1]!=YT){	//右 
			R_point[R_num]=poly_points[i][1];
			R_num++;
		}
		if(poly_points[i][1]==YT && poly_points[i][0]!=XL && poly_points[i][0]!=XR){	//上 
			T_point[T_num]=poly_points[i][0];
			T_num++;
		}
	}
	
	//判断角点是否为多边形内点 
	bool one=false,two=false,three=false,four=false;		//分别代表左上，左下，右下，右上
	if(IsWithin(XL,YB,poly_points_backup,poly_size_backup)) one=true; else one=false;
	if(IsWithin(XL,YT,poly_points_backup,poly_size_backup)) two=true; else two=false;
	if(IsWithin(XR,YT,poly_points_backup,poly_size_backup)) three=true; else three=false;
	if(IsWithin(XR,YB,poly_points_backup,poly_size_backup)) four=true; else four=false;
	
	clearcliprgn();
	setcolor(RED);
	for(int z=0 ; z<poly_size_backup ; z++){
		circle(poly_points_backup[z][0],poly_points_backup[z][1],3);
	}

	//颜色
	setcolor(GREEN);

	//画边线及四边形角线 
	order(L_point,L_num);
	order(B_point,B_num);
	order(R_point,R_num);
	order(T_point,T_num);
	if(!one){
		for(j=0 ; j<L_num ; j+=2){
			if(j!=L_num-1){
				line(XL,L_point[j],XL,L_point[j+1]);
			}
		}
		for(j=0 ; j<B_num ; j+=2){
			if(j!=B_num-1){
				line(B_point[j],YB,B_point[j+1],YB);
			}
		}
	}else{
		if(B_num==0) B_point[0]=XR;
		line(B_point[0],YB,XL,YB);
		if(L_num==0) L_point[0]=YT;
		line(XL,L_point[0],XL,YB);
	}
	if(!two){
		for(j=L_num-1 ; j>=0 ; j-=2){
			if(j!=0){
				line(XL,L_point[j],XL,L_point[j-1]);
			}
		}
		for(j=0 ; j<T_num ; j+=2){
			if(j!=T_num-1){
				line(T_point[j],YT,T_point[j+1],YT);
			}
		}
	}else{
		if(T_num==0) T_point[0]=XR;
		line(T_point[0],YT,XL,YT);
		if(L_num==0) L_point[L_num-1]=YB;
		line(XL,L_point[L_num-1],XL,YT);
	}
	if(!three){
		for(j=R_num-1 ; j>=0 ; j-=2){
			if(j!=0){
				line(XR,R_point[j],XR,R_point[j-1]);
			}
		}
		for(j=T_num-1 ; j>=0 ; j-=2){
			if(j!=0){
				line(T_point[j],YT,T_point[j-1],YT);
			}
		}
	}else{
		if(T_num==0) T_point[T_num-1]=XL;
		line(T_point[T_num-1],YT,XR,YT);
		if(R_num==0) R_point[R_num-1]=YB;
		line(XR,R_point[R_num-1],XR,YT);
	}
	if(!four){
		for(j=0 ; j<R_num ; j+=2){
			if(j!=R_num-1){
				line(XR,R_point[j],XR,R_point[j+1]);
			}
		}
		for(j=B_num-1 ; j>=0 ; j-=2){
			if(j!=0){
				line(B_point[j],YB,B_point[j-1],YB);
			}
		}
	}else{
		if(B_num==0) B_point[B_num-1]=XL;
		line(B_point[B_num-1],YB,XR,YB);
		if(R_num==0) R_point[0]=YT;
		line(XR,R_point[0],XR,YB);
	}
	
	//画四边形内部的线 
	for(i=0 ; i<poly_size_backup-1 ; i++){
		Cohen_Sutherla(poly_points_backup[i][0],poly_points_backup[i][1],poly_points_backup[i+1][0],poly_points_backup[i+1][1]);
	}
	Cohen_Sutherla(poly_points_backup[i][0],poly_points_backup[i][1],poly_points_backup[0][0],poly_points_backup[0][1]);
}
int main()
{
	// 初始化图形窗口
	initializer();
	
	while(1){
		int out=Mouse_event();				 
		if(!out) return 0;
		
		//开始裁剪
		clipping();

		//重置
		poly_size=0;
		poly_size_backup=0;
	}
	
	// 关闭图形窗口
	closegraph();
	return 0;
}
void Repaint(int LINE[50][4],int LINE_NUM){
	setcolor(BLACK);
	rectangle(XL,YT,XR,YB);
	setcolor(RED);

	for(int i=0 ; i<LINE_NUM ; i++){
		circle(LINE[i][0],LINE[i][1],3);
		line(LINE[i][0],LINE[i][1],LINE[i][2],LINE[i][3]);
	}
}
int Mouse_event(){
	MOUSEMSG m;		// 定义鼠标消息
	int LINE[300][4];
	int LINE_NUM=0;
	int x1,y1;			//上一个点
	bool first=false;	//第一个点点下去
	while(true)
	{
		// 获取一条鼠标消息
		if(poly_size==9){
			return 1;
		}
		m = GetMouseMsg();
		
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				first=true;
				x1=m.x;
				y1=m.y;
				circle(m.x,m.y,3);
				poly_points[poly_size][0]=m.x;
				poly_points[poly_size][1]=m.y;
				poly_points_backup[poly_size][0]=m.x;
				poly_points_backup[poly_size][1]=m.y;
				poly_size++;
				poly_size_backup++;
				if(poly_size>1){
					LINE[LINE_NUM][0]=poly_points[poly_size-2][0];
					LINE[LINE_NUM][1]=poly_points[poly_size-2][1];
					LINE[LINE_NUM][2]=poly_points[poly_size-1][0];
					LINE[LINE_NUM][3]=poly_points[poly_size-1][1];
					LINE_NUM++;
					line(poly_points[poly_size-2][0],poly_points[poly_size-2][1],
					poly_points[poly_size-1][0],poly_points[poly_size-1][1]);
				}
				break;

			case WM_LBUTTONUP:

				// 鼠标左键弹起,记住终点并画线
				break;
			case WM_MOUSEMOVE:
				if(LINE_NUM>=0 && first){
					BeginBatchDraw();
					clearcliprgn();
					Repaint(LINE,LINE_NUM);
					circle(x1,y1,3);
					line(m.x,m.y,x1,y1);
					circle(m.x,m.y,3);
					FlushBatchDraw();
					EndBatchDraw();
				}
				break;
			
			case WM_RBUTTONDOWN:
				clearcliprgn();
				setcolor(BLACK);
				rectangle(XL,YT,XR,YB);
				poly_size=0;
				poly_size_backup=0;
				first=false;
				LINE_NUM=0;
				break;

			case WM_RBUTTONDBLCLK:
				return 0;	// 双击鼠标右键退出程序
				
		}
	}
}
void order(int* shuzu,int num){
	for(int i=0 ; i<num-1 ; i++){
		for(int j=i+1 ; j<num ; j++){
			if(shuzu[i]>shuzu[j]){
				int ex=shuzu[i];
				shuzu[i]=shuzu[j];
				shuzu[j]=ex;
			}
		}
	}
}
double x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){ 
	if(x3==x4){
		return x3;
	}else if(x1==x2){
		return x1;
	}
    double num = (1.0*(x3*y4-y3*x4)/(x3-x4))-(1.0*(x1*y2-y1*x2)/(x1-x2)); 
    double den = (1.0*(y1-y2)/(x1-x2))-(1.0*(y3-y4)/(x3-x4)); 
    return num/den;
} 
double y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){ 
	if(x1==x2){
		return ( 1.0*(y3-y4)*x1/(x3-x4)+1.0*(x3*y4-y3*x4)/(x3-x4) );
	}else if(x3==x4){
		return ( 1.0*(y1-y2)*x3/(x1-x2)+1.0*(x1*y2-y1*x2)/(x1-x2) );
	}
    return (1.0*(y1-y2)*x_intersect(x1,y1,x2,y2,x3,y3,x4,y4)/(x1-x2))+(1.0*(x1*y2-y1*x2)/(x1-x2)); 
} 
void Find_intersections(int poly_points[][2], int& poly_size){
	int intersection[80][2];
	int new_size=0;
	int x1,y1,x2,y2;
	for(int j=0 ; j<4 ; j++){
		if(j==0){x1=XL;y1=YB;x2=XL;y2=YT;}
		if(j==1){x1=XR;y1=YT;x2=XL;y2=YT;}
		if(j==2){x1=XR;y1=YB;x2=XR;y2=YT;}
		if(j==3){x1=XL;y1=YB;x2=XR;y2=YB;}
		for(int i=0 ; i<poly_size ; i++){
			if(i!=poly_size-1){
				intersection[new_size][0]=int(x_intersect(x1,y1,x2,y2,poly_points[i][0],poly_points[i][1],poly_points[i+1][0],poly_points[i+1][1]));
				intersection[new_size][1]=int(y_intersect(x1,y1,x2,y2,poly_points[i][0],poly_points[i][1],poly_points[i+1][0],poly_points[i+1][1]));
				int x=intersection[new_size][0];
				int y=intersection[new_size][1];
				if(x1<=x2 && poly_points[i][0]<poly_points[i+1][0]){
					if(x>=x1&&x<=x2&&x>=poly_points[i][0]&&x<=poly_points[i+1][0]&&y>=y1&&y<=y2)
						new_size++;
				}else if(x1<=x2 && poly_points[i][0]>poly_points[i+1][0]){
					if(x>=x1&&x<=x2&&x<=poly_points[i][0]&&x>=poly_points[i+1][0]&&y>=y1&&y<=y2)
						new_size++;
				}else if(x1>=x2 && poly_points[i][0]>poly_points[i+1][0]){
					if(x<=x1&&x>=x2&&x<=poly_points[i][0]&&x>=poly_points[i+1][0]&&y>=y1&&y<=y2)
						new_size++;
				}else if(x1>=x2 && poly_points[i][0]<poly_points[i+1][0]){
					if(x<=x1&&x>=x2&&x>=poly_points[i][0]&&x<=poly_points[i+1][0]&&y>=y1&&y<=y2)
						new_size++;
				}
			}else{
				intersection[new_size][0]=int(x_intersect(x1,y1,x2,y2,poly_points[i][0],poly_points[i][1],poly_points[0][0],poly_points[0][1]));
				intersection[new_size][1]=int(y_intersect(x1,y1,x2,y2,poly_points[i][0],poly_points[i][1],poly_points[0][0],poly_points[0][1]));
				int x=intersection[new_size][0];
				int y=intersection[new_size][1];
				if(x1<=x2 && poly_points[i][0]<poly_points[0][0]){
					if(x>=x1&&x<=x2&&x>=poly_points[i][0]&&x<=poly_points[0][0]&&y>=y1&&y<=y2)
						new_size++;
				}else if(x1<=x2 && poly_points[i][0]>poly_points[0][0]){
					if(x>=x1&&x<=x2&&x<=poly_points[i][0]&&x>=poly_points[0][0]&&y>=y1&&y<=y2)
						new_size++;
				}else if(x1>=x2 && poly_points[i][0]>poly_points[0][0]){
					if(x<=x1&&x>=x2&&x<=poly_points[i][0]&&x>=poly_points[0][0]&&y>=y1&&y<=y2)
						new_size++;
				}else if(x1>=x2 && poly_points[i][0]<poly_points[0][0]){
					if(x<=x1&&x>=x2&&x>=poly_points[i][0]&&x<=poly_points[0][0]&&y>=y1&&y<=y2)
						new_size++;
				}
			}
		}
	}
	for(int k=0 ; k<new_size ; k++){
		poly_points[k][0]=intersection[k][0];
		poly_points[k][1]=intersection[k][1];
	}
	poly_size=new_size;
}
bool IsWithin(int x,int y,int poly_points[][2],int poly_size){
	int sect_num=0;
    for(int i=0 ; i<poly_size ; i++){
    	if(i!=poly_size-1){
    		long int x_sect=x_intersect(x,y,x+5,y,poly_points[i][0],poly_points[i][1],poly_points[i+1][0],poly_points[i+1][1]);
    		if(((x_sect<=poly_points[i][0]&&x_sect>=poly_points[i+1][0]) || (x_sect>=poly_points[i][0]&&x_sect<=poly_points[i+1][0]))&&x_sect>=x&&( (y<=poly_points[i][1]&&y>=poly_points[i+1][1]) || (y>=poly_points[i][1]&&y<=poly_points[i+1][1]) )){
    			sect_num++;
			}
		}else{
			long int x_sect=x_intersect(x,y,x+5,y,poly_points[i][0],poly_points[i][1],poly_points[0][0],poly_points[0][1]);
			if(((x_sect<=poly_points[i][0]&&x_sect>=poly_points[0][0]) || (x_sect>=poly_points[i][0]&&x_sect<=poly_points[0][0]))&&x_sect>=x&&( (y<=poly_points[i][1]&&y>=poly_points[0][1]) || (y>=poly_points[i][1]&&y<=poly_points[0][1]) )){
    			sect_num++;
			}
		}
	}
	if(sect_num%2==1){
		return true;
	}
	return false;
}
