//
//  C++ class.hpp
//  first_cocos
//
//  Created by 董依萌 on 2017/4/27.
//
//

#ifndef C___class_hpp
#define C___class_hpp

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;
class Block:public Sprite{
    
private:
    static Vector<Block*> *blocks; //记录创建Block(块)的数组
    int lineIndex;//记录行的索引
public:
    
    //获取所有块的方法
    static Vector<Block*> *getBlocks();
    //静态的创建的方法
    static Block* createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    // 初始化的方法 颜色 大小 呈现的字符 字符大小 字符颜色
    virtual bool initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    //移除的方法
    void removeBlock();
    
    int getLineIndex();                  //得到行的索引
    void setLineIndex(int LineIndex);    //在外界可以设置行的索引
    void moveDown();
};


#endif /* C___class_hpp */
