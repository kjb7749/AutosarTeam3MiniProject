#include "pch.h"
#include "Environment.h"
#include "Player.h"
#include "LogicDavid.h"

using namespace std;


TEST(TestCaseName, TestName) {


}


int main()
{
	Environment env;
	Player pa(&env, 1, "���غ�", 500000);
	Player pb(&env, 2, "�����", 500000);

	LogicDavid logic;

	env.setSubsidy(5000);

	//IPlayerGetter *testgetter = &pa;
	//IPlayerSetter *testsetter = &pa;

	//std::cout<<testgetter->getMoney();
	//testsetter->setMoney(100);
	//std::cout << testgetter->getMoney();

	pa.setLogic(logic);
	pb.setLogic(logic);

	env.appendUser(&pa);
	env.appendUser(&pb);

	//�ʱ� cityowner id���� ��ġ�� �ʴ� ������ �÷��̾� id ������ �����ؾ� �Ѵ� �ѹ���

	while (env.playGame());
	IPlayerGetter *winner = env.getWinner();
	if (winner != NULL)
	{
		//���� ���
		cout <<"���ڴ� " << winner->getName() <<" �Դϴ�! �����մϴ�!!!  ¦¦¦¦" << endl;
	}
}