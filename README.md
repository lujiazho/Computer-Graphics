# Computer Graphics
中国农业大学计算机图形学完整代码和报告，欢迎参考学习

## Environment
- VC++ 6.0
- easyX

## Experiment
### Experiment Ⅰ —— Scan Conversion Algorithm 扫描转换算法

| (●'◡'●) |  SHOWCASE |
|--|--|
| Experiment 1-1：绘制任意斜率的直线 | <img src="https://img-blog.csdnimg.cn/2021012422353524.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 1-3：用中点画圆法画圆 | <img src="https://img-blog.csdnimg.cn/202101242235593.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 1-4：中点画圆法画椭圆 | <img src="https://img-blog.csdnimg.cn/2021012422364235.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 1-5：中点画圆法画圆弧 | <img src="https://img-blog.csdnimg.cn/20210124223700589.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 1-7：具有宽度的直线 | <img src="https://img-blog.csdnimg.cn/20210124223711180.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 1-8：具有宽度的圆和椭圆 | <img src="https://img-blog.csdnimg.cn/2021012422372236.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |

实验一中的代码并未进行优化，从截图可以看出，UI界面不够友好（毕竟刚学习这门课），操作起来比后面的实验更复杂

---
### Experiment Ⅱ —— clipping Algorithm 裁剪算法

| (●'◡'●) |  SHOWCASE |
|--|--|
| Experiment 2-1：Cohen-Sutherland算法实现直线段裁剪 | <img src="https://img-blog.csdnimg.cn/20210124224226636.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 2-2：Liang-Barsky算法实现直线段裁剪 | <img src="https://img-blog.csdnimg.cn/20210124224245160.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 2-5：综合算法实现多边形裁剪（自创） | <img src="https://img-blog.csdnimg.cn/20210124224303776.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |

**多边形裁剪**：该算法实现了对任意多边形的裁剪，程序中设置多边形的顶点为固定的9个。算法上的实现分为三步：
- **第一**，先画裁剪框内的线段：用直线段裁剪算法对多边形进行裁剪，最后留下在裁剪框内的线段
- **第二**，画裁剪框四个顶点旁的线。先判断裁剪框的四个顶点是否在多边形内，具体判断方法是：过该顶点一条射线与多边形的每条线段相交，如果交点有奇数个，则在多边形内，反之则在多边形外。如果顶点在多边形内，那么它邻接的在裁剪框边上的点与它之间一定有连线
- **第三**，画裁剪框四条边上与顶点无交点的线段。取出在多边形外的四边形顶点，从这一点开始，往邻接的两条边方向画，得到该边和多边形线段的交点，然后画第奇数个到下一个点上的线段，若有奇数个点，则略去最后一个。*例如：假设左下角的点在多边形外，则从该点向上和向右画，当向上画时，假如有5个交点（y1,y2,y3,y4,y5），则画线段（y1,y2），（y3,y4），y5则省略*

---
### Experiment Ⅲ —— Image Transformation 图形变换

| (●'◡'●) |  SHOWCASE |
|--|--|
| Experiment 3-2：实现多步复合变换，并显示动画效果 | <img src="https://img-blog.csdnimg.cn/20210124224458203.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 3-3：任意直线的对称变换 | <img src="https://img-blog.csdnimg.cn/20210124224513426.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |

**不足之处**：各种二维变换在数学上理论上都能得到结果，但实现在程序里难免有舍入，会导致一些四边形放大倍数时，四边形的同一边可能有错位

---
### Experiment Ⅳ —— 3D Graphics Projection and Blanking 三维图形投影和消隐

| (●'◡'●) |  SHOWCASE |
|--|--|
| Experiment 4-4和4-5：完成图形绕某一坐标轴旋转（包括三视图和正等轴测图） | <img src="https://img-blog.csdnimg.cn/20210124224556201.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |

如下是源码中**正十二面体**坐标对应的点
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210124225241734.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70)

**不足之处**：由于采用的消隐算法是外法线消隐算法，此算法只对凸多面体有效，这是该消隐算法的局限；且该消隐算法是按照每个面的边数都相等的多面体来具体实现的，于是对于由三角形和四边形等组成的混合型多面体无法在原有算法中实现，若有需要还得进一步修改

---
### Experiment Ⅴ —— Curve and Surface 曲线和曲面

| (●'◡'●) |  SHOWCASE |
|--|--|
| Experiment 5-2绘制Bezier曲线 | <img src="https://img-blog.csdnimg.cn/20210124224901340.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |
| Experiment 5-4绘制B样条曲面 | <img src="https://img-blog.csdnimg.cn/20210124224916487.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjgxNTg0Ng==,size_16,color_FFFFFF,t_70" width="50%"> |

**存在问题**：Bezier曲线的代码中对点采用递归方式计算，当增加一个点时，需要对之前已经计算过的低阶Bezier函数重新进行计算，使得空间消耗和时间消耗增加（当时并未进行优化）。所以当点越来越多时，程序运行速度会大大降低，甚至可能程序崩溃（当有10几个点时）
