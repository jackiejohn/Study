#include "stdafx.h"
#include <windows.h>
#include <mstask.h>
#include <tchar.h>

BOOL CreateTask(
    WCHAR *in_wszTaskName,//��������
    WCHAR *in_wszTargetName,//����������
    WCHAR *in_wszStartPath,//��ʼλ��
    WCHAR *in_wszComment,//��ע��Ϣ
    WCHAR *in_wszAccountName,//�û���
    WCHAR *in_wszPwd,//�û�����
    SYSTEMTIME *in_pStartTime,//����ʼʱ��
    SYSTEMTIME *in_pEndTime,//�������ʱ��
    DWORD in_dwStartType)//��������
{
    BOOL bResult = FALSE;
    HRESULT hr = S_OK;
    ITaskScheduler *pITS;
    SYSTEMTIME time;
    GetLocalTime(&time);

    if(!in_wszTaskName|| !in_wszTargetName)//������Ϊ��
    {
        return bResult;
    }

    /*CoCreateInstance(*/
    ::CoInitialize(NULL);
    hr = CoCreateInstance(CLSID_CTaskScheduler,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_ITaskScheduler,
        (void **) &pITS);
    if (FAILED(hr))
    {
        //printf("Failed calling CoCreateInstance, error = 0x%x\n",hr);
    }
    else
    {
        ITask *pITask;
        pITS->Delete(in_wszTaskName);
        hr = pITS->NewWorkItem(in_wszTaskName, // Name of task
            CLSID_CTask, // Class identifier
            IID_ITask, // Interface identifier
            (IUnknown**)&pITask); // Address of task
        if (FAILED(hr))
        {
            //printf("Failed calling NewWorkItem, error = 0x%x\n",hr);
        }
        else
        {
            IPersistFile *pIPersistFile;
            hr = pITask->QueryInterface(IID_IPersistFile,(void **)&pIPersistFile);
            if (FAILED(hr))
            {
                //printf("Failed calling QueryInterface, error = 0x%x\n",hr);
            }
            else
            {
                hr = pITask->SetApplicationName(in_wszTargetName);//���������������
                if (FAILED(hr))
                {
                    //printf("Failed calling SetApplicationName, error = 0x%x\n",hr);
                }
                pITask->SetWorkingDirectory(in_wszStartPath);
                if(in_wszComment)// ���ñ�ע��Ϣ
                {
                    hr = pITask->SetComment(in_wszComment);
                    if (FAILED(hr))
                    {
                        //printf("Failed calling SetComment, error = 0x%x\n",hr);
                    }
                }

                if(in_wszAccountName)//�����û���������
                {
                    hr = pITask->SetAccountInformation(in_wszAccountName,NULL);
                    if (FAILED(hr))
                    {
                        //printf("Failed calling SetAccountInformation, error = 0x%x\n",hr);
                    }
                }

                DWORD dwFlag;
                dwFlag = TASK_FLAG_INTERACTIVE; //ʹ�������ʹ��
                hr = pITask->GetFlags(&dwFlag);//�Ȼ�ñ�����flag
                if (FAILED(hr))
                {
                    //printf("Failed calling GetFlags, error = 0x%x\n",hr);
                }
                //printf("dwFlag = 0x%x\n",dwFlag);


                //dwFlag |= TASK_FLAG_DELETE_WHEN_DONE; //������ɺ�ɾ������
                hr = pITask->SetFlags(dwFlag);
                if (FAILED(hr))
                {
                    //printf("Failed calling SetFlags, error = 0x%x\n",hr);
                }


                //�������񴥷�ʱ��
                ITaskTrigger *pITaskTrigger;
                WORD piNewTrigger;
                hr = pITask->CreateTrigger(&piNewTrigger, &pITaskTrigger);
                //piNewTrigger : A pointer to the returned trigger index value of the new trigger.
                //pITaskTrigger : A pointer to a pointer to an ITaskTrigger interface.
                if (FAILED(hr))
                {
                    //wprintf(L"Failed calling ITask::CreatTrigger: error = 0x%x\n",hr);
                }
                else
                {
                    TASK_TRIGGER pTrigger;
                    ZeroMemory(&pTrigger, sizeof (TASK_TRIGGER));
                    //UpdateData(true);
                    // Add code to set trigger structure?
                    pTrigger.wBeginDay = in_pStartTime->wDay; // Required
                    pTrigger.wBeginMonth = in_pStartTime->wMonth; // Required
                    pTrigger.wBeginYear = in_pStartTime->wYear; // Required
                    //pTrigger.wStartHour = m_dtDatetime.GetHour();
                    //pTrigger.wStartMinute = m_dtDatetime.GetMinute();
                    pTrigger.cbTriggerSize = sizeof (TASK_TRIGGER);
                    if(in_pEndTime)
                    {
                        pTrigger.wEndDay = in_pEndTime->wDay;
                        pTrigger.wEndMonth = in_pEndTime->wMonth;
                        pTrigger.wEndYear = in_pEndTime->wYear;
                    }
                    pTrigger.TriggerType = /*TASK_TIME_TRIGGER_ONCE*/(TASK_TRIGGER_TYPE)in_dwStartType;//���ô�������
                    hr = pITaskTrigger->GetTrigger(&pTrigger);
                    CTime time;

                    m_TimeBegin.GetTime(time);
                    pTrigger.wStartHour = time.GetHour();
                    pTrigger.wStartMinute = time.GetMinute();
                    //pTrigger.rgFlags = TASK_TRIGGER_FLAG_HAS_END_DATE;
                    hr = pITaskTrigger->SetTrigger(&pTrigger);
                    if (FAILED(hr))
                    {
                        //wprintf(L"Failed calling ITaskTrigger::SetTrigger: error = 0x%x\n",hr);
                        //wprintf(L"ErrorCode = %d\n",GetLastError());
                    }
                    else
                    {
                        IPersistFile *pIPersistFile;
                        hr = pITask->QueryInterface(IID_IPersistFile,(void **)&pIPersistFile);
                        if (FAILED(hr))
                        {
                            //wprintf(L"Failed calling QueryInterface::QueryInterface: error = 0x%x\n",hr);
                        }
                        else
                        {
                            hr = pIPersistFile->Save(NULL,TRUE);
                            if (FAILED(hr))
                            {
                                //wprintf(L"Failed calling IPersistFile::Save: error = 0x%x\n",hr);
                            }
                            else
                            {
                                //wprintf(L"The trigger was created and IPersistFile::Save was called to save the new trigger to disk.\n");
                                bResult=TRUE;
                            }
                            pIPersistFile->Release();
                        }
                    }
                    pITaskTrigger->Release();
                }
                // }
                //}
                //pIPersistFile->Release();
            }
            pITask->Release();
        }
        pITS->Release();
    }
    ::CoUninitialize();
    return bResult;
}
