#include "pch.h"
#include "GamUser.h"

void GameObj::workthread()
{
	loopcount = 0;
	bExit = false;
	bool bSetRange = false;

	bExit = false;
	m_ExitEvent->ResetEvent();

	if (this == nullptr)
	{
		AfxMessageBox(L"先选择角色");
		return;
	}
	bool bFindedRightface = false;
	
	GPSXY targetGPSXY[4];
	int targetPost = 0;
	while (!bExit)
	{
		//update targetGPSXY
		targetGPSXY[0].x = settingGPSX  ;
		targetGPSXY[0].y = settingGPSY  ;
		targetGPSXY[1].x = settingGPSX - m_ConfigItem.areaOffset;
		targetGPSXY[1].y = settingGPSY ;

		targetGPSXY[2].x = settingGPSX - m_ConfigItem.areaOffset;
		targetGPSXY[2].y = settingGPSY + m_ConfigItem.areaOffset;

		targetGPSXY[3].x = settingGPSX ;
		targetGPSXY[3].y = settingGPSY + m_ConfigItem.areaOffset;

		loopcount++;
		DWORD dt = WaitForSingleObject(*m_ExitEvent, 100);
		if (dt == WAIT_OBJECT_0)break;
		hsn.getGPS(currentGPSX, currentGPSY);
		hsn.doRead();

		move_one_offset = m_ConfigItem.stepOffset;
		if (m_ConfigItem.NP && hsn.info.np < 50)
		{
			logFunc(L"press5 for NP");
			Press5_forNP();
		}

		bFindedRightface = true;
		if (!bFindedRightface)
		{
			int oldmove_one_offset = move_one_offset;
			for (int y = 0; y < 4; y++)
			{
				turn_map();
				Sleep(1000);
				move_one_offset = 100;
				hsn.getGPS(currentGPSX, currentGPSY);
				int lastX = hsn.bb1.x;
				int lastY = hsn.bb1.y;
				for (int i = 0; i < 3; i++)
				{
					//调整游戏方向
					//往左走 获取坐标是变大还是变小
					move_top_one();					
					hsn.getGPS(currentGPSX, currentGPSY);
					int curX = hsn.bb1.x;
					int curY = hsn.bb1.y;
					if (curX < lastX)
					{
						g_GoCenterInfo = L"正向";
					}
					else if (curX> lastX)
					{
						g_GoCenterInfo = L"反向";
					}
					CString x;
					x.Format(L"turn_mapGPS-->loopcount:%lld y=%d i=%d %d-%d=%3d %d-%d=%3d %s", loopcount, y, i, 
						curX,lastX, curX -lastX,
						curY,lastY, curY - lastY, g_GoCenterInfo);
					OutputDebugString(x);
				}
			}
			move_one_offset = oldmove_one_offset;
		}
		if (!bFindedRightface)
			continue;

		//logFunc(L"handleAttack begin");
		handleAttack();
		//logFunc(L"handleAttack End");
		//logFunc(L"checkIfoutGPS begin");
		bool b = checkIfoutGPS();

		//logFunc(L"checkIfoutGPS end");
		if (!b)
		{
			if (goto_XY(currentGPSX, currentGPSY,targetGPSXY[targetPost %4]))
				targetPost++;
		}
		b = false;
		if (!b)
		{
			switch (loopcount/2 % 4)
			{
			case 0:	move_top_one(); break;
			case 1: move_right_one(); break;
			case 2: move_down_one(); break;
			case 3: move_left_one(); break;
			}
		}

		Sleep(50);
	}
}

void GameObj::handlePickUP()
{
	if (!m_ConfigItem.pickup)return;

	uint64_t dNow = GetTickCount();
	if (m_ConfigItem.pickupTime > 0 && (dNow - m_ConfigItem.last_PickupTime > m_ConfigItem.pickupTime * 1000))
	{
		m_ConfigItem.cout_pickup++; 
		
		doPickup();
		m_ConfigItem.last_PickupTime = dNow;
	}

}

void GameObj::handleAttack()
{
	if (!m_ConfigItem.attack)return;
	int iAttack = 100;

	hsn.doRead();
	if (hsn.info.HP == hsn.info.HPMax)
	{
		g_GoCenterInfo.Format(L"HP 满了 不攻击");
		return;
	}
	for (int i = iAttack; i > 0 && !bExit && m_ConfigItem.attack; i--)
	{
		uint64_t dNow = GetTickCount();
		if (m_ConfigItem.f1Time > 0 && (dNow - m_ConfigItem.last_f1Time > m_ConfigItem.f1Time * 1000))
		{
			m_ConfigItem.cout_f1++; this->F1(); m_ConfigItem.last_f1Time = dNow;
		}
		if (m_ConfigItem.f2Time > 0 && (dNow - m_ConfigItem.last_f2Time > m_ConfigItem.f2Time * 1000))
		{
			m_ConfigItem.cout_f2++; this->F2(); m_ConfigItem.last_f2Time = dNow;
		}
		if (m_ConfigItem.f3Time > 0 && (dNow - m_ConfigItem.last_f3Time > m_ConfigItem.f3Time * 1000))
		{
			m_ConfigItem.cout_f3++; this->F3(); m_ConfigItem.last_f3Time = dNow;
		}
		if (m_ConfigItem.f4Time > 0 && (dNow - m_ConfigItem.last_f4Time > m_ConfigItem.f4Time * 1000))
		{
			m_ConfigItem.cout_f4++; this->F4(); m_ConfigItem.last_f4Time = dNow;
		}
		if (m_ConfigItem.f5Time > 0 && (dNow - m_ConfigItem.last_f5Time > m_ConfigItem.f5Time * 1000))
		{
			m_ConfigItem.cout_f5++; this->F5(); m_ConfigItem.last_f5Time = dNow;
		}
		if (m_ConfigItem.kTime > 0 && (dNow - m_ConfigItem.last_kTime > m_ConfigItem.kTime * 1000))
		{
			m_ConfigItem.cout_k++; this->FKey('K'); m_ConfigItem.last_kTime = dNow; logFunc(L"press K");
		}
		this->gobackMainFun(m_ConfigItem.mainFunc);

		this->attack();


		g_GoCenterInfo.Format(L"持续攻击 %d次", i);
		if (i % 100 == 0)
		{
			Sleep(1);
		}

	}


}
