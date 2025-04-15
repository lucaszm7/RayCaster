#define OLC_PGE_APPLICATION

#include <cmath>
#include <iostream>
#include "olcPixelGameEngine.h"

// g++ -fopenmp main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17 -O3 -o main

class RayCaster : public olc::PixelGameEngine
{
public:

    int x = 0;
    int y = 0;

	struct Player{
		olc::vf2d posicao;
		float raio;
		// Construtor
		Player(olc::PixelGameEngine* ptr, float a){
			posicao = ptr->GetMousePos();
			raio = a;
		}
		void drawPlayer(olc::PixelGameEngine* ptr){
			ptr->FillCircle(posicao, raio, olc::BLUE);
		}
	};

	struct Boundary{
		float x1, y1;		
		float x2, y2;
		// Funçao construtora da struct Boundary
		Boundary(float a, float b, float c, float d){
			x1 = a;
			y1 = b;
			x2 = c;
			y2 = d;
		}
		// Precisamos de um endereço do tipo olc::PixelGameEngine*
		void draw(olc::PixelGameEngine* pt){
			pt->DrawLine(x1, y1, x2, y2, olc::BLACK);
		}
	};

	Boundary wall = Boundary(400, 150, 400, 350);

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
		// um é inicializado no OnUserUpdate para receber a posiçao do mouse em tempo real
		Player um = Player(this, 5);
		// Called once per frame
		Clear(olc::WHITE);
		// Ja que wall é objeto da struct Boundary e esta pertence a class RayCaster, entao o ponteiro this recebe a funçao DrawLine como herança 
		wall.draw(this);
		um.drawPlayer(this);

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