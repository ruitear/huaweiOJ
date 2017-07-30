#ifndef _OJ_H
#define _OJ_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#endif
using namespace std;

//ͳ���ַ������ظ��ַ������ɶ�������
//���ͳ���ַ��ĸ�����ͬ������ASCII����С�����������������������ַ�����Щ�ַ����ý���ͳ�ơ�
//ʵ��һ���ӿڣ�ʵ�֣�����һ���ַ��������ַ��и���Ӣ���ַ����֣��ո����ͳ�����򣨿ɷ������ã�
//����ͳ�Ƹ����жൽ�����ͳ�ƽ�������ͳ�Ƶĸ�����ͬ������ASCII���С��С�����������
//���Ŀǰͳ�ƽ��������ͳ��
struct charStruct
{
	int ch;//�洢��ǰ�ַ���ASCII��
	int count;//��¼��ǰ�ַ����ֵĴ���
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
//�ж�������̨�������IP��ַ�Ƿ�����ͬһ������
//���������������ж�������̨�������IP��ַ�Ƿ�����ͬһ������ĸ��ݡ�
//��Ϊ�򵥵���������̨��������Ե�IP��ַ�������������AND�����
//����ó��Ľ������ͬ�ģ���˵������̨������Ǵ���ͬһ���������ϵģ�
//���Խ���ֱ�ӵ�ͨѶ������ô�򵥡�
/*
����: �ж���̨�����IP��ַ��ͬһ�����硣
ԭ�ͣ�
int IsSameSubNetwork(char * pcIp1, char * pcIp2, char * pcSubNetworkMask);

���������
char * pcIP1: �����1��IP��ַ����ʽ����192.168.0.254����
char * pcIP2: �����2��IP��ַ����ʽ����192.168.0.1����
char * pcSubNetworkMask: �������룬��ʽ����255.255.255.0����

����ֵ��
0��IP1��IP2������ͬһ�����磻
1��IP1��IP2����ͬһ�����磻
*/
int str2int(string str)
{
	int temp = 0;//����str2int�����շ���ֵ��
	
	int tenBit = 1;//strû��Ϊ����Ӧ������Ӧ������ֵ�ĳ���ʼֵ
	int size = str.size();//
	int i = 0;//ѭ����ʾλ
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
		int strTemp=str2int(sIp.substr(0, index));//�õ�"."֮ǰ�������ַ���
		ipFlag.push_back(strTemp);
		if (index + 1>sIp.size())
		{
			return false;
		}
		sIp = sIp.substr(index + 1, sIp.size() - index - 1);//gengxin�ַ���
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
//��������
//��Ŀ������ʵ������һ����ڵ���0�����������ݴ�С�����˳�������������������������ʱ��ֻ�������������С��������������
//����:
//һ����ڵ���0�������������ǷǷ����룬��������֮���Զ���(��, ��)�ָ�, �����ַ������ܳ���С�ڵ���100���ֽڡ�
//��� :
//������ֵ����������֮���Կո�ָ���
//�������� : 1, 4, 3, 110, 2, 90, 7
// ������� : 1 4 7 90 110
vector<int> intSort(char* intstr)
{
	vector<int> result;
	if (intstr==NULL)
	{
		return result;
	}
	string sintStr = intstr;
	int num = 0;
	for (int i = 0; i <= sintStr.size(); ++i) //�ָ��ַ���
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
	sort(result.begin(), result.end());//sortĬ�������������е�
	int indexNum = 0;
	int current = 0;//��¼��ǰ���������ֵ�λ��
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
			if (current>=2)//ע��i�����һ�����Ͳ������һ�����ĵݼ��仯
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