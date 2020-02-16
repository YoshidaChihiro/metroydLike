#pragma once
#include"Particle.h"
#include"RelativeTimer.h"
namespace Framework {
	struct ParticleEmitterParameter {

		Vector3 range_maxVelocity = Vector3(1.0f, 1.0f,1.0f);//進行方向の最大値、正規化は内部でする
		Vector3 range_maxPhisicsForce = Vector3();//重力や風の影響などの最大値
		float range_maxExtentionPase = 0;//拡大していくペースの最大値
		Vector3 range_maxRotation = Vector3(0,0,0);//最初の回転の最大値
		float range_maxPosFluctuation = 0;//生成時どれくらいEmitterから離れてるかの揺らぎの最大値
		Vector3 range_maxRotatePase =Vector3(0,0,0);//回転していくペースの最大値
		float range_maxScale = 1.0f;//拡大率の最大値
		float range_maxAccelation = 1.0f;//どれだけ加速していくかの最大値。1より大きいと毎フレーム早くなっていく。1より小さいと逆
		float range_maxSpeed = 1;//速度の最大値
		size_t range_maxEmitCount = 1;//一回の生成での生成量の最大値
		size_t range_maxLifeSpan = 180;//寿命フレームの最大値

		Vector3 range_minVelocity = Vector3(-1.0f, -1.0f,-1.0f);//進行方向の最小値、正規化は内部でする
		Vector3 range_minPhisicsForce = Vector3();//重力や風の影響などの最小値
		float range_minExtentionPase = 0;//拡大していくペースの最小値
		Vector3 range_minRotation = Vector3(0, 0, 0);//最初の回転の最小値
		float range_minPosFluctuation = 0; // 生成時どれくらいEmitterから離れてるかの揺らぎの最小値
		Vector3 range_minRotatePase =Vector3(0,0,0);//回転していくペースの最小値
		float range_minAccelation = 1.0f;//拡大率の最小値
		float range_minScale = 1.0f;//どれだけ加速していくかの最小値。1より大きいと毎フレーム早くなっていく。1より小さいと逆
		float range_minSpeed = 1;//速度の最小値
		size_t range_minEmitCount = 1;//一回の生成での生成量の最小値
		size_t range_minLifeSpan = 10;//寿命フレームの最小値


		int layer = 0.2f;//レイヤ-の指定
		int emitSpan = 10;//何フレームに一回生成を行うか
		int graphHandle = 0;//使う画像のハンドル

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