#include "MenuPrincipal.h"


MenuPrincipal::MenuPrincipal(sf::RenderWindow* ventana) : ventana(ventana)
{
	if (!fuente.loadFromFile("fuente.ttf"))
	{
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	textoJugar.setFont(fuente);
	textoJugar.setString("Jugar");
	textoJugar.setCharacterSize(50);
	textoJugar.setPosition(ventana->getSize().x / 2 - 50, ventana->getSize().y / 3);

	textoIformacion.setFont(fuente);
	textoIformacion.setString("Información");
	textoIformacion.setCharacterSize(50);
	textoIformacion.setPosition(ventana->getSize().x / 2 - 130, ventana->getSize().y / 2 - 30);

	textoNiveles.setFont(fuente);
	textoNiveles.setString("Ver Niveles");
	textoNiveles.setCharacterSize(50);
	textoNiveles.setPosition(ventana->getSize().x / 2 - 120, ventana->getSize().y / 1.75 - 10);

	textoSalir.setFont(fuente);
	textoSalir.setString("Salir");
	textoSalir.setCharacterSize(50);
	textoSalir.setPosition(ventana->getSize().x / 2 - 45, ventana->getSize().y / 1.5);

	MostrarMenu();
}

int MenuPrincipal::MostrarMenu()
{
	while (ventana->isOpen())
	{
		Event evento;
		while (ventana->pollEvent(evento))
		{
			if (evento.type == Event::Closed)
				return -1;

			if (evento.type == Event::MouseButtonPressed)
			{
				Vector2i posicionMouse = Mouse::getPosition(*ventana);

				if (textoJugar.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
					return 1;

				if (textoIformacion.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
					return 2;

				if (textoNiveles.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
					return 3;

				if (textoSalir.getGlobalBounds().contains(posicionMouse.x, posicionMouse.y))
					return -1;
			}
		}

		ventana->clear();
		ventana->draw(textoJugar);
		ventana->draw(textoNiveles);
		ventana->draw(textoIformacion);
		ventana->draw(textoSalir);
		ventana->display();
	}
	return -1;
}
