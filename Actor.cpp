#include "Actor.h"

Actor::Actor(b2Body* cuerpo, RectangleShape* figura) : bdy_actor(cuerpo), fig_actor(figura)
{
	posicion = bdy_actor->GetPosition();

	dimensiones.lowerBound = b2Vec2(FLT_MAX, -FLT_MAX);
	dimensiones.upperBound = b2Vec2(-FLT_MAX, FLT_MAX);

	for (b2Fixture* i = bdy_actor->GetFixtureList(); i != NULL; i = i->GetNext())
	{
		dimensiones = i->GetAABB(0);
	}

	fig_actor->setSize({ dimensiones.GetExtents().x * 2, dimensiones.GetExtents().y * 2 });

	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);

	fig_actor->setPosition(posicion.x, posicion.y);
}

void Actor::Dibujar(RenderWindow& ventana)
{
	posicion = bdy_actor->GetPosition();

	fig_actor->setPosition(posicion.x, posicion.y);

	fig_actor->setRotation(Rad2Deg(bdy_actor->GetAngle()));

	ventana.draw(*fig_actor);
}

float Actor::Rad2Deg(float radianes)
{
	return radianes * 180.0f / 3.14;
}
