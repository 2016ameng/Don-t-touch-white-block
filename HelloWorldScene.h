#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Scene
{
private:
    Size visibleSize;    //获取屏幕的大小
    int linesCount;     //记录行数
    bool showEnd;
    Label *timeLabel;     //时间
    Node *gameLayer;      //分层 时间在最上层
    bool timerRunning;
    long startTime;
    
   // Node *
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);   //是定义一个静态的create类成员函数，
    //并在这个函数中调用 virtual bool init();初始化这个场景。
    
    void addStartLine();       //创建开始行
    void addEndLine();         //创建结束行
    void addNormalLine(int LineIndex);      //创建黑白行    从下往上一行一行添加
    void moveDown();
    void startGame();
    void startTimer();
    void stopTimer();
    
    virtual void update(float dt);     //计时
};

#endif // __HELLOWORLD_SCENE_H__
