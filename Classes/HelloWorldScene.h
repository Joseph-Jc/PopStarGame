#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	CREATE_FUNC(HelloWorld);
	//��Ϸ����
	void background();

	//�Զ�������Ϸ�е�10*10���η���
	void autoCreateBlock(Size size);

	//�������
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	//��ʾ�ɼ�
	void showScore();

	//��óɼ�
	int getScore();

	//���óɼ�
	void setScore(int score);
private:
	//���巽�����飬������ŷ���
	Block *blockSprite[10][10];
	//����õ��������
	Block *getBlockSprite(Size size, Point touch);
	//���������ŵ���ķ���
	__Array *blockClickArr;
	//���ݵ���Ķ��󣬻�ȡ���������ҵ�����
	__Array *checkBlockUDLR(Block *block);
	//ͨ����⵽�ĵ���ķ��������ѭ�����������ÿһ����������������
	void checkArrBlockNew(__Array *arrold);
	//���鱬ը
	void blockBomb(Block *block);
	//���淽��������
	void moveDown();
	void moveDownRun(int x);
	//�ж��Ƿ���Ҫ����
	void moveLeft();
	//�ɼ�
	int score;
	LabelTTF *labelScore;
	//��Ϸ����
	bool GameNext();
	//ʣ����ٷ���
	int blockNum();
};

#endif // __HELLOWORLD_SCENE_H__
