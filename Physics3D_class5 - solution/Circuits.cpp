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

	UpdateCheckPoints();

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
		CreateCircuitPoint({ 0, 25.4f, 61 }, 0);
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
		CreateCircuitPoint({ 0, 63.5f, 262 }, 0);
		CreateCircuitPoint({ 0, 63.5f, 263 }, 0);
		CreateCircuitPoint({ 0, 64, 265 }, 0);
		CreateCircuitPoint({ 0, 64.5f, 266 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 65, 270 }, 0);
		CreateCircuitPoint({ 0, 68, 277 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 65, 284 }, 0);
		CreateCircuitPoint({ 0, 68, 291 }, 0);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 65, 298 }, 0);
		CreateCircuitPoint({ 0, 68, 305 }, 0);

	}

	// Check Points -------------------------

	CreateCheckpoint({ 0, 51, 3 }, 10);
	CreateCheckpoint({ 0, 33, 90 }, 10);
	CreateCheckpoint({ 0, 71.5f, 200 }, 10);

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
	pieces.PhysBody = App->physics->AddBody(*c, 0.0f, App->scene_intro);

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

// Updates current checkpoint, move arround checkpoints and color
void CircuitsManager::UpdateCheckPoints()
{
	// Update farest checkpoint
	mat4x4 pos;
	App->player->vehicle->GetTransform(&pos);
	for (int i = 0; i < check_points.count(); i++)
	{
		if (pos.translation().z >= check_points[i].pos.z && pos.translation().y < check_points[i].pos.y + 10 && pos.translation().y > check_points[i].pos.y - 10)
		{
			if (i > max_checkpoint)
			{
				max_checkpoint = i;
				current_checkpoint = i;
			}
			else if(i > current_checkpoint)
			{
				current_checkpoint = i;
			}
		}

		if (i <= max_checkpoint)
			check_points[i].visual->color = Green;
		else
			check_points[i].visual->color = Red;
	}

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
