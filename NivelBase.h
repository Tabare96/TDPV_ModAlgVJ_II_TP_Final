#pragma once
#include "Actor.h"
#include "Ragdoll.h"
#include <Box2D/Box2D.h>
#include <vector>
#include "Caja.h"
#include "Plataforma.h"
#include <SFML/Graphics.hpp>
#include "PantallaFinal.h"

class NivelBase : public b2ContactListener
{
public:
	NivelBase();
	virtual ~NivelBase();

	virtual void SetCamera();					// Configura la cámara para centrarse en una parte específica del nivel
	virtual void ActualizarPosicionArma();		// Actualiza la posición y rotación del arma según la posición del ratón
	virtual float Rad2Deg(float radianes);		// Convierte un ángulo de radianes a grados
	virtual float Deg2Rad(float grados);		// Convierte un ángulo de grados a radianes
	virtual Vector2f ObtenerPuntaArma();		// Obtiene la posición de la punta del arma
	virtual void GameLoop(int cajasTotales);	// Bucle principal del juego: maneja eventos, física y renderizado
	virtual void ActualizarFisica();
	virtual void ProcesarEventos(int cajasTotales);
	virtual void ComprobarEstadoCajas(int cajasRequeridas);	// Comprueba si se han golpeado suficientes cajas para completar el nivel
	virtual bool Ganado() const;
	virtual void Dibujar() = 0;		// Método abstracto para dibujar los elementos del nivel
	virtual void CargarImagenes();
	void ConfigurarTextos(const std::string& textoInicial, int limiteRagdolls);

protected:
	RenderWindow* ventana1; // Ventana principal donde se renderiza el juego
	View* camara1;			// Cámara utilizada para enfocar áreas específicas del nivel

	Event* evento1;			// Almacena eventos como teclado y ratón

	Time* tiempo1;			// Tiempo actual en la simulación
	Clock* reloj1;			// Reloj para medir el tiempo transcurrido

	float fps, tiempoFrame, tiempo2; // Variables para controlar el rendimiento y la tasa de frames

	b2World* mundo1;		// Mundo físico de Box2D

	//Suelo
	b2Body* bdy_suelo;
	b2BodyDef bdyDef_suelo;
	b2Fixture* fix_suelo;
	b2FixtureDef fixDef_suelo;

	//Cañon
	b2Body* bdy_cannon;
	b2BodyDef bdyDef_cannon;
	b2Fixture* fix_cannon;
	b2FixtureDef fixDef_cannon;

	//Plataformas y cajas
	std::vector<Caja*> cajas;
	std::vector<Plataforma*> plataformas;

	//Texturas y Sprites
	Texture* txt_suelo;
	Texture* txt_caja;
	Texture* txt_cannon;

	Sprite* spr_suelo;
	Sprite* spr_caja;
	Sprite* spr_cannon;

	Texture* txt_fondo;
	Sprite* spr_fondo;

	Texture* txt_baseCannon;
	Sprite* spr_baseCannon;

	//Forma rectangular (SFML)
	RectangleShape* fig_suelo;
	RectangleShape* fig_cannon;
	RectangleShape* fig_caja;

	Actor* act_suelo;
	Actor* act_cannon;
	Actor* act_caja;

	Ragdoll* rag_1;
	Ragdoll* rag_2;
	Ragdoll* rag_3;

	std::vector<Ragdoll*> ragdolls;

	Font fuente;	// Fuente para los textos en pantalla
	Text textoRagdollsRestantes;

	bool todasCajasGolpeadas;
	bool derrota;
	Text textoVictoriaDerrota;
	Text textoCajasGolpeadas;
	int cajasGolpeadas;		// Contador de cajas golpeadas

	int ragdollsRestantes;	// Cantidad de ragdolls restantes que el jugador puede lanzar

	b2RevoluteJoint* joint_barra = nullptr; // Junta para controlar una barra
};
