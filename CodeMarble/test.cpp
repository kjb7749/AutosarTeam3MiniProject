#include "pch.h"
#include "Environment.h"
#include "Player.h"
#include "LogicDavid.h"

using namespace std;


TEST(TestCaseName, TestName) {


}


int main()
{
	srand(time(NULL));


	Environment env;
	Player pa(&env, 1, "���غ�", 200000);
	Player pb(&env, 2, "���ä", 200000);
	Player pc(&env, 3, "������", 200000);

	LogicDavid logic;

	env.setSubsidy(5000);

	pa.setLogic(logic);
	pb.setLogic(logic);
	pc.setLogic(logic);

	env.appendUser(&pa);
	env.appendUser(&pb);
	env.appendUser(&pc);

	//�ʱ� cityowner id���� ��ġ�� �ʴ� ������ �÷��̾� id ������ �����ؾ� �Ѵ� �ѹ���

	while (env.playGame());
	IPlayerGetter *winner = env.getWinner();
	if (winner != NULL)
	{
		//���� ���
		cout <<"���ڴ� " << winner->getName() <<" �Դϴ�! �����մϴ�!!!  ¦¦¦¦" << endl;
	}

	return 0;
}