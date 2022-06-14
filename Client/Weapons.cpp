#include "pch.h"
#include "Weapons.h"

Bullet::Bullet() 
	:type{}, B_Pos{}, B_Scale{}, B_angle{}, B_isOn{}
{

}

void Bullet::SetAngle(Vec2 _1st_Pos, Vec2 _2nd_Pos) {
	float Distance_x = _2nd_Pos.x - _1st_Pos.x;
	float Distance_y = _2nd_Pos.y - _1st_Pos.y;

	float Degree_Agl = (float)atan2f(Distance_y, Distance_x);

	float Anglex = cosf(Degree_Agl);
	float Angley = sinf(Degree_Agl);

	B_angle = Vec2(Anglex, Angley);
}

void Bullet::FireBullet(Vec2 _Scale, Vec2 _1st_Pos, Vec2 _2nd_Pos, int _type) {
	TurnOn();
	SetScale(_Scale);
	SetType(_type);
	SetAngle(_1st_Pos, _2nd_Pos);
}