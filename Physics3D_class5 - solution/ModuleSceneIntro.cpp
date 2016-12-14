#include "Globals.h"
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

	App->camera->Move(vec3(0, 200, 0));
	App->camera->LookAt(vec3(0, 0, 0));

	// Circuit
	//CreateCircuitLine({ 0, 0, 0 }, { 0, 0, 30 }, 50);
	//CreateCircuitCorner({ -15, 0, 50}, {7.5f, 0, 50 }, 15);
	//CreateCircuitLine({ 7.5f, 0, 57.5f }, { 50, 0, 57.5f }, 45);

	// Start circuit

	// Recta inicial
	{
		CreateCircuitPoint({ -100, 1, 0 }, 13, 0);
		CreateCircuitPoint({ -50, 1, 0 }, 15, -30);
	}
	// Gir dreta
	{
		CreateCircuitPoint({ -40, 1, 3 }, 14, -20);
		CreateCircuitPoint({ -30, 1, 20 }, 12, -40);
		CreateCircuitPoint({ -28, 1, 30 }, 10, -80);
		CreateCircuitPoint({ -28, 1, 35 }, 10, -90);
	}
	// Gir esquerra
	{
		CreateCircuitPoint({ -26, 1, 45 }, 10, -80);
		CreateCircuitPoint({ -23, 1, 50 }, 10, -70);
		CreateCircuitPoint({ -15, 1, 58 }, 10, -30);
		CreateCircuitPoint({ -0, 1, 62 }, 10, -5);
	}
	// Recta
	{
		CreateCircuitPoint({35, 1, 63 }, 10, -0);
	}
	// Rampa
	{
		CreateCircuitPoint({ 40, 4, 63 }, 10, 0);
		CreateCircuitPoint({ 45, 5, 63 }, 10, 0);
		CreateCircuitPoint({ 48, 7, 63 }, 10, 0);
		CreateCircuitPoint({ 53, 9, 63 }, 10, 0);
		CreateCircuitPoint({ 63, 11, 63 }, 10, 0);
		CreateElevation({ 40, 1, 58 }, 10, 10, 20);
		CreateElevation({ 48, 4.5f, 58 }, 10, 10, 30);
		CreateElevation({ 57, 7.7f, 58 }, 10, 10, 10);
	}
	// Elevacio
	CreateElevation({ 87, 8.5f, 58 }, 50, 50, 0);


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

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCircuitLine(const vec3 init, const vec3 last, int interval)
{
	float distance = sqrt(pow(last.x - init.x, 2) + pow(last.y - init.y, 2) + pow(last.z - init.z, 2));

	vec3 direction = last - init;
	float direction_module = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	direction /= direction_module;

	vec3 perpendicular = { -direction.z, 0, direction.x };
	float prependicular_module = sqrt(pow(perpendicular.x, 2) + pow(perpendicular.y, 2) + pow(perpendicular.z, 2));
	perpendicular /= prependicular_module;

	vec3 pos;
	vec3 dim(1, 3, 1);

	Cube c(dim.x, dim.y, dim.z);
	c.color = Black;

	for (uint i = 0; i < interval; ++i) 
	{
		c.color = i % 2 ? White : Black;
		pos = (init + (direction * i)) + ((15.0f / 2) * perpendicular);
		c.SetPos(pos.x, pos.y + 1, pos.z);
		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));

		pos = (init + (direction * i)) + ((15.0f / 2) * -perpendicular);
		c.SetPos(pos.x, pos.y + 1, pos.z);
		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));
	}
}

void ModuleSceneIntro::CreateCircuitCorner(const vec3 init, const vec3 last, int interval)
{
	float distance = sqrt(pow(last.x - init.x, 2) + pow(last.y - init.y, 2) + pow(last.z - init.z, 2));

	vec3 direction = last - init;
	float direction_module = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	direction /= direction_module;

	vec3 perpendicular = { -direction.z, 0, direction.x };
	float prependicular_module = sqrt(pow(perpendicular.x, 2) + pow(perpendicular.y, 2) + pow(perpendicular.z, 2));
	perpendicular /= prependicular_module;

	vec3 pos;
	vec3 dim(1, 3, 1);

	Cube c(dim.x, dim.y, dim.z);
	c.color = Black;

	for (uint i = 0; i < interval; ++i) 
	{
		c.color = i % 2 ? Green : Orange;
		pos = (init + (direction * i)) + ((15.0f / 2) * perpendicular);
		c.SetPos(pos.x + interval/2 + .5f, pos.y + 1, pos.z + interval/2 + .5f);
		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));


		pos = (init + (perpendicular * i)) + ((15.0f / 2) * direction);
		c.SetPos(pos.x, 1, pos.z);
		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));
	}
}

void ModuleSceneIntro::CreateCircuitPoint(const vec3 init, int distance_between, float angle, float platform_y, float platform_x)
{
	circuitPoints points;

	points.platform_x = platform_x;
	points.platform_y = platform_y;

	vec3 pos = init;
	vec3 dim(1, 3, 1);

	Cube c(dim.x, dim.y, dim.z);
	c.color = Orange;

	points.first = pos;
	c.SetPos(pos.x, pos.y, pos.z);
	c.SetRotation(angle, vec3(0, 1, 0));

	pieces.PrimBodies.PushBack(c);
	pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));


	pos.x -= distance_between * sin(angle*DEGTORAD);
	pos.z -= distance_between * cos(angle*DEGTORAD);

	points.second = pos;
	c.SetPos(pos.x, pos.y, pos.z);
	c.SetRotation(angle, vec3(0, 1, 0));

	pieces.PrimBodies.PushBack(c);
	pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));

	circuit_points.add(points);

}

void ModuleSceneIntro::CreateElevation(const vec3 init, int size_x, int size_y, float angle, bool which_side)
{
	vec3 pos = init;

	Cube c(size_x, 1, size_y);
	c.color = Orange;

	c.SetPos(pos.x, pos.y, pos.z);

	if(which_side)
		c.SetRotation(angle, vec3(1, 0, 0));
	else
		c.SetRotation(angle, vec3(0, 0, 1));

	pieces.PrimBodies.PushBack(c);
	pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));
}

void ModuleSceneIntro::JoinCircuitPoints()
{
	for (int i = 0; i < circuit_points.count() - 1; i++)
	{
		// First

		// Angle Horizontal -----
		float P1_x = circuit_points[i].first.x;
		float P1_z = circuit_points[i].first.z;

		float P2_x = circuit_points[i + 1].first.x;
		float P2_z = circuit_points[i + 1].first.z;

		float deltaY = P2_z - P1_z;
		float deltaX = P2_x - P1_x;

		float angleH = atan2(deltaY, deltaX) * 180 / 3.141592653589793;
		angleH -= 90;
		// -----------

		// Barriers --
		vec3 distance_vec = circuit_points[i + 1].first - circuit_points[i].first;

		float distance = length(distance_vec);

		Cube c(1, 4, distance);
		c.color = Orange;

		c.SetRotation(-angleH, vec3(0, 1, 0));

		c.SetPos(circuit_points[i].first.x + distance_vec.x/2, circuit_points[i].first.y + distance_vec.y / 2, circuit_points[i].first.z + distance_vec.z/2);

		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));
		// -----------

		distance_vec = circuit_points[i + 1].first - circuit_points[i].second;


		// Second

		// Angle Horizontal -----
		P1_x = circuit_points[i].second.x;
		P1_z = circuit_points[i].second.z;

		P2_x = circuit_points[i + 1].second.x;
		P2_z = circuit_points[i + 1].second.z;

		deltaY = P2_z - P1_z;
		deltaX = P2_x - P1_x;

		angleH = atan2(deltaY, deltaX) * 180 / 3.141592653589793;
		angleH -= 90;
		// -----------

		distance_vec = circuit_points[i + 1].second - circuit_points[i].second;

		distance = length(distance_vec);

		Cube c2(1, 4, distance);
		c2.color = Orange;

		c2.SetRotation(-angleH, vec3(0, 1, 0));

		c2.SetPos(circuit_points[i].second.x + distance_vec.x / 2, circuit_points[i].second.y + distance_vec.y / 2, circuit_points[i].second.z + distance_vec.z / 2);

		pieces.PrimBodies.PushBack(c2);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c2, 0.0f, this));
		

	}
}


