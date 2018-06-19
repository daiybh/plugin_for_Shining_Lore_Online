/*********************************************************************
	�����ǰ�������Ĳ��ģ��
	��ӭ��Ϊ�����������������
	���ģ�����°汾��֧�ַḻ�Ĳ����ͷ���ֵ��
	������ֹͣʹ��2005����ģ�壬��������ģ���������Ĳ��
	
  	����в����׵ĵط�����ӭ��email��rchu@vrbrothers.comѯ�ʡ�ף��ɹ���

	�ֵܹ�����  2007.11
*********************************************************************/

/*********************************************************************
 * ���µ����ݣ�һ�������������Ҫ������Ҳ����Ҫ�����޸�
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
 * ���ϵ����ݣ�һ�������������Ҫ������Ҳ����Ҫ�����޸�
*********************************************************************/

/*********************************************************************
	���������ÿ���������֧�����������
	�������Ҫдһ���Լ��������Ҫ��ѭ���²��裺
	1. ���ļ�CQMPlugin.cpp�����������ڿ���������ļ�
	2. ��Visual C++ 6.0�Ĳ˵���ѡ�� View->ClassWizard
	3. �ڵ����ĶԻ�����ѡ��Automation��壬��Add Method��ť
	4. ������д���Ĳ�����������֡��������ͺͲ�������
	   ��Ҫע����ǣ��������ֵ���ַ������ͣ���ѡ��BSTR
	   ����������ַ������ͣ���ѡ��LPCTSTR
	   �����Ҫ����ַ�Ĳ����������ڷ��ض��ֵ��������������ѡ��VARIANT*���������GetScreenResolution���������ʾ
	5. ��OK��ť�����ῴ��CQMPlugin.cpp����һ���հ׵ĺ�������ֻ��Ҫ��д�������ܼ���
	6. ��Ҳ������Automation�����ѡ��ɾ��ĳ�����еĺ�������ͬʱ������ĳ�����ɾ����Ӧ�ĺ�����
	7. �������m_DescriptionList�������д���Ĳ��˵���ͺ���˵��
	8. �����γ�DLL�ļ�����DLL�ļ����ڰ��������PluginĿ¼��
	9. �򿪰������飬����༭�ű����棬�򿪡���������壬��д�ű�������Ĳ����
*********************************************************************/

/*********************************************************************
 * ����:m_DescriptionList
 * ����԰�������һ����񣬱���е�ÿһ�д�����һ��������
 * ÿ�е�һ���ַ����ǲ����������֣����Ϊ�գ������������������ڶ����ַ����������������Ľ��ͣ�
 * �������ַ����ǲ���������ʾģ����Ϣ�����е�$1 $2 ... ����������ʾʱ���õ�һ���������ڶ���������... ����
 * ������Ҫ����һ����������ʱ�򣬾���Ҫ�ڱ�������һ�С�
*********************************************************************/
CQMPlugin::DESCRIPTION_LIST CQMPlugin::m_DescriptionList[] = 
{
	{"","�ļ�",""},
	{"WriteINI","�������ļ���дһ����ֵ(С����,����,д������,INI�ļ�·��)","�������ļ���дһ����ֵ,С����$1,����$2,����$3,ini�ļ�·��$4"},
	{"ReadINI","�������ļ����һ����ֵ(С����,����,INI�ļ�·��)[��������]","�������ļ����һ����ֵ,С����$1,����$2,ini�ļ�·��$3"},
	{"CopyFile","�����ļ�(Ŀ���ļ�,���·��)","�����ļ�,Ŀ���ļ�$1,���·��$2"},
	{"IsFileExit","�ж�һ���ļ��Ƿ����(Ŀ���ļ�)[���]","�ж�$1�ļ��Ƿ����"},
	{"DeleteFile","ɾ���ļ�(Ŀ���ļ�)","ɾ���ļ�$1"},
	{"MoveFile","�ƶ��ļ�(Ŀ���ļ�,���·��)","�ƶ��ļ�,��$1��$2"},
	{"CreateFolder","�����ļ���(�����ļ���·��)","�����ļ���,·��Ϊ$1"},
	{"DeleteFolder","ɾ���ļ���(Ŀ���ļ�)","ɾ��$1�ļ���"},
	{"ReNameFile","�������ļ�(Դ�ļ�,Ŀ���ļ�)","�������ļ�$1Ϊ$2"},
	{"SetAttrib","�����ļ�����(Ŀ���ļ�,��/д)","����$2����$1�ļ�����"},
	{"SetDate","�����ļ����ں�ʱ��(Ŀ���ļ�,���ں�ʱ��)","����$1�����ں�ʱ��Ϊ$2"},
//	{"ReadFile","���ı�����(Ŀ���ļ�·��)[�ı�����]","��$1���ı�����"},
//	{"WriteFile","д�ı�����(Ŀ���ļ�·��,д������)","��$1д������Ϊ$2���ı�����"},
	{"GetFileLength","�õ��ı����ݳ���(�ı�����)[���ݳ���]","�õ�$1�ı����ݵĳ���"},
	{"ReadFileEx","���ı�����(Ŀ���ļ�·��)[�ı�����]","��$1���ı�����"},
	{"WriteFileEx","д�ı�����(Ŀ���ļ�·��,д������)","��$1д������Ϊ$2���ı�����"},
	{"SelectFile","����ѡ���ļ��ĶԻ��򣬲��õ��û�ѡ����ļ�"},
	{"SelectDirectory","����ѡ���ļ��еĶԻ��򣬲��õ��û�ѡ����ļ���"},
	{"SeekFile","�����ļ��ĵ�ǰ��дλ��(�ļ����,��дλ��)","�����ļ��ĵ�ǰ��дλ��,�ļ����$1,��дλ��$2"},
	{"ReadLine","���ļ���ǰ�Ķ�дλ�ö�һ������(�ļ����)","���ļ���ǰ�Ķ�дλ�ö�һ������,�ļ����Ϊ$1"},
	{"WriteLine","д�ı�����(Ŀ���ļ�·��,д������)","��$1д������Ϊ$2���ı�����"},
	{"ReadFile","���ļ���ǰ�Ķ�дλ�ö�ȡһ�����ȵ�����(�ļ����,��ȡ����)","���ļ���ǰ�Ķ�дλ�ö�ȡһ�����ȵ�����,�ļ����$1,��ȡ����$2"},
	{"WriteFile","���ļ���ǰ��дλ��д��һ���ַ���(�ļ����,д������)","���ļ���ǰ��дλ��д��һ���ַ���,�ļ����Ϊ$1,д������Ϊ$2"},
	{"OpenFile","��һ���ļ����Ա���дʹ��(�ļ�ȫ·��)","�ļ�ȫ·��ΪS1"},
	{"CloseFile","�ر�һ���Ѿ��򿪵��ļ�(�ļ����)","�ļ����Ϊ$1"},
	{"ExistFile","�ж��ļ��Ƿ����","�ж�$1�ļ��Ƿ����"},
};

//����������Ҫ������Ҳ����Ҫ�޸�
const int CQMPlugin::m_iDescriptionListSize = sizeof(CQMPlugin::m_DescriptionList) / sizeof(CQMPlugin::DESCRIPTION_LIST);



/*********************************************************************
 * �����ǹ�����������
 * OnLoad �������ڲ��������ʱ���ã�����ֵͨ��ΪTRUE���������FALSE����ʾ����ܾ�������
 * OnExit �������ڲ����ж���ǵ��ã�û�з���ֵ
*********************************************************************/
BOOL OnLoad()
{
	return TRUE;
}

void OnExit()
{
	return;
}
//�������ļ���дһ����ֵ(С����,����,д������,INI�ļ�·��)	
long CQMPlugin::WriteINI(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszBuffer, LPCTSTR lpszINIFilePath) 
{
	return WritePrivateProfileString(lpszSectionName,lpszKeyName,lpszBuffer,lpszINIFilePath);
}
//�������ļ����һ����ֵ(С����,����,INI�ļ�·��)[��������]
BSTR CQMPlugin::ReadINI(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszINIFilePath) 
{
	CString strResult;
	char lpszBuffer[4096] = {0};	
	GetPrivateProfileString(lpszSectionName,lpszKeyName,"",lpszBuffer,sizeof(lpszBuffer),lpszINIFilePath);
	strResult = lpszBuffer;		//���Ƶ�lpszRetVal,,����������������һ���ַ���
	return strResult.AllocSysString();
}
//�����ļ�(Ŀ���ļ�,���·��)	
long CQMPlugin::CopyFile(LPCTSTR lpszSourceFile, LPCTSTR lpszTargetFile) 
{
	return ::CopyFile(lpszSourceFile,lpszTargetFile,FALSE);
}
//�ж�һ���ļ��Ƿ����(Ŀ���ļ�)[���]
BOOL CQMPlugin::IsFileExit(LPCTSTR lpszSourceFile) 
{
    DWORD dwFileAttr = GetFileAttributes(lpszSourceFile);//ֻ��һ���ַ������������Բ��÷ָ������

	if((int)dwFileAttr < 0)			//�������û���ҵ�
		return FALSE;
	else if(dwFileAttr & FILE_ATTRIBUTE_DIRECTORY)		//���ļ���
		return FALSE;
	else						//���ļ�
		return TRUE;
}
//ɾ���ļ�(Ŀ���ļ�)	
long CQMPlugin::DeleteFile(LPCTSTR FileName) 
{
	return ::DeleteFile(FileName);
}
//�ƶ��ļ�(Ŀ���ļ�,���·��)	
long CQMPlugin::MoveFile(LPCTSTR lpszSourceFile, LPCTSTR lpszTargetFile) 
{
	return ::MoveFile(lpszSourceFile,lpszTargetFile);
}
//�����ļ���(�����ļ���·��)	
long CQMPlugin::CreateFolder(LPCTSTR lpszDirectory) 
{
	return _mkdir(lpszDirectory); 
}
//ɾ���ļ���(Ŀ���ļ�)
long CQMPlugin::DeleteFolder(LPCTSTR lpszDirectory) 
{
	return _rmdir(lpszDirectory);  
}
//�������ļ�(ԭ�ļ�$1,Ŀ���ļ�$2)	
long CQMPlugin::ReNameFile(LPCTSTR oldName,LPCTSTR newName) 
{
	return rename(oldName,newName);
}
//�����ļ�����(Ŀ���ļ�,��/д)
BOOL CQMPlugin::SetAttrib(LPCTSTR lpszFilePath, BOOL Sign) 
{
	CFileStatus rStatus;
	CFile::GetStatus(lpszFilePath,rStatus);//����ļ�����������
	if (Sign==0)
	{
		rStatus.m_attribute=rStatus.m_attribute & 0x3E;   //����ļ�Ϊֻ���ģ���ֻ������ȥ��
	}
	else
		rStatus.m_attribute=rStatus.m_attribute | 0x01;   //����ļ�Ϊ���ģ���ֻ�����Թ���
	CFile::SetStatus(lpszFilePath, rStatus );//�����ļ�����������
	return TRUE;
}
//�����ļ����ں�ʱ��(Ŀ���ļ�,���ں�ʱ��)
long CQMPlugin::SetDate(LPCTSTR lpszFileName, LPCTSTR lpLastWriteTime) 
{
//	CString lpLastWriteTime="1999-09-09 07:20:20",lpszFileName="C://������.txt";
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

//�õ��ı����ݳ���(�ı�����)[���ݳ���]
long CQMPlugin::GetFileLength(LPCTSTR lpszFileName) 
{
	CFile   file;   BOOL sign;
	sign=file.Open(lpszFileName,CFile::modeRead);
	if (sign==0)
	{
	//	MessageBox("���ļ�ʧ��");
		return FALSE;
	}
	DWORD   filelength   =   file.GetLength();
//	CString str;
//	str.Format("�ļ�����=%d",filelength);
//	MessageBox(str);
	file.Close();
	return filelength;
}

//����ѡ���ļ��ĶԻ��򣬲��õ��û�ѡ����ļ�
BSTR CQMPlugin::SelectFile() 
{
	CString strResult;
	
	char lpszBuffer[4096] = {0};
	OPENFILENAME sOpenFileDialogInfo = {0};
	sOpenFileDialogInfo.lStructSize = sizeof(sOpenFileDialogInfo);
	sOpenFileDialogInfo.lpstrFile = lpszBuffer;
	sOpenFileDialogInfo.nMaxFile = sizeof(lpszBuffer);
	sOpenFileDialogInfo.Flags = 6148;
	if(GetOpenFileName(&sOpenFileDialogInfo) == 0)//���ѡ����"ȡ��"
		return NULL;
	strResult = lpszBuffer;
	return strResult.AllocSysString();
}

//����ѡ���ļ��еĶԻ��򣬲��õ��û�ѡ����ļ���
BSTR CQMPlugin::SelectDirectory() 
{
	CString lpszRetVal;
	char str[4096] = {0};
	BROWSEINFO sBrowseDirectoryInfo = {0};
	LPITEMIDLIST lpSelectDirectoryReturn = NULL;
	sBrowseDirectoryInfo.lpszTitle = "";
	sBrowseDirectoryInfo.ulFlags = BIF_RETURNONLYFSDIRS;
    
	lpSelectDirectoryReturn = SHBrowseForFolder(&sBrowseDirectoryInfo);
	
	if(lpSelectDirectoryReturn == NULL)//û������ѡ����ѡ���ˡ�ȡ������
		return NULL;
	SHGetPathFromIDList(lpSelectDirectoryReturn,str);//������޸�str,����������������һ���ַ���
    lpszRetVal = str;
	return lpszRetVal.AllocSysString();
}

//�����ļ��ĵ�ǰ��дλ��
long CQMPlugin::SeekFile(long lpszHandle, long lpszOffset) 
{
	SetFilePointer((HANDLE)lpszHandle,lpszOffset,NULL,FILE_BEGIN);
	return 0;
}

//���ļ���ǰ�Ķ�дλ�ö�һ������
BSTR CQMPlugin::ReadLine(long hFile) 
{
	CString strResult;
	
	DWORD dwNumberOfBytesRead;
	char lpszCurrentReadPos[4096];
	
	//windows api��Ȼû�ж�ȡһ�еĺ�����ֻ���Լ�д�ˡ�Ч�ʿ����е�ͣ��������ð�
	int i=0;
	do 
	{
		::ReadFile((HANDLE)hFile,lpszCurrentReadPos+i,1,&dwNumberOfBytesRead,NULL);
		if(*(lpszCurrentReadPos+i) == '\n')//������ĩ
			break;
		i++;
	} while(dwNumberOfBytesRead);
	*(lpszCurrentReadPos+i)= 0;//�����ַ���������ʾ
	strResult = lpszCurrentReadPos;
	return strResult.AllocSysString();
}
//ͬWriteFile�������д��һ���س����з���
long CQMPlugin::WriteLine(long lpszHandle, LPCTSTR lpszWriteContent) 
{
	DWORD dwNumberOfBytesWrite;
	strcat((char*)lpszWriteContent,"\r\n");//��WriteFile��Ψһ�����Ǻ�����˻س����з�
	return ::WriteFile((HANDLE)lpszHandle,lpszWriteContent,strlen(lpszWriteContent),&dwNumberOfBytesWrite,NULL);
}
//���ı�����(Ŀ���ļ�·��)[�ı�����]
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
//д�ı�����(Ŀ���ļ�·��,д������)
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
//���ļ���ǰ�Ķ�дλ�ö�ȡһ�����ȵ�����
BSTR CQMPlugin::ReadFile(long lpszHandle, long lpszReadLength) 
{
	CString strResult;
	DWORD dwNumberOfBytesRead;
	char str[4096];
	::ReadFile((HANDLE)lpszHandle,str,lpszReadLength,&dwNumberOfBytesRead,NULL);
	str[dwNumberOfBytesRead] = 0;   //�����ַ���������ʾ
	strResult = str;
	return strResult.AllocSysString();
}
//���ļ���ǰ��дλ��д��һ���ַ���
long CQMPlugin::WriteFile(long lpszHandle, LPCTSTR lpszWriteContent) 
{
	DWORD dwNumberOfBytesWrite;
	
	return ::WriteFile((HANDLE)lpszHandle,lpszWriteContent,strlen(lpszWriteContent),&dwNumberOfBytesWrite,NULL);
}
//�ж��ļ����ļ����Ƿ����
long CQMPlugin::ExistFile(LPCTSTR FileAttr) 
{
	DWORD dwFileAttr = GetFileAttributes(FileAttr);//ֻ��һ���ַ������������Բ��÷ָ������
	
	if((int)dwFileAttr < 0)			//�������û���ҵ�
		return 0;
	else if(dwFileAttr & FILE_ATTRIBUTE_DIRECTORY)		//���ļ���
		return 2;
	else						//���ļ�
		return 1;
}
//��һ���ļ����Ա���дʹ��

long CQMPlugin::OpenFile(LPCTSTR FileName) 
{
	return (long)CreateFile(FileName,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
}

//�ر�һ���Ѿ��򿪵��ļ����ļ��رպ�����������Ч
long CQMPlugin::CloseFile(long hwd) 
{
	return CloseHandle((HANDLE)hwd);
}
