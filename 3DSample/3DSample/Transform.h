#pragma once
#include"ButiMath.h"
#include"Util.h"
namespace Framework {
	class Transform:public IObject
	{
	public:
		Vector3 localPosition = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
		Transform();
		Transform(Vector3 pos, Vector3 rotate, Vector3 sca);
		Transform(Vector3 pos);
		void Initialize()override {};
		void PreInitialize()override {};
		Matrix4x4 ToMatrix();
		Matrix4x4 GetLocalMatrix();
		Vector3 GetPosition();
		Vector3 GetRotation();
		Vector3 GetScale();
		void SetBaseTransform(std::shared_ptr<Transform> argParent);
		std::shared_ptr<Transform> GetParent();
		~Transform();
		static  std::unique_ptr<Transform> GetNutral();
		std::shared_ptr<Transform> baseTransform = nullptr;
		std::shared_ptr<Transform> GetClone();
	};
}

