#include "NivelBase.h"

class Nivel1 : public NivelBase
{
public:
	Nivel1(Vector2i resolucion, const std::string& titulo);

	void CargarImagenes() override;
	void IniciarFisica();
	void Dibujar() override;
	void BeginContact(b2Contact* contact);
};