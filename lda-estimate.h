#ifndef LDA_ESTIMATE_H
#define LDA_ESTIMATE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <time.h>

#include "lda.h"
#include "lda-data.h"
#include "lda-inference.h"
#include "lda-model.h"
#include "lda-alpha.h"
#include "utils.h"
#include "cokus.h"

extern int LAG;

extern float EM_CONVERGED;
extern int EM_MAX_ITER;
extern int ESTIMATE_ALPHA;
extern double INITIAL_ALPHA;
extern int NTOPICS;

double doc_e_step(document* doc,
                  double* gamma,
                  double** phi,
                  lda_model* model,
                  lda_suffstats* ss);

void save_gamma(char* filename,
                double** gamma,
                int num_docs,
                int num_topics);

void run_em(char* start,
            char* directory,
            corpus* corpus);

void read_settings(char* filename);

void infer(char* model_root,
           char* save,
           corpus* corpus);

#endif


