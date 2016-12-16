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
	moto.chassis_size.Set(0.5f, 1, 2.5f);
	moto.chassis_offset.Set(0.08f, 1.0f, 0);
	moto.mass = 500.0f;
	moto.suspensionStiffness = 15.88f;
	moto.suspensionCompression = 200.0f; // Important
	moto.suspensionDamping = 0.88f;
	moto.maxSuspensionTravelCm = 100.0f;
	moto.frictionSlip = 1000.5;
	moto.maxSuspensionForce = 10000.0f; // Important

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.3f;
	float wheel_width = 0.4f;
	float suspensionRestLength = 1.2f;

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

	vehicle = App->physics->AddVehicle(moto);
	vehicle->SetPos(0, 60, 2);
	vehicle->body->setLinearFactor(btVector3(0, 1, 1));
	vehicle->body->setAngularFactor(btVector3(1, 0, 0));

	App->camera->Follow(vehicle, 15, 15, 10);
	
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

	float turn_change = GetCarTrunCapability();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = (MAX_ACCELERATION - (abs(vehicle->GetKmh()) * (0.1*abs(vehicle->GetKmh()))));
		LOG("%f", MAX_ACCELERATION - (abs(vehicle->GetKmh()) * (0.1*abs(vehicle->GetKmh()))));
	}
	else if (vehicle->GetKmh() > 0)
	{
		acceleration = -MAX_ACCELERATION * 0.6;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->player->vehicle->body->applyTorque(btVector3(-2000, 0, 0));
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->player->vehicle->body->applyTorque(btVector3(2000, 0, 0));
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() > 0)
			acceleration = -MAX_ACCELERATION;
		else {
			acceleration = 0;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vehicle->SetPos(0, 60, 2);
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

float ModulePlayer::GetCarTrunCapability()
{
	float turn_change = turn_degrees;
	turn_change -= (abs(vehicle->GetKmh()) * (0.00009*abs(vehicle->GetKmh())));

	if (turn_change > turn_degrees)
		turn_change = turn_degrees;

	if (turn_change <= 0)
		turn_change = 0.05f;



	return turn_change;
}

float ModulePlayer::abs(float number)
{
	if (number < 0)
		number = -number;
	return number;
}



