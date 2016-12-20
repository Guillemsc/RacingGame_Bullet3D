#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Circuits.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
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

	App->camera->Move(vec3(30, 70, 150));
	//App->camera->LookAt(vec3(0, 0, 0));

	App->circuits->SetCircuit(1);

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

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
	{
		App->circuits->SetCircuit(1);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == pb_vehicle)
	{
		if (body2->type == pb_checkpoint)
		{
			App->circuits->Check_CheckPoints(body2);
		}
		if (body2->type == pb_scoredot) 
		{
			App->circuits->Check_ScoreDots(body2);
		}
		if (body2->type == pb_hammer)
		{
			App->player->vehicle->body->setLinearFactor(btVector3(1, 1, 1));
			App->player->vehicle->body->setAngularFactor(btVector3(1, 1, 1));
		}
	}
}




