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
	//游戏背景
	void background();

	//自动创建游戏中的10*10矩形方阵
	void autoCreateBlock(Size size);

	//监听点击
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	//显示成绩
	void showScore();

	//获得成绩
	int getScore();

	//设置成绩
	void setScore(int score);
private:
	//定义方阵数组，用来存放方阵
	Block *blockSprite[10][10];
	//点击得到方块对象
	Block *getBlockSprite(Size size, Point touch);
	//定义数组存放点击的方块
	__Array *blockClickArr;
	//传递点击的对象，获取他上下左右的数据
	__Array *checkBlockUDLR(Block *block);
	//通过检测到的点击的方块的数组循环检测数组里每一个的上下左右数据
	void checkArrBlockNew(__Array *arrold);
	//方块爆炸
	void blockBomb(Block *block);
	//上面方块往下移
	void moveDown();
	void moveDownRun(int x);
	//判断是否需要左移
	void moveLeft();
	//成绩
	int score;
	LabelTTF *labelScore;
	//游戏结束
	bool GameNext();
	//剩余多少方块
	int blockNum();
};

#endif // __HELLOWORLD_SCENE_H__
