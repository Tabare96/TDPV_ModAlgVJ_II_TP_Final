#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;
class Caja
{
public:
	Caja(b2World* mundo, float posX, float posY, float width, float height);

	void Dibujar(sf::RenderWindow& ventana);

	b2Body* GetBody();

	bool haSidoGolpeada();
	void MarcarComoGolpeada();

private:
	b2Body* cuerpo;
	b2BodyDef cuerpoDef;
	b2Fixture* fixture;
	b2FixtureDef fixtureDef;

	RectangleShape figura;
	Sprite sprite;
	Texture textura;

	bool golpeada;
};
