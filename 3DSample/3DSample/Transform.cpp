#include "Transform.h"

Framework::Transform::Transform()
{
}

Framework::Transform::Transform(Vector3 arg_position, Vector3 arg_rotation, Vector3 arg_scale)
	:localPosition(arg_position), rotation(arg_rotation), scale(arg_scale) {}

Framework::Transform::Transform(Vector3 arg_position) : localPosition(arg_position)
{
}

Framework::Matrix4x4 Framework::Transform::ToMatrix()
{
	Matrix4x4 output =
		DirectX::XMMatrixTranspose(GetLocalMatrix());

	return output;
}

Framework::Matrix4x4 Framework::Transform::GetLocalMatrix()
{
	Matrix4x4 output =
		DirectX::XMMatrixRotationX(
			DirectX::XMConvertToRadians(rotation.x)
		)*
		DirectX::XMMatrixRotationY(
			DirectX::XMConvertToRadians(rotation.y)
		)*
		DirectX::XMMatrixRotationZ(
			DirectX::XMConvertToRadians(rotation.z)
		) *(
			DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
			DirectX::XMMatrixTranslation(localPosition.x, localPosition.y, localPosition.z));
	if (baseTransform)
		output = DirectX::XMLoadFloat4x4(&output)*DirectX::XMLoadFloat4x4(&(baseTransform->GetLocalMatrix()));
	return output;
}

Framework::Vector3 Framework::Transform::GetPosition()
{
	return Vector3(ToMatrix()._14, ToMatrix()._24, ToMatrix()._34);
}

Framework::Vector3 Framework::Transform::GetRotation()
{
	if (baseTransform == nullptr)
		return rotation;
	else
	{
		auto out = Vector3(rotation.x + baseTransform->rotation.x, rotation.y + baseTransform->rotation.y, rotation.z + baseTransform->rotation.z);
		return out;
	}
}

Framework::Vector3 Framework::Transform::GetScale()
{
	return Vector3(ToMatrix()._11, ToMatrix()._22, ToMatrix()._33);
}

void Framework::Transform::SetBaseTransform(std::shared_ptr<Transform> argParent)
{
	baseTransform = argParent;
	localPosition = localPosition - baseTransform->GetPosition();
}

std::shared_ptr<Framework::Transform> Framework::Transform::GetParent()
{
	return baseTransform->GetThis<Transform>();
}

Framework::Transform::~Transform()
{
}

std::unique_ptr<Framework::Transform> Framework::Transform::GetNutral()
{
	auto outputTrans = std::make_unique<Transform>();
	return std::move(outputTrans);
}
