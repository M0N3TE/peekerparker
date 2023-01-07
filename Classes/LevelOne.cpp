#include "LevelOne.h"
#include "LevelTwo.h"
#include "SplashScreen.h"

USING_NS_CC;
Scene* LevelOne::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    auto layer = LevelOne::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);

    return scene;
}

MoveBy* move(float x, float y) {
    return MoveBy::create(0.3, Vec2(x, 0));
}

bool LevelOne::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = DrawNode::create();
    background->drawSolidRect(origin, visibleSize, Color4F(1, 1, 1, 1));
    this->addChild(background, 0);

    auto level = Label::createWithTTF("LEVEL 1", "fonts/unispace bd.ttf", 24);
    level->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 52));
    level->setColor(Color3B(255, 121, 33));
    this->addChild(level, 1);

    auto menuButton = MenuItemImage::create("menu_button.png", "menu_button_pressed.png", CC_CALLBACK_1(LevelOne::GoBackToMenu, this));
    menuButton->setPosition(Vec2(visibleSize.width - 90, visibleSize.height - 50));
    auto menu = Menu::create(menuButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 30);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    auto ground = DrawNode::create();
    ground->drawSolidRect(origin, Size(visibleSize.width, 30), Color4F(1, 0.4745, 0.1294, 1));
    ground->setPosition(Point(0, 0));
    this->addChild(ground, 1);

    auto beginWall = DrawNode::create();
    beginWall->drawSolidRect(origin, Size(30, visibleSize.height), Color4F(1, 0.4745, 0.1294, 1));
    beginWall->setPosition(Vec2(0, 0));
    this->addChild(beginWall, 1);

    auto endWall = DrawNode::create();
    endWall->drawSolidRect(origin, Size(30, visibleSize.height), Color4F(1, 0.4745, 0.1294, 1));
    endWall->setPosition(Vec2(visibleSize.width - 30, 0));
    this->addChild(endWall, 1);

    auto door = Sprite::create("door.png");
    door->setPosition(Vec2(visibleSize.width - 80, 78));

    auto doorBody = PhysicsBody::createBox(door->getContentSize(), PhysicsMaterial(1, 0, 1));
    doorBody->setDynamic(false);
    doorBody->setCollisionBitmask(3);
    doorBody->setContactTestBitmask(true);
    door->setPhysicsBody(doorBody);

    this->addChild(door, 1);

    auto key = Sprite::create("key.png");
    key->setContentSize(cocos2d::Size(60, 60));
    key->setPosition(Vec2(visibleSize.width - 400, 180));

    auto keyBody = PhysicsBody::createBox(key->getContentSize(), PhysicsMaterial(0, 0, 1));
    keyBody->setDynamic(false);
    keyBody->setCollisionBitmask(2);
    keyBody->setContactTestBitmask(true);
    key->setPhysicsBody(keyBody);

    this->addChild(key, 1);

    float playerX = 60;
    float playerY = 60;

    auto player = Sprite::create("player.png");
    player->setContentSize(cocos2d::Size(60, 60));
    player->setPosition(Point(playerX, playerY));

    auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(1, 0, 1));
    playerBody->setCollisionBitmask(1);
    playerBody->setContactTestBitmask(true);
    player->setPhysicsBody(playerBody);

    this->addChild(player, 3);


    auto keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [playerX, playerY, player, visibleSize](EventKeyboard::KeyCode keyCode, Event* event) mutable
    {
        auto jump = JumpBy::create(0.6, Point(0, 0), 80, 1);

        float currentPositionY = player->getPositionY();

        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                player->runAction(jump);
                break;

            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

                player->runAction(move(-50, 0));
                break;

            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

                player->runAction(move(50, 0));
                break;
        }

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelOne::onContactBegin, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

bool LevelOne::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();


    if (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) {
        this->SetKeyObtained();
        b->getNode()->removeFromParent();
    }

    if (1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) {
        
        if (this->GetKeyObtained()) Director::getInstance()->replaceScene(TransitionFade::create(2, LevelTwo::createScene()));
    }

    return true;
}

void LevelOne::GoBackToMenu(Ref* pSender) {

    auto scene = SplashScreen::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}


