#include "PantallaFinal.h"
#include <iostream>

PantallaFinal::PantallaFinal(RenderWindow* ventana) : ventana(ventana)
{
	if (!fuente.loadFromFile("fuente.ttf"))
	{
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	// Texto "FIN"
	textoFin.setFont(fuente);
	textoFin.setString("FIN");
	textoFin.setCharacterSize(80);
	textoFin.setFillColor(Color::Green);
	textoFin.setPosition(ventana->getSize().x / 2 - 70, ventana->getSize().y / 3);

	// Botón "Salir"
	textoSalir.setFont(fuente);
	textoSalir.setString("Salir");
	textoSalir.setCharacterSize(40);
	textoSalir.setFillColor(Color::Red);
	textoSalir.setPosition(ventana->getSize().x / 2 - 50, ventana->getSize().y / 1.5);
}

void PantallaFinal::MostrarPantallaFinal()
{
	while (ventana->isOpen())
	{
		Event evento;
		while (ventana->pollEvent(evento))
		{
			if (evento.type == Event::Closed)
			{
				ventana->close();
				exit(0); // Salir del programa
			}

			if (evento.type == Event::MouseButtonPressed)
			{
				Vector2i posicionMouse = Mouse::getPosition(*ventana);
				if (textoSalir.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
				{
					ventana->close();
					exit(0); // Salir del programa
				}
			}
		}

		ventana->clear();
		ventana->draw(textoFin);
		ventana->draw(textoSalir);
		ventana->display();
	}
}
