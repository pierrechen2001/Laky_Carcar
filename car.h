#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<./position.h>
using namespace std;

class Car
{
    protected :
        string directionType;
        string lenType;
        int color;
        position start;
        position end;
        int id;
        bool lakeFail;
    public: 
        Car(string directionType, string lenType, int color, position start, int id)
        {
            this->directionType = directionType;
            this->lenType = lenType;
            this->color = color;
            this->start = start;
            this->end.x = 0;
            this->end.y = 0;
            this->id = id;
            this->lakeFail = false;
        }
        virtual ~Car(){}
        bool lakeFailorNot(){ return lakeFail;}
        int getId(){ return id;}
        int getCarColor(){ return color;}
        virtual position Moving(int y, int x) = 0;
};

class StraightCar : public Car
{
    private:
    public:
        //將車子存在的地方設成該車的id
        StraightCar(string directionType, string lenType, int color, position start, int id) : Car::Car(directionType, lenType, color, start, id)
        {
            if (lenType == "short")
            {
                ParkingSpace[start.y][start.x] = id;
                ParkingSpace[start.y + 1][start.x] = id;
                this->end.x = start.x;
                this->end.y = start.y + 1;
            }
            else
            {
                for(int i = start.y; i <= start.y + 2; i++){
                    ParkingSpace[i][start.x] = id;
                }
                this->end.x = start.x;
                this->end.y = start.y + 2;
            }
        }
        ~StraightCar(){}
        //判斷straightCar移動的函式，並回傳車頭最後移動到的位置
        position Moving(int y, int x)
        {   
            position moving = {0,0};
            //若點擊車頭，則判斷上一格是否沒車，沒車就讓車子往上走，若碰到湖則判斷遊戲失敗
            if(y == start.y)
            {
                if(ParkingSpace[start.y-1][start.x] == -2){
                    moving.y--;
                    lakeFail = true;
                }
                while(ParkingSpace[start.y-1][start.x] == 0){
                    ParkingSpace[end.y][end.x] = 0;
                    ParkingSpace[start.y-1][start.x] = this->id;
                    start.y--;
                    end.y--;
                    moving.y--;
                    if(ParkingSpace[start.y-1][start.x] == -2){
                        moving.y--;
                        lakeFail = true;
                    }
                }
            }
            //若點擊車尾，則判斷下一格是否沒車，沒車就讓車子往下走，若碰到湖則判斷遊戲失敗
            else if(y == end.y)
            {
                if(ParkingSpace[end.y+1][end.x] == -2){
                    moving.y++;
                    lakeFail = true;
                }
                while(ParkingSpace[end.y+1][end.x] == 0){
                    ParkingSpace[start.y][start.x] = 0;
                    ParkingSpace[end.y+1][end.x] = this->id;
                    start.y++;
                    end.y++;
                    moving.y++;
                    if(ParkingSpace[end.y+1][end.x] == -2){
                        moving.y++;
                        lakeFail = true;
                    }
                }
            }
            return moving;
        }
};

class HorizontalCar : public Car
{
    private:
    public:
        //將車子存在的地方設成該車的id
        HorizontalCar(string directionType, string lenType, int color, position start, int id) : Car::Car(directionType, lenType, color, start, id)
        {
            if (lenType == "short")
            {
                ParkingSpace[start.y][start.x] = id;
                ParkingSpace[start.y][start.x + 1] = id;
                this->end.x = start.x + 1;
                this->end.y = start.y;
            }
            else
            {
                for(int i = start.x; i <= start.x + 2; i++){
                    ParkingSpace[start.y][i] = id;
                }
                this->end.x = start.x + 2;
                this->end.y = start.y;
            }
        }
        ~HorizontalCar(){}
        //判斷straightCar移動的函式，並回傳車頭最後移動到的位置
        position Moving(int y, int x)
        {
            position moving = {0,0};
            //若點擊車頭，則判斷右邊那格是否沒車，沒車就讓車子往右走，若碰到湖則判斷遊戲失敗
            if(x == start.x)
            {
                if(ParkingSpace[start.y][start.x-1] == -2){
                    moving.x--;
                    lakeFail = true;
                }
                while(ParkingSpace[start.y][start.x-1] == 0){
                    ParkingSpace[end.y][end.x] = 0;
                    ParkingSpace[start.y][start.x-1] = this->id;
                    start.x--;
                    end.x--;
                    moving.x--;
                    if(ParkingSpace[start.y][start.x-1] == -2){
                        moving.x--;
                        lakeFail = true;
                    }
                }
            }
            //若點擊車尾，則判斷左邊那格是否沒車，沒車就讓車子往左走，若碰到湖則判斷遊戲失敗
            else if(x == end.x)
            {
                if(ParkingSpace[end.y][end.x+1] == -2){
                    moving.x++;
                    lakeFail = true;
                }  
                while(ParkingSpace[end.y][end.x+1] == 0){
                    ParkingSpace[start.y][start.x] = 0;
                    ParkingSpace[end.y][end.x+1] = this->id;
                    start.x++;
                    end.x++;
                    moving.x++;
                    if(ParkingSpace[end.y][end.x+1] == -2){
                        moving.x++;
                        lakeFail = true;
                    }
                }
            }
            return moving;
        }
};
