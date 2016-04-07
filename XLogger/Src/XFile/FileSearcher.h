#pragma once

#include "FileBase.h"

class CFileSearcher
{
public:
	CFileSearcher(void);
	virtual ~CFileSearcher(void);

	// ���Ҳ����ļ������ڱ��ݸ�����
	virtual BOOL Search(const CFileBase *FileBase, SYSTEMTIME Time, CAtlArray<BACKUPFILE> &arrFileNames);

	// ���ҵ�ǰҪд����ļ������ļ��Ѿ����ڴ���
	virtual BOOL Search(const CFileBase *FileBase, SYSTEMTIME Time, CString &strFileName);

protected:
	BOOL FilesSearch(CString strPath, CString strCondition, 
		BOOL Subdirectory, CAtlArray<BACKUPFILE> &arrFileNames);
	virtual BOOL AddFile(const BACKUPFILE &sFileInfo, CAtlArray<BACKUPFILE> &arrFileNames);
};
