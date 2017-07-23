unsigned int getLastLength(string& str)
{
	unsigned int countt = 0;
	/*if (str.empty())
		return countt;*/
	int len = str.size();
	for ( int i = len - 1; i >= 0; --i)
	{
		if (i >0 && str[i] == ' '&&countt==0) continue;
		if (str[i] != ' ')countt++;
		else break;	
	}
	return countt;
}
int main()
{
	//最后一个字符串的长度
	string str;
	getline(cin, str);
	unsigned int length = getLastLength(str);
	cout << length;
	return 0;
}