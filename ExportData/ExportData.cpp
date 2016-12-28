// ExportData.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "FoxFunc.h"

const char * sub_folder_table[] = {"Empty0", "Empty1", "TICK", "MIN1", "MIN5", "MIN15", "MIN30", "MIN60", "DAY", "WEEK", "MONTH", "YEAR"};

// ��鵼��Ŀ¼�Ƿ����, ��������ھʹ���
static void CheckDirectories()
{
	if(_access(".\\KTExportData",0) == -1) {
		_mkdir("KTExportData");
		for (int i = 2; i <= 11; i++) {
			char str[128] = "KTExportData\\";
			strcat(str, sub_folder_table[i]);
			_mkdir(str);
		}
	}
}

const char folder_name[] = "KTExportData";

static void getFileName(char *export_file_name, CALCINFO* pData)
{
	strcat(export_file_name, folder_name);
	strcat(export_file_name, "\\");
	strcat(export_file_name, sub_folder_table[pData->m_dataType]);
	strcat(export_file_name, "\\");
	strcat(export_file_name, pData->m_strStkLabel);
}

//���÷���:
//	"ExportData@ExportData"(Amount, Settle)
extern "C" __declspec(dllexport) int WINAPI ExportData(CALCINFO* pData)
{
	CheckDirectories();

	if (pData->m_dataType < TICK_DATA || pData->m_dataType > YEAR_DATA) {
		// Invalid data type
		return -2;
	}

	if (pData->m_nNumData <= 0 || pData->m_strStkLabel == NULL) {
		return -1;
	}

	char export_file_name[128] = "";
	getFileName(export_file_name, pData);

	if (pData->m_dataType == TICK_DATA) {
		if(_access(export_file_name,0) == -1) {
			_mkdir(export_file_name);
		}
		char tmp[32];
		sprintf(tmp, "%c%d.tick", '\\', pData->m_pData[0].m_time);
		strcat(export_file_name, tmp);
	}

	int actual_export_number = 0;
	if (pData->m_pData != NULL) {

		FILE *pf = fopen(export_file_name, "wb");
		if (pf != NULL) {
			// �������С
			int struct_size = sizeof(STKDATA) + sizeof(float) * pData->m_nNumParam;
			// �ļ���С
			int file_size = struct_size * pData->m_nNumData + 16;
			fwrite(&file_size, sizeof(int), 1, pf);
			// ����ʱ��
			__time32_t time = _time32(NULL);	// may fail after January 18, 2038
			fwrite(&time, sizeof(__time32_t), 1, pf);
			// �������С
			fwrite(&struct_size, sizeof(int), 1, pf);
			// ��������
			fwrite(&pData->m_nNumData, sizeof(int), 1, pf);

			for (int i = 0; i < pData->m_nNumData; i++) {
				actual_export_number += fwrite(pData->m_pData + i, sizeof(STKDATA), 1, pf);
				for (int j = 0; j < pData->m_nNumParam; j++) {
					fwrite(pData->m_pCalcParam[j].m_pfParam + i, sizeof(float), 1, pf);
				}
			}
			fclose(pf);
		}
	}

#if 0	// ������, pData->m_pDataExֻ��һ����չ����, ��֪��Ϊʲô
	int numEx = 0;
	if (pData->m_pDataEx != NULL) {
		strcat(export_file_name, "Ex");
		FILE *pf = fopen(export_file_name, "wb");
		numEx = fwrite(pData->m_pDataEx, sizeof(STKDATAEx), pData->m_nNumData, pf);
		fclose(pf);
	}
#endif

	char logfilename[128] = "";
	strcat(logfilename, folder_name);
	strcat(logfilename, "\\");
	strcat(logfilename, "ExportDataLog.txt");
	FILE *pflog = fopen(logfilename, "at");
	if (pflog != NULL) {
		SYSTEMTIME time;
		GetLocalTime(&time);

		fprintf(pflog, "%d-%d-%d %d:%d:%d\tpData->m_strStkLabel = %s\tTime Frame = %s\tpData->m_nNumData = %d\tpData->m_nNumParam = %d\tactual_export_number = %d\n", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, pData->m_strStkLabel, sub_folder_table[pData->m_dataType], pData->m_nNumData, pData->m_nNumParam, actual_export_number);
		fclose(pflog);
	}

	return actual_export_number;
}
