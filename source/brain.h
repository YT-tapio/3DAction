#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include"virtual_camera_base.h"

class Player;

class Brain
{
public:

	static Brain& GetInstance()
	{
		static Brain instance;
		return instance;
	}

	Brain(const Brain&) = delete;
	Brain& operator = (const Brain&) = default;

	void Init();

	void CreatePlaySceneVirtualCamera(std::shared_ptr<Player> player, VECTOR* camera_pos, VECTOR* target_pos);

	void Update();

	void DeleteVirtualCamera();

	const VECTOR GetVelocity() const;

	const VECTOR GetTargetVelocity() const;

private:
	
	Brain();

	const std::string kTracking = "Tracking";
	const std::string kSphere = "Sphere";

	std::string now_camera_;

	std::unordered_map<std::string, std::shared_ptr<VirtualCameraBase>> virtual_cameras_;

	VECTOR vel_;
	VECTOR target_vel_;

};