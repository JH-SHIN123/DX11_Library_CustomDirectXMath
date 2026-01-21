#pragma once

#include "../GMath/Vector.h"
#include "../GMath/Matrix.h"

#define INLINE inline

namespace GMath
{
	static constexpr float PI = 3.141592f;
	static constexpr float CENTRAL_ANGLE = 360.f;

#pragma region NonInlineFunctions

	FVector3D ReflectionVector(const FVector3D& SrcDirection, const FVector3D& DestNormal);

	FVector3D TransformNormal(const FMatrix& mat, const FVector3D& vec);
	FVector3D TransformCoord(const FMatrix& mat, const FVector3D& vec);

	FVector3D GetScale(const FMatrix& mat);
	FVector3D GetRotationEular(const FMatrix& mat);
	FVector3D GetLocation(const FMatrix& mat);

	FVector4D GetQuaternion(const FMatrix& mat);
	FVector3D ConvertQuaternionToEular(const FVector4D& Quaternion);
	FVector4D ConvertEularToQuaternion(const FVector3D& Eular);
	FVector4D QuaternionInverse(const FVector4D& Quaternion);
	FVector4D QuaternionMultiply(const FVector4D& Quat1, const FVector4D& Quat2);
	void QuaternionToAxisAngle(const FVector4D& Quaternion, FVector3D* _Out_Axis, float* _Out_Angle);

	FMatrix MatrixTranspose(const FMatrix& mat);
	FMatrix MatrixInverse(const FMatrix& mat);
	FMatrix MatrixNormalize_Scale(const FMatrix& mat);

	FMatrix MatrixScaling(const FVector2D& Scale);
	FMatrix MatrixScaling(const FVector3D& Scale);

	FMatrix MatrixRotation_AxisZ(float RotationZ);
	FMatrix MatrixRotation(const FVector2D& Rotation);
	FMatrix MatrixRotation(const FVector3D& Rotation);

	FMatrix MatrixTranslation(const FVector2D& Location);
	FMatrix MatrixTranslation(const FVector3D& Location);


#pragma endregion NonInlineFunctions

#pragma region Convert
	// 16 number -> 10 number
	// ex. 255 -> 1.0f
	INLINE float ConvertHexToDecRatio(unsigned int Hex)
	{
		return (float)Hex / 0xFF;
	}

	// 16 number -> 10 number
	// ex. 255 -> 1.0f
	INLINE FVector3D ConvertHexToDecRatio(unsigned int HexX, unsigned int HexY, unsigned int HexZ)
	{
		return FVector3D((float)HexX / 0xFF, (float)HexY / 0xFF, (float)HexZ / 0xFF);
	}

	// 16 number -> 10 number
	// ex. 255 -> 1.0f
	INLINE FVector3D ConvertHexToDecRatio(const FVector3D& HexXYZ)
	{
		return HexXYZ / (float)0xFF;
	}

	// 16 number -> 10 number
	// ex. 255 -> 1.0f
	INLINE FVector4D ConvertHexToDecRatio(unsigned int HexX, unsigned int HexY, unsigned int HexZ, unsigned int HexW)
	{
		return FVector4D((float)HexX / 0xFF, (float)HexY / 0xFF, (float)HexZ / 0xFF, (float)HexW / 0xFF);
	}

	// 16 number -> 10 number
	// ex. 255 -> 1.0f
	INLINE FVector4D ConvertHexToDecRatio(const FVector4D& HexXYZW)
	{
		return HexXYZW / (float)0xFF;
	}

	// Radians -> Degree
	INLINE float ConvertRadianToDegree(float Rad) { return DirectX::XMConvertToDegrees(Rad); }

	// Radians -> Degree
	INLINE float ConvertDegreeToRadian(float Deg) { return DirectX::XMConvertToRadians(Deg); }

	INLINE DirectX::XMVECTOR Convert(const FVector2D& v) { return DirectX::XMLoadFloat2((DirectX::XMFLOAT2*)&v); }
	INLINE DirectX::XMVECTOR Convert(const FVector3D& v) { return DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&v); }
	INLINE DirectX::XMVECTOR Convert(const FVector4D& v) { return DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&v); }


#pragma endregion Convert

	INLINE int	Clamp(int Value, int Min, int Max)
	{
		if (Value < Min)
			Value = Min;

		else if (Value > Max)
			Value = Max;

		return Value;
	}

	INLINE float Clamp(float Value, float Min, float Max)
	{
		if (Value < Min)
			Value = Min;

		else if (Value > Max)
			Value = Max;

		return Value;
	}

	INLINE float Lerp(float Src, float Dest, float LerpValue) { return Src * (1.f - LerpValue) + Dest * LerpValue; }

	INLINE bool IsZero(float value) { return fabsf(value) <= FLT_EPSILON; }

	INLINE bool IsNearlyZero(float value, float ErrorTolerance = FLT_EPSILON) { return fabsf(value) <= ErrorTolerance; }

	INLINE float Length(const FVector2D& v) { return DirectX::XMVectorGetX(DirectX::XMVector2Length(Convert(v))); }
	INLINE float Length(const FVector3D& v) { return DirectX::XMVectorGetX(DirectX::XMVector3Length(Convert(v))); }
	INLINE float Length(const FVector4D& v) { return DirectX::XMVectorGetX(DirectX::XMVector4Length(Convert(v))); }

	INLINE float Dot(const FVector2D& v1, const FVector2D& v2) { return v1.x * v2.x + v1.y * v2.y; }
	INLINE float Dot(const FVector3D& v1, const FVector3D& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	INLINE float Dot(const FVector4D& v1, const FVector4D& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }

	INLINE FVector2D Cross(const FVector2D& v1, const FVector2D& v2) { return FVector2D(DirectX::XMVector2Cross(Convert(v1), Convert(v1))); }
	INLINE FVector3D Cross(const FVector3D& v1, const FVector3D& v2) { return FVector3D(DirectX::XMVector3Cross(Convert(v1), Convert(v1))); }
	INLINE FVector4D Cross(const FVector4D& v1, const FVector4D& v2, const FVector4D& v3)
	{
		return FVector4D(DirectX::XMVector4Cross(Convert(v1), Convert(v1), Convert(v3)));
	}

	INLINE float Distance(const FVector2D& v1, const FVector2D& v2) { return Length(v1 - v2); }
	INLINE float Distance(const FVector3D& v1, const FVector3D& v2) { return Length(v1 - v2); }
	INLINE float Distance(const FVector4D& v1, const FVector4D& v2) { return Length(v1 - v2); }

	INLINE bool IsNaN(const FVector2D& v) { return isnan(v.x) || isnan(v.y); }
	INLINE bool IsNaN(const FVector3D& v) { return isnan(v.x) || isnan(v.y) || isnan(v.z); }
	INLINE bool IsNaN(const FVector4D& v) { return isnan(v.x) || isnan(v.y) || isnan(v.z) || isnan(v.w); }

	INLINE bool IsZero(const FVector2D& v) { return IsZero(Length(v)); }
	INLINE bool IsZero(const FVector3D& v) { return IsZero(Length(v)); }
	INLINE bool IsZero(const FVector4D& v) { return IsZero(Length(v)); }

	INLINE bool IsNormalize(const FVector2D& v) { return IsZero(Length(v) - 1.f); }
	INLINE bool IsNormalize(const FVector3D& v) { return IsZero(Length(v) - 1.f); }
	INLINE bool IsNormalize(const FVector4D& v) { return IsZero(Length(v) - 1.f); }


	INLINE FVector2D Lerp(const FVector2D& Src, const FVector2D& Dest, float LerpValue)
	{
		return FVector2D(Lerp(Src.x, Dest.x, LerpValue), Lerp(Src.y, Dest.y, LerpValue));
	}

	INLINE FVector3D Lerp(const FVector3D& Src, const FVector3D& Dest, float LerpValue)
	{
		return FVector3D(Lerp(Src.x, Dest.x, LerpValue), Lerp(Src.y, Dest.y, LerpValue), Lerp(Src.z, Dest.z, LerpValue));
	}

	INLINE FVector4D Lerp(const FVector4D& Src, const FVector4D& Dest, float LerpValue)
	{
		return FVector4D(Lerp(Src.x, Dest.x, LerpValue), Lerp(Src.y, Dest.y, LerpValue), Lerp(Src.z, Dest.z, LerpValue), Lerp(Src.w, Dest.w, LerpValue));
	}

	INLINE FVector2D Normalize(const FVector2D& v)
	{
		if (IsNormalize(v))
			return v;

		FVector2D result;
		float Size = Length(v);

		if (IsNearlyZero(Size))
			return result;

		result.x = v.x / Size;
		result.y = v.y / Size;
		return result;
	}

	INLINE FVector3D Normalize(const FVector3D& v)
	{
		if (IsNormalize(v))
			return v;

		FVector3D result;
		float Size = Length(v);

		if (IsNearlyZero(Size))
			return result;

		result.x = v.x / Size;
		result.y = v.y / Size;
		result.z = v.z / Size;
		return result;
	}

	INLINE FVector4D Normalize(const FVector4D& v)
	{
		if (IsNormalize(v))
			return v;

		FVector4D result;
		float Size = Length(v);

		if (IsNearlyZero(Size))
			return result;

		result.x = v.x / Size;
		result.y = v.y / Size;
		result.z = v.z / Size;
		result.w = v.w / Size;
		return result;
	}

	// 쿼터니언으로 회전한 축 계산
	INLINE FVector3D RotateAxisQuternion(const FVector4D& Qaut, const FVector3D& Direction)
	{
		return DirectX::XMVector3Rotate(Convert(Direction), Convert(Qaut));
	}

	// 두 방향벡터의 각도를 계산
	INLINE float AngleDir(const FVector2D& LookDir, const FVector2D& TargetDir)
	{
		FVector3D _LookDir = LookDir;
		FVector3D _TargetDir = TargetDir;

		return AngleDir(_LookDir, _TargetDir);
	}

	// 두 방향벡터의 각도를 계산
	INLINE float AngleDir(const FVector3D& LookDir, const FVector3D& TargetDir)
	{
		FVector3D _LooDir = Normalize(LookDir);
		FVector3D _TargetDir = Normalize(TargetDir);

		float Angle = ConvertRadianToDegree(acosf(Dot(_LooDir, _TargetDir)));

		if (IsNearlyZero(Angle))
			return 0.f;

		FVector3D CrossVec = Cross(_LooDir, _TargetDir);
		if (CrossVec.z < 0.f)
			Angle *= -1.f;

		return Angle;
	}

	// 위치를 이용해 각도를 계산
	INLINE float Angle(const FVector2D& TargetLocation, const FVector2D& Location, EAxis::Type AxisType)
	{
		FVector3D _TargetLocation;
		FVector3D _Location;

		size_t Size = sizeof(FVector2D);

		memcpy(&_TargetLocation, &TargetLocation, Size);
		memcpy(&_Location, &Location, Size);

		return Angle(_TargetLocation, _Location, AxisType);
	}

	// 위치를 이용해 각도를 계산
	INLINE float Angle(const FVector3D& TargetLocation, const FVector3D& Location, EAxis::Type AxisType)
	{
		FVector3D Dir = Normalize(TargetLocation - Location);

		float Angle = ConvertRadianToDegree(acosf(Dot(Dir, FVector3D::Axis[AxisType])));

		if (TargetLocation.x > Location.x)
			Angle = CENTRAL_ANGLE - Angle;

		return Angle;
	}

	// 2D 상태에서의 Rotation
	INLINE FVector3D FindLookAtRotation(const FVector3D& TargetLocation, const FVector3D& Location, const FVector3D& RotationAxis = FVector3D::Axis[EAxis::Z])
	{
		FVector3D NewY = Normalize(TargetLocation - Location);
		FVector3D NewZ = RotationAxis;
		FVector3D NewX = Cross(NewY, NewZ);

		FMatrix MatRotation = FMatrix::Identity;
		size_t Size = sizeof(FVector3D);
		memcpy(&MatRotation.v[EAxis::X], &NewX, Size);
		memcpy(&MatRotation.v[EAxis::Y], &NewY, Size);
		memcpy(&MatRotation.v[EAxis::Z], &NewZ, Size);

		return ConvertQuaternionToEular(GetQuaternion(MatRotation));
	}
}