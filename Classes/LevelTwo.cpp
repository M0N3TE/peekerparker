#include "LevelTwo.h"
#include "SplashScreen.h"

USING_NS_CC;
Scene* LevelTwo::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    auto layer = LevelTwo::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);

    return scene;
}

MoveBy* moveplayer(float x, float y) {
    return MoveBy::create(0.3, Vec2(x, 0));
}

bool LevelTwo::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    /* Screen size */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* Background */
    auto background = DrawNode::create();
    background->drawSolidRect(origin, visibleSize, Color4F(1, 1, 1, 1));
    this->addChild(background, 0);

    /* Level label */
    auto level = Label::createWithTTF("LEVEL 2", "fonts/unispace bd.ttf", 24);
    level->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 52));
    level->setColor(Color3B(255, 121, 33));
    this->addChild(level, 1);

    /* Go back to menu button */
    auto menuButton = MenuItemImage::create("menu_button.png", "menu_button_pressed.png", CC_CALLBACK_1(LevelTwo::GoBackToMenu, this));
    menuButton->setPosition(Vec2(visibleSize.width - 90, visibleSize.height - 50));
    auto menu = Menu::create(menuButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /* Physics body */
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 30);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    /* Scene borders and ground */
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

    /* obstacle */
    auto obstacle = Sprite::create("obstacle.png");
    obstacle->setContentSize(cocos2d::Size(50, 520));
    obstacle->setPosition(Point(200, 290));
    auto obstacleBody = PhysicsBody::createBox(obstacle->getContentSize(), PhysicsMaterial(1, 0, 1));
    obstacleBody->setDynamic(false);
    obstacle->setPhysicsBody(obstacleBody);
    this->addChild(obstacle, 2);

    /* obstacle horizontal*/
    auto obstacle2 = Sprite::create("obstacle-hor.png");
    obstacle2->setContentSize(cocos2d::Size(300, 30));
    obstacle2->setPosition(Vec2(373, 320));
    auto obstacleBody2 = PhysicsBody::createBox(obstacle2->getContentSize(), PhysicsMaterial(1, 0, 1));
    obstacleBody2->setDynamic(false);
    obstacle2->setPhysicsBody(obstacleBody2);
    this->addChild(obstacle2, 1);

    /* Button */
    auto button = Sprite::create("button.png");
    button->setContentSize(cocos2d::Size(50, 30));
    button->setPosition(Vec2(400, 290));

    auto buttonBody = PhysicsBody::createBox(button->getContentSize(), PhysicsMaterial(1, 0, 1));
    buttonBody->setDynamic(false);
    buttonBody->setCollisionBitmask(4);
    buttonBody->setContactTestBitmask(true);
    button->setPhysicsBody(buttonBody);

    this->addChild(button, 1);


    /* Door */
    auto door = Sprite::create("door.png");
    door->setPosition(Vec2(visibleSize.width - 80, 78));

    auto doorBody = PhysicsBody::createBox(door->getContentSize(), PhysicsMaterial(1, 0, 1));
    doorBody->setDynamic(false);
    doorBody->setCollisionBitmask(3);
    doorBody->setContactTestBitmask(true);
    door->setPhysicsBody(doorBody);

    this->addChild(door, 1);


    /* Key */
    auto key = Sprite::create("key.png");
    key->setContentSize(cocos2d::Size(60, 60));
    key->setPosition(Vec2(100, 200));

    auto keyBody = PhysicsBody::createBox(key->getContentSize(), PhysicsMaterial(0, 0, 1));
    keyBody->setDynamic(false);
    keyBody->setCollisionBitmask(2);
    keyBody->setContactTestBitmask(true);
    key->setPhysicsBody(keyBody);

    this->addChild(key, 1);

    /* Player */
    float playerX = 300;
    float playerY = 60;

    auto player = Sprite::create("player.png");
    player->setContentSize(cocos2d::Size(60, 60));
    player->setPosition(Point(playerX, playerY));

    auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(1, 0, 1));
    playerBody->setCollisionBitmask(1);
    playerBody->setContactTestBitmask(true);
    player->setPhysicsBody(playerBody);

    this->addChild(player, 3);


    /* Keyboard event listener */
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

                player->runAction(moveplayer(-50, 0));
                break;

            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

                player->runAction(moveplayer(50, 0));
                break;
        }

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelTwo::onContactBegin, this, obstacle);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

int count = 0;

bool LevelTwo::onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::Sprite* obstacleToMove) {
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();


    if (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) {
        this->SetKeyObtained();
        b->getNode()->removeFromParent();
    }

    if (1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) {
        count++;
        if (count < 4) obstacleToMove->setPositionY(obstacleToMove->getPositionY() + 50);
    }

    if (1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) {
        
        if (this->GetKeyObtained()) Director::getInstance()->replaceScene(TransitionFade::create(2, SplashScreen::createScene()));
    }

    return true;
}

void LevelTwo::GoBackToMenu(Ref* pSender) {

    auto scene = SplashScreen::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}


