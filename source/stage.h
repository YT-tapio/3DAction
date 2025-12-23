#pragma once
#include"object_3D.h"
#include"vector_assistant.h"
#include"hit_interface.h"

class RigidBody;

class Stage : public Object3D , public IHit
{
public:

	Stage();

	~Stage() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

	void OnHit(std::shared_ptr<IHit> object) override;

protected:



private:

	std::shared_ptr<RigidBody> rigid_body_;


	void LoadFile();

};