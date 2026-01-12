
#include"DxLib.h"

#include"object_setter.h"
#include"set_object.h"

void ObjectSetter::AddResource(const int& handle, VECTOR* pos, VECTOR* rot, VECTOR* scale)
{
	set_objects_.push_back(std::make_shared<SetObject>(handle, pos, rot, scale));
}

void ObjectSetter::Update()
{
	for (auto& obj : set_objects_)
	{
		obj->Update();
	}
}