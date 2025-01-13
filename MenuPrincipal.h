#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
class MenuPrincipal
{
public:
	MenuPrincipal(RenderWindow* ventana);
	int MostrarMenu();

private:
	RenderWindow* ventana;

	Font fuente;
	Text textoJugar;
	Text textoNiveles;
	Text textoIformacion;
	Text textoSalir;
};

