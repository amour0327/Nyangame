#ifndef __BLOCKSPRITE__H__
#define __BLOCKSPRITE__H__

#include "cocos2d.h"
#include "Config.h"

class BlockSprite : public cocos2d::CCSprite
{
    protected:
        const char* getBlockImageFileName( kBlock blockType );

    public:
        CC_SYNTHESIZE_READONLY( kBlock, m_blockType, BlockType );

        BlockSprite();
        virtual ~BlockSprite();
        virtual bool initWithBlockType( kBlock blockType );
        static BlockSprite* createWithBlockType( kBlock blockType );
};

#endif // __BLOCKSPRITE__H__
