#ifndef _OJ_H
#define _OJ_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#endif
using namespace std;

//统计字符串中重复字符，按由多少排序。
//如果统计字符的个数相同，则按照ASCII码由小到大排序输出。如果有其他字符则这些字符不用进行统计。
//实现一个接口，实现：输入一个字符串，对字符中各个英文字符数字，空格进行统计排序（可反复调用）
//按照统计个数有多到少输出统计结果。如果统计的个数相同，则按照ASCII码大小有小到到排序输出
//清空目前统计结果，重新统计
struct charStruct
{
	int ch;//存储当前字符的ASCII码
	int count;//记录当前字符出现的次数
};
bool comChar(charStruct chars1, charStruct chars2)
{
	/*if (chars1.count == chars2.count&&chars1.ch<chars2.ch)
	{
		return true;
	}*/
	return chars1.count>chars2.count;
}
string countChar(char* str)
{
	int len=strlen(str);
	charStruct charHash[256];
	for (int i = 0; i < 256; i++)
	{
		charHash[i].ch= i;
		charHash[i].count = 0;
	}
	while (*str!='\0')
	{
		if (*str == ' ' || isalpha(*str) || isalnum(*str))
		{
			charHash[*str].count++;
		}
		str++;
	}
	sort(charHash, charHash + 256 - 1, comChar);
	string result;
	for (int i = 0; i < 256; i++)
	{
		if (charHash[i].count == 0)
		{
			break;
		}
		result += charHash[i].ch;
	}
	return result;
}
//判断任意两台计算机的IP地址是否属于同一子网络
//子网掩码是用来判断任意两台计算机的IP地址是否属于同一子网络的根据。
//最为简单的理解就是两台计算机各自的IP地址与子网掩码进行AND运算后，
//如果得出的结果是相同的，则说明这两台计算机是处于同一个子网络上的，
//可以进行直接的通讯。就这么简单。
/*
功能: 判断两台计算机IP地址是同一子网络。
原型：
int IsSameSubNetwork(char * pcIp1, char * pcIp2, char * pcSubNetworkMask);

输入参数：
char * pcIP1: 计算机1的IP地址，格式：“192.168.0.254”；
char * pcIP2: 计算机2的IP地址，格式：“192.168.0.1”；
char * pcSubNetworkMask: 子网掩码，格式：“255.255.255.0”；

返回值：
0：IP1与IP2不属于同一子网络；
1：IP1与IP2属于同一子网络；
*/
int str2int(string str)
{
	int temp = 0;//保存str2int的最终返回值。
	
	int tenBit = 1;//str没以为所对应的数相应的整数值的厨初始值
	int size = str.size();//
	int i = 0;//循环表示位
	while (i<size)
	{
		int bittemp = size - i - 1;
		while (bittemp--)
		{
			tenBit *= 10;
		}
		temp += tenBit*(str[i] - '0');
		tenBit = 1;
		i++;
	}
	return temp;
}
bool checkIp(char* ip,vector<int>&ipFlag)
{
	if (ip == NULL)
	{
		return false;
	}
	string sIp = ip;
	int index = sIp.find(".", 0);
	int pointCount = 0;
	while (index != string::npos)
	{
		int strTemp=str2int(sIp.substr(0, index));//得到"."之前的数字字符段
		ipFlag.push_back(strTemp);
		if (index + 1>sIp.size())
		{
			return false;
		}
		sIp = sIp.substr(index + 1, sIp.size() - index - 1);//gengxin字符串
		index = sIp.find(".", 0);
		pointCount++;
	}
	int strTemp = str2int(sIp);
	ipFlag.push_back(strTemp);
	int i = 0;
	if (ipFlag.size() != 4 || pointCount!=3)
	{
		return false;
	}
	while (i<ipFlag.size())
	{
		if (ipFlag[i]>255 || ipFlag[i]<0)
		{
			return false;
		}
		++i;
	}
	return true;
}
int IsSameSubNetwork(char * pcIp1, char * pcIp2, char * pcSubNetworkMask)
{
	vector<int> sip1;
	vector<int> sip2;
	vector<int> smask;
	int flag = 0;
	if (checkIp(pcIp1, sip1) && checkIp(pcIp2, sip2) && checkIp(pcSubNetworkMask, smask))
	{
		flag = 1;
		for (size_t i = 0; i < sip1.size(); i++)
		{
			int tempip1 = sip1[i] & smask[i];
			int tempip2 = sip2[i] & smask[i];
			if (tempip1 != tempip2)
			{
				flag = 0;
				break;
			}
		}
	}
	return flag;
}
//整数排序
//题目描述：实现输入一组大于等于0的整数，根据从小到大的顺序排序后输出，排序后有连续数时，只输出连续数中最小和最大的两个数。
//输入:
//一组大于等于0的整数，不考虑非法输入，各个整数之间以逗号(“, ”)分隔, 输入字符串的总长度小于等于100个字节。
//输出 :
//排序后的值，各个整数之间以空格分隔。
//样例输入 : 1, 4, 3, 110, 2, 90, 7
// 样例输出 : 1 4 7 90 110
vector<int> intSort(char* intstr)
{
	vector<int> result;
	if (intstr==NULL)
	{
		return result;
	}
	string sintStr = intstr;
	int num = 0;
	for (int i = 0; i <= sintStr.size(); ++i) //分割字符串
	{
		if (i == sintStr.size() || sintStr[i] == ',')
		{
			result.push_back(num);
			num = 0;
		}
		else if (sintStr[i] >= '0' && sintStr[i] <= '9')
		{
			num = num * 10 + sintStr[i] - '0';
		}
	}
	sort(result.begin(), result.end());//sort默认是以升序排列的
	int indexNum = 0;
	int current = 0;//记录当前连续的数字的位移
	for (int i = 0; i < result.size()-1; i++)
	{		
		
		if (result[i] == result[i + 1]-1)
		{
			current++;
			if (i+1 == result.size() - 1 && current>=2)
			{
				int k = 0;
				while (k< current-1)
				{
					result[i - k] = -1;
					k++;
				}
			}

		}
		else
		{
			if (current>=2)//注意i到最后一个数和不是最后一个数的递减变化
			{
				int k = 1;
				while (k < current)
				{
					result[i - k] = -1;
					k++;
				}
			}
			current = 0;
		}
	}
	for (vector<int>::iterator Iter = result.begin(); Iter != result.end(); Iter++)
	{
		if (*Iter == -1)
		{
			result.erase(Iter);
			Iter = result.begin();
		}
	}
	return result;
}