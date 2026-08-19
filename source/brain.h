#pragma once
#include<unordered_map>
#include<string>
#include<memory>
#include<vector>
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

	void CreatePlaySceneVirtualCamera(VECTOR* camera_pos, VECTOR* target_pos, std::function<VECTOR()> enemy_center_pos, std::function<VECTOR()> enemy_dir);

	void Update();

	void DeleteVirtualCamera();

	void ChangeCamera(const std::string& request_name);

	void CollisionNotActive();

	void CollisionActive();

	const VECTOR GetVelocity() const;

	const VECTOR GetTargetVelocity() const;

private:
	
	Brain();

	const std::string kTracking = "Tracking";
	const std::string kSphere = "Sphere";

	std::vector<std::string> camera_names_;

	std::string now_camera_;
	std::string before_camera_;

	std::unordered_map<std::string, std::shared_ptr<VirtualCameraBase>> virtual_cameras_;

	VECTOR vel_;
	VECTOR target_vel_;

	bool can_hit_;

};