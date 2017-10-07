#include "utils.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
/*
 * given log(a) and log(b), return log(a + b)
 *
 */

double log_sum(double log_a, double log_b)
{
  double v;

  if (log_a < log_b)
  {
      v = log_b+log(1 + exp(log_a-log_b));
  }
  else
  {
      v = log_a+log(1 + exp(log_b-log_a));
  }
  return(v);
}

 /**
   * Proc to calculate the value of the trigamma, the second
   * derivative of the loggamma function. Accepts positive matrices.
   * From Abromowitz and Stegun.  Uses formulas 6.4.11 and 6.4.12 with
   * recurrence formula 6.4.6.  Each requires workspace at least 5
   * times the size of X.
   *
   **/

double trigamma(double x)
{
    double p;
    int i;

    x=x+6;
    p=1/(x*x);
    p=(((((0.075757575757576*p-0.033333333333333)*p+0.0238095238095238)
         *p-0.033333333333333)*p+0.166666666666667)*p+1)/x+0.5*p;
    for (i=0; i<6 ;i++)
    {
        x=x-1;
        p=1/(x*x)+p;
    }
    return(p);
}


/*
 * taylor approximation of first derivative of the log gamma function
 *
 */

double digamma(double x)
{
    double p;
    x=x+6;
    p=1/(x*x);
    p=(((0.004166666666667*p-0.003968253986254)*p+
	0.008333333333333)*p-0.083333333333333)*p;
    p=p+log(x)-0.5/x-1/(x-1)-1/(x-2)-1/(x-3)-1/(x-4)-1/(x-5)-1/(x-6);
    return p;
}


double loggamma(double x)
{
     double z=1/(x*x);

    x=x+6;
    z=(((-0.000595238095238*z+0.000793650793651)
	*z-0.002777777777778)*z+0.083333333333333)/x;
    z=(x-0.5)*log(x)-x+0.918938533204673+z-log(x-1)-
	log(x-2)-log(x-3)-log(x-4)-log(x-5)-log(x-6);
    return z;
}



/*
 * make directory
 *
 */

void make_directory(char* name)
{
	_mkdir(name);
}


/*
 * argmax
 *
 */

int argmax(double* x, int n)
{
    int i;
    double max = x[0];
    int argmax = 0;
    for (i = 1; i < n; i++)
    {
        if (x[i] > max)
        {
            max = x[i];
            argmax = i;
        }
    }
    return(argmax);
}


double Gamma
	(
	double x    // We require x > 0
	)
{
// 	if (x <= 0.0)
// 	{
// 		std::stringstream os;
// 		os << "Invalid input argument " << x <<  ". Argument must be positive.";
// 		throw std::invalid_argument( os.str() ); 
// 	}

	// Split the function domain into three intervals:
	// (0, 0.001), [0.001, 12), and (12, infinity)

	///////////////////////////////////////////////////////////////////////////
	// First interval: (0, 0.001)
	//
	// For small x, 1/Gamma(x) has power series x + gamma x^2  - ...
	// So in this range, 1/Gamma(x) = x + gamma x^2 with error on the order of x^3.
	// The relative error over this interval is less than 6e-7.

	const double gamma = 0.577215664901532860606512090; // Euler's gamma constant

	if (x < 0.001)
		return 1.0/(x*(1.0 + gamma*x));

	///////////////////////////////////////////////////////////////////////////
	// Second interval: [0.001, 12)

	if (x < 12.0)
	{
		// The algorithm directly approximates gamma over (1,2) and uses
		// reduction identities to reduce other arguments to this interval.

		double y = x;
		int n = 0;
		bool arg_was_less_than_one = (y < 1.0);

		// Add or subtract integers as necessary to bring y into (1,2)
		// Will correct for this below
		if (arg_was_less_than_one)
		{
			y += 1.0;
		}
		else
		{
			n = static_cast<int> (floor(y)) - 1;  // will use n later
			y -= n;
		}

		// numerator coefficients for approximation over the interval (1,2)
		static const double p[] =
		{
			-1.71618513886549492533811E+0,
			2.47656508055759199108314E+1,
			-3.79804256470945635097577E+2,
			6.29331155312818442661052E+2,
			8.66966202790413211295064E+2,
			-3.14512729688483675254357E+4,
			-3.61444134186911729807069E+4,
			6.64561438202405440627855E+4
		};

		// denominator coefficients for approximation over the interval (1,2)
		static const double q[] =
		{
			-3.08402300119738975254353E+1,
			3.15350626979604161529144E+2,
			-1.01515636749021914166146E+3,
			-3.10777167157231109440444E+3,
			2.25381184209801510330112E+4,
			4.75584627752788110767815E+3,
			-1.34659959864969306392456E+5,
			-1.15132259675553483497211E+5
		};

		double num = 0.0;
		double den = 1.0;
		int i;

		double z = y - 1;
		for (i = 0; i < 8; i++)
		{
			num = (num + p[i])*z;
			den = den*z + q[i];
		}
		double result = num/den + 1.0;

		// Apply correction if argument was not initially in (1,2)
		if (arg_was_less_than_one)
		{
			// Use identity gamma(z) = gamma(z+1)/z
			// The variable "result" now holds gamma of the original y + 1
			// Thus we use y-1 to get back the orginal y.
			result /= (y-1.0);
		}
		else
		{
			// Use the identity gamma(z+n) = z*(z+1)* ... *(z+n-1)*gamma(z)
			for (i = 0; i < n; i++)
				result *= y++;
		}

		return result;
	}

	///////////////////////////////////////////////////////////////////////////
	// Third interval: [12, infinity)

	if (x > 171.624)
	{
		// Correct answer too large to display. Force +infinity.
		double temp = DBL_MAX;
		return temp*2.0;
	}

	return exp(lgamma(x));
}

double lgamma(double x)
{
// 	if (x <= 0.0)
// 	{
// 		return ;
// 	}

	if (x < 12.0)
	{
		return log(fabs(Gamma(x)));
	}

	// Abramowitz and Stegun 6.1.41
	// Asymptotic series should be good to at least 11 or 12 figures
	// For error analysis, see Whittiker and Watson
	// A Course in Modern Analysis (1927), page 252

	static const double c[8] =
	{
		1.0/12.0,
		-1.0/360.0,
		1.0/1260.0,
		-1.0/1680.0,
		1.0/1188.0,
		-691.0/360360.0,
		1.0/156.0,
		-3617.0/122400.0
	};
	double z = 1.0/(x*x);
	double sum = c[7];
	for (int i=6; i >= 0; i--)
	{
		sum *= z;
		sum += c[i];
	}
	double series = sum/x;

	static const double halfLogTwoPi = 0.91893853320467274178032973640562;
	double logGamma = (x - 0.5)*log(x) - x + halfLogTwoPi + series;    
	return logGamma;
}

char * strconcat( const char *s, const char *t )
{
	static char z[BUFSIZ];
	strcpy(z, s);
	strcat(z, t);
	return z;
}
