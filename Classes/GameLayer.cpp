#include "GameLayer.h"
#include "R.h"
#include "Constants.h"
#include "AdmobHelper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

GameLayer::GameLayer()
{
	_leftWall = nullptr;
	_rightWall = nullptr;
	_leftHero = nullptr;
	_rightHero = nullptr;
    _leftHeroSpeed=0;
    _rightHeroSpeed=0;
	_status = start;
	_thornsUsed = nullptr;
	_isNewRecord = false;
	_score = 0;
	_leftHeroSpeed = 0;
	_rightHeroSpeed = 0;
    _leftDt=0;
    _rightDt=0;
	_heroWidth = 0;
	_touchMode = Point::ZERO;
	_thornSpeed = Constants::ORIGIN_SPEED;
}

GameLayer::~GameLayer()
{
	CC_SAFE_RELEASE_NULL(_leftWall);
	CC_SAFE_RELEASE_NULL(_rightWall);
	CC_SAFE_RELEASE_NULL(_thornsUsed);
	CC_SAFE_RELEASE_NULL(_thornPool);
}

bool GameLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		//init land
		_leftWall = Land::create();
		_leftWall->retain();
		Ref* obj = NULL;
		CCARRAY_FOREACH(_leftWall->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			sprite->setTag(Constants::TAG_WALL_LEFT);
			this->addChild(sprite);
		};
		_rightWall = Land::create();
		_rightWall->retain();
		_rightWall->turnRightWall();
		CCARRAY_FOREACH(_rightWall->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			sprite->setTag(Constants::TAG_WALL_RIGHT);
			this->addChild(sprite);
		};
		//init GroundBody
		float wallWidth = _leftWall->getOneLandSize().width;
		Node* groundNode = Node::create();
		PhysicsBody* groundBody = PhysicsBody::createBox(Size(wallWidth,visibleSize.height ));
		PhysicsMaterial groundM = PhysicsMaterial(0, 0, 0);
		groundBody->addShape(PhysicsShapeBox::create(Size(wallWidth, visibleSize.height), groundM, Point(visibleSize.width-wallWidth, 0)));
		groundBody->setDynamic(false);
		groundBody->setLinearDamping(0);
		groundBody->setContactTestBitmask(-1);
		groundNode->setPhysicsBody(groundBody);
		groundNode->setPosition(origin.x + wallWidth/2, origin.y + visibleSize.height / 2);
		groundNode->setTag(Constants::TAG_WALL_LEFT);
		this->addChild(groundNode);
		//init Hero
		_leftHero = LeftHero::creat();
		_leftHero->setTag(Constants::TAG_HERO_LEFT);
		_leftHero->setPosition(origin.x + visibleSize.width / 2-_leftHero->getContentSize().width/2, origin.y + Constants::HERO_POSITION_Y);
		this->addChild(_leftHero);
		_leftHero->idle();
		PhysicsMaterial leftHeroM = PhysicsMaterial(0, 0, 0);
		PhysicsBody* leftHeroBody = PhysicsBody::create();
		leftHeroBody->addShape(PhysicsShapeBox::create(_leftHero->getContentSize(),leftHeroM));
		leftHeroBody->setDynamic(true);
		leftHeroBody->setLinearDamping(0);
		leftHeroBody->setRotationEnable(false);
		leftHeroBody->setContactTestBitmask(-1);
		leftHeroBody->setGravityEnable(false);
		_leftHero->setPhysicsBody(leftHeroBody);

		_rightHero = RightHero::creat();
		_rightHero->setTag(Constants::TAG_HERO_RIGHT);
		_rightHero->setPosition(origin.x + visibleSize.width / 2 + _rightHero->getContentSize().width / 2, origin.y + Constants::HERO_POSITION_Y);
		this->addChild(_rightHero);
		_rightHero->idle();
		PhysicsMaterial rightHeroM = PhysicsMaterial(0, 0, 0);
		PhysicsBody* rightHeroBody = PhysicsBody::create();
		rightHeroBody->addShape(PhysicsShapeBox::create(_rightHero->getContentSize(), rightHeroM));
		rightHeroBody->setDynamic(true);
		rightHeroBody->setLinearDamping(0);
		rightHeroBody->setRotationEnable(false);
		rightHeroBody->setContactTestBitmask(-1);
		rightHeroBody->setGravityEnable(false);
		_rightHero->setPhysicsBody(rightHeroBody);

		_heroWidth = _rightHero->getContentSize().width;
		//init thorns
		//init thorns heights
		float h1 = Sprite::createWithSpriteFrameName(R::thorn1)->getContentSize().height;
		float h2 = Sprite::createWithSpriteFrameName(R::thorn2)->getContentSize().height;
		float h3 = Sprite::createWithSpriteFrameName(R::thorn3)->getContentSize().height;
		float h4 = Sprite::createWithSpriteFrameName(R::thorn4)->getContentSize().height;
		_thornsHeights.push_back(0);	//占位 为了跟Tag常亮对应
		_thornsHeights.push_back(h1);	//TAG_THORN_LEFT_BIG
		_thornsHeights.push_back(h1);	//TAG_THORN_RIGHT_BIG
		_thornsHeights.push_back(h2);	//TAG_THORN_SIDE_SMALL
		_thornsHeights.push_back(h3);	//TAG_THORN_MIDDLE_SMALL
		_thornsHeights.push_back(h4);	//TAG_THORN_MIDDLE_BIG
		_thornsUsed = __Array::createWithCapacity(Constants::THORNS_POOL_MAX);
		_thornPool = __Array::create();
		for (int i = 0; i < Constants::THORNS_POOL_MAX; i++){
			_isNews.push_back(true);
		}
		_thornsUsed->retain();
		_thornPool->retain();
		createThorns();

		this->scheduleUpdate();

		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = [this](PhysicsContact& contact)->bool
		{
			Node* nodeA = contact.getShapeA()->getBody()->getNode();
			Node* nodeB = contact.getShapeB()->getBody()->getNode();
			if (nodeA == nullptr || nodeB == nullptr){
				return true;
			}
			if (nodeA->getTag() == Constants::TAG_HERO_LEFT || nodeA->getTag() == Constants::TAG_HERO_RIGHT){
				return this->collision(nodeA, nodeB);
			}
			if (nodeB->getTag() == Constants::TAG_HERO_LEFT || nodeB->getTag() == Constants::TAG_HERO_RIGHT){
				return this->collision(nodeB, nodeA);
			}
			return true;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

		if (AdmobHelper::isAdShowing)
		{
			AdmobHelper::hideAd();
		}

		SimpleAudioEngine::getInstance()->playBackgroundMusic(R::a_bg_playing,true);
		bRet = true;
	} while (0);
	return bRet;
}

void GameLayer::update(float dt)
{
	_leftWall->scroll(_thornSpeed);
	_rightWall->scroll(_thornSpeed);
	if (_status == start){
		Ref* obj = nullptr;
		//滚动障碍物
		CCARRAY_FOREACH(_thornsUsed, obj){
			Node* pipeNode = (Node*)obj;
			pipeNode->setPositionY(pipeNode->getPositionY() - _thornSpeed);
		}
		//回收超出边界的障碍
		int recyleIndex = -1;
		for (int i = 0; i < _thornsUsed->count(); i++){
			Node* pipeNode = (Node*)(_thornsUsed->getObjectAtIndex(i));
			if (pipeNode->getPositionY() < origin.y-Constants::THORN_RECYLE_DISTANCE ){
				//int last = i - 1 < 0 ? _thornsUsed->count() - 1 : i - 1;
				//Node* lastLand = (Node*)(_thornsUsed->getObjectAtIndex(last));
				//pipeNode->setPosition(lastLand->getPositionX() + THORN_SPACING,getRandomHeight()+origin.y);
				_isNews[i] = true;
				recyleIndex = i;
			}
		}
		if (recyleIndex != -1)
		{
			_thornPool->addObject(_thornsUsed->getObjectAtIndex(recyleIndex));
			_thornsUsed->removeObjectAtIndex(recyleIndex);
		}
		//障碍不够用时从障碍池取出所有障碍随机重排加入使用队列
		Node* last = (Node*)_thornsUsed->getLastObject();
		float lastY = last->getPositionY()+last->getContentSize().height/2;
		if (lastY < origin.y + visibleSize.height + Constants::THORN_RECYLE_DISTANCE)
		{
			int count = _thornPool->count();
			log(__String::createWithFormat("pool_count=%i", count)->getCString());
			for (int i = 0; i < count; i++)
			{
				int index = rand() % _thornPool->count();
				Node* n = (Node*)_thornPool->getObjectAtIndex(index);
				float nHeight = _thornsHeights[n->getTag()];
				lastY += Constants::THORN_SPACING + nHeight/2;
				n->setPositionY(lastY);
				log(__String::createWithFormat("index=%i,type=%i,nHeight=%.0f,lastY=%.0f",index, n->getTag(), nHeight, lastY)->getCString());
				lastY += nHeight / 2;
				_thornsUsed->addObject(n);
				_isNews[_thornsUsed->count() - 1] = true;
				_thornPool->removeObject(n);
			}
		}
		checkHit();
	}
}

void GameLayer::createThorns()
{
	float y = origin.y + visibleSize.height / 2 + Constants::PLAYER_READY_DISTANCE;
	//产生0至Constants::THORNS_POOL_MAX - 1的不重复随机数
	int a[Constants::THORNS_POOL_MAX];
	for (int i = 0; i < Constants::THORNS_POOL_MAX; ++i) a[i] = i;
	for (int i = Constants::THORNS_POOL_MAX - 1; i >= 1; --i) {
		//swap(a[i], a[rand() % i]);
		int temp = a[i];
		int index = rand() % i;
		a[i] = a[index];
		a[index] = temp;
	}
	//生成初始障碍
	for (int i = 0; i < Constants::THORNS_POOL_MAX; i++)
	{
		Node* thornNode = Node::create();
		//根据type生成不同类型障碍
		int type = a[i] % Constants::THORN_TYPE_COUNT + 1;
		thornNode->setTag(type);
		Sprite* thorn1 = nullptr;
		Sprite* thorn2 = nullptr;
		PhysicsBody* body = PhysicsBody::create();
		PhysicsShape* s1 = nullptr;
		PhysicsShape* s2 = nullptr;
		float wallWidth = _leftWall->getOneLandSize().width;
		Point* plb1 = nullptr;
		Point* plb2 = nullptr;
		switch (type)
		{
		case Constants::TAG_THORN_LEFT_BIG:
			thorn1 = Sprite::createWithSpriteFrameName(R::thorn1);
			//y += thorn1->getContentSize().width / 2;
			y += _thornsHeights[type]/2 + Constants::THORN_SPACING;
			thornNode->setPosition(origin.x + wallWidth + thorn1->getContentSize().width / 2, y);
			plb1 = new Point[3]{
					Point(-254.5000, -121.0000),
					Point(-254.5000, -9.0000),
					Point(254.5000, 121.0000)
			};
			s1 = PhysicsShapePolygon::create(plb1, 3, PhysicsMaterial(0, 0, 0));
			break;
		case Constants::TAG_THORN_RIGHT_BIG:
			thorn1 = Sprite::createWithSpriteFrameName(R::thorn1);
			thorn1->setFlippedX(true);
			//y += thorn1->getContentSize().width / 2;
			y += _thornsHeights[type]/2 + Constants::THORN_SPACING;
			thornNode->setPosition(origin.x + visibleSize.width - wallWidth - thorn1->getContentSize().width / 2, y);
			plb1 = new Point[3]{
				Point(254.5000, -9.0000),
					Point(254.5000, -121.0000),
					Point(-254.5000, 121.0000)
			};
			s1 = PhysicsShapePolygon::create(plb1, 3, PhysicsMaterial(0, 0, 0));
			break;
		case Constants::TAG_THORN_SIDE_SMALL:
			thorn1 = Sprite::createWithSpriteFrameName(R::thorn2);
			thorn2 = Sprite::createWithSpriteFrameName(R::thorn2);
			thorn2->setFlippedX(true);
			//计算右边障碍距离
			thorn2->setPositionX(visibleSize.width - wallWidth * 2 - thorn1->getContentSize().width);
			//y += thorn1->getContentSize().width / 2;
			y += _thornsHeights[type]/2 + Constants::THORN_SPACING;
			thornNode->setPosition(origin.x + wallWidth + thorn1->getContentSize().width / 2, y);
			plb1 = new Point[3]{
					Point(-128.0000, -81.0000),
					Point(-128.0000, -6.0000),
					Point(128.0000, 81.0000)
			};
			s1 = PhysicsShapePolygon::create(plb1, 3, PhysicsMaterial(0, 0, 0));
			plb2 = new Point[3]{
					Point(128.0000, -6.0000),
					Point(128.0000, -81.0000),
					Point(-128.0000, 81.0000)
			};
			s2 = PhysicsShapePolygon::create(plb2, 3, PhysicsMaterial(0, 0, 0), Point(visibleSize.width - thorn1->getContentSize().width - _leftWall->getOneLandSize().width * 2, 0));
			break;
		case Constants::TAG_THORN_MIDDLE_SMALL:
			thorn1 = Sprite::createWithSpriteFrameName(R::thorn3);
			//y += thorn1->getContentSize().width / 2;
			y += _thornsHeights[type]/2 + Constants::THORN_SPACING;
			thornNode->setPosition(origin.x + visibleSize.width / 2, y );
			plb1 = new Point[4]{
					Point(0.0000, -73.0000),
					Point(-152.0000, 0.0000),
					Point(0.0000, 74.0000),
					Point(152.0000, 1.0000),
			};
			s1 = PhysicsShapePolygon::create(plb1, 4, PhysicsMaterial(0, 0, 0));
			break;
		case Constants::TAG_THORN_MIDDLE_BIG:
			thorn1 = Sprite::createWithSpriteFrameName(R::thorn4);
			//y += thorn1->getContentSize().width / 2;
			y += _thornsHeights[type]/2 + Constants::THORN_SPACING;
			thornNode->setPosition(origin.x + visibleSize.width / 2, y);
			plb1 = new Point[4]{
					Point(-0.5000, 107.0000),
					Point(218.5000, 1.0000),
					Point(-0.5000, -106.0000),
					Point(-218.5000, 0.0000),
			};
			s1 = PhysicsShapePolygon::create(plb1, 4, PhysicsMaterial(0, 0, 0));
			break;
		default:
			break;
		}
		y += _thornsHeights[type]/2 ;

		CC_SAFE_DELETE(plb1);
		CC_SAFE_DELETE(plb2);
		if (s1 != nullptr) body->addShape(s1);
		if (s2 != nullptr) body->addShape(s2);
		body->setDynamic(false);
		body->setLinearDamping(0);
		body->setContactTestBitmask(-1);
		thornNode->setPhysicsBody(body);
		if (thorn1 != nullptr) thornNode->addChild(thorn1);
		if (thorn2 != nullptr) thornNode->addChild(thorn2);
		this->addChild(thornNode);
		_thornsUsed->addObject(thornNode);
		
		//Sprite* pipeTop = Sprite::createWithSpriteFrameName(R::pipe_green_top);
		//Sprite* pipeBottom = Sprite::createWithSpriteFrameName(R::pipe_green_bottom);
		//pipeTop->setPosition(0, PIPE_SPACING_VERTICAL / 2 + _pipeSize.height / 2);
		//pipeBottom->setPosition(0, -PIPE_SPACING_VERTICAL / 2 - _pipeSize.height / 2);
		//pipeNode->addChild(pipeTop);
		//pipeNode->addChild(pipeBottom);

		//PhysicsBody* pipeBody = PhysicsBody::create();
		//pipeBody->addShape(PhysicsShapeBox::create(_pipeSize, PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIPE_SPACING_VERTICAL / 2 + _pipeSize.height / 2)));
		//pipeBody->addShape(PhysicsShapeBox::create(_pipeSize, PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, -PIPE_SPACING_VERTICAL / 2 - _pipeSize.height / 2)));
		//pipeBody->setDynamic(false);
		//pipeBody->setLinearDamping(0);
		//pipeBody->setContactTestBitmask(-1);
		//pipeBody->setGravityEnable(false);
		//pipeNode->setPhysicsBody(pipeBody);

		//pipeNode->setPosition(x, getRandomHeight()+origin.y);
		////_batchNode->addChild(pipeNode);	//TODO 这里没找到合适的方法添加进batchNode，直接添加会报错
		//this->addChild(pipeNode,-1);
		//x += THORN_SPACING;
		//_pipeNodes->addObject(pipeNode);
	}
	
}

void GameLayer::gameOver()
{
	if (_status==end)
	{
		return;
	}
	_status = end;
	SimpleAudioEngine::getInstance()->playEffect(R::a_thorn);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	this->unscheduleUpdate();
	int bestScore = UserDefault::getInstance()->getIntegerForKey(Constants::PROP_INT_BEST_SCORE);
	if (_score > bestScore){
		UserDefault::getInstance()->setIntegerForKey(Constants::PROP_INT_BEST_SCORE, _score);
		_isNewRecord = true;
	}
	//_bird->die();
	//_bird->setRotation(-90);
	//_bird->stopAllActions();
	////auto fadeOut = FadeOut::create(1.5);
	////_bird->runAction(fadeOut);
	_delegate->onGameEnd(_score,bestScore);
	AdmobHelper::showAd();
}

void GameLayer::checkHit()
{
	for (int i = 0; i < _thornsUsed->count(); i++){
		Node* pipeNode = (Node*)(_thornsUsed->getObjectAtIndex(i));
		if (pipeNode->getPositionY() < _leftHero->getPositionY() && _isNews[i] == true){
			_score++;
			_isNews[i] = false;
			//迭代加速
			if (_score>0 && _score%Constants::THRON_INTERVAL == 0){
				_thornSpeed += Constants::THRON_ACCELERATION;
				_thornSpeed = _thornSpeed > Constants::THRON_SPEED_LIMIT ? Constants::THRON_SPEED_LIMIT : _thornSpeed;
			}
		}
	}
	_delegate->onGamePlaying(_score);
}


void GameLayer::onTouchModeChanged(Point oldMode, Point newMode)
{
	if (_status==end)
	{
		return;
	}
	_touchMode = newMode;
	if (newMode == Point::ZERO)
	{
		//lefthero在左边
		if (_leftHero->getPositionX() < origin.x + visibleSize.width / 2-_heroWidth/2){
			if (_leftHeroSpeed < 0){
				_leftHeroSpeed = Constants::HERO_ORIGIN_SPEED;
				_leftDt = 0;
			}
		}//右边
		else{
			if (_leftHeroSpeed > 0){

				_leftHeroSpeed = -Constants::HERO_ORIGIN_SPEED;
				_leftDt = 0;
			}
		}
		//_rightHero在左边
		if (_rightHero->getPositionX() < origin.x + visibleSize.width / 2+_heroWidth/2){
			if (_rightHeroSpeed < 0){
				_rightHeroSpeed = Constants::HERO_ORIGIN_SPEED;
				_rightDt = 0;
			}
		}//右边
		else{
			if (_rightHeroSpeed>0){
				_rightHeroSpeed = -Constants::HERO_ORIGIN_SPEED ;
				_rightDt = 0;
			}
		}
	}
	else if (newMode == Point(1, 0)){
		if (_leftHeroSpeed >= 0){
			_leftHeroSpeed =  -Constants::HERO_ORIGIN_SPEED;
			_leftDt = 0;
		}
		if (_rightHeroSpeed >= 0)
		{
			_rightHeroSpeed = -Constants::HERO_ORIGIN_SPEED ;
			_rightDt = 0;
		}
	}
	else if (newMode == Point(0, 1)){
		if (_leftHeroSpeed <= 0){
			_leftHeroSpeed = Constants::HERO_ORIGIN_SPEED;
			_leftDt = 0;
		}
		if (_rightHeroSpeed <= 0){
			_rightHeroSpeed = Constants::HERO_ORIGIN_SPEED ;
			_rightDt = 0;
		}
	}
	else if (newMode == Point(1, 1)){
		if (_leftHeroSpeed >= 0){
			_leftHeroSpeed = -Constants::HERO_ORIGIN_SPEED;
			_leftDt = 0;
		}
		if (_rightHeroSpeed <= 0){
			_rightHeroSpeed = Constants::HERO_ORIGIN_SPEED;
			_rightDt = 0;
		}
	}
}

void GameLayer::onHolding(float dt)
{
	if (_status == end){
		return;
	}
	_leftDt += dt;
	_rightDt += dt;
	float leftV0 = _leftHeroSpeed;
	float rightV0 = _rightHeroSpeed;
	_leftHeroSpeed = leftV0 + Constants::HERO_ACCELERATION*_leftDt*(leftV0>0?1:-1);
	_rightHeroSpeed = rightV0 + Constants::HERO_ACCELERATION*_rightDt*(rightV0>0 ? 1 : -1);
	float leftX = (leftV0 + _leftHeroSpeed)*_leftDt / 2 + _leftHero->getPositionX();
	float rightX = (rightV0 + _rightHeroSpeed)*_rightDt / 2 + _rightHero->getPositionX();
	float wallWidth = Land::getOneSize().width;
	_leftHero->setPositionX(leftX);
	_rightHero->setPositionX(rightX);
	if (leftX < origin.x + wallWidth + _heroWidth / 2){
		_leftHeroSpeed = -Constants::HERO_ORIGIN_SPEED;
		_leftHero->setPositionX(origin.x + wallWidth + _heroWidth / 2);
	}
	if (leftX>origin.x + visibleSize.width - wallWidth - _heroWidth / 2 - _heroWidth){
		_leftHeroSpeed = Constants::HERO_ORIGIN_SPEED;
		_leftHero->setPositionX(origin.x + visibleSize.width - wallWidth - _heroWidth / 2 - _heroWidth);
	}
	if (rightX>origin.x + visibleSize.width - wallWidth - _heroWidth / 2){
		_rightHeroSpeed = Constants::HERO_ORIGIN_SPEED;
		_rightHero->setPositionX(origin.x + visibleSize.width - wallWidth - _heroWidth / 2);
	}
	if (rightX < origin.x + wallWidth + _heroWidth / 2 + _heroWidth){
		_rightHeroSpeed = -Constants::HERO_ORIGIN_SPEED;
		_rightHero->setPositionX(origin.x + wallWidth + _heroWidth / 2 + _heroWidth);
	}
	if (_touchMode == Point::ZERO)
	{
		//lefthero在左边切速度向左或leftHero在右边且速度向右
		if ((leftX < origin.x + visibleSize.width / 2 - _heroWidth / 2 && _leftHeroSpeed<=0) 
			|| (leftX >= origin.x + visibleSize.width / 2 - _heroWidth / 2 && _leftHeroSpeed >= 0)){
			_leftHeroSpeed = 0;
			_leftHero->setPositionX(origin.x + visibleSize.width / 2 - _heroWidth / 2);
		}
		//_rightHero在左边切速度向左或_rightHero在右边且速度向右
		if ((rightX < origin.x + visibleSize.width / 2 + _heroWidth / 2 && _rightHeroSpeed<=0)
			|| (rightX >= origin.x + visibleSize.width / 2 + _heroWidth / 2 && _rightHeroSpeed >= 0)){
			_rightHeroSpeed = 0;
			_rightHero->setPositionX(origin.x + visibleSize.width / 2 + _heroWidth / 2);
		}
	}
	
}

bool GameLayer::collision(Node* hero, Node* thorn)
{
	if (hero->getTag() == Constants::TAG_HERO_LEFT){
		switch (thorn->getTag())
		{
		case Constants::TAG_HERO_RIGHT:
			return true;
		case Constants::TAG_THORN_LEFT_BIG:
			gameOver();
			break;
		case Constants::TAG_THORN_RIGHT_BIG:
			gameOver();
			break;
		case Constants::TAG_THORN_SIDE_SMALL:
			gameOver();
			break;
		case Constants::TAG_THORN_MIDDLE_SMALL:
			gameOver();
			break;
		case Constants::TAG_THORN_MIDDLE_BIG:
			gameOver();
			break;
		case Constants::TAG_WALL_LEFT:
		case Constants::TAG_WALL_RIGHT:
			SimpleAudioEngine::getInstance()->playEffect(R::a_wall);
			return true;
		default:
			return true;
		}
	}
	if (hero->getTag() == Constants::TAG_HERO_RIGHT){
		switch (thorn->getTag())
		{
		case Constants::TAG_HERO_LEFT:
			return true;
		case Constants::TAG_THORN_LEFT_BIG:
			gameOver();
			break;
		case Constants::TAG_THORN_RIGHT_BIG:
			gameOver();
			break;
		case Constants::TAG_THORN_SIDE_SMALL:
			gameOver();
			break;
		case Constants::TAG_THORN_MIDDLE_SMALL:
			gameOver();
			break;
		case Constants::TAG_THORN_MIDDLE_BIG:
			gameOver();
			break;
		case Constants::TAG_WALL_LEFT:
		case Constants::TAG_WALL_RIGHT:
			SimpleAudioEngine::getInstance()->playEffect(R::a_wall);
			return true;
		default:
			return true;
		}
	}
}
