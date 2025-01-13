#include "NivelBase.h"

class Nivel3 : public NivelBase
{
public:
	Nivel3(Vector2i resolucion, const std::string& titulo);

	void CargarImagenes() override;
	void IniciarFisica();
	void Dibujar() override;
	void BeginContact(b2Contact* contact);
};