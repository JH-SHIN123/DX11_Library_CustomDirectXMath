#include "../GMath/GMath.h"

using namespace GMath;

FVector3D GMath::ReflectionVector(const FVector3D& SrcDirection, const FVector3D& DestNormal)
{
	FVector3D Direction = GMath::IsNormalize(SrcDirection) ? SrcDirection : GMath::Normalize(SrcDirection);
	FVector3D Normal = GMath::IsNormalize(DestNormal) ? DestNormal : GMath::Normalize(DestNormal);

	return Direction - Normal * (2.f * GMath::Dot(Normal, Direction));
}

FVector3D GMath::TransformNormal(const FMatrix& mat, const FVector3D& vec)
{
	// XMVector3TransformNormal: w = 0
	DirectX::XMVECTOR result = DirectX::XMVector3TransformNormal(GMath::Convert(vec), mat.m);

	return DirectX::XMVector3Normalize(result);
}

FVector3D GMath::TransformCoord(const FMatrix& mat, const FVector3D& vec)
{
	// XMVector3TransformCoord: w = 1
	DirectX::XMVECTOR result = DirectX::XMVector3TransformCoord(GMath::Convert(vec), mat.m);

	return result;
}

FVector3D GMath::GetScale(const FMatrix& mat)
{
	FVector3D Scale = {};

	for (int i = 0; i < EAxis::End; ++i)
		Scale[i] = GMath::Length(mat.v[i]);

	return Scale;
}

FVector3D GMath::GetRotationEular(const FMatrix& mat)
{
	return GMath::ConvertQuaternionToEular(GMath::GetQuaternion(mat));
}

FVector4D GMath::GetQuaternion(const FMatrix& mat)
{
	FVector4D Quat = {};

	DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)&Quat,
		DirectX::XMQuaternionRotationMatrix(GMath::MatrixNormalize_Scale(mat).m));

	return Quat;
}

FVector3D GMath::GetLocation(const FMatrix& mat)
{
	return FVector3D(mat.v[3].x, mat.v[3].y, mat.v[3].z);
}

FVector3D GMath::ConvertQuaternionToEular(const FVector4D& Quaternion)
{
	FVector3D Eular = FVector3D::ZeroVector;
	DirectX::FXMVECTOR Quat = DirectX::XMQuaternionNormalize((GMath::Convert(Quaternion)));
	
	float qx = DirectX::XMVectorGetX(Quat);
	float qy = DirectX::XMVectorGetY(Quat);
	float qz = DirectX::XMVectorGetZ(Quat);
	float qw = DirectX::XMVectorGetW(Quat);		

	// Yaw (Y축 회전)
	Eular.y = atan2f((2.f * (qw * qy + qx * qz)), (1.f - 2.f * (qy * qy + qx * qx)));

	// Pitch (X축 회전)
	float sinp = 2.f * (qw * qx - qy * qz);
	if (fabsf(sinp) >= 1.f)
		Eular.x = copysignf(DirectX::XM_PIDIV2, sinp);
	else
		Eular.x = asinf(sinp);

	// Roll (Z축 회전)
	Eular.z = atan2f((2.f * (qw *qz + qx * qy)), 1.f - 2.f * (qz * qz + qx * qx));

	for (int i = 0; i < EAxis::End; ++i)
	{
		Eular[i] = ConvertRadianToDegree(Eular[i]);
	}

	return Eular;
}

FVector4D GMath::ConvertEularToQuaternion(const FVector3D& Eular)
{
	return DirectX::XMQuaternionRotationRollPitchYaw(
		ConvertDegreeToRadian(Eular.x), ConvertDegreeToRadian(Eular.y), ConvertDegreeToRadian(Eular.z));
}

FVector4D GMath::QuaternionInverse(const FVector4D& Quaternion)
{
	return DirectX::XMQuaternionInverse(GMath::Convert(Quaternion));
}

FVector4D GMath::QuaternionMultiply(const FVector4D& Quat1, const FVector4D& Quat2)
{
	return DirectX::XMQuaternionMultiply(GMath::Convert(Quat1), GMath::Convert(Quat2));
}

void GMath::QuaternionToAxisAngle(const FVector4D& Quaternion, FVector3D* _Out_Axis, float* _Out_Angle)
{
	if (!_Out_Axis || !_Out_Angle)
		return;

	DirectX::XMVECTOR Quat = DirectX::XMQuaternionNormalize((GMath::Convert(Quaternion)));
	DirectX::XMVECTOR Axis = GMath::Convert(*_Out_Axis);
	DirectX::XMQuaternionToAxisAngle(&Axis, _Out_Angle, Quat);

	*_Out_Axis = Axis;
}

FMatrix GMath::MatrixTranspose(const FMatrix& mat)
{
	return DirectX::XMMatrixTranspose(mat.m);
}

FMatrix GMath::MatrixInverse(const FMatrix& mat)
{
	DirectX::XMVECTOR Deter = DirectX::XMMatrixDeterminant(mat.m);
	return DirectX::XMMatrixInverse(&Deter, mat.m);
}

FMatrix GMath::MatrixNormalize_Scale(const FMatrix& mat)
{
	FMatrix MatNormalize = mat;

	for (int i = 0; i < EAxis::End; ++i)
	{
		MatNormalize.v[i] = GMath::Normalize(MatNormalize.v[i]);
	}

	return MatNormalize;
}

FMatrix GMath::MatrixScaling(const FVector2D& Scale)
{
	return DirectX::XMMatrixScaling(Scale.x, Scale.y, 1.f);
}

FMatrix GMath::MatrixScaling(const FVector3D& Scale)
{
	return DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
}

FMatrix GMath::MatrixRotation_AxisZ(float RotationZ)
{
	float RadianZ = DirectX::XMConvertToRadians(RotationZ);

	return DirectX::XMMatrixRotationZ(RadianZ);
}

FMatrix GMath::MatrixRotation(const FVector2D& Rotation)
{
	FVector4D Quat = GMath::ConvertEularToQuaternion(FVector3D(Rotation.x, Rotation.y, 0.f));

	return DirectX::XMMatrixRotationQuaternion(GMath::Convert(Quat));
}

FMatrix GMath::MatrixRotation(const FVector3D& Rotation)
{
	FVector4D Quat = GMath::ConvertEularToQuaternion(Rotation);

	return DirectX::XMMatrixRotationQuaternion(GMath::Convert(Quat));
}

FMatrix GMath::MatrixTranslation(const FVector2D& Location)
{
	return DirectX::XMMatrixTranslation(Location.x, Location.y, 0.f);
}

FMatrix GMath::MatrixTranslation(const FVector3D& Location)
{
	return DirectX::XMMatrixTranslation(Location.x, Location.y, Location.z);
}
