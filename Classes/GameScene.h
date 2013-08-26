#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 8
#define REMOVE_TIME 0.1f
#define PNG_BACKGROUND "background.png"
#define MP3_REMOVE_BLOCK "removeBlock.mp3"

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

        void getTouchBlockTag( cocos2d::CCPoint touchPoint, int &tag, kBlock &blockType );
        std::list<int> getSameColorBlockTags( int baseTag, kBlock blockType );
        void removeBlock( std::list<int> blockTags, kBlock blockType );
        bool hasSameColorBlock( std::list<int> blockTagList, int searchBlockTag );

        void removingBlock( cocos2d::CCNode* block );

    public:
        virtual bool init();
        static cocos2d::CCScene* scene();
        CREATE_FUNC( GameScene );

        virtual bool ccTouchBegan( cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent );
        virtual void ccTouchEnded( cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent );

};

#endif // __GAMESCENE_H__
