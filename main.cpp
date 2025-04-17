#define OLC_PGE_APPLICATION

#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "olcPixelGameEngine.h"
#define PI 3.141592653589793f

// g++ -fopenmp main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17 -O3 -o main

class RayCaster : public olc::PixelGameEngine
{
public:

    int x = 0;
    int y = 0;

	struct Player{
		float posicaoX, posicaoY;
		float speed;
		float raio;
		// Construtor
		Player(float a, float b, float c, float d){
			posicaoX = a;
			posicaoY = b;
			speed = c;
			raio = d;
		}

		void drawPlayer(olc::PixelGameEngine* ptr){
			ptr->FillCircle(posicaoX, posicaoY, raio, olc::RED);
		}
	};
	Player um = Player(100, 100, 100, 5);

	struct Map{
		int largura, altura;
		int tijolo;
		int stage[8][8] =  {0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 1, 1, 0,
							0, 0, 0, 0, 0, 1, 1, 0,
							0, 0, 0, 0, 0, 1, 1, 0,
							0, 1, 0, 0, 0, 0, 0, 0,
							0, 1, 0, 0, 0, 0, 0, 0,};

		Map(int a, int b, int c){
			largura = a;
			altura = b;
			tijolo = c;
		}
	};
	Map mapa = Map(8, 8, 64);

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
		// Called once per frame
		Clear(olc::BLACK);
		olc::vi2d pos = GetMousePos();
		// MAPA

		for(int y = 0; y < mapa.altura; y++){
			for(int x = 0; x < mapa.largura; x++){
				if(mapa.stage[y][x] == 1){
					FillRect(x*mapa.tijolo, y*mapa.tijolo, mapa.tijolo, mapa.tijolo, olc::WHITE);
				}
			}
		}
		// RAY
		// Calcula a hipotenusa com a diferença dos eixos X e Y do jogador ate a posicao do mouse
		float hipotenusa = sqrtf(powf((um.posicaoX - pos.x), 2) + powf((um.posicaoY - pos.y), 2));
		// Calcula os seno e cosseno
		float anguloYsin = (pos.y - um.posicaoY)/hipotenusa;
		float anguloXcos = (pos.x - um.posicaoX)/hipotenusa; 
		// Acha o angulo entre jogador e mouse usando a funçao atan2()
		float angulo = atan2f(anguloYsin, anguloXcos);
		// Ideia inicializar o loop subtraindo 45 graus do angulo achado com atan2() e fazer o loop ate completar 90 graus
		// Tava dando erro no loop pq a variavel angulo que checava o fim do loop era a mesma que incrementava, entao ficava infinito
		for(float anguloLoop = angulo - (PI/4); anguloLoop < angulo + (PI/4); anguloLoop += 0.1){ 
			// Calcula o seno e cosseno pra cada angulo do incremento do loop
			float rayX = cos(anguloLoop);
			float rayY = sin(anguloLoop);
			// Calculo para o tamanho dos raios
			float fimX = um.posicaoX + rayX * 500;
			float fimY = um.posicaoY + rayY * 500;
			DrawLine(um.posicaoX, um.posicaoY, fimX, fimY, olc::BLUE);
		}
		DrawLine(um.posicaoX, um.posicaoY, pos.x, pos.y, olc::RED);
		// MOVIMENTAÇAO

		if (GetKey(olc::W).bHeld) um.posicaoY -= um.speed * fElapsedTime;
    	if (GetKey(olc::S).bHeld) um.posicaoY += um.speed * fElapsedTime;
   		if (GetKey(olc::A).bHeld) um.posicaoX -= um.speed * fElapsedTime;
   		if (GetKey(olc::D).bHeld) um.posicaoX += um.speed * fElapsedTime;
		um.drawPlayer(this);

		return true;
	}
};


int main(int argc, char** argv)
{
    std::cout << "Hello World\n";

    RayCaster application;
    if (application.Construct(512, 512, 1, 1))
    {
        application.Start();
    }

    return 0;
}