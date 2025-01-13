#include "NivelBase.h"

class Nivel2 : public NivelBase
{
public:
	Nivel2(Vector2i resolucion, const std::string& titulo);

	void CargarImagenes() override;
	void IniciarFisica();
	void Dibujar() override;
	void BeginContact(b2Contact* contact);

private:
	//-------------------------------------------------------------
	// Revolute Joint en el obstáculo giratorio
	//-------------------------------------------------------------
	static b2RevoluteJoint* CreateRevoluteJoint(b2World* phyWorld, b2Body* base, b2Vec2 anchorBase, b2Body* second,
		float angMin, float angMax, float motorSpeed, float maxTorque,
		bool enableMotor, bool enableLimits)
	{
		b2RevoluteJointDef jointDef;
		jointDef.Initialize(base, second, anchorBase);
		jointDef.lowerAngle = angMin;
		jointDef.upperAngle = angMax;
		jointDef.enableLimit = enableLimits;
		jointDef.maxMotorTorque = maxTorque;
		jointDef.motorSpeed = motorSpeed;
		jointDef.enableMotor = enableMotor;

		b2RevoluteJoint* revJoint = (b2RevoluteJoint*)phyWorld->CreateJoint(&jointDef);
		return revJoint;
	}
	b2Body* bdy_barra;
	b2BodyDef bdyDef_barra;
	b2Fixture* fix_barra;
	b2FixtureDef fixDef_barra;
	b2RevoluteJoint* joint_barra;
	RectangleShape* fig_barra;
};