﻿#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include <cmath>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(60, 60, 0));
	App->camera->LookAt(vec3(0, 0, 0));

	// Initial Rect
	{
		CreateCircuitPoint({ 0, 51, 0 }, 0);
		CreateCircuitPoint({ 0, 50, 0 }, 0);
		CreateCircuitPoint({ 0, 50, 10 }, 0);
	}
	
	// Down
	{
		CreateCircuitPoint({ 0, 49.5f, 12 }, 0);
		CreateCircuitPoint({ 0, 48.5f, 14 }, 0);
		CreateCircuitPoint({ 0, 47, 16 }, 0);
		CreateCircuitPoint({ 0, 25, 45 }, 0);
	}
	// Rise
	{
		CreateCircuitPoint({ 0, 24, 47 }, 0);
		CreateCircuitPoint({ 0, 23, 50 }, 0);
		CreateCircuitPoint({ 0, 23, 53 }, 0);
		CreateCircuitPoint({ 0, 24, 56 }, 0);
		CreateCircuitPoint({ 0, 26, 59 }, 0);
	}
	// Space
	JoinCircuitPoints();

	// Reception
	{
		CreateCircuitPoint({ 0, 32, 88 }, 0);
		CreateCircuitPoint({ 0, 31, 92 }, 0);
		CreateCircuitPoint({ 0, 29, 98 }, 0);
		CreateCircuitPoint({ 0, 17, 130 }, 0);
	}
	// Rise 2
	{
		CreateCircuitPoint({ 0, 16.5f, 132 }, 0);
		CreateCircuitPoint({ 0, 16.5f, 134 }, 0);
		CreateCircuitPoint({ 0, 16.75f, 136 }, 0);
		CreateCircuitPoint({ 0, 17.5f, 138 }, 0);
		CreateCircuitPoint({ 0, 18, 139 }, 0);
		CreateCircuitPoint({ 0, 19, 141 }, 0);
		CreateCircuitPoint({ 0, 20, 143 }, 0);
		CreateCircuitPoint({ 0, 21.5f, 146 }, 0);
		CreateCircuitPoint({ 0, 23.5f, 149 }, 0);
		CreateCircuitPoint({ 0, 25.5f, 152 }, 0);
		CreateCircuitPoint({ 0, 27.5f, 154 }, 0);
		CreateCircuitPoint({ 0, 47.5f, 170 }, 0);
		CreateCircuitPoint({ 0, 67.5f, 190 }, 0);
		CreateCircuitPoint({ 0, 68.5f, 191 }, 0);
		CreateCircuitPoint({ 0, 69.0f, 192 }, 0);
		CreateCircuitPoint({ 0, 69.5f, 193 }, 0);
		CreateCircuitPoint({ 0, 70.0f, 194 }, 0);
		CreateCircuitPoint({ 0, 70.0f, 195 }, 0);
		CreateCircuitPoint({ 0, 70.0f, 215 }, 0);
	}
	// Rise 3
	{
		CreateCircuitPoint({ 0, 70.3f, 216 }, 0);
		CreateCircuitPoint({ 0, 70.9f, 218 }, 0);
		
		JoinCircuitPoints();
	}
	// platforms 1-2
	{
		CreateCircuitPoint({ 0, 70, 225 }, 0);
		CreateCircuitPoint({ 0, 70, 235 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 65, 245 }, 0);
		CreateCircuitPoint({ 0, 65, 255 }, 0);
	}
	// Down 2
	{
		CreateCircuitPoint({ 0, 64.5f, 257 }, 0);
		CreateCircuitPoint({ 0, 64, 259 }, 0);
		CreateCircuitPoint({ 0, 63.5f, 261 }, 0);
		CreateCircuitPoint({ 0, 50, 270 }, 0);
	}

	JoinCircuitPoints();
	return true;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 10, 0, 0);

	p.axis = true;

	p.Render();
	for (int i = 0; i < pieces.PrimBodies.Count(); i++)
		pieces.PrimBodies[i].Render();
	for (int i = 0; i < cilinders.count(); i++)
		cilinders[i].Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCircuitPoint(const vec3 init, int distance_between)
{
	circuitPoints points;

	vec3 pos = init;
	vec3 dim(5, 0.5f, 0.5f);

	Cube c(dim.x, dim.y, dim.z);
	c.color = Orange;

	points.first = pos;
	c.SetPos(pos.x, pos.y, pos.z);

	//pieces.PrimBodies.PushBack(c);
	pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));

	circuit_points.add(points);

}

void ModuleSceneIntro::CreateCilinder(const vec3 init, int radius, int h, int angle)
{
	Cylinder cilinder(radius, h);
	cilinder.color = Orange;
	cilinder.SetPos(init.x, init.y, init.z);
	cilinder.SetRotation(angle, vec3(0, 1, 0));

	pieces.PhysBodies.PushBack(App->physics->AddBody(cilinder, 0.0f, this));
	cilinders.add(cilinder);
}


void ModuleSceneIntro::JoinCircuitPoints()
{
	for (int i = 0; i < circuit_points.count() - 1; i++)
	{
		// Angle Vertical -----
		float P1_z = circuit_points[i].first.z;
		float P1_y = circuit_points[i].first.y;

		float P2_z = circuit_points[i + 1].first.z;
		float P2_y = circuit_points[i + 1].first.y;

		float deltaY = P2_y - P1_y;
		float deltaX = P2_z - P1_z;

		float angleV = atan2(deltaY, deltaX) * 180 / 3.141592653589793;
		//angleV -= 90;
		LOG("%d", angleV);

		// -----------

		// Barriers --
		vec3 distance_vec = circuit_points[i + 1].first - circuit_points[i].first;

		float distance = length(distance_vec);

		Cube c(5, 0.5f, distance);
		c.color = Orange;

		c.SetRotation(-angleV, vec3(1, 0, 0));

		c.SetPos((circuit_points[i].first.x + distance_vec.x/2), circuit_points[i].first.y + distance_vec.y / 2, circuit_points[i].first.z + distance_vec.z/2);

		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));
		// -----------
	}

	circuit_points.clear();
}



