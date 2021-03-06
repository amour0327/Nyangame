#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSprite.h"
#include "CCPlaySE.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild( layer );
    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }

    setTouchEnabled( true );
    setTouchMode( kCCTouchesOneByOne );

    initForVariables();

    showBackground();

    showBlock();

    SimpleAudioEngine::sharedEngine()->preloadEffect( MP3_REMOVE_BLOCK );

    return true;
}

void GameScene::showBackground()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    m_background = CCSprite::create( PNG_BACKGROUND );
    m_background->setPosition( ccp( winSize.width / 2, winSize.height /2 ) );
    addChild( m_background, kZOrderBackground, kTagBackground );
}

void GameScene::initForVariables()
{
    srand( (unsigned)time(NULL) );
    BlockSprite* pBlock = BlockSprite::createWithBlockType( kBlockRed );
    m_blockSize = pBlock->getContentSize().height;

    blockTypes.push_back( kBlockRed );
    blockTypes.push_back( kBlockBlue );
    blockTypes.push_back( kBlockYellow );
    blockTypes.push_back( kBlockGreen );
    blockTypes.push_back( kBlockGray );
}

CCPoint GameScene::getPosition( int posIndexX, int posIndexY )
{
    float offsetX = m_background->getContentSize().width * 0.168;
    float offsetY = m_background->getContentSize().height * 0.029;
    return CCPoint( (posIndexX + 0.5) * m_blockSize + offsetX, (posIndexY + 0.5) * m_blockSize + offsetY );
}

int GameScene::getTag( int posIndexX, int posIndexY )
{
    return kTagBaseBlock + posIndexX * 100 + posIndexY;
}

void GameScene::showBlock()
{
    for( int x= 0; x < MAX_BLOCK_X; x++ ) {
        for( int y = 0; y < MAX_BLOCK_Y; y++ ) {
            kBlock blockType = (kBlock)(rand() % kBlockCount );

            int tag = getTag( x, y );
            m_blockTags[blockType].push_back( tag );

            BlockSprite* pBlock = BlockSprite::createWithBlockType( blockType );
            pBlock->setPosition( getPosition( x, y ) );
            m_background->addChild( pBlock, kZOrderBlock, tag );
        }
    }
}

bool GameScene::ccTouchBegan( CCTouch* pTouch, CCEvent* pEvent )
{
    return true;
}

void GameScene::ccTouchEnded( CCTouch* pTouch, CCEvent* pEvent )
{
    CCPoint touchPoint = m_background->convertTouchToNodeSpace( pTouch );
    int tag = 0;
    kBlock blockType;
    getTouchBlockTag( touchPoint, tag, blockType );

    if ( tag != 0 ) {
        list<int> sameColorBlockTags = getSameColorBlockTags( tag, blockType );
        if ( sameColorBlockTags.size() > 1 ) {
            removeBlock( sameColorBlockTags, blockType );
            movingBlockAnimation1( sameColorBlockTags );
        }
    }
}

void GameScene::getTouchBlockTag( CCPoint touchPoint, int &tag, kBlock &blockType )
{
    for( int x = 0; x < MAX_BLOCK_X; x++ ) {
        for ( int y = 0; y < MAX_BLOCK_Y; y++ ) {
            int currentTag = getTag( x, y );
            CCNode* node = m_background->getChildByTag( currentTag );
            if ( node && node->boundingBox().containsPoint( touchPoint ) ) {
                tag = currentTag;
                blockType = ((BlockSprite*)node)->getBlockType();
                return;
            }
        }
    }
}

bool GameScene::hasSameColorBlock( list<int> blockTagList, int searchBlockTag )
{
    list<int>::iterator it;
    for( it = blockTagList.begin(); it != blockTagList.end(); ++it ) {
        if ( *it == searchBlockTag ) {
            return true;
        }
    }
    return false;
}

list<int> GameScene::getSameColorBlockTags( int baseTag, kBlock blockType )
{
    list<int> sameColorBlockTags;
    sameColorBlockTags.push_back( baseTag );

    list<int>::iterator it = sameColorBlockTags.begin();
    while( it != sameColorBlockTags.end() ) {
        int tags[] = {
            *it + 100,
            *it - 100,
            *it + 1,
            *it - 1,
        };

        for( int i = 0; i < sizeof(tags) / sizeof(tags[0]); i++ ) {
            if ( !hasSameColorBlock( sameColorBlockTags, tags[i] ) ) {
                if ( hasSameColorBlock( m_blockTags[blockType], tags[i] ) ) {
                    sameColorBlockTags.push_back( tags[i] );
                }
            }
        }
        it++;
    }
    return sameColorBlockTags;
}

void GameScene::removeBlock( list<int> blockTags, kBlock blockType )
{
    bool first = true;

    list<int>::iterator it = blockTags.begin();
    while( it != blockTags.end() ) {
        m_blockTags[blockType].remove( *it );
        CCNode* block = m_background->getChildByTag( *it );
        if ( block ) {
            CCScaleTo* scale = CCScaleTo::create( REMOVE_TIME, 0 );
            CCCallFuncN* func = CCCallFuncN::create( this, callfuncN_selector( GameScene::removingBlock ));
            CCFiniteTimeAction* sequence = CCSequence::create( scale, func, NULL );
            CCFiniteTimeAction* action;
            if ( first ) {
                CCPlaySE* playSe = CCPlaySE::create( MP3_REMOVE_BLOCK );
                action = CCSpawn::create( sequence, playSe, NULL );
                first = false;
            } else {
                action = sequence;
            }

            block->runAction( action );
        }
        it++;
    }
    SimpleAudioEngine::sharedEngine()->playEffect( MP3_REMOVE_BLOCK );
}

void GameScene::removingBlock( CCNode* block )
{
    block->removeFromParentAndCleanup( true );
}

GameScene::PositionIndex GameScene::getPositionIndex( int tag )
{
    int pos1_x = (tag - kTagBaseBlock) / 100;
    int pos1_y = (tag - kTagBaseBlock) % 100;

    return PositionIndex( pos1_x, pos1_y );
}

void GameScene::setNewPosition1(int tag, PositionIndex posIndex )
{
    BlockSprite* blockSprite = (BlockSprite*)m_background->getChildByTag( tag );
    int nextPosY = blockSprite->getNextPosY();
    if( nextPosY == -1 ) {
        nextPosY = posIndex.y;
    }

    blockSprite->setNextPos( posIndex.x, --nextPosY );
}

void GameScene::searchNewPosition1( list<int> blocks )
{
    list<int>::iterator it1 = blocks.begin();
    while( it1 != blocks.end() ) {
        PositionIndex posIndex1 = getPositionIndex( *it1 );
        vector<kBlock>::iterator it2 = blockTypes.begin();
        while( it2 != blockTypes.end() ) {
            list<int>::iterator it3 = m_blockTags[*it2].begin();
            while( it3 != m_blockTags[*it2].end() ) {
                PositionIndex posIndex2 = getPositionIndex( *it3 );
                if ( posIndex1.x == posIndex2.x && posIndex1.y == posIndex2.y ) {
                    setNewPosition1( *it3, posIndex2 );
                }
                it3++;
            }
            it2++;
        }
        it1++;
    }
}

void GameScene::moveBlock()
{
    vector<kBlock>::iterator it1 = blockTypes.begin();
    while( it1 != blockTypes.end() ) {
        list<int>::iterator it2 = m_blockTags[*it1].begin();
        while( it2 != m_blockTags[*it1].end() ) {
            BlockSprite* blockSprite = (BlockSprite*)m_background->getChildByTag( *it2 );
            int nextPosX = blockSprite->getNextPosX();
            int nextPosY = blockSprite->getNextPosY();

            if( nextPosX != -1 || nextPosY != -1 ) {
                int newTag = getTag( nextPosX, nextPosY );
                blockSprite->initNextPos();
                blockSprite->setTag( newTag );

                *it2 = newTag;

                CCMoveTo* move = CCMoveTo::create( MOVING_TIME, getPosition( nextPosX, nextPosY ) );
                blockSprite->runAction( move );
            }
            it2++;
        }
        it1++;
    }
}

void GameScene::movingBlockAnimation1( list<int> blocks )
{
    searchNewPosition1( blocks );
    moveBlock();
}
