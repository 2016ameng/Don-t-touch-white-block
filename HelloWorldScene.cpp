#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()

{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
    
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    srand(time(NULL));
    
    visibleSize = Director::getInstance()->getVisibleSize();  //获取屏幕大小
    
    //addStartLine();    //创建开始行
    //addEndLine();
    gameLayer = Node::create();
    addChild(gameLayer);
    
    timeLabel = Label::create();
    timeLabel->setTextColor(Color4B::BLUE);
    timeLabel->setSystemFontSize(35);
    timeLabel->setPosition(visibleSize.width/2,visibleSize.height-15);
    timeLabel->setString("0.000000");
    addChild(timeLabel);
    
    startGame();
    //事件侦听器  侦听应用程序的 TouchBegan
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *t,Event *e){
        log("onTouch");      //this 截取变量
        
        //对所有的块进行访问
        auto bs=Block::getBlocks();
        Block *b;
        for(auto it = bs->begin();it!=bs->end();it++){
            
            b = *it;
            //在第一行 并且 和触摸点相碰撞
            if(b->getLineIndex()==1&&
               b->getBoundingBox().containsPoint(t->getLocation())){
                
                if(b->getColor()==Color3B::BLACK){
                    if(!timerRunning){
                        this->startTimer();
                    }
                    
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                    
                }else if(b->getColor()==Color3B::GREEN){
                    this->moveDown();
                    
                    this->stopTimer();
                }else{
                    MessageBox("GameOver","失败");
                    b->getBoundingBox().containsPoint(t->getLocation());
                    HelloWorld::init();
                    //exit(0);
                    //HelloWorld::startGame();
                }
                break;
            }
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    return true;
}

void HelloWorld::startGame(){
    linesCount = 0;
    showEnd=false;
    timerRunning = false;
    
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
  //  addEndLine(4);
}
//创建开始行
void HelloWorld::addStartLine(){
    //添加一个块  块的颜色 块的大小  没有字符串 字符大小 文本颜色
    auto b = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width,visibleSize.height/4),"" , 20, Color4B::BLACK);
    gameLayer->addChild(b);          //添加到容器
    b->setLineIndex(0);
    
}
void HelloWorld::addEndLine(){
    //添加一个块  块的颜色 块的大小  没有字符串 字符大小 文本颜色
    auto b = Block::createWithArgs(Color3B::GREEN, visibleSize,"GAME OVER" , 32, Color4B::BLACK);
    gameLayer->addChild(b);
    b->setLineIndex(4);
}
//黑白行
void HelloWorld::addNormalLine(int LineIndex){
    Block *b;
    int blackIndex = rand()%4;
    for(int i=0;i<4;i++){
        b = Block::createWithArgs(blackIndex==i?Color3B::BLACK:Color3B::WHITE, Size(visibleSize.width/4-1,visibleSize.height/4-1),"",20,Color4B::BLUE);
        gameLayer->addChild(b);
        
        b->setPosition(i*visibleSize.width/4,LineIndex*visibleSize.height/4);
        b->setLineIndex(LineIndex);
    }
    
    linesCount++;
}
void HelloWorld::moveDown(){
    // 输出五十行
    if(linesCount<50){
        addNormalLine(4);
    }else if(!showEnd){
        addEndLine();
        showEnd = true;
    }
   // addNormalLine(4);
    
    auto bs = Block::getBlocks();
    
    for(auto it = bs->begin();it!=bs->end();it++){
        (*it)->moveDown();
    }
    
}
void HelloWorld::update(float dt){
    long offset = clock()-startTime;
    
    timeLabel->setString(StringUtils::format("%g",(double)offset/1000000));
}
void HelloWorld::startTimer(){
    if(!timerRunning){
        scheduleUpdate();
        startTime = clock();
        timerRunning = true;
    }
}
void HelloWorld::stopTimer(){
    if(timerRunning){
        unscheduleUpdate();
        timerRunning = false;
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    
    return;
#endif

    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    exit(0);
    
#endif
    
}
