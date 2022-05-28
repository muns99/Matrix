#include "matrix.h"
#include "mat_test.h"


int main()
{
    Mat_Test mt;
    int test_num = -1;
    // start message
    mt.display_s_msg();
    // default value of test_num: -1
    cin >> test_num;
    system("cls");
    switch(test_num)
    {
        /*------------------------------------------------------*/
        /* [1] Test 3 Constructors & print (4p)*/
        /*------------------------------------------------------*/
        case(1):
        {
            mt.constructor_test();
            // Proceed to next test?
            mt.proceed();
        }
        /*------------------------------------------------------*/
        /*[2] Test float& access(int r_ind, c_ind)*/
        /*------------------------------------------------------*/
        case(2):
        {
            mt.access_test();
            // Proceed to next test?
            mt.proceed();
        }
	 	/*------------------------------------------------------*/
	 	/*[3] Test Copy Constructor/Addition/subtraction*/
	    /*------------------------------------------------------*/
        case(3):
        {
            mt.add_test();
            // Proceed to next test?
            mt.proceed();
        }
	 	/*------------------------------------------------------*/
	 	/*[4] Test operator==(), operator!=()*/
	    /*------------------------------------------------------*/
        case(4):
        {
            mt.cmp_test();
            // Proceed to next test?
            mt.proceed();
        }
	 	/*------------------------------------------------------*/
	 	/*[5] Test Matrix operator*(const Matrix&)*/
	    /*------------------------------------------------------*/
	 	case(5):
        {
            mt.mul_test();
		    // Proceed to next test?
		    mt.proceed();
	 	}
	 	/*------------------------------------------------------*/
	 	/*[6] Test Matrix transpose()*/
	    /*------------------------------------------------------*/
	 	case(6):
	 	{
		 	mt.transpose_test();
		    // Proceed to next test?
		    mt.proceed();
	 	}
	 	/*------------------------------------------------------*/
	 	/*[7] Test get_rows(), get_cols()*/
	    /*------------------------------------------------------*/
	 	case(7):
	 	{
		    mt.getcount_test();
            // Proceed to next test?
		    mt.proceed();
	 	}
	 	/*------------------------------------------------------*/
	 	/*[8] Test 6 boolean functions*/
	    /*------------------------------------------------------*/
	 	/*(Identity, Idempotent, Square, Symmetric, UpperT, LowerT)*/
	 	case(8):
	 	{
            mt.bool_test();
		    // Proceed to next test?
		    mt.proceed();
	 	}
	 	/*------------------------------------------------------*/
	 	/*[9] Test Matrix void fill(float val)*/
	    /*------------------------------------------------------*/
	 	case(9):
	 	{
            mt.fill_test();
           // Proceed to next test?
		    mt.proceed();
	 	}
	 	/*------------------------------------------------------*/
	 	/*[10] Test Matrix Scaling*/
	 	/* operator*(float val), Matrix operator/(float val)*/
	    /*------------------------------------------------------*/
	 	case(10):
	 	{
		 	mt.scale_test();
		    // Proceed to next test?
		    mt.proceed();
	 	}
	 	/*------------------------------------------------------*/
	 	/*[11] Test float minElement(), float maxElement()*/
	    /*------------------------------------------------------*/
	 	case(11):
	 	{
            mt.minmax_test();
		    // Proceed to next test?
		    mt.proceed();
		}
	    /*------------------------------------------------------*/
	    /*[BONUS] Test string toString()*/
	    /*------------------------------------------------------*/
	    case(0):
	    {
	        mt.toString_test();
	    }
	    default:
	        break;
    }
    return 0;
}
/*
  Bonus:
  determinant();
  operator/(const Matrix&); // Matrix inverse
*/
