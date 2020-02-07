#pragma once
#include<DirectXMath.h>
#include <memory>
namespace Framework {

	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix4x4;

	struct Matrix4x4 :public DirectX::XMFLOAT4X4
	{
	public:
		inline Matrix4x4() {}
		inline Matrix4x4(const DirectX::XMMATRIX other)
		{
			DirectX::XMMATRIX tmp = other;
			DirectX::XMStoreFloat4x4(this, tmp);
		}
		inline Matrix4x4& operator=(const DirectX::XMMATRIX& other)
		{
			auto tmp = other;
			DirectX::XMStoreFloat4x4(this, tmp);
			return *this;
		}
		inline operator DirectX::XMMATRIX() const
		{
			auto tmp = *this;
			auto output = DirectX::XMLoadFloat4x4(&tmp);
			return output;
		}
		inline Matrix4x4& Identify()
		{
			*this = (Matrix4x4)DirectX::XMMatrixIdentity();
			return *this;
		}
		~Matrix4x4() {}
	};
	struct Vector2 :public DirectX::XMFLOAT2
	{
		inline Vector2(const DirectX::XMVECTOR other)
		{

			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat2(this, temp);
		};

		inline Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		inline Vector2(){}

		inline ~Vector2(){}


		inline  float* GetData()
		{
			float output[2] = { x,y };
			return output;
		}
		inline  void GetData(float* out)
		{
			auto data = GetData();
			for (int i = 0; i < 2; i++) {
				out[i] = data[i];
			}
		}

		inline Vector2& operator=(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat2(this, temp);
			return *this;
		}

		inline Vector2& operator +=(const Vector2& vec)
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector2& operator +=(float value)
		{
			*this = *this + value;
			return *this;
		}

		inline Vector2 operator +(float value)
		{
			Vector2 temp(value, value);
			return (Vector2)XMVectorAdd(*this, temp);
		}

		inline Vector2& operator -=(const Vector2& vec)
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector2& operator -=(float value)
		{
			*this = *this - value;
			return *this;
		}


		inline Vector2 operator -(float value)
		{
			Vector2 temp(value, value);
			return (Vector2)XMVectorSubtract(*this, temp);
		}

		inline Vector2& operator *=(float value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector2& operator /=(float value)
		{
			*this = *this / value;
			return *this;
		}

		inline const Vector2 operator -() const
		{
			return Vector2();
		}


		inline Vector2& Floor(int len)
		{
			// TODO: return ステートメントをここに挿入します
		}

		inline Vector2& Round(int len)
		{
			// TODO: return ステートメントをここに挿入します
		}

		inline Vector2& Ceil(int len)
		{
			// TODO: return ステートメントをここに挿入します
		}

		inline float Dot(const Vector2 & vec1) const
		{
			return ((Vector2)DirectX::XMVector2Dot(DirectX::XMVECTOR(*this), vec1)).x;
		}

		inline bool isNaN() const
		{
			return XMVector2IsNaN(*this);
		}

		inline bool isInfinite() const
		{
			return XMVector2IsInfinite(*this);
		}

		inline float GetLengthSqr() const
		{
			return ((Vector2)DirectX::XMVector2LengthSq(DirectX::XMVECTOR(*this))).x;
		}

		inline operator DirectX::XMVECTOR() const
		{
			DirectX::XMFLOAT2 temp = *this;
			DirectX::XMVECTOR output = DirectX::XMLoadFloat2(&temp);
			return output;
		}

		inline float GetLength() const {
			return ((Vector2)DirectX::XMVector2Length(DirectX::XMVECTOR(*this))).x;
		}

		inline float GetDistance(Vector2& other) const{
			auto i = sqrt((other.x - x)*(other.x - x) + (other.y - y)*(other.y - y));
			return i;
		}

		inline void Normalize()
		{
			*this = DirectX::XMVector2Normalize(DirectX::XMVECTOR(*this));
		}
	};

	struct  Vector3 :public DirectX::XMFLOAT3
	{
		inline Vector3(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat3(this, temp);
		}
		inline Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		inline Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		inline Vector2 GetVector2() {
			return Vector2(x,y);
		}

		inline ~Vector3()
		{
		}
		inline  float* GetData() {
			float output[3] = { x,y,z };
			return output;
		}

		inline  void GetData(float* out)
		{
			auto data = GetData();
			for (int i = 0; i < 3; i++) {
				out[i] = data[i];
			}
		}
		inline Vector3& operator=(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat3(this, temp);
			return *this;

		}

		inline Vector3 operator=(const Vector3& other)
		{
			if (this != &other) {
				x = other.x;
				y = other.y;
				z = other.z;
			}
			return *this;
		}

		inline Vector3& operator=(const DirectX::XMFLOAT3& other)
		{
			DirectX::XMVECTOR temp = DirectX::XMLoadFloat3(&other);
			DirectX::XMStoreFloat3(this, temp);
			return *this;
		}

		inline Vector3& operator +=(const Vector3& vec)
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector3& operator +=(float value)
		{
			*this = *this + value;
			return *this;
		}


		inline Vector3 operator +(float value)
		{
			Vector3 temp(value, value, value);
			return (Vector3)XMVectorAdd(*this, temp);
		}

		inline Vector3& operator -=(const Vector3& vec)
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector3& operator -=(float value)
		{
			*this = *this - value;
			return *this;
		}

		inline Vector3 operator -(float value)
		{
			Vector3 temp(value, value, value);
			return (Vector3)XMVectorSubtract(*this, temp);
		}

		inline Vector3& operator *=(float value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector3& operator *=(Matrix4x4 value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector3& operator *(Matrix4x4 value) const
		{
			auto tmp = (Vector3)XMVector3Transform(*this, value);
			return tmp;
		}

		inline Vector3& operator /=(float value)
		{
			*this = *this / value;
			return *this;
		}

		inline const Vector3 operator -() const
		{
			Vector3 temp(-1.0f, -1.0f, -1.0f);
			return (Vector3)XMVectorSubtract(*this, temp);
		}

		inline Vector3& Floor(int len)
		{
			// TODO: return ステートメントをここに挿入します
		}

		inline Vector3& Round(int len)
		{
			// TODO: return ステートメントをここに挿入します
		}

		inline Vector3& Ceil(int len)
		{
			// TODO: return ステートメントをここに挿入します
		}

		inline float Dot(const Vector3 & vec1) const
		{
			return ((Vector3)XMVector3Dot(*this, vec1)).x;
		}

		inline Vector3& Cross(const Vector3 & vec1)
		{
			*this = (Vector3)XMVector3Cross(*this, vec1);
			return *this;
		}

		inline bool isNaN() const
		{
			return XMVector3IsNaN(*this);
		}

		inline bool isInfinite() const
		{
			return XMVector3IsInfinite(*this);
		}

		inline float GetLengthSqr() const
		{
			return ((Vector3)XMVector3LengthSq(*this)).x;
		}

		inline operator DirectX::XMVECTOR() const
		{
			DirectX::XMFLOAT3 temp = *this;
			DirectX::XMVECTOR output = DirectX::XMLoadFloat3(&temp);
			return output;
		};

		inline float GetLength() const
		{
			return ((Vector3)DirectX::XMVector3Length(DirectX::XMVECTOR(*this))).x;
		}

		inline void Normalize()
		{
			*this = DirectX::XMVector3Normalize(DirectX::XMVECTOR(*this));
		}
	};

	struct Vector4 :public DirectX::XMFLOAT4
	{
		inline Vector4(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat4(this, temp);
		}
		inline Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		inline Vector4(const Vector3& xyz, float w)
		{
			this->x = xyz.x;
			this->y = xyz.y;
			this->z = xyz.z;
			this->w = w;
		}
		inline Vector4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		inline  float* GetData()
		{
			float output[4] = { x,y,z,w };
			return output;
		};
		inline  void GetData(float* out)
		{
			auto data = GetData();
			for (int i = 0; i < 4; i++) {
				out[i] = data[i];
			}
		}
		inline Vector4& operator=(const DirectX::XMVECTOR& other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat4(this, temp);
			return *this;
		};
		inline ~Vector4() {};
		inline Vector4& operator +=(const Vector4& vec) {
			*this = *this + vec;
			return *this;
		};


		inline Vector4& operator +=(float value) {
			*this = *this + value;
			return *this;
		};

		inline Vector4 operator +(float value) {
			Vector4 temp(value, value, value, value);
			return (Vector4)XMVectorAdd(*this, temp);
		}


		inline Vector4& operator -=(const Vector4& vec)
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector4& operator -=(float value)
		{
			*this = *this - value;
			return *this;
		};

		inline Vector4 operator -(float value)
		{
			Vector4 temp(value, value, value, value);
			return (Vector4)XMVectorSubtract(*this, temp);
		};

		inline Vector4& operator *=(float value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector4& operator /=(float value)
		{
			*this = *this / value;
			return *this;
		}

		inline const Vector4 operator -() const
		{
			Vector4 temp(1.0f, 1.0f, 1.0f, 1.0f);
			return (Vector4)XMVectorSubtract(*this, temp);
		}


		inline Vector4& Floor(int len) {}

		inline Vector4& Round(int len) {}

		inline Vector4& Ceil(int len){}

		inline float Dot(const Vector4 & vec1) const
		{
			return ((Vector3)XMVector4Dot(*this, vec1)).x;
		}

		inline bool isNaN() const
		{
			return XMVector4IsNaN(*this);
		}

		inline bool isInfinite() const
		{
			return XMVector4IsInfinite(*this);
		}

		inline float GetLengthSqr() const
		{
			return ((Vector3)DirectX::XMVector4LengthSq(DirectX::XMVECTOR(*this))).x;
		}

		inline operator DirectX::XMVECTOR() const
		{
			DirectX::XMFLOAT4 temp = *this;
			DirectX::XMVECTOR output = DirectX::XMLoadFloat4(&temp);
			return output;
		}

		inline float GetLength() const
		{
			return ((Vector4)DirectX::XMVector4Length(DirectX::XMVECTOR(*this))).x;
		}

		inline void Normalize()
		{
			*this = DirectX::XMVector4Normalize(DirectX::XMVECTOR(*this));
		}
	};

	typedef Vector4 Color;
	typedef Vector2 Point2D;

	class Rectangle {
	public:
		float width;
		float height;
		float outerCircleRadius;
		Vector2 position;
		inline Rectangle() :width(0), height(0), position(Vector2()), outerCircleRadius(0) {};
		inline Rectangle(float arg_width, float  arg_height, Vector2 arg_position) :width(arg_width), height(arg_height), position(arg_position), outerCircleRadius(GetRectangleOuterCircleRadius(width, height)) {};
		inline Rectangle(float arg_width, float  arg_height, Vector2 arg_position, float arg_outerCircleRadius) :width(arg_width), height(arg_height), position(arg_position), outerCircleRadius(arg_outerCircleRadius) {};
		inline Rectangle(float arg_width, float  arg_height, float x, float y) :width(arg_width), height(arg_height), position(Vector2(x, y)), outerCircleRadius(GetRectangleOuterCircleRadius(width, height)) {};
		inline Point2D* GetVertecies()
		{
			 Point2D out[]{
				Point2D(position.x - width / 2, position.y - height / 2),
					Point2D(position.x + width / 2, position.y - height / 2),
					Point2D(position.x + width / 2, position.y + height / 2),
					Point2D(position.x - width / 2, position.y + height / 2)
			};

			 return out;
		}
			
		inline void GetVertecies(Point2D* out) {
			out = GetVertecies();
		}
		inline bool IsIntersects(std::shared_ptr< Rectangle> other) {

			auto d = other->position.GetDistance(position);
			if (other->position.GetDistance(position) > other->outerCircleRadius + outerCircleRadius) {
				return false;
			}
			auto otherVertecies = other->GetVertecies();
			for (auto i=0; i<4; i++)
			{
				if (IsContain(otherVertecies[ i])) {
					return true;
				}
			}
			return false;
		}
		inline bool IsContain(Point2D arg_point2D) {
			if (arg_point2D.x >= position.x - width / 2 && arg_point2D.x <= position.x + width / 2
				&& arg_point2D.y >= position.y - height / 2 && arg_point2D.y <= position.y + height / 2) {
				return true;
			}
			return false;
		}
		inline float GetTop() {

			return position.y - height / 2;
		}
		inline float GetBottom() {

			return position.y + height / 2;
		}
		inline float GetLeft() {
			return position.x - width / 2;
		}
		inline float GetRight() {

			return position.x + width / 2;
		}
		inline static float GetRectangleOuterCircleRadius(const int width, const int height) {
			auto aW = width; auto aH = height;
			auto s = (aW + aH);
			auto t = (s - aW)*(s - aH)* (s - aW)*(s - aH);
			auto u = (aW*aH * 2)*(aW*aH * 2)*(aW*aW + aH * aH);


			auto output = std::sqrt(u / t) / 4;
			return output;
		}
		inline static float GetRectangleOuterCircleRadius(const Rectangle& ref_rect) {
			auto s = (ref_rect.width + ref_rect.height);
			auto t = (s - ref_rect.width)*(s - ref_rect.height)* (s - ref_rect.width)*(s - ref_rect.height);
			auto u = (ref_rect.width*ref_rect.height * 2)*(ref_rect.width*ref_rect.height * 2)*(ref_rect.width*ref_rect.width + ref_rect.height * ref_rect.height);
			auto output = std::sqrt(u / t) / 4;
			return output;
		}
	};


	class MathHelper
	{
	public:
		inline static double Ceil(double dSrc, int iLen)
		{
			double	dRet;

			dRet = dSrc * pow(10.0, iLen);
			dRet = (double)(int)(dRet + 0.9);

			return dRet * pow(10.0, -iLen);
		}
		inline static double Floor(double dSrc, int iLen)
		{
			double dRet;

			dRet = dSrc * pow(10.0, iLen);
			dRet = (double)(int)(dRet);

			return dRet * pow(10.0, -iLen);
		}
		inline static double Round(double dSrc, int iLen)
		{
			double	dRet;

			dRet = dSrc * pow(10.0, iLen);
			dRet = (double)(int)(dRet + 0.5);

			return dRet * pow(10.0, -iLen);
		}
		template<typename T>
		inline static T GetMaximum(const T& v1, const T& v2) {
			return v1 > v2 ? v1 : v2;
		}
		template<typename T>
		inline static T GetMinimum(const T& v1, const T& v2) {
			return v1 < v2 ? v1 : v2;
		}

	private:
		MathHelper() {};
	};


	class Calculater {
	private:
		Calculater();
	public:
		inline static  Vector3 Cross(const Vector3 & vec0, const Vector3 & vec1)
		{
			return (Vector3)XMVector3Cross(vec0, vec1);
		}
		inline static  Vector2 Cross(const Vector2 & vec0, const Vector2 & vec1) {
			return (Vector2)XMVector2Cross(vec0, vec1);
		}
		inline static  Vector4 Cross(const Vector4 & vec0, const Vector4 & vec1, const Vector4 & vec2);
	};
}