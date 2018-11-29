///константные матрицы и их размерности, которые потом уберутся
#ifndef stdafx_H
#define stdafx_H

static const int M = 3;
static const int N = 9;
static const int MeasurMiss = 3, TraceMiss = 3, HypoMiss = 3, HypoApprove=3;
static const double constQ=1;
static const double constSimilarityRate = 9; //порог для D
static const double constBigNumber = 10000; //для матрицы назначения, значения которые ставим туда, где точно нет решения
static int COPIES_COUNT = 0; //счетчик для трасc
static int COPIES_COUNT2 = 0; //счетчик для гипотез

struct CVector {
	double x, y, z;
};

#include "targetver.h"
#include <armadillo>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <tchar.h>
#include <string>

#include "Imitator.h"
#include "AirObject.h"
#include "ResultOfScan.h"
#include "Noize.h"
#include "Voi2.h"
#include "Hypo2.h"
#include "Saver.h"
#include "ReferenceState.h"
#include "VOI.h"
#include "BaseTraceHypo.h"
#include "FilterKalman.h"
#include "Measurements.h"

using namespace std;

#endif stdafx_H