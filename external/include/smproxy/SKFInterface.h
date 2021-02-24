#ifndef __SKFINTERFACE_H
#define __SKFINTERFACE_H

//6.1	算法标识
//6.1.1	分组密码算法标识
//分组密码算法标识包含密码算法的类型和加密模式。
//分组密码算法标识的编码规则为：从低位到高位，第0位到第7位按位表示分组密码算法工作模式，
//第8位到第31位按位表示分组密码算法类型，分组密码算法的标识如下所示。
#define	SGD_SM1_ECB		0x00000101		//SM1算法ECB加密模式
#define	SGD_SM1_CBC		0x00000102		//SM1算法CBC加密模式
#define	SGD_SM1_CFB		0x00000104		//SM1算法CFB加密模式
#define	SGD_SM1_OFB		0x00000108		//SM1算法OFB加密模式
#define	SGD_SM1_MAC		0x00000110		//SM1算法MAC运算
#define	SGD_SSF33_ECB	0x00000201		//SSF33算法ECB加密模式
#define	SGD_SSF33_CBC	0x00000202		//SSF33算法CBC加密模式
#define	SGD_SSF33_CFB	0x00000204		//SSF33算法CFB加密模式
#define	SGD_SSF33_OFB	0x00000208		//SSF33算法OFB加密模式
#define	SGD_SSF33_MAC	0x00000210		//SSF33算法MAC运算
#define	SGD_SMS4_ECB	0x00000401		//SMS4算法ECB加密模式
#define	SGD_SMS4_CBC	0x00000402		//SMS4算法CBC加密模式
#define	SGD_SMS4_CFB	0x00000404		//SMS4算法CFB加密模式
#define	SGD_SMS4_OFB	0x00000408		//SMS4算法OFB加密模式
#define	SGD_SMS4_MAC	0x00000410		//SMS4算法MAC运算

#define SGD_3DES_ECB	0x00000001  //3DES算法ECB加密模式

#define	SGD_ZYJM_ECB	0x00000601		//ZYJM算法ECB模式
#define	SGD_ZYJM_CBC	0x00000602		//ZYJM算法CBC模式

//6.1.2	非对称密码算法标识
//非对称密码算法标识仅定义了密码算法的类型，在使用非对称算法进行数字签名运算时，可将非对称密码算法标识符与密码杂凑算法
//标识符进行"或"运算后使用，如"RSA with SHA1"可表示为SGD_RSA | SGD_SHA1，即0x00010002，"|"表示"或"运算。
//非对称密码算法标识的编码规则为：从低位到高位，第0位到第7位为0，第8位到第15位按位表示非对称密码算法的算法协议，如果所
//表示的非对称算法没有相应的算法协议则为0，第16位到第31位按位表示非对称密码算法类型，非对称密码算法的标识如下所示。
#define	SGD_RSA			0x00010000		//RSA算法
#define	SGD_SM2_1		0x00020100		//椭圆曲线签名算法
#define	SGD_SM2_2		0x00020200		//椭圆曲线密钥交换协议
#define	SGD_SM2_3		0x00020400		//椭圆曲线加密算法
#define	SGD_ECC_512		0x00040100		//ECC512算法

//6.1.3	密码杂凑算法标识
//密码杂凑算法标识符可以在进行密码杂凑运算或计算MAC时应用，也可以与非对称密码算法标识符进行"或"运算后使用，表示签名运算
//前对数据进行密码杂凑运算的算法类型。
//密码杂凑算法标识的编码规则为：从低位到高位，第0位到第7位表示密码杂凑算法，第8位到第31位为0，密码杂凑算法的标识如下所示。
#define	SGD_SM3			0x00000001		//SM3密码杂凑算法
#define	SGD_SHA1		0x00000002		//SHA1密码杂凑算法
#define	SGD_SHA256		0x00000004		//SHA256密码杂凑算法

//6.2	基本数据类型
//INT8	有符号8位整数	
//INT16	有符号16位整数	
//INT32	有符号32位整数	
//UINT8	无符号8位整数	
//UINT16	无符号16位整数	
//UINT32	无符号32位整数	
//BOOL	布尔类型，取值为TRUE或FALSE	
//BYTE	字节类型，无符号8位整数
typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;

typedef UINT8 BYTE;
//CHAR	字符类型，无符号8位整数
typedef UINT8 CHAR1;
//SHORT	短整数，有符号16位
typedef INT16 SHORT;
//USHORT	无符号16位整数	
typedef UINT16 USHORT;
//LONG 	长整数，有符号32位整数	
typedef INT32 LONG1;
//ULONG	长整数，无符号32位整数
typedef UINT32 ULONG32;
//UINT	无符号32位整数	
typedef UINT32 UINT;
//WORD	字类型，无符号16位整数	
typedef UINT16 WORD;
//DWORD	双字类型，无符号32位整数
typedef UINT32 DWORD1;
//FLAGS	标志类型，无符号32位整数	
typedef UINT32 FLAGS;
//LPSTR	8位字符串指针，按照UTF8格式存储及交换	
typedef char * LPSTR;
//HANDLE 	句柄，指向任意数据对象的起始地址	
typedef  void * HANDLE;
//DEVHANDLE	设备句柄	
typedef HANDLE DEVHANDLE;
//HAPPLICATION	应用句柄	
typedef HANDLE HAPPLICATION;
//HCONTAINER	容器句柄	
typedef HANDLE HCONTAINER;

//6.3	常量定义
#ifndef TRUE
#define	TRUE	0x00000001		//布尔值为真
#endif

#ifndef FALSE
#define	FALSE	0x00000000		//布尔值为假
#endif

#ifndef DEVAPI
#define	DEVAPI	__stdcall		//__stdcall函数调用方式
#endif



#ifndef ADMIN_TYPE
#define	ADMIN_TYPE	0			//管理员PIN类型
#endif

#ifndef USER_TYPE
#define	USER_TYPE	1			//用户PIN类型
#endif

#pragma pack(push, 1)

//6.4	复合数据类型
//6.4.1	版本
typedef struct Struct_Version{
	BYTE major;		//主版本号
	BYTE minor;		//次版本号	
}VERSION;
//主版本号和次版本号以"."分隔，例如 Version 1.0，主版本号为1，次版本号为0；Version 2.10，主版本号为2，次版本号为10。

//6.4.2	设备信息
typedef struct Struct_DEVINFO{
	VERSION		Version;					//版本号	数据结构版本号，本结构的版本号为1.0
	CHAR		Manufacturer[64];			//设备厂商信息	以 '\0'为结束符的ASCII字符串
	CHAR		Issuer[64];					//发行厂商信息	以 '\0'为结束符的ASCII字符串
	CHAR		Label[32];					//设备标签	以 '\0'为结束符的ASCII字符串
	CHAR		SerialNumber[32];			//序列号	以 '\0'为结束符的ASCII字符串
	VERSION		HWVersion;					//设备硬件版本
	VERSION		FirmwareVersion;			//设备本身固件版本
	ULONG		AlgSymCap;					//分组密码算法标识
	ULONG		AlgAsymCap;					//非对称密码算法标识
	ULONG		AlgHashCap;					//密码杂凑算法标识
	ULONG		DevAuthAlgId;				//设备认证使用的分组密码算法标识
	ULONG		TotalSpace;					//设备总空间大小
	ULONG		FreeSpace;					//用户可用空间大小
	//ULONG		MaxECCBufferSize;			// 能够处理的 ECC 加密数据大小
	//ULONG		MaxBufferSize;				//能够处理的分组运算和杂凑运算的数据大小
	BYTE  		Reserved[64];				//保留扩展
}DEVINFO,*PDEVINFO;

//6.4.3	RSA公钥数据结构
#define MAX_RSA_MODULUS_LEN 256			//算法模数的最大长度
#define MAX_RSA_EXPONENT_LEN 4			//算法指数的最大长度
typedef struct Struct_RSAPUBLICKEYBLOB{
	ULONG	AlgID;									//算法标识号
	ULONG	BitLen;									//模数的实际位长度	必须是8的倍数
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];			//模数n = p * q	实际长度为BitLen/8字节
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];	//公开密钥e	一般为0x00010001
}RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;

//6.4.4	RSA私钥数据结构
typedef struct Struct_RSAPRIVATEKEYBLOB{
	ULONG	AlgID;									//算法标识号
	ULONG	BitLen;									//模数的实际位长度	必须是8的倍数
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];			//模数n = p * q	实际长度为BitLen/8字节
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];	//公开密钥e	一般为00010001
	BYTE	PrivateExponent[MAX_RSA_MODULUS_LEN];	//私有密钥d	实际长度为BitLen/8字节
	BYTE	Prime1[MAX_RSA_MODULUS_LEN/2];			//素数p	实际长度为BitLen/16字节
	BYTE	Prime2[MAX_RSA_MODULUS_LEN/2];			//素数q	实际长度为BitLen/16字节
	BYTE	Prime1Exponent[MAX_RSA_MODULUS_LEN/2];	//d mod (p-1)的值	实际长度为BitLen/16字节
	BYTE	Prime2Exponent[MAX_RSA_MODULUS_LEN/2];	//d mod (q -1)的值	实际长度为BitLen/16字节
	BYTE	Coefficient[MAX_RSA_MODULUS_LEN/2];		//q模p的乘法逆元	实际长度为BitLen/16字节
}RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;

//6.4.5	ECC公钥数据结构
#define ECC_MAX_XCOORDINATE_BITS_LEN 512	//ECC算法X坐标的最大长度
#define ECC_MAX_YCOORDINATE_BITS_LEN 512	//ECC算法Y坐标的最大长度
typedef struct Struct_ECCPUBLICKEYBLOB{
	ULONG	BitLen;											//模数的实际位长度	必须是8的倍数
	BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];	//曲线上点的X坐标	有限域上的整数
	BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];	//曲线上点的Y坐标	有限域上的整数
}ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;

//6.4.6	ECC私钥数据结构
#define ECC_MAX_MODULUS_BITS_LEN 512 //ECC算法模数的最大长度。
typedef struct Struct_ECCPRIVATEKEYBLOB{
	ULONG	BitLen;											//模数的实际位长度	必须是8的倍数
	BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];			//私有密钥	有限域上的整数
}ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;

//6.4.7	ECC密文数据结构
typedef struct Struct_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];		//与y组成椭圆曲线上的点（x，y）
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];		//与x组成椭圆曲线上的点（x，y）
	BYTE  HASH[32];											//明文的杂凑值
	ULONG	CipherLen;										//密文数据长度
	BYTE  Cipher[1];										//密文数据	实际长度为CipherLen
} ECCCIPHERBLOB, *PECCCIPHERBLOB;

//6.4.8	ECC签名数据结构
//ECC算法模数的最大长度
typedef struct Struct_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];			//签名结果的r部分
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];			//签名结果的s部分
} ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

//6.4.9	分组密码参数
#define MAX_IV_LEN 32
typedef struct Struct_BLOCKCIPHERPARAM{
	BYTE	IV[MAX_IV_LEN];							//初始向量，MAX_IV_LEN为初始化向量的最大长度
	ULONG	IVLen;									//初始向量实际长度（按字节计算）
	ULONG	PaddingType;							//填充方式，0表示不填充，1表示按照PKCS#5方式进行填充
	ULONG	FeedBitLen;								//反馈值的位长度（按位计算）	只针对OFB、CFB模式
} BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;

//6.4.10	ECC加密密钥对保护结构
typedef struct SKF_ENVELOPEDKEYBLOB{
	ULONG Version;							// 当前版本为 1
	ULONG ulSymmAlgID;						// 对称算法标识，限定ECB模式
	ULONG ulBits;							// 加密密钥对的密钥位长度
	BYTE cbEncryptedPriKey[64];				// 对称算法加密的加密私钥,加密私钥的原文为ECCPRIVATEKEYBLOB结构中的PrivateKey。	
	// 其有效长度为原文的（ulBits + 7）/8
	ECCPUBLICKEYBLOB PubKey;				// 加密密钥对的公钥
	ECCCIPHERBLOB ECCCipherBlob;			// 用保护公钥加密的对称密钥密文。
}ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

//6.4.11	文件属性
typedef struct Struct_FILEATTRIBUTE{
	CHAR	FileName[32];					//文件名	以'\0'结束的ASCII字符串，最大长度为32
	ULONG	FileSize;						//文件大小	创建文件时定义的文件大小
	ULONG	ReadRights;						//读取权限	读取文件需要的权限
	ULONG	WriteRights;					//写入权限	写入文件需要的权限
} FILEATTRIBUTE, *PFILEATTRIBUTE;

#pragma pack(pop)


//6.4.12	权限类型
#define SECURE_NEVER_ACCOUNT	0x00000000	//不允许
#define SECURE_ADM_ACCOUNT		0x00000001	//管理员权限
#define SECURE_USER_ACCOUNT		0x00000010	//用户权限
#define SECURE_ANYONE_ACCOUNT	0x000000FF	//任何人

//6.4.13	设备状态
#define DEV_ABSENT_STATE		0x00000000	//设备不存在
#define DEV_PRESENT_STATE		0x00000001	//设备存在
#define DEV_UNKNOW_STATE		0x00000002	//设备状态未知

//接口
#ifdef __cplusplus
extern "C" {
#endif

	//7.1	设备管理
	//7.1.2	等待设备插拔事件
	//函数原型	ULONG DEVAPI SKF_WaitForDevEvent(LPSTR szDevName,ULONG *pulDevNameLen, ULONG *pulEvent)
	//功能描述	该函数等待设备插入或者拔除事件。szDevName返回发生事件的设备名称。
	//参数		szDevName		[OUT] 发生事件的设备名称。
	//			pulDevNameLen	[IN/OUT] 输入/输出参数，当输入时表示缓冲区长度，输出时表示设备名称的有效长度,长度包含字符串结束符。
	//			pulEvent		[OUT]事件类型。1表示插入，2表示拔出。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_WaitForDevEvent(LPSTR szDevName,ULONG *pulDevNameLen, ULONG *pulEvent);

	//7.1.3	取消等待设备插拔事件
	//函数原型	ULONG DEVAPI SKF_CancelWaitForDevEvent()
	//功能描述	该函数取消等待设备插入或者拔除事件。
	//参数		
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		使本进程正在执行的SKF_WaitForDevEvent函数立即返回。
	ULONG DEVAPI SKF_CancelWaitForDevEvent();

	//7.1.4	枚举设备
	//函数原型	ULONG DEVAPI SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize)
	//功能描述	获得当前系统中的设备列表。
	//参数		bPresent	[IN] 为TRUE表示取当前设备状态为存在的设备列表。为FALSE表示取当前驱动支持的设备列表。
	//			szNameList	[OUT] 设备名称列表。如果该参数为NULL，将由pulSize返回所需要的内存空间大小。每个设备的名称以单个'\0'结束，以双'\0'表示列表的结束。
	//			pulSize		[IN，OUT] 输入时表示设备名称列表的缓冲区长度，输出时表示szNameList所占用的空间大小。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize);

	//7.1.5	连接设备
	//函数原型	ULONG DEVAPI SKF_ConnectDev (LPSTR szName, DEVHANDLE *phDev)
	//功能描述	通过设备名称连接设备，返回设备的句柄。
	//参数		szName	[IN] 设备名称。
	//			phDev	[OUT] 返回设备操作句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ConnectDev(LPSTR szName, DEVHANDLE *phDev);

	//7.1.6	断开连接
	//函数原型	ULONG DEVAPI SKF_DisConnectDev (DEVHANDLE hDev)
	//功能描述	断开一个已经连接的设备，并释放句柄。
	//参数		hDev	[IN] 连接设备时返回的设备句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		如果该设备已被锁定，函数应首先解锁该设备。断开连接操作并不影响设备的权限状态。
	ULONG DEVAPI SKF_DisConnectDev(DEVHANDLE hDev);

	//7.1.7	获取设备状态
	//函数原型	ULONG DEVAPI SKF_GetDevState(LPSTR szDevName, ULONG *pulDevState)
	//功能描述	获取设备是否存在的状态。
	//参数		szDevName	[IN] 设备名称。
	//			pulDevState	[OUT] 返回设备状态。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GetDevState(LPSTR szDevName, ULONG *pulDevState);

	//7.1.8	设置设备标签
	//函数原型	ULONG DEVAPI SKF_SetLabel (DEVHANDLE hDev, LPSTR szLabel)
	//功能描述	设置设备标签。
	//参数		hDev	[IN] 连接设备时返回的设备句柄。
	//			szLabel	[IN] 设备标签字符串。该字符串应小于32字节。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_SetLabel(DEVHANDLE hDev, LPSTR szLabel);

	//7.1.9	获取设备信息
	//函数原型	ULONG DEVAPI SKF_GetDevInfo (DEVHANDLE hDev, DEVINFO *pDevInfo)
	//功能描述	获取设备的一些特征信息，包括设备标签、厂商信息、支持的算法等。
	//参数		hDev		[IN] 连接设备时返回的设备句柄。
	//			pDevInfo	[OUT] 返回设备信息。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GetDevInfo(DEVHANDLE hDev, DEVINFO *pDevInfo);

	//7.1.10	锁定设备
	//函数原型	ULONG DEVAPI SKF_LockDev (DEVHANDLE hDev, ULONG ulTimeOut)
	//功能描述	获得设备的独占使用权。
	//参数		hDev		[IN] 连接设备时返回的设备句柄。
	//			ulTimeOut	[IN] 超时时间，单位为毫秒。如果为0xFFFFFFFF表示无限等待。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_LockDev(DEVHANDLE hDev, ULONG ulTimeOut);

	//7.1.11	解锁设备
	//函数原型	ULONG DEVAPI SKF_UnlockDev (DEVHANDLE hDev)
	//功能描述	释放对设备的独占使用权。
	//参数		hDev	[IN] 连接设备时返回的设备句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_UnlockDev(DEVHANDLE hDev);

	//7.1.12	设备命令传输
	//函数原型	ULONG DEVAPI SKF_Transmit(DEVHANDLE hDev, BYTE* pbCommand, ULONG ulCommandLen,BYTE* pbData, ULONG* pulDataLen)
	//功能描述	将命令直接发送给设备，并返回结果。
	//参数		hDev			[IN] 设备句柄。
	//			pbCommand		[IN] 设备命令。
	//			ulCommandLen	[IN] 命令长度。
	//			pbData			[OUT] 返回结果数据。
	//			pulDataLen		[IN，OUT] 输入时表示结果数据缓冲区长度，输出时表示结果数据实际长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_Transmit(DEVHANDLE hDev, BYTE* pbCommand, ULONG ulCommandLen,BYTE* pbData, ULONG* pulDataLen);

	//7.2	访问控制
	//访问控制主要完成设备认证、PIN码管理和安全状态管理等操作。

	//7.2.2	修改设备认证密钥
	//函数原型	ULONG DEVAPI SKF_ChangeDevAuthKey (DEVHANDLE hDev, BYTE *pbKeyValue， ULONG ulKeyLen)
	//功能描述	更改设备认证密钥。
	//参数		hDev		[IN] 连接时返回的设备句柄。
	//			pbKeyValue	[IN] 密钥值。
	//			ulKeyLen 	[IN] 密钥长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：设备认证成功后才能使用。
	ULONG DEVAPI SKF_ChangeDevAuthKey(DEVHANDLE hDev, BYTE *pbKeyValue, ULONG ulKeyLen);

	//7.2.3	设备认证
	//函数原型	ULONG DEVAPI SKF_DevAuth (DEVHANDLE hDev, BYTE *pbAuthData，ULONG ulLen)
	//功能描述	设备认证是设备对应用程序的认证。认证过程参见8.2.3。
	//参数		hDev		[IN] 连接时返回的设备句柄。
	//			pbAuthData	[IN] 认证数据。
	//			ulLen		[IN] 认证数据的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_DevAuth(DEVHANDLE hDev, BYTE *pbAuthData, ULONG ulLen);

	//7.2.4	修改PIN 
	//函数原型	ULONG DEVAPI SKF_ChangePIN (HAPPLICATION hApplication, ULONG ulPINType, LPSTR szOldPin, LPSTR szNewPin, ULONG *pulRetryCount)
	//功能描述	调用该函数可以修改Administrator PIN和User PIN的值。
	//			如果原PIN码错误导致验证失败，该函数会返回相应PIN码的剩余重试次数，当剩余次数为0时，表示PIN已经被锁死。
	//参数		hApplication	[IN] 应用句柄。
	//			ulPINType		[IN] PIN类型，可为ADMIN_TYPE或USER_TYPE。
	//			szOldPin		[IN] 原PIN值。
	//			szNewPin		[IN] 新PIN值。
	//			pulRetryCount	[OUT] 出错后重试次数。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ChangePIN(HAPPLICATION hApplication, ULONG ulPINType, LPSTR szOldPin, LPSTR szNewPin, ULONG *pulRetryCount);

	//7.2.5	获取PIN信息
	//函数原型	ULONG DEVAPI SKF_GetPINInfo(HAPPLICATION hApplication, ULONG  ulPINType, ULONG *pulMaxRetryCount, ULONG *pulRemainRetryCount, BOOL *pbDefaultPin)
	//功能描述	获取PIN码信息，包括最大重试次数、当前剩余重试次数，以及当前PIN码是否为出厂默认PIN码。
	//参数		hApplication		[IN] 应用句柄。
	//			ulPINType			[IN] PIN类型。
	//			pulMaxRetryCount	[OUT] 最大重试次数。
	//			pulRemainRetryCount	[OUT] 当前剩余重试次数，当为0时表示已锁死。
	//			pbDefaultPin		[OUT] 是否为出厂默认PIN码。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GetPINInfo(HAPPLICATION hApplication, ULONG  ulPINType, ULONG *pulMaxRetryCount, ULONG *pulRemainRetryCount, BOOL *pbDefaultPin);

	//7.2.6	校验PIN 
	//函数原型	ULONG DEVAPI SKF_VerifyPIN (HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount)
	//功能描述	校验PIN码。校验成功后，会获得相应的权限，如果PIN码错误，会返回PIN码的重试次数，当重试次数为0时表示PIN码已经锁死。
	//参数		hApplication	[IN] 应用句柄。
	//			ulPINType		[IN] PIN类型。
	//			szPIN			[IN] PIN值。
	//			pulRetryCount	[OUT] 出错后返回的重试次数。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_VerifyPIN(HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount);

	//7.2.7	解锁PIN 
	//函数原型	ULONG DEVAPI SKF_UnblockPIN (HAPPLICATION hApplication, LPSTR szAdminPIN, LPSTR szNewUserPIN,  ULONG *pulRetryCount)
	//功能描述	当用户的PIN码锁死后，通过调用该函数来解锁用户PIN码。
	//			解锁后，用户PIN码被设置成新值，用户PIN码的重试次数也恢复到原值。
	//参数		hApplication	[IN] 应用句柄。
	//			szAdminPIN		[IN] 管理员PIN码。
	//			szNewUserPIN	[IN] 新的用户PIN码。
	//			pulRetryCount	[OUT] 管理员PIN码错误时，返回剩余重试次数。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		验证完管理员PIN才能够解锁用户PIN码，如果输入的Administrator PIN不正确或者已经锁死，会调用失败，并返回Administrator PIN的重试次数。
	ULONG DEVAPI SKF_UnblockPIN(HAPPLICATION hApplication, LPSTR szAdminPIN, LPSTR szNewUserPIN,  ULONG *pulRetryCount);

	//7.2.8	清除应用安全状态
	//函数原型	ULONG DEVAPI SKF_ClearSecureState (HAPPLICATION hApplication)
	//功能描述	清除应用当前的安全状态。
	//参数		hApplication	[IN] 应用句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ClearSecureState(HAPPLICATION hApplication);

	//7.3	应用管理
	//应用管理主要完成应用的创建、枚举、删除、打开、关闭等操作

	//7.3.2	创建应用
	//函数原型	ULONG DEVAPI SKF_CreateApplication(DEVHANDLE hDev, LPSTR szAppName, LPSTR szAdminPin, DWORD dwAdminPinRetryCount,LPSTR szUserPin, DWORD dwUserPinRetryCount,DWORD dwCreateFileRights, HAPPLICATION *phApplication)
	//功能描述	创建一个应用。 
	//参数		hDev					[IN] 连接设备时返回的设备句柄。
	//			szAppName				[IN] 应用名称。
	//			szAdminPin				[IN] 管理员PIN。
	//			dwAdminPinRetryCount	[IN] 管理员PIN最大重试次数。
	//			szUserPin				[IN] 用户PIN。
	//			dwUserPinRetryCount		[IN] 用户PIN最大重试次数。
	//			dwCreateFileRights		[IN] 在该应用下创建文件和容器的权限，参见6.4.9权限类型。为各种权限的或值。
	//			phApplication			[OUT] 应用的句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要设备权限。
	ULONG DEVAPI SKF_CreateApplication(DEVHANDLE hDev, LPSTR szAppName, LPSTR szAdminPin, DWORD dwAdminPinRetryCount,LPSTR szUserPin, DWORD dwUserPinRetryCount,DWORD dwCreateFileRights, HAPPLICATION *phApplication);

	//7.3.3	枚举应用
	//函数原型	ULONG DEVAPI SKF_EnumApplication(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize)
	//功能描述	枚举设备中存在的所有应用。
	//参数		hDev		[IN] 连接设备时返回的设备句柄。
	//			szAppName	[OUT] 返回应用名称列表, 如果该参数为空，将由pulSize返回所需要的内存空间大小。每个应用的名称以单个'\0'结束，以双'\0'表示列表的结束。
	//			pulSize		[IN，OUT] 输入时表示应用名称的缓冲区长度，输出时返回szAppName所占用的空间大小。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EnumApplication(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize);

	//7.3.4	删除应用
	//函数原型	ULONG DEVAPI SKF_DeleteApplication(DEVHANDLE hDev, LPSTR szAppName)
	//功能描述	删除指定的应用。
	//参数		hDev		[IN] 连接设备时返回的设备句柄。
	//			szAppName	[IN] 应用名称。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要设备权限。
	ULONG DEVAPI SKF_DeleteApplication(DEVHANDLE hDev, LPSTR szAppName);

	//7.3.5	打开应用
	//函数原型	ULONG DEVAPI SKF_OpenApplication(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication)
	//功能描述	打开指定的应用。
	//参数		hDev			[IN] 连接设备时返回的设备句柄。
	//			szAppName		[IN] 应用名称。
	//			phApplication	[OUT] 应用的句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_OpenApplication(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);

	//7.3.6	关闭应用
	//函数原型	ULONG DEVAPI SKF_CloseApplication(HAPPLICATION hApplication)
	//功能描述	关闭应用并释放应用句柄。
	//参数		hApplication	[IN]应用句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		此函数不影响应用安全状态。
	ULONG DEVAPI SKF_CloseApplication(HAPPLICATION hApplication);

	//7.4	文件管理
	//7.4.1	概述
	//文件管理函数用以满足用户扩展开发的需要，包括创建文件、删除文件、枚举文件、获取文件信息、文件读写等操作。

	//7.4.2	创建文件
	//函数原型	ULONG DEVAPI SKF_CreateFile (HAPPLICATION hApplication, LPSTR szFileName, ULONG ulFileSize, ULONG ulReadRights，ULONG ulWriteRights)
	//功能描述	创建文件时要指定文件的名称，大小，以及文件的读写权限。
	//参数		hApplication	[IN] 应用句柄。
	//			szFileName		[IN] 文件名称，长度不得大于32个字节。
	//			ulFileSize		[IN] 文件大小。
	//			ulReadRights	[IN] 文件读权限，参见6.4.9 权限类型。可为各种权限的或值。
	//			ulWriteRights	[IN] 文件写权限，参见6.4.9权限类型。可为各种权限的或值。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		创建文件需要应用指定的创建文件权限。
	ULONG DEVAPI SKF_CreateFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulFileSize, ULONG ulReadRights, ULONG ulWriteRights);

	//7.4.3	删除文件
	//函数原型	ULONG DEVAPI SKF_DeleteFile (HAPPLICATION hApplication, LPSTR szFileName)
	//功能描述	删除指定文件：
	//文件删除后，文件中写入的所有信息将丢失。
	//文件在设备中的占用的空间将被释放。
	//参数		hApplication	[IN] 要删除文件所在的应用句柄。
	//			szFileName		[IN] 要删除文件的名称。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：删除一个文件应具有对该文件的创建权限。
	ULONG DEVAPI SKF_DeleteFile(HAPPLICATION hApplication, LPSTR szFileName);

	//7.4.4	枚举文件
	//函数原型	ULONG DEVAPI SKF_EnumFiles (HAPPLICATION hApplication, LPSTR szFileList, ULONG *pulSize)
	//功能描述	枚举一个应用下存在的所有文件。
	//参数		hApplication	[IN] 应用句柄。
	//			szFileList		[OUT] 返回文件名称列表，该参数为空，由pulSize返回文件信息所需要的空间大小。每个文件名称以单个'\0'结束，以双'\0'表示列表的结束。
	//			pulSize			[IN，OUT] 输入时表示数据缓冲区的大小，输出时表示实际文件名称列表的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EnumFiles(HAPPLICATION hApplication, LPSTR szFileList, ULONG *pulSize);

	//7.4.5	获取文件属性
	//函数原型	ULONG DEVAPI SKF_GetFileInfo (HAPPLICATION hApplication, LPSTR szFileName, FILEATTRIBUTE *pFileInfo)
	//功能描述	获取文件信息：
	//获取应用文件的属性信息，例如文件的大小、权限等。
	//参数		hApplication	[IN] 文件所在应用的句柄。
	//			szFileName		[IN] 文件名称。
	//			pFileInfo		[OUT] 文件信息，指向文件属性结构的指针。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GetFileInfo(HAPPLICATION hApplication, LPSTR szFileName, FILEATTRIBUTE *pFileInfo);

	//7.4.6	读文件
	//函数原型	ULONG DEVAPI SKF_ReadFile(HAPPLICATION hApplication， LPSTR szFileName, ULONG ulOffset, ULONG ulSize, BYTE * pbOutData, ULONG *pulOutLen)
	//功能描述	读取文件内容。
	//参数		hApplication	[IN] 应用句柄。
	//			szFileName		[IN] 文件名。
	//			ulOffset		[IN] 文件读取偏移位置。
	//			ulSize			[IN] 要读取的长度。
	//			pbOutData		[OUT] 返回数据的缓冲区。
	//			pulOutLen		[IN，OUT]输入时表示给出的缓冲区大小；输出时表示实际读取返回的数据大小。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：须具备对该文件的读权限。
	ULONG DEVAPI SKF_ReadFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulOffset, ULONG ulSize, BYTE * pbOutData, ULONG *pulOutLen);

	//7.4.7	写文件
	//函数原型	ULONG DEVAPI SKF_WriteFile (HAPPLICATION hApplication, LPSTR szFileName, ULONG  ulOffset, BYTE *pbInData, ULONG ulSize)
	//功能描述	写数据到文件中。
	//参数		hApplication	[IN] 应用句柄。
	//			szFileName		[IN] 文件名。
	//			ulOffset		[IN] 写入文件的偏移量。
	//			pbData			[IN] 写入数据缓冲区。
	//			ulSize			[IN] 写入数据的大小。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：须具备该文件的写权限。
	ULONG DEVAPI SKF_WriteFile(HAPPLICATION hApplication, LPSTR szFileName, ULONG  ulOffset, BYTE *pbInData, ULONG ulSize);

	//7.5	容器管理
	//7.5.1	概述
	//本规范提供的应用管理用于满足各种不同应用的管理，包括创建、删除、枚举、打开和关闭容器的操作。

	//7.5.2	创建容器
	//函数原型	ULONG DEVAPI SKF_CreateContainer (HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer)
	//功能描述	在应用下建立指定名称的容器并返回容器句柄。
	//参数		hApplication	[IN] 应用句柄。
	//			szContainerName	[IN] ASCII字符串，表示所建立容器的名称，容器名称的最大长度不能超过64字节。
	//			phContainer		[OUT] 返回所建立容器的容器句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_CreateContainer(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer);

	//7.5.3	删除容器
	//函数原型	ULONG DEVAPI SKF_DeleteContainer(HAPPLICATION hApplication, LPSTR szContainerName)
	//功能描述	在应用下删除指定名称的容器并释放容器相关的资源。
	//参数		hApplication	[IN] 应用句柄。
	//			szContainerName	[IN] 指向删除容器的名称。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_DeleteContainer(HAPPLICATION hApplication, LPSTR szContainerName);

	//7.5.4	打开容器
	//函数原型	ULONG DEVAPI SKF_OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer)
	//功能描述	获取容器句柄。
	//参数		hApplication	[IN] 应用句柄。
	//			szContainerName	[IN] 容器的名称。
	//			phContainer		[OUT] 返回所打开容器的句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);

	//7.5.5	关闭容器
	//函数原型	ULONG DEVAPI SKF_CloseContainer(HCONTAINER hContainer)
	//功能描述	关闭容器句柄，并释放容器句柄相关资源。
	//参数		hContainer	[IN] 容器句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_CloseContainer(HCONTAINER hContainer);

	//7.5.6	枚举容器
	//函数原型	ULONG DEVAPI SKF_EnumContainer (HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize)
	//功能描述	枚举应用下的所有容器并返回容器名称列表。
	//参数		hApplication	[IN] 应用句柄。
	//			szContainerName	[OUT] 指向容器名称列表缓冲区，如果此参数为NULL时，pulSize表示返回数据所需要缓冲区的长度，如果此参数不为NULL时，返回容器名称列表，每个容器名以单个'\0'为结束，列表以双'\0'结束。 
	//			pulSize			[IN，OUT] 输入时表示szContainerName缓冲区的长度，输出时表示容器名称列表的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EnumContainer(HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize);

	//7.5.7	获得容器类型
	//函数原型	ULONG DEVAPI SKF_GetContainerType(HCONTAINER hContainer, ULONG *pulContainerType)
	//功能描述	获取容器的类型
	//参数		hContainer			[IN] 容器句柄。
	//			pulContainerType	[OUT] 获得的容器类型。指针指向的值为0表示未定、尚未分配类型或者为空容器，为1表示为RSA容器，为2表示为ECC容器。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GetContainerType(HCONTAINER hContainer, ULONG *pulContainerType);

	//7.5.8	导入数字证书
	//函数原型	ULONG DEVAPI SKF_ImportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG ulCertLen)
	//功能描述	向容器内导入数字证书。
	//参数		hContainer	[IN] 容器句柄。
	//			bSignFlag	[IN] TRUE表示签名证书，FALSE表示加密证书。
	//			pbCert		[IN] 指向证书内容缓冲区。
	//			ulCertLen	[IN] 证书长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ImportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG ulCertLen);

	//7.5.9	导出数字证书
	//函数原型	ULONG DEVAPI SKF_ExportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen)
	//功能描述	从容器内导出数字证书。
	//参数		hContainer	[IN] 容器句柄。
	//			bSignFlag	[IN] TRUE表示签名证书，FALSE表示加密证书。
	//			pbCert		[OUT] 指向证书内容缓冲区，如果此参数为NULL时，pulCertLen表示返回数据所需要缓冲区的长度，如果此参数不为NULL时，返回数字证书内容。
	//			pulCertLen	[IN/OUT] 输入时表示pbCert缓冲区的长度，输出时表示证书内容的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ExportCertificate(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen);

	//7.6	密码服务
	//7.6.1	概述
	//密码服务函数提供对称算法运算、非对称算法运算、密码杂凑运算、密钥管理、消息鉴别码计算等功能。

	//7.6.2	生成随机数
	//函数原型	ULONG DEVAPI SKF_GenRandom (DEVHANDLE hDev, BYTE *pbRandom,ULONG ulRandomLen)
	//功能描述	产生指定长度的随机数。
	//参数		hDev		[IN] 设备句柄。
	//			pbRandom	[OUT]返回的随机数。
	//			ulRandomLen	[IN] 随机数长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GenRandom(DEVHANDLE hDev, BYTE *pbRandom,ULONG ulRandomLen);

	//7.6.3	生成外部RSA密钥对
	//函数原型	ULONG DEVAPI SKF_GenExtRSAKey (DEVHANDLE hDev, ULONG ulBitsLen, RSAPRIVATEKEYBLOB *pBlob)
	//功能描述	由设备生成RSA密钥对并明文输出。
	//参数		hDev		[IN]设备句柄。
	//			ulBitsLen	[IN] 密钥模长。
	//			pBlob		[OUT] 返回的私钥数据结构。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注：	生成的私钥只用于输出，接口内不做保留和计算。
	ULONG DEVAPI SKF_GenExtRSAKey(DEVHANDLE hDev, ULONG ulBitsLen, RSAPRIVATEKEYBLOB *pBlob);

	//7.6.4	生成RSA签名密钥对
	//函数原型	ULONG DEVAPI SKF_GenRSAKeyPair (HCONTAINER hContainer, ULONG ulBitsLen, RSAPUBLICKEYBLOB *pBlob)
	//功能描述	生成RSA签名密钥对并输出签名公钥。
	//参数		hContainer	[IN] 容器句柄。
	//			ulBitsLen	[IN] 密钥模长。
	//			pBlob		[OUT] 返回的RSA公钥数据结构。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_GenRSAKeyPair(HCONTAINER hContainer, ULONG ulBitsLen, RSAPUBLICKEYBLOB *pBlob);

	//7.6.5	导入RSA加密密钥对
	//函数原型	ULONG DEVAPI SKF_ImportRSAKeyPair (
	//												HCONTAINER hContainer, ULONG ulSymAlgId, 
	//												BYTE *pbWrappedKey, ULONG ulWrappedKeyLen,
	//												BYTE *pbEncryptedData, ULONG ulEncryptedDataLen)
	//功能描述	导入RSA加密公私钥对。
	//参数		hContainer			[IN] 容器句柄。
	//			ulSymAlgId			[IN] 对称算法密钥标识。
	//			pbWrappedKey		[IN] 使用该容器内签名公钥保护的对称算法密钥。
	//			ulWrappedKeyLen		[IN] 保护的对称算法密钥长度。
	//			pbEncryptedData		[IN] 对称算法密钥保护的RSA加密私钥。私钥的格式遵循PKCS #1 v2.1: RSA Cryptography Standard中的私钥格式定义。
	//			ulEncryptedDataLen	[IN] 对称算法密钥保护的RSA加密公私钥对长度。
	//返回值	SAR_OK：			成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_ImportRSAKeyPair(HCONTAINER hContainer, ULONG ulSymAlgId, 
		BYTE *pbWrappedKey, ULONG ulWrappedKeyLen,
		BYTE *pbEncryptedData, ULONG ulEncryptedDataLen);

	//7.6.6	RSA签名
	//函数原型	ULONG DEVAPI SKF_RSASignData(HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG *pulSignLen)
	//功能描述	使用hContainer指定容器的签名私钥，对指定数据pbData进行数字签名。签名后的结果存放到pbSignature缓冲区，设置pulSignLen为签名的长度。
	//参数		hContainer	[IN] 用来签名的私钥所在容器句柄。
	//			pbData		[IN] 被签名的数据。
	//			ulDataLen	[IN] 签名数据长度，应不大于RSA密钥模长-11。
	//			pbSignature	[OUT] 存放签名结果的缓冲区指针，如果值为NULL，用于取得签名结果长度。
	//			pulSignLen	[IN，OUT] 输入时表示签名结果缓冲区大小，输出时表示签名结果长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_RSASignData(HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG *pulSignLen);

	//7.6.7	RSA验签
	//函数原型	ULONG DEVAPI SKF_RSAVerify (DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG ulSignLen)
	//功能描述	验证RSA签名。用pRSAPubKeyBlob内的公钥值对待验签数据进行验签。
	//参数		hDev			[IN] 设备句柄。
	//			pRSAPubKeyBlob	[IN] RSA公钥数据结构。
	//			pbData			[IN] 待验证签名的数据。
	//			ulDataLen		[IN] 数据长度，应不大于公钥模长-11。
	//			pbSignature		[IN] 待验证的签名值。
	//			ulSignLen		[IN] 签名值长度，必须为公钥模长。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_RSAVerify(DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG ulSignLen);

	//7.6.8	RSA生成并导出会话密钥
	//函数原型	ULONG DEVAPI SKF_RSAExportSessionKey (HCONTAINER hContainer, ULONG ulAlgId, RSAPUBLICKEYBLOB *pPubKey, BYTE *pbData, ULONG  *pulDataLen, HANDLE *phSessionKey)
	//功能描述	生成会话密钥并用外部RSA公钥加密输出。
	//参数		hContainer	[IN] 容器句柄。
	//			ulAlgId		[IN] 会话密钥算法标识。
	//			pPubKey		[IN] 加密会话密钥的RSA公钥数据结构。
	//			pbData		[OUT] 导出的加密会话密钥密文，按照PKCS#1v1.5要求封装。
	//			pulDataLen	[IN，OUT] 输入时表示会话密钥密文数据缓冲区长度，输出时表示会话密钥密文的实际长度。
	//			phSessionKey[OUT] 导出的密钥句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_RSAExportSessionKey(HCONTAINER hContainer, ULONG ulAlgId, RSAPUBLICKEYBLOB *pPubKey, BYTE *pbData, ULONG  *pulDataLen, HANDLE *phSessionKey);

	//7.6.9	RSA外来公钥运算
	//函数原型	ULONG DEVAPI SKF_ExtRSAPubKeyOperation (DEVHANDLE hDev, RSAPUBLICKEYBLOB* pRSAPubKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen)
	//功能描述	使用外部传入的RSA公钥对输入数据做公钥运算并输出结果。
	//参数		hDev			[IN] 设备句柄。
	//			pRSAPubKeyBlob	[IN] RSA公钥数据结构。
	//			pbInput			[IN] 指向待运算的原始数据缓冲区。
	//			ulInputLen		[IN] 待运算原始数据的长度，必须为公钥模长。
	//			pbOutput		[OUT] 指向RSA公钥运算结果缓冲区，如果该参数为NULL，则由pulOutputLen返回运算结果的实际长度。
	//			pulOutputLen	[IN，OUT] 输入时表示pbOutput缓冲区的长度，输出时表示RSA公钥运算结果的实际长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ExtRSAPubKeyOperation(DEVHANDLE hDev, RSAPUBLICKEYBLOB* pRSAPubKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen);

	//7.6.10	RSA外来私钥运算
	//函数原型	ULONG DEVAPI SKF_ExtRSAPriKeyOperation (DEVHANDLE hDev, RSAPRIVATEKEYBLOB* pRSAPriKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen)
	//功能描述	直接使用外部传入的RSA私钥对输入数据做私钥运算并输出结果。
	//参数		hDev			[IN] 设备句柄。
	//			pRSAPriKeyBlob	[IN] RSA私钥数据结构。
	//			pbInput			[IN] 指向待运算数据缓冲区。
	//			ulInputLen		[IN] 待运算数据的长度，必须为公钥模长。
	//			pbOutput		[OUT] RSA私钥运算结果，如果该参数为NULL，则由pulOutputLen返回运算结果的实际长度。
	//			pulOutputLen	[IN，OUT] 输入时表示pbOutput缓冲区的长度，输出时表示RSA私钥运算结果的实际长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ExtRSAPriKeyOperation(DEVHANDLE hDev, RSAPRIVATEKEYBLOB* pRSAPriKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen);

	//7.6.11	生成ECC签名密钥对
	//函数原型	ULONG DEVAPI SKF_GenECCKeyPair (HCONTAINER hContainer, ULONG ulAlgId， ECCPUBLICKEYBLOB *pBlob)
	//功能描述	生成ECC签名密钥对并输出签名公钥。
	//参数		hContainer	[IN] 密钥容器句柄。
	//			ulAlgId		[IN] 算法标识，只支持SGD_SM2_1算法。
	//			pBlob		[OUT] 返回ECC公钥数据结构。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_GenECCKeyPair(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pBlob);

	//7.6.12	导入ECC加密密钥对
	//函数原型	ULONG DEVAPI SKF_ImportECCKeyPair(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob)
	//功能描述	导入ECC公私钥对。
	//参数		hContainer			[IN] 密钥容器句柄。
	//			pEnvelopedKeyBlob	[IN] 受保护的加密密钥对。
	//返回值	SAR_OK：			成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_ImportECCKeyPair(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob);

	//7.6.13	ECC签名
	//函数原型	ULONG DEVAPI SKF_ECCSignData (HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature)
	//功能描述	ECC数字签名。采用ECC算法和指定私钥hKey，对指定数据pbData进行数字签名。签名后的结果存放到pSignature中。
	//参数		hContainer	[IN] 密钥容器句柄。
	//			pbData		[IN] 待签名的数据。
	//			ulDataLen	[IN] 待签名数据长度，必须小于密钥模长。
	//			pSignature	[OUT] 签名值。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	//			输入数据为待签数据的杂凑值。当使用SM2算法时，该输入数据为待签数据经过SM2签名预处理的结果，
	//			预处理过程遵循《公钥密码基础设施应用技术体系 SM2算法密码使用规范》。
	ULONG DEVAPI SKF_ECCSignData(HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);

	//7.6.14	ECC验签
	//函数原型	ULONG DEVAPI SKF_ECCVerify (DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature)
	//功能描述	用ECC公钥对数据进行验签。
	//参数		hDev			[IN] 设备句柄。
	//			pECCPubKeyBlob	[IN] ECC公钥数据结构。
	//			pbData			[IN] 待验证签名的数据。
	//			ulDataLen		[IN] 数据长度。
	//			pSignature		[IN] 待验证签名值。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	//备注		输入数据为待签数据的杂凑值。当使用SM2算法时，该输入数据为待签数据经过SM2签名预处理的结果，
	//			预处理过程遵循《公钥密码基础设施应用技术体系 SM2算法密码使用规范》。
	ULONG DEVAPI SKF_ECCVerify(DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);

	//7.6.15	ECC生成并导出会话密钥
	//函数原型	ULONG DEVAPI SKF_ECCExportSessionKey (HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pPubKey, PECCCIPHERBLOB pData, HANDLE *phSessionKey)
	//功能描述	生成会话密钥并用外部公钥加密导出。
	//参数		hContainer		[IN] 容器句柄。
	//			ulAlgId			[IN] 会话密钥算法标识。
	//			pPubKey			[IN] 外部输入的公钥结构。
	//			pData			[OUT] 会话密钥密文。
	//			phSessionKey	[OUT] 会话密钥句柄。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ECCExportSessionKey(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pPubKey, PECCCIPHERBLOB pData, HANDLE *phSessionKey);

	//7.6.16	ECC外来公钥加密
	//函数原型	ULONG DEVAPI SKF_ExtECCEncrypt (DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbPlainText, ULONG ulPlainTextLen, PECCCIPHERBLOB pCipherText)
	//功能描述	使用外部传入的ECC公钥对输入数据做加密运算并输出结果。
	//参数		hDev			[IN] 设备句柄。
	//			pECCPubKeyBlob	[IN] ECC公钥数据结构。
	//			pbPlainText		[IN] 待加密的明文数据。
	//			ulPlainTextLen	[IN] 待加密明文数据的长度。
	//			pCipherText		[OUT] 密文数据。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ExtECCEncrypt(DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbPlainText, ULONG ulPlainTextLen, PECCCIPHERBLOB pCipherText);

	//7.6.17	ECC外来私钥解密
	//函数原型	ULONG DEVAPI SKF_ExtECCDecrypt (DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, PECCCIPHERBLOB pCipherText, BYTE* pbPlainText, ULONG* pulPlainTextLen)
	//功能描述	使用外部传入的ECC私钥对输入数据做解密运算并输出结果。
	//参数		hDev			[IN] 设备句柄。
	//			pECCPriKeyBlob	[IN] ECC私钥数据结构。
	//			pCipherText		[IN] 待解密的密文数据。
	//			pbPlainText		[OUT] 返回明文数据，如果该参数为NULL，则由pulPlainTextLen返回明文数据的实际长度。
	//			pulPlainTextLen	[IN，OUT] 输入时表示pbPlainText缓冲区的长度，输出时表示明文数据的实际长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ExtECCDecrypt(DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, PECCCIPHERBLOB pCipherText, BYTE* pbPlainText, ULONG* pulPlainTextLen);

	//7.6.18	ECC外来私钥签名
	//函数原型	ULONG DEVAPI SKF_ExtECCSign (DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature)
	//功能描述	使用外部传入的ECC私钥对输入数据做签名运算并输出结果。
	//参数		hDev			[IN] 设备句柄。
	//			pECCPriKeyBlob	[IN] ECC私钥数据结构。
	//			pbData			[IN] 待签名数据。
	//			ulDataLen		[IN] 待签名数据的长度。
	//			pSignature		[OUT]签名值。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	//备注：	输入数据为待签数据的杂凑值。当使用SM2算法时，该输入数据为待签数据经过SM2签名预处理的结果，
	//			预处理过程遵循《公钥密码基础设施应用技术体系 SM2算法密码使用规范》。
	ULONG DEVAPI SKF_ExtECCSign(DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);

	//7.6.19	ECC外来公钥验签
	//函数原型	ULONG DEVAPI SKF_ExtECCVerify (DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature)
	//功能描述	外部使用传入的ECC公钥做签名验证。
	//参数		hDev			[IN] 设备句柄。
	//			pECCPubKeyBlob	[IN] ECC公钥数据结构。
	//			pbData			[IN] 待验证数据。
	//			ulDataLen		[IN] 待验证数据的长度。
	//			pSignature		[IN] 签名值。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	//备注：	输入数据为待签数据的杂凑值。当使用SM2算法时，该输入数据为待签数据经过SM2签名预处理的结果，
	//			预处理过程遵循《公钥密码基础设施应用技术体系 SM2算法密码使用规范》。
	ULONG DEVAPI SKF_ExtECCVerify(DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);

	//7.6.20	ECC生成密钥协商参数并输出
	//函数原型	ULONG DEVAPI SKF_GenerateAgreementDataWithECC (HCONTAINER hContainer, ULONG ulAlgId,ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,BYTE* pbID, ULONG ulIDLen,HANDLE *phAgreementHandle)
	//功能描述	使用ECC密钥协商算法，为计算会话密钥而产生协商参数，返回临时ECC密钥对的公钥及协商句柄。
	//参数		hContainer			[IN] 容器句柄。
	//			ulAlgId				[IN] 会话密钥算法标识。
	//			pTempECCPubKeyBlob	[OUT] 发起方临时ECC公钥。
	//			pbID				[IN] 发起方的ID。
	//			ulIDLen				[IN] 发起方ID的长度，不大于32。
	//			phAgreementHandle	[OUT] 返回的密钥协商句柄。
	//返回值	SAR_OK：			成功。
	//其他：	错误码。
	//备注		为协商会话密钥，协商的发起方应首先调用本函数。	
	ULONG DEVAPI SKF_GenerateAgreementDataWithECC(HCONTAINER hContainer, ULONG ulAlgId,ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,BYTE* pbID, ULONG ulIDLen,HANDLE *phAgreementHandle);

	//7.6.21	ECC产生协商数据并计算会话密钥
	//函数原型：ULONG DEVAPI SKF_GenerateAgreementDataAndKeyWithECC(
	//														HANDLE hContainer, ULONG ulAlgId,
	//														ECCPUBLICKEYBLOB*  pSponsorECCPubKeyBlob,
	//														ECCPUBLICKEYBLOB*  pSponsorTempECCPubKeyBlob,
	//														ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
	//														BYTE* pbID, ULONG ulIDLen, BYTE *pbSponsorID, ULONG ulSponsorIDLen,
	//														HANDLE *phKeyHandle)
	//功能描述：使用ECC密钥协商算法，产生协商参数并计算会话密钥，输出临时ECC密钥对公钥，并返回产生的密钥句柄。
	//参数：	hContainer					[IN] 容器句柄。
	//			ulAlgId						[IN] 会话密钥算法标识。
	//			pSponsorECCPubKeyBlob		[IN] 发起方的ECC公钥。
	//			pSponsorTempECCPubKeyBlob	[IN] 发起方的临时ECC公钥。
	//			pTempECCPubKeyBlob			[OUT] 响应方的临时ECC公钥。
	//			pbID						[IN] 响应方的ID。
	//			ulIDLen						[IN] 响应方ID的长度，不大于32。
	//			pbSponsorID					[IN] 发起方的ID。
	//			ulSponsorIDLen				[IN] 发起方ID的长度，不大于32。
	//			phKeyHandle					[OUT] 返回的对称算法密钥句柄。
	//返回值	SAR_OK：					成功。
	//其他：	错误码。
	//备注：	本函数由响应方调用。
	ULONG DEVAPI SKF_GenerateAgreementDataAndKeyWithECC(
		HANDLE hContainer, ULONG ulAlgId,
		ECCPUBLICKEYBLOB*  pSponsorECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pSponsorTempECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
		BYTE* pbID, ULONG ulIDLen, BYTE *pbSponsorID, ULONG ulSponsorIDLen,
		HANDLE *phKeyHandle);

	//7.6.22	ECC计算会话密钥
	//函数原型：ULONG DEVAPI SKF_GenerateKeyWithECC (HANDLE hAgreementHandle,
	//												ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
	//												ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
	//												BYTE* pbID, ULONG ulIDLen, HANDLE *phKeyHandle)
	//功能描述：使用ECC密钥协商算法，使用自身协商句柄和响应方的协商参数计算会话密钥，同时返回会话密钥句柄。
	//参数：	hAgreementHandle	[IN] 密钥协商句柄。
	//			pECCPubKeyBlob		[IN] 外部输入的响应方ECC公钥。
	//			pTempECCPubKeyBlob	[IN] 外部输入的响应方临时ECC公钥。
	//			pbID				[IN] 响应方的ID。
	//			ulIDLen				[IN] 响应方ID的长度，不大于32。
	//			phKeyHandle			[OUT] 返回的密钥句柄。
	//返回值	SAR_OK：			成功。
	//其他：	错误码。
	//备注：	协商的发起方获得响应方的协商参数后调用本函数，计算会话密钥。
	//			计算过程遵循《公钥密码基础设施应用技术体系 SM2算法密码使用规范》。
	ULONG DEVAPI SKF_GenerateKeyWithECC(HANDLE hAgreementHandle,
		ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
		BYTE* pbID, ULONG ulIDLen, HANDLE *phKeyHandle);

	//7.6.23	导出公钥
	//函数原型	ULONG DEVAPI SKF_ExportPublicKey (HCONTAINER hContainer, BOOL bSignFlag， BYTE* pbBlob, ULONG* pulBlobLen)
	//功能描述	导出容器中的签名公钥或者加密公钥。
	//参数		hContainer	[IN] 密钥容器句柄。
	//			bSignFlag	[IN] TRUE表示导出签名公钥，FALSE表示导出加密公钥。
	//			pbBlob		[OUT] 指向RSA公钥结构（RSAPUBLICKEYBLOB）或者ECC公钥结构（ECCPUBLICKEYBLOB），
	//							  如果此参数为NULL时，由pulBlobLen返回pbBlob的长度。
	//			pulBlobLen	[IN，OUT] 输入时表示pbBlob缓冲区的长度，输出时表示导出公钥结构的大小。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ExportPublicKey(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen);

	//7.6.24	导入会话密钥
	//函数原型	ULONG DEVAPI SKF_ImportSessionKey (HCONTAINER hContainer, ULONG ulAlgId,BYTE *pbWrapedData,ULONG ulWrapedLen，HANDLE *phKey)
	//功能描述	导入会话密钥密文，使用容器中的加密私钥解密得到会话密钥。
	//参数		hContainer		[IN] 容器句柄。
	//			ulAlgId			[IN] 会话密钥算法标识。
	//			pbWrapedData	[IN] 要导入的会话密钥密文。当容器为ECC类型时，此参数为ECCCIPHERBLOB密文数据，当容器为RSA类型时，此参数为RSA公钥加密后的数据。
	//			ulWrapedLen		[IN] 会话密钥密文长度。
	//			phKey			[OUT] 返回会话密钥句柄。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	//备注		权限要求：需要用户权限。
	ULONG DEVAPI SKF_ImportSessionKey(HCONTAINER hContainer, ULONG ulAlgId,BYTE *pbWrapedData,ULONG ulWrapedLen, HANDLE *phKey);

	//7.6.25	明文导入会话密钥
	//函数原型	ULONG DEVAPI SKF_SetSymmKey (DEVHANDLE hDev, BYTE* pbKey, ULONG ulAlgID, HANDLE* phKey)
	//功能描述	设置明文对称密钥，返回密钥句柄。
	//参数		hDev		[IN] 设备句柄。
	//			pbKey		[IN] 指向会话密钥值的缓冲区。
	//			ulAlgID		[IN] 会话密钥算法标识。
	//			phKey		[OUT] 返回会话密钥句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_SetSymmKey(DEVHANDLE hDev, BYTE* pbKey, ULONG ulAlgID, HANDLE* phKey);

	//7.6.26	加密初始化
	//函数原型	ULONG DEVAPI SKF_EncryptInit (HANDLE hKey, BLOCKCIPHERPARAM EncryptParam)
	//功能描述	数据加密初始化。设置数据加密的算法相关参数。
	//参数		hKey			[IN] 加密密钥句柄。
	//			EncryptParam	[IN] 分组密码算法相关参数：初始向量、初始向量长度、填充方法、反馈值的位长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EncryptInit(HANDLE hKey, BLOCKCIPHERPARAM EncryptParam);

	//7.6.27	单组数据加密
	//函数原型	ULONG DEVAPI SKF_Encrypt(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen)
	//功能描述	单一分组数据的加密操作。用指定加密密钥对指定数据进行加密，被加密的数据只包含一个分组，加密后的密文保存到指定的缓冲区中。SKF_Encrypt只对单个分组数据进行加密，在调用SKF_Encrypt之前，必须调用SKF_EncryptInit初始化加密操作。SKF_Encypt等价于先调用SKF_EncryptUpdate再调用SKF_EncryptFinal。
	//参数		hKey 			[IN] 加密密钥句柄。
	//			pbData			[IN] 待加密数据。
	//			ulDataLen		[IN] 待加密数据长度。
	//			pbEncryptedData	[OUT] 加密后的数据缓冲区指针，可以为NULL，用于获得加密后数据长度。
	//			pulEncryptedLen	[IN，OUT] 输入时表示结果数据缓冲区长度，输出时表示结果数据实际长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_Encrypt(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);

	//7.6.28	多组数据加密
	//函数原型	ULONG DEVAPI SKF_EncryptUpdate(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen)
	//功能描述	多个分组数据的加密操作。用指定加密密钥对指定数据进行加密，被加密的数据包含多个分组，加密后的密文保存到指定的缓冲区中。SKF_EncryptUpdate对多个分组数据进行加密，在调用SKF_EncryptUpdate之前，必须调用SKF_EncryptInit初始化加密操作；在调用SKF_EncryptUpdate之后，必须调用SKF_EncryptFinal结束加密操作。
	//参数		hKey 			[IN] 加密密钥句柄。
	//			pbData			[IN] 待加密数据。
	//			ulDataLen		[IN] 待加密数据长度。
	//			pbEncryptedData	[OUT] 加密后的数据缓冲区指针。
	//			pulEncryptedLen	[OUT] 返回加密后的数据长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EncryptUpdate(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);

	//7.6.29	结束加密
	//函数原型	ULONG DEVAPI SKF_EncryptFinal (HANDLE hKey, BYTE *pbEncryptedData, ULONG *ulEncryptedDataLen )
	//功能描述	结束多个分组数据的加密，返回剩余加密结果。先调用SKF_EncryptInit初始化加密操作，再调用SKF_EncryptUpdate对多个分组数据进行加密，最后调用SKF_EncryptFinal结束多个分组数据的加密。
	//参数		hKey				[IN] 加密密钥句柄。
	//			pbEncyptedData		[OUT] 加密结果的缓冲区。
	//			ulEncyptedDataLen	[OUT] 加密结果的长度。
	//返回值	SAR_OK：			成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_EncryptFinal(HANDLE hKey, BYTE *pbEncryptedData, ULONG *ulEncryptedDataLen );

	//7.6.30	解密初始化
	//函数原型	ULONG DEVAPI SKF_DecryptInit (HANDLE hKey, BLOCKCIPHERPARAM DecryptParam)
	//功能描述	数据解密初始化，设置解密密钥相关参数。调用SKF_DecryptInit之后，可以调用SKF_Decrypt对单个分组数据进行解密，也可以多次调用SKF_DecryptUpdate之后再调用SKF_DecryptFinal完成对多个分组数据的解密。
	//参数		hKey			[IN] 解密密钥句柄。
	//			DecryptParam	[IN] 分组密码算法相关参数：初始向量、初始向量长度、填充方法、反馈值的位长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_DecryptInit(HANDLE hKey, BLOCKCIPHERPARAM DecryptParam);

	//7.6.31	单组数据解密
	//函数原型	ULONG DEVAPI SKF_Decrypt(HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen)
	//功能描述	单个分组数据的解密操作。用指定解密密钥对指定数据进行解密，被解密的数据只包含一个分组，解密后的明文保存到指定的缓冲区中。SKF_Decrypt只对单个分组数据进行解密，在调用SKF_Decrypt之前，必须调用SKF_DecryptInit初始化解密操作。SKF_Decypt等价于先调用SKF_DecryptUpdate再调用SKF_DecryptFinal。
	//参数		hKey 			[IN] 解密密钥句柄。
	//			pbEncryptedData	[IN] 待解密数据。
	//			ulEncryptedLen	[IN] 待解密数据长度。
	//			pbData			[OUT] 指向解密后的数据缓冲区指针，当为NULL时可获得解密后的数据长度。
	//			pulDataLen		[IN，OUT] 输入时表示结果数据缓冲区长度，输出时表示结果数据实际长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_Decrypt(HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);

	//7.6.32	多组数据解密
	//函数原型	ULONG DEVAPI SKF_DecryptUpdate(HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen)
	//功能描述	多个分组数据的解密操作。用指定解密密钥对指定数据进行解密，被解密的数据包含多个分组，解密后的明文保存到指定的缓冲区中。SKF_DecryptUpdate对多个分组数据进行解密，在调用SKF_DecryptUpdate之前，必须调用SKF_DecryptInit初始化解密操作；在调用SKF_DecryptUpdate之后，必须调用SKF_DecryptFinal结束解密操作。
	//参数		hKey 			[IN] 解密密钥句柄。
	//			pbEncryptedData	[IN] 待解密数据。
	//			ulEncryptedLen	[IN] 待解密数据长度。
	//			pbData			[OUT] 指向解密后的数据缓冲区指针。
	//			pulDataLen		[IN，OUT] 输入时表示结果数据缓冲区长度，输出时表示结果数据实际长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_DecryptUpdate(HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);

	//7.6.33	结束解密
	//函数原型	ULONG DEVAPI SKF_DecryptFinal (HANDLE hKey, BYTE *pbDecryptedData, ULONG *pulDecryptedDataLen)
	//功能描述	结束多个分组数据的解密。先调用SKF_DecryptInit初始化解密操作，再调用SKF_DecryptUpdate对多个分组数据进行解密，最后调用SKF_DecryptFinal结束多个分组数据的解密。
	//参数		hKey				[IN] 解密密钥句柄。
	//			pbDecryptedData		[OUT] 指向解密结果的缓冲区，如果此参数为NULL时，由pulDecryptedDataLen返回解密结果的长度。
	//			pulDecryptedDataLen	[IN，OUT] 输入时表示pbDecryptedData缓冲区的长度，输出时表示解密结果的长度。
	//返回值	SAR_OK：			成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_DecryptFinal(HANDLE hKey, BYTE *pbDecryptedData, ULONG *pulDecryptedDataLen);

	//7.6.34	密码杂凑初始化
	//函数原型	ULONG DEVAPI SKF_DigestInit(DEVHANDLE hDev, ULONG ulAlgID,  ECCPUBLICKEYBLOB *pPubKey, unsigned char *pucID, ULONG ulIDLen, HANDLE *phHash)
	//功能描述	初始化密码杂凑计算操作，指定计算密码杂凑的算法。
	//参数		hDev	[IN] 连接设备时返回的设备句柄。
	//			ulAlgID	[IN] 密码杂凑算法标识。
	//			pPubKey	[IN] 签名者公钥。当alAlgID为SGD_SM3时有效。
	//			pucID	[IN] 签名者的ID值，当alAlgID为SGD_SM3时有效。
	//			ulIDLen	[IN] 签名者ID的长度，当alAlgID为SGD_SM3时有效。
	//			phHash	[OUT] 密码杂凑对象句柄。
	//返回值	SAR_OK：成功。
	//其他：	错误码。
	//备注		当ulAlgID为SGD_SM3且ulIDLen不为0的情况下pPubKey、pucID有效，执行SM2算法签名预处理1操作。
	//			计算过程遵循《公钥密码基础设施应用技术体系 SM2算法密码使用规范》。
	ULONG DEVAPI SKF_DigestInit(DEVHANDLE hDev, ULONG ulAlgID,  ECCPUBLICKEYBLOB *pPubKey, unsigned char *pucID, ULONG ulIDLen, HANDLE *phHash);

	//7.6.35	单组数据密码杂凑
	//函数原型	ULONG DEVAPI SKF_Digest (HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen)
	//功能描述	对单一分组的消息进行密码杂凑计算。调用SKF_Digest之前，必须调用SKF_DigestInit初始化密码杂凑计算操作。
	//			SKF_Digest等价于多次调用SKF_DigestUpdate之后再调用SKF_DigestFinal。
	//参数		hHash		[IN] 密码杂凑对象句柄。
	//			pbData		[IN] 指向消息数据的缓冲区。
	//			ulDataLen	[IN] 消息数据的长度。
	//			pbHashData	[OUT] 密码杂凑数据缓冲区指针，当此参数为NULL时，由pulHashLen返回密码杂凑结果的长度。
	//			pulHashLen	[IN，OUT] 输入时表示结果数据缓冲区长度，输出时表示结果数据实际长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_Digest(HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen);

	//7.6.36	多组数据密码杂凑
	//函数原型	ULONG DEVAPI SKF_DigestUpdate (HANDLE hHash, BYTE *pbData, ULONG  ulDataLen)
	//功能描述	对多个分组的消息进行密码杂凑计算。调用SKF_DigestUpdate之前，必须调用SKF_DigestInit初始化密码杂凑计算操作；
	//			调用SKF_DigestUpdate之后，必须调用SKF_DigestFinal结束密码杂凑计算操作。
	//参数		hHash		[IN] 密码杂凑对象句柄。
	//			pbData		[IN] 指向消息数据的缓冲区。
	//			ulDataLen	[IN] 消息数据的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_DigestUpdate(HANDLE hHash, BYTE *pbData, ULONG  ulDataLen);

	//7.6.37	结束密码杂凑
	//函数原型	ULONG DEVAPI SKF_DigestFinal (HANDLE hHash, BYTE *pHashData, ULONG  *pulHashLen)
	//功能描述	结束多个分组消息的密码杂凑计算操作，将密码杂凑结果保存到指定的缓冲区。
	//参数		hHash		[IN] 密码杂凑对象句柄。
	//			pHashData	[OUT] 返回的密码杂凑结果缓冲区指针，如果此参数NULL时，由pulHashLen返回杂凑结果的长度。
	//			pulHashLen	[IN，OUT] 输入时表示杂凑结果缓冲区的长度，输出时表示密码杂凑结果的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		SKF_DigestFinal必须用于SKF_DigestUpdate之后。
	ULONG DEVAPI SKF_DigestFinal(HANDLE hHash, BYTE *pHashData, ULONG  *pulHashLen);

	//7.6.38	消息鉴别码运算初始化
	//函数原型	ULONG DEVAPI SKF_MacInit (HANDLE hKey, BLOCKCIPHERPARAM* pMacParam, HANDLE *phMac)
	//功能描述	初始化消息鉴别码计算操作，设置计算消息鉴别码的所需参数，并返回消息鉴别码句柄。
	//参数		hKey		[IN] 计算消息鉴别码的密钥句柄。
	//			pMacParam	[IN] 消息认证计算相关参数，包括初始向量、初始向量长度、填充方法等。
	//			phMac		[OUT] 消息鉴别码对象句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		消息鉴别码计算采用分组加密算法的CBC模式，将加密结果的最后一块作为计算结果。待计算数据的长度必须是分组加密算法块长的倍数，接口内部不作数据填充。
	ULONG DEVAPI SKF_MacInit(HANDLE hKey, BLOCKCIPHERPARAM* pMacParam, HANDLE *phMac);

	//7.6.39	单组数据消息鉴别码运算
	//函数原型	ULONG DEVAPI SKF_Mac(HANDLE hMac, BYTE* pbData, ULONG ulDataLen, BYTE *pbMacData, ULONG *pulMacLen)
	//功能描述	SKF_Mac计算单一分组数据的消息鉴别码。
	//参数		hMac		[IN] 消息鉴别码句柄。
	//			pbData		[IN] 指向待计算数据的缓冲区。
	//			ulDataLen	[IN] 待计算数据的长度。
	//			pbMacData	[OUT] 指向计算后的Mac结果，如果此参数为NULL时，由pulMacLen返回计算后Mac结果的长度。
	//			pulMacLen	[IN，OUT] 输入时表示pbMacData缓冲区的长度，输出时表示Mac结果的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		调用SKF_Mac之前，必须调用SKF_MacInit初始化消息鉴别码计算操作。SKF_Mac等价于多次调用SKF_MacUpdate之后再调用SKF_MacFinal。
	ULONG DEVAPI SKF_Mac(HANDLE hMac, BYTE* pbData, ULONG ulDataLen, BYTE *pbMacData, ULONG *pulMacLen);

	//7.6.40	多组数据消息鉴别码运算
	//函数原型	ULONG DEVAPI SKF_MacUpdate(HANDLE hMac, BYTE * pbData, ULONG ulDataLen)
	//功能描述	计算多个分组数据的消息鉴别码。
	//参数		hMac		[IN] 消息鉴别码句柄。
	//			pbData		[IN] 指向待计算数据的缓冲区。
	//			plDataLen	[IN] 待计算数据的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	//备注		调用SKF_MacUpdate之前，必须调用SKF_MacInit初始化消息鉴别码计算操作；调用SKF_MacUpdate之后，必须调用SKF_MacFinal结束多个分组数据的消息鉴别码计算操作。
	ULONG DEVAPI SKF_MacUpdate(HANDLE hMac, BYTE * pbData, ULONG ulDataLen);

	//7.6.41	结束消息鉴别码运算
	//函数原型	ULONG DEVAPI SKF_MacFinal (HANDLE hMac, BYTE *pbMacData, ULONG *pulMacDataLen)
	//功能描述	结束多个分组数据的消息鉴别码计算操作。
	//参数		hMac			[IN] 消息鉴别码句柄。
	//			pbMacData		[OUT] 指向消息鉴别码的缓冲区，当此参数为NULL时，由pulMacDataLen返回消息鉴别码返回的长度。
	//			pulMacDataLen	[OUT] 调用时表示消息鉴别码缓冲区的最大长度，返回消息鉴别码的长度。
	//返回值	SAR_OK：		成功。
	//其他：	错误码。
	//备注		SKF_MacFinal必须用于SKF_MacUpdate之后。
	ULONG DEVAPI SKF_MacFinal(HANDLE hMac, BYTE *pbMacData, ULONG *pulMacDataLen);

	//7.6.42	关闭密码对象句柄
	//函数原型	ULONG DEVAPI SKF_CloseHandle(HANDLE hHandle)
	//功能描述	关闭会话密钥、密码杂凑对象、消息鉴别码对象、ECC密钥协商等句柄。
	//参数		hHandle		[IN] 要关闭的对象句柄。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_CloseHandle(HANDLE hHandle);


	// 扩展函数

	// ECC解密
	//函数原型	ULONG DEVAPI SKF_ECCDecrypt(HCONTAINER hContainer, BYTE *pbCiphertext, ULONG ulCiphertextLen, BYTE *pbPlaintext, ULONG *pulPlaintextLen)
	//功能描述	ECC数据解密。用容器中解密私钥解密数据，解密后的结果存放到pbPlaintext中。
	//参数		hContainer		[IN] 密钥容器句柄。
	//			pbCiphertext	[IN] 待解密的数据。此参数为ECCCIPHERBLOB密文数据。
	//			ulCiphertextLen	[IN] 待解密数据长度。
	//			pbPlaintext		[OUT] 解密后的明文，如果该参数为NULL，将由pulPlaintextLen返回所需要的内存空间大小。
	//			pulPlaintextLen	[IN OUT] 输入时表示pbPlaintext缓冲区的长度，输出时表示密文结果的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ECCDecrypt(HCONTAINER hContainer, BYTE *pbCiphertext, ULONG ulCiphertextLen, BYTE *pbPlaintext, ULONG *pulPlaintextLen);

	// ECC解密2
	//函数原型	ULONG DEVAPI SKF_ECCDecryptEx(HCONTAINER hContainer, PECCCIPHERBLOB pCipherText, BYTE *pbPlaintext, ULONG *pulPlaintextLen)
	//功能描述	ECC数据解密。用容器中解密私钥解密数据，解密后的结果存放到pbPlaintext中。
	//参数		hContainer		[IN] 密钥容器句柄。
	//			pCipherText		[IN] 待解密的数据。此参数为ECCCIPHERBLOB密文数据。
	//			pbPlaintext		[OUT] 解密后的明文，如果该参数为NULL，将由pulPlaintextLen返回所需要的内存空间大小。
	//			pulPlaintextLen	[IN OUT] 输入时表示pbPlaintext缓冲区的长度，输出时表示密文结果的长度。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_ECCDecryptEx(HCONTAINER hContainer, PECCCIPHERBLOB pCipherText, BYTE *pbPlaintext, ULONG *pulPlaintextLen);


	// RSA解密
	//函数原型	ULONG DEVAPI SKF_RSAPriKeyOperation(HCONTAINER hContainer, BYTE *pbIn, ULONG ulInLen, BYTE *pbOut, ULONG *pulOutLen, BOOL bSignFlag)
	//参数		hContainer		[IN] 密钥容器句柄。
	//			pbIn			[IN] 输入数据。
	//			ulInLen			[IN] 输入数据长度。
	//			pbOut			[OUT] 输出数据。
	//			pulOutLen		[IN OUT] 输入时表示pbOut缓冲区的长度，输出时表示密文结果的长度。
	//			bSignFlag       [IN] 非0，表示使用签名密钥对；0，表示加密密钥对
	ULONG DEVAPI SKF_RSAPriKeyOperation(HCONTAINER hContainer, BYTE *pbIn, ULONG ulInLen, BYTE *pbOut, ULONG *pulOutLen, BOOL bSignFlag);


	// 获取应用安全状态
	//函数原型	ULONG DEVAPI SKF_GetSecureState (HAPPLICATION hApplication, ULONG *pulSecureState)
	//功能描述	获取应用当前的安全状态。
	//参数		hApplication	[IN] 应用句柄。
	//参数		pulSecureState	[OUT] 应用当前安全状态。
	//返回值	SAR_OK：	成功。
	//其他：	错误码。
	ULONG DEVAPI SKF_GetSecureState(HAPPLICATION hApplication, ULONG *pulSecureState);

	//7.6.20	ECC生成密钥协商参数并输出: 临时密钥对，使用固定值
	ULONG DEVAPI SKF_GenerateAgreementDataWithECCEx(HCONTAINER hContainer, ULONG ulAlgId,ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,BYTE* pbID, ULONG ulIDLen,HANDLE *phAgreementHandle);

	//7.6.21 ECC产生协商数据并计算会话密钥 扩展接口: 使用固定临时密钥对, 返回协商后的密钥
	ULONG DEVAPI SKF_GenerateAgreementDataAndKeyWithECCEx(HANDLE hContainer, ULONG ulAlgId,
		ECCPUBLICKEYBLOB*  pSponsorECCPubKeyBlob, ECCPUBLICKEYBLOB*  pSponsorTempECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
		BYTE* pbID, ULONG ulIDLen, BYTE *pbSponsorID, ULONG ulSponsorIDLen,
		BYTE *pbAgreementKey,
		ULONG *pulAgreementKeyLen);

	//7.6.21 ECC产生协商数据并计算会话密钥 扩展接口: 输入B方临时密钥对, 返回协商后的密钥
	ULONG DEVAPI SKF_GenerateAgreementDataAndKeyWithECCEx2(HANDLE hContainer, ULONG ulAlgId,
		ECCPUBLICKEYBLOB*  pSponsorECCPubKeyBlob, ECCPUBLICKEYBLOB*  pSponsorTempECCPubKeyBlob,
		BYTE*  pbTempECCPair, // 数据格式：PubX(32字节) + PubY(32字节) + Pri(32字节)
		BYTE* pbID, ULONG ulIDLen, BYTE *pbSponsorID, ULONG ulSponsorIDLen,
		BYTE *pbAgreementKey,
		ULONG *pulAgreementKeyLen);

	//7.6.22 ECC计算会话密钥 扩展接口: 返回协商后的密钥
	ULONG DEVAPI SKF_GenerateKeyWithECCEx(HANDLE hAgreementHandle,
		ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
		BYTE* pbID, ULONG ulIDLen, 
		BYTE *pbAgreementKey, ULONG *pulAgreementKeyLen);



	ULONG DEVAPI SKF_ExtGenECCKeyPair(DEVHANDLE hDev, ULONG ulBitsLen, PECCPUBLICKEYBLOB pECCPublicKeyBlob, PECCPRIVATEKEYBLOB pECCPrivateKeyBlob);

	ULONG DEVAPI SKF_ImportECCExchangeKeyPair(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob);
	ULONG DEVAPI SKF_ImportExchangeCertificate(HCONTAINER hContainer, BYTE* pbCert, ULONG ulCertLen);
	ULONG DEVAPI SKF_ExportECCExchangePubKey(HCONTAINER hContainer, PECCPUBLICKEYBLOB pECCPublicKeyBlob);

	ULONG DEVAPI SKF_ImportHMACKey(HAPPLICATION hApplication, BYTE* pbLabel, ULONG ulLabelLen, BYTE* pbID, ULONG ulIDLen, BYTE* pbKey, ULONG ulKeyLen);



	// 生成ECC加密密钥对
	ULONG DEVAPI SKF_GenECCEncryptKeyPair(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pBlob);
	ULONG DEVAPI SKF_ImportECCSignKeyPair(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob);

	ULONG DEVAPI SKF_GenSessionKey(HCONTAINER hContainer, ULONG ulAlgID, HANDLE* phKey);
	ULONG DEVAPI SKF_WrapKey(HCONTAINER hContainer, HANDLE hKey, ECCPUBLICKEYBLOB *pBlob, ECCCIPHERBLOB *pEccCipherBlob);
	ULONG DEVAPI SKF_UnwrapKey(HCONTAINER hContainer, ECCCIPHERBLOB *pEccCipherBlob, ULONG ulAlgID, HANDLE* phKey);


#ifdef __cplusplus
}
#endif

#endif	//__SKFINTERFACE_H
