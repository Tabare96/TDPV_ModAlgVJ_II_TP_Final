#pragma once
#include "Actor.h"

class Ragdoll
{
public:
	Ragdoll(Vector2f posicion, b2World& mundo1);	// inicializa un Ragdoll en una posición dada dentro de un mundo físico.
	void Dibujar(RenderWindow& ventana);			// Dibuja las partes del Ragdoll en la ventana proporcionada.
	void AplicarFuerza(Vector2f posicion_m);		// Aplica una fuerza a todas las partes del Ragdoll hacia una posición específica.

	float Rad2Deg(float radianes);

	b2Body* GetCuerpo(int index);					// Obtiene el cuerpo físico de una parte específica del Ragdoll.

	bool EstaEnMovimiento();
private:
	RectangleShape* fig_rag[6];
	Actor* act_rag[6];

	//Resortes
	b2DistanceJoint* jnt_rag[5];
	b2DistanceJointDef jntDef_rag[5];

	//Cuerpos físicos que componen el Ragdoll en Box2D
	b2Body* bdy_rag[6];
	b2BodyDef bdyDef_rag[6];
	//propiedades físicas
	b2Fixture* fix_rag[6];
	b2FixtureDef fixDef_rag[6];


	Texture texturaCabeza,
		texturaPecho,
		texturaBrazo,
		texturaPierna;

	Sprite spriteCabeza,
		spritePecho,
		spriteBrazoDerecho,
		spriteBrazoIzquierdo,
		spritePiernaDerecha,
		spritePiernaIzquierda;

};
