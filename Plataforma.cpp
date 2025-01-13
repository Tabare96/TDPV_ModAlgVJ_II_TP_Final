#include "Plataforma.h"

Plataforma::Plataforma(b2World* mundo, float posX, float posY, float width, float height)
{
	// Define el cuerpo
	cuerpoDef.type = b2_staticBody;
	cuerpoDef.position.Set(posX, posY);
	cuerpo = mundo->CreateBody(&cuerpoDef);

	// Define la forma
	b2PolygonShape shape;
	shape.SetAsBox(width / 2.0f, height / 2.0f);

	// Configura las propiedades físicas
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	fixture = cuerpo->CreateFixture(&fixtureDef);

	textura.loadFromFile("viga.png");
	sprite.setTexture(textura);
	sprite.setOrigin(textura.getSize().x / 2.0f, textura.getSize().y / 2.0f);
	sprite.setPosition(posX, posY);
	sprite.setScale(width / textura.getSize().x, height / textura.getSize().y);
}

void Plataforma::Dibujar(sf::RenderWindow& ventana) {
	sprite.setPosition(cuerpo->GetPosition().x, cuerpo->GetPosition().y);
	sprite.setRotation(cuerpo->GetAngle() * 180.0f / 3.14159265f);
	ventana.draw(sprite);
}

b2Body* Plataforma::GetBody() {
	return cuerpo;
}
