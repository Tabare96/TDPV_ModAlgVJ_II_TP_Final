#include "Nivel2.h"
#include <cmath>
#include <iostream>


Nivel2::Nivel2(Vector2i resolucion, const std::string& titulo) : NivelBase()
{
	fps = 120;
	tiempoFrame = 1 / 120.f;
	tiempo2 = 0;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	int limiteRagdolls = 4;
	this->ragdollsRestantes = limiteRagdolls;

	ConfigurarTextos("cajas golpeadas 0/1", limiteRagdolls);

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

	GameLoop(1);
}

void Nivel2::IniciarFisica()
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

	plataformas.push_back(new Plataforma(mundo1, 110.f, 180.f, 48.f, 7.f));

	plataformas.push_back(new Plataforma(mundo1, 210.f, 180.f, 7.f, 480.f));
	plataformas.push_back(new Plataforma(mundo1, 47.f, -80.f, 400.f, 8.f));

	cajas.push_back(new Caja(mundo1, 110.f, 140.f, 20.f, 20.f));

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

	//Barra
	bdyDef_barra.type = b2_dynamicBody;
	bdyDef_barra.position.Set(20.f, 150.f); // Posición inicial
	bdy_barra = mundo1->CreateBody(&bdyDef_barra);

	b2PolygonShape shp_barra;
	shp_barra.SetAsBox(35.f, 2.f); // Tamaño de la barra

	fixDef_barra.shape = &shp_barra;
	fixDef_barra.density = 0.1f;
	fixDef_barra.friction = 0.3f;
	fixDef_barra.restitution = 0.1f;

	fix_barra = bdy_barra->CreateFixture(&fixDef_barra);

	// Crea la junta revoluta entre el suelo y la barra
	joint_barra = CreateRevoluteJoint(
		mundo1,
		bdy_suelo,
		b2Vec2(20.f, 150.f),
		bdy_barra,
		0.0f,
		0.0f,
		5.0f,
		100.0f,
		true,
		false
	);

	// Para asegurar que el motor está activo y girando
	joint_barra->EnableMotor(true);
	joint_barra->SetMotorSpeed(5.0f); // Velocidad positiva para girar en sentido horario

	bdy_barra->SetTransform(bdy_barra->GetPosition(), b2_pi / 4); // Ángulo inicial de -45 grados
}

void Nivel2::CargarImagenes()
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

	fig_barra = new RectangleShape(Vector2f(50.f, 4.f)); // Tamaño gráfico (ancho, alto)
	fig_barra->setOrigin(25.f, 2.f);                     // Centro en el punto medio
	fig_barra->setFillColor(Color::Blue);              // Color para visualizar
}

void Nivel2::Dibujar()
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

	fig_barra->setPosition(bdy_barra->GetPosition().x, bdy_barra->GetPosition().y);
	fig_barra->setRotation(Rad2Deg(bdy_barra->GetAngle())); // Rotación en grados
	ventana1->draw(*fig_barra);
}

void Nivel2::BeginContact(b2Contact* contact)
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

				textoCajasGolpeadas.setString("cajas golpeadas " + std::to_string(cajasGolpeadas) + "/1");

				if (cajasGolpeadas == 1)
				{
					todasCajasGolpeadas = true;
				}

				break;
			}
		}
	}
}
