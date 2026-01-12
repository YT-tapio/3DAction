#pragma once
#include<iostream>
#include<vector>

class SetObject;

class ObjectSetter
{
public:

	static ObjectSetter& GetInstance()
	{
		static ObjectSetter instance;
		return instance;
	}

	ObjectSetter(const ObjectSetter&) = delete;
	ObjectSetter& operator = (const ObjectSetter&) = delete;
	

	void AddResource(const int& handle, VECTOR* pos, VECTOR* rot, VECTOR* scale);

	void Update();

private:
	
	ObjectSetter() = default;

	std::vector<std::shared_ptr<SetObject>> set_objects_;

};