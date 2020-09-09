#pragma once
#include"DrawAll.h"

class Box:public DrawAll<Box>
{
public:
	Box(Graphics& gfx, 
		//随机数
		std::mt19937& rng,
		//均匀分布的随机数
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist
	);
	void Updata(float dt) override;
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	//位置
	float r;//离圆心的距离
	//自转位置
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	//公转世界位置
	float theta;
	float phi;
	float chi;

	//速度
	float droll;//自转
	float dpitch;
	float dyaw; 

	float dtheta;//公转
	float dphi;
	float dchi;
};

