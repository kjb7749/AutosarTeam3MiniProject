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
	Player pa(&env, 1, "윤준병", 200000);
	Player pb(&env, 2, "김민채", 200000);
	Player pc(&env, 3, "김형진", 200000);

	LogicDavid logic;

	env.setSubsidy(5000);

	pa.setLogic(logic);
	pb.setLogic(logic);
	pc.setLogic(logic);

	env.appendUser(&pa);
	env.appendUser(&pb);
	env.appendUser(&pc);

	//초기 cityowner id값은 겹치지 않는 랜덤한 플레이어 id 값으로 설정해야 한다 한번만

	while (env.playGame());
	IPlayerGetter *winner = env.getWinner();
	if (winner != NULL)
	{
		//승자 출력
		cout <<"승자는 " << winner->getName() <<" 입니다! 축하합니다!!!  짝짝짝짝" << endl;
	}

	return 0;
}