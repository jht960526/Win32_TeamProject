#pragma once
#include "playerOBJ.h"

class CObject;

class Camera
{
	SINGLE(Camera);
public:
	void update();

	void SetLookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }
	void SetTargetObj(playerOBJ* _pTargerObj) { m_pTargetObj = _pTargerObj; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return Vec2(_vObjPos.x - m_vDiff.x, _vObjPos.y - m_vDiff.y); }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return Vec2(_vRenderPos.x + m_vDiff.x, _vRenderPos.y + m_vDiff.y); }

private:
	Vec2 m_vLookAt;
	playerOBJ* m_pTargetObj;
	Vec2 m_vDiff;

	void CalDiff();

};


