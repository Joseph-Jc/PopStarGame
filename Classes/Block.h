#include "cocos2d.h"
USING_NS_CC;

class Block :public Sprite {
public:
	//��ʼ����Ϸ���ݣ���ȣ��߶ȣ�X�ᣬY��
	static Block *createBlock(int numbers, int wight, int height, float BlockX, float BlockY);
	virtual bool init();
	CREATE_FUNC(Block);

	//��ȡ����
	int getNumber();
	//��������
	void setNumber(int num);
	//��ȡɫ������
	Point getColorBGPoint();
	//��ȡBLock��λ��
	int PopX, PopY;
	//��ȡX��Y
	int getBlockX();
	int getBlockY();
	//����X��Y
	void setBlockX(int x);
	void setBlockY(int y);
	//��ȡ��ɫ
	Color4B getColor(int num);

private:
	//��ʾ����ɫ
	int number;
	void enemyInit(int numbers, int wight, int height, float BlockX, float BlockY);
	//��ʾ�ı���
	LayerColor *layerColorBG;
};