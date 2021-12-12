//////////////////////////
//程序名称：立方体三视图及正等轴测图及其旋转 
//功    能：鼠标左键单击时绕Z轴逆时针旋转10°,右键双击后退出程序
//remember to use MBCS character set
#include <math.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define N 20																		//	N个点*** 
#define PI 3.1415926535
/*
int facet_table[6][5]={{0,1,3,2,0},{0,4,5,1,0},{4,6,7,5,4},
{2,3,7,6,2},{0,2,6,4,0},{1,5,7,3,1}};												//	面表--内嵌环表
double points[N][4]={{0,0,0,1},{0,0,50,1},{80,0,0,1},{80,0,50,1},
{0,40,0,1},{0,40,50,1},{80,40,0,1},{80,40,50,1}};									//	六面体初始顶点表(三角形)
*/
/*
int facet_table[4][4]={{0,2,1,0},{0,1,3,0},{0,3,2,0},{1,2,3,1}};					//	面表--内嵌环表
double points[N][4]={{0,0,0,1},{50,0,0,1},{25,30,0,1},{25,15,40,1}};				//	四面体初始顶点表(三角形)
*/
/*
int facet_table[8][4]={{0,1,4,0},{1,2,4,1},{4,2,3,4},
{0,4,3,0},{0,3,5,0},{1,0,5,1},{1,5,2,1},{2,5,3,2}};									//	面表--内嵌环表
double points[N][4]={{50,0,10,1},{0,50,10,1},{-50,0,-10,1},{0,-50,-10,1},
{-10,-10,50,1},{10,10,-50,1}};														//	八面体初始顶点表(三角形)
*/
double a = 1.618;
int T = 30;
int facet_table[12][6] = {
{3,16,17,7,14,3},{3,11,10,0,16,3},{0,12,4,17,16,0},{4,8,9,7,17,4},{6,15,14,7,9,6},{2,11,3,14,15,2},
{1,19,18,5,13,1},{0,10,1,13,12,0},{2,19,1,10,11,2},
{2,15,6,18,19,2},{5,18,6,9,8,5},{4,12,13,5,8,4}
};																					//	面表--内嵌环表 
double points[N][4] = {
{-T,-T,T,1},{-T,T,T,1},{T,T,T,1},{T,-T,T,1},
{-T,-T,-T,1},{-T,T,-T,1},{T,T,-T,1},{T,-T,-T,1},
{-1.0 / a * T,0,-a * T,1},{1.0 / a * T,0,-a * T,1},{-1.0 / a * T,0,a * T,1},{1.0 / a * T,0,a * T,1},
{-a * T,-1.0 / a * T,0,1},{-a * T,1.0 / a * T,0,1},{a * T,-1.0 / a * T,0,1},{a * T,1.0 / a * T,0,1},
{0,-a * T,1.0 / a * T,1},{0,-a * T,-1.0 / a * T,1},{0,a * T,-1.0 / a * T,1},{0,a * T,1.0 / a * T,1}
};																					//	十二面体初始顶点表(五边形)

int facet = 12;																		//	几个面***
int ring_points = 5;																	//	一个面上几个点*** 

int cishu = 0;

void Blank(double NOW[][4], double T_x, double T_y, double times);						//	画消隐图 
void Matrix_Multiplication(double t[][4]);											//	矩阵相乘及画图
void Number(double* x, double* y);													//	输出点的编号
void Dotted_line(int x0, int y0, int x1, int y1, int color, int wheel);					//	画虚线 
int Mouse_event();																	//	鼠标事件 
void muti_Matrix_by_PPT(double Trans_points[N][4], double another[4][4]);			//	旋转矩阵乘法专用函数
void ThreeD_rotate(int degree_x, int degree_y, int degree_z);							//	参数分别为绕x,y,z逆时针旋转的角度
void lsometric_translation();														//	画正等轴测投影图变换 
void three_facet_view();															//	画三视图 
void initializer();																	//	界面初始化

int main() {
	initializer();
	ThreeD_rotate(35, 10, 0);

	three_facet_view();

	lsometric_translation();

	if (!Mouse_event()) return 0;

	//停住
	_getch();
	closegraph();
	return 0;
}
void initializer() {
	initgraph(800, 640);

	setbkcolor(WHITE);
	setcolor(WHITE);
	fillrectangle(0, 0, 800, 640);
	setcolor(BLACK);
	rectangle(0, 0, 799, 639);
	setcolor(BLACK);
	line(0, 80, 800, 80);

	RECT r1 = { 0, 0, 800, 80 };
	drawtext(_T("\n单击左键一次绕Z轴旋转10°\n\n双击右键可退出程序"), &r1, DT_CENTER | DT_VCENTER);
	RECT r2 = { 0, 81, 70, 100 };
	drawtext(_T("正视图"), &r2, DT_CENTER | DT_VCENTER);
	RECT r3 = { 0, 620, 70, 640 };
	drawtext(_T("俯视图"), &r3, DT_CENTER | DT_VCENTER);
	RECT r4 = { 730, 81, 800, 100 };
	drawtext(_T("侧视图"), &r4, DT_CENTER | DT_VCENTER);
	RECT r5 = { 700, 620, 800, 640 };
	drawtext(_T("正等轴测图"), &r5, DT_CENTER | DT_VCENTER);

	HRGN rgn = CreateRectRgn(71, 101, 699, 619);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);

	setcolor(BLACK);
	rectangle(0, 0, 800, 640);
	setcolor(RED);
}
void muti_Matrix_by_PPT(double Trans_points[N][4], double another[4][4]) {
	int i, j, k;
	double New[N][4] = { 0 };
	for (i = 0; i < N; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++) {
				New[i][j] += Trans_points[i][k] * another[k][j];
			}
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < 4; j++) {
			Trans_points[i][j] = New[i][j];
		}
	}
}
void ThreeD_rotate(int degree_x, int degree_y, int degree_z) {
	double cita_x = degree_x * PI / 180;
	double cita_y = degree_y * PI / 180;
	double cita_z = degree_z * PI / 180;
	double X_rotate[4][4] = { {1,0,0,0},{0,cos(cita_x),sin(cita_x),0},{0,-sin(cita_x),cos(cita_x),0},{0,0,0,1} };
	double Y_rotate[4][4] = { {cos(cita_y),0,-sin(cita_y),0},{0,1,0,0},{sin(cita_y),0,cos(cita_y),0},{0,0,0,1} };
	double Z_rotate[4][4] = { {cos(cita_z),sin(cita_z),0,0},{-sin(cita_z),cos(cita_z),0,0},{0,0,1,0},{0,0,0,1} };
	muti_Matrix_by_PPT(points, X_rotate);
	muti_Matrix_by_PPT(points, Y_rotate);
	muti_Matrix_by_PPT(points, Z_rotate);
}
void lsometric_translation() {
	static double ex[4][4];
	double beta = 45, cita = 180 * atan(1.0 / sqrt(2)) / PI;							//cita下,beta右
	beta = beta * PI / 180.0;
	cita = cita * PI / 180.0;

	ex[0][0] = cos(beta);
	ex[0][2] = -sin(beta) * sin(cita);
	ex[1][0] = -sin(beta);
	ex[1][2] = -cos(beta) * sin(cita);
	ex[2][2] = cos(cita);
	ex[3][3] = 1;

	Matrix_Multiplication(ex);
}
void three_facet_view() {
	double one[4][4] = { 0 }, two[4][4] = { 0 }, thr[4][4] = { 0 };

	one[0][0] = 1;one[2][2] = 1;one[3][3] = 1;
	two[0][0] = 1;two[1][2] = -1;two[3][2] = -160;two[3][3] = 1;
	thr[1][0] = -1;thr[2][2] = 1;thr[3][0] = -160;thr[3][3] = 1;

	Matrix_Multiplication(one);
	Matrix_Multiplication(two);
	Matrix_Multiplication(thr);
}
void Matrix_Multiplication(double ex[][4]) {
	double NOW[N][4];
	int i, j, k;

	for (i = 0; i < N; i++) {
		for (j = 0; j < 4; j++) {
			NOW[i][j] = 0;
			for (k = 0; k < 4; k++) {
				NOW[i][j] += points[i][k] * ex[k][j];
			}
		}
	}
	Blank(NOW, 400, 350, 2);
}
void Blank(double NOW[][4], double T_x, double T_y, double times) {
	double x[N], y[N];
	int i, j;
	cishu++;
	cishu = cishu % 5;
	if (!cishu) cishu++;

	for (i = 0; i < N; i++) {
		if (cishu == 4) {
			x[i] = NOW[i][0] * times + 550;
			y[i] = NOW[i][2] * times + 430;
		}
		else {
			x[i] = -NOW[i][0] * times + 225;
			y[i] = -NOW[i][2] * times + 210;
			if (cishu == 2) y[i] -= 100;
		}
	}
	Number(x, y);

	double D, E, F, N_fa;
	int Xs, Ys, Zs, Xa, Ya, Za, Xb, Yb, Zb;
	int x1, y1, x2, y2;
	for (i = 0; i < facet; i++) {								//facet个面 
		Xs = points[facet_table[i][0]][0];Ys = points[facet_table[i][0]][1];Zs = points[facet_table[i][0]][2];
		Xa = points[facet_table[i][1]][0];Ya = points[facet_table[i][1]][1];Za = points[facet_table[i][1]][2];
		Xb = points[facet_table[i][2]][0];Yb = points[facet_table[i][2]][1];Zb = points[facet_table[i][2]][2];
		D = 1.0 * (Ya - Ys) * (Zb - Za) - (Za - Zs) * (Yb - Ya);
		E = 1.0 * (Za - Zs) * (Xb - Xa) - (Xa - Xs) * (Zb - Za);
		F = 1.0 * (Xa - Xs) * (Yb - Ya) - (Ya - Ys) * (Xb - Xa);

		if (-E == 0) E = 0;
		if (-D == 0) D = 0;
		if (-F == 0) F = 0;
		N_fa = sqrt(D * D + E * E + F * F);
		double COS;
		if (cishu == 1) {
			COS = E * 1.0 / N_fa;
		}
		else if (cishu == 3) {
			COS = D * 1.0 / N_fa;
		}
		else if (cishu == 2) {
			COS = F * 1.0 / N_fa;
		}
		else if (cishu == 4) {
			Xs = NOW[facet_table[i][0]][0];Ys = NOW[facet_table[i][0]][1];Zs = NOW[facet_table[i][0]][2];
			Xa = NOW[facet_table[i][1]][0];Ya = NOW[facet_table[i][1]][1];Za = NOW[facet_table[i][1]][2];
			Xb = NOW[facet_table[i][2]][0];Yb = NOW[facet_table[i][2]][1];Zb = NOW[facet_table[i][2]][2];
			E = 1.0 * (Za - Zs) * (Xb - Xa) - (Xa - Xs) * (Zb - Za);
			COS = E * 1.0 / N_fa;
		}
		if (COS > 0) {
			for (j = 0; j < ring_points; j++) {								//ring_points个点
				x1 = x[facet_table[i][j]];
				y1 = y[facet_table[i][j]];
				x2 = x[facet_table[i][j + 1]];
				y2 = y[facet_table[i][j + 1]];
				line(x1, y1, x2, y2);
			}
		}
		else {
			for (j = 0; j < ring_points; j++) {								//ring_points个点
				x1 = x[facet_table[i][j]];
				y1 = y[facet_table[i][j]];
				x2 = x[facet_table[i][j + 1]];
				y2 = y[facet_table[i][j + 1]];
				Dotted_line(x1, y1, x2, y2, RED, 0);
			}
		}
	}
}
void Number(double* x, double* y) {
	for (int i = 0; i < N; i++) {
		circle(int(x[i]), int(y[i]), 3);
		char str[10];
		int a = i + 1;
		sprintf_s(str, "%d", a);
		outtextxy(int(x[i]), int(y[i]), str);
	}
}
int z = 0;
void Putpixel(int x, int y, int color, int wheel) {
	z++;
	if (wheel == 0 && z % 4 == 0) {
		putpixel(x, y, color);
	}
	int i, j;
	for (i = 0; i < 2 * wheel + 1; i++) {
		for (j = int(wheel / 2); j < 2 * wheel; j++) {
			putpixel(x - wheel + i, y - wheel + j, color);
		}
	}
	for (i = int(wheel / 2); i < 2 * wheel; i++) {
		for (j = 0; j < 2 * wheel + 1; j++) {
			putpixel(x - wheel + i, y - wheel + j, color);
		}
	}
}
void Dotted_line(int x0, int y0, int x1, int y1, int color, int wheel) {
	wheel = 0;
	int a, b, delta1, delta2, d, x, y;		/*	delta1代表d>0	delta2代表d<0	*/
	a = y0 - y1;
	b = x1 - x0;

	x = x0;
	y = y0;
	Putpixel(x, y, color, wheel);

	if (-a == 0) {
		while (x < x1) {
			x++;
			Putpixel(x, y, color, wheel);
		}
		while (x > x1) {
			x--;
			Putpixel(x, y, color, wheel);
		}
	}
	else if (b == 0) {
		while (y < y1) {
			y++;
			Putpixel(x, y, color, wheel);
		}
		while (y > y1) {
			y--;
			Putpixel(x, y, color, wheel);
		}
	}

	if (-a > 0 && b > 0) {					/*第一象限*/
		if (-a - b >= 0) {					/*斜率大于等于1*/
			d = a + 2 * b;
			delta1 = 2 * (a + b);
			delta2 = 2 * b;
			while (y < y1) {
				if (d < 0) {
					y++;
					d += delta2;
				}
				else {
					x++;
					y++;
					d += delta1;
				}
				Putpixel(x, y, color, wheel);
			}
		}
		else {							/*斜率小于1大于0*/
			d = 2 * a + b;
			delta1 = 2 * a;
			delta2 = 2 * (a + b);
			while (x < x1) {
				if (d < 0) {
					x++;
					y++;
					d += delta2;
				}
				else {
					x++;
					d += delta1;
				}
				Putpixel(x, y, color, wheel);
			}
		}
	}
	else if (-a < 0 && b>0) {				/*第四象限*/
		if (-a + b <= 0) {					/*斜率小于等于-1*/
			d = a - 2 * b;
			delta1 = -2 * b;
			delta2 = 2 * a - 2 * b;
			while (y > y1) {
				if (d < 0) {
					x++;
					y--;
					d += delta2;
				}
				else {
					y--;
					d += delta1;
				}
				Putpixel(x, y, color, wheel);
			}
		}
		else {							/*斜率大于-1小于0*/
			d = 2 * a - b;
			delta1 = 2 * a - 2 * b;
			delta2 = 2 * a;
			while (x < x1) {
				if (d < 0) {
					x++;
					d += delta2;
				}
				else {
					x++;
					y--;
					d += delta1;
				}
				Putpixel(x, y, color, wheel);
			}
		}
	}

}
int Mouse_event() {
	MOUSEMSG m;		// 定义鼠标消息
	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:

			break;

		case WM_LBUTTONUP:
			BeginBatchDraw();
			clearcliprgn();
			ThreeD_rotate(0, 0, 10);
			three_facet_view();
			lsometric_translation();
			FlushBatchDraw();
			EndBatchDraw();
			break;

		case WM_MOUSEMOVE:

			break;

		case WM_RBUTTONDOWN:

			break;

		case WM_RBUTTONDBLCLK:
			return 0;	// 双击鼠标右键退出程序

		}
	}
}
