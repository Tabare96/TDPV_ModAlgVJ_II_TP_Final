#include "NivelBase.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include "MenuPrincipal.h"
#include "MenuInformacion.h"
#include "MenuInNiveles.h"
#include "PantallaFinal.h"

int main(int argc, char* args[])
{
	//	Por nivel

	//Nivel1 nivel1(sf::Vector2i(800, 600), "Nivel 1");
	//Nivel2 nivel2(sf::Vector2i(800, 600), "Nivel 2");
	//Nivel3 nivel3(sf::Vector2i(800, 600), "Nivel 3");


	//--------------------------------------------------------------------\\
	//	DESDE EL MENU


	sf::RenderWindow ventana(sf::VideoMode(800, 600), "Menu Principal");
	// Creación de instancias de los menús necesarios
	MenuPrincipal menuPrincipal(&ventana);
	MenuInformacion menuInformacion(&ventana);
	MenuInNiveles menuInfoNiveles(&ventana);

	int nivelActual = 1; // Inicia desde el Nivel 1

	// Bucle principal de la aplicación
	while (true)
	{
		int seleccion = menuPrincipal.MostrarMenu();	// Muestra el menú principal y obtiene la selección del usuario

		if (seleccion == 1) // Opción "Jugar"
		{
			while (nivelActual <= 3)	// Bucle para avanzar por los niveles
			{
				if (nivelActual == 1)
				{
					Nivel1 nivel1(sf::Vector2i(800, 600), "Nivel 1");	// Creación y ejecución del Nivel 1
					if (nivel1.Ganado())
					{
						nivelActual++;
					}
					else
					{
						sf::sleep(sf::seconds(1.5)); // Pausa antes de salir
						break;  // Salir del bucle de niveles
					}
				}

				else if (nivelActual == 2)
				{
					Nivel2 nivel2(sf::Vector2i(800, 600), "Nivel 2");
					if (nivel2.Ganado())
					{
						nivelActual++;
					}
					else
					{
						sf::sleep(sf::seconds(1.5));
						break;
					}
				}

				else if (nivelActual == 3)
				{
					Nivel3 nivel3(sf::Vector2i(800, 600), "Nivel 3");
					if (nivel3.Ganado())
					{
						PantallaFinal pantallaFinal(&ventana);
						pantallaFinal.MostrarPantallaFinal();
						break;
					}
					else
					{
						sf::sleep(sf::seconds(1.5));
						break;
					}
				}
			}
		}
		else if (seleccion == 2) // Opción "Información"
		{
			menuInformacion.MostrarMenuInformacion();
		}
		else if (seleccion == 3) // Opción "Niveles"
		{
			menuInfoNiveles.MostrarMenuInNiveles();
		}
		else if (seleccion == -1) // Opción "Salir"
		{
			break;
		}
	}

	// FIN DESDE EL MENU
	//--------------------------------------------------------------------\\
    
	return 0;
}