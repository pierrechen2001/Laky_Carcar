#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include"./publicfunction.h"
using namespace sf;

int main()
{
    //開選單視窗
    RenderWindow menu(VideoMode(512,512), "menu");
    menu.setFramerateLimit(60);

    //存取圖片
    Texture carPicture, success, failOfLake, failOfTurtle, failOfFrog;
    Texture background[9];
    Texture menuBackground, homepage;
    carPicture.loadFromFile("./texture/textureOfCars.png");
    success.loadFromFile("./texture/success.png");
    failOfLake.loadFromFile("./texture/failOfLake.png");
    failOfFrog.loadFromFile("./texture/failOfFrog.png");
    failOfTurtle.loadFromFile("./texture/failOfTurtle.png");
    menuBackground.loadFromFile("./background/menu.png");
    homepage.loadFromFile("./background/homepage.png");

    //將圖片設成Sprite
    Sprite Success(success);
    Sprite FailOfLake(failOfLake);
    Sprite FailOfFrog(failOfFrog);
    Sprite FailOfTurtle(failOfTurtle);
    Sprite Background[9];
    Sprite MenuBackground(menuBackground);
    Sprite Homepage(homepage);
    Sprite frog;
    Sprite dragon;
    Sprite turtle;

    //設定各台車、各動物的圖片
    Sprite* CarType[4];
    Sprite straightShortCar[6];
    CarType[0] = straightShortCar;
    Sprite straightLongCar[2];
    CarType[1] = straightLongCar;
    Sprite horizontalShortCar[6];
    CarType[2] = horizontalShortCar;
    Sprite horizontalLongCar[2];
    CarType[3] = horizontalLongCar;
    setOriginalCar(CarType, carPicture, frog, dragon, turtle);
    
    //設定關卡背景以及每關關卡內容要從哪個路徑讀取
    setStageBackground(totalStageCnt, background, Background);
    string stageInfo[totalStageCnt];
    setStageInfoPathString(totalStageCnt, stageInfo);

    //印出首頁
    menu.draw(Homepage);
    menu.display();
    printf("\033[31m🚗 Welcome to LAKY CARCAR!!!🚗\033[0m \n");
    printf("\033[31m╔╗─────╔╗─────╔═══╗────╔═══╗\n║║─────║║─────║╔═╗║────║╔═╗║\n║║──╔══╣║╔╦╗─╔╣║─╚╬══╦═╣║─╚╬══╦═╗\n║║─╔╣╔╗║╚╝╣║─║║║─╔╣╔╗║╔╣║─╔╣╔╗║╔╝\n║╚═╝║╔╗║╔╗╣╚═╝║╚═╝║╔╗║║║╚═╝║╔╗║║\n╚═══╩╝╚╩╝╚╩═╗╔╩═══╩╝╚╩╝╚═══╩╝╚╩╝\n──────────╔═╝║\n──────────╚══╝\033[0m \n\n");
    cout << "Press START to play the game!" << endl;
    
    //整數 stage 用來存使用者點選哪一關
    int stage = 0;
    //布林值 homeFlag 用來判斷是否是首頁
    bool homeFlag = true;
    
    while(menu.isOpen())
    {
        //點擊開始遊戲、選關卡
        Event f;
        while(menu.pollEvent(f))
        {
            if(f.type == Event::MouseButtonPressed && homeFlag == true)
            {
                if(f.mouseButton.button == Mouse::Left)
                {
                    //畫出選關卡的畫面
                    menu.draw(MenuBackground);
                    menu.display();
                    //首頁被點完之後就把flag設成false，不再跑出首頁
                    homeFlag = false;
                    cout << "Press the stage you want to play!" << endl;
                }
            }
            else if(f.type == Event::Closed)
                menu.close();
            else if(f.type == Event::MouseButtonPressed)
                if(f.mouseButton.button == Mouse::Left)
                {
                    Vector2i pos = Mouse::getPosition(menu);
                    int x = pos.x/170;
                    int y = pos.y/170;
                    stage = DecideStage(x, y);
                    cout << endl << "☆*:. Stage " << stage << " START!! .:*☆" << endl;
                    cout << "    ゲーム・スタート !" << endl << endl;
                }
        }

        //點擊某一關卡後，跳出該關卡的畫面
        if(stage != 0)
        {
            //重設停車場陣列
            resetParkingSpace(ParkingSpace);
        
            //開一個關卡的視窗
            RenderWindow gameStage(VideoMode(512,512), "parking");
            gameStage.setFramerateLimit(60);

            //讀檔
            ifstream fin(stageInfo[stage - 1]);
            int carCnt = 0;
            fin >> carCnt;
            Car* car[carCnt + 1];
            Sprite* carSprite[carCnt + 1];
            
            //畫背景跟設定該關車輛資訊
            gameStage.draw(Background[stage - 1]);
            setCarInfo(fin, car, carSprite, gameStage, carCnt, CarType);
            
            //fin關卡特殊物件
            bool mouseClicked = false;
            bool frogExist = false;
            bool turtleExist = false;
            int limitCnt = 0;
            fin >> limitCnt;
            Limit* limit[limitCnt];
            //設定limit並記錄動物限制的索引值以便後續getlimit資訊
            int animalI = setLimit(fin, stage, limitCnt, &frogExist, &turtleExist, limit, frog, dragon, turtle, gameStage);
            gameStage.display();
        
            //計時用特殊物件
            sf::Clock clock;
            sf::Time elapsed;

            //在關卡裡跑移動函式
            bool gameContinue = true;
            while(gameStage.isOpen() && stage != 0)
            {
                Event e;
                //如果是烏龜（計時）關卡，跑第一個while
                if (turtleExist)
                {
                    while (gameStage.pollEvent(e)){
                        if (e.type == Event::Closed){
                            endGameStage(stage, gameStage);
                            gameContinue = false;
                            break;
                        }
                        else if (e.type == Event::MouseButtonPressed){
                            if (e.mouseButton.button == sf::Mouse::Left)
                                mouseClicked = true;
                        }
                    }

                    //使用者為點擊時的計時，若超過一秒則畫出烏龜移動後的位子，若無則繼續。
                    if(gameContinue)
                    {
                        elapsed = clock.getElapsedTime();
                        if ((checkTime(carCnt, clock, elapsed, limit, animalI, stage, gameContinue, Background, FailOfTurtle, turtle, gameStage)))
                            drawContainCar(frogExist, turtleExist, carCnt, stage, Background, carSprite, turtle, gameStage);
                        else
                            continue;
                    }

                    //若使用者點擊了滑鼠，便開始判斷滑鼠位子以及移動車輛
                    if (mouseClicked)
                    {
                        if(gameContinue == false){
                            endGameStage(stage, gameStage);
                            break;
                        }
                        
                        Vector2i pos = Mouse::getPosition(gameStage);
                        int x = pos.x/w ;
                        int y = pos.y/w ;

                        //當使用者點擊到的不是沒車、牆或是湖的時候便進入迴圈
                        if(ParkingSpace[y][x] != 0 && ParkingSpace[y][x] != -1 && ParkingSpace[y][x] != -2)
                        {
                            //紀錄點擊的車輛
                            int theCarMovingNow = ParkingSpace[y][x];
                            position tmp = {0,0};
                            //Moving函式會回傳車子移動到的最終位置
                            tmp = car[theCarMovingNow]->Moving(y,x);
                            int dx = tmp.x;
                            int dy = tmp.y;
                            float speed = 2;
                            
                            //移動車子，每次移動都重新畫且顯示一次畫面
                            for(int j = 0; j < 64 * (dx != 0 ? abs(dx) : abs(dy)); j += speed)
                            {
                                //若車子無移動，則break掉迴圈不讓車子移動
                                if (DecideWhereToMove(theCarMovingNow, dx, dy, speed, carSprite) == false)
                                    break;
                                //迴圈內也要算時間，讓烏龜持續移動
                                elapsed = clock.getElapsedTime();
                                if ((checkTime(carCnt, clock, elapsed, limit, animalI, stage, gameContinue, Background, FailOfTurtle, turtle, gameStage)))
                                    drawContainCar(frogExist, turtleExist, carCnt, stage, Background, carSprite, turtle, gameStage);
                                else
                                    break;
                            }
                            
                            //若仍有時間剩餘且紅車已到達出口則判斷為成功
                            if (limit[animalI]->getLimitValue() > 0 && ParkingSpace[3][7] != 0)
                            {
                                drawWithoutCar(stage, Background, Success, gameStage);
                                cout << "Success!" << endl;
                                printf("\033[33m▒█▀▀▀█ █░░█ █▀▀ █▀▀ █▀▀ █▀▀ █▀▀ \n░▀▀▀▄▄ █░░█ █░░ █░░ █▀▀ ▀▀█ ▀▀█ \n▒█▄▄▄█ ░▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ \033[0m\n\n ");
                                gameContinue = false;
                            }
                            if(gameContinue && (dx != 0 or dy != 0)){
                                print(car);
                                cout << endl;
                            }
                        }
                        mouseClicked = false;
                    }
                    gameStage.clear(Color::White);
                }   
                //如果是青蛙（步數）關卡或是普通關卡，跑第二個while
                else
                {
                    while (gameStage.pollEvent(e))
                    {
                        if (e.type == Event::Closed){
                            endGameStage(stage, gameStage);
                            break;
                        }
                        //等到滑鼠點擊後開始處理事件
                        if (e.type == Event::MouseButtonPressed)
                        {
                            if (e.mouseButton.button == Mouse::Left)
                            {
                                //若遊戲結束則直接關掉遊戲視窗
                                if(gameContinue == false){
                                    endGameStage(stage, gameStage);
                                    break;
                                }

                                //判斷鼠標點擊位置
                                Vector2i pos = Mouse::getPosition(gameStage);
                                int x = pos.x/w ;
                                int y = pos.y/w ;
                                if(ParkingSpace[y][x] != 0 && ParkingSpace[y][x] != -1 && ParkingSpace[y][x] != -2)
                                {
                                    int theCarMovingNow = ParkingSpace[y][x];
                                    position tmp = {0,0};
                                    tmp = car[theCarMovingNow]->Moving(y,x);
                                    int dx = tmp.x;
                                    int dy = tmp.y;
                                    float speed = 2;

                                    //移動車輛        
                                    for(int j = 0; j < 64 * (dx != 0 ? abs(dx) : abs(dy)); j += speed)
                                    {
                                        if (DecideWhereToMove(theCarMovingNow, dx, dy, speed, carSprite) == false)
                                            break;
                                        if (stage <= 3)
                                            drawContainCar(frogExist, turtleExist, carCnt, stage, Background, carSprite, dragon, gameStage);
                                        else
                                            drawContainCar(frogExist, turtleExist, carCnt, stage, Background, carSprite, frog, gameStage);
                                    }

                                    //若紅車已達終點，則判斷為成功且遊戲結束
                                    if(ParkingSpace[3][7] != 0)
                                    {
                                        drawWithoutCar(stage, Background, Success, gameStage);
                                        cout << "Success!" << endl;
                                        printf("\033[33m▒█▀▀▀█ █░░█ █▀▀ █▀▀ █▀▀ █▀▀ █▀▀ \n░▀▀▀▄▄ █░░█ █░░ █░░ █▀▀ ▀▀█ ▀▀█ \n▒█▄▄▄█ ░▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ \033[0m\n\n ");
                                        gameContinue = false;
                                        continue;
                                    }
                                     
                                    //若掉進湖裡，則判斷為失敗且遊戲結束
                                    if(car[theCarMovingNow]->lakeFailorNot())
                                    {
                                        drawWithoutCar(stage, Background, FailOfLake, gameStage);
                                        cout << "You fall into the LAKY!" << endl;
                                        gameContinue = false;
                                        continue;
                                    }

                                    //若是青蛙限制的關卡，且尚有剩餘步數的話便移動青蛙
                                    if(frogExist and (dx != 0 or dy != 0) and limit[animalI]->getLimitValue() > 0)
                                    {                                            
                                        //青蛙移動 
                                        for(int j = 0; j < 64; j += speed)
                                        {
                                            position moveway = limit[animalI]->Moving();
                                            if (stage <= 3){
                                                dragon.move(moveway.x * speed, moveway.y * speed);
                                                drawContainCar(frogExist, turtleExist, carCnt, stage, Background, carSprite, dragon, gameStage);
                                            }
                                            else{
                                                frog.move(moveway.x * speed, moveway.y * speed);
                                                drawContainCar(frogExist, turtleExist, carCnt, stage, Background, carSprite, frog, gameStage);
                                            }                                        
                                        }
                                        limit[animalI]->limitMinusMinus();
                                    }

                                    //若是青蛙限制的關卡，且剩餘步數為零則判斷為失敗且遊戲結束
                                    if(frogExist and limit[animalI]->getLimitValue() == 0)
                                    {
                                        drawWithoutCar(stage, Background, FailOfFrog, gameStage);
                                        cout << "You got NO step left! Try AGAIN!" << endl;
                                        gameContinue = false;
                                        continue;
                                    }

                                    //cout文字版車車
                                    if(dx != 0 or dy != 0){
                                        print(car);
                                        cout << endl;
                                        if(frogExist)
                                            cout << "You got " << limit[animalI]->getLimitValue() << " steps left."  << endl;
                                    }
                                }
                            }
                        }
                    }
                }
                gameStage.clear(Color::White);
            }
            //Delete New出來的東西
            for(int i = 1; i <= carCnt; i++){
                delete car[i];
                car[i] = nullptr;
            }
            for(int i = 0; i < limitCnt; i++){
                delete limit[i];
                limit[i] = nullptr;
            }
        }
    //跳回選關卡的畫面
    }
    return 0;
}