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

	App->camera->Move(vec3(0, 70, 0));
	App->camera->LookAt(vec3(0, 0, 0));

	// Circuit
	CreateCircuitLine({ 0, 0, 0 }, { 0, 0, 30 }, 50);
	CreateCircuitCorner({ -15, 0, 50}, {7.5f, 0, 50 }, 15);
	CreateCircuitLine({ 7.5f, 0, 57.5f }, { 50, 0, 57.5f }, 45);

	CreateCircuitPoint({ 50, 1, 1 }, 10, 60);
	CreateCircuitPoint({ 30, 1, 20 }, 15, 100);
	CreateCircuitPoint({ 50, 1, 30 }, 10, 160);

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
	Plane p(0, 1, 0, 0);

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

void ModuleSceneIntro::CreateCircuitPoint(const vec3 init, int distance_between, float angle)
{
	circuitPoints points;

	points.angle = angle;

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

void ModuleSceneIntro::JoinCircuitPoints()
{
	for (int i = 0; i < circuit_points.count() - 1; i++)
	{
		float P1_x = circuit_points[i].first.x;
		float P1_y = circuit_points[i].first.z;

		float P2_x = circuit_points[i + 1].first.x;
		float P2_y = circuit_points[i + 1].first.z;

		//
		float deltaY = P2_y - P1_y;
		float deltaX = P2_x - P1_x;

		float angle = atan2(deltaY, deltaX) * 180 / 3.141592653589793;
		angle -= 90;
		//

		vec3 distance_vec = circuit_points[i + 1].first - circuit_points[i].first;

		float distance = length(distance_vec);

		Cube c(1, 4, distance);
		c.color = Orange;

		c.SetRotation(-angle, vec3(0, 1, 0));

		c.SetPos(circuit_points[i].first.x + distance_vec.x/2, 1, circuit_points[i].first.z + distance_vec.z/2);

		pieces.PrimBodies.PushBack(c);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c, 0.0f, this));


		//

		P1_x = circuit_points[i].second.x;
		P1_y = circuit_points[i].second.z;

		P2_x = circuit_points[i + 1].second.x;
		P2_y = circuit_points[i + 1].second.z;

		//
		deltaY = P2_y - P1_y;
		deltaX = P2_x - P1_x;

		angle = atan2(deltaY, deltaX) * 180 / 3.141592653589793;
		angle -= 90;
		//

		//

		distance_vec = circuit_points[i + 1].second - circuit_points[i].second;

		distance = length(distance_vec);

		Cube c2(1, 4, distance);
		c2.color = Orange;

		c2.SetRotation(-angle, vec3(0, 1, 0));

		c2.SetPos(circuit_points[i].second.x + distance_vec.x / 2, 1, circuit_points[i].second.z + distance_vec.z / 2);

		pieces.PrimBodies.PushBack(c2);
		pieces.PhysBodies.PushBack(App->physics->AddBody(c2, 0.0f, this));

	}
}


