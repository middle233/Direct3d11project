#pragma once
#include"DrawBase.h"

class Box:public DrawBase
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
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
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
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

