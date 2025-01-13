#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class MenuInformacion
{
public:
	MenuInformacion(sf::RenderWindow* ventana);
	int MostrarMenuInformacion();

private:
	RenderWindow* ventana;
	Font fuente;
	Text textoInformacion;
	Text textoHechoCon;
	Text textoVolver;
};
