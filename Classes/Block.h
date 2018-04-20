#include "cocos2d.h"
USING_NS_CC;

class Block :public Sprite {
public:
	//初始化游戏数据，宽度，高度，X轴，Y轴
	static Block *createBlock(int numbers, int wight, int height, float BlockX, float BlockY);
	virtual bool init();
	CREATE_FUNC(Block);

	//获取数字
	int getNumber();
	//设置数字
	void setNumber(int num);
	//获取色块坐标
	Point getColorBGPoint();
	//获取BLock的位置
	int PopX, PopY;
	//获取X，Y
	int getBlockX();
	int getBlockY();
	//设置X，Y
	void setBlockX(int x);
	void setBlockY(int y);
	//获取颜色
	Color4B getColor(int num);

private:
	//显示的颜色
	int number;
	void enemyInit(int numbers, int wight, int height, float BlockX, float BlockY);
	//显示的背景
	LayerColor *layerColorBG;
};