#pragma once
#include"DrawAll.h"

class Box:public DrawAll<Box>
{
public:
	Box(Graphics& gfx, 
		//�����
		std::mt19937& rng,
		//���ȷֲ��������
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist
	);
	void Updata(float dt) override;
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	//λ��
	float r;//��Բ�ĵľ���
	//��תλ��
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	//��ת����λ��
	float theta;
	float phi;
	float chi;

	//�ٶ�
	float droll;//��ת
	float dpitch;
	float dyaw; 

	float dtheta;//��ת
	float dphi;
	float dchi;
};

