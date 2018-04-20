#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ӱ���
	background();
	//��ʾ�ɼ�
	showScore();
	//����10*10����
	autoCreateBlock(visibleSize);
	//���ü���
	auto touchLinstener = EventListenerTouchOneByOne::create();
	touchLinstener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchLinstener, this);


    return true;
}

void HelloWorld::background() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = CCParticleSystemQuad::create("particle_bg.plist");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg);
}

void HelloWorld::autoCreateBlock(Size size) {
	//�����������
	srand(((unsigned)time(NULL)));
	//���ÿ��Block�Ŀ�Ⱥ͸߶�
	int lon = (size.width - 28) / 10;

	//10*10�ĵ�Ԫ��
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			int maxX = 5;
			int minX = 0;

			int rangeX = maxX - minX;
			//��ȡһ�������
			int actua1X = (rand() % rangeX) + minX;

			Block *block = Block::createBlock(-1, lon, lon, lon*j + 20, lon*i + 20 + size.height / 6);
			block->setBlockX(j);
			block->setBlockY(i);
			block->setNumber(actua1X);
			addChild(block);

			//���뵽������
			blockSprite[j][i] = block;
		}
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
	//��ʼ���������
	blockClickArr = __Array::create();
	//��ȡ������Xֵ��Yֵ
	Point touchPO = touch->getLocation();

	//��ȡ��Ļ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Block *block = getBlockSprite(visibleSize, touchPO);

	if (block != NULL && block->getNumber() != -1) {
		//������
		blockClickArr = checkBlockUDLR(block);
		if (blockClickArr->count() >= 2) {
			//ѭ�����������
			checkArrBlockNew(blockClickArr);
		}else {
			return true;
		}
	}
	//log("%i,%i", block->getBlockX(), block->getBlockY());
	return true;
}

Block *HelloWorld::getBlockSprite(Size size,Point touch) {
	//���ÿ��Block�Ŀ�Ⱥ͸߶�
	int lon = (size.width - 28) / 10;

	//��������Xλ��
	float x = (touch.x - 28) / lon;
	//��������Yλ��
	float y = (touch.y - (size.height / 6 + 20)) / lon;

	if (x < 10 && y < 10 && x >= 0 && y >= 0) {
		int x1 = (touch.x - 28) / lon;
		int y1 = (touch.y - (size.height / 6 + 20)) / lon;
		return blockSprite[x1][y1];
	}
	else {
		return NULL;
	}
}

__Array *HelloWorld::checkBlockUDLR(Block *block) {
	__Array *arr = __Array::create();
	bool isDoubleBlock = false;

	//�жϵ��λ�����ϵ���ͬ������
	int up = block->getBlockY();
	for (int yu = up + 1; yu < 10; yu++) {
		if (blockSprite[block->getBlockX()][yu]->getNumber() == blockSprite[block->getBlockX()][up]->getNumber()) {
			arr->addObject(blockSprite[block->getBlockX()][yu]);
			//blockSprite[block->getBlockX()][yu]->setNumber(-1);
			isDoubleBlock = true;
		}else {
			break;
		}
	}

	//�жϵ��λ�����µ���ͬ������
	int down = block->getBlockY();
	for (int yd = down - 1; yd >= 0; yd--) {
		if (blockSprite[block->getBlockX()][yd]->getNumber() == blockSprite[block->getBlockX()][down]->getNumber()) {
			arr->addObject(blockSprite[block->getBlockX()][yd]);
			//blockSprite[block->getBlockX()][yd]->setNumber(-1);
			isDoubleBlock = true;
		}
		else {
			break;
		}
	}

	//�жϵ��λ���������ͬ������
	int left = block->getBlockX();
	for (int xl = left - 1; xl >= 0; xl--) {
		if (blockSprite[xl][block->getBlockY()]->getNumber() == blockSprite[left][block->getBlockY()]->getNumber()) {
			arr->addObject(blockSprite[xl][block->getBlockY()]);
			//blockSprite[xl][block->getBlockY()]->setNumber(-1);
			isDoubleBlock = true;
		}
		else {
			break;
		}
	}

	//�жϵ��λ�����ҵ���ͬ������
	int right = block->getBlockX();
	for (int xr = right + 1; xr < 10; xr++) {
		if (blockSprite[xr][block->getBlockY()]->getNumber() == blockSprite[right][block->getBlockY()]->getNumber()) {
			arr->addObject(blockSprite[xr][block->getBlockY()]);
			//blockSprite[xr][block->getBlockY()]->setNumber(-1);
			isDoubleBlock = true;
		}
		else {
			break;
		}
	}

	if (isDoubleBlock) {
		arr->addObject(blockSprite[block->getBlockX()][block->getBlockY()]);
		//blockSprite[block->getBlockX()][block->getBlockY()]->setNumber(-1);
	}

	return arr;
}

//���������飬ѭ������
void HelloWorld::checkArrBlockNew(__Array *arrold) {
	//��ȡ���µ�����
	__Array *arrnew = __Array::create();
	for (int i = 0; i < arrold->count(); i++) {
		//��������Ԫ��һ��һ���ó���
		Block *block = (Block *)arrold->getObjectAtIndex(i);
		__Array *arrnews = checkBlockUDLR(block);
		for (int j = 0; j < arrnews->count(); j++) {
			bool isSave = false;
			Block *blocknews = (Block *)arrnews->getObjectAtIndex(j);
			for (int k = 0; k < blockClickArr->count(); k++) {
				Block *blockold = (Block *)blockClickArr->getObjectAtIndex(k);
				if ((blocknews->getBlockY() == blockold->getBlockY()) && (blocknews->getBlockX() == blockold->getBlockX())) {
					isSave = true;
					break;
				}
			}
			if (!isSave) {
				arrnew->addObject(blocknews);
			}
		}
	}
	if (arrnew->count() > 0) {
		for (int f = 0; f < arrnew->count(); f++) {
			blockClickArr->addObject(arrnew->getObjectAtIndex(f));
		}
		checkArrBlockNew(arrnew);
	}else {
		//�������
		for (int s = 0; s < blockClickArr->count(); s++) {
			Block *sp = (Block *)blockClickArr->getObjectAtIndex(s);
			blockBomb(sp);
			sp->setNumber(-1);
		}
		//����ķ���������
		moveDown();

		score += blockClickArr->count() * 100;
		labelScore->setString(__String::createWithFormat("%i", score)->getCString());
	}
}

//���鱬ը
void HelloWorld::blockBomb(Block *block) {
	auto bomb = CCParticleSystemQuad::create("particle_bomb.plist");
	int x = block->getBlockX();
	int y = block->getBlockY();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int lon = (visibleSize.width - 28) / 10;
	bomb->setPosition(lon*x + lon / 2 + 14, lon*y + lon / 2 + 14 + visibleSize.height / 6);
	bomb->setStartColor(ccc4FFromccc4B(block->getColor(block->getNumber())));
	this->addChild(bomb);
}

//��������
void HelloWorld::moveDown() {
	for (int x = 0; x < 10; x++) {
		moveDownRun(x);
	}

	//�ж��Ƿ���Ҫ����
	for (int i = 0; i < 9; i++) {
		moveLeft();
	}

	GameNext();
}

void HelloWorld::moveDownRun(int x) {
	//���ÿ�еĿո���
	int num = 0;
	for (int k = 0; k < 10; k++) {
		if (blockSprite[x][k]->getNumber() == -1) {
			num++;
		}
	}

	if (num > 0) {
		for (int y = 0; y < 10; y++) {
			//�ж��Ƿ�Ϊ�ո�
			if (blockSprite[x][y]->getNumber() == -1) {
				if (10 - blockSprite[x][y]->getBlockY() > num) {
					for (int s = y; s < 10; s++) {
						if (s + 1 == 10) {
							blockSprite[x][s]->setNumber(-1);
						}else {
							blockSprite[x][s]->setNumber(blockSprite[x][s + 1]->getNumber());
						}
					}
					moveDownRun(x);
				}else {
					break;
				}
			}
		}
	}
}

void HelloWorld::moveLeft() {
	for (int x = 0; x < 10; x++) {
		//���ÿ�еĿո���
		int num = 0;
		for (int k = 0; k < 10; k++) {
			if (blockSprite[x][k]->getNumber() == -1) {
				num++;
			}
		}
		if (num == 10) {
			for (int z = 0; z < 10; z++) {
				for (int s = x; s < 9; s++) {
					blockSprite[s][z]->setNumber(blockSprite[s + 1][z]->getNumber());
					blockSprite[s + 1][z]->setNumber(-1);
				}
			}
		}
	}
}

void HelloWorld::showScore() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto drawRect = DrawNode::create();
	drawRect->drawRect(Vec2(14, visibleSize.height / 6 * 5), Vec2(visibleSize.width - 14, visibleSize.height - 14), Color4F(1, 1, 1, 1));

	labelScore = LabelTTF::create("0", "", 50);
	labelScore->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6 * 5 + visibleSize.height / 6 / 2));
	this->addChild(labelScore);
	this->addChild(drawRect);
}

int HelloWorld::getScore() {
	return score;
}

void HelloWorld::setScore(int score) {
	this->score = score;
}

bool HelloWorld::GameNext() {
	bool isGameOver = true;
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (checkBlockUDLR(blockSprite[j][i])->count() > 0 && blockSprite[j][i]->getNumber() != -1) {
				isGameOver = false;
				break;
			}
		}
		if (isGameOver == false) {
			break;
		}
	}
	if (isGameOver) {
		//���ʣ�෽�����10����GameOver,������һ��
		if (blockNum() > 10) {
			for (int j = 0; j < 10; j++) {
				for (int i = 0; i < 10; i++) {
					if (blockSprite[j][i]->getNumber() != -1) {
						blockBomb(blockSprite[j][i]);
						blockSprite[j][i]->setNumber(-1);
					}
				}
			}
			Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
		}else {
			for (int j = 0; j < 10; j++) {
				for (int i = 0; i < 10; i++) {
					if (blockSprite[j][i]->getNumber() != -1) {
						blockBomb(blockSprite[j][i]);
						blockSprite[j][i]->setNumber(-1);
					}
				}
			}
			auto visibleSize = Director::getInstance()->getVisibleSize();
			autoCreateBlock(visibleSize);
		}
	}
	return isGameOver;
}

int HelloWorld::blockNum() {
	int num = 0;
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (blockSprite[j][i]->getNumber() != -1) {
				num++;
			}
		}
	}
	return num;
}