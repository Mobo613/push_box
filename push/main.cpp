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


// ����ԭ��
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
		// ���Ȼ���
		draw(state, gStageWidth, gStageHeight);
		// ͨ�ؼ��
		if (checkClear(state, gStageWidth, gStageHeight))
		{
			break;
		}

		// ��ȡ����
		cout << "a: left d: right w: up s: down" << endl; //����˵��
		char input;
		cin >> input;

		// ����
		update(state, input, gStageWidth, gStageHeight);
	}

	// ʤ��ʱ����ʾ��Ϣ
	cout << "ʤ��" << endl;
	// ͨ��
	delete[] state; // ɾ����̬���������飬��Ҫʹ��delete []
	state = 0;

	return 0;
}


void initialize(
	Object* state,
	int width,
	int height,
	const char* stageData) {
	
	const char* d = stageData; // ��ȡָ��
	int x = 0;
	int y = 0;

	while (*d != '\0') { // ���ַ���ΪNULLʱ
		Object t;
		switch (*d) {
			case '#': t = OBJ_WALL; break;
			case ' ': t = OBJ_SPACE; break;
			case 'o': t = OBJ_BLOCK; break;
			case 'O': t = OBJ_BLOCK_ON_GOAL; break;
			case '.': t = OBJ_GOAL; break;
			case 'p': t = OBJ_MAN; break;
			case 'P': t = OBJ_MAN_ON_GOAL; break;
			case '\n': // ����һ��
				x = 0; // x���ص������
				++y;   // y������һ��
				t = OBJ_UNKNOWN; // û������
				break;
			default: t = OBJ_UNKNOWN; break; // �Ƿ�����
		}
		++d;
		if (t != OBJ_UNKNOWN) {
			state[y * width + x] = t; // д��״̬����
			++x;
		}
	}
}


void draw(
	const Object* state,
	int width,
	int height) {

	// ��Objectö�����͵�˳��
	const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' };

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object i = state[y * width + x];
			cout << font[i];
		}
		cout << endl;
	}
}