/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "SplashScreen.h"
#include "LevelOne.h"

USING_NS_CC;

Scene* SplashScreen::createScene()
{
    return SplashScreen::create();
}


bool SplashScreen::init()
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

    auto avatarLogo = Sprite::create("player.jpg");
    avatarLogo->setContentSize(cocos2d::Size(150, 150));
    avatarLogo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 70));
    this->addChild(avatarLogo, 1);

    auto title = Label::createWithTTF("PICO PARK", "fonts/unispace bd.ttf", 42);
    title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
    title->setColor(Color3B(255, 121, 33));
    this->addChild(title, 1);

    auto playButton = MenuItemImage::create("play_button.png", "play_button_pressed.png", CC_CALLBACK_1(SplashScreen::GoToLevelOne, this));
    playButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100));

    auto menu = Menu::create(playButton, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu, 1);

    return true;
}

void SplashScreen::GoToLevelOne(Ref* pSender) {

    auto scene = LevelOne::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
