//
//  C++ class.cpp
//  first_cocos
//
//  Created by 董依萌 on 2017/4/27.
//
//

#include "Block.h"

Vector<Block*> *Block::blocks = new Vector<Block*>();

Vector<Block*> * Block::getBlocks(){
    return Block::blocks;
}

Block* Block::createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor){
    
    auto b = new Block();  //创建 Block
    b->initWithArgs(color,size,label,fontSize,textColor);   // 初始化
    b->autorelease();       //释放
   
    blocks->pushBack(b);
    
    return b;
}
//初始化
bool Block::initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor){
    
    Sprite::init();     // 父类的init方法
    
    lineIndex = 0;     //初始化行索引 记录到第几行
    
    //配置Block
    setContentSize(size);          //内容大小
    setAnchorPoint(Point::ZERO);   //从左下角开始对齐
    setTextureRect(Rect(0,0,size.width,size.height)); //呈现颜色
    setColor(color);               //设置颜色
    
    //添加文本
    auto l = Label::create();
    l->setString(label);         //设置文字 为 babel
    l->setSystemFontSize(fontSize);  //设置字号
    l->setTextColor(textColor);      //设置颜色
    addChild(l);                    //添加到当前的容器里面
    l->setPosition(size.width/2,size.height/2);  //设置位置 为 中间位置
    
    return true;
}
void Block::removeBlock(){
    auto c = getColor();
    log("Remove block,color is (%d,%d,%d)",c.r,c.g,c.b);
    
    removeFromParent();
    blocks->eraseObject(this);
}
void Block::setLineIndex(int v){
    this->lineIndex = v;
}

int Block::getLineIndex(){
   // int a = this->lineIndex;
    //std::cout<<a;
    return this->lineIndex;
}

void Block::moveDown(){
    
    this->lineIndex--;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex*visibleSize.height/4)),
                               CallFunc::create([this](){
        
        if (lineIndex<0) {
            this->removeBlock();
        }
        
    }), NULL));
}


