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
		if (m_ConfigItem.bPressK)
		{
			uint64_t dNow = GetTickCount();
			if (m_ConfigItem.kTime > 0 && (dNow - m_ConfigItem.last_kTime > m_ConfigItem.kTime * 1000))
			{
				m_ConfigItem.cout_k++; this->FKey('K'); m_ConfigItem.last_kTime = dNow; logFunc(L"press K");
			}
		}
		
		//logFunc(L"handleAttack End");
		//logFunc(L"checkIfoutGPS begin");
		bool b = checkIfoutGPS();
		if(b)continue;
		
		if ( m_ConfigItem.pickup)
		{
			logFunc(L"pickup begin");
			pickup(center_X - move_one_offset, center_y - move_one_offset);
		}
		else {
			//b = true;
		////logFunc(L"checkIfoutGPS end");
		//if (!b)
		//{
		//	if (goto_XY(currentGPSX, currentGPSY,targetGPSXY[targetPost %4]))
		//		targetPost++;
		//}
				switch (loopcount / 2 % 4)
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
		
		this->gobackMainFun(m_ConfigItem.mainFunc);

		this->attack();


		g_GoCenterInfo.Format(L"持续攻击 %d次", i);
		if (i % 100 == 0)
		{
			Sleep(1);
		}

	}


}

bool GameObj::goto_XY(int curX, int curY, GPSXY destGPS)
{
	if (curX == destGPS.x && curY == destGPS.y)
	{
		return true;
	}
	CString  showText;
	showText.Format(L"goto [%d,%d]-->[%d,%d]", curX, curY, destGPS.x, destGPS.y);
	logFunc(showText);
	if (curX < destGPS.x)
	{
		showText.Format(L"curX(%d)小于 destX(%d) 往左", curX, destGPS.x);
		logFunc(showText);
		this->move_left_one();
	}
	else if (curX > destGPS.x)
	{
		showText.Format(L"curX(%d)大于 destX(%d) 往右", curX, destGPS.x);
		logFunc(showText);
		this->move_right_one();
	}
	else if (curY < destGPS.y)
	{
		showText.Format(L"curY(%d)小于 destY(%d) 往下", curY, destGPS.y);
		logFunc(showText);
		this->move_down_one();
	}
	else if (curY > destGPS.y)
	{
		showText.Format(L"curY(%d)大于 destY(%d) 往上", curY, destGPS.y);
		logFunc(showText);
		this->move_top_one();
	}
	return false;
}

CString GameObj::goto_Center(int x1, int y1, int x4, int y4)
{
	CString  showText = L""; bNeedGoCenter = true;
	if (currentGPSX < x1)
	{
		showText.Format(L"x(%d)小于 x1(%d) 往左", currentGPSX, x1);

		logFunc(showText);
		this->move_left_one();

		//向左了 但是x 比刚才小了，方向反了

		int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
		hsn.getGPS(currentGPSX, currentGPSY);
		if (currentGPSX < lastGPSX)
		{
			CString s;
			s.Format(L"已经向左了 但是x %d 比刚才 %d 小了，方向反了", currentGPSX, lastGPSX);
			OutputDebugString(s);
			logFunc(s);
			turn_map();
		}
	}
	else if (currentGPSX > x4)
	{
		showText.Format(L"x(%d)于 x4(%d) 往右", currentGPSX, x4);
		logFunc(showText);
		this->move_right_one();

		int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
		hsn.getGPS(currentGPSX, currentGPSY);
		if (currentGPSX > lastGPSX)
		{
			CString s;
			s.Format(L"已经往右了 但是x %d 比刚才 %d 大了，方向反了", currentGPSX, lastGPSX);
			OutputDebugString(s);
			logFunc(s);
			turn_map();
		}
	}
	else if (currentGPSY < y1)
	{
		showText.Format(L"y(%d)小于 y1(%d) 往下", currentGPSY, y1);
		logFunc(showText);
		this->move_down_one();



		int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
		hsn.getGPS(currentGPSX, currentGPSY);
		if (currentGPSY < lastGPSY)
		{
			CString s;
			s.Format(L"已经往下了 但是y %d 比刚才 %d 小了，方向反了", currentGPSY, lastGPSY);
			OutputDebugString(s);
			logFunc(s);
			turn_map();
		}
	}
	else if (currentGPSY > y4)
	{
		showText.Format(L"y(%d)大于 y4(%d) 往上", currentGPSY, y4);
		logFunc(showText);
		this->move_top_one();

		int lastGPSX = currentGPSX, lastGPSY = currentGPSY;
		hsn.getGPS(currentGPSX, currentGPSY);
		if (currentGPSY > lastGPSY)
		{
			CString s;
			s.Format(L"已经往上了 但是y %d 比刚才 %d 大了，方向反了", currentGPSY, lastGPSY);
			OutputDebugString(s);
			logFunc(s);
			turn_map();
		}
	}
	else
	{
		showText.Format(L"正常");
		bNeedGoCenter = false;
	}

	return showText;
}

void GameObj::pickup(int DestX, int DestY)
{
	this->PressAlt(true);
	int x1, x2, y1, y2;
	x1 = x2 = center_X;
	y1 = y2 = center_y;
	if (DestX > center_X)
	{
		x1 = center_X;
		x2 = DestX;
	}
	else if (DestX < center_X)
	{
		x2 = center_X;
		x1 = DestX;
	}
	else if (DestY < center_y)
	{
		y2 = center_y;
		y1 = DestY;
	}
	else if (DestY > center_y)
	{
		y1 = center_y;
		y2 = DestY;

	}
	
	{
		for (int x = x1; x <= x2; x += 5)
		{
			for (int y = y1; y <= y2; y += 5)
			{// 模拟鼠标左键单击  

				move(x, y);
				Sleep(100);
				if (bExit)return;
			}
		}
	}
	PressAlt(false);
}
