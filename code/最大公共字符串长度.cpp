#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
最大公共字符串长度
int getCommonStrLength(char * pFirstStr, char * pSecondStr)
{
	if (pFirstStr == NULL || pSecondStr == NULL)
		return 0;
	int len1 = strlen(pFirstStr);
	int len2 = strlen(pSecondStr);
	int tempcom = 1;
	int common = 0;
	int minl =min(len1,len2);
	for (int i = 0; i < len1; ++i)
	{
		for (int j = 0; j < len2; ++j)
		{
			if (tolower(pSecondStr[j]) == tolower(pFirstStr[i]))
			{
				for (int k = j + 1; (i + k - j) < minl; ++k)
				{			
					if (tolower(pSecondStr[k]) == tolower(pFirstStr[i + k - j])) ++tempcom;
					else break;
				}
				if (tempcom>common) { common = tempcom; }
				tempcom = 1;
			}
		}
	}
	return common;
}

int main()
{
	
	//公共字符串的长度
	char str1[100], str2[100];
	cin >> str1 >> str2;
	int length = getCommonStrLength(str1, str2);
	cout << length;
	return 0;
}