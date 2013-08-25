#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

class GameScene : public cococs2d::CCLayer
{
    public:
        virtual bool init();
        static cocos2d::CCScene* scene();
        CREATE_FUNC( GameScene );

};

#endif // __GAMESCENE_H__#endif // __GAMESCENE_H__
