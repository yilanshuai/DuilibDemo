#pragma once
/****************************************************************************
*   作者:  符星
*   日期:  2013-4-14
*   目的:  读取配置文件的信息，以string的形式返回
*   要求:  配置文件的格式，以#作为行注释，配置的形式是key = value，中间可有空格，也可没有空格
*****************************************************************************/
#include <Shlwapi.h> 
#include <string>
#include <unordered_map>
#include<vector>
#define COMMENT_CHAR '#'//注释符  
using namespace std;

class operate_config
{
private:
	wifstream *infile;
	wstring filename;

public:
	operate_config(void);
	//参数filename，配置文件的名字  
	operate_config(const wstring & filename);

	~operate_config();
	//参数name，配置项的名字  
	//返回值，对应配置项name的value值  
	unordered_map <wstring, wstring> getValue(const wstring & name);

	vector<std::wstring> split(wstring str, wstring pattern);

	/*******************url匹配begin**********************************/
	int matchstar(int c, wchar_t *regexp, wchar_t *text);
	int matchhere(wchar_t *regexp, wchar_t *text);
	//URL匹配算法，用原URL（src）去匹配目的URL（dst）.[~] 匹配任意的单个字符;[^] 匹配输入字符串的开头;[$] 匹配输入字符串的结尾; [*] 匹配前一个字符的零个或者多个出现
	bool match(const wchar_t *src, const wchar_t *dst);
	/*******************url匹配end**********************************/
	std::string utf8_encode(const std::wstring &wstr);
	static std::wstring utf8_decode(const std::string &str);
	static int  operate_config::callback(void *para, int n_column, char **column_value, char **column_name);
	//参数name，配置项的名字  
	//返回值，对应配置项name的value值  
	unordered_map <wstring, wstring> operate_config::getDBValue(const wstring & name);
	//删除字符串制定标记
	int operate_config::deleteAllMark(string &s, const string &mark, size_t len);

	string* byteToHexStr(BYTE byte_arr[], int arr_len);

	bool saveDataToFile(wstring path, wstring data, int mode=0);
};