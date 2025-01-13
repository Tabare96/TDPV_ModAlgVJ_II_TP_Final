
#include "NivelBase.h"
#include <iostream>

NivelBase::NivelBase()
{
}

NivelBase::~NivelBase()
{
	for (Ragdoll* ragdoll : ragdolls)
	{
		delete ragdoll;
	}

	ragdolls.clear();
}

void NivelBase::SetCamera()
{
	camara1 = new View({ 5.f, 5.f, }, { 300.f, 300.f });

	camara1->move(47.f, 90.f);

	ventana1->setView(*camara1);
}

void NivelBase::ActualizarPosicionArma()
{
	// Actualiza la posición y rotación del cañón según la posición del mouse
	Vector2i posicion_m = Mouse::getPosition(*ventana1);
	Vector2f posicion_mc = ventana1->mapPixelToCoords(posicion_m);

	// Calcula el ángulo entre el cañón y el mouse en radianes
	float angulo = atan2f(posicion_mc.y - bdy_cannon->GetPosition().y,
		posicion_mc.x - bdy_cannon->GetPosition().x);
	float anguloGrados = Rad2Deg(angulo);

	// Limita el ángulo entre 0 y -90 grados para restringir el movimiento del cañón
	anguloGrados = std::clamp(anguloGrados, -90.f, 0.f);

	angulo = Deg2Rad(anguloGrados);

	// Aplica la nueva rotación al cuerpo físico y al sprite del cañón.
	bdy_cannon->SetTransform(bdy_cannon->GetPosition(), angulo);
	spr_cannon->setRotation(anguloGrados);
}

float NivelBase::Deg2Rad(float grados)
{
	return grados * 3.14 / 180.0f;
}

float NivelBase::Rad2Deg(float radianes)
{
	return radianes * 180.0f / 3.14;
}

Vector2f NivelBase::ObtenerPuntaArma()
{
	float anguloArma = bdy_cannon->GetAngle();
	float longitudArma = 16.f; // Para que el ragdoll salga un poco despegado del cañon

	float puntaX = bdy_cannon->GetPosition().x + longitudArma * cos(anguloArma);
	float puntaY = bdy_cannon->GetPosition().y + longitudArma * sin(anguloArma);

	return Vector2f(puntaX, puntaY);
}

void NivelBase::GameLoop(int cajasTotales)
{
	while (ventana1->isOpen())
	{
		*tiempo1 = reloj1->getElapsedTime();
		if (tiempo2 + tiempoFrame < tiempo1->asSeconds())
		{
			tiempo2 = tiempo1->asSeconds();

			ventana1->clear();

			ProcesarEventos(cajasTotales);
			ActualizarFisica();
			Dibujar();

			if (todasCajasGolpeadas)	// Si se golpearon todas las cajas, muestra el mensaje de victoria y cierra la ventana.
			{
				textoVictoriaDerrota.setString("¡Nivel completado!");
				textoVictoriaDerrota.setFillColor(sf::Color::Green);
				ventana1->draw(textoVictoriaDerrota);
				ventana1->display();
				sf::sleep(sf::seconds(2));
				ventana1->close();
			}

			ventana1->display();
		}
	}
}

void NivelBase::ActualizarFisica()
{
	mundo1->Step(tiempoFrame, 8, 8);
	if (joint_barra)
	{
		joint_barra->SetMotorSpeed(100.0f);
	}
}

void NivelBase::ProcesarEventos(int cajasTotales)
{
	int limiteRagdolls = 4;

	while (ventana1->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
		case Event::Closed:
			exit(0);
			break;

		case Event::MouseButtonPressed:
			if (evento1->mouseButton.button == Mouse::Left && this->ragdollsRestantes > 0)
			{
				Vector2i posicion_m = Mouse::getPosition(*ventana1);
				Vector2f posicion_mc = ventana1->mapPixelToCoords(posicion_m);

				Vector2f puntaArma = ObtenerPuntaArma();

				Ragdoll* nuevoRagdoll = new Ragdoll({ puntaArma.x, puntaArma.y }, *mundo1);
				ragdolls.push_back(nuevoRagdoll);

				this->ragdollsRestantes--;

				textoRagdollsRestantes.setString("ragdolls " + std::to_string(this->ragdollsRestantes) + "/" + std::to_string(limiteRagdolls));

				ComprobarEstadoCajas(cajasTotales); // Verifica si se golpearon suficientes cajas

				Vector2f direccion = { posicion_mc.x - puntaArma.x, posicion_mc.y - puntaArma.y };
				float distancia = sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
				Vector2f direccionNormalizada = { direccion.x / distancia, direccion.y / distancia };

				float fuerzaBase = 10.f;
				float fuerzaMaxima = 5000.f;
				float fuerzaDisparo = std::min(distancia * fuerzaBase, fuerzaMaxima);
				Vector2f fuerzaFinal = { direccionNormalizada.x * fuerzaDisparo, direccionNormalizada.y * fuerzaDisparo };

				nuevoRagdoll->AplicarFuerza(fuerzaFinal);
			}

			if (this->ragdollsRestantes == 0 && !todasCajasGolpeadas)    // Comprueba si el último ragdoll lanzado está en movimiento
			{
				bool ultimoRagdollEnVuelo = false;

				for (Ragdoll* ragdoll : ragdolls)
				{
					if (ragdoll->EstaEnMovimiento())
					{
						ultimoRagdollEnVuelo = true;
						break;
					}
				}

				if (!ultimoRagdollEnVuelo)	// En caso de no quedar ragdolls en movimiento
				{
					derrota = true;
					textoVictoriaDerrota.setString("¡Derrota!");
					textoVictoriaDerrota.setFillColor(sf::Color::Red);
					textoVictoriaDerrota.setPosition(-20.f, 50.f);
					ventana1->draw(textoVictoriaDerrota);
					ventana1->display();
					sf::sleep(sf::seconds(1));
					ventana1->close();

					RenderWindow ventanaFinal(VideoMode(800, 600), "Pantalla Final");
					PantallaFinal pantallaFinal(&ventanaFinal);
					pantallaFinal.MostrarPantallaFinal();

					exit(0);
				}
			}
			break;
		}
	}

	ActualizarPosicionArma();
	ventana1->draw(textoRagdollsRestantes);

	if (todasCajasGolpeadas || derrota)
	{
		ventana1->draw(textoVictoriaDerrota);
	}
}

void NivelBase::ComprobarEstadoCajas(int cajasRequeridas)
{
	int cajasGolpeadas = 0;
	for (Caja* caja : cajas)
	{
		if (caja->haSidoGolpeada())
		{
			cajasGolpeadas++;
		}
	}

	if (cajasGolpeadas == cajasRequeridas)
	{
		todasCajasGolpeadas = true;	// Marca el nivel como completado si se golpearon todas las cajas requeridas
	}
}

bool NivelBase::Ganado() const
{
	return todasCajasGolpeadas;
}

void NivelBase::CargarImagenes()
{
}

void NivelBase::ConfigurarTextos(const std::string& textoInicial, int limiteRagdolls)
{
	if (!fuente.loadFromFile("fuente.ttf"))
	{
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	textoRagdollsRestantes.setFont(fuente);
	textoRagdollsRestantes.setFillColor(sf::Color::Red);
	textoRagdollsRestantes.setString("ragdolls " + std::to_string(limiteRagdolls) + "/" + std::to_string(limiteRagdolls));
	textoRagdollsRestantes.setCharacterSize(20);
	textoRagdollsRestantes.setPosition(-90.f, -50.f);

	textoVictoriaDerrota.setFont(fuente);
	textoVictoriaDerrota.setCharacterSize(35);
	textoVictoriaDerrota.setPosition(-95.f, 50.f);
	textoVictoriaDerrota.setString("");

	textoCajasGolpeadas.setFont(fuente);
	textoCajasGolpeadas.setFillColor(Color::Blue);
	textoCajasGolpeadas.setCharacterSize(20);
	textoCajasGolpeadas.setPosition(-90.f, -30.f);
	textoCajasGolpeadas.setString(textoInicial);
}

