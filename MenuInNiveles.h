#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class MenuInNiveles
{
public:
	MenuInNiveles(sf::RenderWindow* ventana);
	int MostrarMenuInNiveles();

private:
	RenderWindow* ventana;
	Font fuente;
	Text textoNivel1;
	Text textoNivel2;
	Text textoNivel3;
	Text textoVolver;

	Texture texturaNivel1;
	Texture texturaNivel2;
	Texture texturaNivel3;

	Sprite spriteNivel1;
	Sprite spriteNivel2;
	Sprite spriteNivel3;
};
