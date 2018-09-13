#include "pch.h"
#include "Environment.h"
#include "Player.h"

using namespace std;


TEST(TestCaseName, TestName) {


}


int main()
{
	Environment env;
	PlayerA pa(&env, 1, "윤준병", 500000);
	PlayerA pb(&env, 2, "오토사", 500000);

	env.appendUser(&pa);
	env.appendUser(&pb);

	//초기 cityowner id값은 겹치지 않는 랜덤한 플레이어 id 값으로 설정해야 한다 한번만

	while (env.playGame());
	Player *winner = env.getWinner();
	if (winner != NULL)
	{
		//승자 출력
		cout << winner->getName() << endl;
	}
}