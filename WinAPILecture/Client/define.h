#pragma once

#define SINGLE(type) public:\
	                        static type* GetInst()\
	                        {\
	                            static type mgr;\
                                return &mgr;\
                            }\
					/*private: \
							type();\
							~type();*/

#define fDT CTimerMgr::GetInst()->GetfDT()
#define DT CTimerMgr::GetInst()->GetDT()
