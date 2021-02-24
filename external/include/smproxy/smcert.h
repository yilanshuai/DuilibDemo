#ifndef __SMCERT_H
#define __SMCERT_H

#define STDCALL __stdcall

#if 1		//证书信息项定义
//主项定义，iNameID
#define CERT_VERSION				1		//Version					证书版本
#define CERT_SERIALNUMBER			2		//SerialNumber				证书序列号
#define CERT_SIGNATUREALGORITHM		3		//SignatureAlgorithm		签名算法
#define CERT_NOTBEFORE				4		//NotBefore					有效起始日期
#define CERT_NOTAFTER				5		//NotAfter					有效终止日期
#define CERT_SUBJECTPUBLICKEYINFO	6		//SubjectPublicKeyInfo		公钥值
#define CERT_ISSUER_DN				7		//Issuer					颁发者
#define CERT_SUBJECT_DN				8		//Subject					主题
#define CERT_KEYUSAGE				9		//Keyusage					密钥用法

#define CERT_PURPOSE				10		//certpurpose				证书目的

//子项定义，iSubNameID
#define NID_COMMONNAME				13		//"commonName""CN"
#define NID_COUNTRYNAME				14		//"countryName" "C"
#define NID_LOCALITYNAME			15		//"localityName" "L"
#define NID_STATEORPROVINCENAME		16		//"stateOrProvinceName" "ST"
#define NID_ORGANIZATIONNAME		17		//"organizationName" "O"
#define NID_ORGANIZATIONALUNITNAME	18		//"organizationalUnitName" "OU"
#define NID_PKCS9_EMAILADDRESS		48		//"emailAddress" "E"

#endif

//---------------------------------------------------------------------------------------
//错误码定义
#define	WT_OK							0x00000000		//成功

#define	WT_ERR							0x0E000000		//失败
#define	WT_ERR_UNKNOWNERR				(WT_ERR+1)		//未知异常错误
#define	WT_ERR_INVALIDPARAM				(WT_ERR+2)		//无效的参数

#define	WT_ERR_FILE						(WT_ERR+3)		//文件操作错误
#define	WT_ERR_READFILE					(WT_ERR+4)		//读文件错误
#define	WT_ERR_WRITEFILE				(WT_ERR+5)		//写文件错误

#define	WT_ERR_MEMORY					(WT_ERR+6)		//内存错误
#define	WT_ERR_BUFFER_TOO_SMALL			(WT_ERR+7)		//缓冲区不足
//---------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//功能：设置证书,支持PEM以及DER格式
//参数：pbMyCert：	证书内容
//		ulCertLen：	证书内容长度
int STDCALL WT_SetMyCert(unsigned char *pbMyCert, unsigned long ulCertLen);

//功能：获取证书信息
//参数：iNameID：	证书信息项，见上宏定义CERT_XXXX
//	    iSubNameID：证书信息子项，当iNameID=CERT_ISSUER_DN或CERT_SUBJECT_DN时本参数有效, 否则默认为-1, 
//					本参数有效时，可取值见上宏定义NID_XXX。
//		pszGB：		返回字符串，  当iNameID=CERT_ISSUER_DN或CERT_SUBJECT_DN时，字符串以"/"作为分隔符。
//		piLen：		返回字符串长度，当值pszGB为NULL时，本参数可以返回需要的缓存长度。
//备注：必须预先调用WT_SetMyCert
int STDCALL WT_GetCertInfo(int iNameID, int iSubNameID, char *pszGB, int* piLen);

//功能：清除以前设置的证书
int STDCALL WT_ClearCert();

#ifdef __cplusplus
}
#endif

#endif //__SMCERT_H