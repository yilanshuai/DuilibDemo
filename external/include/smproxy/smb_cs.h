
#ifndef _SMB_CS_API_H_
#define _SMB_CS_API_H_

#include "common.h"

// 证书(验证标志) 可以做按位与操作
typedef enum _SMB_CERT_VERIFY_FLAG
{
	SMB_CERT_VERIFY_FLAG_NOTHING = 0x00000000,		// 不验证
	SMB_CERT_VERIFY_FLAG_TIME = 0x00000001,		// 使用本地当前时间验证有效期
	SMB_CERT_VERIFY_FLAG_CHAIN = 0x00000002,		// 验证证书链以及签名
	SMB_CERT_VERIFY_FLAG_CRL = 0x00000004,		// 尚未实现

}SMB_CERT_VERIFY_FLAG;

// 验证结果
typedef enum _SMB_CERT_VERIFY_RESULT_FLAG
{
	SMB_CERT_VERIFY_RESULT_FLAG_OK = 0x00000000,		// 验证成功
	SMB_CERT_VERIFY_RESULT_FLAG_TIME_INVALID = 0x00000001,		// 不在有效期
	SMB_CERT_VERIFY_RESULT_FLAG_CHAIN_INVALID = 0x00000002,		// 证书链异常
	SMB_CERT_VERIFY_RESULT_FLAG_SIGN_INVALID = 0x00000003,		// 非法用户证书
	SMB_CERT_VERIFY_RESULT_FLAG_CRL_INVALID = 0x00000004,		// 尚未加入

}SMB_CERT_VERIFY_RESULT_FLAG;

// 证书(密钥类型标志) 可以做按位与操作
typedef enum _SMB_CERT_ALG_FLAG
{
	SMB_CERT_ALG_FLAG_RSA = 0x00000001,		// RSA证书
	SMB_CERT_ALG_FLAG_SM2 = 0x00000002,		// SM2证书

}SMB_CERT_ALG_TYPE;

// 证书(签名|加密标志) 可以做按位与操作
typedef enum _SMB_CERT_USAGE_FLAG
{
	SMB_CERT_USAGE_FLAG_SIGN = 0x00000001,		// 签名证书
	SMB_CERT_USAGE_FLAG_EX = 0x00000002,		// 加密证书

}SMB_CERT_USAGE_FLAG;

typedef enum _SMB_CERT_FILTER_FLAG
{
	SMB_CERT_FILTER_FLAG_FALSE = 0x00000000,		// 不过滤
	SMB_CERT_FILTER_FLAG_TRUE = 0x00000001,		// 过滤
}SMB_CERT_FILTER_FLAG;

//数据
typedef struct _SMB_CS_Data
{
	unsigned int length;            // 长度
	unsigned char *data;            // 数据
}SMB_CS_Data;

//证书属性
typedef struct _SMB_CS_CertificateAttr
{
	SMB_CS_Data stSKFName;			// SKF接口名称
	SMB_CS_Data stDeviceName;		// 设备名称
	SMB_CS_Data stApplicationName;	// 应用名称
	SMB_CS_Data stContainerName;	// 容器名称
	SMB_CS_Data stCommonName;		// 通用名 显示设备名
	SMB_CS_Data stSubject;    		// 主题项
	SMB_CS_Data stIssue;            // 颁发者
	SMB_CS_Data stPublicKey;        // 公钥
	SMB_CS_Data stSerialNumber;     // 序列号
	SMB_CS_Data stSubjectKeyID;     // 使用者密钥标识
	SMB_CS_Data stIssueKeyID;       // 颁发者密钥标识
	SMB_CS_Data stVendorData;       // 用户自定义数据
	unsigned char ucCertAlgType;	// 证书类型
	unsigned char ucCertUsageType;	// 签名加密 1 签名 2 加密 3 签名加密
	unsigned int ulVerify;			// 验证结果 WTF_CERT_VERIFY_RESULT_FLAG
	unsigned long long ulNotBefore;	// 起始
	unsigned long long ulNotAfter;	// 截止
}SMB_CS_CertificateAttr;

//证书查找属性
typedef struct _SMB_CS_CertificateFindAttr
{
	unsigned int uiFindFlag;        // 查找标记 以下选项按位或 1 2 4 8 16 32 64 128 ... 支持4*8=32个查找项 32与组合查找
	unsigned char ucCertAlgType;	// 证书类型 1
	unsigned char ucCertUsageType;	// 签名加密 2
	unsigned char ucStoreType;      // 存储类型 4
	SMB_CS_Data stSubject;    		// 主题项   8
	SMB_CS_Data stIssue;            // 颁发者   16
	SMB_CS_Data stPublicKey;        // 公钥     32
	SMB_CS_Data stSerialNumber;     // 序列号   64
	SMB_CS_Data stSubjectKeyID;     // 使用者密钥标识  128
	SMB_CS_Data stIssueKeyID;       // 颁发者密钥标识  256
	SMB_CS_Data stVendorData;       // 用户自定义数据  512

}SMB_CS_CertificateFindAttr;

typedef struct _SMB_CS_CRLFindAttr
{
	unsigned int uiFindFlag;        // 查找标记 以下选项按位或 1 2 4 8 16 32 64 128 ... 支持4*8=32个查找项 32与组合查找
	SMB_CS_Data stIssue;            // 颁发者   1
	SMB_CS_Data stEffectTime;       // 生效时间，精确到天  2
}SMB_CS_CRLFindAttr;



//证书内容
typedef struct _SMB_CS_CertificateContent
{
	unsigned int length;            // 长度
	unsigned char *data;            // 数据
}SMB_CS_CertificateContent;

//证书上下文
typedef struct _SMB_CS_CertificateContext
{
	SMB_CS_CertificateAttr     stAttr;      // 证书属性
	SMB_CS_CertificateContent  stContent;   // 证书内容
	unsigned char ucStoreType;              // 存储类型 1:CA&ROOT 2:USER
}SMB_CS_CertificateContext;

//证书上下文节点（链表）
typedef struct _SMB_CS_CertificateContext_NODE
{
	SMB_CS_CertificateContext *ptr_data;
	struct _SMB_CS_CertificateContext_NODE *ptr_next;
}SMB_CS_CertificateContext_NODE;

//PIDVID结构
typedef struct _SMB_CS_PIDVID
{
	SMB_CS_Data     stPID;   // 产品号
	SMB_CS_Data     stVID;   // 厂商号
	SMB_CS_Data     stType;  // 类型 csp skf
}SMB_CS_PIDVID;

//PIDVID节点（链表）
typedef struct _SMB_CS_PIDVID_NODE
{
	SMB_CS_PIDVID *ptr_data;
	struct _SMB_CS_PIDVID_NODE *ptr_next;
}SMB_CS_PIDVID_NODE;

//SKF结构
typedef struct _SMB_CS_SKF
{
	SMB_CS_Data     stName;      // 名称
	SMB_CS_Data     stPath;      // 路径
	SMB_CS_Data     stSignType;  // 签名类型 digest data
	SMB_CS_Data     stPinVerify; // PIN校验选择 "0" || "" ：标准PIN有效使用； "1"：无需调用校验PIN接口；"2"：需调用校验PIN接口，但忽略接口中的PIN值

}SMB_CS_SKF;

//SKF结构节点（链表）
typedef struct _SMB_CS_SKF_NODE
{
	SMB_CS_SKF *ptr_data;
	struct _SMB_CS_SKF_NODE *ptr_next;
}SMB_CS_SKF_NODE;


//CRL结构
typedef struct _SMB_CS_CRL
{
	unsigned int length;            // 长度
	unsigned char *data;            // 数据
}SMB_CS_CRL;

//CRL结构节点（链表）
typedef struct _SMB_CS_CRL_NODE
{
	SMB_CS_CRL *ptr_data;
	struct _SMB_CS_CRL_NODE *ptr_next;
}SMB_CS_CRL_NODE;

//CSP结构
typedef struct _SMB_CS_CSP
{
	SMB_CS_Data     stName;       // 名称
	SMB_CS_Data     stValue;      // 值
}SMB_CS_CSP;

//CSP结构节点（链表）
typedef struct _SMB_CS_CSP_NODE
{
	SMB_CS_CSP *ptr_data;
	struct _SMB_CS_CSP_NODE *ptr_next;
}SMB_CS_CSP_NODE;

//文件信息结构
typedef struct _SMB_CS_FileInfo
{
	SMB_CS_Data     stName;       // 名称
	SMB_CS_Data     stPath;       // 路径
	SMB_CS_Data     stDigestMD5;  // MD5值
	SMB_CS_Data     stDigestSHA1; // SHA1值
	SMB_CS_Data     stFileType;   // 文件类别 csp skf control driver cert  .etc
	SMB_CS_Data     stCategory;   // 类目 如 CSP名称
}SMB_CS_FileInfo;

//文件信息结构节点（链表）
typedef struct _SMB_CS_FileInfo_NODE
{
	SMB_CS_FileInfo *ptr_data;
	struct _SMB_CS_FileInfo_NODE *ptr_next;
}SMB_CS_FileInfo_NODE;

typedef enum _EErr_SMB
{
	EErr_SMB_OK,									// 成功
													// SKFERROR 0x0A000001-0x0A000032				// SKF错误码范围
													// HRESULT  0x00000000-0x00015301				// 微软错误码范围
													// HRESULT  0x8000FFFF-0x802A010A				// 微软错误码范围
													// HRESULT  .....								// 微软错误码范围

													EErr_SMB_BASE = 0xF000FFFF,						// 起始错误码
													EErr_SMB_DLL_REG_PATH,							// 注册路径
													EErr_SMB_DLL_PATH,								// 获取函数地址失败
													EErr_SMB_NO_APP,								// 没有应用
													EErr_SMB_CREATE_STORE,							// 创建存储区失败
													EErr_SMB_OPEN_STORE,							// 打开存储区失败
													EErr_SMB_NO_CERT_CHAIN,							// 没有证书链
													EErr_SMB_EXPORT_PUK,							// 导出公钥失败
													EErr_SMB_VERIFY_CERT,							// 验证证书签名失败
													EErr_SMB_VERIFY_TIME,							// 验证证书有效期失败
													EErr_SMB_CREATE_CERT_CONTEXT,					// 创建证书上下文
													EErr_SMB_ADD_CERT_TO_STORE,						// 保存证书
													EErr_SMB_NO_RIGHT,								// 没有权限
													EErr_SMB_SET_CERT_CONTEXT_PROPERTY,				// 设置属性
													EErr_SMB_MEM_LES,                               // 内存不足
													EErr_SMB_INVALID_ARG,                           // 参数错误
													EErr_SMB_NO_CERT,                               // 没找见证书
													EErr_SMB_FAIL = -1,

}EErr_SMB;

#define SMB_API COMMON_API
#define CALL_MODE CALL_CONVENTION

#ifdef __cplusplus
extern "C" {
#endif

	SMB_API unsigned int CALL_MODE SMB_CS_CreateCRL(OUT SMB_CS_CRL **ppCRL, IN unsigned char *pCrlData, IN unsigned int uiCrlDataLen);

	SMB_API unsigned int CALL_MODE SMB_CS_AddCRL(IN SMB_CS_CRL *pCRL);

	SMB_API unsigned int CALL_MODE SMB_CS_DelCRL(IN SMB_CS_CRL *pCRL);

	SMB_API unsigned int CALL_MODE SMB_CS_EnumCRL(OUT SMB_CS_CRL_NODE **ppNodeHeader);

	SMB_API unsigned int CALL_MODE SMB_CS_FindCRL(IN SMB_CS_CRLFindAttr *pCRLFindAttr, OUT SMB_CS_CRL_NODE **ppNodeHeader);

	SMB_API unsigned int CALL_MODE SMB_CS_FreeCRLLink(IN OUT SMB_CS_CRL_NODE **ppNodeHeader);

	SMB_API unsigned int CALL_MODE SMB_CS_FreeCRL(IN SMB_CS_CRL *pPtr);

	SMB_API unsigned int CALL_MODE SMB_CS_GetCertStateByOCSP(
		unsigned char *pOcspHostURL,
		unsigned int uiOcspHostURLLen,
		unsigned char *pUsrCertificate,
		unsigned int uiUsrCertificateLen,
		unsigned char *pCACertificate,
		unsigned int uiCACertificateLen,
		unsigned int * puiState
	);

	SMB_API unsigned int CALL_MODE SMB_CS_CheckCertIfExistFromCRL(unsigned char *pCrlData, unsigned int uiCrlDataLen, unsigned char *pCert, unsigned int uiCertLen, unsigned int *pBoolExist);

	SMB_API unsigned int CALL_MODE SMB_CS_GetCertStateFromCRL(unsigned char *pCrlData, unsigned int uiCrlDataLen, unsigned char *pCert, unsigned int uiCertLen, unsigned int * puiState);

	//通过LDAP方式获取证书
	SMB_API unsigned int CALL_MODE SMB_CS_GetCertFromLdap(
		char *pLdapHostURL,
		unsigned int uiLdapHostURLLen,
		unsigned char *pQueryDN,
		unsigned int uiQueryDNLen,
		unsigned char *pOutCert,
		unsigned int *puiOutCertLen);

	//通过LDAP方式获取证书对应的CRL
	SMB_API unsigned int CALL_MODE SMB_CS_GetCrlFromLdap(
		char *pLdapHostURL,
		unsigned int uiLdapHostURLLen,
		unsigned char *pCertificate,
		unsigned int uiCertificateLen,
		unsigned char *pCrlData,
		unsigned int *puiCrlDataLen);


	SMB_API unsigned int CALL_MODE SMB_CS_CreateSKF(OUT SMB_CS_SKF **ppSKF, IN char *pSKFName, IN char *pSKFPath, IN char *pSKFSignType, IN int uiSKFPinMode);

	SMB_API unsigned int CALL_MODE SMB_CS_AddSKF(IN SMB_CS_SKF *pSKF);
	
	SMB_API unsigned int CALL_MODE SMB_CS_DelSKF(IN SMB_CS_SKF *pSKF);







	/*
	数据库路径初始化
	pDbPath:NULL 默认路径C:\Users\xxxxx\AppData\Roaming\xxxx.smb_cs.db
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_SetPath(char * pDbPath);

	/*
	数据库初始化
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_Init();

	/*
	创建证书上下文
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_CreateCertCtx(OUT SMB_CS_CertificateContext **ppCertCtx, IN unsigned char *pCertificate, IN unsigned int uiCertificateLen);

	/*
	释放证书上下文
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeCertCtx(IN SMB_CS_CertificateContext *pCertCtx);

	/*
	拷贝证书属性
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_DuplicateCertAttr(IN SMB_CS_CertificateContext *pCertCtx, IN OUT SMB_CS_CertificateAttr **ppCertAttr);

	/*
	释放证书属性
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeCertAttr(IN SMB_CS_CertificateAttr *pCertAttr);

	/*
	添加证书到数据库 ucStoreType 1:CA&ROOT 2:USER
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_AddCertCtx(IN SMB_CS_CertificateContext *pCertCtx, IN unsigned char ucStoreType);

	/*
	从数据库删除证书
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_DelCertCtx(IN SMB_CS_CertificateContext *pCertCtx);

	/*
	清空数据库
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_ClrAllCertCtx(IN unsigned char ucStoreType);

	/*
	从数据库查找证书
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FindCertCtx(IN SMB_CS_CertificateFindAttr *pCertificateFindAttr, OUT SMB_CS_CertificateContext_NODE **ppCertCtxNodeHeader);

	/*
	从数据库遍历证书
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_EnumCertCtx(OUT SMB_CS_CertificateContext_NODE **ppCertCtxNodeHeader, IN unsigned char ucStoreType);

	/*
	从数据库删除证书上
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_DelCertCtxLink(IN SMB_CS_CertificateContext_NODE *pCertCtxNodeHeader);

	/*
	释放证书上下文链表
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeCertCtxLink(IN OUT SMB_CS_CertificateContext_NODE **ppCertCtxNodeHeader);

	/*
	通过证书获取上下文
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_GetCertCtxByCert(OUT SMB_CS_CertificateContext **ppCertCtx, IN unsigned char *pCertificate, IN unsigned int uiCertificateLen);

	/*
	从数据库遍历CSP
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_EnumCSP(OUT SMB_CS_CSP_NODE **ppNodeHeader);

	/*
	释放CSP链表
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeCSPLink(IN OUT SMB_CS_CSP_NODE **ppNodeHeader);

	/*
	释放结构
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeCSP(IN SMB_CS_CSP *pPtr);

	/*
	从数据库遍历SKF
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_EnumSKF(OUT SMB_CS_SKF_NODE **ppNodeHeader);

	/*
	释放SKF链表
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeSKFLink(IN OUT SMB_CS_SKF_NODE **ppNodeHeader);

	/*
	释放结构
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeSKF(IN SMB_CS_SKF *pPtr);

	/*
	从数据库遍历PIDVID
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_EnumPIDVID(OUT SMB_CS_PIDVID_NODE **ppNodeHeader);

	/*
	释放PIDVID链表
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreePIDVIDLink(IN OUT SMB_CS_PIDVID_NODE **ppNodeHeader);

	/*
	释放结构
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreePIDVID(IN SMB_CS_PIDVID *pPtr);

	/*
	从数据库遍历FileInfo
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_EnumFileInfo(OUT SMB_CS_FileInfo_NODE **ppNodeHeader);

	/*
	释放FileInfo链表
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeFileInfoLink(IN OUT SMB_CS_FileInfo_NODE **ppNodeHeader);

	/*
	释放结构
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_FreeFileInfo(IN SMB_CS_FileInfo *pPtr);

	/*
	工具类xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	*/
	/*
	设置用户自定义数据
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_SetCertCtxVendor(IN OUT SMB_CS_CertificateContext *pCertCtx, IN unsigned char *pVendor, IN unsigned int uiVendorLen);

	/*
	验证证书的合法性
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_VerifyCert(IN unsigned int uiFlag, IN unsigned char *pbCert, IN unsigned int uiCertLen);

	/*
	导入CA&ROOT证书
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_ImportCaCert(IN unsigned char *pbCert, IN unsigned int uiCertLen, OUT unsigned int *pulAlgType);
#if defined(WINDOWS) || defined(WIN32)
	/*
	检测根证书是否存在
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_CheckRootCertExist(wchar_t * pKeyIDHex, unsigned int ulAlgType);

	/*
	导入CA&ROOT证书文件
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_ImportCaCertFile(wchar_t * pCertFile, OUT unsigned int *pulAlgType);
#endif
	/*
	导入CA&ROOT RSA证书
	*/
	SMB_API unsigned int CALL_MODE SMB_CS_ImportCaCertRSA(unsigned char *pbCert, unsigned int uiCertLen, unsigned int *pulAlgType);

#ifdef __cplusplus
}
#endif




#endif /*_SMB_CS_API_H_*/