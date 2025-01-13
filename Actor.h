#pragma once
#include "SFML\Graphics.hpp"
#include "box2d/box2d.h"

using namespace sf;

class Actor
{
public:
	Actor(b2Body* cuerpo, RectangleShape* figura);	// Psocia un cuerpo físico de Box2D con su representación gráfica en SFML
	void Dibujar(RenderWindow& ventana);
	float Rad2Deg(float radianes);					// Para convertir radianes a grados

private:
	b2Body* bdy_actor;
	RectangleShape* fig_actor;

	b2AABB dimensiones;
	b2Vec2 posicion;
};