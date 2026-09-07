#pragma once

class ObjectBase;

template <typename T>
class ObjectPoolBase
{
public:

	ObjectPoolBase()
	{

	}

	virtual ~ObjectPoolBase() = default;

	virtual void Init()
	{
		for (auto& object : objects_)
		{
			object->Init();
		}
	}
		
	virtual void Update()
	{
		for (auto& object : objects_)
		{
			if (object->GetIsActive())
			{
				object->Update();
			}
		}
	}

protected:
	
	std::shared_ptr<T> Get()
	{
		for (auto& object : objects_)
		{
			// アクティブ状態ではないものを渡す。
			if (!object->GetIsActive())
			{
				return object;
			}
		}
		return nullptr;
	}

protected:

	std::vector<std::shared_ptr<T>> objects_;

private:



};