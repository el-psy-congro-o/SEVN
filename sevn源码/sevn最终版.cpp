#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<time.h>
#include "mmsystem.h"  
#pragma comment(lib,"winmm.lib")
void mainP();//加载主界面函数
void setting();//设置界面
void shop();//商城界面
void Rules();//规则介绍界面
void gameInterface();//进入游戏
int check(int i, int j, int map[][7]);//判断map[i][j]棋子是否处在角上的函数
int check(int i, int j, int map[][7]) {
	//上下和左右的未拆除棋子数小于2
	int down = i + 1, up = i - 1, left = j - 1, right = j + 1;
	if ((down == 7 || map[down][j] == 0 || map[up][j] == 0 || up < 0) && (left < 0 || map[i][left] == 0 || map[i][right] == 0 || right == 7)) {
		return 1;
	}
	else {
		return 0;
	}
}
void gameInterface() {

	initgraph(1280, 720);
	while (1) {
		MOUSEMSG m2;
		m2 = GetMouseMsg();
		if (m2.uMsg == WM_LBUTTONDOWN)
		{
			srand((unsigned int)time(NULL));
			int map[7][7] = { 0 };//用于存储颜色和状态，0表示已拆除，1-7表示颜色并且表示未拆除
			int is_[7][7] = //is数组为一可拆，为零不可拆，四个角初始可拆
			{
				{1,0,0,0,0,0,1},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{1,0,0,0,0,0,1}
			};
			int score1 = 0;
			int score2 = 0;
			int num[8] = { 0 };//玩家1-7颜色棋子所拆的棋子数之差
			int turns = -1; //turns为-1时表示玩家1，为1时表示玩家2
			int changeturns = 0;//表示是否转换玩家
			int step = 50;//格子长度
			int t = 0, total = 0, color = 8;//t为当前回合拆掉的棋子数，total为整个游戏过程玩家拆掉的棋子数，color表示目前可拆的棋子颜色，8为任意颜色都可拆
			int scorechange = 0;//表示是否需要改变分数，值为0时不需更改，为1时需更改，为2时代表游戏结束
			initgraph(1280, 720);//初始化窗口大小
			initgraph(1280, 720, SHOWCONSOLE);//设置控制台窗口
			setbkcolor(RGB(226, 150, 180));//背景颜色
			cleardevice();//用背景颜色遮盖原始屏幕
			setlinestyle(PS_SOLID, 2);//设置成实线，宽度为2个像素实线的粗细
			setcolor(RGB(226, 150, 180));//设置成跟背景图一样的粉色
			IMAGE BACK;//定义 变量名称 
			loadimage(&BACK, "./ziyuan/Background1.png");
			putimage(0, 0, &BACK);//在坐标0,0处放上背景图
			for (int i = 1; i <= 8; i++)
			{
				line(i * step, step, i * step, 8 * step);//x改变，平行于与y轴的线
				line(step, i * step, 8 * step, i * step);//y改变，平行于x轴的线
			}

			//鼠标消息
			settextcolor(RGB(17, 249, 218));//设置文字的颜色
			settextstyle(50, 0, "华文彩云");//设置文字的风格 字体高度 宽度（为0是自适应）字体样式
			outtextxy(100, 500, "p1玩家的分数为:");
			outtextxy(100, 570, "p2玩家的分数为:");
			settextcolor(RGB(128, 0, 255));//设置文字的颜色
			settextstyle(50, 0, "华文彩云");//设置文字的风格 字体高度 宽度（为0是自适应）字体样式
			outtextxy(400, 130, "现在是玩家p1回合");
			char s[5];
			sprintf_s(s, "%d", score1);//打印玩家1的分数
			outtextxy(500, 500, s);
			sprintf_s(s, "%d", score2);//打印玩家2的分数
			outtextxy(500, 570, s);
			settextcolor(RGB(2555, 255, 255));
			settextstyle(50, 0, "华文彩云");
			outtextxy(525, 50, "信息板");
			outtextxy(150, 420, "计分板");
			outtextxy(500, 300, "结束回合");

			int x, y, w, h;//表示坐标
			int p;//储存随机生成的颜色
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					p = rand() % 7 + 1;
					//此时暂时借用num数组存储每个颜色已经生成过的数量
					if (num[p] < 7) {//若该颜色棋子数没有达到7个则，达到7个则重新生成新的随机数
						num[p]++;//计数
						map[i][j] = p;//记下颜色
						x = step * (j + 1);
						y = step * (i + 1);
						w = step * (j + 2);
						h = step * (i + 2);
						switch (p)//涂色
						{
						case 1:
							setfillcolor(RGB(255, 0, 0));
							fillrectangle(x, y, w, h);
							break;
						case 2:
							setfillcolor(RGB(155, 62, 0));
							fillrectangle(x, y, w, h);
							break;
						case 3:
							setfillcolor(RGB(255, 253, 85));
							fillrectangle(x, y, w, h);
							break;
						case 4:
							setfillcolor(RGB(0, 255, 0));
							fillrectangle(x, y, w, h);
							break;
						case 5:
							setfillcolor(RGB(54, 126, 127));
							fillrectangle(x, y, w, h);
							break;
						case 6:
							setfillcolor(RGB(0, 0, 255));
							fillrectangle(x, y, w, h);
							break;
						case 7:
							setfillcolor(RGB(115, 43, 245));
							fillrectangle(x, y, w, h);
							break;
						}
					}
					else {
						j--;//重新生成随机数
					}
				}
			}
			//借用完num数组重置为0
			for (int i = 1; i <= 7; i++) {
				num[i] = 0;
			}
			ExMessage msg;
			setfillcolor(RGB(226, 150, 180));
			//设置点击后的覆盖色为跟背景图一样粉色
			while (true)
			{

				//该循环持续记录并反馈玩家一回合内进行的操作，回合结束退出循环，changeturns==0时则回合未结束，一直循环直至玩家点击“结束回合”按钮，changeturns==1
				while (changeturns == 0) {
					if (peekmessage(&msg, EM_MOUSE))
					{
						//接受鼠标消息
						switch (msg.message)
						{
						case WM_LBUTTONDOWN:
							if (color != 8 && msg.x >= 500 && msg.x <= 700 && msg.y >= 300 && msg.y <= 350)
								//这个坐标范围是结束回合按钮的大小范围
							{
								turns = -turns;//轮到另一玩家
								changeturns = 1;
								if (turns == 1) {
									mciSendString("close ./ziyuan/切换回合音效.mp3", NULL, 0, NULL);
									mciSendString("open ./ziyuan/切换回合音效.mp3", NULL, 0, NULL);
									mciSendString("play ./ziyuan/切换回合音效.mp3", NULL, 0, NULL);

									settextcolor(RGB(255, 255, 0));//设置文字的颜色
									settextstyle(50, 0, "华文彩云");//设置文字的风格 字体高度 宽度（为0是自适应）字体样式
									outtextxy(400, 130, "现在是玩家p2回合");

								}
								else {
									mciSendString("close ./ziyuan/切换回合音效.mp3", NULL, 0, NULL);
									mciSendString("open ./ziyuan/切换回合音效.mp3", NULL, 0, NULL);
									mciSendString("play ./ziyuan/切换回合音效.mp3", NULL, 0, NULL);

									settextcolor(RGB(128, 0, 255));//设置文字的颜色
									settextstyle(50, 0, "华文彩云");//设置文字的风格 字体高度 宽度（为0是自适应）字体样式
									outtextxy(400, 130, "现在是玩家p1回合");

								}
							}
							//若点击的不是结束回合按钮
							else {
								for (int i = 0; i < 7; i++)
									//检查49个棋子中哪些是可拆棋子，一个个与鼠标点击位置对比，若鼠标点击位置为可拆棋子，执行系列操作
								{
									for (int j = 0; j < 7; j++) {
										if (is_[i][j] == 1 && (map[i][j] == color || color == 8))
											//若检索到的这颗棋子可拆且颜色符合条件
										{
											if (msg.x >= step * (j + 1) && msg.x <= step * (j + 2) && msg.y >= step * (i + 1) && msg.y <= step * (i + 2)) //判断点击位置是否在可拆棋子范围内
											{
												color = map[i][j];//记录点击的颜色

												total++;//total记录玩家总共点击成功的棋子数
												is_[i][j] = 0;//将此棋设置为不可再点击
												if (num[color] == 0 || (num[color] + turns == 0)) {
													scorechange = 1;//若点击此棋后双方分数会发生变化，返回1
												}
												num[color] += turns;// turns玩家2为1，玩家1为-1，计算该颜色棋子被拆的数量
												if (num[color] == 7 || num[color] == -7) {
													scorechange = 2;//提前结束游戏返回2
												}
												if (total == 49 && scorechange != 2) {
													scorechange = 3;//若游戏结束，返回3
												}
												map[i][j] = 0;//将此棋颜色设置为已点击色
												solidrectangle(step * (j + 1), step * (i + 1), step * (j + 2), step * (i + 2));
												//在点击成功位置的棋子涂上背景色表示拆除

												goto escape;//跳出循环
											}
										}
									}
								}
							}escape:
							break;
						default:
							break;
						}
					}
				}
				color = 8; //重置颜色为任意色可拆
				for (int i = 0; i < 7; i++) //此循环用于更新新出现的可拆棋子的is_属性，
				{
					for (int j = 0; j < 7; j++) {
						if (map[i][j] != 0) //如果棋子没有被拆
						{
							is_[i][j] = check(i, j, map);
						}
					}
				}
				//得分判定部分，如果scorechange=2结束while循环
				if (scorechange != 0) {
					//重新统计分数
					score1 = 0;
					score2 = 0;
					for (int i = 1; i < 8; i++) {
						if (num[i] < 0) {
							score1++;
						}
						else if (num[i] > 0) {
							score2++;
						}
					}
					sprintf_s(s, "%d", score1);//打印玩家1的分数
					outtextxy(500, 500, s);
					sprintf_s(s, "%d", score2);//打印玩家2的分数
					outtextxy(500, 570, s);
					if (scorechange == 2) //某种颜色棋子拆满七颗的获胜方式
					{
						settextcolor(RGB(249, 17, 63));
						settextstyle(50, 0, "华文琥珀");
						if (turns == 1)//回合转换后是谁的回合那么获胜的应是另一个玩家
						{
							outtextxy(400, 130, "玩家p1已取得胜利");
						}
						else {
							outtextxy(400, 130, "玩家p2已取得胜利");
						}
						mciSendString("close ./ziyuan/胜利的音效.mp3", NULL, NULL, NULL);
						mciSendString("open ./ziyuan/胜利的音效.mp3", NULL, 0, NULL);
						mciSendString("play ./ziyuan/胜利的音效.mp3", NULL, 0, NULL);
						while (1)
						{
							m2 = GetMouseMsg();//获取鼠标操作，此时返回主菜单按钮可点击
							if (m2.x >= 1200 && m2.x <= 1280 && m2.y >= 650 && m2.y <= 720)
							{
								if (m2.uMsg == WM_LBUTTONDOWN)
								{
									mainP();
								}
							}
						}
					}
					if (scorechange == 3) {
						settextcolor(RGB(249, 17, 63));
						settextstyle(50, 0, "华文琥珀");
						if (score1 > score2) //棋盘中此时没有棋子且玩家1的分数大于玩家2的分数，玩家1胜利
						{
							outtextxy(400, 130, "玩家p1已取得胜利");
						}
						else {
							outtextxy(400, 130, "玩家p2已取得胜利");
						}
						mciSendString("close ./ziyuan/胜利的音效.mp3", NULL, NULL, NULL);
						mciSendString("open ./ziyuan/胜利的音效.mp3", NULL, 0, NULL);
						mciSendString("play ./ziyuan/胜利的音效.mp3", NULL, 0, NULL);
						while (1)
						{
							m2 = GetMouseMsg();//获取鼠标操作，此时返回主菜单按钮可点击
							if (m2.x >= 1200 && m2.x <= 1280 && m2.y >= 650 && m2.y <= 720)
							{
								if (m2.uMsg == WM_LBUTTONDOWN)
								{
									mainP();
								}
							}
						}
					}
				}
				scorechange = 0;// scorechange判定作用结束归零重置
				changeturns = 0;// changeturns判定回合结束作用完毕归零重置，继续进入while循环
			}
		}
	}
}
void Rules() {
	MOUSEMSG m3;
	m3 = GetMouseMsg();
	initgraph(1280, 720);
	loadimage(NULL, _T("./ziyuan/rules.png"));//加载规则图片
	while (1)
	{
		m3 = GetMouseMsg();//获取鼠标操作
		if (m3.x >= 1180 && m3.x <= 1280 && m3.y >= 0 && m3.y <= 110)//回主界面
		{

			if (m3.uMsg == WM_LBUTTONDOWN)
			{
				mainP();
			}
		}
	}
}
void setting() {
	MOUSEMSG m4;

	initgraph(1280, 720);
	loadimage(NULL, _T("./ziyuan/setting.png"));
	while (1) {
		m4 = GetMouseMsg();
		if (m4.x >= 0 && m4.x <= 150 && m4.y >= 0 && m4.y <= 90)
			//回主界面
		{
			if (m4.uMsg == WM_LBUTTONDOWN)
			{
				mainP();
			}
		}
		if (m4.uMsg == WM_LBUTTONDOWN)
		{
			if (m4.x >= 590 && m4.x <= 595 + 120 && m4.y >= 350 && m4.y <= 345 + 50)//点击播放音乐
			{
				mciSendString("open ./ziyuan/music.mp3 ", NULL, NULL, NULL);
				mciSendString("play ./ziyuan/music.mp3 repeat", 0, 0, 0);
			}
			if (m4.x >= 590 && m4.x <= 595 + 120 && m4.y >= 350 + 70 && m4.y <= 345 + 50 + 70)//点击关闭音乐
			{
				mciSendString("close ./ziyuan/music.mp3 ", NULL, NULL, NULL);

			}
		}

	}



}
void shop() {
	MOUSEMSG m3;
	m3 = GetMouseMsg();
	initgraph(1280, 720);
	loadimage(NULL, _T("./ziyuan/shop.png"));
	while (1)
	{
		m3 = GetMouseMsg();//获取鼠标操作
		if (m3.x >= 1195 && m3.x <= 1280 && m3.y >= 0 && m3.y <= 100)//回主界面
		{
			if (m3.uMsg == WM_LBUTTONDOWN)
			{
				mainP();
			}
		}


	}
}
void mainP() {
	loadimage(NULL, _T("./ziyuan/main.png"));
	MOUSEMSG m1;
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 470 && m1.x <= 470 + 390 && m1.y >= 310 && m1.y <= 310 + 90)//开始游戏
		{
			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				//进入游戏界面
				gameInterface();
			}
		}
		else if (m1.x >= 470 && m1.x <= 470 + 390 && m1.y >= 310 + 90 && m1.y <= 310 + 90 + 90)//规则介绍
		{
			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				Rules();
			}
		}
		else if (m1.x >= 1120 && m1.x <= 1280 && m1.y >= 600 && m1.y <= 720)//设置
		{


			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				setting();

			}
		}
		else if (m1.x >= 470 && m1.x <= 470 + 390 && m1.y >= 400 + 90 && m1.y <= 400 + 90 + 90)//退出
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
		else if (m1.x >= 470 + 25 && m1.x <= 470 + 390 - 25 && m1.y >= 400 + 90 + 90 && m1.y <= 400 + 90 + 90 + 90)//商城
		{

			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				shop();
			}
		}

	}

}
int main()
{
	initgraph(1280, 720);
	mainP();
}