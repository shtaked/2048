#include "MainScene.h"

USING_NS_CC;

MainScene::MainScene()
        : board_(Board(4))
{
    board_.addListener(this);
}


Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

    auto minSize = ::std::min(visibleSize.width, visibleSize.height);
    auto fieldSize = minSize * 0.8;

    auto layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), fieldSize, fieldSize);
    layerColorBG->setPosition(Vec2(origin.x + visibleSize.width/2 - fieldSize/2,
            origin.y + visibleSize.height/2 - fieldSize/2));
    this->addChild(layerColorBG);

    auto size = board_.size();
    cells_.assign(size, ::std::vector<UiCell>(size, UiCell()));

    const auto cellsProportion = 0.90;
    auto cellSize = fieldSize * cellsProportion / size;
    auto cellMargin = fieldSize * (1 - cellsProportion) / (size + 1);
    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size; ++j) {
            auto cellPos = Vec2(cellMargin + j * (cellSize + cellMargin),
                    fieldSize - cellMargin - cellSize - i * (cellSize + cellMargin));

            auto layerCell = LayerColor::create(Color4B(180, 190, 200, 255), cellSize, cellSize);
            layerCell->setPosition(cellPos);
            layerColorBG->addChild(layerCell);

            layerCell = LayerColor::create(Color4B(190, 200, 180, 0), cellSize, cellSize);
            layerCell->setPosition(cellPos);
            layerColorBG->addChild(layerCell);

            auto label = LabelTTF::create("", "Arial", 48);
            label->setPosition(Vec2(cellSize/2, cellSize/2));

            layerCell->addChild(label);

            cells_[i][j] = { layerCell, label };
        }
    }

    board_.spawnNew();
    board_.spawnNew();
    
    return true;
}


void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainScene::onCellMoved(const Index &startIndex, const Index &endIndex)
{
    auto cellDistance = (startIndex.first == endIndex.first) ?
            (std::abs(startIndex.second - endIndex.second)) :
            (std::abs(startIndex.first - endIndex.first));
    const auto cellSpeed = 16.0; //4 cells per second

    auto actionMove = MoveTo::create(cellDistance / cellSpeed, cells_[endIndex.first][endIndex.second].color->getPosition());
    auto actionUpdate = CallFunc::create(
            [this, startIndex, endIndex, oldPos = cells_[startIndex.first][startIndex.second].color->getPosition()](){
        cells_[startIndex.first][startIndex.second].color->setPosition(oldPos);
        updateCell(startIndex);
        updateCell(endIndex);
    });

    cells_[startIndex.first][startIndex.second].color->runAction(
            Sequence::create(actionMove, actionUpdate, NULL));
}

void MainScene::onCellUpdated(const Index &index, CellValue value)
{
    cells_[index.first][index.second].color->setOpacity(value == 0 ? 0 : 255);
    cells_[index.first][index.second].color->setLocalZOrder(value == 0 ? 0 : 1);
    //cells_[index.first][index.second].color->setPositionZ(value == 0 ? 0 : 1);
    //cells_[index.first][index.second].text->setPositionZ(value == 0 ? 0 : 1);
    cells_[index.first][index.second].text->setString(value == 0 ? " " : ::std::to_string(value));
}

void MainScene::updateCell(const Index &index)
{
    onCellUpdated(index, board_.rows()[index.first][index.second]);
}

void MainScene::onUpdated(const Rows &rows)
{
//    for (auto i = 0; i < rows.size(); ++i)
//        for (auto j = 0; j < rows.size(); ++j)
//            onCellUpdated(Index(i, j), rows[i][j]);
}

void MainScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

}

void MainScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W: board_.move(Board::MovementType::kUp); break;
        case EventKeyboard::KeyCode::KEY_A: board_.move(Board::MovementType::kLeft); break;
        case EventKeyboard::KeyCode::KEY_D: board_.move(Board::MovementType::kRight); break;
        case EventKeyboard::KeyCode::KEY_S: board_.move(Board::MovementType::kDown); break;
        default: break;
    }
}