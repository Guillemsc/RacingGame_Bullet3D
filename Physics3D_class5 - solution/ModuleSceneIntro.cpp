#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
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

	App->camera->Move(vec3(0, 50.5f, 0));
	//App->camera->Move(vec3(-300, 100.5f, 200));
	App->camera->LookAt(vec3(0, 0, 200));

	App->circuits->SetCircuit(4);

	engine_idle_fx = App->audio->LoadFx("Game/Music/engine_idle_fx.wav");
	engine_start_fx = App->audio->LoadFx("Game/Music/engine_start_fx.wav");
	checkpoint_fx = App->audio->LoadFx("Game/Music/checkpoint_fx.wav");
	level_finished_fx = App->audio->LoadFx("Game/Music/level_finished_fx.wav");

	theme_song_ms = App->audio->LoadFx("Game/Music/theme_song_ms.wav");
	App->audio->PlayFx(theme_song_ms, -1, 5);

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
	//Plane p(0, 10, 0, 0);

	//p.axis = true;

	//p.Render();

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->circuits->SetCircuit(1);
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->circuits->SetCircuit(2);
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->circuits->SetCircuit(3);
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		App->circuits->SetCircuit(4);

	

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) 
	{
		App->audio->PlayFx(engine_start_fx, 0, 2);
		App->audio->PlayFx(engine_idle_fx, -1, 1);
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
		App->audio->PlayFx(engine_idle_fx, -1, 1);

	else if (App->player->vehicle->GetKmh() == 0) 
		App->audio->PlayFx(engine_idle_fx, 0, 1);



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
			App->player->Crash();
		}
		if (body2->type == pb_die_sensor)
		{
			App->circuits->ReturnToLastCheckpoint();
		}
	}
}




