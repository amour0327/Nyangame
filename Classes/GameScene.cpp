#include "GameScene.h"
#include "SimpleAudioEngine.h"

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

    showBackground();

    return true;
}

void GameScene::showBackground()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    m_background = CCSprite::create( PNG_BACKGROUND );
    m_background->setPosition( ccp( winSize.width / 2, winSize.height /2 ) );
    addChild( m_background, kZOrderBackground, kTagBackground );
}

