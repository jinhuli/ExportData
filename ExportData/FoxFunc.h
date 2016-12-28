#ifndef __FOXFUNC_H_INCLUDE
#define __FOXFUNC_H_INCLUDE

// 金魔方的time_t是64位的
// 老飞狐是32位，所有原来time_t的字段，现在都用TimeType来表示，是64位的
// 使用vc6编译dll的，如果需要用到时间的，注意把时间字段转换成vc6的time_t类型
// 使用vc2008以上版本的，time_t就是__int64，不需要特别处理
#define TimeType int

/*
///////////////////////////////////////////////////////////////////////////
飞狐交易师“C语言接口”扩展程序调用接口规范V3.0
1.本规范适用于飞狐交易师V3.x公式系统.
2.扩展函数可用于实现系统公式函数不能实现的特殊算法.
3.扩展函数用windows 32位动态链接库实现,建议使用Microsoft Visual C++编程.
4.调用时在公式编辑器中书写"动态库名称@函数名称"(参数表)即可,例如下面函数可以写为"FOXFUNC@MYMACLOSE"(5)
5.动态链接库名称和函数名称可以自己定义.
6.使用时必须将动态库文件放置在飞狐交易师安装目录下的FmlDLL子目录下使用.
*/

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

////////////////////////////////////////////////////
//分析周期
////////////////////////////////////////////////////
enum DATA_TYPE
{
	TICK_DATA=2,				//分笔成交
	MIN1_DATA,					//1分钟线
	MIN5_DATA,					//5分钟线
	MIN15_DATA,					//15分钟线
	MIN30_DATA,					//30分钟线
	MIN60_DATA,					//60分钟线
	DAY_DATA,					//日线
	WEEK_DATA,					//周线
	MONTH_DATA,					//月线
	YEAR_DATA,					//年线
	MULTIDAY_DATA,				//多日线
	MULTIMIN_DATA,				//多分钟线
	MULTISEC_DATA				//多秒线
};

////////////////////////////////////////////////////
//基本数据
////////////////////////////////////////////////////

typedef struct tagSTKDATA
{
	TimeType m_time;		//时间,UCT
	float	m_fOpen;		//开盘
	float	m_fHigh;		//最高
	float	m_fLow;			//最低
	float	m_fClose;		//收盘
	float	m_fVolume;		//成交量(手)
	float	m_fAmount;		//成交额(元)/持仓(未平仓合约，仅期货有效)
	WORD	m_wAdvance;		//上涨家数(仅大盘有效)
	WORD	m_wDecline;		//下跌家数(仅大盘有效)
} STKDATA;

////////////////////////////////////////////////////
//扩展数据,用于描述分笔成交数据的买卖盘
////////////////////////////////////////////////////

typedef union tagSTKDATAEx
{
	struct
	{
		float m_fBuyPrice[3];		//买1--买3价
		float m_fBuyVol[3];			//买1--买3量
		float m_fSellPrice[3];		//卖1--卖3价
		float m_fSellVol[3];		//卖1--卖3量
		DWORD m_dwToken;			//成交方向
	};
	float m_fDataEx[13];
} STKDATAEx;

////////////////////////////////////////////////////
//除权数据
////////////////////////////////////////////////////

typedef struct tagSPLITDATA
{
	TimeType	m_time;			//时间,UCT
	float	m_fHg;			//红股
	float	m_fPg;			//配股
	float	m_fPgj;			//配股价
	float	m_fHl;			//红利
} SPLITDATA;


////////////////////////////////////////////////////
/*财务数据顺序(m_pfFinData内容)

	序号	内容

	0	总股本(万股),
	1	国家股,
	2	发起人法人股,
	3	法人股,
	4	B股,
	5	H股,
	6	流通A股,
	7	职工股,
	8	A2转配股,
	9	总资产(千元),
	10	流动资产,
	11	固定资产,
	12	无形资产,
	13	长期投资,
	14	流动负债,
	15	长期负债,
	16	资本公积金,
	17	每股公积金,
	18	股东权益,
	19	主营收入,
	20	主营利润,
	21	其他利润,
	22	营业利润,
	23	投资收益,
	24	补贴收入,
	25	营业外收支,
	26	上年损益调整,
	27	利润总额,
	28	税后利润,
	29	净利润,
	30	未分配利润,
	31	每股未分配,
	32	每股收益,
	33	每股净资产,
	34	调整每股净资,
	35	股东权益比,
	36	净资收益率
	37  经营现金流入
	38  经营现金流出
	39  经营现金流量
	40  投资现金流入
	41  投资现金流出
	42  投资现金流量
	43  筹资现金流入
	44  筹资现金流出
	45  筹资现金流量
	46  现金及等价物
	47  应收帐款周转率
	48  存货周转率
	49  股东总数
	50  发行价
	51  速动比率
	52  主营业务增长率
	53  税后利润增长率
	54  净资产增长率
	55  总资产增长率
*/

////////////////////////////////////////////////////
//调用参数项结构
////////////////////////////////////////////////////
typedef struct tagCALCPARAM
{
	union
	{
		const float m_fParam; //数值参数
		const float* m_pfParam; //序列参数，指向一个浮点型数组	
		const char* m_szParam; //字符串参数
	};
	//序列参数有效起始位置
	const int	m_nParamStart;
}CALCPARAM;


////////////////////////////////////////////////////
//调用接口信息数据结构
////////////////////////////////////////////////////
typedef struct tagCALCINFO
{
	//结构大小
	DWORD m_dwSize;
	//调用软件版本(V3.00 : 0x300)
	DWORD m_dwVersion;
	//调用软件序列号
	DWORD m_dwSerial;
	//软件用户名
	//char* m_strUserName;
	//股票代码
	char* m_strStkLabel;
	//大盘
	BOOL m_bIndex;
	//数据数量(pData,pDataEx,pResultBuf数据数量)
	int m_nNumData;
	//常规数据,注意:当m_nNumData==0时可能为 NULL
	STKDATA* m_pData;
	//扩展数据,分笔成交买卖盘,注意:可能为 NULL
	STKDATAEx* m_pDataEx;
	//参数1有效位置
	int m_nParam1Start;
	//调用参数1
	float*	 m_pfParam1;
	//调用参数2
	float*	 m_pfParam2;
	//调用参数3
	float*	 m_pfParam3;
	//调用参数4
	float*	 m_pfParam4;
	//结果缓冲区
	float* m_pResultBuf;
	//数据类型
	int m_dataType;
	//财务数据
	float* m_pfFinData;
	//以上与分析家兼容，所以沿用其结构和名称

	//以下为 FoxTrader 扩展
	// function type
	DWORD m_nFncType;
	// 调用参数数量
	int m_nNumParam;
	// 调用参数数组
	CALCPARAM* m_pCalcParam;
	//扩展结果缓冲区
	float* m_pResultBufExt[8];
	//扩展结果有效位置
	int m_nResultStart[8];
	// 用户数据(102400字节)
	void* m_pUserData;

	//内部函数计算用
	//参数2有效位置
	int	m_nParam2Start;
	//参数3有效位置
	int m_nParam3Start;
	//参数4有效位置
	int m_nParam4Start;
	//股票名称
	char* m_strStkName;
	//除权数据
	SPLITDATA*	m_pSplitData;
	//除权次数
	int m_nNumSplitData;
	//计算当前下标数据
	int m_iCurIndex;

	void* m_pReserved1;
	void* m_pReserved2;
	void* m_pReserved3;
	void* m_pReserved4;

} CALCINFO;

/* 
注1: (与分析家兼容)
	1.函数调用参数由m_pfParam1--m_pfParam4带入,若为NULL则表示该参数无效.
	2.当一个参数无效时,则其后的所有参数均无效.
		如:m_pfParam2为NULL,则m_pfParam3,m_pfParam4也为NULL.
	3.参数1可以是常数参数或序列数参数,其余参数只能为常数参数.
	4.若m_nParam1Start<0, 则参数1为常数参数,参数等于*m_pfParam1;
	5.若m_nParam1Start>=0,则参数1为序列数参数,m_pfParam1指向一个浮点型数组,
		数组大小为m_nNumData,数据有效范围为 m_nParam1Start 至 m_nNumData-1.
		在时间上m_pData[x] 与 m_pfParam1[x]是一致的

注2: (飞狐交易师扩展)
	1.该扩展结构使调用参数在技术上可以是无限数目的，且每个参数都可为数值或序列，由公式中实际的调用参数决定。
	2.CALCPARAM结构用于带入参数信息和实际数据，m_pCalcParam数组大小为m_nNumParam，数据有效范围为 0 至 m_nNumParam-1.
	3.按参数的顺序，m_pCalcParam[0]为第一个参数的数据，m_pCalcParam[1]为第二个参数的数据...，为了保持兼容，原m_nParam1Start、m_pfParam1等5个属性依然有赋值。
	4.若 i位置的参数为数值，取用m_pCalcParam[i].m_fParam.
	5.若 i位置的参数为序列，取用m_pCalcParam[i].m_pfParam，数组大小为m_nNumData,数据有效范围为m_pCalcParam[i].m_nParamStart 至 m_nNumData-1. 若m_pCalcParam[i].m_nParamStart<0, 则此数组中无有效数据。
	6.由于可以调用多个序列，许多序列的计算可以先在公式中进行，然后作为调用的参数即可。
	7.经此扩展，对分析家的DLL依然可以调用、兼容。

*/


////////////////////////////////////////////////////
/* 函数输出

__declspec(dllexport) int xxxxxxxx(CALCINFO* pData);

1.函数名称需全部大写.
2.函数必须以上述形式声明,请用实际函数名称替代xxxxxxxx;
	对于C++程序还需包括在 extern "C" {   } 括号中.
3.函数计算结果用pData->m_pResultBuf带回.
4.函数返回-1表示错误或全部数据无效,否则返回第一个有效值位置,即:
	m_pResultBuf[返回值] -- m_pResultBuf[m_nNumData-1]间为有效值.
5.函数名称长度不能超过15字节,动态连接库文件名不能超过9字节(不包括扩展名),动态库名称不能叫SYSTEM,EXPLORER



//示例函数,使用时用实际名称替换,这些函数只适用于逐行模式
__declspec(dllexport) int WINAPI MYMACLOSE(CALCINFO* pData);
__declspec(dllexport) int WINAPI MYMAVAR(CALCINFO* pData);
__declspec(dllexport) int WINAPI MYBBI(CALCINFO* pData);
__declspec(dllexport) int WINAPI mymax(CALCINFO* PData);

// 以下函数只适用于逐根模式
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
