//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<vector>
//using namespace std;
//
//
//int namebeauty(string strname)
//{
//	int len = strname.size();
//	int ss[26] = { 0 };
//	int beauty = 0;
//	for (int i = 0; i < len; ++i)
//	{
//		++ss[tolower(strname[i]) - 'a'];
//	}
//	sort(ss, ss + 26);
//	for (int j = 25; j >25 - len; --j)
//	{
//		beauty += ss[j] * (26 - (25 - j));
//	}
//	return beauty;
//}
//int main()
//{
//
//	int n;
//	string name;
//	vector<string> strname;
//	cin >> n;
//	for (int k = 0; k < n; ++k)
//	{
//		cin >> name;
//		strname.push_back(name);
//	}
//	for (int k = 0; k < n; ++k)
//		cout << namebeauty(strname[k])<<endl;
//	//cout<<namebeauty(strname[n-1]);
//	return 0;
//}