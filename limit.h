#include<iostream>
#include<string>
#include<algorithm>
#include"./textgame.h"
using namespace std;

class Limit
{
    protected :
        position UpperLeftPosition;
        int id;
    public: 
        Limit(position Position):id(0){
            this->UpperLeftPosition = Position;
        }
        Limit(int ParkingSpace[][8], int sLimit){}
        int getID(){ return id;}
        position getPosition(){ return UpperLeftPosition;}
        virtual ~Limit(){}
        virtual position Moving() = 0;
        virtual int getLimitValue() = 0;
        virtual void limitMinusMinus() = 0;
};

class Lake: public Limit
{
    private:
    public:
        //將有湖的地方設為-2
        Lake(position UpperLeftPosition, int ParkingSpace[][8]) : Limit::Limit(UpperLeftPosition)
        {
            id = -2;
            ParkingSpace[UpperLeftPosition.y][UpperLeftPosition.x] = id;
            ParkingSpace[UpperLeftPosition.y][UpperLeftPosition.x + 1] = id;
            ParkingSpace[UpperLeftPosition.y + 1][UpperLeftPosition.x] = id;
            ParkingSpace[UpperLeftPosition.y + 1][UpperLeftPosition.x + 1] = id;
        }
        position Moving(){ return {0,0};}
        int getLimitValue(){ return 0;}
        void limitMinusMinus(){}
};

class Frog: public Limit
{
    private:
        int stepLimit;
    public:
        //青蛙如同停車場的牆一樣，撞到要停下，因此id設為-1
        Frog(int ParkingSpace[][8], int sLimit):Limit::Limit(ParkingSpace, sLimit)
        {
            id = -1;
            stepLimit = sLimit;
            //根據輸入的步數限制判斷要將青蛙放在哪一格
            position Location;
            if (stepLimit <= 4)
            {
                Location.x = 512 - 64;
                Location.y = 192 + 64 * sLimit;
            }
            else if (stepLimit <= 11)
            {
                Location.x = 64 * (11 - sLimit);
                Location.y = 448;
            }
            else if (stepLimit <= 18)
            {
                Location.x = 0;
                Location.y = 64 * (18 - sLimit);
            }
            else if (stepLimit <= 25)
            {
                Location.x = 448 - 64 * (25 - sLimit);
                Location.y = 0;
            }
            ParkingSpace[Location.y][Location.x] = id;   
            this->UpperLeftPosition = Location;
        }
        ~Frog(){}
        //判斷步數剩多少，並回傳移動的方向
        position Moving()
        {
            position move = {0,0};
            if(stepLimit <= 4)
                move.y = -1;
            else if (stepLimit <= 11)
                move.x = 1;
            return move;
        }
        int getLimitValue(){ return stepLimit;}
        void limitMinusMinus(){ stepLimit--;}
};

class Turtle: public Limit
{
    private:
        int timeLimit;
    public:
        //烏龜如同停車場的牆一樣，撞到要停下，因此id設為-1
        Turtle(int ParkingSpace[][8], int tLimit):Limit::Limit(ParkingSpace, tLimit)
        {
            id = -1;
            timeLimit = tLimit;
            //計算應該把烏龜放到哪裡
            position Location;
            if (timeLimit <= 8)
            {
                Location.x = 512 - 64;
                Location.y = 192 + 32 * tLimit;
            }
            else if (timeLimit <= 22)
            {
                Location.x = 32 * (22 - tLimit);
                Location.y = 448;
            }
            else if (timeLimit <= 36)
            {
                Location.x = 0;
                Location.y = 32 * (36 - tLimit);
            }
            else if (timeLimit <= 50)
            {
                Location.x = 448 - 32 * (50 - tLimit);
                Location.y = 0;
            }
            ParkingSpace[Location.y][Location.x] = id;   
            this->UpperLeftPosition = Location;
        }
        ~Turtle(){}
        //根據剩餘時間計算烏龜的移動方向
        position Moving()
        {
            position move = {0,0};
            if(timeLimit > 36)
                move.x = -32;
            else if (timeLimit > 22)
                move.y = 32;
            else if (timeLimit > 8)
                move.x = 32;
            else
                move.y = -32;
            return move;
        }
        int getLimitValue(){ return timeLimit;}
        void limitMinusMinus(){ timeLimit--;}
};
