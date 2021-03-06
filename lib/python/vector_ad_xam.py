
# This file can be automatically generaeted using the following command
# m4 ../python.m4 ../xam/vector_ad_xam.m4 > vector_ad_xam.py
# -----------------------------------------------------------------------------
#         cppad_swig: A C++ Object Library and SWIG Interface to CppAD
#          Copyright (C) 2017-17 Bradley M. Bell (bradbell@seanet.com)
#              This program is distributed under the terms of the
#          GNU Affero General Public License version 3.0 or later see
#                     http://www.gnu.org/licenses/agpl.txt
# -----------------------------------------------------------------------------
# std::vector<a_double>
# -----------------------------------------------------------------------------
def vector_ad_xam() :
	#
	# load the cppad swig library
	import py_cppad
	#
	# initialize return variable
	ok = True
	n = 4
	a_vec = py_cppad.vector_ad(n)
	#
	# check size
	ok = ok and a_vec.size() == n
	#
	# setting elements
	for i in range( n  ) :
		ad = py_cppad.a_double(2.0 * i)
		a_vec[i] = ad
	#
	# getting elements
	for i in range( n  ) :
		a_element = a_vec[i]
		ok = ok and a_element.value() == 2.0 * i
	#
	return( ok )
#
