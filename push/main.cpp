#include<iostream>

using namespace std;

const char gStageData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

const int gStageWidth = 8;
const int gStageHeight = 5;

enum Object
{
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BLOCK,
	OBJ_BLOCK_ON_GOAL,
	OBJ_MAN,
	OBJ_MAN_ON_GOAL,

	OBJ_UNKNOWN,
};


// 函数原型
void initialize(Object* state, int w, int h, const char* stageData);
void draw(const Object* state, int w, int h);
void update(Object* state, char input, int w, int h);
bool checkClear(const Object* state, int w, int h);


int main()
{
	// 创建状态数组
	Object* state = new Object[gStageWidth * gStageHeight];
	// 初始化场景
	initialize(state, gStageWidth, gStageHeight, gStageData);
	// 主循环
	while (true)
	{
		// 首先绘制
		draw(state, gStageWidth, gStageHeight);
		// 通关检测
		if (checkClear(state, gStageWidth, gStageHeight))
		{
			break;
		}

		// 获取输入
		cout << "a: left d: right w: up s: down" << endl; //操作说明
		char input;
		cin >> input;

		// 更新
		update(state, input, gStageWidth, gStageHeight);
	}

	// 胜利时的提示信息
	cout << "胜利" << endl;
	// 通关
	delete[] state; // 删除动态创建的数组，需要使用delete []
	state = 0;

	return 0;
}


void initialize(
	Object* state,
	int width,
	int height,
	const char* stageData) {
	
	const char* d = stageData; // 读取指针
	int x = 0;
	int y = 0;

	while (*d != '\0') { // 当字符不为NULL时
		Object t;
		switch (*d) {
			case '#': t = OBJ_WALL; break;
			case ' ': t = OBJ_SPACE; break;
			case 'o': t = OBJ_BLOCK; break;
			case 'O': t = OBJ_BLOCK_ON_GOAL; break;
			case '.': t = OBJ_GOAL; break;
			case 'p': t = OBJ_MAN; break;
			case 'P': t = OBJ_MAN_ON_GOAL; break;
			case '\n': // 到下一行
				x = 0; // x返回到最左边
				++y;   // y进到下一行
				t = OBJ_UNKNOWN; // 没有数据
				break;
			default: t = OBJ_UNKNOWN; break; // 非法数据
		}
		++d;
		if (t != OBJ_UNKNOWN) {
			state[y * width + x] = t; // 写入状态数组
			++x;
		}
	}
}


void draw(
	const Object* state,
	int width,
	int height) {

	// 按Object枚举类型的顺序
	const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' };

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object i = state[y * width + x];
			cout << font[i];
		}
		cout << endl;
	}
}

void update(
	Object* s,
	char input,
	int w,
	int h) {

	// 将输入转换为移动量
	int dx = 0;
	int dy = 0;
	// 方向
	switch (input) {
	case 'a': dx = -1; break; // 左
	case 'd': dx = 1; break;  // 右
	case 'w': dy = -1; break; // 上，左上角为（0，0）
	case 's': dy = 1; break;  // 下
	}

	// 查找玩家的坐标
	int i = 0;
	for (int i = 0; i < w * h; ++i) {
		if (s[i] == OBJ_MAN || s[i] == OBJ_MAN_ON_GOAL)
			break;
	}
	int x = i % w; // x的值为除以宽度后的余数
	int y = i / w; // y的值为除以宽度后的商

	// 处理移动
	int tx = x + dx;
	int ty = y + dy;
	// 检查坐标的最大值和最小值，不允许超出范围
	if (tx < 0 || ty < 0 || tx >= w || tx >= h) {
		return;
	}

	// 1. 要移动到的位置是空白或者目的地，玩家移动
	int p = y * w + x;     // 玩家位置
	int tp = ty * w + tx;  // 目标位置
	if (s[tp] == OBJ_SPACE || s[tp] == OBJ_GOAL) {
		// 如果是目的地，则将该处设置为“目的地玩家”
		s[tp] = (s[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
		// 如果已经在目的地了，则将玩家所在的位置设置为目的地
		s[tp] = (s[tp] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
	}
	// 2. 要移动到的位置有箱子。如果沿着该方向的下一个网格是空白或者目的地，则移动
	else if (s[tp] == OBJ_BLOCK || s[tp] == OBJ_BLOCK_ON_GOAL) {
		//检测沿着该方向的第二个网格位置是否在允许的范围内
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || tx2 >= w || ty2 <0 || ty2>h) {
			return; // 不能推动
		}
		int tp2 = ty2 * w + tx2; // 沿该方向的第二个网格的位置
		if (s[tp2] == OBJ_SPACE || s[tp2] == OBJ_GOAL) {
			//逐个替换
			s[tp2] = (s[tp2] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;    // 该方向第二个网格
			s[tp] = (s[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN; // 该方向下一个网格
			s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;          // 现在的位置
		}
	}
}