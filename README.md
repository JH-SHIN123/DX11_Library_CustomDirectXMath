* DirecX 11의 수학 기능을 Unreal스타일에 맞춰 커스텀 및 래핑한 프로젝트

## 주요 기능
1 변환 함수 추가  
- 16진수 -> 10진수  
- Radian -> Degree  
- FVector -> DirectX::XMVECTOR  

2. 유효성 검증 함수 추가  
- IsZero  
- IsNaN  
- IsNormalize  

3. 벡터 관련 수학  
- 내적, 외적 계산  
- 각도 계산  
- 길이 계산  
- 반사 벡터 계산  

4. 4x4 행렬 관련 수학  
- TransformNormal, TransformCoord 추가  
- 크기, 회전, 위치 추출 추가  
- 벡터를 기반(크기, 회전, 위치)으로 행렬 구성 추가  
- 역행렬 추가  

5. 쿼터니언 지원  
- 쿼터니언 각 -> 오일러 각 변환 지원  

### 설치 방법
1. 해당 프로젝트 빌드 후 *x64/솔루션구성/GMath.lib* 생성 (디버그 환경에서는 _d 네이밍 추가 생성)
2. *GMath*폴더와 함께 lib 파일을 원하는 프로젝트에 추가
3. ```GMath/GMath.h``` 선언으로 기능 사용 가능


### 사용 예제
#ifdef _DEBUG
#pragma comment(lib, "GMath_d.lib")
#else
#pragma comment(lib, "GMath.lib")
#endif

#include <iostream>
#include "GMath/GMath.h"

int main()
{
	GMath::FVector3D Start(0.f, 0.f, 0.f);
	GMath::FVector3D End(10.f, 10.f, 10.f);

	GMath::FVector3D Mid = Lerp(Start, End, 0.5f);

	GMath::FMatrix Rotation = GMath::MatrixRotation_AxisZ(45.f);
	GMath::FVector3D RotatedVec = GMath::TransformNormal(Rotation, GMath::FVector3D::Axis[GMath::EAxis::X]);

	std::cout << "Mid Point: " << Mid.x << ", " << Mid.y << ", " << Mid.z << std::endl;
	std::cout << "Rotated X-Axis (45 deg): " << RotatedVec.x << ", " << RotatedVec.y << std::endl;

	if (GMath::IsNormalize(RotatedVec)) 
	{
		std::cout << "Rotation preserved length!" << std::endl;
	}

	return 0;
}
