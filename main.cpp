
/*
 * main
 *
 */


#include "lda-interface.h"
#include <iostream>
#include <QTime>

using namespace std;
/*
#include "lda-estimate.h"

int origin_main(int argc, char* argv[])
{
	 corpus* corpus;

	time_t t1;
	(void) time(&t1);
	seedMT(t1);
	// seedMT(4357U);

	if (argc > 1)
	{
		//alpha = 50/NTOPICS
		//est 25 3 ./data/settings.txt ./data/train random ./data/LDA_result
		if (strcmp(argv[1], "est")==0)
		{
			INITIAL_ALPHA = atof(argv[2]);
			NTOPICS = atoi(argv[3]);
			read_settings(argv[4]);
			corpus = read_data(argv[5]);
			make_directory(argv[7]);
			run_em(argv[6], argv[7], corpus);
		}

		//inf ./data/settings.txt ./data/LDA_result/final ./data/predict ./data/LDA_INF
		if (strcmp(argv[1], "inf")==0)
		{
			read_settings(argv[2]);
			corpus = read_data(argv[4]);
			infer(argv[3], argv[5], corpus);
		}
	}
	else
	{
		printf("usage : lda est [initial alpha] [k] [settings] [data] [random/seeded/*] [directory]\n");
		printf("        lda inf [settings] [model] [data] [name]\n");
	}
	return(0);
}
*/



int main(int argc, char* argv[])
{
	QTime startTime;
	startTime.start();

	lda_estimate_fun(0.5, 100, "random", "./data/settings.txt", "./data/POItoVec_lda_NEW", "./data/LDA_result_100_NEW");		//输出是LDA_RESULT/final.alpha LDA_RESULT/final.beta LDA_RESULT/final.gamma
	//lda_prediction_fun("./data/settings.txt", "./data/LDA_result", "./data/predict", "./data/LDA_INF");	//通过最后的LDA_INF.gamma文件获取类别

	int nTime = startTime.elapsed();
	cout<<"spend time = "<<(double)nTime / 1000.0<<endl;

	return 0;
   
}