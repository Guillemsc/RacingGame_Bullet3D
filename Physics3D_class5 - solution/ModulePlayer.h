#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 40000.0f // 37000
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

	void SetCameraDistance();
	void ResetCarMotion();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	float turn_degrees;
	
	int score = 0;

private:
	float starting_camera_distance = 0;
};