#include "Globals.h"
#include "Circuits.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

CircuitsManager::CircuitsManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

CircuitsManager::~CircuitsManager()
{
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
		if(circuit_pieces[i].PrimBody != nullptr)
			circuit_pieces[i].PrimBody->Render();
	}

	// Checkpoints render
	for(int i = 0; i<check_points.count(); i++)
	{
		if (check_points[i].PrimBody != nullptr)
		{
			if(App->physics->debug)
				check_points[i].PrimBody->Render();
			check_points[i].visual->Render();
		}
	}

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

	switch (i)
	{
	case 1:
		Circtuit1();
		break;
	}

	InitCheckPoints();
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
		CreateCircuitPoint({ 0, 54.2f, 178 }, 0);
		CreateCircuitPoint({ 0, 55.0f, 179 }, 0);
		CreateCircuitPoint({ 0, 55.0f, 180 }, 0);
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
		CreateCircuitPoint({ 0, 60, 265 }, 0);
		CreateCircuitPoint({ 0, 63, 272 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 57.5f, 287 }, 0);
		CreateCircuitPoint({ 0, 54, 310 }, 0);

	}
	//Loop
	{
		CreateCircuitPoint({ 0, 54.1f, 311 }, 0);
		CreateCircuitPoint({ 0, 54.35f, 313 }, 0);
		CreateCircuitPoint({ 0, 54.45f, 314 }, 0); 
		CreateCircuitPoint({ 0, 54.5f, 315 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 55, 320 }, 0);
		CreateCircuitPoint({ 0, 55.3f, 322 }, 0);
		CreateCircuitPoint({ 0, 55.7f, 323 }, 0);
		CreateCircuitPoint({ 0, 56.1f, 324 }, 0);
		CreateCircuitPoint({ 0, 57, 325 }, 0);
		CreateCircuitPoint({ 0, 58, 326 }, 0);
		CreateCircuitPoint({ 0, 58, 326 }, 0);
		CreateCircuitPoint({ 0, 59.5f, 327 }, 0); 
		CreateCircuitPoint({ 0, 61, 328 }, 0);
		CreateCircuitPoint({ 0, 63, 328.5f }, 0);
		
	}


	// Check Points -------------------------

	CreateCheckpoint({ 0, 51, 3 }, 5);
	CreateCheckpoint({ 0, 33, 90 }, 13);
	CreateCheckpoint({ 0, 56.5f, 185 }, 10);
	CreateCheckpoint({ 0, 57.5f, 300 }, 10);

	// --------------------------------------

	JoinCircuitPoints();
}

// Free and reset circuit and checkpoint list
void CircuitsManager::DeleteCircuit()
{
	for (int i = 0; i < circuit_pieces.count(); i++)
	{
		delete circuit_pieces[i].PhysBody;
		delete circuit_pieces[i].PrimBody;
	}

	for (int i = 0; i < check_points.count(); i++)
	{
		delete check_points[i].PhysBody;
		delete check_points[i].PrimBody;
	}

	circuit_pieces.clear();
	circuit_points.clear();
	check_points.clear();

	current_checkpoint = 0;
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

	circuitPieces pieces;
	//pieces.PrimBody = c;
	//pieces.PhysBody = App->physics->AddBody(*c, 0.0f, App->scene_intro);

	circuit_points.add(points);
	circuit_pieces.add(pieces);
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
	}
}

// Move arround checkpoints and color
void CircuitsManager::MoveAroundCheckPoints()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
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

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		current_checkpoint = 0;

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

// Update farest checkpoint
void CircuitsManager::Check(PhysBody3D * body)
{
	for (int i = 0; i < check_points.count(); i++)
	{
		if (check_points[i].PhysBody == body)
		{
			if (i > max_checkpoint)
			{
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
