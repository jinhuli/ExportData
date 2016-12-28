#ifndef __FOXFUNC_H_INCLUDE
#define __FOXFUNC_H_INCLUDE

// ��ħ����time_t��64λ��
// �Ϸɺ���32λ������ԭ��time_t���ֶΣ����ڶ���TimeType����ʾ����64λ��
// ʹ��vc6����dll�ģ������Ҫ�õ�ʱ��ģ�ע���ʱ���ֶ�ת����vc6��time_t����
// ʹ��vc2008���ϰ汾�ģ�time_t����__int64������Ҫ�ر���
#define TimeType int

/*
///////////////////////////////////////////////////////////////////////////
�ɺ�����ʦ��C���Խӿڡ���չ������ýӿڹ淶V3.0
1.���淶�����ڷɺ�����ʦV3.x��ʽϵͳ.
2.��չ����������ʵ��ϵͳ��ʽ��������ʵ�ֵ������㷨.
3.��չ������windows 32λ��̬���ӿ�ʵ��,����ʹ��Microsoft Visual C++���.
4.����ʱ�ڹ�ʽ�༭������д"��̬������@��������"(������)����,�������溯������дΪ"FOXFUNC@MYMACLOSE"(5)
5.��̬���ӿ����ƺͺ������ƿ����Լ�����.
6.ʹ��ʱ���뽫��̬���ļ������ڷɺ�����ʦ��װĿ¼�µ�FmlDLL��Ŀ¼��ʹ��.
*/

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

////////////////////////////////////////////////////
//��������
////////////////////////////////////////////////////
enum DATA_TYPE
{
	TICK_DATA=2,				//�ֱʳɽ�
	MIN1_DATA,					//1������
	MIN5_DATA,					//5������
	MIN15_DATA,					//15������
	MIN30_DATA,					//30������
	MIN60_DATA,					//60������
	DAY_DATA,					//����
	WEEK_DATA,					//����
	MONTH_DATA,					//����
	YEAR_DATA,					//����
	MULTIDAY_DATA,				//������
	MULTIMIN_DATA,				//�������
	MULTISEC_DATA				//������
};

////////////////////////////////////////////////////
//��������
////////////////////////////////////////////////////

typedef struct tagSTKDATA
{
	TimeType m_time;		//ʱ��,UCT
	float	m_fOpen;		//����
	float	m_fHigh;		//���
	float	m_fLow;			//���
	float	m_fClose;		//����
	float	m_fVolume;		//�ɽ���(��)
	float	m_fAmount;		//�ɽ���(Ԫ)/�ֲ�(δƽ�ֺ�Լ�����ڻ���Ч)
	WORD	m_wAdvance;		//���Ǽ���(��������Ч)
	WORD	m_wDecline;		//�µ�����(��������Ч)
} STKDATA;

////////////////////////////////////////////////////
//��չ����,���������ֱʳɽ����ݵ�������
////////////////////////////////////////////////////

typedef union tagSTKDATAEx
{
	struct
	{
		float m_fBuyPrice[3];		//��1--��3��
		float m_fBuyVol[3];			//��1--��3��
		float m_fSellPrice[3];		//��1--��3��
		float m_fSellVol[3];		//��1--��3��
		DWORD m_dwToken;			//�ɽ�����
	};
	float m_fDataEx[13];
} STKDATAEx;

////////////////////////////////////////////////////
//��Ȩ����
////////////////////////////////////////////////////

typedef struct tagSPLITDATA
{
	TimeType	m_time;			//ʱ��,UCT
	float	m_fHg;			//���
	float	m_fPg;			//���
	float	m_fPgj;			//��ɼ�
	float	m_fHl;			//����
} SPLITDATA;


////////////////////////////////////////////////////
/*��������˳��(m_pfFinData����)

	���	����

	0	�ܹɱ�(���),
	1	���ҹ�,
	2	�����˷��˹�,
	3	���˹�,
	4	B��,
	5	H��,
	6	��ͨA��,
	7	ְ����,
	8	A2ת���,
	9	���ʲ�(ǧԪ),
	10	�����ʲ�,
	11	�̶��ʲ�,
	12	�����ʲ�,
	13	����Ͷ��,
	14	������ծ,
	15	���ڸ�ծ,
	16	�ʱ�������,
	17	ÿ�ɹ�����,
	18	�ɶ�Ȩ��,
	19	��Ӫ����,
	20	��Ӫ����,
	21	��������,
	22	Ӫҵ����,
	23	Ͷ������,
	24	��������,
	25	Ӫҵ����֧,
	26	�����������,
	27	�����ܶ�,
	28	˰������,
	29	������,
	30	δ��������,
	31	ÿ��δ����,
	32	ÿ������,
	33	ÿ�ɾ��ʲ�,
	34	����ÿ�ɾ���,
	35	�ɶ�Ȩ���,
	36	����������
	37  ��Ӫ�ֽ�����
	38  ��Ӫ�ֽ�����
	39  ��Ӫ�ֽ�����
	40  Ͷ���ֽ�����
	41  Ͷ���ֽ�����
	42  Ͷ���ֽ�����
	43  �����ֽ�����
	44  �����ֽ�����
	45  �����ֽ�����
	46  �ֽ𼰵ȼ���
	47  Ӧ���ʿ���ת��
	48  �����ת��
	49  �ɶ�����
	50  ���м�
	51  �ٶ�����
	52  ��Ӫҵ��������
	53  ˰������������
	54  ���ʲ�������
	55  ���ʲ�������
*/

////////////////////////////////////////////////////
//���ò�����ṹ
////////////////////////////////////////////////////
typedef struct tagCALCPARAM
{
	union
	{
		const float m_fParam; //��ֵ����
		const float* m_pfParam; //���в�����ָ��һ������������	
		const char* m_szParam; //�ַ�������
	};
	//���в�����Ч��ʼλ��
	const int	m_nParamStart;
}CALCPARAM;


////////////////////////////////////////////////////
//���ýӿ���Ϣ���ݽṹ
////////////////////////////////////////////////////
typedef struct tagCALCINFO
{
	//�ṹ��С
	DWORD m_dwSize;
	//��������汾(V3.00 : 0x300)
	DWORD m_dwVersion;
	//����������к�
	DWORD m_dwSerial;
	//����û���
	//char* m_strUserName;
	//��Ʊ����
	char* m_strStkLabel;
	//����
	BOOL m_bIndex;
	//��������(pData,pDataEx,pResultBuf��������)
	int m_nNumData;
	//��������,ע��:��m_nNumData==0ʱ����Ϊ NULL
	STKDATA* m_pData;
	//��չ����,�ֱʳɽ�������,ע��:����Ϊ NULL
	STKDATAEx* m_pDataEx;
	//����1��Чλ��
	int m_nParam1Start;
	//���ò���1
	float*	 m_pfParam1;
	//���ò���2
	float*	 m_pfParam2;
	//���ò���3
	float*	 m_pfParam3;
	//���ò���4
	float*	 m_pfParam4;
	//���������
	float* m_pResultBuf;
	//��������
	int m_dataType;
	//��������
	float* m_pfFinData;
	//����������Ҽ��ݣ�����������ṹ������

	//����Ϊ FoxTrader ��չ
	// function type
	DWORD m_nFncType;
	// ���ò�������
	int m_nNumParam;
	// ���ò�������
	CALCPARAM* m_pCalcParam;
	//��չ���������
	float* m_pResultBufExt[8];
	//��չ�����Чλ��
	int m_nResultStart[8];
	// �û�����(102400�ֽ�)
	void* m_pUserData;

	//�ڲ�����������
	//����2��Чλ��
	int	m_nParam2Start;
	//����3��Чλ��
	int m_nParam3Start;
	//����4��Чλ��
	int m_nParam4Start;
	//��Ʊ����
	char* m_strStkName;
	//��Ȩ����
	SPLITDATA*	m_pSplitData;
	//��Ȩ����
	int m_nNumSplitData;
	//���㵱ǰ�±�����
	int m_iCurIndex;

	void* m_pReserved1;
	void* m_pReserved2;
	void* m_pReserved3;
	void* m_pReserved4;

} CALCINFO;

/* 
ע1: (������Ҽ���)
	1.�������ò�����m_pfParam1--m_pfParam4����,��ΪNULL���ʾ�ò�����Ч.
	2.��һ��������Чʱ,���������в�������Ч.
		��:m_pfParam2ΪNULL,��m_pfParam3,m_pfParam4ҲΪNULL.
	3.����1�����ǳ�������������������,�������ֻ��Ϊ��������.
	4.��m_nParam1Start<0, �����1Ϊ��������,��������*m_pfParam1;
	5.��m_nParam1Start>=0,�����1Ϊ����������,m_pfParam1ָ��һ������������,
		�����СΪm_nNumData,������Ч��ΧΪ m_nParam1Start �� m_nNumData-1.
		��ʱ����m_pData[x] �� m_pfParam1[x]��һ�µ�

ע2: (�ɺ�����ʦ��չ)
	1.����չ�ṹʹ���ò����ڼ����Ͽ�����������Ŀ�ģ���ÿ����������Ϊ��ֵ�����У��ɹ�ʽ��ʵ�ʵĵ��ò���������
	2.CALCPARAM�ṹ���ڴ��������Ϣ��ʵ�����ݣ�m_pCalcParam�����СΪm_nNumParam��������Ч��ΧΪ 0 �� m_nNumParam-1.
	3.��������˳��m_pCalcParam[0]Ϊ��һ�����������ݣ�m_pCalcParam[1]Ϊ�ڶ�������������...��Ϊ�˱��ּ��ݣ�ԭm_nParam1Start��m_pfParam1��5��������Ȼ�и�ֵ��
	4.�� iλ�õĲ���Ϊ��ֵ��ȡ��m_pCalcParam[i].m_fParam.
	5.�� iλ�õĲ���Ϊ���У�ȡ��m_pCalcParam[i].m_pfParam�������СΪm_nNumData,������Ч��ΧΪm_pCalcParam[i].m_nParamStart �� m_nNumData-1. ��m_pCalcParam[i].m_nParamStart<0, �������������Ч���ݡ�
	6.���ڿ��Ե��ö�����У�������еļ���������ڹ�ʽ�н��У�Ȼ����Ϊ���õĲ������ɡ�
	7.������չ���Է����ҵ�DLL��Ȼ���Ե��á����ݡ�

*/


////////////////////////////////////////////////////
/* �������

__declspec(dllexport) int xxxxxxxx(CALCINFO* pData);

1.����������ȫ����д.
2.����������������ʽ����,����ʵ�ʺ����������xxxxxxxx;
	����C++����������� extern "C" {   } ������.
3.������������pData->m_pResultBuf����.
4.��������-1��ʾ�����ȫ��������Ч,���򷵻ص�һ����Чֵλ��,��:
	m_pResultBuf[����ֵ] -- m_pResultBuf[m_nNumData-1]��Ϊ��Чֵ.
5.�������Ƴ��Ȳ��ܳ���15�ֽ�,��̬���ӿ��ļ������ܳ���9�ֽ�(��������չ��),��̬�����Ʋ��ܽ�SYSTEM,EXPLORER



//ʾ������,ʹ��ʱ��ʵ�������滻,��Щ����ֻ����������ģʽ
__declspec(dllexport) int WINAPI MYMACLOSE(CALCINFO* pData);
__declspec(dllexport) int WINAPI MYMAVAR(CALCINFO* pData);
__declspec(dllexport) int WINAPI MYBBI(CALCINFO* pData);
__declspec(dllexport) int WINAPI mymax(CALCINFO* PData);

// ���º���ֻ���������ģʽ
__declspec(dllexport) double WINAPI ARRAYPLUS(double* array, double* array1, double n, double add);
__declspec(dllexport) double WINAPI ALL_TYPE_ADD(char d1,  int d2, LONG d3, DWORD d4, float d5, double d6, BOOL d7, ULONG d8);
__declspec(dllexport) void WINAPI TestNumbericRef(double* x, double* y, double* z);
__declspec(dllexport) void WINAPI SetString(LPCWSTR str1, LPCWSTR str2);
__declspec(dllexport) LPCWSTR WINAPI MyString();
__declspec(dllexport) double* WINAPI NewDouble();
__declspec(dllexport) void WINAPI FreeDouble(double* p);
__declspec(dllexport) void WINAPI my_ma(double* resultArray, double* array, int n, int barpos);

_declspec(dllexport) void WINAPI pass_array(double* params, double* result);
_declspec(dllexport) void WINAPI pass_array2(double params[20], double result[10]);

*/

#ifdef __cplusplus
}
#endif //__cplusplus


#endif //__FOXFUNC_H_INCLUDE
