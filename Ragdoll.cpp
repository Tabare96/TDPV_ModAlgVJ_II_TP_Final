#include "Ragdoll.h"

Ragdoll::Ragdoll(Vector2f posicion, b2World& mundo1)
{
	//Posiciona las partes del ragdoll
	bdyDef_rag[0].position = b2Vec2(posicion.x, posicion.y + 1.f);			// Cabeza (antes 0.1f)
	bdyDef_rag[1].position = b2Vec2(posicion.x, posicion.y + 6.5f);			// Pecho (antes 0.65f)
	bdyDef_rag[2].position = b2Vec2(posicion.x + 3.2f, posicion.y + 5.0f);  // Brazo derecho (antes 0.32f)
	bdyDef_rag[3].position = b2Vec2(posicion.x - 3.2f, posicion.y + 5.0f);  // Brazo izquierdo (antes -0.32f)
	bdyDef_rag[4].position = b2Vec2(posicion.x + 0.9f, posicion.y + 15.0f); // Pierna derecha (antes 0.09f)
	bdyDef_rag[5].position = b2Vec2(posicion.x - 0.9f, posicion.y + 15.0f); // Pierna izquierda (antes -0.09f)

	//Cuerpo Ragdollico
	for (int i = 0; i < 6; i++)
	{
		bdyDef_rag[i].type = b2_dynamicBody;
		bdy_rag[i] = mundo1.CreateBody(&bdyDef_rag[i]);
	}

	b2PolygonShape shp_rag[6];
	shp_rag[0].SetAsBox(1.0f, 1.0f);  // Cabeza (antes 0.1f, 0.1f)
	shp_rag[1].SetAsBox(2.0f, 4.0f);  // Pecho (antes 0.2f, 0.4f)
	shp_rag[2].SetAsBox(0.7f, 3.0f);  // Brazo derecho (antes 0.07f, 0.3f)
	shp_rag[3].SetAsBox(0.7f, 3.0f);  // Brazo izquierdo (antes 0.07f, 0.3f)
	shp_rag[4].SetAsBox(0.7f, 4.0f);  // Pierna derecha (antes 0.07f, 0.4f)
	shp_rag[5].SetAsBox(0.7f, 4.0f);  // Pierna izquierda (antes 0.07f, 0.4f)

	for (int i = 0; i < 6; i++)
	{
		fixDef_rag[i].shape = &shp_rag[i];
		fixDef_rag[i].density = 0.2f;
		fixDef_rag[i].friction = 3.f;
		fixDef_rag[i].restitution = 0.7f;
		fix_rag[i] = bdy_rag[i]->CreateFixture(&fixDef_rag[i]);
	}

	//Resortica
	jntDef_rag[0].Initialize(bdy_rag[0], bdy_rag[1], b2Vec2(bdy_rag[0]->GetPosition().x, bdy_rag[0]->GetPosition().y + 0.8), b2Vec2(bdy_rag[1]->GetPosition().x, bdy_rag[1]->GetPosition().y - 3.8));
	jntDef_rag[1].Initialize(bdy_rag[1], bdy_rag[2], b2Vec2(bdy_rag[1]->GetPosition().x + 1.8, bdy_rag[1]->GetPosition().y - 3.8), b2Vec2(bdy_rag[2]->GetPosition().x - 0.5, bdy_rag[2]->GetPosition().y - 2.8));
	jntDef_rag[2].Initialize(bdy_rag[1], bdy_rag[3], b2Vec2(bdy_rag[1]->GetPosition().x - 1.8, bdy_rag[3]->GetPosition().y - 3.8), b2Vec2(bdy_rag[3]->GetPosition().x + 0.5, bdy_rag[3]->GetPosition().y - 2.8));
	jntDef_rag[3].Initialize(bdy_rag[1], bdy_rag[4], b2Vec2(bdy_rag[1]->GetPosition().x + 0.9, bdy_rag[1]->GetPosition().y + 3.8), b2Vec2(bdy_rag[4]->GetPosition().x, bdy_rag[4]->GetPosition().y - 3.8));
	jntDef_rag[4].Initialize(bdy_rag[1], bdy_rag[5], b2Vec2(bdy_rag[1]->GetPosition().x + 0.9, bdy_rag[1]->GetPosition().y + 3.8), b2Vec2(bdy_rag[5]->GetPosition().x, bdy_rag[5]->GetPosition().y - 3.8));

	for (int i = 0; i < 5; i++)
	{
		jntDef_rag[i].damping = 0.3f;
		jntDef_rag[i].stiffness = 4.f;
		jntDef_rag[i].collideConnected = true;
		jntDef_rag[i].length = 0.025f;
		jnt_rag[i] = (b2DistanceJoint*)mundo1.CreateJoint(&jntDef_rag[i]);

	}

	// Carga texturas
	texturaCabeza.loadFromFile("cabeza.png");
	texturaPecho.loadFromFile("cuerpo.png");
	texturaBrazo.loadFromFile("brazo.png");
	texturaPierna.loadFromFile("pierna.png");

	spriteCabeza.setTexture(texturaCabeza);
	spritePecho.setTexture(texturaPecho);
	spriteBrazoDerecho.setTexture(texturaBrazo);
	spriteBrazoIzquierdo.setTexture(texturaBrazo);
	spritePiernaDerecha.setTexture(texturaPierna);
	spritePiernaIzquierda.setTexture(texturaPierna);

	//posiciona las texturas
	spriteCabeza.setOrigin(texturaCabeza.getSize().x / 2, texturaCabeza.getSize().y / 2);
	spritePecho.setOrigin(texturaPecho.getSize().x / 2, texturaPecho.getSize().y / 2);
	spriteBrazoDerecho.setOrigin(texturaBrazo.getSize().x / 2, texturaBrazo.getSize().y / 2);
	spriteBrazoIzquierdo.setOrigin(texturaBrazo.getSize().x / 2, texturaBrazo.getSize().y / 2);
	spritePiernaDerecha.setOrigin(texturaPierna.getSize().x / 2, texturaPierna.getSize().y / 2);
	spritePiernaIzquierda.setOrigin(texturaPierna.getSize().x / 2, texturaPierna.getSize().y / 2);

	spriteCabeza.setScale(0.1, 0.1);
	spritePecho.setScale(0.1, 0.1);
	spriteBrazoDerecho.setScale(0.1, 0.1);
	spriteBrazoIzquierdo.setScale(0.1, 0.1);
	spritePiernaDerecha.setScale(0.1, 0.1);
	spritePiernaIzquierda.setScale(0.1, 0.1);

	// Inicia imagen
	for (int i = 0; i < 6; i++)
	{
		fig_rag[i] = new RectangleShape;
	}
}

void Ragdoll::Dibujar(RenderWindow& ventana1)
{
	// Actualiza posiciones y rotaciones de los sprites según los cuerpos físicos
	spriteCabeza.setPosition(bdy_rag[0]->GetPosition().x, bdy_rag[0]->GetPosition().y - 5);
	spriteCabeza.setRotation(bdy_rag[0]->GetAngle() * 180 / b2_pi);

	spritePecho.setPosition(bdy_rag[1]->GetPosition().x, bdy_rag[1]->GetPosition().y);
	spritePecho.setRotation(bdy_rag[1]->GetAngle() * 180 / b2_pi);

	spriteBrazoDerecho.setPosition(bdy_rag[2]->GetPosition().x + 4, bdy_rag[2]->GetPosition().y);
	spriteBrazoDerecho.setRotation(bdy_rag[2]->GetAngle() * 180 / b2_pi);

	spriteBrazoIzquierdo.setPosition(bdy_rag[3]->GetPosition().x - 4, bdy_rag[3]->GetPosition().y);
	spriteBrazoIzquierdo.setRotation(bdy_rag[3]->GetAngle() * 180 / b2_pi);

	spritePiernaDerecha.setPosition(bdy_rag[4]->GetPosition().x, bdy_rag[4]->GetPosition().y);
	spritePiernaDerecha.setRotation(bdy_rag[4]->GetAngle() * 180 / b2_pi);

	spritePiernaIzquierda.setPosition(bdy_rag[5]->GetPosition().x, bdy_rag[5]->GetPosition().y);
	spritePiernaIzquierda.setRotation(bdy_rag[5]->GetAngle() * 180 / b2_pi);

	// Dibujar sprites
	ventana1.draw(spriteCabeza);
	ventana1.draw(spritePecho);
	ventana1.draw(spriteBrazoDerecho);
	ventana1.draw(spriteBrazoIzquierdo);
	ventana1.draw(spritePiernaDerecha);
	ventana1.draw(spritePiernaIzquierda);
}

void Ragdoll::AplicarFuerza(Vector2f posicion_m)
{
	for (int i = 0; i < 6; i++)
	{
		bdy_rag[i]->ApplyForceToCenter(b2Vec2(posicion_m.x * 30, posicion_m.y * 30), false);
	}
}

float Ragdoll::Rad2Deg(float radianes)
{
	return radianes * 180 / 3.14;
}

b2Body* Ragdoll::GetCuerpo(int index)
{
	return bdy_rag[index]; // Devuelve el cuerpo en la posición especificada
}

bool Ragdoll::EstaEnMovimiento()
{
	for (int i = 0; i < 6; i++) // Para las 6 partes del ragdoll
	{
		b2Body* cuerpo = GetCuerpo(i); // Obtiene cada parte del ragdoll
		if (cuerpo->GetLinearVelocity().Length() > 2.f) // Verifica si se está moviendo
		{
			return true;
		}
	}
	return false;
}
