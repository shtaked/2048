#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

#include "Board.h"

class MainScene :
        public cocos2d::Layer,
        public BoardListener
{
public:
    MainScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

private:
    virtual void onCellMoved(const Index &startIndex, const Index &endIndex) override;
    virtual void onCellUpdated(const Index &index, CellValue value) override;
    virtual void onUpdated(const Rows &rows) override;

    void updateCell(const Index &index);

    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

private:
    Board board_;

    struct UiCell
    {
        cocos2d::LayerColor *color;
        cocos2d::LabelTTF *text;
    };

    ::std::vector< ::std::vector<UiCell> > cells_;
};

#endif // __MAIN_SCENE_H__
