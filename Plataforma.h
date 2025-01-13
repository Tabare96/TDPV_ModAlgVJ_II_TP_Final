#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Plataforma
{
public:
	Plataforma(b2World* mundo, float posX, float posY, float width, float height);
	void Dibujar(sf::RenderWindow& ventana);
	b2Body* GetBody();

private:
	b2Body* cuerpo;
	b2BodyDef cuerpoDef;
	b2Fixture* fixture;
	b2FixtureDef fixtureDef;

	sf::RectangleShape figura;
	sf::Sprite sprite;
	sf::Texture textura;
};
