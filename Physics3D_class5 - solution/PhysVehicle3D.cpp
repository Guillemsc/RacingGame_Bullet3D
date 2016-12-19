#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
	body->setUserPointer(this);
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btQuaternion q2 = q;	q2.setEulerZYX(45, 0, 0);

	//--------
	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	//--------
	Cube front_forkTube(info.front_forkTube_size.x, info.front_forkTube_size.y, info.front_forkTube_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front_forkTube.transform);
	btVector3 front_FT_offset(info.front_forkTube_offset.x, info.front_forkTube_offset.y, info.front_forkTube_offset.z);
	front_FT_offset = front_FT_offset.rotate(q2.getAxis(), q2.getAngle());

//	front_forkTube.SetRotation(45, vec3(1, 0, 0));

	front_forkTube.transform.M[12] += front_FT_offset.getX();
	front_forkTube.transform.M[13] += front_FT_offset.getY();
	front_forkTube.transform.M[14] += front_FT_offset.getZ();

	//--------
	Cube back_forkTube(info.back_forkTube_size.x, info.back_forkTube_size.y, info.back_forkTube_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back_forkTube.transform);
	btVector3 back_FT_offset(info.back_forkTube_offset.x, info.back_forkTube_offset.y, info.back_forkTube_offset.z);
	back_FT_offset = back_FT_offset.rotate(q.getAxis(), q.getAngle());

	back_forkTube.transform.M[12] += back_FT_offset.getX();
	back_forkTube.transform.M[13] += back_FT_offset.getY();
	back_forkTube.transform.M[14] += back_FT_offset.getZ();

	back_forkTube.SetRotation(-45, vec3(1, 0, 0));
	//--------
	Cube handleBar(info.handleBar_size.x, info.handleBar_size.y, info.handleBar_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&handleBar.transform);
	btVector3 HB_offset(info.handleBar_offset.x, info.handleBar_offset.y, info.handleBar_offset.z);
	HB_offset = HB_offset.rotate(q.getAxis(), q.getAngle());

	handleBar.transform.M[12] += HB_offset.getX();
	handleBar.transform.M[13] += HB_offset.getY();
	handleBar.transform.M[14] += HB_offset.getZ();
	//--------
	Cube front_seat(info.front_seat_size.x, info.front_seat_size.y, info.front_seat_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front_seat.transform);
	btVector3 FS_offset(info.front_seat_offset.x, info.front_seat_offset.y, info.front_seat_offset.z);
	FS_offset = FS_offset.rotate(q.getAxis(), q.getAngle());

	front_seat.transform.M[12] += FS_offset.getX();
	front_seat.transform.M[13] += FS_offset.getY();
	front_seat.transform.M[14] += FS_offset.getZ();
	//--------
	Cube back_seat(info.back_seat_size.x, info.back_seat_size.y, info.back_seat_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back_seat.transform);
	btVector3 BS_offset(info.back_seat_offset.x, info.back_seat_offset.y, info.back_seat_offset.z);
	BS_offset = BS_offset.rotate(q.getAxis(), q.getAngle());

	back_seat.transform.M[12] += BS_offset.getX();
	back_seat.transform.M[13] += BS_offset.getY();
	back_seat.transform.M[14] += BS_offset.getZ();
	//--------

	front_forkTube.Render();
	back_forkTube.Render();
	handleBar.Render();
	front_seat.Render();
	back_seat.Render();


}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}