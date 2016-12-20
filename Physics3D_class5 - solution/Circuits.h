#ifndef __CIRCUITS_H_
#define __CIRCUITS_H_

#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List2.h"

struct PhysBody3D;
class btHingeConstraint;
class Timer;

struct circuitPoints
{
	vec3	 first;
	vec3	 second;
	float	 platform_x;
	float	 platform_y;
};

struct circuitPieces
{
	PhysBody3D*		PhysBody = nullptr;
	Cube*			PrimBody = nullptr;
};

struct checkpoints
{
	vec3			pos;
	Cube*			PrimBody = nullptr;
	PhysBody3D*		PhysBody = nullptr;

	Cube*			visual = nullptr;
};

struct scoreDots
{
	vec3			pos;
	Cube*			PrimBody = nullptr;
	PhysBody3D*		PhysBody = nullptr;

	Cube*			visual = nullptr;
};

struct circuitConstraints
{
	PhysBody3D*		   PhysBody = nullptr;
	PhysBody3D*		   Sensor = nullptr;
	Cube*			   PrimBody = nullptr;
	btHingeConstraint* hinge = nullptr;
};

class CircuitsManager : public Module
{
public:
	CircuitsManager(Application* app, bool start_enabled = true);
	virtual ~CircuitsManager();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void SetCircuit(int i);
	void Check_CheckPoints(PhysBody3D* body);
	void Check_ScoreDots(PhysBody3D* body);

private:

	// Circuits -----------
	void Circtuit1();
	// Circuits -----------

	// Circuit Creation ---
	void DeleteCircuit();
	void CreateCircuitPoint(const vec3 init, int distance_between);
	void CreateCilinder(const vec3 init, int radius, int h, int angle);
	void CreateHammer(const vec3 posA, const vec3 posB, int velocity, int max_speed);
	void JoinCircuitPoints();
	// --------------------

	// Checkpoint ---------
	void CreateCheckpoint(const vec3 init, int height);
	void InitCheckPoints();
	void MoveAroundCheckPoints();
	void ReturnToLastCheckpoint();
	// --------------------

	// ScoreDots ----------
	void CreateScoreDots(const vec3 init, int height);
	void InitScoreDots();
	// --------------------

	void ChangeTitle();

public:
	p2List2<checkpoints>        check_points;

	bool			            started = false;
	bool				        finished = false;

private:
	p2List2<circuitPoints>      circuit_points;
	p2List2<circuitPieces>		circuit_pieces;
	p2List2<circuitConstraints> circuit_constraints;
	p2List2<scoreDots>          score_dots;     

	uint				        current_circuit = 0;

	uint				        current_checkpoint = 0;
	uint				        max_checkpoint = 0;

	float				        taken_score_dots = 0.0f;
	uint				        dots_rotation = 0;

	Timer*				        timer = nullptr;
};
#endif // !__CIRCUITS_H_