#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	VehicleInfo moto;
	
	//Moto properties
	moto.front_forkTube_size.Set(0.15f, 0.15f, 1);
	moto.front_forkTube_offset.Set(0, 0.25f, 0.65f);
	moto.back_forkTube_size.Set(0.15f, 0.15f, 1);
	moto.back_forkTube_offset.Set(0, 0, -0.65f);
	moto.front_seat_size.Set(0.5f, 0.25f, 0.65f);
	moto.front_seat_offset.Set(0, 0.30f, -0.05f);
	moto.back_seat_size.Set(0.5f, 0.25f, 0.65f);
	moto.back_seat_offset.Set(0, 0.40f, -0.6f);
	moto.back_seat_colored_size.Set(0.25f, 0.25f, 0.55f);
	moto.back_seat_colored_offset.Set(0, 0.45f, -0.65f);
	moto.handleBar_size.Set(0.5f, 0.05f, 0.05f);
	moto.handleBar_offset.Set(0, 0.65f, 0.25f);
	moto.chassis_size.Set(0.5f, 1, 2.75f);
	moto.chassis_offset.Set(0.08f, 1.0f, 0);
	//Man properties
	moto.torso_size.Set(0.25f, 0.7f, 0.4f);
	moto.torso_offset.Set(0, 0.75f, -0.15f);
	moto.biceps1_size.Set(0.1f, 0.6f, 0.1f);
	moto.biceps1_offset.Set(0.15f, 0.85f, 0.05f);
	moto.biceps2_size.Set(0.1f, 0.6f, 0.1f);
	moto.biceps2_offset.Set(-0.15f, 0.85f, 0.05f);
	moto.head_size = 0.25f;
	moto.head_offset.Set(0, 1.35f, -0.15f);

	moto.mass = 700.0f; // 700
	moto.suspensionStiffness = 130.88f; // 130
	moto.suspensionCompression = 40.8f; // 130
	moto.suspensionDamping = 999; // 999
	moto.maxSuspensionTravelCm = 40.0f; // 1000
	moto.frictionSlip = 500.5f; // 500
	moto.maxSuspensionForce = 50000.0f; // 30000

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.4f;
	float wheel_width = 0.1f;
	float suspensionRestLength = 1.4f;

	float half_width = moto.chassis_size.x*0.5f;
	float half_length = moto.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	moto.num_wheels = 2;
	moto.wheels = new Wheel[2];
	
	//Front Wheel
	moto.wheels[0].connection.Set(half_width*wheel_width, connection_height, half_length - wheel_radius);
	moto.wheels[0].direction = direction;
	moto.wheels[0].axis = axis;
	moto.wheels[0].suspensionRestLength = suspensionRestLength;
	moto.wheels[0].radius = wheel_radius;
	moto.wheels[0].width = wheel_width;
	moto.wheels[0].front = true;
	moto.wheels[0].drive = true;
	moto.wheels[0].brake = false;
	moto.wheels[0].steering = true;

	//Back Wheel
	moto.wheels[1].connection.Set(half_width*wheel_width, connection_height, -half_length + wheel_radius);
	moto.wheels[1].direction = direction;
	moto.wheels[1].axis = axis;
	moto.wheels[1].suspensionRestLength = suspensionRestLength;
	moto.wheels[1].radius = wheel_radius;
	moto.wheels[1].width = wheel_width;
	moto.wheels[1].front = false;
	moto.wheels[1].drive = false;
	moto.wheels[1].brake = true;
	moto.wheels[1].steering = false;

	vehicle = App->physics->AddVehicle(moto, App->scene_intro);
	vehicle->SetPos(0, 65, 2);
	vehicle->type = pb_vehicle;
	vehicle->body->setLinearFactor(btVector3(0, 1, 1));
	vehicle->body->setAngularFactor(btVector3(1, 0, 0));

	App->camera->Follow(vehicle, 15, 15, 8, 5);

	starting_camera_distance = App->camera->camera_distance;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	SetCameraDistance(dt);

	if (App->circuits->started)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if((MAX_ACCELERATION - (abs(vehicle->GetKmh()) * ((5.0f)*abs(vehicle->GetKmh())))) > 0)
				acceleration = (MAX_ACCELERATION - (abs(vehicle->GetKmh()) * ((5.0f)*abs(vehicle->GetKmh())))); // 5.4
		}
		else if (vehicle->GetKmh() > 0)
		{
			brake = BRAKE_POWER * 0.4;
		}


		btVector3 torque = App->player->vehicle->body->getAngularVelocity();

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (torque.getX() > -4)
				App->player->vehicle->body->setAngularVelocity(btVector3(torque.getX() - (12.55f * dt), torque.getY(), torque.getZ()));
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (torque.getX() < 4)
				App->player->vehicle->body->setAngularVelocity(btVector3(torque.getX() + (12.55f * dt), torque.getY(), torque.getZ()));
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			brake = BRAKE_POWER;
		}
	}
	

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Brake(brake);
	vehicle->Render();

	return UPDATE_CONTINUE;
}

void ModulePlayer::SetCameraDistance(float dt)
{
	float dist = App->camera->camera_distance;
	float movement = 0.52f * dt;

	if (starting_camera_distance + abs(vehicle->GetKmh() * 0.2f) > dist + 5)
	{
		if(dist < 25)
			App->camera->camera_distance += movement;
	}
	else if(App->camera->camera_distance - movement > starting_camera_distance - 5)
	{
		if(dist > starting_camera_distance)
			App->camera->camera_distance -= movement * 2;
	}
}

void ModulePlayer::ResetCarMotion()
{
	// Reestart angle
	btTransform startTransform;
	startTransform.setIdentity();
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	vehicle->body->setMotionState(myMotionState);
	// --------------

	// Reestart velocity
	vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
	vehicle->body->setAngularVelocity(btVector3(0, 0, 0));

	// Fix angles
	vehicle->body->setLinearFactor(btVector3(0, 1, 1));
	vehicle->body->setAngularFactor(btVector3(1, 0, 0));
}

void ModulePlayer::Crash()
{
	App->player->vehicle->body->setLinearFactor(btVector3(1, 1, 1));
	App->player->vehicle->body->setAngularFactor(btVector3(1, 1, 1));
}

float ModulePlayer::abs(float number)
{
	if (number < 0)
		number = -number;
	return number;
}



