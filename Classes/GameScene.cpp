#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSprite.h"

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
    CCLog( "ccTouchEnded" );
}
