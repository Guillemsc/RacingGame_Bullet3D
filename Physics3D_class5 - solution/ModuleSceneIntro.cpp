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

	App->camera->Move(vec3(-10, 55, 10));
	//App->camera->LookAt(vec3(0, 0, 0));

	App->circuits->SetCircuit(1);

	_0to2kmh_fx = App->audio->LoadFx("Game/Music/0to2kmh_fx.wav");
	_3to20kmh_fx = App->audio->LoadFx("Game/Music/3to20kmh_fx.wav");
	_more20kmh_fx = App->audio->LoadFx("Game/Music/more20kmh_fx.wav");

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

	//if (App->player->vehicle->GetKmh() >= 0 && App->player->vehicle->GetKmh() < 15) {
	//	App->audio->PlayFx(_0to2kmh_fx);
	//}
	//else if (App->player->vehicle->GetKmh() >= 15 && App->player->vehicle->GetKmh() < 40) {
	//	App->audio->PlayFx(_3to20kmh_fx);
	//}
	//else if (App->player->vehicle->GetKmh() >= 40) {
	//	App->audio->PlayFx(_more20kmh_fx);
	//}

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
	}
}




