#include "ParticleEmitter.h"
#include"GameObjectManager.h"
Framework::ParticleEmitter::ParticleEmitter(std::shared_ptr<Transform> arg_transform, ParticleEmitterParameter * arg_p_particleEmitetrParameter, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_transform,arg_manager)
{
	p_particleEmitterParameter = arg_p_particleEmitetrParameter;
	timer = p_particleEmitterParameter->emitSpan;
	sucide = new RelativeTimer(p_particleEmitterParameter->emitterLifeSpan);
	sucide->Start();
}

Framework::ParticleEmitter::~ParticleEmitter()
{
	delete p_particleEmitterParameter;
	delete sucide;
}

bool Framework::ParticleEmitter::OnUpdate()
{
	if (sucide->Update()) {
		SetIsDead(true);
		return true;
	}
	if (timer < 0) {
		timer = p_particleEmitterParameter->emitSpan;
		Emit();
	}
	else
	{
		timer--;
	}
	return true;
}

void Framework::ParticleEmitter::Emit()
{
	size_t emitCount = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minEmitCount, p_particleEmitterParameter->range_maxEmitCount, 1);
	for (int i = 0; i < emitCount; i++) {
		auto velocity = Vector3(ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minVelocity.x, p_particleEmitterParameter->range_maxVelocity.x, 100), ButiRandom::GetRandom(p_particleEmitterParameter->range_minVelocity.y, p_particleEmitterParameter->range_maxVelocity.y, 100), ButiRandom::GetRandom(p_particleEmitterParameter->range_minVelocity.z, p_particleEmitterParameter->range_maxVelocity.z, 100));
		velocity.Normalize();
		auto scale =
			ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minScale, p_particleEmitterParameter->range_maxScale, 10);

		auto rotatex = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minRotation.x, p_particleEmitterParameter->range_maxRotation.x, 1);
		auto rotatey = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minRotation.y, p_particleEmitterParameter->range_maxRotation.y, 1);
		auto rotatez = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minRotation.z, p_particleEmitterParameter->range_maxRotation.z, 1);
		
		auto rotatePx = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minRotatePase.x, p_particleEmitterParameter->range_maxRotatePase.x, 10);
		auto rotatePy = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minRotatePase.y, p_particleEmitterParameter->range_maxRotatePase.y, 10);
		auto rotatePz = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minRotatePase.z, p_particleEmitterParameter->range_maxRotatePase.z, 10);

		auto exPase =ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minExtentionPase, p_particleEmitterParameter->range_maxExtentionPase, 100);

		auto argtransform = ObjectFactory::Create<Transform>(
			transform->GetPosition() +
			velocity * ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minPosFluctuation, p_particleEmitterParameter->range_maxPosFluctuation, 10)
			, Vector3(rotatex, rotatey, rotatez),
			Vector3(scale, scale, scale)
			);

		auto accelation = ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minAccelation, p_particleEmitterParameter->range_maxAccelation, 10);


		auto speed= ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minSpeed, p_particleEmitterParameter->range_maxSpeed, 10);
		
		auto lifespan =
			ButiRandom::GetRandom<int>(p_particleEmitterParameter->range_minLifeSpan, p_particleEmitterParameter->range_maxLifeSpan, 1);

		auto particle =
			ObjectFactory::Create<Particle>(
				p_particleEmitterParameter->graphHandle,
				p_particleEmitterParameter->layer,
				argtransform,
				velocity,
				speed,
				Vector3(rotatePx, rotatePy, rotatePz),
				Vector3(exPase, exPase, exPase),
				accelation,
				Vector3(
					ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minPhisicsForce.x, p_particleEmitterParameter->range_maxPhisicsForce.x, 100),
					ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minPhisicsForce.y, p_particleEmitterParameter->range_maxPhisicsForce.y, 100),
					ButiRandom::GetRandom<float>(p_particleEmitterParameter->range_minPhisicsForce.z, p_particleEmitterParameter->range_maxPhisicsForce.z, 100)),
				lifespan,
				manager
				);
		manager->AddObject(
			particle->GetThis<GameObject>()
		);
	}
}
