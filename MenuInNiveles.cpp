#include "MenuInNiveles.h"
#include <iostream>

MenuInNiveles::MenuInNiveles(sf::RenderWindow* ventana) : ventana(ventana)
{
	if (!fuente.loadFromFile("fuente.ttf"))
	{
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	textoNivel1.setFont(fuente);
	textoNivel1.setString("Nivel 1     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  ");
	textoNivel1.setCharacterSize(30);
	textoNivel1.setPosition(40, 40);

	textoNivel2.setFont(fuente);
	textoNivel2.setString("Nivel 2     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  ");
	textoNivel2.setCharacterSize(30);
	textoNivel2.setPosition(40, 100);

	textoNivel3.setFont(fuente);
	textoNivel3.setString("Nivel 3     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  ");
	textoNivel3.setCharacterSize(30);
	textoNivel3.setPosition(40, 160);

	textoVolver.setFont(fuente);
	textoVolver.setString("Volver");
	textoVolver.setCharacterSize(40);
	textoVolver.setPosition(ventana->getSize().x / 2 - 50, ventana->getSize().y - 220);

	if (!texturaNivel1.loadFromFile("sprite_nivel1.png") ||
		!texturaNivel2.loadFromFile("sprite_nivel2.png") ||
		!texturaNivel3.loadFromFile("sprite_nivel3.png"))
	{
		std::cout << "Error al cargar las texturas" << std::endl;
	}

	spriteNivel1.setTexture(texturaNivel1);
	spriteNivel2.setTexture(texturaNivel2);
	spriteNivel3.setTexture(texturaNivel3);

	spriteNivel1.setPosition(ventana->getSize().x - 70, 30);
	spriteNivel2.setPosition(ventana->getSize().x - 120, 90);
	spriteNivel3.setPosition(ventana->getSize().x - 170, 150);
}

int MenuInNiveles::MostrarMenuInNiveles()
{
	while (ventana->isOpen())
	{
		Event evento;
		while (ventana->pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
				return -1; // Salir del juego

			if (evento.type == sf::Event::MouseButtonPressed)
			{
				Vector2i posicionMouse = sf::Mouse::getPosition(*ventana);

				if (textoVolver.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
				{
					return 0; // Volver al menú principal
				}
			}
		}

		ventana->clear();
		ventana->draw(textoNivel1);
		ventana->draw(textoNivel2);
		ventana->draw(textoNivel3);
		ventana->draw(textoVolver);

		// Dibujar los sprites
		ventana->draw(spriteNivel1);
		ventana->draw(spriteNivel2);
		ventana->draw(spriteNivel3);

		ventana->display();
	}

	return 0; // Por defecto, volver al menú principal
}
