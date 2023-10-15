#include "op.h"
#include "imageProc/ImageProc.h"


long OP::FindPic(std::wstring bigPic, std::wstring smallpic, long& lx, long& ly)
{
	if (imageProc == nullptr) {
		imageProc = new ImageProc();
	}
	imageProc->_src.read(bigPic.data());

	imageProc->Capture(bigPic);
	return imageProc->FindPic(smallpic, L"000000", 1.0, 0, lx, ly);
}
