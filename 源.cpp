#include<iostream>
#include<cstring>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
//#include"resource.h"//������Դ֮����һ��resource.hͷ�ļ� �ǵü���
#include<Windows.h>
#include<mmsystem.h>
#include<iomanip>//����setw()����
#include<ctime>
#include<cstdlib>//����srand()������rand()����
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include<cmath>
#include<math.h>
#include<algorithm>
#include <fstream>
#include<stdio.h>
#undef UNICODE
using namespace std;
MOUSEMSG mouse; //��������ȫ�ֱ���
int board[25][25];//���������   0Ϊ�� 1Ϊ��  2Ϊ��  ��������
int r = 1;//�غ���
int option = 0;//ѡ���������ɫ �Ұ�����Ϊȫ�ֱ��� ��Ϊ�����и�����Ҫ�õ�
int x = 0, y = 0;//�µ��������� ��Ҳ��Ϊ��ȫ�ֱ��� ��Ϊ�Ƚ���Ҫ
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
bool lose_directly = false;
//���׼�������  1280x650��С��Ļ
int X1 = 0;//���ĺ���
int Y1 = 0;
void screen_of_game();
void choose_color();
int main();
void save();
void load();
void game();
void restore();
IMAGE img[5];				// ����ͼƬ
void load_picture() {//��ݶ
	loadimage(&img[0], L"�㶹.png");
	loadimage(&img[1], L"���.png");
	mciSendString(_T("open music.mp3 alias mymusic"), NULL, 0, NULL);
	loadimage(&img[2], L"����.png", 80, 80);
	loadimage(&img[3], L"����.png", 80, 80);
	loadimage(&img[4], L"����.png", 80, 80);
}
void victory() {//ʤ������   //��ݶ
	cleardevice();//��ջ���	
	loadimage(NULL, L"victory.png");				//����ͼƬ
}
void defeat() {//ʤ������   //��ݶ
	cleardevice();//��ջ���	
	loadimage(NULL, L"defeat.png");				//����ͼƬ
}
bool have_saved = false;
void get_x_and_y() {
	FlushMouseMsgBuffer();// ��������Ϣ������
	while (true) {
		mouse = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
		if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
		{
			int xs = mouse.x;
			int ys = mouse.y;
			if (xs >= 700 && xs <= 750 && ys >= 50 && ys <= 100)
			{
				//��������
				lose_directly = true;
				defeat();
				while (true) {
					mouse = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
					if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
					{
						return;
					}
				}
			}
			if (xs >= 800 && xs <= 850 && ys >= 50 && ys <= 100)
			{
				//��������
				main();
				return;
			}
			if (xs >= 900 && xs <= 950 && ys >= 50 && ys <= 100)
			{
				//���˴���
				save();
				have_saved = true;
				return;
			}
			if (xs <= 660 && xs >= 100 && ys >= 50 && ys <= 610)
			{
				for (int i = 0; i < 9; i++)

					for (int j = 0; j < 9; j++)
						if (70 * i + 100 - xs <= 20 && xs - (70 * i + 100) <= 20 && 70 * j + 50 - ys <= 20 && ys - (70 * j + 50) <= 20)
						{
							x = i;
							y = j;
							return;
						}

			}//ѡ�����������xy
		}
	}
}

//��Ϸ˵��
void init()//��ݶ
{

	initgraph(1280, 650); // ��ʼͼ�λ����棬���	
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	loadimage(NULL, L"smy.jpg");				//����ͼƬ
	//��Ļ������
	setlinecolor(BLACK);
	FlushMouseMsgBuffer();// ��������Ϣ������

	while (true) {
		mouse = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
		if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
		{
			X1 = mouse.x;
			Y1 = mouse.y;
			if (X1 >= 200 && X1 <= 350 && Y1 >= 510 && Y1 <= 580)//�����һ��99999��
			{
				victory();
				FlushMouseMsgBuffer();// ��������Ϣ������
				while (true) {
					mouse = GetMouseMsg();
					if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
					{
						init();
						return;
					}
				}
			}
			if (X1 >= 390 && X1 <= 540 && Y1 >= 510 && Y1 <= 580)//���������Ϸ
			{
				choose_color();
				return;
			}
			if (X1 >= 730 && X1 <= 910 && Y1 >= 510 && Y1 <= 580)//������ȡ�浵
			{
				load();
				return;

			}
			if (X1 >= 950 && X1 <= 1100 && Y1 >= 510 && Y1 <= 580)//�������Ϸ˵��
			{
				cleardevice();//��ջ���	
				loadimage(NULL, L"��Χ�����.png");
				FlushMouseMsgBuffer();// ��������Ϣ������
				while (true) {
					mouse = GetMouseMsg();
					if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
					{
						init();
						return;
					}
				}
			}
		}
	}
}
//xs=70x+100  ys=70y+50

void screen_of_game() {//��ݶ
	cleardevice();//��ջ���	
	loadimage(NULL, L"����ͼƬ.png");
	putimage(700, 50, &img[2]);
	putimage(800, 50, &img[3]);
	putimage(900, 50, &img[4]);
	//restore();
	//�����̵���
	setlinecolor(YELLOW);
	//������
	for (int i = 0; i < 9; i++)
		line(100, 50 + 70 * i, 660, 50 + 70 * i);
	for (int i = 0; i < 9; i++)
		line(100 + 70 * i, 50, 100 + 70 * i, 610);
}

void delay() {
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 10000; j++) {
			for (int k = 0; k < 12; k++) {
			}
		}
	}
}
int has_found[9][9] = { 0 };//�����ж�����ʱ���Ƿ��ҹ�(x,y)�������ҹ��ˣ�����1��������0
//�жϱ߽�
inline bool inBorder(int x, int y)//��ϣ
{
	return x >= 0 && x < 9 && y >= 0 && y < 9;
}
//Ӧ�������������һ���ӣ������ԱߵĶԷ�����û�������䣻
//�������һ���ӣ����������λ����������ɱ��

//�ж�(x,y)���������Ƿ����� ��ϣ
bool has_air(int x, int y)
{
	has_found[x][y] = true;
	bool flag = false;
	for (int dir = 0; dir < 4; dir++)
	{
		int temp_x = x + dx[dir], temp_y = y + dy[dir];
		if (inBorder(temp_x, temp_y))
		{
			if (board[temp_x][temp_y] == 0)
				flag = true;
		}
	}
	for (int dir = 0; dir < 4; dir++)
	{
		int temp_x = x + dx[dir], temp_y = y + dy[dir];
		if (inBorder(temp_x, temp_y))
		{
			if (board[temp_x][temp_y] == board[x][y] && !has_found[temp_x][temp_y])
				if (has_air(temp_x, temp_y))
					flag = true;
		}
	}
	return flag;
}
//�ж���ɱ  true ��ɱ   false���� ��ϣ
bool suicide(int x, int y)
{
	if (!has_air(x, y))
	{
		memset(has_found, 0, sizeof(has_found));
		return true;
	}
	else
	{
		memset(has_found, 0, sizeof(has_found));
		return false;
	}
}

//�ж��Ƿ����   false  ����    true û���� ��ϣ
bool not_eat_opponent(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int temp_x = x + dx[i];
		int temp_y = y + dy[i];
		if (inBorder(temp_x, temp_y) && board[temp_x][temp_y] != 0 && board[temp_x][temp_y] != board[x][y])
		{
			if (!has_air(temp_x, temp_y))
			{
				memset(has_found, 0, sizeof(has_found));
				return false;
			}
		}
	}
	memset(has_found, 0, sizeof(has_found));
	return true;
}

//�ж�������һ��������û��   ��ϣ
//�ж�(x,y)���Ƿ�����ɫΪcolor �����ӵĺϷ�λ��   true�Ϸ�(����֮���䣩 false���Ϸ� �����˾����ˣ�
bool legal_step(int x, int y, int color)//�ڻ�û�а�colorɫ�������������
//�ж�(x,y)���Ƿ�����ɫΪcolor�����ӵĺϷ�λ��
{
	bool ans = false;
	if (board[x][y] == 0)
	{
		board[x][y] = color;
		if (!suicide(x, y) && not_eat_opponent(x, y))
			ans = true;
		board[x][y] = 0;
		memset(has_found, 0, sizeof(has_found));
	}
	return ans;
}
//�ж�һ��λ����Χ���ڱ߽��ڵ�λ���м���  ��ϣ
int calc_dir(int fx, int fy) {
	int cnt = 0;
	for (int i = 0; i < 4; ++i) {
		int temp_x = fx + dx[i], temp_y = fy + dy[i];
		if (inBorder(temp_x, temp_y)) ++cnt;
	}
	return cnt;
}
//�ж�һ��λ�����ܵ��ڱ߽��ڵ�λ�����м���colɫ������  ��ϣ
int check_cross(int fx, int fy, int col) {
	int cnt = 0;
	for (int i = 0; i < 4; ++i) {
		int cx = fx + dx[i], cy = fy + dy[i];
		if (inBorder(cx, cy)) {
			if (board[cx][cy] == col) ++cnt;
		}
	}
	return cnt;
}
int eyelist[10][10] = { 0 };
//�ж��Ƿ��ǵ����˹������Ѿ��γɵ��ۣ�Ŀ��������ڰ��Լ��γɵ�������  ��ϣ
void eye()
{
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
		{
			if (board[x][y] == 0)
			{
				int cnt = 0;
				for (int i = 0; i < 4; i++)
				{
					int xx = x + dx[i];
					int yy = y + dy[i];
					if (inBorder(xx, yy) && board[xx][yy] == 3 - option)
						cnt++;
				}
				if (cnt == calc_dir(x, y))
					eyelist[x][y] = 3;
			}
		}
}
//����Ϸ��ʼ�� ��������� �غ�������
void origin() {
	memset(board, 0, sizeof(board));
	r = 1;
}
//�������

//��ݶ
//����µ�ĳһ���Ƿ�Ϸ�(������Ϸ����
bool checkstep(int x, int y) {
	if (x < 0 || y < 0 || x >= 9 || y >= 9)
		return false;
	if (board[x][y] != 0)
		return false;
	if (x == 4 && y == 4 && r == 1)//�������ֲ������м�
		return false;
	return true;
}
void choose_color() {
	cleardevice();//��ջ���	
	loadimage(NULL, L"ѡ�ڰ�.png");
	FlushMouseMsgBuffer();// ��������Ϣ������
	while (true) {
		mouse = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
		if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
		{
			X1 = mouse.x;
			Y1 = mouse.y;
			if (X1 >= 10 && X1 <= 120 && Y1 >= 90 && Y1 <= 200)
			{
				option = 1;
				return;
			}
			if (X1 >= 140 && X1 <= 250 && Y1 >= 90 && Y1 <= 200)
			{
				option = 2;
				return;
			}
		}
	}
}

//��̬������������ �õ�x��y��ļ�ֵ

int valuepoint[9][9] = { 0 };
int significance[9][9];
//��significance��ֵ ��ϣ
void give_significance() {

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			significance[i][j] = 1;
}
//ѡ��,ÿһ���µ�������valuepoint����  ����ÿ�����value ��ϣ
int give_valuepoint(int x, int y, int color)
{
	int value = 0;
	if (checkstep(x, y))
	{//�����������(���ŵ�)
		board[x][y] = color;// ����
		if (suicide(x, y) || !not_eat_opponent(x, y)) {//�����һ�����˾�����
			value = -10000;
			board[x][y] = 0;
			return value;
		}
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (!legal_step(i, j, 3 - color))//����������� �������˵��Ի���
					value += significance[i][j];
			}
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (!legal_step(i, j, color))//�������²��������˻���
					value -= significance[i][j];
			}
		board[x][y] = 0;
	}
	valuepoint[x][y] = value;
	return value;
}
//���������پ��� ��ϣ
int manhattan_d(int x1, int y1, int x2, int y2)
{
	int d = abs(x1 - x2) + abs(y1 - y1);
	return d;
}
//��ݶ
void scatter() {
	int cnt = 0;//��ɢ�����з����������ܵ���
	int x_scatter[81], y_scatter[81];
	int max1 = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (!legal_step(i, j, 3 - option) || !checkstep(i, j))
				continue;
			else//�����ǿ�����  ѡ���������������е�������پ������Сֵ
			{
				int min1 = 20;
				for (int ii = 0; ii < 9; ii++)
					for (int jj = 0; jj < 9; jj++) {
						if (manhattan_d(i, j, ii, jj) < min1)
							min1 = manhattan_d(i, j, ii, jj);
					}//min1�Ƕ��ڣ�i��j������˵�����پ������Сֵ
				if (min1 > max1) {//�����پ�����С�����ֵ�ĵ�
					cnt = 0;
					max1 = min1;
					x_scatter[cnt] = i;
					y_scatter[cnt] = j;
					cnt++;
				}
				if (min1 == max1) {//�����پ�����С�����ֵ�ĵ�
					x_scatter[cnt] = i;
					y_scatter[cnt] = j;
					cnt++;
				}

			}
		}
	if (cnt == 1)
	{
		x = x_scatter[0];
		y = y_scatter[0];
	}
	if (cnt > 1) {
		int k = 0;
		srand((unsigned)time(NULL));//��ϵͳʱ��������������
		k = rand() % cnt;//��0��cnt-1��ѡһ����
		x = x_scatter[k];
		y = y_scatter[k];
	}
}
//minmax����
int maxi = 2;//����
//��ϣ
void give_maxivalue()
{
	if (r <= 30)
		maxi = 1;
	else if (r >= 50)
		maxi = 3;
	else
		maxi = 2;
}
int temp_x1, temp_y1;
//��ϣ
int dfs(int depth, int color, int number)//���� �ӵ���ɫ ֵ ��ɫ
{
	give_maxivalue();
	if (depth > maxi)//�ѵ�����ײ㣬����
	{
		return give_valuepoint(temp_x1, temp_y1, color);
	}
	int ret = 0, flag = 0;
	if (color == 3 - option) {
		//�����max��
		ret = -2147483647, flag = 0;
	}
	if (color == option) {
		//�����min��
		ret = 2147483647, flag = 0;
	}
	//int ret = 0, flag = 0;//��ֵ��һ������0�����ݵ�ǰmin����max������
	if (color == 3 - option)//��max�� 
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (legal_step(i, j, color))//ö�����ӵ㲢����
				{
					temp_x1 = i;
					temp_y1 = j;
					ret = max(ret, dfs(depth + 1, 3 - color, ret));//�����ӽڵ�ķ���ֵȡmax
					if (ret > number)//��֦
					{
						flag = 1;
						break;
					}
				}
				if (flag == 1)
					break;
			}
			return ret;
		}
	if (color == option)//��min��
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (legal_step(i, j, color))//ö�����ӵ㲢����
				{
					temp_x1 = i;
					temp_y1 = j;
					ret = min(ret, dfs(depth + 1, 3 - color, ret));//�����ӽڵ�ķ���ֵȡmax
					if (ret < number)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 1)
					break;
			}
			return ret;
		}
}
bool flag1 = 0;//�����ж��Ƿ�¶Է�����
void blockopponenteye()//��ס�Է���Ҫ�������  ��ϣ
{
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (legal_step(i, j, 3 - option)) {
				if (check_cross(i, j, option) == calc_dir(i, j) - 1) {
					x = i;
					y = j;
					flag1 = 1;
				}
			}
			if (flag1) break;
		}
		if (flag1) break;
	}
}

bool ans1 = false;//�����ж��Ƿ������Լ�����
void makeeye()//�ֶ�����  ��ϣ
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 0)
			{
				int cnt1 = 0;
				int cnt2 = 0;
				int x0 = 0;
				int y0 = 0;
				for (int k = 0; k < 4; k++)
				{
					int xx = i + dx[k];
					int yy = j + dy[k];
					if (inBorder(xx, yy) && board[xx][yy] == 3 - option)//�Լ������Ӹ���
						cnt1++;
					if (inBorder(xx, yy) && board[xx][yy] == 0)//��λ
					{
						cnt2++;
						x0 = xx;
						y0 = yy;
					}
				}
				if (cnt1 == calc_dir(i, j) - 1 && cnt2 == 1 && legal_step(x0, y0, 3 - option))
				{
					ans1 = true;
					x = x0;
					y = y0;
					break;
				}
			}
		}
		if (ans1 == true)
			break;
	}
}
//�˹�����

//ͨ����ֵ����������ѡ��������ӵĵط�
//int point_of_maxvalue[81][9][9];// ��ֵ���ĵ�
struct point {
	int x;
	int y;
};
point point_of_maxvalue[81];
int cnt_of_maxvalue = 0;
bool findnoteye = false;
//��ݶ
void putchess_of_AI() {//���Ե���ɫ����3-option
	if (r == 1)
	{
		srand((unsigned)time(NULL));//��ϵͳʱ��������������
		x = rand() % 9;
		y = rand() % 9;
		while (!checkstep(x, y)) {
			srand((unsigned)time(NULL));//��ϵͳʱ��������������
			x = rand() % 9;
			y = rand() % 9;
		}
	}
	else {
		blockopponenteye();
		if (!flag1)//û�ж¶Է�����
		{
			makeeye();//ȥ�Լ�����
			if (!ans1)//�Լ�û�������
			{
				eye();
				int maxvalue = -2147483648;
				cnt_of_maxvalue = 0;
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 9; j++) {//����ÿ����ļ�ֵ
						if (checkstep(i, j) && legal_step(i, j, 3 - option) && eyelist[i][j] != 3) {//������������¶��Ҳ����������
							findnoteye = true;//���п��Բ��ð��Լ����۶��ϵ�λ��
							int temp_max = dfs(0, 3 - option, 2147483647);
							if (temp_max > maxvalue) {
								cnt_of_maxvalue = 0;
								maxvalue = temp_max;
								point_of_maxvalue[cnt_of_maxvalue].x = i;
								point_of_maxvalue[cnt_of_maxvalue].y = j;
								cnt_of_maxvalue++;
							}
							if (temp_max == maxvalue) {
								point_of_maxvalue[cnt_of_maxvalue].x = i;
								point_of_maxvalue[cnt_of_maxvalue].y = j;
								cnt_of_maxvalue++;
							}
						}

					}
				if (cnt_of_maxvalue == 1)
				{
					x = point_of_maxvalue[cnt_of_maxvalue - 1].x;
					y = point_of_maxvalue[cnt_of_maxvalue - 1].y;//ѡ���˵����µ�x y
				}
				if (cnt_of_maxvalue > 1)
				{
					//ִ�д�ɢ����
					scatter();
					//ѡ���˵����µ�x y
				}
				if (!findnoteye)
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 9; j++)
							if (eyelist[i][j] == 3)
							{
								x = i;
								y = j;
							}
			}
		}
	}
}

//��ɢ��ѡAI������
//��ϣ
void save()
{
	ofstream fout("temp.txt");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			fout << board[i][j] << " ";
		fout << endl;
	}
	fout << option << " ";
	fout << r;
	fout.close();
}
//��ϣ
void load() {
	ifstream fin("temp.txt");
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			fin >> board[i][j];
	fin >> option;
	fin >> r;
	//fin.close();
}
//��ݶ
void restore() {
	//��ԭ����ľ���
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			X1 = 70 * i + 100;
			Y1 = 70 * j + 50;
			if (board[i][j] == 1)
			{
				putimage(X1 - 30, Y1 - 30, &img[0]);
			}
			if (board[i][j] == 2)
			{
				putimage(X1 - 30, Y1 - 30, &img[1]);

			}
		}
}
//��ݶ
void game() {
	screen_of_game();
	restore();
	while (true) {
		if (r % 2 == 2 - option) {//����ֵ��Լ���
			lose_directly = false;//�Ƿ��������
			have_saved = false;
			get_x_and_y();
			//���Ҫ�µĻ�		
			if (lose_directly)
				return;
			if (have_saved)
				return;
			while (!checkstep(x, y)) {
				get_x_and_y();
			}
			if (checkstep(x, y)) {//����Ϸ�
				board[x][y] = option;
				X1 = 70 * x + 100;
				Y1 = 70 * y + 50;
				if (option == 1)
				{
					putimage(X1 - 30, Y1 - 30, &img[0]);
				}
				if (option == 2)
				{
					putimage(X1 - 30, Y1 - 30, &img[1]);

				}
				if (suicide(x, y) || !not_eat_opponent(x, y))
				{
					//����Ľ���
					defeat();
					FlushMouseMsgBuffer();// ��������Ϣ������
					while (true) {
						mouse = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
						if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
						{
							return;
						}
					}
				}
				r++;//�غ�����һ
			}
		}
		if (r % 2 != option) {//����ֵ�������
			/*srand((unsigned)time(NULL));//��ϵͳʱ��������������
			x = rand() % 9;
			y = rand() % 9;
			while (!checkstep(x, y)) {
				srand((unsigned)time(NULL));//��ϵͳʱ��������������
				x = rand() % 9;
				y = rand() % 9;
			}*/
			putchess_of_AI();//�õ���x, y ;
			ans1 = false;
			flag1 = 0;
			memset(eyelist, 0, sizeof(eyelist));
			board[x][y] = 3 - option;
			X1 = 70 * x + 100;
			Y1 = 70 * y + 50;
			if (option == 1)
				putimage(X1 - 30, Y1 - 30, &img[1]);
			if (option == 2)
				putimage(X1 - 30, Y1 - 30, &img[0]);
			if (suicide(x, y) || !not_eat_opponent(x, y))
			{
				//�������� ����Ӯ��
				victory();
				while (true) {
					mouse = GetMouseMsg();// ��ȡһ�������Ϣ�����û�У��͵ȴ�
					if (mouse.uMsg == WM_LBUTTONDOWN)	//�Ƿ�������
					{
						return;
					}
				}
			}
			r++;//�غ�����һ
		}
	}

}
int main() {
	load_picture();
	init();
	game();

	return 0;
}

