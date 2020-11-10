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

