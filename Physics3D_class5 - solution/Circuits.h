#ifndef __CIRCUITS_H_
#define __CIRCUITS_H_

#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List2.h"

struct PhysBody3D;

struct circuitPoints
{
	vec3 first;
	vec3 second;
	float platform_x;
	float platform_y;
};

struct circuitPieces
{
	PhysBody3D*		PhysBody = nullptr;
	Cube*			PrimBody = nullptr;
};

class CircuitsManager : public Module
{
public:
	CircuitsManager(Application* app, bool start_enabled = true);
	virtual ~CircuitsManager();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void SetCircuit(int i);

private:
	// Circuits
	void Circtuit1();

	void DeleteCircuit();
	void CreateCircuitPoint(const vec3 init, int distance_between);
	void CreateCilinder(const vec3 init, int radius, int h, int angle);
	void JoinCircuitPoints();
private:
	p2List2<circuitPoints> circuit_points;
	p2List2<circuitPieces> circuit_pieces;
};
#endif // !__CIRCUITS_H_