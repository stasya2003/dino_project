#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include < ctime>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


using namespace sf;

int ground = 370;  // координата отвечает за то, чтобы динозавр не падал в этом месте 

class Player    //создаём класс
{
public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float curFrame;
	int a;

	Player(Texture& image)
	{
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(0, 0, 90, 95));

		dx = dy = 0;
		curFrame = 0;
		a = 0;
	}

	void update(float time)
	{
		rect.left += dx * time; //координата х верхнего левого угла 

		if (!onGround)
			dy = dy + 0.0005 * time;

		rect.top += dy * time;    // координата у верхнего левого угла 

		if (rect.left == 0)
			rect.left = 100;
		if (rect.top == 0)      
			rect.top = 370;

		onGround = false;

		if (rect.top > ground)
		{
			rect.top = ground;     
			dy = 0;

			onGround = true;
		}

		if (dy == 0)
		{
			if (a == 0) 
			{
				curFrame += 0.0005;
				if (curFrame > 1 && curFrame < 1.95)
					curFrame = 1.95;
				if (curFrame > 2)
					curFrame -= 2;
			}

			else if (a == 1)
			{
				if (curFrame < 2)
					curFrame = 2;

				curFrame += 0.007;
				if (curFrame > 4)
					curFrame -= 2;
			}

			else if (a == 2)
				curFrame = 4;

			sprite.setTextureRect(IntRect(90 * int(curFrame), 0, 90, 95));
		}

		sprite.setPosition(rect.left, rect.top);

		dx = 0;
	}
};

int main() {
	RenderWindow window(VideoMode(1000, 500), "Dinosaur!");

	Texture P;    // картинка пола
	P.loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/pol.png");
	Sprite Pol(P);
	Pol.scale(0.42, 1);   // меняем масштаб
	Pol.setPosition(0, 450);   //меняем расположение картинки, чтобы пол был не посередине 

	Texture D;  //картинка персонажа
	D.loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Din.png");
	Player p(D);

	Texture C[6];  
	Sprite Cact[6];
	C[0].loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cact/1.png");
	C[1].loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cact/2.png");
	C[2].loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cact/3.png");
	C[3].loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cact/4.png");
	C[4].loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cact/5.png");
	C[5].loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cact/6.png");
	for (int i = 0; i < 6; i++) 
	{
		Cact[i].setTexture(C[i]);

		if (i < 3)
			Cact[i].setPosition(1000, 395);
		if (i > 2)
			Cact[i].setPosition(1000, 370);
	}
	srand(NULL(time));
	int cit = rand() % 6 + 1;
	int b = 0;

	Texture Pt;
	Pt.loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Ptic.png");
	Sprite Ptic(Pt);
	Ptic.setTextureRect(IntRect(0, 0, 93, 80));
	int pt = rand() % 2 + 1;
	Ptic.setPosition(1000, 380 - 100 * (pt - 1));
	float Fp = 0;

	bool play = false;
	bool go = false;
	Clock clock;

	Texture O;
	O.loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/GameOver.png");
	Sprite Over(O);
	Over.setPosition(1000, 0);

	Texture N;
	N.loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Naz.png");
	Sprite Naz(N);
	Naz.setPosition(1000, 0);

	Texture Cf;
	Cf.loadFromFile("C:/Users/Balas/source/repos/dinosaur/images/Cifr.png");
	Sprite Cifr[5];
	float cr[5] = { 0, 0, 0, 0, 0 };
	for (int i = 0; i < 5; i++) 
	{
		Cifr[i].setTexture(Cf);
		Cifr[i].setTextureRect(IntRect(0, 0, 20, 24));
		Cifr[i].setPosition(950 - 25 * i, 2);
	}

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))   // если произошло нажатие на пробел
			if (p.onGround)            //если динозавр находится на земле
			{
				if (p.a < 2)
				{
					p.dy = -0.4;
					p.onGround = false;

					p.sprite.setTextureRect(IntRect(180, 0, 90, 95));
					p.a = 1;
				}

				else if (p.a == 2) 
				{
					p.a = 1;

					for (int i = 0; i < 6; i++)
					{
						if (i < 3)
							Cact[i].setPosition(1000, 395);
						if (i > 2)
							Cact[i].setPosition(1000, 370);
					}
					cit = rand() % 6 + 1;
					pt = rand() % 2 + 1;
					Ptic.setPosition(1000, 380 - 100 * (pt - 1));

					b = 0;

					Over.setPosition(1000, 0); 
					Naz.setPosition(1000, 0);    

					go = false;

					for (int i = 0; i < 5; i++)
					{
						cr[i] = 0;

						Cifr[i].setTextureRect(IntRect(0, 0, 20, 24));
					}
				}
			}

		if (p.a == 1 && p.onGround == true) //если динозавр бегает и находится на земле, т.е. не прыгает 
			play = true;

		for (int i = 0; i < 6; i++)
			if (p.sprite.getGlobalBounds().intersects(Cact[i].getGlobalBounds()))
				go = true;

		if (p.sprite.getGlobalBounds().intersects(Ptic.getGlobalBounds()))
			go = true;

		if (play)
		{
			if (b < 10)
			{
				Cact[cit - 1].move(-0.35 * time, 0);

				Vector2f ct[6];
				for (int i = 0; i < 6; i++)
				{
					ct[i] = Cact[i].getPosition();

					if (ct[i].x < -100)
					{
						if (i < 3)
							Cact[i].setPosition(1000, 395);
						if (i > 2)
							Cact[i].setPosition(1000, 370);

						cit = rand() % 6 + 1;

						b++;
					}
				}
			}

			else if (b == 10) 
			{
				Ptic.move(-0.2 * time, 0);

				Vector2f pit = Ptic.getPosition();
				if (pit.x < -100)
				{
					pt = rand() % 2 + 1;

					Ptic.setPosition(1000, 380 - 100 * (pt - 1));

					b = 0;
				}
			}

			cr[0] += 0.005;
			if (cr[0] > 10)
			{
				cr[0] -= 10;

				cr[1]++;
				if (cr[1] > 9)
				{
					cr[1] -= 10;

					cr[2]++;
					if (cr[2] > 9) 
					{
						cr[2] -= 10;

						cr[3]++;
						if (cr[3] > 9) 
						{
							cr[3] -= 10;

							cr[4]++;
							if (cr[4] > 9)
								cr[4] -= 10;

							Cifr[4].setTextureRect(IntRect(20 * int(cr[4]), 0, 20, 24));
						}

						Cifr[3].setTextureRect(IntRect(20 * int(cr[3]), 0, 20, 24));
					}

					Cifr[2].setTextureRect(IntRect(20 * int(cr[2]), 0, 20, 24));
				}

				Cifr[1].setTextureRect(IntRect(20 * int(cr[1]), 0, 20, 24));
			}

			Cifr[0].setTextureRect(IntRect(20 * int(cr[0]), 0, 20, 24));
		}

		if (go)
		{
			p.a = 2;

			play = false;

			Over.setPosition(300, 200);
			Naz.setPosition(450, 250);
		}

		Fp += 0.0025;
		if (Fp > 2)
			Fp -= 2;
		Ptic.setTextureRect(IntRect(93 * int(Fp), 0, 93, 80));

		p.update(time);
		window.clear(Color::White);
		window.draw(Pol);
		window.draw(p.sprite);
		for (int i = 0; i < 6; i++)
			window.draw(Cact[i]);
		window.draw(Ptic);
		window.draw(Over);
		window.draw(Naz);
		for (int i = 0; i < 5; i++)
			window.draw(Cifr[i]);
		window.display();
	}

	return 0;
}