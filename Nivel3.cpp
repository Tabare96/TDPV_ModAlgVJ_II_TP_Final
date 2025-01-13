#include "Nivel3.h"
#include <cmath>
#include <iostream>


Nivel3::Nivel3(Vector2i resolucion, const std::string& titulo) : NivelBase()
{
	fps = 120;
	tiempoFrame = 1 / 120.f;
	tiempo2 = 0;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	int limiteRagdolls = 4;
	this->ragdollsRestantes = limiteRagdolls;

	ConfigurarTextos("cajas golpeadas 0/3", limiteRagdolls);

	todasCajasGolpeadas = false;
	derrota = false;

	SetCamera();
	IniciarFisica();
	CargarImagenes();

	evento1 = new Event;
	reloj1 = new Clock;
	tiempo1 = new Time;

	act_suelo = new Actor(bdy_suelo, fig_suelo);
	act_cannon = new Actor(bdy_cannon, fig_cannon);

	ragdolls.clear();

	mundo1->SetContactListener(this);

	cajasGolpeadas = 0;

	GameLoop(3);
}

void Nivel3::IniciarFisica()
{
	mundo1 = new b2World(b2Vec2(0.f, 99.f));

	bdyDef_suelo.type = b2_staticBody;
	bdyDef_suelo.position = b2Vec2(52.f, 240.f);

	bdy_suelo = mundo1->CreateBody(&bdyDef_suelo);
	b2PolygonShape shp_suelo;
	shp_suelo.SetAsBox(150.f, 5.f);

	fixDef_suelo.shape = &shp_suelo;
	fixDef_suelo.restitution = 0.f;
	fixDef_suelo.friction = 0.3f;
	fixDef_suelo.density = 1.f;

	fix_suelo = bdy_suelo->CreateFixture(&fixDef_suelo);

	plataformas.push_back(new Plataforma(mundo1, 210.f, 180.f, 7.f, 480.f));
	plataformas.push_back(new Plataforma(mundo1, 47.f, -80.f, 400.f, 8.f));

	plataformas.push_back(new Plataforma(mundo1, 40.f, 220.f, 48.f, 7.f));
	plataformas.push_back(new Plataforma(mundo1, 110.f, 180.f, 48.f, 7.f));
	plataformas.push_back(new Plataforma(mundo1, 180.f, 120.f, 48.f, 7.f));

	cajas.push_back(new Caja(mundo1, 40.f, 180.f, 20.f, 20.f));
	cajas.push_back(new Caja(mundo1, 110.f, 140.f, 20.f, 20.f));
	cajas.push_back(new Caja(mundo1, 180.f, 80.f, 20.f, 20.f));

	bdyDef_cannon.type = b2_staticBody;
	bdyDef_cannon.position = b2Vec2(-70.f, 208.f);

	bdy_cannon = mundo1->CreateBody(&bdyDef_cannon);
	b2PolygonShape shp_arma;
	shp_arma.SetAsBox(8.f, 3.f);

	fixDef_cannon.shape = &shp_arma;
	fixDef_cannon.density = 1.f;
	fixDef_cannon.restitution = 0.1f;
	fixDef_cannon.friction = 0.3f;

	fix_cannon = bdy_cannon->CreateFixture(&fixDef_cannon);
}

void Nivel3::CargarImagenes()
{
	fig_suelo = new RectangleShape;
	fig_cannon = new RectangleShape;

	txt_fondo = new Texture();
	txt_suelo = new Texture();
	txt_cannon = new Texture();
	txt_baseCannon = new Texture();
	txt_caja = new Texture();

	txt_fondo->loadFromFile("fondo.png");
	txt_suelo->loadFromFile("suelo.png");
	txt_cannon->loadFromFile("cañon.png");
	txt_baseCannon->loadFromFile("baseCañon.png");
	txt_caja->loadFromFile("caja.png");

	spr_fondo = new Sprite();
	spr_suelo = new Sprite();
	spr_cannon = new Sprite();
	spr_baseCannon = new Sprite();
	spr_caja = new Sprite();

	spr_fondo->setTexture(*txt_fondo);
	spr_suelo->setTexture(*txt_suelo);
	spr_cannon->setTexture(*txt_cannon);
	spr_baseCannon->setTexture(*txt_baseCannon);
	spr_caja->setTexture(*txt_caja);

	spr_fondo->setOrigin(txt_fondo->getSize().x / 2.0f, txt_fondo->getSize().y / 2.0f);
	spr_suelo->setOrigin(spr_suelo->getTexture()->getSize().x / 2, spr_suelo->getTexture()->getSize().y / 2);
	spr_cannon->setOrigin(spr_cannon->getTexture()->getSize().x / 2, spr_cannon->getTexture()->getSize().y / 2);
	spr_baseCannon->setOrigin(spr_baseCannon->getTexture()->getSize().x / 2, spr_baseCannon->getTexture()->getSize().y / 2 - 50);
	spr_caja->setOrigin(spr_caja->getTexture()->getSize().x / 2, spr_caja->getTexture()->getSize().y / 2);

	spr_fondo->setPosition(camara1->getCenter().x, camara1->getCenter().y);
	spr_fondo->setScale(0.375f, 0.5f);

	spr_suelo->setPosition(bdy_suelo->GetPosition().x, bdy_suelo->GetPosition().y);
	spr_suelo->setScale(0.4f, 0.3f);

	spr_cannon->setPosition(bdy_cannon->GetPosition().x, bdy_cannon->GetPosition().y);
	spr_cannon->setScale(0.05f, 0.05f);

	spr_baseCannon->setPosition(bdy_cannon->GetPosition().x, bdy_cannon->GetPosition().y);
	spr_baseCannon->setScale(0.2f, 0.2f);

	fig_cannon->setFillColor(Color::White);
}

void Nivel3::Dibujar()
{
	ventana1->draw(*spr_fondo);

	ventana1->draw(*spr_suelo);

	ventana1->draw(*spr_cannon);

	ventana1->draw(*spr_baseCannon);

	for (Plataforma*& plataforma : plataformas)
	{
		plataforma->Dibujar(*ventana1);
	}

	for (Caja*& caja : cajas)
	{
		caja->Dibujar(*ventana1);
	}

	for (Ragdoll* ragdoll : ragdolls)
	{
		ragdoll->Dibujar(*ventana1);
	}


	ventana1->draw(textoRagdollsRestantes);
	ventana1->draw(textoCajasGolpeadas);

	if (todasCajasGolpeadas || derrota)
	{
		ventana1->draw(textoVictoriaDerrota);
	}
}

void Nivel3::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	for (Caja* caja : cajas)
	{
		if ((fixtureA->GetBody() == caja->GetBody() || fixtureB->GetBody() == caja->GetBody()) && !caja->haSidoGolpeada())
		{
			bool colisionConRagdoll = false;
			for (Ragdoll* ragdoll : ragdolls)
			{
				for (int i = 0; i < 6; i++)
				{
					if (fixtureA->GetBody() == ragdoll->GetCuerpo(i) || fixtureB->GetBody() == ragdoll->GetCuerpo(i))
					{
						colisionConRagdoll = true;
						break;
					}
				}
				if (colisionConRagdoll) break;
			}

			if (colisionConRagdoll)
			{
				caja->MarcarComoGolpeada();
				cajasGolpeadas++;

				textoCajasGolpeadas.setString("cajas golpeadas " + std::to_string(cajasGolpeadas) + "/3");

				if (cajasGolpeadas == 3)
				{
					todasCajasGolpeadas = true;
				}

				break;
			}
		}
	}
}
