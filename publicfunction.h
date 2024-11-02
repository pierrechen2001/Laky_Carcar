#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include<fstream>
#include"./limit.h"
using namespace std;

//設定車輛及限制各在carPicture中的哪裡
void setOriginalCar(sf::Sprite* CarType[], sf::Texture& carPicture, sf::Sprite& frog, sf::Sprite& dragon, sf::Sprite& turtle)
{
    int shortHeight = 128;
    int longHeight = 192;

    for(int i = 0; i < 6; i++){
        CarType[0][i].setTexture(carPicture);
        CarType[0][i].setTextureRect( sf::IntRect(i*w, 0, w, shortHeight));
    }
    for(int i = 0; i < 2; i++){
        CarType[1][i].setTexture(carPicture);
        CarType[1][i].setTextureRect( sf::IntRect(i*w + 6*w, 0, w, longHeight));
    }
    int n = 0;
    for(int i = 0; i < 2; i++)
      for(int j = 0; j < 3; j++){
        CarType[2][n].setTexture(carPicture);
        CarType[2][n].setTextureRect( sf::IntRect(i*shortHeight, (4+j)*w, shortHeight, w));
        n++;
    }
    for(int i = 0; i < 2; i++){
        CarType[3][i].setTexture(carPicture);
        CarType[3][i].setTextureRect( sf::IntRect(2*shortHeight, (4+i)*w, longHeight, w));
    }
    frog.setTexture(carPicture);
    frog.setTextureRect(sf::IntRect(5*w, 3*w, w, w));
    dragon.setTexture(carPicture);
    dragon.setTextureRect(sf::IntRect(7*w, 3*w, w, w));
    turtle.setTexture(carPicture);
    turtle.setTextureRect(sf::IntRect(6*w, 3*w, w, w));
}

//設定每關停車場背景
void setStageBackground(const int totalStageCnt, sf::Texture background[], sf::Sprite Background[])
{
    string stagePath = "./background/stage.png";  
    //將每關的背景讀入
    for(int i = 0; i < totalStageCnt; i++)
    {
        string replacementChar = to_string(i + 1);
        stagePath.insert(57, replacementChar);
        background[i].loadFromFile(stagePath);
        //重設stagePath
        stagePath = "./background/stage.png";
    }
    for(int i = 0; i < 9; i++){
        Background[i].setTexture(background[i]);
        Background[i].setPosition(0,0);
    }
}

//設定每關關卡內容的讀取路徑
void setStageInfoPathString(int totalStageCnt, string stageInfo[])
{
    string stageInfoPathString = "./stageInfo/carInfo_Stage.txt";
    for(int i = 0; i < totalStageCnt; i++)
    {
        string replacementChar = to_string(i + 1);
        stageInfoPathString.insert(64, replacementChar);
        stageInfo[i] = stageInfoPathString;
        //重設路徑
        stageInfoPathString = "./stageInfo/carInfo_Stage.txt";
    }
}    

//判斷使用者點擊哪一關
int DecideStage(int x, int y)
{
    if(x == 0 && y == 0)
        return 1;
    else if(x == 1 && y == 0)
        return 2;
    else if(x == 2 && y == 0)
        return 3;
    else if(x == 0 && y == 1)
        return 4;
    else if(x == 1 && y == 1)
        return 5;
    else if(x == 2 && y == 1)
        return 6;
    else if(x == 0 && y == 2)
        return 7;
    else if(x == 1 && y == 2)
        return 8;
    else if(x == 2 && y == 2)
        return 9;
    else
        return 0;
}

//重設停車場陣列
void resetParkingSpace(int ParkingSpace[][8])
{
    //先全部設為空值(0)
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            ParkingSpace[i][j] = 0;
    //邊界設為-1
    for(int i = 0; i < 8; i++)
    {
        ParkingSpace[i][0] = -1;
        ParkingSpace[i][7] = -1;
        ParkingSpace[0][i] = -1;
        ParkingSpace[7][i] = -1;
    }
    //出口設為空(0)
    ParkingSpace[3][7] = 0;
}

//讀取停車場中的車輛資訊
void setCarInfo(ifstream& fin, Car* car[], sf::Sprite* carSprite[], sf::RenderWindow& gameStage, int carCnt, sf::Sprite* CarPicture[])
{
    int carNum;
    position start;
    string carType, carLength;
    for(int i = 1; i <= carCnt; i++)
    {
        fin >> carType >> carLength >> carNum >> start.x >> start.y;
        //New出Car並找到車子圖片及設定圖片位置
        if(carType == "straight")
        {
            car[i] = new StraightCar(carType, carLength, carNum, start, i);
            if(carLength == "short"){
                carSprite[i] = &CarPicture[0][carNum];
                CarPicture[0][carNum].setPosition(start.x * w, start.y * w);
                gameStage.draw(CarPicture[0][carNum]);
            }
            else if (carLength == "long")
            {
                carSprite[i] = &CarPicture[1][carNum];
                CarPicture[1][carNum].setPosition(start.x * w, start.y * w);
                gameStage.draw(CarPicture[1][carNum]);
            } 
        }
        else if(carType == "horizontal"){
            car[i] = new HorizontalCar(carType, carLength, carNum, start, i);
            if(carLength == "short"){
                carSprite[i] = &CarPicture[2][carNum];
                CarPicture[2][carNum].setPosition(start.x * w, start.y * w);
                gameStage.draw(CarPicture[2][carNum]);
            }
            else if(carLength == "long"){
                carSprite[i] = &CarPicture[3][carNum];
                CarPicture[3][carNum].setPosition(start.x * w, start.y * w);
                gameStage.draw(CarPicture[3][carNum]);
            }
        }
    }
}

//讀取該關卡的限制們，並回傳青蛙或烏龜限制在Limit陣列的第幾格位子
int setLimit(ifstream& fin, int stage, int limitCnt, bool* frogExist, bool* turtleExist, Limit* limit[], sf::Sprite& frog, sf::Sprite& dragon, sf::Sprite& turtle, sf::RenderWindow& gameStage)
{
    std::string limitType = "";
    int animalI;
    int stepLimit;
    int timeLimit;
    position limitPosition;
    //讀取limit的位子並畫出限制圖像
    for(int i = 0; i < limitCnt; i++)
    {
        fin >> limitType;
        if(limitType == "lake")
        {
            fin >> limitPosition.x >> limitPosition.y;
            limit[i] = new Lake(limitPosition, ParkingSpace);
        }
        if(limitType == "frog")
        {
            animalI = i;
            *frogExist = true;
            fin >> stepLimit;
            limit[i] = new Frog(ParkingSpace, stepLimit);
            limitPosition = limit[i]->getPosition();
            if (stage <= 3)
            {
                dragon.setPosition(limitPosition.x, limitPosition.y);
                gameStage.draw(dragon); 
            }
            else
            {
                frog.setPosition(limitPosition.x, limitPosition.y);
                gameStage.draw(frog); 
            }
             
        }
        if(limitType == "turtle")
        {
            animalI = i;
            *turtleExist = true;
            fin >> timeLimit;
            limit[i] = new Turtle(ParkingSpace, timeLimit);
            limitPosition = limit[i]->getPosition();
            turtle.setPosition(limitPosition.x, limitPosition.y);
            gameStage.draw(turtle);
        }
    }
    return animalI;
}

//重設stage並關掉遊戲視窗
void endGameStage(int& stage, sf::RenderWindow& gameStage)
{
    stage = 0;
    gameStage.close();
}

//畫出所有車子的draw function
void drawContainCar(bool frogExist, bool turtleExist, int carCnt, int stage, sf::Sprite Background[], sf::Sprite* carSprite[], sf::Sprite& something, sf::RenderWindow& gameStage)
{
    gameStage.clear();
    //畫背景
    gameStage.draw(Background[stage-1]);
    //若不是烏龜限制也不是青蛙限制，代表沒有限制或是只有湖，那就不要印傳進來的something
    if(!(!turtleExist && !frogExist))
        gameStage.draw(something);
    //把所有車畫出來
    for(int i = 1; i <= carCnt; i++)
        gameStage.draw(*carSprite[i]); 
    gameStage.display(); 
}

//不用畫出所有車子的draw function
void drawWithoutCar(int stage, sf::Sprite Background[], sf::Sprite& something, sf::RenderWindow& gameStage)
{
    gameStage.clear();
    gameStage.draw(Background[stage-1]);
    gameStage.draw(something);
    gameStage.display(); 
}

//給有時間限制（烏龜限制）的關卡使用，用來判斷時間是否已經到達限制，或是已經超過一秒。
//若已剩餘時間為0，便把gameContinue設成false，並畫出失敗的畫面，return false讓程式碼不用畫出新的畫面覆蓋掉失敗的畫面。
//若仍有剩餘時間，代表遊戲尚未結束，回傳true去印出所有的畫面及車子。若時間已達1秒，便移動limit的位子並重設時間，且將剩餘時間-1。若時間未達一秒就單純回傳true並跳出迴圈。
bool checkTime(int carCnt, sf::Clock& clock, sf::Time& elapsed, Limit* limit[], int animalI, int stage, bool& gameContinue, sf::Sprite Background[], sf::Sprite& FailOfTurtle, sf::Sprite& turtle, sf::RenderWindow& gameStage)
{
    if(limit[animalI]->getLimitValue() == 0)
    {
        gameContinue = false;
        drawWithoutCar(stage, Background, FailOfTurtle, gameStage);
        cout << "You got NO time left! Try AGAIN!" << endl;
        return false;
    }
    else if (elapsed.asSeconds() >= 1)
    {
        position moveway = limit[animalI]->Moving();
        turtle.move(moveway.x, moveway.y);
        clock.restart();
        limit[animalI]->limitMinusMinus();                       
    }
    return true;
}

//若回傳true則無事，回傳false則break原本的迴圈
bool DecideWhereToMove(int theCarMovingNow, int dx, int dy, int speed, sf::Sprite* carSprite[])
{
    if(dx == 0 && dy == 0)
        //break;
        return false;
    if(dx != 0)
        carSprite[theCarMovingNow]->move(speed * (dx > 0 ? 1 : -1), 0);
    else if(dy != 0)
        carSprite[theCarMovingNow]->move(0, speed * (dy > 0 ? 1 : -1));
    return true;
}