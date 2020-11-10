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

void initialize(Object* state, int w, int h, const char* stageData);
void draw(const Object* state, int w, int h);
void update(Object* state, char input, int w, int h);
bool checkClear(const Object* state, int w, int h);


int main()
{
	// ����״̬����
	Object* state = new Object[gStageWidth * gStageHeight];
	// ��ʼ������
	initialize(state, gStageWidth, gStageHeight, gStageData);
	// ��ѭ��
	while (true)
	{
		getInput();
		updateGame();
		draw();
	}

	// ʤ��ʱ����ʾ��Ϣ
	cout << "ʤ��" << endl;
	// ͨ��
	delete[] state; // ɾ����̬���������飬��Ҫʹ��delete []
	state = 0;

	return 0;
}