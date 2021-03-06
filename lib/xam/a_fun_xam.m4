header_(a_fun_xam)
c_ -----------------------------------------------------------------------------
c_         cppad_swig: A C++ Object Library and SWIG Interface to CppAD
c_          Copyright (C) 2017-17 Bradley M. Bell (bradbell@seanet.com)
c_              This program is distributed under the terms of the
c_          GNU Affero General Public License version 3.0 or later see
c_                     http://www.gnu.org/licenses/agpl.txt
c_ -----------------------------------------------------------------------------
c_ std::vector<a_double>
c_ -----------------------------------------------------------------------------
begin_bool_fun_0_(ok, a_fun_xam)
	new_var_(n, 2)
	new_var_(m, 1)
	c_
	c_ create ax
	new_var_new_(x, module_fun_1_(vector_double, n))
	begin_for_(i, var_(n) )
		vec_set_(x, var_(i), var_(i) + 1.0)
	new_var_(ax, module_fun_1_(independent, x))
	c_
	c_ create af
	new_var_(ax0, vec_get_(ax, 0))
	new_var_(ax1, vec_get_(ax, 1))
	new_var_new_(ay, module_fun_1_(vector_ad, 1))
	vec_set_(ay, 0, var_(ax0) + var_(ax0) - var_(ax1))
	new_var_new_(af, module_fun_2_(a_fun, var_(ax), var_(ay)))
	c_
	c_ zero order forward
	vec_set_(x, 0, 3.0)
	vec_set_(x, 1, 1.0)
	new_var_(y, member_fun_2_(af, forward, 0, var_(x)))
	and_assign_(ok, vec_get_(y, 0) == 5.0)
	c_
	c_ first order forward
	vec_set_(x, 0, 0.0)
	vec_set_(x, 1, 1.0)
	assign_(y, member_fun_2_(af, forward, 1, var_(x)))
	and_assign_(ok, vec_get_(y, 0) == -1.0)
	c_
	return_(var_(ok))
end_
