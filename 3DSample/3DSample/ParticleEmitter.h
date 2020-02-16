#pragma once
#include"Particle.h"
#include"RelativeTimer.h"
namespace Framework {
	struct ParticleEmitterParameter {

		Vector3 range_maxVelocity = Vector3(1.0f, 1.0f,1.0f);//�i�s�����̍ő�l�A���K���͓����ł���
		Vector3 range_maxPhisicsForce = Vector3();//�d�͂╗�̉e���Ȃǂ̍ő�l
		float range_maxExtentionPase = 0;//�g�債�Ă����y�[�X�̍ő�l
		Vector3 range_maxRotation = Vector3(0,0,0);//�ŏ��̉�]�̍ő�l
		float range_maxPosFluctuation = 0;//�������ǂꂭ�炢Emitter���痣��Ă邩�̗h�炬�̍ő�l
		Vector3 range_maxRotatePase =Vector3(0,0,0);//��]���Ă����y�[�X�̍ő�l
		float range_maxScale = 1.0f;//�g�嗦�̍ő�l
		float range_maxAccelation = 1.0f;//�ǂꂾ���������Ă������̍ő�l�B1���傫���Ɩ��t���[�������Ȃ��Ă����B1��菬�����Ƌt
		float range_maxSpeed = 1;//���x�̍ő�l
		size_t range_maxEmitCount = 1;//���̐����ł̐����ʂ̍ő�l
		size_t range_maxLifeSpan = 180;//�����t���[���̍ő�l

		Vector3 range_minVelocity = Vector3(-1.0f, -1.0f,-1.0f);//�i�s�����̍ŏ��l�A���K���͓����ł���
		Vector3 range_minPhisicsForce = Vector3();//�d�͂╗�̉e���Ȃǂ̍ŏ��l
		float range_minExtentionPase = 0;//�g�債�Ă����y�[�X�̍ŏ��l
		Vector3 range_minRotation = Vector3(0, 0, 0);//�ŏ��̉�]�̍ŏ��l
		float range_minPosFluctuation = 0; // �������ǂꂭ�炢Emitter���痣��Ă邩�̗h�炬�̍ŏ��l
		Vector3 range_minRotatePase =Vector3(0,0,0);//��]���Ă����y�[�X�̍ŏ��l
		float range_minAccelation = 1.0f;//�g�嗦�̍ŏ��l
		float range_minScale = 1.0f;//�ǂꂾ���������Ă������̍ŏ��l�B1���傫���Ɩ��t���[�������Ȃ��Ă����B1��菬�����Ƌt
		float range_minSpeed = 1;//���x�̍ŏ��l
		size_t range_minEmitCount = 1;//���̐����ł̐����ʂ̍ŏ��l
		size_t range_minLifeSpan = 10;//�����t���[���̍ŏ��l


		int layer = 0.2f;//���C��-�̎w��
		int emitSpan = 10;//���t���[���Ɉ�񐶐����s����
		int graphHandle = 0;//�g���摜�̃n���h��

		int emitterLifeSpan = 3;

		Vector4 color;
	};
	class ParticleEmitter :public GameObject {
	public:
		ParticleEmitter(std::shared_ptr<Transform> arg_transform, ParticleEmitterParameter* arg_p_particleEmitetrParameter, std::shared_ptr<GameObjectManager> arg_manager);
		~ParticleEmitter();
		bool OnUpdate()override;
		void Emit();
	private:
		ParticleEmitterParameter* p_particleEmitterParameter;
		int timer = 0;
		RelativeTimer * sucide;
	};

}