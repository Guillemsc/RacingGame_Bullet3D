#include "Globals.h"
#include "Circuits.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Timer.h"
#include <stdio.h>

CircuitsManager::CircuitsManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

CircuitsManager::~CircuitsManager()
{
	//delete timer;
}

bool CircuitsManager::Start()
{
	return true;
}

update_status CircuitsManager::Update(float dt)
{
	// Circuit render
	for (int i = 0; i < circuit_pieces.count(); i++)
	{
		if (circuit_pieces[i].PrimBody != nullptr)
			circuit_pieces[i].PrimBody->Render();
	}

	// Checkpoints render
	for (int i = 0; i<check_points.count(); i++)
	{
		if (check_points[i].PrimBody != nullptr)
		{
			if (App->physics->debug)
				check_points[i].PrimBody->Render();
			check_points[i].visual->Render();
		}
	}

	// Score render
	dots_rotation++;
	for (int i = 0; i < score_dots.count(); i++)
	{
		if (score_dots[i].PrimBody != nullptr)
		{
			if (App->physics->debug)
				score_dots[i].PrimBody->Render();
			score_dots[i].visual->Render();

			score_dots[i].visual->SetRotation(dots_rotation, vec3(0, 1, 0));
		}
	}

	// Constraints
	for (int i = 0; i < circuit_constraints.count(); i++)
	{
		circuit_constraints[i].PhysBody->GetTransform(&(circuit_constraints[i].PrimBody->transform));

		if (circuit_constraints[i].Sensor != nullptr)
		{
			mat4x4 m;
			circuit_constraints[i].PhysBody->GetTransform(&m);
			m[12] -= 5;

			circuit_constraints[i].Sensor->SetTransform(&m);
		}
		circuit_constraints[i].PrimBody->Render();
	}

	ChangeTitle();

	MoveAroundCheckPoints();


	return UPDATE_CONTINUE;
}

bool CircuitsManager::CleanUp()
{
	return true;
}

void CircuitsManager::SetCircuit(int i)
{
	DeleteCircuit();
	App->player->ResetCarMotion();

	current_circuit = i;
	started = false;
	finished = false;
	timer = new Timer();

	switch (i)
	{
	case 1:
		Circtuit1();
		break;
	}

	InitCheckPoints();
	InitScoreDots();
}

void CircuitsManager::Circtuit1()
{
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
		CreateCircuitPoint({ 0, 23.2f, 49 }, 0);
		CreateCircuitPoint({ 0, 22.7f, 51 }, 0);
		CreateCircuitPoint({ 0, 22.7f, 53 }, 0);
		CreateCircuitPoint({ 0, 22.9f, 55 }, 0);
		CreateCircuitPoint({ 0, 23.4f, 57 }, 0);
		CreateCircuitPoint({ 0, 24.2f, 59 }, 0);
		CreateCircuitPoint({ 0, 25.5f, 61 }, 0);
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
		CreateCircuitPoint({ 0, 16.2f, 134 }, 0);
		CreateCircuitPoint({ 0, 16.2f, 136 }, 0);
		CreateCircuitPoint({ 0, 16.3f, 138 }, 0);
		CreateCircuitPoint({ 0, 16.6f, 140 }, 0);
		CreateCircuitPoint({ 0, 17.1f, 142 }, 0);
		CreateCircuitPoint({ 0, 17.9f, 144 }, 0);
		CreateCircuitPoint({ 0, 19.0f, 146 }, 0);
		CreateCircuitPoint({ 0, 20.7f, 148 }, 0);
		CreateCircuitPoint({ 0, 22.9f, 150 }, 0);

		CreateCircuitPoint({ 0, 52.5f, 176 }, 0);
		CreateCircuitPoint({ 0, 53.4f, 177 }, 0);
		CreateCircuitPoint({ 0, 54.2f, 178 }, 0);
		CreateCircuitPoint({ 0, 54.6f, 179 }, 0);
		CreateCircuitPoint({ 0, 54.8f, 180 }, 0);
	}
	// Spaces zone
	{
		CreateCircuitPoint({ 0, 55.3f, 193 }, 0);
		CreateCircuitPoint({ 0, 55.6f, 195 }, 0);
		CreateCircuitPoint({ 0, 56.0f, 197 }, 0);
		CreateCircuitPoint({ 0, 56.8f, 199 }, 0);

		JoinCircuitPoints();
	}
	// platforms 1-2
	{
		CreateCircuitPoint({ 0, 55, 206 }, 0);
		CreateCircuitPoint({ 0, 55, 216 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 53, 225 }, 0);
		CreateCircuitPoint({ 0, 53, 235 }, 0);
	}
	// Down 2
	{
		CreateCircuitPoint({ 0, 53.2f, 237 }, 0);
		CreateCircuitPoint({ 0, 53.6f, 239 }, 0);
		CreateCircuitPoint({ 0, 54.2f, 241 }, 0);
		CreateCircuitPoint({ 0, 55.0f, 243 }, 0);
		CreateCircuitPoint({ 0, 60.5f, 254 }, 0);
		CreateCircuitPoint({ 0, 60.9f, 256 }, 0);

		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 61, 265 }, 0);
		CreateCircuitPoint({ 0, 64, 272 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 57.5f, 292 }, 0);
		CreateCircuitPoint({ 0, 54, 310 }, 0);

	}
	//Loop
	{
		CreateCircuitPoint({ 0, 53.9f, 311 }, 0);
		CreateCircuitPoint({ 0, 54.0f, 312 }, 0);
		CreateCircuitPoint({ 0, 54.18f, 313 }, 0);
		CreateCircuitPoint({ 0, 54.4f, 314 }, 0);
		CreateCircuitPoint({ 0, 54.6f, 315 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 55, 320 }, 0);
		CreateCircuitPoint({ 0, 55.3f, 322 }, 0);
		CreateCircuitPoint({ 0, 55.6f, 323 }, 0);
		CreateCircuitPoint({ 0, 56.1f, 324 }, 0);
		CreateCircuitPoint({ 0, 56.8f, 325 }, 0);
		CreateCircuitPoint({ 0, 57.7f, 326 }, 0);
		CreateCircuitPoint({ 0, 59.0f, 327 }, 0);
		CreateCircuitPoint({ 0, 61, 328 }, 0);
		CreateCircuitPoint({ 0, 63, 328.5f }, 0);
		CreateCircuitPoint({ 0, 65, 328.5f }, 0);
		CreateCircuitPoint({ 0, 67, 328 }, 0);
		CreateCircuitPoint({ 0, 68.5f, 327 }, 0);
		CreateCircuitPoint({ 0, 70, 325.5f }, 0);
		CreateCircuitPoint({ 0, 71, 324 }, 0);
		CreateCircuitPoint({ 0, 71.5f, 322 }, 0);
		CreateCircuitPoint({ 0, 71.5f, 320 }, 0);
		CreateCircuitPoint({ 0, 71.1f, 318 }, 0);
		CreateCircuitPoint({ 0, 69.8f, 316 }, 0);
		CreateCircuitPoint({ 0, 68.7f, 315 }, 0);
		CreateCircuitPoint({ 0, 67, 314 }, 0);
		CreateCircuitPoint({ 0, 65, 313.5f }, 0);
		CreateCircuitPoint({ 0, 63, 313.6f }, 0);
		CreateCircuitPoint({ 0, 60, 314.2f }, 0);
		JoinCircuitPoints();
	}
	//Space zone 3
	{
		CreateCircuitPoint({ 0, 54.5f, 314.75f }, 0);
		CreateCircuitPoint({ 0, 50, 316 }, 0);
		CreateCircuitPoint({ 0, 48, 317 }, 0);
		CreateCircuitPoint({ 0, 46, 318.5f }, 0);
		CreateCircuitPoint({ 0, 44, 320 }, 0);
		CreateCircuitPoint({ 0, 42.5f, 322 }, 0);
		CreateCircuitPoint({ 0, 41.5f, 324 }, 0);
		CreateCircuitPoint({ 0, 40.5f, 327 }, 0);
		CreateCircuitPoint({ 0, 40, 329 }, 0);
		CreateCircuitPoint({ 0, 40, 350 }, 0);
		CreateCircuitPoint({ 0, 43, 350 }, 0);
	}

	// Check Points -------------------------

	CreateCheckpoint({ 0, 51, 3 }, 5);
	CreateCheckpoint({ 0, 33, 90 }, 13);
	CreateCheckpoint({ 0, 56.5f, 185 }, 10);
	CreateCheckpoint({ 0, 57.5f, 300 }, 10);

	// --------------------------------------

	// Score Creation -----------------------

	CreateScoreDots({ 0, 49, 16 }, 4);
	CreateScoreDots({ 0, 70, 320 }, 4);
	CreateScoreDots({ 0, 42, 342 }, 4);

	// --------------------------------------

	// Hummer -------------------------------
	CreateHammer(vec3(0, 87.5f, 210), vec3(0, 57.5f, 210), 2, 160.0f);
	CreateHammer(vec3(0, 87.5f, 230), vec3(0, 57.5f, 230), 2, 160.0f);
	CreateHammer(vec3(0, 87.5f, 215), vec3(0, 57.5f, 215), 4, 160.0f);
	// --------------------------------------

	JoinCircuitPoints();
}

// Free and reset circuit and checkpoint list
void CircuitsManager::DeleteCircuit()
{
	for (int i = 0; i < circuit_pieces.count(); i++)
	{
		App->physics->UnloadPhysBody(circuit_pieces[i].PhysBody);
		delete circuit_pieces[i].PrimBody;
	}

	for (int i = 0; i < check_points.count(); i++)
	{
		App->physics->UnloadPhysBody(check_points[i].PhysBody);
		delete check_points[i].PrimBody;
		delete check_points[i].visual;
	}

	for (int i = 0; i < score_dots.count(); i++)
	{
		App->physics->UnloadPhysBody(score_dots[i].PhysBody);
		delete score_dots[i].PrimBody;
		delete score_dots[i].visual;
	}

	int counter = 1;
	for (int i = 0; i < circuit_constraints.count(); i++)
	{
		App->physics->UnloadPhysBody(circuit_constraints[i].PhysBody);
		if (circuit_constraints[i].hinge != nullptr)
		{
			LOG("%d", counter);
			App->physics->UnloadConstraint(circuit_constraints[i].hinge);
			counter++;
		}
		if (circuit_constraints[i].Sensor != nullptr)
			App->physics->UnloadPhysBody(circuit_constraints[i].Sensor);
	}

	circuit_pieces.clear();
	circuit_points.clear();
	circuit_constraints.clear();
	check_points.clear();
	score_dots.clear();

	//if (timer != nullptr)
	//delete timer;
}

void CircuitsManager::CreateCircuitPoint(const vec3 init, int distance_between)
{
	circuitPoints points;

	vec3 pos = init;
	vec3 dim(5, 0.5f, 0.5f);

	Cube* c = new Cube(dim.x, dim.y, dim.z);
	c->color = Orange;

	points.first = pos;
	c->SetPos(pos.x, pos.y, pos.z);

	circuit_points.add(points);
}

void CircuitsManager::CreateCilinder(const vec3 init, int radius, int h, int angle)
{
	/*Cylinder cilinder(radius, h);
	cilinder.color = Orange;
	cilinder.SetPos(init.x, init.y, init.z);
	cilinder.SetRotation(angle, vec3(0, 1, 0));

	pieces.PhysBodies.PushBack(App->physics->AddBody(cilinder, 0.0f, this));
	cilinders.add(cilinder);*/
}

void CircuitsManager::CreateHammer(const vec3 posA, const vec3 posB, int velocity, int max_speed)
{
	circuitConstraints piece1;
	Cube* c = new Cube(3, 3, 3);
	c->color = Orange;
	c->SetPos(posA.x, posA.y, posA.z);
	piece1.PhysBody = App->physics->AddBody(*c, 0, App->scene_intro);
	piece1.PrimBody = c;
	piece1.hinge = nullptr;
	circuit_constraints.add(piece1);

	circuitConstraints piece2;
	Cube* c2 = new Cube(10, 3, 4);
	c2->color = Orange;
	c2->SetPos(posB.x, posB.y, posB.z);
	piece2.PhysBody = App->physics->AddBody(*c2, 30, App->scene_intro);
	piece2.PrimBody = c2;
	piece2.hinge = nullptr;

	Cube* c3 = new Cube(10, 3, 4);
	c3->color = Orange;
	c3->SetPos(posB.x + 1, posB.y, posB.z);
	piece2.Sensor = App->physics->AddBody(*c3, 30, App->scene_intro, true);
	piece2.Sensor->type = pb_hammer;
	piece2.hinge = nullptr;

	int dist = piece1.PrimBody->transform.translation().y - piece2.PrimBody->transform.translation().y;

	piece2.hinge = App->physics->AddConstraintHinge(*piece1.PhysBody, *piece2.PhysBody, vec3(0, 0, 0), vec3(0, dist, 0), vec3(0, 0, 1), vec3(0, 0, 1));

	piece2.hinge->enableAngularMotor(true, velocity, max_speed);

	circuit_constraints.add(piece2);
}

void CircuitsManager::JoinCircuitPoints()
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

		// -----------

		// Ground --
		vec3 distance_vec = circuit_points[i + 1].first - circuit_points[i].first;

		float distance = length(distance_vec);

		Cube* c = new Cube(5, 0.5f, distance);
		c->color = Orange;

		c->SetRotation(-angleV, vec3(1, 0, 0));

		c->SetPos((circuit_points[i].first.x + distance_vec.x / 2), circuit_points[i].first.y + distance_vec.y / 2, circuit_points[i].first.z + distance_vec.z / 2);

		circuitPieces pieces;
		pieces.PrimBody = c;
		pieces.PhysBody = App->physics->AddBody(*c, 0.0f, App->scene_intro);

		circuit_pieces.add(pieces);
		// -----------
	}

	circuit_points.clear();
}

void CircuitsManager::CreateCheckpoint(const vec3 init, int height)
{
	Cube* c = new Cube(5, height, 0.5f);
	c->color = Black;
	c->SetPos(init.x, init.y, init.z);

	Cube* visual = new Cube(1, 3, 1);
	visual->color = White;
	visual->SetPos(init.x + 4, init.y, init.z);

	checkpoints cp;
	cp.pos = init;
	cp.PhysBody = App->physics->AddBody(*c, 0, App->scene_intro, true);
	cp.PhysBody->type = pb_checkpoint;
	cp.PrimBody = c;
	cp.visual = visual;
	check_points.add(cp);
}

// Sets initial values for the checkpoints
void CircuitsManager::InitCheckPoints()
{
	if (check_points[0].PrimBody != nullptr)
	{
		vec3 pos = check_points[0].pos;
		App->player->vehicle->SetPos(pos.x, pos.y, pos.z);
		current_checkpoint = 0;
		max_checkpoint = 0;
	}
}

// Move arround checkpoints and color
void CircuitsManager::MoveAroundCheckPoints()
{
	if (!finished)
	{
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ReturnToLastCheckpoint();
		}

		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
		{
			if (current_checkpoint > 0)
			{
				current_checkpoint -= 1;

				vec3 new_pos;
				new_pos.x = check_points[current_checkpoint].pos.x;
				new_pos.y = check_points[current_checkpoint].pos.y;
				new_pos.z = check_points[current_checkpoint].pos.z;

				// Reset all car motion
				App->player->ResetCarMotion();

				// Set pos
				App->player->vehicle->SetPos(new_pos.x, new_pos.y, new_pos.z);
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		App->circuits->SetCircuit(current_circuit);
	}
}

void CircuitsManager::ReturnToLastCheckpoint()
{
	vec3 new_pos;
	new_pos.x = check_points[current_checkpoint].pos.x;
	new_pos.y = check_points[current_checkpoint].pos.y;
	new_pos.z = check_points[current_checkpoint].pos.z;

	// Reset all car motion
	App->player->ResetCarMotion();

	// Set pos
	App->player->vehicle->SetPos(new_pos.x, new_pos.y, new_pos.z);
}

// Update farest checkpoint
void CircuitsManager::Check_CheckPoints(PhysBody3D * body)
{
	for (int i = 0; i < check_points.count(); i++)
	{
		if (check_points[i].PhysBody == body)
		{
			if (i > max_checkpoint)
			{
				App->audio->PlayFx(App->scene_intro->checkpoint_fx);
				max_checkpoint = i;
				current_checkpoint = i;
			}
			else if (i > current_checkpoint)
			{
				current_checkpoint = i;
			}
		}

		if (i <= max_checkpoint)
			check_points[i].visual->color = Green;
		else
			check_points[i].visual->color = Red;
	}
}

void CircuitsManager::Check_ScoreDots(PhysBody3D * body)
{
	for (int i = 0; i < score_dots.count(); i++)
	{
		if (score_dots[i].PhysBody == body)
		{
			if (taken_score_dots + 1 == i)
			{
				taken_score_dots = i;
			}
		}

		if (i <= taken_score_dots)
			score_dots[i].visual->color = Green;
		else
			score_dots[i].visual->color = Grey;
	}
}

void CircuitsManager::CreateScoreDots(const vec3 init, int height)
{
	Cube* c = new Cube(0.6f, height, 0.6f);
	c->color = Black;
	c->SetPos(init.x, init.y, init.z);

	Cube* visual = new Cube(0.6f, 0.6f, 0.6f);
	visual->color = Grey;
	visual->SetPos(init.x, init.y, init.z);

	scoreDots cp;
	cp.pos = init;
	cp.PhysBody = App->physics->AddBody(*c, 0, App->scene_intro, true);
	cp.PhysBody->type = pb_scoredot;
	cp.PrimBody = c;
	cp.visual = visual;
	score_dots.add(cp);
}

void CircuitsManager::InitScoreDots()
{
	taken_score_dots = -1.0f;
	dots_rotation = 0;
}

void CircuitsManager::ChangeTitle()
{
	if (!finished)
	{
		char title[120];
		float time = (App->circuits->timer->Read() / 1000);

		if (taken_score_dots == score_dots.count() - 1 && started)
		{
			sprintf_s(title, "Circuit %d completed. Time: %.3f sec     | R to reestart |  | NUMBERS to change circuit |", current_circuit, time - 3);
			started = false;
			finished = true;
		}
		else if (time < 3 && !started)
		{
			sprintf_s(title, "Time to start: %2.f", 3 - time);
			started = false;
		}
		else
		{
			sprintf_s(title, "Current time: %.3f  Collected points %.0f/%d     | SPACE to return to the last checkpoint |", time - 3, taken_score_dots + 1, score_dots.count());
			started = true;
		}

		App->window->SetTitle(title);
	}
}
