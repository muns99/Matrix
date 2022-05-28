#include "mat_test.h"

Mat_Test::Mat_Test()
{
    t_seed = time(NULL);
    srand(t_seed);
    // Init. test case variable
    status = true;
    // Min #elements
    min_count = 3;
    // Gen. random numbers
    rand_num = rand()%MAX+min_count;
    rand_num1 = rand()%MAX+min_count;
    // for non-square matrices
    if(rand_num1==rand_num)
    {
        rand_num1=rand_num1-1;
    }
    // matrix indices
    r=rand_num, c=rand_num;
    r1=rand_num, c1=rand_num1;
    // compiler settings: follow the C++11 language standard
    s_msg = R"(
	/--------------------------------------------------/
	/-------------------Matrix Lab---------------------/
	/--------------------------------------------------/

	-Please implement: Destructor, and
	 a Copy Constructor to avoid shallow copy.
	-Total 15p: 14p(pdf) and 1p:(Destructor/Copy Constructor)
	-Copy constructor VS operator=(const Matrix&):
		Matrix m1(r, c, Identity);
		Matrix m2 = m1; // invokes copy "constructor"
		Matrix m3(m1);  // invokes copy "constructor"
		Matrix m4(r, c, Random);
		m4 = m1; 	// invokes operator=(const Matrix&)

	-Select Test case:
	[1] Test 3 constructors & print
	[2] Test float& access(int r_ind, c_ind)
	[3] Test Copy Constructor/Addition/subtraction
	[4] Test operator==(), operator!=()
	[5] Test Matrix operator*(const Matrix&)
	[6] Test Matrix transpose()
	[7] Test get_rows(), get_cols()
	[8] Test 6 boolean functions
	[9] Test Matrix void fill(float val)
	[10] Test Matrix Scaling:
	     Matrix operator*(float), Matrix operator/(float)
	[11] Test float minElement(), float maxElement()
	[0] Test string toString()
	your input:)";
}

void Mat_Test::constructor_test()
{
    Matrix m(r, c), m1(r1, c1, -1);
    Matrix m_i(r, c, Identity), m_r(r1, c1, Random);
    // Matrix m_r1(r1, c1, Random);

    ss << "[1] Test 3 constructors & print: \n";
    ss << "Note (print function): separate elements with \\t \n";
    ss << "Matrix of size " << r << 'x' << c;
    ss << " w/ elements initialized to 0:\n";
    display_msg(ss);
    m.print();

    ss << "\n\n\nMatrix of size " << r1 << 'x' << c1;
    ss << " w/ elements initialized to -1:\n";
    display_msg(ss);
    m1.print();

    ss << "\n\n\nIdentity matrix of size: "
       << r << 'x' << c << ':' << endl;
    display_msg(ss);
    m_i.print();

    ss << "\n\n\nRandomly initialized matrix of size: "
       << r1 << 'x' << c1 << ':' << endl;
    display_msg(ss);
    m_r.print();
}

void Mat_Test::access_test()
{
    Matrix m_i(r, c, Identity), m_r(r1, c1, Random);
    cout << "[2] Test float& access(int r_ind, int c_ind): \n";
    cout << "Note: test uses get_rows(), get_cols().\n";
    // diagonal elements are equal to 1
    if((m_i.access(1, 1)) && !m_i.access(0, 1))
    {
        cout << "Test I: passed\n";
    }
    else
    {
        cout << "Test I: failed.\n";
    }
    // test return by ref.
    m_r.access(1, 0)=rand_num;
    if(m_r.get_rows()==r1 && m_r.get_cols()==c1 &&
        m_r.access(1, 0)==rand_num)
    {
        cout << "Test II: passed.\n";
    }
    else
    {
        cout << "Test II: failed.\n";
    }
    // test: out of bounds
    cout << "Test III: (Memory Issues/Crash Test): \n";
    m_r.access(1000*r1, 1000*c1);
}

void Mat_Test::add_test(){
    Matrix  m_r(r1, c1, Random), m_r1(r1, c1, Random);
    cout << "[3] Test Copy Constructor/Addition/subtraction: \n";
    Matrix res = m_r + m_r1;
    // res = m_r + m_r1; // invokes operator=();
    status = true;
    Matrix res1 = res - m_r1; // now res equals m_r
    for (int i=0; i<r1; i++)
    {
        for (int j=0; j<c1; j++)
        {
            if(res1.access(i, j)!=m_r.access(i, j))
            {
                status = false;
                break;
            }
        }
        // break out of outer loop
        if(!status) break;
    }
    if(status)
    {
        cout<<"Test passed.\n";
    }
    else
    {
        cout <<"Test failed.\n";
    }
}

void Mat_Test::cmp_test(){
	Matrix  m_r(r1, c1, Random), m_r1(r1, c1, Random);
	cout << "[4] Test operator==(), operator!=(): \n";
    cout << "Test uses copy constructor, operator+(), access(), get_rows, get_cols()\n";
    m_r.access(r1-1, c1-1) = r1;
    m_r1.access(r1-1, c1-1) = c1;

    Matrix sum = m_r + m_r1;
    Matrix m_r1_mod (m_r1);
    // modify value of last elem
    m_r1_mod.access(r1-1, c1-1) -= 1;
    // Test cases
    if( m_r.get_rows()==r1 && m_r.get_cols()==c1)
    {
        if(sum-m_r1 == m_r)
        {
            cout << "Test I: passed.\n";
        }
        else
        {
            cout <<"Test I: failed.\n";
        }
        if ( m_r1 != m_r1_mod)
        {
            cout << "Test II: passed.\n";
        }
        else
        {
            cout <<"Test II: failed.\n";
        }
    }
    else
        cout << "Test: failed.\n";
}

void Mat_Test::mul_test(){
 	cout << "[5] Test Matrix operator*(const Matrix&): \n";
    Matrix m_t(r1, c1, -1), m_t1(c1, r1, -1);
    Matrix prod = m_t*m_t1;
    status = true;
    // Test II
	for (int i=0; i<r1; i++)
	{
		for (int j=0; j<r1; j++)
		{
			// each element is equal to #cols of m_t
			if(prod.access(i, j) != c1)
				{status = false; break;}
		}
		if(!status) break;
    }
    // Test cases
    if(prod.get_rows()==r1 && prod.get_rows()==prod.get_cols())
    	{cout << "Test I: passed.\n";}
    else
    	{cout <<"Test I: failed.\n";}
    if(status)
    	{cout << "Test II: passed.\n";}
    else
    	{cout <<"Test II: failed.\n";}
}

void Mat_Test::transpose_test(){
	Matrix m_r(r1, c1, Random);
	cout << "[6] Test Matrix transpose(): \n";
 	Matrix m_trans = m_r.transpose();
 	int mt_r = m_trans.get_rows();
 	int mt_c = m_trans.get_cols();
 	// Test II
	status = true;
	for (int i=0; i<mt_r; i++)
	{
		for (int j=0; j<mt_c; j++)
		{
			// each element is equal to #cols of m_t
			if(m_trans.access(i, j) != m_r.access(j, i))
				{status = false; break;}
		}
		if(!status) break;
    }
 	// Test cases
   if(mt_r==m_r.get_cols() &&
      mt_c==m_r.get_rows())
   	{cout << "Test I: passed.\n";}
   else
   	{cout <<"Test I: failed.\n";}// Test II
   if (status)
   	{cout << "Test II: passed.\n";}
   else
   	{cout <<"Test II: failed.\n";}
}

void Mat_Test::getcount_test(){
    Matrix m(r, c), m1(r1, c1, -1);
	cout << "[7] get_rows(), get_cols(): \n";
 	if (r==m.get_rows() && c==m.get_cols() &&
 		r1==m1.get_rows() && c1==m1.get_cols())
 		cout << "Test passed.\n";
 	else
 		cout <<"Test failed.\n";
}

void Mat_Test::bool_test(){
	Matrix m_i(r, c, Identity);
	Matrix m_r1(r1, c1, Random);
	cout << "[8] Test 6 boolean functions\n";
 	// 1. Identity
    if(m_i.isIdentity() && m_i.get_rows()==r)
    	{cout <<"1. isIdentity():\t passed.\n";}
    else
    	{cout <<"1. isIdentity():\t failed.\n";}
    // 2. Idempotent
    Matrix m1(r1, c1, 3);
    Matrix m_sym = m1*m1.transpose();
    if(m_i.isIdempotent() && !m_sym.isIdempotent() && m_i.get_rows()==r)
    	{cout <<"2. isIdempotent():\t passed.\n";}
    else
    	{cout <<"2. isIdempotent():\t failed.\n";}
    // 3. Square
    if(m_i.isSquare() && !m_r1.isSquare() && m_i.get_rows()==r)
    	{cout << "3. isSquare():\t\t passed.\n";}
    else
    	{cout << "3. isSquare():\t\t failed.\n";}
    // 4. Symmetric
    Matrix m_asym = m_sym;
    // min_count = 3
    m_asym.access(1, 2) -=1;
    if(m_sym.isSymmetric() && !m_asym.isSymmetric() && m_sym.get_rows()==r1)
    	{cout << "4. isSymmetric():\t passed.\n";}
    else
    	{cout << "4. isSymmetric():\t failed.\n";}
    // Triangular Matrices
    Matrix m_tri(r, r, 1), m_one(r, r, 1);
    for (int i=0; i<r; i++)
    {
    	for (int j=0; j<r; j++)
    	{
    		if (j>=i)
    		m_tri.access(i, j) += 1;
    	}
    }
    Matrix m_ut = m_tri - m_one;
    Matrix m_lt = m_tri - m_ut*2 + m_i;
    // insert zeros
    m_ut.access(1, 2)=0;
    m_lt.access(2, 1)=0;
    // m_ut.print(); cout << endl;
    // m_lt.print(); cout << endl;
    // Non-square Matrices
	int ns_r = r+1;
	int ns_c = r;
    Matrix m_nsu(ns_r, ns_c, 1), m_nsl(ns_r, ns_c, 1);
    for (int i=0; i<ns_r; i++)
    {
    	for (int j=0; j<ns_c; j++)
    	{
    		if (j<i)
    		{m_nsu.access(i, j) = 0;}
    		if (j>i)
    		{m_nsl.access(i, j) = 0;}
    	}
    }
    // Test cases
    // 5. UpperTriangle
    if(m_i.isUpperTriangle() && m_ut.isUpperTriangle() &&
    	!m_nsu.isUpperTriangle() && m_i.get_rows()==r)
    	{cout << "5. isUpperTriangle():\t passed.\n";}
    else
    	{cout << "5. isUpperTriangle():\t failed.\n";}
    // 6. LowerTriangle
    if(m_i.isLowerTriangle() && m_lt.isLowerTriangle() &&
    	!m_nsl.isLowerTriangle() && m_i.get_rows()==r)
    	{cout << "6. isLowerTriangle():\t passed.\n";}
    else
    	{cout << "6. isLowerTriangle():\t failed.\n";}
}

void Mat_Test::fill_test(){
	Matrix m(r1, r1, Identity);
 	cout << "[9] Test void fill(float val): \n";
 	float fill_val = -5;
 	m.fill(fill_val);
 	status = true;
	for (int i=0; i<r1; i++)
	{
		for (int j=0; j<r1; j++)
		{
			// each element is equal to #cols of m_t
			if(m.access(i, j) != fill_val)
				{status = false; break;}
		}
		if(!status) break;
    }
 	// Test cases
   	if(status && m.get_rows()==r1)
   	{cout << "Test I: passed.\n";}
   	else
   	{cout <<"Test I: failed.\n";}
}

void Mat_Test::scale_test(){
	Matrix m_i(r, c, Identity);
	cout << "[10] Test Matrix operator*(float val), "
 	     << "Matrix operator/(float val): \n"
 	     << "Note: uses operator !=()\n";
 	float scale = -5, scale1 = 4, scale2 = 0.0;
 	Matrix res = m_i * scale;
 	Matrix res1 = m_i / scale1;
 	Matrix res2 = res1 * scale1;
 	Matrix m_test = m_i / scale2;
 	// Test I
	status = true;
	for (int i=0; i<r; i++)
	{
		for (int j=0; j<r; j++)
		{
			// each element is equal to #cols of m_t
			float cur_val = res.access(i, j);
			if(((i==j) && cur_val!=scale) ||
			   (i!=j && cur_val!=0))
				{status = false; break;}
		}
		if(!status) break;
    }
 	// Test cases
   if(status && m_i.get_rows()==r)
   	{cout << "Test I:\t\t\t\t passed.\n";}
   else
   	{cout <<"Test I:\t\t\t\t failed.\n";}
   if (res2==m_i && m_i.get_rows()==r)
   	{cout << "Test II:\t\t\t passed.\n";}
   else
   	{cout <<"Test II:\t\t\t failed.\n";}
   if((m_test.get_rows() && m_test.get_cols() && isinf(m_test.access(0, 0)))
      || m_i.get_rows()!=r)
   	{cout <<"Test III (div. by zero):\t failed.\n";}
   else
   	{cout <<"Test III (div. by zero):\t passed.\n";}
}

void Mat_Test::minmax_test(){
	cout << "[11] Test float minElement(), float maxElement(): \n";
 	Matrix m_minmax(r1, c1);
 	float min_val = 1e2+1e8;
 	float max_val = -min_val;
 	for (int i=0; i<r1; i++)
 	{
 		for (int j=0; j<c1; j++)
 		{
 			rand_num = rand()%(int)1e8 + 1e2;
 			rand_num1 = rand()%(int)1e2 + 1;
 			// randomly flip sign
 			if(rand_num%2) {rand_num*=-1;}
 			float cur_val = (float)rand_num/rand_num1;
	 		m_minmax.access(i, j) = cur_val;
	 		if(cur_val<min_val) {min_val = cur_val;}
 			if(cur_val>max_val) {max_val = cur_val;}
 		}
 	}
    // Test cases
   if(m_minmax.minElement()==min_val)
   	{cout << "Test I: passed.\n";}
   else
   	{cout <<"Test I: failed.\n";}
   if (m_minmax.maxElement()==max_val)
   	{cout << "Test II: passed.\n";}
   else
   	{cout <<"Test II: failed.\n";}
}

void Mat_Test::toString_test()
{
    Matrix m_r(r1, c1, Random);
    cout << "[BONUS] Test string toString(): \n";
    string str_mat = m_r.toString();
    cout << "Stringified Matrix: \n" << str_mat << endl;
    cout << "Expected output: \n";
    m_r.print();
}

/* Helper functions */
void Mat_Test::proceed()
{
    char input_cmd = 0;
    cout << "\nNext Test (press ctrl+c to exit)?";
    input_cmd = getch();
    if (input_cmd==ETX)
        exit(0);
    system("cls");
}

void Mat_Test::display_msg(stringstream& ss)
{
    string msg = ss.str();
    ss.str(string());
    cout << msg;
}

void Mat_Test::display_s_msg()
{
    cout << s_msg;
}
