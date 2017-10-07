#include "lda-interface.h"
#include <iostream>
#include "utils.h"
using namespace std;

bool lda_estimate_fun( float _alpha, long _ntopics,  char* _trainingMode, char* inputSettingFilename, char* inputTrainingFilename, char* outputResultDirectory )
{
	time_t t1;
	(void) time(&t1);
	seedMT(t1);

	INITIAL_ALPHA = _alpha;
	NTOPICS = _ntopics;

	try
	{
		cout<<"START LDA ESTIMATION.........."<<endl;

		read_settings(inputSettingFilename);
		corpus* corpus = read_data(inputTrainingFilename);
		make_directory(outputResultDirectory);
		run_em(_trainingMode, outputResultDirectory, corpus);
		
		cout<<"LDA ESTIMATION SUCCESS."<<endl;
		delete corpus;
		return true;
	}
	catch (...)
	{
		cout<<"LDA ESTIMATION FAILED."<<endl;
		return false;
	}
}

bool lda_prediction_fun( char* inputSettingFilename, char* inputLDAResultDirectory, char* inputPredictingFilename, char* outputResultFilename )
{
	time_t t1;
	(void) time(&t1);
	seedMT(t1);

	try
	{
		cout<<"START LDA PREDICTION.........."<<endl;
		read_settings(inputSettingFilename);
		corpus* corpus = read_data(inputPredictingFilename);
		char* sresultname = strconcat(inputLDAResultDirectory, "/final");
		infer(sresultname, outputResultFilename, corpus);
		delete corpus;

		cout<<"LDA PREDICTION SUCCESS."<<endl;
		return true;
	}
	catch (...)
	{
		cout<<"LDA PREDICTION FAILED."<<endl;
		return false;
	}
}

