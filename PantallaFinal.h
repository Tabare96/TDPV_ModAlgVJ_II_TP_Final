#ifndef PANTALLAFINAL_H
#define PANTALLAFINAL_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class PantallaFinal
{
private:
	RenderWindow* ventana;
	Font fuente;
	Text textoFin;
	Text textoSalir;

public:
	PantallaFinal(RenderWindow* ventana);
	void MostrarPantallaFinal();
};

#endif
