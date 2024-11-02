#include<iostream>
#include"./car.h"
using namespace std;

void print(Car *car[])
{   
    cout << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (ParkingSpace[i][j] == -1)
            {
                cout << "牆 ";
            }
            else if (ParkingSpace[i][j] == 0)
            {
                cout << "   ";
            }
            else if (ParkingSpace[i][j] == -2)
            {
                cout << "\033[5;30m湖\033[0m ";
            }
            else
            {
                const int &color = car[ParkingSpace[i][j]]->getCarColor();
                if (color == 0)
                {
                    if (car[ParkingSpace[i][j]]->getId() == 1)
                        printf("\033[1;31m紅\033[0m ");
                    else
                        printf("\033[31m紅\033[0m ");
                }
                if (color == 1)
                {
                    printf("\033[36m車\033[0m ");
                }
                if (color == 2)
                    printf("\033[35m紫\033[0m ");
                if (color == 3)
                    printf("\033[32m綠\033[0m ");
                if (color == 4)
                    printf("\033[34m藍\033[0m ");
                if (color == 5)
                    printf("\033[33m黃\033[0m ");
            }
        }
        cout << endl;
    }
}