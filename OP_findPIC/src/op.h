#pragma once

#include <string>

class ImageProc;
class OP {
public:
	long FindPic(std::wstring bigPic,std::wstring smallpic, long& lx, long& ly);

private:
	ImageProc* imageProc;
};
