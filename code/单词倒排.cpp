#include <iostream>
#include<string>
#include<stack>
using namespace std;
/*题目描述
对字符串中的所有单词进行倒排。
说明：
1、每个单词是以26个大写或小写英文字母构成；
2、非构成单词的字符均视为单词间隔符；
3、要求倒排后的单词间隔符以一个空格表示；如果原字符串中相邻单词间有多个间隔符时，倒排转换后也只允许出现一个空格间隔符；
4、每个单词最长20个字母；
样例输入
I am a student
样例输入
student a am I*/
string swapStr(string str, size_t begin, size_t end)
{
	if (str.empty())
	{
		return str;
	}
	while (begin<end)
	{
		char temp = str[begin];
		str[begin] = str[end];
		str[end] = temp;
		begin++; end--;
	}
	return str;
}
string resString(string str)
{
	string result;
	if (str.empty())
	{
		return result;
	}
	size_t size = str.size();
	str = swapStr(str, 0, size - 1);
	size_t index = 0, begin = 0, end = 0;;
	for (size_t i = 0; i < size - 1; i++)
	{
		if (str[i] != ' ')
		{

			index++;
			end = index;
		}
		else if (str[index] == ' ' || index == size)
		{
			str = swapStr(str, begin, end - 1);
			index++;
			begin = index;
		}
	}
	return str;
}
stack<string> sepString(string str)
{
	stack<string> result;
	if (str.empty())
	{
		return result;
	}
	size_t len = str.size();
	size_t begin = 0, end = 0, index = 0;
	string temp;
	for (size_t i = 0; i < len; i++)
	{
		if ((str[i] >= 'a'&&str[i] <= 'z') || (str[i] >= 'A'&&str[i] <= 'Z'))
		{
			index++;
			end = index;
			if (end == len)
			{
				temp = str.substr(begin, end - begin);
				if (!temp.empty())
				{
					result.push(temp);
				}
			}
		}
		else
		{

			if (begin < end)
			{
				temp = str.substr(begin, end - begin);
				if (!temp.empty())
				{
					result.push(temp);
				}
			}
			index++;
			begin = index;
		}
	}
	return result;
}
string strSSS(stack<string> str)
{
	string result;
	if (str.empty())
	{
		return result;
	}
	size_t lenn = str.size();
	for (size_t i = 0; i <lenn; i++)
	{
		if (i == lenn - 1)
		{
			result += str.top();
			str.pop();
			break;
		}
		result += str.top() + " ";
		str.pop();
	}
	return result;
}
//
int main()
{
	string str;
	getline(cin, str);
	stack<string> temp = sepString(str);
	string strtt = strSSS(temp);
	cout << strtt << endl;
	return 0;
}