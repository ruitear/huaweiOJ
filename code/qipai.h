#include"title.h"

typedef enum{
	CARD_TYPE_SPADE,//����
	CARD_TYPE_HEART,//����

	CARD_TYPE_CLUB,//÷��
	CARD_TYPE_DIAMOND//����
}CardType;
CardType typeArr[4] = { CARD_TYPE_SPADE, CARD_TYPE_HEART, CARD_TYPE_CLUB, CARD_TYPE_DIAMOND };
typedef enum{
	POYAL_FLUSH,//�ʼ�ͬ��˳
	STRAIGHT_FLUSH,//ͬ��˳
	FOUR_OF_A_KIND,//����
	FULL_HOUSE,//��«
	FLUSH,//ͬ��
	STRAIGHT,//˳��
	THREE_OF_A_KIND,//����
	TWO_PAIR,//����
	ONE_PAIR,//һ��
	HIGH_CARD//����
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
{//typeNum����һ��ɫ�ֱ𱣴�������typeInt����һ�����ֱ𱣴�����ͣ�
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
//���Ƿ�Ϊͬ����Ϊͬ���Ļ��ͽ����������result��isOKΪTRUE
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
		return -1;//��ʾ����˳��
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
		ittb++;//����5��Ϊһ��鿴�ǲ���˳��
		for (size_t i = 0; i < 2; i++,ittb--)
		{
			ittn--;
			flag = ittb->first - ittn->first;
			if (flag==5)
			{
				int sumTemp = (ittb->first + ittn->first) * 5 / 2;
				globalType.setPoint(sumTemp);
				globalType.setMax();
				return 1;//flag==1,��ʾ��˳��
			}
		}
		//return -1;//��ʾ����˳��
	}
	ittb = reault.begin();
	if (reault.size() == 7)
	{
		ittn = reault.end();
		ittb++; ittb++;//����2��++��λ��ƫ�Ƶ��������ط�����Ϊsize=7 �������3������������������
		for (size_t i = 0; i < 3; i++, ittb--)
		{
			ittn--;
			flag = ittb->first - ittn->first;//�����õ����������߸�֮���5�����Ƚϣ����ǲ���������˳��
			if (flag == 5)
			{
				int sumTemp = (ittb->first + ittn->first) * 5 / 2;
				globalType.setPoint(sumTemp);
				globalType.setMax();
				return 1;//flag==1,��ʾ��˳��
			}
		}
		//return -1;//��ʾ����˳��
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
	{//c��ʱ��ͬ��
		int flag=isFlush(typeInt);
		if (flag==1)
		{//��˳������ͬ�������ǻʼ�ͬ��˳���ǣ���ͨ��ͬ��˳
			map<CardType, vector<CardInfo>>::iterator itt = typeNum.find(typeArr[res]);//���ҵ�ͬ���Ļ�ɫ
			int isPolal=isPOYAL_FLUSH(itt->second);
			if (isPolal==1)
			{
				return POYAL_FLUSH;//��˳������ͬ��,��Ϊͬ��˳
			}
			else
			{
				return STRAIGHT_FLUSH;//��˳������ͬ��
			}
		}
		else//��ͬ��������˳�ӣ���ʱ���Ƿ��б�ͬ����Ŀ��ܳ��֣������ͺ�«
		{//������˳�ӾͲ�������������Ҳ�������Ǻ�«������ֻ������ͨ��ͬ��
			return FLUSH;
		}
	}
	if (res==-1)
	{//��ʱ����ͬ��
		int flag = isFlush(typeInt);
		if (flag == 1)
		{//����ͬ����˳�ӣ��Ǿ���˳����
			return FLUSH;
		}
		else
		{//����˳�ӣ����ʱ����кܶ������
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