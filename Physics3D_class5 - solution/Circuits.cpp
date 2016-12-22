#include "Globals.h"
#include "Circuits.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Timer.h"
#include <stdio.h>

#define NUMBER_OF_CIRCUITS 4

CircuitsManager::CircuitsManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

CircuitsManager::~CircuitsManager()
{
	//delete timer;
}

bool CircuitsManager::Start()
{
	started = false;
	finished = false;
	choose_level = true;

	for (int i = 0; i < NUMBER_OF_CIRCUITS; i++)
		better_times.add(0.0f);

	return true;
}

update_status CircuitsManager::Update(float dt)
{
	// Circuit render
	for (int i = 0; i < circuit_pieces.count(); i++)
	{
		if (circuit_pieces[i].PrimBody != nullptr && circuit_pieces[i].PhysBody->type != pb_die_sensor)
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
		circuit_constraints[i].PhysBody2->GetTransform(&(circuit_constraints[i].PrimBody2->transform));

		if (circuit_constraints[i].Sensor != nullptr)
		{
			mat4x4 m;
			circuit_constraints[i].PhysBody2->GetTransform(&m);
			m[12] -= 5;

			circuit_constraints[i].Sensor->SetTransform(&m);
		}
		circuit_constraints[i].PrimBody2->Render();
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

	current_circuit = i;
	started = false;
	finished = false;
	choose_level = false;
	timer = new Timer();

	switch (i)
	{
	case 1:
		Circtuit1();
		break;
	case 2:
		Circtuit2();
		break;
	case 3:
		Circtuit3();
		break;
	case 4:
		Circtuit4();
		break;
	}

	App->player->ResetCarMotion();

	InitCheckPoints();
	InitScoreDots();
}

void CircuitsManager::Circtuit1()
{
	// Initial Rect
	{
		CreateCircuitPoint({ 0, 53, 0 }, 5);
		CreateCircuitPoint({ 0, 50, 0 }, 5);
		CreateCircuitPoint({ 0, 50, 10 }, 5);
	}

	// Down
	{
		CreateCircuitPoint({ 0, 49.5f, 12 }, 5);
		CreateCircuitPoint({ 0, 48.5f, 14 }, 5);
		CreateCircuitPoint({ 0, 47, 16 }, 5);
		CreateCircuitPoint({ 0, 25, 45 }, 5);
	}
	// Rise
	{
		CreateCircuitPoint({ 0, 24, 47 }, 5);
		CreateCircuitPoint({ 0, 23.2f, 49 }, 5);
		CreateCircuitPoint({ 0, 22.7f, 51 }, 5);
		CreateCircuitPoint({ 0, 22.7f, 53 }, 5);
		CreateCircuitPoint({ 0, 22.9f, 55 }, 5);
		CreateCircuitPoint({ 0, 23.4f, 57 }, 5);
		CreateCircuitPoint({ 0, 24.2f, 59 }, 5);
		CreateCircuitPoint({ 0, 25.5f, 61 }, 5);
	}
	// Space
	JoinCircuitPoints();

	// Reception
	{
		CreateCircuitPoint({ 0, 32, 88 }, 5);
		CreateCircuitPoint({ 0, 31, 92 }, 5);
		CreateCircuitPoint({ 0, 29, 98 }, 5);
		CreateCircuitPoint({ 0, 17, 130 }, 5);
	}
	// Rise 2
	{
		CreateCircuitPoint({ 0, 16.5f, 132 }, 5);
		CreateCircuitPoint({ 0, 16.2f, 134 }, 5);
		CreateCircuitPoint({ 0, 16.2f, 136 }, 5);
		CreateCircuitPoint({ 0, 16.3f, 138 }, 5);
		CreateCircuitPoint({ 0, 16.6f, 140 }, 5);
		CreateCircuitPoint({ 0, 17.1f, 142 }, 5);
		CreateCircuitPoint({ 0, 17.9f, 144 }, 5);
		CreateCircuitPoint({ 0, 19.0f, 146 }, 5);
		CreateCircuitPoint({ 0, 20.7f, 148 }, 5);
		CreateCircuitPoint({ 0, 22.9f, 150 }, 5);

		CreateCircuitPoint({ 0, 52.5f, 176 }, 5);
		CreateCircuitPoint({ 0, 53.4f, 177 }, 5);
		CreateCircuitPoint({ 0, 54.2f, 178 }, 5);
		CreateCircuitPoint({ 0, 54.6f, 179 }, 5);
		CreateCircuitPoint({ 0, 54.8f, 180 }, 5);
	}
	// Spaces zone
	{
		CreateCircuitPoint({ 0, 55.3f, 193 }, 5);
		CreateCircuitPoint({ 0, 55.6f, 195 }, 5);
		CreateCircuitPoint({ 0, 56.0f, 197 }, 5);
		CreateCircuitPoint({ 0, 56.8f, 199 }, 5);

		JoinCircuitPoints();
	}
	// platforms 1-2
	{
		CreateCircuitPoint({ 0, 55, 206 }, 5);
		CreateCircuitPoint({ 0, 55, 216 }, 5);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 53, 225 }, 5);
		CreateCircuitPoint({ 0, 53, 235 }, 5);
	}
	// Down 2
	{
		CreateCircuitPoint({ 0, 53.2f, 237 }, 5);
		CreateCircuitPoint({ 0, 53.6f, 239 }, 5);
		CreateCircuitPoint({ 0, 54.2f, 241 }, 5);
		CreateCircuitPoint({ 0, 55.0f, 243 }, 5);
		CreateCircuitPoint({ 0, 60.5f, 254 }, 5);
		CreateCircuitPoint({ 0, 60.9f, 256 }, 5);

		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 61, 265 }, 5);
		CreateCircuitPoint({ 0, 64, 272 }, 5);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 57.5f, 292 }, 5);
		CreateCircuitPoint({ 0, 54, 310 }, 5);

	}
	//Loop
	{
		CreateCircuitPoint({ 0, 53.9f, 311 }, 5);
		CreateCircuitPoint({ 0, 54.0f, 312 }, 5);
		CreateCircuitPoint({ 0, 54.18f, 313 }, 5);
		CreateCircuitPoint({ 0, 54.4f, 314 }, 5);
		CreateCircuitPoint({ 0, 54.6f, 315 }, 5);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 55, 320 }, 5);
		CreateCircuitPoint({ 0, 55.3f, 322 }, 5);
		CreateCircuitPoint({ 0, 55.6f, 323 }, 5);
		CreateCircuitPoint({ 0, 56.1f, 324 }, 5);
		CreateCircuitPoint({ 0, 56.8f, 325 }, 5);
		CreateCircuitPoint({ 0, 57.7f, 326 }, 5);
		CreateCircuitPoint({ 0, 59.0f, 327 }, 5);
		CreateCircuitPoint({ 0, 61, 328 }, 5);
		CreateCircuitPoint({ 0, 63, 328.5f }, 5);
		CreateCircuitPoint({ 0, 65, 328.5f }, 5);
		CreateCircuitPoint({ 0, 67, 328 }, 5);
		CreateCircuitPoint({ 0, 68.5f, 327 }, 5);
		CreateCircuitPoint({ 0, 70, 325.5f }, 5);
		CreateCircuitPoint({ 0, 71, 324 }, 5);
		CreateCircuitPoint({ 0, 71.5f, 322 }, 5);
		CreateCircuitPoint({ 0, 71.5f, 320 }, 5);
		CreateCircuitPoint({ 0, 71.1f, 318 }, 5);
		CreateCircuitPoint({ 0, 69.8f, 316 }, 5);
		CreateCircuitPoint({ 0, 68.7f, 315 }, 5);
		CreateCircuitPoint({ 0, 67, 314 }, 5);
		CreateCircuitPoint({ 0, 65, 313.5f }, 5);
		CreateCircuitPoint({ 0, 63, 313.6f }, 5);
		CreateCircuitPoint({ 0, 60, 314.2f }, 5);
		JoinCircuitPoints();
	}
	//Space zone 3
	{
		CreateCircuitPoint({ 0, 54.5f, 314.75f }, 5);
		CreateCircuitPoint({ 0, 50, 316 }, 5);
		CreateCircuitPoint({ 0, 48, 317 }, 5);
		CreateCircuitPoint({ 0, 46, 318.5f }, 5);
		CreateCircuitPoint({ 0, 44, 320 }, 5);
		CreateCircuitPoint({ 0, 42.5f, 322 }, 5);
		CreateCircuitPoint({ 0, 41.5f, 324 }, 5);
		CreateCircuitPoint({ 0, 40.5f, 327 }, 5);
		CreateCircuitPoint({ 0, 40, 329 }, 5);
		CreateCircuitPoint({ 0, 40, 350 }, 5);
		CreateCircuitPoint({ 0, 43, 350 }, 5);
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
	CreateHammer(vec3(0, 87.5f, 215), vec3(0, 57.5f, 215), 3.5f, 160.0f);
	CreateHammer(vec3(0, 86.0f, 230), vec3(0, 56.0f, 230), 2, 160.0f);
	// --------------------------------------

	// Dead sensor
	CreateDeadSensor(vec3(0, 10.5f, 200), 100, 500);
	CreateDeadSensor(vec3(0, 35.5f, 270), 100, 150);

	JoinCircuitPoints();
}

void CircuitsManager::Circtuit2()
{
	// start + slope
	{
		CreateCircuitPoint({ 0, 37, 0 }, 5);
		CreateCircuitPoint({ 0, 33, 0 }, 5);
		CreateCircuitPoint({ 0, 33, 16 }, 5);
		CreateCircuitPoint({ 0, 33.2f, 18 }, 2);
		CreateCircuitPoint({ 0, 33.8f, 20 }, 2);
		CreateCircuitPoint({ 0, 34.5f, 21 }, 2);
		CreateCircuitPoint({ 0, 35.7f, 22 }, 2);
		CreateCircuitPoint({ 0, 30.0f, 22 }, 2);
	}

	JoinCircuitPoints();

	//down 1
	{
		CreateCircuitPoint({ 0, 33, 16 }, 5);
		CreateCircuitPoint({ 0, 15, 50 }, 5);
	}
	//jump1
	{
		CreateCircuitPoint({ 0, 14.2f, 52 }, 5);
		CreateCircuitPoint({ 0, 14.0f, 54 }, 5);
		CreateCircuitPoint({ 0, 14.0f, 66 }, 5);
		JoinCircuitPoints();
	}
	//down & rise 1
	{
		CreateCircuitPoint({ 0, 12.25f, 75 }, 5);
		CreateCircuitPoint({ 0, 12.25f, 76 }, 5);
		CreateCircuitPoint({ 0, 12.25, 77 }, 5);
		CreateCircuitPoint({ 0, 12.25f, 78 }, 5);
		CreateCircuitPoint({ 0, 12.25f, 79 }, 5);
		CreateCircuitPoint({ 0, 12.5f, 80 }, 5);
		CreateCircuitPoint({ 0, 13, 81 }, 5);
		CreateCircuitPoint({ 0, 13.5f, 82 }, 5);
		CreateCircuitPoint({ 0, 14, 83 }, 5);
		CreateCircuitPoint({ 0, 14.5f, 84 }, 5);
		CreateCircuitPoint({ 0, 15, 85 }, 5);
		JoinCircuitPoints();
	}
	//rising platfrorm 1
	{
		CreateCircuitPoint({ 0, 17.25f, 102 }, 5);
		CreateCircuitPoint({ 0, 17.5f, 103 }, 5);
		CreateCircuitPoint({ 0, 18, 104 }, 5);
		CreateCircuitPoint({ 0, 18.5f, 105 }, 5);
		CreateCircuitPoint({ 0, 19, 106 }, 5);
		CreateCircuitPoint({ 0, 19.5f, 107 }, 5);
		CreateCircuitPoint({ 0, 20, 108 }, 5);
		JoinCircuitPoints();
	}
	//rising platfrorm 2
	{
		CreateCircuitPoint({ 0, 22.25f, 115 }, 5);
		CreateCircuitPoint({ 0, 22.5f, 116 }, 5);
		CreateCircuitPoint({ 0, 23, 117 }, 5);
		CreateCircuitPoint({ 0, 23.5f, 118 }, 5);
		CreateCircuitPoint({ 0, 24, 119 }, 5);
		CreateCircuitPoint({ 0, 24.5f, 120 }, 5);
		CreateCircuitPoint({ 0, 25, 121 }, 5);
		CreateCircuitPoint({ 0, 25.5f, 122 }, 5);
		CreateCircuitPoint({ 0, 26, 123 }, 5);
		CreateCircuitPoint({ 0, 26.5f, 124 }, 5);
		JoinCircuitPoints();
	}
	//Plane	
	{
		CreateCircuitPoint({ 0, 26.75f, 133 }, 5);
		CreateCircuitPoint({ 0, 24, 145 }, 5);
	}
	//Loop
	{
		CreateCircuitPoint({ 0, 23.9f, 146 }, 5);
		CreateCircuitPoint({ 0, 24.0f, 147 }, 5);
		CreateCircuitPoint({ 0, 24.18f, 148 }, 5);
		CreateCircuitPoint({ 0, 24.5f, 150 }, 5);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 25, 155 }, 5);
		CreateCircuitPoint({ 0, 25.3f, 156 }, 5);
		CreateCircuitPoint({ 0, 25.6f, 157 }, 5);
		CreateCircuitPoint({ 0, 26.1f, 158 }, 5);
		CreateCircuitPoint({ 0, 27.8f, 160 }, 5);
		CreateCircuitPoint({ 0, 28.7f, 161 }, 5);
		CreateCircuitPoint({ 0, 30.0f, 162 }, 5);
		CreateCircuitPoint({ 0, 32, 163 }, 5);
		CreateCircuitPoint({ 0, 34, 163.5f }, 5);
		CreateCircuitPoint({ 0, 36, 163.5f }, 5);
		CreateCircuitPoint({ 0, 38, 163 }, 5);
		CreateCircuitPoint({ 0, 39.5f, 162 }, 5);
		CreateCircuitPoint({ 0, 41, 160.5f }, 5);
		CreateCircuitPoint({ 0, 42, 159 }, 5);
		CreateCircuitPoint({ 0, 42.5f, 157 }, 5);
		CreateCircuitPoint({ 0, 42.5f, 155 }, 5);
		CreateCircuitPoint({ 0, 42.1f, 153 }, 5);
		CreateCircuitPoint({ 0, 40.8f, 151 }, 5);
		CreateCircuitPoint({ 0, 39.7f, 150 }, 5);
		CreateCircuitPoint({ 0, 38, 149 }, 5);
		CreateCircuitPoint({ 0, 36, 148.5f }, 5);
		CreateCircuitPoint({ 0, 34, 148.6f }, 5);
		CreateCircuitPoint({ 0, 33, 148.8f }, 5);
		JoinCircuitPoints();
	}
	//Space zone 1
	{
		CreateCircuitPoint({ 0, 24.5f, 149.65f }, 5);
		CreateCircuitPoint({ 0, 18, 150.5f }, 5);
		CreateCircuitPoint({ 0, 16, 151 }, 5);
		CreateCircuitPoint({ 0, 14, 151.5f }, 5);
		CreateCircuitPoint({ 0, 12, 152 }, 5);
		CreateCircuitPoint({ 0, 8.7f, 153 }, 5);
		CreateCircuitPoint({ 0, 5.7f, 155 }, 5);
		CreateCircuitPoint({ 0, 4.0f, 157 }, 5);
		CreateCircuitPoint({ 0, 3.0f, 159 }, 5);
		CreateCircuitPoint({ 0, 2.5f, 161 }, 5);
		CreateCircuitPoint({ 0, 2.5f, 163 }, 5);
		CreateCircuitPoint({ 0, 2.5f, 173 }, 5);
	}
	//Rising + Jump
	{
		CreateCircuitPoint({ 0, 2.7f, 175 }, 5);
		CreateCircuitPoint({ 0, 3.2f, 177 }, 5);
		CreateCircuitPoint({ 0, 4.2f, 179 }, 5);
		CreateCircuitPoint({ 0, 49.2f, 229 }, 5);
		CreateCircuitPoint({ 0, 50.6f, 231 }, 5);
		CreateCircuitPoint({ 0, 51.4f, 233 }, 5);
		CreateCircuitPoint({ 0, 51.8f, 235 }, 5);
		CreateCircuitPoint({ 0, 51.8f, 237 }, 5);
		CreateCircuitPoint({ 0, 51.8f, 255 }, 5);
		JoinCircuitPoints();
		CreateCircuitPoint({ 0, 51.8f, 250 }, 2);
		CreateCircuitPoint({ 0, 52.0f, 252 }, 2);
		CreateCircuitPoint({ 0, 52.4f, 254 }, 2);
		CreateCircuitPoint({ 0, 52.8f, 255 }, 2);
		CreateCircuitPoint({ 0, 51.8f, 255 }, 2);
		JoinCircuitPoints();
	}
	// Reception + Jump
	{
		CreateCircuitPoint({ 0, 40.7f, 277 }, 5);
		CreateCircuitPoint({ 0, 10.7f, 330 }, 5);
		CreateCircuitPoint({ 0, 9.7f, 333 }, 5);
		CreateCircuitPoint({ 0, 9.2f, 336 }, 5);
		CreateCircuitPoint({ 0, 9.2f, 339 }, 5);
		CreateCircuitPoint({ 0, 9.5f, 342 }, 5);
		CreateCircuitPoint({ 0, 10.4f, 345 }, 5);
		CreateCircuitPoint({ 0, 12.0f, 348 }, 5);
		CreateCircuitPoint({ 0, 14.6f, 351 }, 5);
		CreateCircuitPoint({ 0, 17.9f, 354 }, 5);
		CreateCircuitPoint({ 0, 22.5f, 357 }, 5);
		CreateCircuitPoint({ 0, 28.5f, 360 }, 5);
		JoinCircuitPoints();
	}
	// Reception + Jump
	{
		CreateCircuitPoint({ 0, 28.5f, 392 }, 5);
		CreateCircuitPoint({ 0, 20.5f, 396 }, 5);
		CreateCircuitPoint({ 0, 15.0f, 400 }, 5);
		CreateCircuitPoint({ 0, 12.0f, 403 }, 5);
		CreateCircuitPoint({ 0, 10.0f, 406 }, 5);
		CreateCircuitPoint({ 0, 9.0f, 409 }, 5);
		CreateCircuitPoint({ 0, 9.0f, 414 }, 5);
		CreateCircuitPoint({ 0, 9.2f, 416 }, 5);
		CreateCircuitPoint({ 0, 9.6f, 418 }, 5);
		CreateCircuitPoint({ 0, 10.5f, 420 }, 5);
		CreateCircuitPoint({ 0, 11.7f, 422 }, 5);
		CreateCircuitPoint({ 0, 13.7f, 424 }, 5);
		CreateCircuitPoint({ 0, 16.7f, 426 }, 5);
		JoinCircuitPoints();
	}
	// End
	{
		CreateCircuitPoint({ 0, 29.5f, 446 }, 5);
		CreateCircuitPoint({ 0, 29.5f, 466 }, 5);
		CreateCircuitPoint({ 0, 34.5f, 466 }, 5);
	}
	JoinCircuitPoints();

	// Check Points -------------------------
	CreateCheckpoint({ 0, 34, 4 }, 5);
	CreateCheckpoint({ 0, 28.7f, 134.5f }, 5);
	CreateCheckpoint({ 0, 52.7f, 235.5f }, 15);
	// --------------------------------------

	// Score Creation -----------------------
	CreateScoreDots({ 0, 20.9f, 106 }, 4);
	CreateScoreDots({ 0, 40.9f, 156 }, 4);
	CreateScoreDots({ 0, 53.9f, 255 }, 4);
	CreateScoreDots({ 0, 32.0f, 454.5f }, 4);
	// --------------------------------------

	// Hummer -------------------------------
	CreateHammer(vec3(0, 35.5f, 165), vec3(0, 5.5f, 165), 2, 160.0f);
	CreateHammer(vec3(0, 35.5f, 170), vec3(0, 5.5f, 170), 3, 160.0f);
	// --------------------------------------

	// Dead sensor
	CreateDeadSensor(vec3(0, -0.5f, 200), 100, 500);
}

void CircuitsManager::Circtuit3()
{
	CreateCircuitPoint({ 0, 305.4f, 0 }, 5);
	CreateCircuitPoint({ 0, 300.5f, 0 }, 5);
	CreateCircuitPoint({ 0, 300.5f, 10 }, 5);
	CreateCircuitPoint({ 0, 300.3f, 12 }, 5);
	CreateCircuitPoint({ 0, 299.7f, 14 }, 5);
	CreateCircuitPoint({ 0, 298.9f, 16 }, 5);
	CreateCircuitPoint({ 0, 297.6f, 18 }, 5);
	CreateCircuitPoint({ 0, 295.6f, 20 }, 5);
	JoinCircuitPoints();
	CreateCircuitPoint({ 0, 250.6f, 40 }, 5);
	CreateCircuitPoint({ 0, 150.6f, 100 }, 5);
	CreateCircuitPoint({ 0, 100.6f, 140 }, 5);
	CreateCircuitPoint({ 0, 97.6f, 143 }, 5);
	CreateCircuitPoint({ 0, 95.6f, 146 }, 5);
	CreateCircuitPoint({ 0, 94.6f, 149 }, 5);
	CreateCircuitPoint({ 0, 93.9f, 152 }, 5);
	CreateCircuitPoint({ 0, 93.5f, 158 }, 5);
	CreateCircuitPoint({ 0, 93.5f, 168 }, 5);
	JoinCircuitPoints();
	CreateCircuitPoint({ 0, 63.5f, 285 }, 5);
	CreateCircuitPoint({ 0, 13.5f, 408 }, 5);
	CreateCircuitPoint({ 0, 11.7f, 414 }, 5);
	CreateCircuitPoint({ 0, 11.7f, 444 }, 5);
	CreateCircuitPoint({ 0, 14.7f, 444 }, 5);

	// Check Points -------------------------

	CreateCheckpoint({ 0, 301, 3 }, 5);

	// --------------------------------------

	// Score Creation -----------------------

	CreateScoreDots({ 0, 12, 430 }, 4);

	// --------------------------------------

	// Hummer -------------------------------
	//CreateHammer(vec3(0, 87.5f, 210), vec3(0, 57.5f, 210), 2, 160.0f);

	// --------------------------------------

	// Dead sensor
	CreateDeadSensor(vec3(0, 0.5f, 150), 100, 400);

	JoinCircuitPoints();
}

void CircuitsManager::Circtuit4()
{
	CreateCircuitPoint({ 0, 15.7f, 0 }, 2);
	CreateCircuitPoint({ 0, 10.7f, 0 }, 2);
	CreateCircuitPoint({ 0, 10.7f, 5 }, 2);
	CreateCircuitPoint({ 0, 10.7f, 200 }, 2);
	CreateCircuitPoint({ 0, 14.7f, 200 }, 2);

	// Check Points -------------------------

	CreateCheckpoint({ 0, 12, 3 }, 5);
	CreateCheckpoint({ 0, 12, 45 }, 5);
	CreateCheckpoint({ 0, 12, 75 }, 5);
	CreateCheckpoint({ 0, 12, 100 }, 5);
	CreateCheckpoint({ 0, 12, 135 }, 5);

	// --------------------------------------

	// Score Creation -----------------------

	CreateScoreDots({ 0, 12, 25 }, 5);
	CreateScoreDots({ 0, 12, 30 }, 4);
	CreateScoreDots({ 0, 12, 35 }, 4);
	CreateScoreDots({ 0, 12, 50 }, 4);
	CreateScoreDots({ 0, 12, 55 }, 4);
	CreateScoreDots({ 0, 12, 60 }, 4);
	CreateScoreDots({ 0, 12, 70 }, 4);
	CreateScoreDots({ 0, 12, 80 }, 4);
	CreateScoreDots({ 0, 12, 90 }, 4);
	CreateScoreDots({ 0, 12, 110 }, 4);
	CreateScoreDots({ 0, 12, 115 }, 4);
	CreateScoreDots({ 0, 12, 120 }, 4);
	CreateScoreDots({ 0, 12, 125 }, 4);
	CreateScoreDots({ 0, 12, 145 }, 4);
	CreateScoreDots({ 0, 12, 150 }, 4);
	CreateScoreDots({ 0, 12, 160 }, 4);
	CreateScoreDots({ 0, 12, 165 }, 4);
	CreateScoreDots({ 0, 12, 175 }, 4);
	CreateScoreDots({ 0, 12, 195 }, 4);

	// --------------------------------------

	// Hummer -------------------------------
	CreateHammer(vec3(0, 43.5f, 25), vec3(0, 13.5f, 25), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 30), vec3(0, 13.5f, 30), 3, 600.0f);
	CreateHammer(vec3(0, 43.5f, 35), vec3(0, 13.5f, 35), 5, 600.0f);
	CreateHammer(vec3(0, 43.5f, 50), vec3(0, 13.5f, 50), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 55), vec3(0, 13.5f, 55), 3, 600.0f);
	CreateHammer(vec3(0, 43.5f, 60), vec3(0, 13.5f, 60), 6, 600.0f);
	CreateHammer(vec3(0, 43.5f, 70), vec3(0, 13.5f, 70), 2, 600.0f);
	CreateHammer(vec3(0, 43.5f, 90), vec3(0, 13.5f, 90), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 110), vec3(0, 13.5f, 110), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 115), vec3(0, 13.5f, 115), 2, 600.0f);
	CreateHammer(vec3(0, 43.5f, 120), vec3(0, 13.5f, 120), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 125), vec3(0, 13.5f, 125), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 145), vec3(0, 13.5f, 145), 1, 600.0f);
	CreateHammer(vec3(0, 43.5f, 150), vec3(0, 13.5f, 150), 3, 600.0f);
	CreateHammer(vec3(0, 43.5f, 160), vec3(0, 13.5f, 160), 4, 600.0f);
	CreateHammer(vec3(0, 43.5f, 165), vec3(0, 13.5f, 165), 6, 600.0f);
	CreateHammer(vec3(0, 43.5f, 175), vec3(0, 13.5f, 175), 2, 600.0f);

	// --------------------------------------

	// Dead sensor
	CreateDeadSensor(vec3(0, 5.0f, 3), 100, 400);

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

	for (int i = 0; i < circuit_constraints.count(); i++)
	{
		App->physics->UnloadConstraint(circuit_constraints[i].hinge);
		App->physics->UnloadPhysBody(circuit_constraints[i].PhysBody1);
		App->physics->UnloadPhysBody(circuit_constraints[i].PhysBody2);
		App->physics->UnloadPhysBody(circuit_constraints[i].Sensor);
		delete circuit_constraints[i].PrimBody1;
		delete circuit_constraints[i].PrimBody2;
	}

	circuit_pieces.clear();
	circuit_points.clear();
	circuit_constraints.clear();
	check_points.clear();
	score_dots.clear();
}

void CircuitsManager::CreateCircuitPoint(const vec3 init, int distance_between)
{
	circuitPoints points;

	vec3 pos = init;
	vec3 dim(distance_between, 0.5f, 0.5f);

	Cube* c = new Cube(dim.x, dim.y, dim.z);
	c->color = Orange;

	points.first = pos;
	c->SetPos(pos.x, pos.y, pos.z);

	points.distance_between = distance_between;

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
	circuitConstraints piece;
	Cube* c = new Cube(3, 3, 3);
	c->color = Orange;
	c->SetPos(posA.x, posA.y, posA.z);
	piece.PhysBody1 = App->physics->AddBody(*c, 0, App->scene_intro);
	piece.PrimBody1 = c;
	piece.hinge = nullptr;

	Cube* c2 = new Cube(10, 3, 4);
	c2->color = Red;
	c2->SetPos(posB.x, posB.y, posB.z);
	piece.PhysBody2 = App->physics->AddBody(*c2, 30, App->scene_intro);
	piece.PrimBody2 = c2;
	piece.hinge = nullptr;

	Cube* c3 = new Cube(10, 3, 4);
	c3->color = Orange;
	c3->SetPos(posB.x + 1, posB.y, posB.z);
	piece.Sensor = App->physics->AddBody(*c3, 30, App->scene_intro, true);
	piece.Sensor->type = pb_hammer;
	piece.hinge = nullptr;

	int dist = piece.PrimBody1->transform.translation().y - piece.PrimBody2->transform.translation().y;

	piece.hinge = App->physics->AddConstraintHinge(*piece.PhysBody1, *piece.PhysBody2, vec3(0, 0, 0), vec3(0, dist, 0), vec3(0, 0, 1), vec3(0, 0, 1));

	piece.hinge->enableAngularMotor(true, velocity, max_speed);

	circuit_constraints.add(piece);
}

void CircuitsManager::JoinCircuitPoints()
{
	if (circuit_points.count() > 0)
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

			Cube* c = new Cube(circuit_points[i + 1].distance_between, 0.5f, distance);
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
}

void CircuitsManager::CreateDeadSensor(const vec3 init, float x, float y)
{
	circuitPieces pieces;
	Cube* c = new Cube(x, 5, y);

	c->SetPos(init.x, init.y, init.z);
	c->color = Black;

	pieces.PhysBody = App->physics->AddBody(*c, 0, App->scene_intro, true);
	pieces.PhysBody->type = pb_die_sensor;
	pieces.PrimBody = c;

	circuit_pieces.add(pieces);
}

void CircuitsManager::CreateCheckpoint(const vec3 init, int height)
{
	Cube* c = new Cube(5, height, 0.5f);
	c->color = Black;
	c->SetPos(init.x, (init.y + height/2) - 3, init.z);

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
	if (check_points.count() > 0)
	{
		if (check_points[0].PrimBody != nullptr)
		{
			vec3 pos = check_points[0].pos;
			App->player->vehicle->SetPos(pos.x, pos.y, pos.z);
			current_checkpoint = 0;
			max_checkpoint = 0;
		}
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
	if (!finished && !choose_level)
	{
		char title[120];
		float time = (App->circuits->timer->Read() / 1000);

		if (taken_score_dots == score_dots.count() - 1 && started)
		{
			App->audio->PlayFx(App->scene_intro->level_finished_fx, 0, -1);

			if (time - 3 < better_times[current_circuit - 1] || better_times[current_circuit - 1] == 0)
				better_times[current_circuit - 1] = time - 3;

			sprintf_s(title, "Circuit %d completed. Time: %.3f sec  Better: %.3f   | R to reestart |  | NUMBERS to change circuit |", current_circuit, time - 3, better_times[current_circuit - 1]);
			started = false;
			finished = true;
		}
		else if (time < 3 && !started)
		{
			sprintf_s(title, "Time to start: %2.f    Better time on this circuit: %.3f", 3 - time, better_times[current_circuit - 1]);
			started = false;
		}
		else
		{
			sprintf_s(title, "Current time: %.3f  Better: %.3f  Collected points %.0f/%d     | SPACE to return to the last checkpoint |", time - 3, better_times[current_circuit - 1], taken_score_dots + 1, score_dots.count());
			started = true;
		}

		App->window->SetTitle(title);
	}
	else if(choose_level)
	{
		char title[120];
		sprintf_s(title, "Welcome! Press the numbers [1], [2], [3] or [4] any time to change levels");
		App->window->SetTitle(title);
	}
}
