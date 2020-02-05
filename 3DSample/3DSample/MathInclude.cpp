//#pragma once
//#include "ButiMath.h"
//
//
//inline Framework::Vector2::Vector2(const DirectX::XMVECTOR other)
//{
//
//	DirectX::XMVECTOR temp = other;
//	DirectX::XMStoreFloat2(this, temp);
//}
//
//inline Framework::Vector2::Vector2(float x, float y)
//{
//	this->x = x;
//	this->y = y;
//}
//
//inline Framework::Vector2::Vector2()
//{
//}
//
//inline Framework::Vector2::~Vector2()
//{
//}
//
//inline float * Framework::Vector2::GetData()
//{
//	float output[2] = { x,y };
//	return output;
//}
//
//inline void Framework::Vector2::GetData(float * out)
//{
//	auto data = GetData();
//	for (int i = 0; i < 2; i++) {
//		out[i] = data[i];
//	}
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator=(const DirectX::XMVECTOR other)
//{
//	DirectX::XMVECTOR temp = other;
//	DirectX::XMStoreFloat2(this, temp);
//	return *this;
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator+=(const Vector2 & vec)
//{
//	*this = *this + vec;
//	return *this;
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator+=(float value)
//{
//	*this = *this + value;
//	return *this;
//}
//
//inline Framework::Vector2  Framework::Vector2::operator+(float value)
//{
//	Vector2 temp(value, value);
//	return (Vector2)XMVectorAdd(*this, temp);
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator-=(const Vector2 & vec)
//{
//	*this = *this - vec;
//	return *this;
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator-=(float value)
//{
//	*this = *this - value;
//	return *this;
//}
//
//inline Framework::Vector2  Framework::Vector2::operator-(float value)
//{
//	Vector2 temp(value, value);
//	return (Vector2)XMVectorSubtract(*this, temp);
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator*=(float value)
//{
//	*this = *this * value;
//	return *this;
//}
//
//inline Framework::Vector2 & Framework::Vector2::operator/=(float value)
//{
//	*this = *this / value;
//	return *this;
//}
//
//inline const Framework::Vector2 Framework::Vector2::operator-() const
//{
//	return Vector2();
//}
//
//inline Framework::Vector2 & Framework::Vector2::Floor(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline Framework::Vector2 & Framework::Vector2::Round(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline Framework::Vector2 & Framework::Vector2::Ceil(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline float Framework::Vector2::Dot(const Vector2 & vec1) const
//{
//	return ((Vector2)DirectX::XMVector2Dot(DirectX::XMVECTOR(*this),vec1)).x;
//}
//
//inline bool Framework::Vector2::isNaN() const
//{
//	return XMVector2IsNaN(*this);
//}
//
//inline bool Framework::Vector2::isInfinite() const
//{
//	return XMVector2IsInfinite(*this);
//}
//
//inline float Framework::Vector2::GetLengthSqr() const
//{
//	return ((Vector2)DirectX::XMVector2LengthSq(DirectX::XMVECTOR(*this))).x;
//}
//
//inline Framework::Vector3::Vector3(const DirectX::XMVECTOR other)
//{
//	DirectX::XMVECTOR temp = other;
//	DirectX::XMStoreFloat3(this, temp);
//}
//
//inline Framework::Vector3::Vector3(float x, float y, float z)
//{
//	this->x = x;
//	this->y = y;
//	this->z = z;
//}
//
//inline Framework::Vector3::Vector3()
//{
//	x = 0;
//	y = 0;
//	z = 0;
//}
//
//inline Framework::Vector3::~Vector3()
//{
//}
//
//inline float * Framework::Vector3::GetData()
//{
//	float output[3] = { x,y,z };
//	return output;
//}
//
//inline void Framework::Vector3::GetData(float * out)
//{
//	auto data = GetData();
//	for (int i = 0; i < 3; i++) {
//		out[i] = data[i];
//	}
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator=(const DirectX::XMVECTOR other)
//{
//	DirectX::XMVECTOR temp = other;
//	DirectX::XMStoreFloat3(this, temp);
//	return *this;
//
//}
//
//inline Framework::Vector3   Framework::Vector3::operator=(const Vector3& other)
//{
//	if (this != &other) {
//		x = other.x;
//		y = other.y;
//		z = other.z;
//	}
//	return *this;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator=(const DirectX::XMFLOAT3 & other)
//{
//	DirectX::XMVECTOR temp = DirectX::XMLoadFloat3(&other);
//	DirectX::XMStoreFloat3(this, temp);
//	return *this;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator+=(const Vector3 & vec)
//{
//	*this = *this + vec;
//	return *this;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator+=(float value)
//{
//	*this = *this + value;
//	return *this;
//}
//
//inline Framework::Vector3 Framework::Vector3::operator+(float value)
//{
//	Vector3 temp(value, value, value);
//	return (Vector3)XMVectorAdd(*this, temp);
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator-=(const Vector3 & vec)
//{
//	*this = *this - vec;
//	return *this;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator-=(float value)
//{
//	*this = *this - value;
//	return *this;
//}
//
//inline Framework::Vector3 Framework::Vector3::operator-(float value)
//{
//	Vector3 temp(value, value, value);
//	return (Vector3)XMVectorSubtract(*this, temp);
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator*=(float value)
//{
//	*this = *this * value;
//	return *this;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator*=(Matrix4x4 value)
//{
//	*this = *this * value;
//	return *this;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator*(Matrix4x4 value) const
//{
//	auto tmp= (Vector3)XMVector3Transform(*this, value);
//	return tmp;
//}
//
//inline Framework::Vector3 & Framework::Vector3::operator/=(float value)
//{
//	*this = *this / value;
//	return *this;
//}
//
//inline const Framework::Vector3 Framework::Vector3::operator-() const
//{
//	Vector3 temp(-1.0f,-1.0f,-1.0f);
//	return (Vector3)XMVectorSubtract(*this, temp);
//}
//
//inline Framework::Vector3 & Framework::Vector3::Floor(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline Framework::Vector3 & Framework::Vector3::Round(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline Framework::Vector3 & Framework::Vector3::Ceil(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline float Framework::Vector3::Dot(const Vector3 & vec1) const
//{
//	return ((Vector3)XMVector3Dot(*this, vec1)).x;
//}
//
//inline Framework::Vector3& Framework::Vector3::Cross(const Vector3 & vec1) 
//{
//	*this= (Vector3)XMVector3Cross(*this, vec1);
//	return *this;
//}
//
//inline bool Framework::Vector3::isNaN() const
//{
//	return XMVector3IsNaN(*this);
//}
//
//inline bool Framework::Vector3::isInfinite() const
//{
//	return XMVector3IsInfinite(*this);
//}
//
//inline float Framework::Vector3::GetLengthSqr() const
//{
//	return ((Vector3)XMVector3LengthSq(*this)).x;
//}
//
//
//inline Framework::Vector4::Vector4(const DirectX::XMVECTOR other)
//{
//	DirectX::XMVECTOR temp = other;
//	DirectX::XMStoreFloat4(this, temp);
//}
//
//inline Framework::Vector4::Vector4(float x, float y, float z, float w)
//{
//	this->x = x;
//	this->y = y;
//	this->z = z;
//	this->w = w;
//}
//
//inline Framework::Vector4::Vector4(const Vector3 & xyz, float w)
//{
//	this->x = xyz.x;
//	this->y = xyz.y;
//	this->z = xyz.z;
//	this->w = w;
//}
//
//inline Framework::Vector4::Vector4()
//{
//	x = 0;
//	y = 0;
//	z = 0;
//	w = 0;
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator=(const DirectX::XMVECTOR & other)
//{
//	DirectX::XMVECTOR temp = other;
//	DirectX::XMStoreFloat4(this, temp);
//	return *this;
//}
//
//inline Framework::Vector4::~Vector4()
//{
//}
//
//inline Framework::Vector2::operator DirectX::XMVECTOR() const
//{
//	DirectX::XMFLOAT2 temp = *this;
//	DirectX::XMVECTOR output = DirectX::XMLoadFloat2(&temp);
//	return output;
//}
//
//inline Framework::Vector3::operator DirectX::XMVECTOR() const
//{
//	DirectX::XMFLOAT3 temp = *this;
//	DirectX::XMVECTOR output = DirectX::XMLoadFloat3(&temp);
//	return output;
//}
//inline Framework::Vector4::operator DirectX::XMVECTOR() const
//{
//	DirectX::XMFLOAT4 temp = *this;
//	DirectX::XMVECTOR output = DirectX::XMLoadFloat4(&temp);
//	return output;
//}
//
//inline  float * Framework::Vector4::GetData()
//{
//	float output[4] = { x,y,z,w };
//	return output;
//}
//
//inline void Framework::Vector4::GetData(float * out)
//{
//	auto data = GetData();
//	for (int i = 0; i < 4; i++) {
//		out[i] = data[i];
//	}
//}
//
//inline float Framework::Vector4::GetLength() const
//{
//	return 0.0f;
//}
//
//inline void Framework::Vector4::Normalize()
//{
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator+=(const Vector4 & vec)
//{
//	*this = *this + vec;
//	return *this;
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator+=(float value)
//{
//	*this = *this + value;
//	return *this;
//}
//
//inline Framework::Vector4 Framework::Vector4::operator+(float value)
//{
//	Vector4 temp(value, value, value, value);
//	return (Vector4)XMVectorAdd(*this, temp);
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator-=(const Vector4 & vec)
//{
//	*this = *this - vec;
//	return *this;
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator-=(float value)
//{
//	*this = *this - value;
//	return *this;
//}
//
//inline Framework::Vector4 Framework::Vector4::operator-(float value)
//{
//	Vector4 temp(value, value, value, value);
//	return (Vector4)XMVectorSubtract(*this, temp);
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator*=(float value)
//{
//	*this = *this * value;
//	return *this;
//}
//
//inline Framework::Vector4 & Framework::Vector4::operator/=(float value)
//{
//	*this = *this / value;
//	return *this;
//}
//
//inline const Framework::Vector4 Framework::Vector4::operator-() const
//{
//	Vector4 temp(1.0f, 1.0f, 1.0f, 1.0f);
//	return (Vector4)XMVectorSubtract(*this, temp);
//}
//
//inline Framework::Vector4 & Framework::Vector4::Floor(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline Framework::Vector4 & Framework::Vector4::Round(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline Framework::Vector4 & Framework::Vector4::Ceil(int len)
//{
//	// TODO: return ステートメントをここに挿入します
//}
//
//inline float Framework::Vector4::Dot(const Vector4 & vec1) const
//{
//	return ((Vector3)XMVector4Dot(*this, vec1)).x;
//}
//
//inline bool Framework::Vector4::isNaN() const
//{
//	return XMVector4IsNaN(*this);
//}
//
//inline bool Framework::Vector4::isInfinite() const
//{
//	return XMVector4IsInfinite(*this);
//}
//
//inline float Framework::Vector4::GetLengthSqr() const
//{
//	return ((Vector3)DirectX::XMVector4LengthSq(DirectX::XMVECTOR(*this))).x;
//}
//
//inline float Framework::Vector3::GetLength() const
//{
//	return ((Vector3)DirectX::XMVector3Length(DirectX::XMVECTOR(*this))).x;
//}
//
//inline void Framework::Vector3::Normalize()
//{
//	*this = DirectX::XMVector3Normalize(DirectX::XMVECTOR(*this));
//}
//
//inline float Framework::Vector2::GetLength() const
//{
//	return ((Vector2)DirectX::XMVector2Length(DirectX::XMVECTOR(*this))).x;
//}
//
//inline void Framework::Vector2::Normalize()
//{
//	*this = DirectX::XMVector2Normalize(DirectX::XMVECTOR(*this));
//}
//
//inline Framework::Matrix4x4::Matrix4x4()
//{
//}
//
//inline Framework::Matrix4x4::Matrix4x4(const DirectX::XMMATRIX other)
//{
//	DirectX::XMMATRIX tmp = other;
//	DirectX::XMStoreFloat4x4(this, tmp);
//}
//
//inline Framework::Matrix4x4 & Framework::Matrix4x4::operator=(const DirectX::XMMATRIX & other)
//{
//	auto tmp = other;
//	DirectX::XMStoreFloat4x4(this, tmp);
//	return *this;
//}
//
//inline Framework::Matrix4x4::operator DirectX::XMMATRIX() const
//{
//	auto tmp = *this;
//	auto output = DirectX::XMLoadFloat4x4(&tmp);
//	return output;
//}
//
//inline Framework::Matrix4x4 & Framework::Matrix4x4::Identify()
//{
//	*this = (Matrix4x4)DirectX::XMMatrixIdentity();
//	return *this;
//}
//
//inline Framework::Matrix4x4::~Matrix4x4()
//{
//}
//
//inline double Framework::MathHelper::Ceil(double dSrc, int iLen)
//{
//	double	dRet;
//
//	dRet = dSrc * pow(10.0, iLen);
//	dRet = (double)(int)(dRet + 0.9);
//
//	return dRet * pow(10.0, -iLen);
//}
//
//inline double Framework::MathHelper::Floor(double dSrc, int iLen)
//{
//	double dRet;
//
//	dRet = dSrc * pow(10.0, iLen);
//	dRet = (double)(int)(dRet);
//
//	return dRet * pow(10.0, -iLen);
//}
//
//inline double Framework::MathHelper::Round(double dSrc, int iLen)
//{
//	double	dRet;
//
//	dRet = dSrc * pow(10.0, iLen);
//	dRet = (double)(int)(dRet + 0.5);
//
//	return dRet * pow(10.0, -iLen);
//}
//template<typename T>
//inline T Framework::MathHelper::GetMaximum(const T & v1, const T & v2) {
//	return v1 > v2 ? v1 : v2;
//}
//
//template<typename T>
//inline T Framework::MathHelper::GetMinimum(const T & v1, const T & v2) {
//	return v1 < v2 ? v1 : v2;
//}
//
//inline Framework::Vector3 Framework::Calculater::Cross(const Vector3 & vec0, const Vector3 & vec1)
//{
//	return (Vector3)XMVector3Cross(vec0, vec1);
//}
//
//inline Framework::Vector2 Framework::Calculater::Cross(const Vector2 & vec0, const Vector2 & vec1)
//{
//	return (Vector2)XMVector2Cross(vec0, vec1);
//}
//
//inline Framework::Vector4 Framework::Calculater::Cross(const Vector4 & vec0, const Vector4 & vec1, const Vector4 & vec2) {
//	return (Vector2)XMVector2Cross(vec0, vec1);
//}
