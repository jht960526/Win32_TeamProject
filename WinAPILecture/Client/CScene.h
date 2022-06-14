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

	void update();

	void render(HDC _dc);

	// 해당 Scene에 진입 시 호출
	virtual void Enter() = 0; // 순수 가상함수 : 씬에는 객체 생성 불가

	// 해당 Scene을 탈출 시 호출
	virtual void Exit() = 0;

protected:
	void AddObject(CObject* _pOb, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pOb); // Inline으로 호출해서 스택에서 처리 -> 함수 호출비용x
	}

public:

	CScene();
	virtual ~CScene();
};

