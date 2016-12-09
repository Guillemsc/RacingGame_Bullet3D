#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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

	App->camera->Move(vec3(20.0f, 30.0f, 5.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Circuit
	CreateCircuitLine({ 0, 0, 0 }, { 0, 0, 30 }, 50);

	return ret;
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

	Cube c;
	c.color = Black;
	c.size = { dim.x, dim.y, dim.z };

	for (uint i = 0; i < interval; ++i) {
		c.color = i % 2 ? Orange : Black;
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
