#include<iostream>

using namespace std;

const char gStageData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
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