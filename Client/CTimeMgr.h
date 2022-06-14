#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);

private:

	// Ƚ�� ī��Ʈ �� �� ���� ���� �ڷ���
	LARGE_INTEGER m_llCurrCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // ������ ������ �ð� ��
	double m_dAcc; // m_dDT�� ����(1�� üũ�� ���� ���� �ð�)
	UINT m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT m_iFPS; // �ʴ� ȣ�� Ƚ��

	// FPS
	// 1�����Ӵ� �ð� (Delta Time)

public:
	// �ʱ�ȭ
	void init();

	// �� �����Ӹ��� ȣ��
	void update();

//private:
//	CTimeMgr();
//	~CTimeMgr();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
	float GetfAcc() { return (float)m_dAcc; }
};

