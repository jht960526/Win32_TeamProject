#pragma once


// 전방선언
// 헤더끼리 서로가 서로를 참조하는 것을 막기 위해서
// 구체적인 정보를 알 수 없기 때문에 포인터를 사용
class CObject;

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];

	// Scene 이름
	wstring m_strName;
	

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }

	const wstring& GetName() { return m_strName; }

public:

	CScene();
	virtual ~CScene();
};

