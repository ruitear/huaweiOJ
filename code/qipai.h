#include"title.h"

typedef enum{
	CARD_TYPE_SPADE,//黑桃
	CARD_TYPE_HEART,//红桃

	CARD_TYPE_CLUB,//梅花
	CARD_TYPE_DIAMOND//方块
}CardType;
CardType typeArr[4] = { CARD_TYPE_SPADE, CARD_TYPE_HEART, CARD_TYPE_CLUB, CARD_TYPE_DIAMOND };
typedef enum{
	POYAL_FLUSH,//皇家同花顺
	STRAIGHT_FLUSH,//同花顺
	FOUR_OF_A_KIND,//四条
	FULL_HOUSE,//葫芦
	FLUSH,//同花
	STRAIGHT,//顺子
	THREE_OF_A_KIND,//三条
	TWO_PAIR,//两对
	ONE_PAIR,//一对
	HIGH_CARD//高牌
}CardsCombinationType;

typedef struct{
	CardType Type;
	unsigned int point;
}CardInfo;

class libStype
{
private:
	int pointSum;
	int pointMax;
	vector<CardInfo>vecType;
public:
	libStype(){ pointSum = 0; pointMax = 0; }
	libStype(int ssize, int pmax) :pointSum(ssize), pointMax(pmax){}
	void setMax()
	{
		pointMax = (pointMax<pointSum) ? pointSum : pointMax ;
	}
	void setPoint(int point)
	{
		pointSum += point;
	}
	int getMax()
	{
		return pointMax;
	}
	void clear()
	{
		pointSum = 0;
		pointMax = 0;
		vecType.clear();
	}
};

void fillTypeAndInt(map<CardType, vector<CardInfo>>& typeNum, map<int, vector<CardInfo>>& typeInt, CardInfo InCards[7])
{//typeNum保存一花色分别保存的情况，typeInt保存一点数分别保存的类型，
	map<CardType, vector<CardInfo>>::iterator ittOfTypeNum;
	map<int, vector<CardInfo>>::iterator ittOfTypeInt;
	for (unsigned int i = 0; i < 7; i++)
	{

		ittOfTypeNum = typeNum.find(InCards[i].Type);
		if (ittOfTypeNum==typeNum.end())
		{
			typeNum[InCards[i].Type].push_back(InCards[i]);
		}
		else
		{
			ittOfTypeNum->second.push_back(InCards[i]);
		}
		ittOfTypeInt = typeInt.find(InCards[i].point);
		if (ittOfTypeInt == typeInt.end())
		{
			typeInt[InCards[i].point].push_back(InCards[i]);
		}
		else
		{
			ittOfTypeInt->second.push_back(InCards[i]);
		}
	}
}

libStype globalType;
//看是否为同花，为同花的话就讲结果保存在result，isOK为TRUE
int isSameType(map<CardType, vector<CardInfo>>& typeNum)
{
	map<CardType, vector<CardInfo>>::iterator itt=typeNum.begin();
	int resSum = 0;
	while (itt!=typeNum.end())
	{
		if (itt->second.size()>=5)
		{
			for (size_t i = 0; i < itt->second.size(); i++)
			{
				globalType.setPoint(itt->second[i].point);
			}
			globalType.setMax();
			return itt->first;
		}
		itt++;
	}
	return -1;
}
int isFlush(map<int, vector<CardInfo>>& reault)
{
	map<int, vector<CardInfo>>::iterator ittb, ittn;
	
	if (reault.size()<5)
	{
		return -1;//表示不是顺子
	}
	ittb = reault.begin();
	int flag = 0;
	if (reault.size()==5)
	{
		ittn = reault.end()--;
		flag = ittb->first - ittn->first;
		if (flag == 5)
		{
			int sumTemp = (ittb->first + ittn->first) * 5 / 2;
			globalType.setPoint(sumTemp);
			globalType.setMax();
			return 1;
		}
		//return  -1;
	}
	ittb = reault.begin();
	if (reault.size() == 6)
	{
		ittn = reault.end();
		ittb++;//连续5个为一组查看是不是顺子
		for (size_t i = 0; i < 2; i++,ittb--)
		{
			ittn--;
			flag = ittb->first - ittn->first;
			if (flag==5)
			{
				int sumTemp = (ittb->first + ittn->first) * 5 / 2;
				globalType.setPoint(sumTemp);
				globalType.setMax();
				return 1;//flag==1,表示是顺子
			}
		}
		//return -1;//表示不是顺子
	}
	ittb = reault.begin();
	if (reault.size() == 7)
	{
		ittn = reault.end();
		ittb++; ittb++;//连续2个++将位置偏移到第三个地方，因为size=7 这里就有3组五个的连续可能组合
		for (size_t i = 0; i < 3; i++, ittb--)
		{
			ittn--;
			flag = ittb->first - ittn->first;//首先让第三个跟第七个之间的5个数比较，看是不是连续的顺子
			if (flag == 5)
			{
				int sumTemp = (ittb->first + ittn->first) * 5 / 2;
				globalType.setPoint(sumTemp);
				globalType.setMax();
				return 1;//flag==1,表示是顺子
			}
		}
		//return -1;//表示不是顺子
	}
	return -1;
}
int isPOYAL_FLUSH(vector<CardInfo>& typeVec)
{
	set<int> newSet;
	for (size_t i = 0; i < typeVec.size(); i++)
	{
		newSet.insert(typeVec[i].point);
	}
	set<int>::iterator itt;
	itt = newSet.begin();
	if (newSet.size() == 5)
	{
		if (*itt==10)
		{
			int sumTemp = (10 + 13) * 4 / 2+1;
			globalType.setPoint(sumTemp);
			globalType.setMax();
			return 1;
		}
		/*else
		{
			return -1;
		}*/
	}
	itt++;
	if (newSet.size() == 6)
	{
		if (*itt == 10)
		{
			int sumTemp = (10 + 13) * 4 / 2 + 1;
			globalType.setPoint(sumTemp);
			globalType.setMax();
			return 1;
		}
		/*else
		{
			return -1;
		}*/
	}
	itt++;
	if (newSet.size() == 7)
	{
		if (*itt == 10)
		{
			int sumTemp = (10 + 13) * 4 / 2 + 1;
			globalType.setPoint(sumTemp);
			globalType.setMax();
			return 1;
		}
		/*else
		{
			return -1;
		}*/
	}
	return -1;
}
CardInfo po1 = { CARD_TYPE_SPADE, 13 };
CardInfo po2 = { CARD_TYPE_SPADE, 12 };
CardInfo po3 = { CARD_TYPE_SPADE, 11 };
CardInfo po4 = { CARD_TYPE_SPADE, 10 };
CardInfo po5 = { CARD_TYPE_SPADE, 9 };
CardInfo po6 = { CARD_TYPE_CLUB, 8 };
CardInfo po7 = { CARD_TYPE_CLUB, 7 };

CardInfo InCards[7] = { po1, po2, po3 ,po4 ,po5, po6 ,po7};

CardsCombinationType getMaxType(map<CardType, vector<CardInfo>>& typeNum,map<int, vector<CardInfo>>& typeInt)
{

	int res = isSameType(typeNum);
	if (res!=-1)
	{//c此时是同花
		int flag=isFlush(typeInt);
		if (flag==1)
		{//是顺子又是同花，看是皇家同花顺还是，普通的同花顺
			map<CardType, vector<CardInfo>>::iterator itt = typeNum.find(typeArr[res]);//查找到同花的花色
			int isPolal=isPOYAL_FLUSH(itt->second);
			if (isPolal==1)
			{
				return POYAL_FLUSH;//是顺子又是同花,且为同花顺
			}
			else
			{
				return STRAIGHT_FLUSH;//是顺子又是同花
			}
		}
		else//是同花但不是顺子，此时看是否有比同花大的可能出现：四条和葫芦
		{//由于是顺子就不可能是四条，也不可能是葫芦，所以只能是普通的同花
			return FLUSH;
		}
	}
	if (res==-1)
	{//此时不是同花
		int flag = isFlush(typeInt);
		if (flag == 1)
		{//不是同花是顺子，那就是顺子了
			return FLUSH;
		}
		else
		{//不是顺子，这个时候就有很多情况了
			if (typeInt.size()==7)
			{
				return HIGH_CARD;
			}
			if (typeInt.size() == 6)
			{
				return ONE_PAIR;
			}
			if (typeInt.size() == 5)
			{
				map<int, vector<CardInfo>>::iterator ittb;
				ittb = typeInt.begin();
				while (ittb!=typeInt.end())
				{
					if (ittb->second.size == 3)
					{
						return THREE_OF_A_KIND;
					}
					ittb++;
				}
				return TWO_PAIR;
			}
			if (typeInt.size() < 5)
			{
				map<int, vector<CardInfo>>::iterator ittb;
				ittb = typeInt.begin();
				int has2=0, has3 = 0, has4 = 0;
				while (ittb != typeInt.end())
				{
					if (ittb->second.size == 2)
					{
						has2 += 1;
					}
					if (ittb->second.size == 3)
					{
						has3 += 1;
					}
					if (ittb->second.size == 4)
					{
						has4 += 1;
					}
					ittb++;
				}
				if (has4>=1)
				{
					return 	FOUR_OF_A_KIND;
				}
				else if (has3 >= 1&&has2>=1)
				{
					return 	FULL_HOUSE;
				}
				else if (has3 >= 1 && has2 < 1)
				{
					return THREE_OF_A_KIND;
				}
				else if (has3 < 1 && has2 > 1)
				{
					return TWO_PAIR;
				}
			}
		}
	}
}
void GetMaxCards(CardInfo InCards[7], unsigned int* TotalPoints, CardsCombinationType* CardsCombType)//,
{
	if (TotalPoints==NULL)
	{
		return;
	}
	map<CardType,vector<CardInfo>> typeNum;
	map<int, vector<CardInfo>> typeInt;
	fillTypeAndInt(typeNum, typeInt, InCards);
	*CardsCombType=getMaxType(typeNum, typeInt);
	*TotalPoints = globalType.getMax();
	globalType.clear();
}