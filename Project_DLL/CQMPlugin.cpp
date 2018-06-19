/*********************************************************************
	这里是按键精灵的插件模板
	欢迎您为按键精灵制作插件！
	这个模板是新版本，支持丰富的参数和返回值等
	建议您停止使用2005版插件模板，今后用这个模板制作您的插件
	
  	如果有不明白的地方，欢迎发email到rchu@vrbrothers.com询问。祝你成功！

	兄弟工作组  2007.11
*********************************************************************/

/*********************************************************************
 * 以下的内容，一般情况下您不需要看懂，也不需要进行修改
*********************************************************************/
#include "stdafx.h"
#include "CQMPlugin.h"
#include   <direct.h>  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CQMPlugin, CCmdTarget)
	//{{AFX_MSG_MAP(CQMPlugin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifdef _DEBUG
	#pragma comment(lib,"CommonLibD.lib")
#else
	#pragma comment(lib,"CommonLib.lib")
#endif

BEGIN_DISPATCH_MAP(CQMPlugin, CCmdTarget)
	DISP_FUNCTION(CQMPlugin, "Get_Plugin_Description", GetPluginDescription, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "Get_Plugin_Interpret_Template", GetPluginInterpretTemplate, VT_BSTR, VTS_BSTR)
	//{{AFX_DISPATCH_MAP(CQMPlugin)
	DISP_FUNCTION(CQMPlugin, "WriteINI", WriteINI, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "ReadINI", ReadINI, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "CopyFile", CopyFile, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "IsFileExit", IsFileExit, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "DeleteFile", DeleteFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "MoveFile", MoveFile, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "CreateFolder", CreateFolder, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "DeleteFolder", DeleteFolder, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "ReNameFile", ReNameFile, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "SetAttrib", SetAttrib, VT_BOOL, VTS_BSTR VTS_BOOL)
	DISP_FUNCTION(CQMPlugin, "SetDate", SetDate, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "GetFileLength", GetFileLength, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "SelectFile", SelectFile, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CQMPlugin, "SelectDirectory", SelectDirectory, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CQMPlugin, "SeekFile", SeekFile, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CQMPlugin, "ReadLine", ReadLine, VT_BSTR, VTS_I4)
	DISP_FUNCTION(CQMPlugin, "WriteLine", WriteLine, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "ReadFileEx", ReadFileEx, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "WriteFileEx", WriteFileEx, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "ReadFile", ReadFile, VT_BSTR, VTS_I4 VTS_I4)
	DISP_FUNCTION(CQMPlugin, "WriteFile", WriteFile, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "ExistFile", ExistFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "OpenFile", OpenFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CQMPlugin, "CloseFile", CloseFile, VT_I4, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CQMPlugin, "QMPlugin.File", 0x57477331, 0x126E, 0x4FC8, 0xB4, 0x30, 0x1C, 0x61, 0x43, 0x48, 0x4A, 0xA9)

BOOL g_bEnablePluginValidate = TRUE;
/*********************************************************************
 * 以上的内容，一般情况下您不需要看懂，也不需要进行修改
*********************************************************************/

/*********************************************************************
	按键精灵的每个插件可以支持若干条命令。
	如果您需要写一条自己的命令，需要遵循以下步骤：
	1. 打开文件CQMPlugin.cpp，就是您现在看到的这个文件
	2. 在Visual C++ 6.0的菜单中选择 View->ClassWizard
	3. 在弹出的对话框中选择Automation面板，按Add Method按钮
	4. 依次填写您的插件函数的名字、返回类型和参数类型
	   需要注意的是，如果返回值是字符串类型，请选择BSTR
	   如果参数是字符串类型，请选择LPCTSTR
	   如果需要传地址的参数（可用于返回多个值），参数类型请选择VARIANT*，如下面的GetScreenResolution插件函数所示
	5. 按OK按钮，您会看到CQMPlugin.cpp有了一个空白的函数，您只需要填写函数功能即可
	6. 您也可以在Automation面板中选择删除某个已有的函数，并同时在下面的程序中删除对应的函数体
	7. 在下面的m_DescriptionList表格中填写您的插件说明和函数说明
	8. 编译形成DLL文件，把DLL文件放在按键精灵的Plugin目录下
	9. 打开按键精灵，进入编辑脚本界面，打开“插件命令”面板，编写脚本测试你的插件！
*********************************************************************/

/*********************************************************************
 * 名称:m_DescriptionList
 * 你可以把它看成一个表格，表格中的每一行代表了一条插件命令。
 * 每行第一个字符串是插件命令的名字（如果为空，则代表整个插件）；第二个字符串是这条插件命令的解释；
 * 第三个字符串是插件命令的显示模板信息，其中的$1 $2 ... 等内容再显示时将用第一个参数、第二个参数、... 代替
 * 当你需要新增一条插件命令的时候，就需要在表格里面加一行。
*********************************************************************/
CQMPlugin::DESCRIPTION_LIST CQMPlugin::m_DescriptionList[] = 
{
	{"","文件",""},
	{"WriteINI","向配置文件里写一个键值(小节名,键名,写入内容,INI文件路径)","向配置文件里写一个键值,小节名$1,键名$2,内容$3,ini文件路径$4"},
	{"ReadINI","从配置文件里读一个键值(小节名,键名,INI文件路径)[读出内容]","从配置文件里读一个键值,小节名$1,键名$2,ini文件路径$3"},
	{"CopyFile","拷贝文件(目标文件,存放路径)","拷贝文件,目标文件$1,存放路径$2"},
	{"IsFileExit","判断一个文件是否存在(目标文件)[真假]","判断$1文件是否存在"},
	{"DeleteFile","删除文件(目标文件)","删除文件$1"},
	{"MoveFile","移动文件(目标文件,存放路径)","移动文件,从$1到$2"},
	{"CreateFolder","建立文件夹(创建文件夹路径)","建立文件夹,路径为$1"},
	{"DeleteFolder","删除文件夹(目标文件)","删除$1文件夹"},
	{"ReNameFile","重命名文件(源文件,目标文件)","重命名文件$1为$2"},
	{"SetAttrib","设置文件属性(目标文件,读/写)","根据$2设置$1文件属性"},
	{"SetDate","设置文件日期和时间(目标文件,日期和时间)","设置$1的日期和时间为$2"},
//	{"ReadFile","读文本内容(目标文件路径)[文本内容]","读$1的文本内容"},
//	{"WriteFile","写文本内容(目标文件路径,写入内容)","向$1写入内容为$2的文本内容"},
	{"GetFileLength","得到文本内容长度(文本内容)[内容长度]","得到$1文本内容的长度"},
	{"ReadFileEx","读文本内容(目标文件路径)[文本内容]","读$1的文本内容"},
	{"WriteFileEx","写文本内容(目标文件路径,写入内容)","向$1写入内容为$2的文本内容"},
	{"SelectFile","弹出选择文件的对话框，并得到用户选择的文件"},
	{"SelectDirectory","弹出选择文件夹的对话框，并得到用户选择的文件夹"},
	{"SeekFile","设置文件的当前读写位置(文件句柄,读写位置)","设置文件的当前读写位置,文件句柄$1,读写位置$2"},
	{"ReadLine","从文件当前的读写位置读一行内容(文件句柄)","从文件当前的读写位置读一行内容,文件句柄为$1"},
	{"WriteLine","写文本内容(目标文件路径,写入内容)","向$1写入内容为$2的文本内容"},
	{"ReadFile","从文件当前的读写位置读取一定长度的内容(文件句柄,读取长度)","从文件当前的读写位置读取一定长度的内容,文件句柄$1,读取长度$2"},
	{"WriteFile","往文件当前读写位置写入一个字符串(文件句柄,写入内容)","往文件当前读写位置写入一个字符串,文件句柄为$1,写入内容为$2"},
	{"OpenFile","打开一个文件，以备读写使用(文件全路径)","文件全路劲为S1"},
	{"CloseFile","关闭一个已经打开的文件(文件句柄)","文件句柄为$1"},
	{"ExistFile","判断文件是否存在","判断$1文件是否存在"},
};

//这行您不需要看懂，也不需要修改
const int CQMPlugin::m_iDescriptionListSize = sizeof(CQMPlugin::m_DescriptionList) / sizeof(CQMPlugin::DESCRIPTION_LIST);



/*********************************************************************
 * 下面是公共处理函数。
 * OnLoad 函数会在插件被加载时调用，返回值通常为TRUE。如果返回FALSE，表示插件拒绝被加载
 * OnExit 函数会在插件被卸载是调用，没有返回值
*********************************************************************/
BOOL OnLoad()
{
	return TRUE;
}

void OnExit()
{
	return;
}
//向配置文件里写一个键值(小节名,键名,写入内容,INI文件路径)	
long CQMPlugin::WriteINI(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszBuffer, LPCTSTR lpszINIFilePath) 
{
	return WritePrivateProfileString(lpszSectionName,lpszKeyName,lpszBuffer,lpszINIFilePath);
}
//从配置文件里读一个键值(小节名,键名,INI文件路径)[读出内容]
BSTR CQMPlugin::ReadINI(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszINIFilePath) 
{
	CString strResult;
	char lpszBuffer[4096] = {0};	
	GetPrivateProfileString(lpszSectionName,lpszKeyName,"",lpszBuffer,sizeof(lpszBuffer),lpszINIFilePath);
	strResult = lpszBuffer;		//复制到lpszRetVal,,因此这个插件命令将返回一个字符串
	return strResult.AllocSysString();
}
//拷贝文件(目标文件,存放路径)	
long CQMPlugin::CopyFile(LPCTSTR lpszSourceFile, LPCTSTR lpszTargetFile) 
{
	return ::CopyFile(lpszSourceFile,lpszTargetFile,FALSE);
}
//判断一个文件是否存在(目标文件)[真假]
BOOL CQMPlugin::IsFileExit(LPCTSTR lpszSourceFile) 
{
    DWORD dwFileAttr = GetFileAttributes(lpszSourceFile);//只有一个字符串参数，可以不用分割参数了

	if((int)dwFileAttr < 0)			//出错或者没有找到
		return FALSE;
	else if(dwFileAttr & FILE_ATTRIBUTE_DIRECTORY)		//是文件夹
		return FALSE;
	else						//是文件
		return TRUE;
}
//删除文件(目标文件)	
long CQMPlugin::DeleteFile(LPCTSTR FileName) 
{
	return ::DeleteFile(FileName);
}
//移动文件(目标文件,存放路径)	
long CQMPlugin::MoveFile(LPCTSTR lpszSourceFile, LPCTSTR lpszTargetFile) 
{
	return ::MoveFile(lpszSourceFile,lpszTargetFile);
}
//建立文件夹(创建文件夹路径)	
long CQMPlugin::CreateFolder(LPCTSTR lpszDirectory) 
{
	return _mkdir(lpszDirectory); 
}
//删除文件夹(目标文件)
long CQMPlugin::DeleteFolder(LPCTSTR lpszDirectory) 
{
	return _rmdir(lpszDirectory);  
}
//重命名文件(原文件$1,目标文件$2)	
long CQMPlugin::ReNameFile(LPCTSTR oldName,LPCTSTR newName) 
{
	return rename(oldName,newName);
}
//设置文件属性(目标文件,读/写)
BOOL CQMPlugin::SetAttrib(LPCTSTR lpszFilePath, BOOL Sign) 
{
	CFileStatus rStatus;
	CFile::GetStatus(lpszFilePath,rStatus);//获得文件的属性设置
	if (Sign==0)
	{
		rStatus.m_attribute=rStatus.m_attribute & 0x3E;   //如果文件为只读的，将只读属性去掉
	}
	else
		rStatus.m_attribute=rStatus.m_attribute | 0x01;   //如果文件为读的，将只读属性钩上
	CFile::SetStatus(lpszFilePath, rStatus );//更改文件的属性设置
	return TRUE;
}
//设置文件日期和时间(目标文件,日期和时间)
long CQMPlugin::SetDate(LPCTSTR lpszFileName, LPCTSTR lpLastWriteTime) 
{
//	CString lpLastWriteTime="1999-09-09 07:20:20",lpszFileName="C://黄明发.txt";
	// TODO: Add your control notification handler code here
	int len=((CString)lpLastWriteTime).GetLength();
	int index0=((CString)lpLastWriteTime).Find('-',0);
	int year=atoi(((CString)lpLastWriteTime).Left(index0));
	CString sTemp0=((CString)lpLastWriteTime).Right(len-index0-1);
	int index1=sTemp0.Find('-',0);
	int month=atoi(sTemp0.Left(index1));
	CString sTemp1=((CString)lpLastWriteTime).Right(len-index0-index1-2);
	int index2=sTemp1.Find(' ',0);
	int day=atoi(sTemp1.Left(index2));
	CString sTmep2=((CString)lpLastWriteTime).Right(len-index0-index1-index2-3);
	int index3=sTmep2.Find(':',0);
	int hour=atoi(sTmep2.Left(index3));
	CString sTmep3=((CString)lpLastWriteTime).Right(len-index0-index1-index2-index3-4);
	int index4=sTmep3.Find(':',0);
	int min=atoi(sTmep3.Left(index4));
	
	CString sTmep4=((CString)lpLastWriteTime).Right(len-index0-index1-index2-index3-index4-5);
	int second=atoi(sTmep4);
	SYSTEMTIME systime;

	if( hour>=12 )
	{ 
		systime.wDay=day;
		systime.wHour=hour-8;
	}
	if(12>=hour&&hour>=8)
	{
		systime.wDay=day;
		systime.wHour=hour-8;
	}
	if (hour<8)
	{
		systime.wDay=day-1;
		systime.wHour=hour+16;
	}
	systime.wYear=year;
	systime.wMonth=month;
	systime.wMinute=min;
	systime.wDayOfWeek=0;
	systime.wMilliseconds=0;
	systime.wSecond=second;
	FILETIME lastWriteTimeme;
	int a =SystemTimeToFileTime(&systime,&lastWriteTimeme); 
	char buffer[1024]={0};
	HFILE  handle=::OpenFile(lpszFileName,(LPOFSTRUCT)buffer,OF_WRITE);
	if(handle==HFILE_ERROR)
	{
		return FALSE;
	}
	SetFileTime((HANDLE)handle,&lastWriteTimeme,&lastWriteTimeme,&lastWriteTimeme);
	_lclose(handle);
	return TRUE;
}

//得到文本内容长度(文本内容)[内容长度]
long CQMPlugin::GetFileLength(LPCTSTR lpszFileName) 
{
	CFile   file;   BOOL sign;
	sign=file.Open(lpszFileName,CFile::modeRead);
	if (sign==0)
	{
	//	MessageBox("打开文件失败");
		return FALSE;
	}
	DWORD   filelength   =   file.GetLength();
//	CString str;
//	str.Format("文件长度=%d",filelength);
//	MessageBox(str);
	file.Close();
	return filelength;
}

//弹出选择文件的对话框，并得到用户选择的文件
BSTR CQMPlugin::SelectFile() 
{
	CString strResult;
	
	char lpszBuffer[4096] = {0};
	OPENFILENAME sOpenFileDialogInfo = {0};
	sOpenFileDialogInfo.lStructSize = sizeof(sOpenFileDialogInfo);
	sOpenFileDialogInfo.lpstrFile = lpszBuffer;
	sOpenFileDialogInfo.nMaxFile = sizeof(lpszBuffer);
	sOpenFileDialogInfo.Flags = 6148;
	if(GetOpenFileName(&sOpenFileDialogInfo) == 0)//如果选择了"取消"
		return NULL;
	strResult = lpszBuffer;
	return strResult.AllocSysString();
}

//弹出选择文件夹的对话框，并得到用户选择的文件夹
BSTR CQMPlugin::SelectDirectory() 
{
	CString lpszRetVal;
	char str[4096] = {0};
	BROWSEINFO sBrowseDirectoryInfo = {0};
	LPITEMIDLIST lpSelectDirectoryReturn = NULL;
	sBrowseDirectoryInfo.lpszTitle = "";
	sBrowseDirectoryInfo.ulFlags = BIF_RETURNONLYFSDIRS;
    
	lpSelectDirectoryReturn = SHBrowseForFolder(&sBrowseDirectoryInfo);
	
	if(lpSelectDirectoryReturn == NULL)//没有作出选择（如选择了“取消”）
		return NULL;
	SHGetPathFromIDList(lpSelectDirectoryReturn,str);//这里会修改str,因此这个插件命令将返回一个字符串
    lpszRetVal = str;
	return lpszRetVal.AllocSysString();
}

//设置文件的当前读写位置
long CQMPlugin::SeekFile(long lpszHandle, long lpszOffset) 
{
	SetFilePointer((HANDLE)lpszHandle,lpszOffset,NULL,FILE_BEGIN);
	return 0;
}

//从文件当前的读写位置读一行内容
BSTR CQMPlugin::ReadLine(long hFile) 
{
	CString strResult;
	
	DWORD dwNumberOfBytesRead;
	char lpszCurrentReadPos[4096];
	
	//windows api居然没有读取一行的函数，只好自己写了。效率可能有点低，将就着用吧
	int i=0;
	do 
	{
		::ReadFile((HANDLE)hFile,lpszCurrentReadPos+i,1,&dwNumberOfBytesRead,NULL);
		if(*(lpszCurrentReadPos+i) == '\n')//读到行末
			break;
		i++;
	} while(dwNumberOfBytesRead);
	*(lpszCurrentReadPos+i)= 0;//加上字符串结束标示
	strResult = lpszCurrentReadPos;
	return strResult.AllocSysString();
}
//同WriteFile，但会多写入一个回车换行符号
long CQMPlugin::WriteLine(long lpszHandle, LPCTSTR lpszWriteContent) 
{
	DWORD dwNumberOfBytesWrite;
	strcat((char*)lpszWriteContent,"\r\n");//和WriteFile的唯一区别是后面多了回车换行符
	return ::WriteFile((HANDLE)lpszHandle,lpszWriteContent,strlen(lpszWriteContent),&dwNumberOfBytesWrite,NULL);
}
//读文本内容(目标文件路径)[文本内容]
BSTR CQMPlugin::ReadFileEx(LPCTSTR lpszFileName) 
{
	CStdioFile   myFile; CString sTemp;    
	CString   ReadFileString;
	
	if(myFile.Open(lpszFileName, CFile::modeRead)   ==   TRUE)     
	{     
		while(myFile.ReadString(ReadFileString)   !=   FALSE)     
		{     
			sTemp+=ReadFileString+"|";
		}
	}     
	return sTemp.AllocSysString();
}
//写文本内容(目标文件路径,写入内容)
long CQMPlugin::WriteFileEx(LPCTSTR lpszFileName, LPCTSTR lpszBeWrite) 
{
	CStdioFile   myFile;//CString sTemp;    
	CString   WriteFileString,ReadFileString;
	if(myFile.Open(lpszFileName, CFile::modeReadWrite)   ==   TRUE)     
    {     
		while(myFile.ReadString(ReadFileString)   !=   FALSE)     
		{     
		}
	}
	else
	{
		myFile.Open(lpszFileName,CFile::modeCreate|CFile::modeWrite);
	}
	WriteFileString=lpszBeWrite;
	myFile.WriteString(WriteFileString+"\r\n"  );       
	return TRUE;
}
//从文件当前的读写位置读取一定长度的内容
BSTR CQMPlugin::ReadFile(long lpszHandle, long lpszReadLength) 
{
	CString strResult;
	DWORD dwNumberOfBytesRead;
	char str[4096];
	::ReadFile((HANDLE)lpszHandle,str,lpszReadLength,&dwNumberOfBytesRead,NULL);
	str[dwNumberOfBytesRead] = 0;   //加上字符串结束标示
	strResult = str;
	return strResult.AllocSysString();
}
//往文件当前读写位置写入一个字符串
long CQMPlugin::WriteFile(long lpszHandle, LPCTSTR lpszWriteContent) 
{
	DWORD dwNumberOfBytesWrite;
	
	return ::WriteFile((HANDLE)lpszHandle,lpszWriteContent,strlen(lpszWriteContent),&dwNumberOfBytesWrite,NULL);
}
//判断文件或文件夹是否存在
long CQMPlugin::ExistFile(LPCTSTR FileAttr) 
{
	DWORD dwFileAttr = GetFileAttributes(FileAttr);//只有一个字符串参数，可以不用分割参数了
	
	if((int)dwFileAttr < 0)			//出错或者没有找到
		return 0;
	else if(dwFileAttr & FILE_ATTRIBUTE_DIRECTORY)		//是文件夹
		return 2;
	else						//是文件
		return 1;
}
//打开一个文件，以备读写使用

long CQMPlugin::OpenFile(LPCTSTR FileName) 
{
	return (long)CreateFile(FileName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
}

//关闭一个已经打开的文件。文件关闭后，其句柄不再有效
long CQMPlugin::CloseFile(long hwd) 
{
	return CloseHandle((HANDLE)hwd);
}
