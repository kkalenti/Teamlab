#include "stadfx.h"
#include "VOI.h"
#include "ResultOfScan.h"
#include "FilterKalman.h"

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
//	cout << "Armadillo version: " << arma_version::as_string() << endl;
//	mat A(2, 3);  // directly specify the matrix size (elements are uninitialised)
//	cout << "A.n_rows: " << A.n_rows << endl;  // .n_rows and .n_cols are read only
//	cout << "A.n_cols: " << A.n_cols << endl;
//	A(1, 2) = 456.0;  // directly access an element (indexing starts at 0)
//	A.print("A:");
//	A = 5.0;         // scalars are treated as a 1x1 matrix
//	A.print("A:");
//	A.set_size(4, 5); // change the size (data is not preserved)
//	A.fill(5.0);     // set all elements to a particular value
//	A.print("A:");
//	// endr indicates "end of row"
//	A << 0.165300 << 0.454037 << 0.995795 << 0.124098 << 0.047084 << endr
//		<< 0.688782 << 0.036549 << 0.552848 << 0.937664 << 0.866401 << endr
//		<< 0.348740 << 0.479388 << 0.506228 << 0.145673 << 0.491547 << endr
//		<< 0.148678 << 0.682258 << 0.571154 << 0.874724 << 0.444632 << endr
//		<< 0.245726 << 0.595218 << 0.409327 << 0.367827 << 0.385736 << endr;
//	A.print("A:");
//	// determinant
//	cout << "det(A): " << det(A) << endl;
//	// inverse
//	cout << "inv(A): " << endl << inv(A) << endl;
//	// save matrix as a text file
//	A.save("A.txt", raw_ascii);
//	// load from file
//	mat B;
//	B.load("A.txt");
//	// submatrices
//	cout << "B( span(0,2), span(3,4) ):" << endl << B(span(0, 2), span(3, 4)) << endl;
//	cout << "B( 0,3, size(3,2) ):" << endl << B(0, 3, size(3, 2)) << endl;
//	cout << "B.row(0): " << endl << B.row(0) << endl;
//	cout << "B.col(1): " << endl << B.col(1) << endl;
//	// transpose
//	cout << "B.t(): " << endl << B.t() << endl;
//	// maximum from each column (traverse along rows)
//	cout << "max(B): " << endl << max(B) << endl;
//	// maximum from each row (traverse along columns)
//	cout << "max(B,1): " << endl << max(B, 1) << endl;
//	// maximum value in B
//	cout << "max(max(B)) = " << max(max(B)) << endl;
//	// sum of each column (traverse along rows)
//	cout << "sum(B): " << endl << sum(B) << endl;
//	// sum of each row (traverse along columns)
//	cout << "sum(B,1) =" << endl << sum(B, 1) << endl;
//	// sum of all elements
//	cout << "accu(B): " << accu(B) << endl;
//	// trace = sum along diagonal
//	cout << "trace(B): " << trace(B) << endl;
//	// generate the identity matrix
//	mat C = eye<mat>(4, 4);
//// random matrix with values uniformly distributed in the [0,1] interval
//	mat D = randu<mat>(4, 4);
//	D.print("D:");
//	// row vectors are treated like a matrix with one row
//	rowvec r;
//	r << 0.59119 << 0.77321 << 0.60275 << 0.35887 << 0.51683;
//	r.print("r:");
//	// column vectors are treated like a matrix with one column
//	vec q;
//	q << 0.14333 << 0.59478 << 0.14481 << 0.58558 << 0.60809;
//	q.print("q:");
//	// convert matrix to vector; data in matrices is stored column-by-column
//	vec v = vectorise(A);
//	v.print("v:");
//	// dot or inner product
//	cout << "as_scalar(r*q): " << as_scalar(r*q) << endl;
//	// outer product
//	cout << "q*r: " << endl << q*r << endl;
//	// multiply-and-accumulate operation (no temporary matrices are created)
//	cout << "accu(A % B) = " << accu(A % B) << endl;
//	// example of a compound operation
//	B += 2.0 * A.t();
//	B.print("B:");
//	// imat specifies an integer matrix
//	imat AA;
//	imat BB;
//	AA << 1 << 2 << 3 << endr << 4 << 5 << 6 << endr << 7 << 8 << 9;
//	BB << 3 << 2 << 1 << endr << 6 << 5 << 4 << endr << 9 << 8 << 7;
//	// comparison of matrices (element-wise); output of a relational operator is a umat
//	umat ZZ = (AA >= BB);
//	ZZ.print("ZZ:");
//	// cubes ("3D matrices")
//	cube Q(B.n_rows, B.n_cols, 2);
//	Q.slice(0) = B;
//	Q.slice(1) = 2.0 * B;
//	Q.print("Q:");
//	// 2D field of matrices; 3D fields are also supported
//	field<mat> F(4, 3);
//	for (uword col = 0; col < F.n_cols; ++col)
//	for (uword row = 0; row < F.n_rows; ++row)
//	{
//		F(row, col) = randu<mat>(2, 3);  // each element in field<mat> is a matrix
//	}
//	F.print("F:");




	//¬енгерский алгоритм, который не работает дл€ пары из одинаковых наборов значений

	/*vector< vector<double> > costMatrix(3, vector<double>(3, 0));
	costMatrix[0][0] = 10000;
	costMatrix[0][1] = 4;
	costMatrix[0][2] = 5;
	costMatrix[1][0] = 10000;
	costMatrix[1][1] = 10000;
	costMatrix[1][2] = 6;
	costMatrix[2][0] = 10000;
	costMatrix[2][1] = 10000;
	costMatrix[2][2] = 10000;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<< costMatrix[i][j]<<"\t";
		}
		cout << "\n";
	}
	HungarianAlgorithm HungAlgo;
	vector<int> assignment;

	double cost = HungAlgo.Solve(costMatrix, assignment);

	for (unsigned int x = 0; x < costMatrix.size(); x++)
		std::cout << x << "," << assignment[x] << "\t";

	std::cout << "\ncost: " << cost << std::endl;*/

	CVOI *voi = new CVOI;
	voi->SetSizeZone(0, 6000);
	CVector v1;
	v1.x = 1000;
	v1.y = 5000;
	v1.z = 5000;
	CResultOfScan r1(v1, 20, 0.0124);
	voi->pushMeasurements(r1);
	voi->pushSectorObserved(0.0200, 2000);
	voi->pushSectorObserved(0.0300, 4000);
	voi->pushSectorObserved(0.0450, 6000);
	v1.x = 1500;
	v1.y = 4900;
	v1.z = 5000;
	CResultOfScan r2(v1, 20, 0.0500);
	voi->pushMeasurements(r2);
	voi->pushSectorObserved(0.0600, 2000);
	voi->pushSectorObserved(0.0700, 4000);
	voi->pushSectorObserved(0.0850, 6000);
		mat P_Const;
		P_Const << 100 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 100 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 100 << endr;
		//P_Const.print("Pconst:");
//cout << "Pconst:" << endl << P_Const << endl;


	

	
	//FK.setDt(0.4);
	//FK.makeDt_squared();


	//mat Q = zeros(1, 1);
	//Q(0, 0) = 0.1;
	////Q << 0.1;
	//mat R = zeros(3, 3);
	//R << 1 << 0 << 0 <<endr
	//	<< 0 << 1 << 0 << endr
	//	<< 0 << 0 << 1 << endr;
	//FK.InitialNoiseMatrix(R, Q);
	////FK.makeMatrix_U();
	////FK.makeMatrix_F();	
	//FK.Prediction(0.1);

	/*FK.makeMatrix_H();
	colvec z = zeros(3, 1);
	z << 3 << endr << 8 << endr << 2 << endr;
	FK.Measurement(z);
	FK.Update();
*/

	/*FK.Prediction(0.2);
	z << -1.3 << endr << 2.3 << endr << 6.1 << endr;
	FK.Measurement(z);
	FK.Update();*/

	double x = 1.2;
	double y = 3.7;
	double c = -4.4;
	double a = 0.1;
	double Hz = 100.0; // Frequency of Vision System
	double dt = 1.0 / Hz;//
	double	T = 1.0;// # s measuremnt tim
	double	m = int(T / dt);// # number of measurements
	double ret = 0.1;

	colvec x_0 = zeros(9, 1);
	x_0 << x << endr << 0 << endr << 0 << endr << y << endr << 0 << endr << 0 << endr << c << endr << 0 << endr << 0 << endr;
	x_0.print("X0:");

	CKalmanFilter FK;
	FK.InitialVariableMatrix(x_0, P_Const);
	mat Q = zeros(1, 1);
	Q(0, 0) = 0.1;
	//Q << 0.1;
	mat R = zeros(3, 3);
	R << 1 << 0 << 0 <<endr
		<< 0 << 1 << 0 << endr
		<< 0 << 0 << 1 << endr;
	FK.InitialNoiseMatrix(R, Q);
	colvec new_z = zeros(3, 1);
	FK.makeMatrix_H();

	for (int i = 0; i < 10; i++)
	{
		FK.Prediction(ret);

		ret = (double)rand() / ((double)rand() + 0.1);
		x = x + (ret - floor(ret));
		ret = (double)rand() / ((double)rand() + 0.1);
		y = y + (ret - floor(ret));
		ret = (double)rand() / ((double)rand() + 0.1);
		c = c - (ret - floor(ret));

		//new_z << x << endr << 0 << endr << 0 << endr << y << endr << 0 << endr << 0 << endr << c << endr << 0 << endr << 0 << endr;
		new_z << x << endr << y << endr << c << endr;
		FK.Measurement(new_z);
		FK.Update();
		//FK.print_coordinate();

		

		
	}



//cout << "Armadillo version: " << arma_version::as_string() << endl;
//  
//  // directly specify the matrix size (elements are uninitialised)
//  mat A(2,3);
//  
//  // .n_rows = number of rows    (read only)
//  // .n_cols = number of columns (read only)
//  cout << "A.n_rows = " << A.n_rows << endl;
//  cout << "A.n_cols = " << A.n_cols << endl;
//  
//  // directly access an element (indexing starts at 0)
//  A(1,2) = 456.0;
//  
//  A.print("A:");
//  
//  // scalars are treated as a 1x1 matrix,
//  // hence the code below will set A to have a size of 1x1
//  A = 5.0;
//  A.print("A:");
//  
//  // if you want a matrix with all elements set to a particular value
//  // the .fill() member function can be used
//  A.set_size(3,3);
//  A.fill(5.0);
//  A.print("A:");
//  
//  
//  mat B;
//  
//  // endr indicates "end of row"
//  B << 0.555950 << 0.274690 << 0.540605 << 0.798938 << endr
//    << 0.108929 << 0.830123 << 0.891726 << 0.895283 << endr
//    << 0.948014 << 0.973234 << 0.216504 << 0.883152 << endr
//    << 0.023787 << 0.675382 << 0.231751 << 0.450332 << endr;
//  
//  // print to the cout stream
//  // with an optional string before the contents of the matrix
//  B.print("B:");
//  
//  // the << operator can also be used to print the matrix
//  // to an arbitrary stream (cout in this case) 
//  cout << "B:" << endl << B << endl;
//  
//  // save to disk
//  B.save("B.txt", raw_ascii);
//  
//  // load from disk
//  mat C;
//  C.load("B.txt");
//  
//  C += 2.0 * B;
//  C.print("C:");
//  
//  
//  // submatrix types:
//  //
//  // .submat(first_row, first_column, last_row, last_column)
//  // .row(row_number)
//  // .col(column_number)
//  // .cols(first_column, last_column)
//  // .rows(first_row, last_row)
//  
//  cout << "C.submat(0,0,3,1) =" << endl;
//  cout << C.submat(0,0,3,1) << endl;
//  
//  // generate the identity matrix
//  mat D = eye<mat>(4,4);
//  
//  D.submat(0,0,3,1) = C.cols(1,2);
//  D.print("D:");
//  
//  // transpose
//  cout << "trans(B) =" << endl;
//  cout << trans(B) << endl;
//  
//  // maximum from each column (traverse along rows)
//  cout << "max(B) =" << endl;
//  cout << max(B) << endl;
//  
//  // maximum from each row (traverse along columns)
//  cout << "max(B,1) =" << endl;
//  cout << max(B,1) << endl;
//  
//  // maximum value in B
//  cout << "max(max(B)) = " << max(max(B)) << endl;
//  
//  // sum of each column (traverse along rows)
//  cout << "sum(B) =" << endl;
//  cout << sum(B) << endl;
//  
//  // sum of each row (traverse along columns)
//  cout << "sum(B,1) =" << endl;
//  cout << sum(B,1) << endl;
//  
//  // sum of all elements
//  cout << "sum(sum(B)) = " << sum(sum(B)) << endl;
//  cout << "accu(B)     = " << accu(B) << endl;
//  
//  // trace = sum along diagonal
//  cout << "trace(B)    = " << trace(B) << endl;
//  
//  // random matrix -- values are uniformly distributed in the [0,1] interval
//  mat E = randu<mat>(4,4);
//  E.print("E:");
//  
//  cout << endl;
//  
//  // row vectors are treated like a matrix with one row
//  rowvec r;
//  r << 0.59499 << 0.88807 << 0.88532 << 0.19968;
//  r.print("r:");
//  
//  // column vectors are treated like a matrix with one column
//  colvec q;
//  q << 0.81114 << 0.06256 << 0.95989 << 0.73628;
//  q.print("q:");
//  
//  // dot or inner product
//  cout << "as_scalar(r*q) = " << as_scalar(r*q) << endl;
//  
//  
//  // outer product
//  cout << "q*r =" << endl;
//  cout << q*r << endl;
//  
//  // multiply-and-accumulate operation
//  // (no temporary matrices are created)
//  cout << "accu(B % C) = " << accu(B % C) << endl;
//  
//  // sum of three matrices (no temporary matrices are created)
//  mat F = B + C + D;
//  F.print("F:");
//  
//  // imat specifies an integer matrix
//  imat AA;
//  imat BB;
//  
//  AA << 1 << 2 << 3 << endr << 4 << 5 << 6 << endr << 7 << 8 << 9;
//  BB << 3 << 2 << 1 << endr << 6 << 5 << 4 << endr << 9 << 8 << 7;
//  
//  // comparison of matrices (element-wise)
//  // output of a relational operator is a umat
//  umat ZZ = (AA >= BB);
//  ZZ.print("ZZ =");
//  
//  
//  // 2D field of arbitrary length row vectors
//  // (fields can also store abitrary objects, e.g. instances of std::string)
//  field<rowvec> xyz(3,2);
//  
//  xyz(0,0) = randu(1,2);
//  xyz(1,0) = randu(1,3);
//  xyz(2,0) = randu(1,4);
//  xyz(0,1) = randu(1,5);
//  xyz(1,1) = randu(1,6);
//  xyz(2,1) = randu(1,7);
//  
//  cout << "xyz:" << endl;
//  cout << xyz << endl;
//  
//  
//  // cubes ("3D matrices")
//  cube Q( B.n_rows, B.n_cols, 2 );
//  
//  Q.slice(0) = B;
//  Q.slice(1) = 2.0 * B;
//  
//  Q.print("Q:");


	system("pause");
	return 0;
}