#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List2.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

struct circuitPieces 
{
	p2DynArray<PhysBody3D*>		PhysBodies;
	p2DynArray<Cube>			PrimBodies;
};

struct circuitPoints
{
	vec3 first;
	vec3 second;
	float platform_x;
	float platform_y;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	// Circuit Creation Functions
	void CreateCircuitLine(const vec3 init, const vec3 last, int interval = 1);
	void CreateCircuitCorner(const vec3 init, const vec3 last, int interval = 1);

	void CreateCircuitPoint(const vec3 init, int distance_between, float angle, float platform_y = 0, float platform_x = 10);
	void CreateElevation(const vec3 init, int distance_between, float angle);
	void JoinCircuitPoints();

	p2List2<circuitPoints> circuit_points;



public:

	circuitPieces pieces;
};
