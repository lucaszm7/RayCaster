#define OLC_PGE_APPLICATION

#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "olcPixelGameEngine.h"
#define PI 3.141592653589793f

// g++ -fopenmp main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17 -O3 -o main

struct Player
{
	olc::vf2d position;
	float speed;
	float raio;

	Player(float x, float y, float speed, float raio)
		: position(x, y), speed(speed), raio(raio)
	{}

	void drawPlayer(olc::PixelGameEngine* ptr)
	{
		ptr->FillCircle(position.x, position.y, raio, olc::MAGENTA);
	}
};


struct Map
{
	int width;
	int heigth;
	int cellSize;
	int stage[32][32] =    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
						
	Map(int width, int heigth, int cellSize)
		: width(width), heigth(heigth), cellSize(cellSize)
	{}

	const int* operator[](size_t row) const 
	{
        return stage[row];
    }
};

struct Ray
{
	olc::vf2d origin;
	olc::vf2d direction;

	Ray(olc::vf2d origin, olc::vf2d direction)
	: origin(origin), direction(direction) {}
};

class RayCaster : public olc::PixelGameEngine
{
public:
	Player player;
	Map map;

    RayCaster()
	: player(100, 100, 100, 5), map(32, 32, 29)
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
		Clear(olc::VERY_DARK_GREY);
		olc::vi2d pos = GetMousePos();

		for(int y = 0; y < map.heigth; y++)
		{
			for(int x = 0; x < map.width; x++)
			{
				if(map[y][x] == 1)
				{
					FillRect(x * map.cellSize, y * map.cellSize, map.cellSize, map.cellSize, olc::VERY_DARK_BLUE);
				}                                  
			}
		}

		// olc::vf2d direction = pos - player.position;
		// float hipotenusa = direction.mag();
		// olc::vf2d directionNormalized = direction / hipotenusa;

		// RAY
		// Calcula a hipotenusa com a diferença dos eixos X e Y do jogador ate a posicao do mouse
		float hipotenusa = sqrtf(powf((pos.x - player.position.x), 2) + powf((player.position.y - pos.y), 2));
		// Calcula os seno e cosseno
		float anguloYsin = (pos.y - player.position.y)/hipotenusa;
		float anguloXcos = (pos.x - player.position.x)/hipotenusa;

		// Acha o angulo entre jogador e mouse usando a funçao atan2()
		float angulo = atan2f(anguloYsin, anguloXcos);
		// Ideia inicializar o loop subtraindo 45 graus do angulo achado com atan2() e fazer o loop ate completar 90 graus
		// Tava dando erro no loop pq a variavel angulo que checava o fim do loop era a mesma que incrementava, entao ficava infinito
		 for(float anguloLoop = angulo - (PI/4); anguloLoop < angulo + (PI/4); anguloLoop += 0.5)
		{
			// Calcula o seno e cosseno pra cada angulo do incremento do loop
			// olc::vf2d collisionPos = Collision(ray, map);
			// float length = (collisionPos - ray.origin).mag();
			// Horizontal
			float nearestHorizontaly;
			float nearestHorizontalx;
			if(sin(anguloLoop) > 0){
				nearestHorizontaly = map.cellSize - (player.position.y - floorf(player.position.y / map.cellSize) * map.cellSize);
			}else {
				nearestHorizontaly = player.position.y - floorf(player.position.y / map.cellSize) * map.cellSize;
			}
			nearestHorizontalx = nearestHorizontaly / tan(anguloLoop);
			olc::vf2d stepHorizontal (player.position.x, player.position.y);
			int KeyH = 0;
			if(map[(int)(nearestHorizontalx / map.cellSize)][(int)(nearestHorizontaly / map.cellSize)] == 1){
				stepHorizontal.x += nearestHorizontalx;
				stepHorizontal.y += nearestHorizontaly;
				KeyH = 1;
			}
			olc::vf2d nextHorizontal;
			nextHorizontal.y = map.cellSize;
			nextHorizontal.x = nextHorizontal.y / tan(anguloLoop);
			while(stepHorizontal.x < map.width && stepHorizontal.y < map.heigth && stepHorizontal.x > 0 && stepHorizontal.y > 0){
				if(map[(int)(stepHorizontal.x / map.cellSize)][(int)(stepHorizontal.y / map.cellSize)] == 1){
					break;
				}
				stepHorizontal.x += nextHorizontal.x;
				stepHorizontal.y += nextHorizontal.y; 
			}
			// Vertical
			olc::vf2d nearestVertical;
			if(cos(anguloLoop) > 0){
				nearestVertical.x = map.cellSize - (player.position.x - floorf(player.position.x / map.cellSize) * map.cellSize);
			} else{
				nearestVertical.x = player.position.x - floorf(player.position.x / map.cellSize) * map.cellSize;
			}
			
			nearestVertical.y = nearestVertical.x * tan(anguloLoop);
			olc::vf2d stepVertical(player.position.x, player.position.y);
			int KeyV = 0;
			if(map[(int)(nearestVertical.x / map.cellSize)][(int)(nearestVertical.y / map.cellSize)] == 1){
				stepVertical.x += nearestVertical.x;
				stepVertical.y += nearestVertical.y;
				KeyV = 1;
			}
			olc::vf2d nextVertical;
			nextVertical.x = map.cellSize;
			nextVertical.y = nextVertical.x / tan(anguloLoop);
			while(stepVertical.x < map.width && stepVertical.y < map.heigth && stepVertical.x > 0 && stepVertical.y > 0){
				if(map[(int)(stepVertical.x / map.cellSize)][(int)(stepVertical.y / map.cellSize)] == 1){
					break;
				}
				stepVertical.x += nextVertical.x;
				stepVertical.y += nextVertical.y;
			}
			float distH = (stepHorizontal - player.position).mag();
			float distV = (stepVertical - player.position).mag();
			float distance = 0;
			if(distH < distV){
				distance = distH;
			}else {
				distance = distV;
			}
			olc::vf2d dir(cos(anguloLoop), sin(anguloLoop));
			Ray ray(player.position, dir);

			olc::vf2d finalPosition = ray.origin + ray.direction * distance;

			DrawLine(player.position.x, player.position.y, finalPosition.x, finalPosition.y, olc::YELLOW);
			anguloLoop = 3222;
		}

		if (GetKey(olc::W).bHeld) player.position.y -= player.speed * fElapsedTime;
    	if (GetKey(olc::S).bHeld) player.position.y += player.speed * fElapsedTime;
   		if (GetKey(olc::A).bHeld) player.position.x -= player.speed * fElapsedTime;
   		if (GetKey(olc::D).bHeld) player.position.x += player.speed * fElapsedTime;
		player.drawPlayer(this);

		return true;
	}
};

int main(int argc, char** argv)
{
    RayCaster application;
    if (application.Construct(928, 928, 1, 1))
    {
        application.Start();
    }

    return 0;
}
