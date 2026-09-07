#include<string>
#include<unordered_map>
#include"DxLib.h"
#include"model_repository.h"

void ModelRepository::Load()
{
	models_["zako"] = MV1LoadModel("data/model/enemy/zako/Demon_T_Wiezzorek.mv1");
}

const int ModelRepository::GetHandle(const std::string& name) const
{
	auto model = models_.find(name);
	if (model == models_.end()) { return -1; }
	return MV1DuplicateModel(model->second);
}

ModelRepository::ModelRepository()
{

}