#include "matrix.h"
#ifndef MAT_TEST_H
#define MAT_TEST_H

// ASCII of ctrl+c
const int ETX = 3;

class Mat_Test{
private:
	enum{MAX = 3};
	string s_msg;
	stringstream ss;
	time_t t_seed;
	bool status;
	int min_count;
	int rand_num;
	int rand_num1;
	int r, r1;
	int c, c1;
public:
	Mat_Test();
	void constructor_test();
	void access_test();
	void add_test();
	void cmp_test();
	void mul_test();
	void transpose_test();
	void getcount_test();
	void bool_test();
	void fill_test();
	void scale_test();
	void minmax_test();
	void toString_test();
	// Helper functions
	/* Proceed to next test? */
	void proceed();
	void display_msg(stringstream&);
	void display_s_msg();
};
	

	
	
#endif