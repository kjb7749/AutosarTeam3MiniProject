#include "pch.h"
#include "Environment.h"
#include "Player.h"

using namespace std;


TEST(TestCaseName, TestName) {


}


int main()
{
	Environment env;
	PlayerA pa(&env, 1, "���غ�", 500000);
	PlayerA pb(&env, 2, "�����", 500000);

	env.appendUser(&pa);
	env.appendUser(&pb);

	//�ʱ� cityowner id���� ��ġ�� �ʴ� ������ �÷��̾� id ������ �����ؾ� �Ѵ� �ѹ���

	while (env.playGame());
	Player *winner = env.getWinner();
	if (winner != NULL)
	{
		//���� ���
		cout << winner->getName() << endl;
	}
}