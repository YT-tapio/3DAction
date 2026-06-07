#include<memory>
#include<string>
#include"DxLib.h"
#include"status_holder_interface.h"
#include"status.h"
#include"status_container.h"

IStatusHolder::~IStatusHolder()
{

}

std::shared_ptr<StatusContainer> IStatusHolder::GetStatusContainer()
{
	return nullptr;
}