#pragma once
#include"virtual_camera_base.h"

class VirtualCameraBase;

class Brain
{
public:

	Brain();

	~Brain();

	void Init();

	void Update();

private:
	
	const std::string kTracking = "";
	// const std::string k

	std::unordered_map<std::string, std::shared_ptr<VirtualCameraBase>> virtual_cameras_;
	std::shared_ptr<VirtualCameraBase> active_camera_;

	VECTOR vel_;
	VECTOR target_vel_;

};