#include "MenuInformacion.h"
#include <iostream>

MenuInformacion::MenuInformacion(sf::RenderWindow* ventana) : ventana(ventana)
{
	if (!fuente.loadFromFile("fuente.ttf"))
	{
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	textoInformacion.setFont(fuente);
	textoInformacion.setString(
		"En este juego debés lanzar ragdolls hacia las cajas.\n\n"
		"Cómo jugar:\n"
		"-Mientras más lejos esté el puntero del mouse,\n más lejos irá el ragdoll.\n"
		"-Perdés si te quedás sin ragdolls.");
	textoInformacion.setCharacterSize(30);
	textoInformacion.setPosition(40, 40);


	textoVolver.setFont(fuente);
	textoVolver.setString("Volver");
	textoVolver.setCharacterSize(40);
	textoVolver.setPosition(ventana->getSize().x / 2 - 50, ventana->getSize().y - 220);


	textoHechoCon.setFont(fuente);
	textoHechoCon.setFillColor(Color::Red);
	textoHechoCon.setString(
		"Proyecto realizado en Visual Studio\n"
		"          utilizando SFML y Box2D");
	textoHechoCon.setCharacterSize(17);
	textoHechoCon.setPosition(ventana->getSize().x / 2 + 90, ventana->getSize().y - 100);
}

int MenuInformacion::MostrarMenuInformacion()
{
	while (ventana->isOpen())
	{
		sf::Event evento;
		while (ventana->pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
				return -1; // Salir del juego

			if (evento.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i posicionMouse = sf::Mouse::getPosition(*ventana);
				if (textoVolver.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
				{
					return 0; // Volver al menú principal
				}
			}
		}

		ventana->clear();
		ventana->draw(textoInformacion);
		ventana->draw(textoHechoCon);
		ventana->draw(textoVolver);
		ventana->display();
	}

	return 0;
}
