#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 8
#define PNG_BACKGROUND "background.png"

class GameScene : public cocos2d::CCLayer
{
    protected:
        enum kTag
        {
            kTagBackground = 1,
            kTagBaseBlock = 10000,
        };

        enum kZOrder
        {
            kZOrderBackground,
            kZOrderBlock,
        };

        cocos2d::CCSprite* m_background;
        void showBackground();

        float m_blockSize;
        std::map<kBlock, std::list<int> > m_blockTags;
        void initForVariables();
        void showBlock();
        cocos2d::CCPoint getPosition( int posIndexX, int posIndexY );
        int getTag( int posIndexX, int posIndexY );

    public:
        virtual bool init();
        static cocos2d::CCScene* scene();
        CREATE_FUNC( GameScene );

};

#endif // __GAMESCENE_H__
