/* -----------------------------------------------------------------------------
           cppad_swig: A C++ Object Library and SWIG Interface to CppAD
            Copyright (C) 2017-17 Bradley M. Bell (bradbell@seanet.com)
                This program is distributed under the terms of the
            GNU Affero General Public License version 3.0 or later see
                       http://www.gnu.org/licenses/agpl.txt
----------------------------------------------------------------------------- */
# include "swig_example.hpp"
# include <string>
# include <limits>

// factorial_by_val
int factorial_by_val(int n) {
	if (n <= 1) return 1;
	else return n * factorial_by_val(n - 1);
}

// message_of_void
const char* message_of_void(void)
{	return "OK";
}

// add_by_ptadd_by_ptr
void add_by_ptr(int x, int y, int* result)
{	*result = x + y;
}

// max_array_ptr
int max_array_by_ptr(int n, int* x)
{	int result = x[0];
	for(int i = 1; i < 10; i++)
		if( x[i] > result )
			result = x[i];
	return result;
}

// max_std_vector_double
double max_std_vector_double(const std::vector<double>& x)
{	double result = - std::numeric_limits<double>::infinity();
	for(size_t i = 0; i < x.size(); i++)
		if( x[i] > result )
			result = x[i];
	return result;
}



// raise_exception or return previous error message
const char* raise_exception(const char* message) throw(const char*)
{	// previous error message
	static std::string previous = "";
	if( message[0] == '\0' )
		return previous.c_str();
	previous = message;
	//
	// raise exception
	throw message;
	//
	// never get to here
	return "";
}

// -----------------------------------------------------------------------
// normal_class
normal_class::normal_class(void)
{ };
normal_class::normal_class(int value) : value_(value)
{ };
// destructor
normal_class::~normal_class(void)
{ };
// value
int normal_class::value (void) const
{	return value_; }
// additon
normal_class normal_class::operator+(const normal_class& right) const
{	return normal_class( value_ + right.value_ ); }
// equality
bool normal_class::operator==(const normal_class& right) const
{	return ( value_ == right.value_ ); }
// -----------------------------------------------------------------------
