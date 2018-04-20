#include "Block.h"
USING_NS_CC;

Block *Block::createBlock(int numbers, int wight, int height, float BlockX, float BlockY) {
	Block *enemy = new Block();
	if (enemy && enemy->init()) {
		enemy->autorelease();
		enemy->enemyInit(numbers, wight, height, BlockX, BlockY);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Block::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void Block::enemyInit(int numbers, int wight, int height, float BlockX, float BlockY) {
	//设置初始化的值
	number = numbers;
	PopX = 0;
	PopY = 0;

	//加入游戏每个方块的颜色
	layerColorBG = LayerColor::create(Color4B(200, 190, 180, 150), wight - 4, height - 4);
	layerColorBG->setPosition(Point(BlockX, BlockY));

	this->addChild(layerColorBG);
}

//获取方块的坐标
Point Block::getColorBGPoint() {
	return layerColorBG->getPosition();
}

//获取数字
int Block::getNumber() {
	return number;
}

//设置数字,使用数字来代表方块的颜色
void Block::setNumber(int num) {
	number = num;
	//判断数字来调整方块的颜色
	if (number == -1) {
		layerColorBG->setColor(Color3B(0, 0, 0));
	}
	if (number == 0) {
		layerColorBG->setColor(Color3B(250, 230, 40));
	}
	if (number == 1) {
		layerColorBG->setColor(Color3B(40, 180, 250));
	}
	if (number == 2) {
		layerColorBG->setColor(Color3B(130, 220, 110));
	}
	if (number == 3) {
		layerColorBG->setColor(Color3B(250, 80, 130));
	}
	if (number == 4) {
		layerColorBG->setColor(Color3B(180, 30, 250));
	}
}

Color4B Block::getColor(int num) {
	Color4B color;
	//判断数字来获取方块的颜色
	switch (num) {
	case -1:
		color = Color4B(0, 0, 0, 0);
		break;
	case 0:
		color = Color4B(250, 230, 40, 255);
		break;
	case 1:
		color = Color4B(40, 180, 250, 255);
		break;
	case 2:
		color = Color4B(130, 220, 110, 255);
		break;
	case 3:
		color = Color4B(250, 80, 130, 255);
		break;
	case 4:
		color = Color4B(180, 30, 250, 255);
		break;
	}
	return color;
}

//获取X,Y
int Block::getBlockX() {
	return PopX;
}
int Block::getBlockY() {
	return PopY;
}

//设置X，Y
void Block::setBlockX(int x) {
	PopX = x;
}
void Block::setBlockY(int y) {
	PopY = y;
}