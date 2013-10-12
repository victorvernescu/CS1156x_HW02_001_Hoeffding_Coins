#include <random>
#include <vector>
#include <functional> 

using namespace std;

//float TossCoin(const int n, function <int()> coinToss)
//{
//	float prob = 0.0;
//	for (int i = 0; i < n; i++)
//	{
//		prob += coinToss();
//	}
//
//	return prob / n;
//}

int main(int argc, char* argv[])
{
	const int NO_COINS = 1000;
	const int NO_TOSSES = 10;
	const int NO_RUNS = 100000;
	vector<float> coinProb;
	float v_1, v_min, v_rand;

	default_random_engine generator;
	uniform_int_distribution<int> faceDistribution(0, 1);
	uniform_int_distribution<int> coinDistribution(1, NO_COINS - 1);
	auto coinToss = bind(faceDistribution, generator);
	auto coinChoice = bind(coinDistribution, generator);

	coinProb.resize(NO_COINS);
	v_1 = v_min = v_rand = 0.0;

	for (int test = 0; test < NO_RUNS; test++)
	{
		float min = 1.0;

		for (int i = 0; i < NO_COINS; i++)
		{
			float p = 0.0;
			for (int j = 0; j < NO_TOSSES; j++)
			{
				p += coinToss();
			}

			p /= NO_TOSSES;

			if (p < min)
			{
				min = p;
			}

			coinProb[i] = p;
		}

		v_min += min;
		v_1 += coinProb[0];
		v_rand += coinProb[coinChoice()];

		if (test % 1000 == 0)
		{
			printf("Completed run %d! Values: %0.4f %0.4f %0.4f\n", test, v_1 / (test + 1), v_rand / (test + 1), v_min / (test + 1));
		}
	}

	printf("Final Result! Values: %0.4f %0.4f %0.4f\n", v_1 / NO_RUNS, v_rand / NO_RUNS, v_min / NO_RUNS);

	return 0;
}

//Final Result! Values: 0.4995 0.4996 0.0377