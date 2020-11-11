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

void update(
	Object* s,
	char input,
	int w,
	int h) {

	// ������ת��Ϊ�ƶ���
	int dx = 0;
	int dy = 0;
	// ����
	switch (input) {
	case 'a': dx = -1; break; // ��
	case 'd': dx = 1; break;  // ��
	case 'w': dy = -1; break; // �ϣ����Ͻ�Ϊ��0��0��
	case 's': dy = 1; break;  // ��
	}

	// ������ҵ�����
	int i = 0;
	for (int i = 0; i < w * h; ++i) {
		if (s[i] == OBJ_MAN || s[i] == OBJ_MAN_ON_GOAL)
			break;
	}
	int x = i % w; // x��ֵΪ���Կ�Ⱥ������
	int y = i / w; // y��ֵΪ���Կ�Ⱥ����

	// �����ƶ�
	int tx = x + dx;
	int ty = y + dy;
	// �����������ֵ����Сֵ������������Χ
	if (tx < 0 || ty < 0 || tx >= w || tx >= h) {
		return;
	}

	// 1. Ҫ�ƶ�����λ���ǿհ׻���Ŀ�ĵأ�����ƶ�
	int p = y * w + x;     // ���λ��
	int tp = ty * w + tx;  // Ŀ��λ��
	if (s[tp] == OBJ_SPACE || s[tp] == OBJ_GOAL) {
		// �����Ŀ�ĵأ��򽫸ô�����Ϊ��Ŀ�ĵ���ҡ�
		s[tp] = (s[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
		// ����Ѿ���Ŀ�ĵ��ˣ���������ڵ�λ������ΪĿ�ĵ�
		s[tp] = (s[tp] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
	}
	// 2. Ҫ�ƶ�����λ�������ӡ�������Ÿ÷������һ�������ǿհ׻���Ŀ�ĵأ����ƶ�
	else if (s[tp] == OBJ_BLOCK || s[tp] == OBJ_BLOCK_ON_GOAL) {
		//������Ÿ÷���ĵڶ�������λ���Ƿ�������ķ�Χ��
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || tx2 >= w || ty2 <0 || ty2>h) {
			return; // �����ƶ�
		}
		int tp2 = ty2 * w + tx2; // �ظ÷���ĵڶ��������λ��
		if (s[tp2] == OBJ_SPACE || s[tp2] == OBJ_GOAL) {
			//����滻
			s[tp2] = (s[tp2] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;    // �÷���ڶ�������
			s[tp] = (s[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN; // �÷�����һ������
			s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;          // ���ڵ�λ��
		}
	}
}