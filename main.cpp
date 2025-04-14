#define OLC_PGE_APPLICATION

#include <iostream>
#include "olcPixelGameEngine.h"

// g++ -fopenmp main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17 -O3 -mavx2 -o main

class RayCaster : public olc::PixelGameEngine
{
public:

    int x = 0;
    int y = 0;

    RayCaster()
	{
		sAppName = "Ray Caster";
	}

public:
	bool OnUserCreate() override
	{
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
        {
			for (int y = 0; y < ScreenHeight(); y++)
            {
				Draw(x, y, olc::Pixel(x % 255, y % 255, (x * y) % 255));
            }
        }
		return true;
	}
};

int main(int argc, char** argv)
{
    std::cout << "Hello World\n";

    RayCaster application;
    if (application.Construct(516, 516, 1, 1))
    {
        application.Start();
    }

    return 0;
}