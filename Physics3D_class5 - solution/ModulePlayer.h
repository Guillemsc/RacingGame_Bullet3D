#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 5000.0f
#define BRAKE_POWER 500.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	float abs(float number);
	float GetCarTrunCapability();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	float turn_degrees;
};