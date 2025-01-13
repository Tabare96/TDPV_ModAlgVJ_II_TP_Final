#include "Caja.h"

Caja::Caja(b2World* mundo, float posX, float posY, float width, float height) : golpeada(false)
{
	//Cuerpo
	cuerpoDef.type = b2_dynamicBody;
	cuerpoDef.position.Set(posX, posY);
	cuerpo = mundo->CreateBody(&cuerpoDef);

	//Forma
	b2PolygonShape shape;
	shape.SetAsBox(width / 2.0f, height / 2.0f);

	// Propiedades físicas
	fixtureDef.shape = &shape;
	fixtureDef.density = 0.3f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.3f;

	fixture = cuerpo->CreateFixture(&fixtureDef);

	// Carga de textura y sprite
	textura.loadFromFile("caja.png");
	sprite.setTexture(textura);
	sprite.setOrigin(textura.getSize().x / 2.0f, textura.getSize().y / 2.0f);
	sprite.setPosition(posX, posY);
	sprite.setScale(width / textura.getSize().x, height / textura.getSize().y);
}

void Caja::Dibujar(sf::RenderWindow& ventana)
{
	sprite.setPosition(cuerpo->GetPosition().x, cuerpo->GetPosition().y);	// Actualiza la posición del sprite
	sprite.setRotation(cuerpo->GetAngle() * 180.0f / 3.14159265f);			// Convierte a grados
	ventana.draw(sprite);
}

b2Body* Caja::GetBody()
{
	return cuerpo;
}

bool Caja::haSidoGolpeada()
{
	return golpeada;
}

void Caja::MarcarComoGolpeada()
{
	golpeada = true;
}
