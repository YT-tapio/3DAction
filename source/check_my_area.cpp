#include<vector>
#include<memory>
#include<string>
#include"check_my_area.h"
#include"object_base.h"
#include"rigid_body.h"
#include"collider_base.h"
#include"physics.h"
#include"player.h"

CheckMyArea::CheckMyArea(std::shared_ptr<ColliderBase> coll,VECTOR* pos)
{
	rigid_body_ = std::make_shared<RigidBody>(coll, pos, FALSE, TRUE, 0, 1.f);
}

CheckMyArea::~CheckMyArea()
{
	my_area_objects_.clear();
}

void CheckMyArea::Init()
{
	rigid_body_->Init(weak_from_this());
	Physics::GetInstance().AddBody(rigid_body_);
	my_area_objects_.clear();
}

void CheckMyArea::Debug()
{
	rigid_body_->Debug();
}

void CheckMyArea::OnCollisionEnter(std::shared_ptr<IPhysicsEventReceiver> object)
{
	
	// object‚É•ÏŠ·
	auto obj = std::dynamic_pointer_cast<ObjectBase>(object);

	// ‚æ‚¤‚»
	bool is_push = TRUE;

	//•ÏŠ·‚Å‚«‚é‚È‚ç
	if (obj != nullptr)
	{
		//printfDx("•ÏŠ·¬Œ÷\n");
		std::weak_ptr<ObjectBase> weak_obj = obj;

		for (const auto& my_object : my_area_objects_)
		{
			if (my_object.lock() == weak_obj.lock())
			{
				//‚æ‚¤‚»‚ğ‚Â‚¢‚©‚µ‚È‚¢@
				//printfDx("—v‘f‚ğ’Ç‰Á‚µ‚È‚¢\n");
				is_push = FALSE;
			}

		}
		if (is_push)
		{
			// —v‘f‚Ì’Ç‰Á
			//printfDx("‚Â‚¢‚©\n");
			my_area_objects_.push_back(weak_obj);
		}
	}
	//printfDx("%d",my_area_objects_.size());
}

void CheckMyArea::OnCollisionStay(std::shared_ptr<IPhysicsEventReceiver> object)
{

}

void CheckMyArea::OnCollisionExit(std::shared_ptr<IPhysicsEventReceiver> object)
{
	 
	// object‚ª‰½ŒÂ–Ú‚É•Û‘¶‚³‚ê‚Ä‚Ì‚©
	int num = 0;
	bool is_erase = FALSE;	// Á‹‚·‚é‚©‚Ç‚¤‚©

	auto obj = std::dynamic_pointer_cast<ObjectBase>(object);

	if (obj != nullptr)
	{
		std::weak_ptr<const ObjectBase> weak_obj = obj;

		for (const auto& my_object : my_area_objects_)
		{
			//weak_ptr‚Í”ä‚×‚é‚±‚Æ‚ª‚Å‚«‚È‚¢
			if (my_object.lock() == weak_obj.lock()) 
			{
				// n”Ô–Ú‚Ì—v‘f‚ğíœ
				my_area_objects_.erase(my_area_objects_.begin() + num);
				// printfDx("Á‹\n");
				break;
			}
			num++;
		}
	}
}

std::vector<std::weak_ptr<ObjectBase>> CheckMyArea::GetMyAreaObject()
{
	return my_area_objects_;
}

std::shared_ptr<RigidBody> CheckMyArea::GetRigidBody()
{
	return rigid_body_;
}

const VECTOR CheckMyArea::GetPos() const
{
	return rigid_body_->GetPosition();
}