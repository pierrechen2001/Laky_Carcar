#include<iostream>
using namespace std;

//w是停車場一格的長度
const int w = 64;
const int totalStageCnt = 9;
int ParkingSpace[8][8] = {0};

struct position
{
    int x;
    int y;
};
