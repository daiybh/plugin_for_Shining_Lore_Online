// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "CMakeProject1.h"

#include "imageProc/ImageProc.h"
int main()
{
	

	std::wstring BigPic = LR"(C:\Users\daiyb\Desktop\opencv_game\1.png)";
	std::wstring smallPic = LR"(C:\Users\daiyb\Desktop\opencv_game\fenjie.bmp)";

	ImageProc ip;
	ip._src.read(BigPic.data());
	ip.Capture(BigPic);

	long lx, ly;
	long lret = 0;
	ip.FindPic(smallPic, L"000000", 1.0, 0, lx, ly);

	return 0;
}
