
#ifndef __LEVELTWO_SCENE_H__
#define __LEVELTWO_SCENE_H__

#include "cocos2d.h"

class LevelTwo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    bool keyObtained = false;

    void SetKeyObtained() { keyObtained = true; };
    bool GetKeyObtained() { return keyObtained; };

    
    void GoBackToMenu(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelTwo);

private:
    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
    bool onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::Sprite* sprite);
};

#endif // __SPLASHSCREEN_SCENE_H__
