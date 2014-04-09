/*
 * entropy.h
 *
 *  Created on: Mar 27, 2014
 *      Author: vlad
 */

#ifndef ENTROPY_H_
#define ENTROPY_H_

#include <cmath>
#include "types.h"
#include "functions.h"
#include "internal.h"
#include "exception.h"

// various entropies

namespace qpp
{

// Shannon/von-Neumann entropy
template<typename Derived>
double shannon(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("shannon", Exception::Type::ZERO_SIZE);

	// input is a vector
	if (rA.rows() == 1 || rA.cols() == 1)
	{
		double result = 0;
		// take the absolut values of the entries
		// to get rid of unwanted imaginary parts
		for (size_t i = 0; i < static_cast<size_t>(rA.size()); i++)
			if (std::abs(rA(i)) != 0) // not identically zero
				result -= std::abs(rA(i)) * std::log2(std::abs(rA(i)));

		return result;
	}

	// input is a matrix

	// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("shannon", Exception::Type::MATRIX_NOT_SQUARE);

	// get the eigenvalues
	types::cmat ev = evals(rA);
	double result = 0;
	// take the absolut values of the entries
	// to get rid of unwanted imaginary parts
	for (size_t i = 0; i < static_cast<size_t>(ev.rows()); i++)
		if (std::abs((types::cplx) ev(i)) != 0) // not identically zero
			result -= std::abs((types::cplx) ev(i))
					* std::log2(std::abs((types::cplx) ev(i)));

	return result;
}

// Renyi-alpha entropy (alpha>=0)
template<typename Derived>
double renyi(const double alpha, const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	if (alpha < 0)
		throw Exception("renyi", Exception::Type::OUT_OF_RANGE);

	if (alpha == 1) // Shannon/von Neumann
		return shannon(rA);

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("renyi", Exception::Type::ZERO_SIZE);

	// input is a vector
	if (rA.rows() == 1 || rA.cols() == 1)
	{
		if (alpha == 0)
			return std::log2(rA.size());

		double result = 0;
		// take the absolut values of the entries
		// to get rid of unwanted imaginary parts
		for (size_t i = 0; i < static_cast<size_t>(rA.size()); i++)
			if (std::abs((types::cplx) rA(i)) != 0) // not identically zero
				result += std::pow(std::abs(rA(i)), alpha);

		return std::log2(result) / (1 - alpha);
	}

	// input is a matrix

	// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("renyi", Exception::Type::MATRIX_NOT_SQUARE);

	if (alpha == 0)
		return std::log2(rA.rows());

	// get the eigenvalues
	types::cmat ev = evals(rA);
	double result = 0;
	// take the absolut values of the entries
	// to get rid of unwanted imaginary parts
	for (size_t i = 0; i < static_cast<size_t>(ev.rows()); i++)
		if (std::abs((types::cplx) ev(i)) != 0) // not identically zero
			result += std::pow(std::abs((types::cplx) ev(i)), alpha);

	return std::log2(result) / (1 - alpha);
}

// Renyi-infinity entropy (min entropy)
template<typename Derived>
double renyi_inf(const Eigen::MatrixBase<Derived>& A)
{
	const types::DynMat<typename Derived::Scalar> & rA = A;

	// check zero-size
	if (!internal::_check_nonzero_size(rA))
		throw Exception("renyi_inf", Exception::Type::ZERO_SIZE);

	// input is a vector
	if (rA.rows() == 1 || rA.cols() == 1)
	{
		double max = 0;
		for (size_t i = 0; i < static_cast<size_t>(rA.size()); i++)
			if (std::abs(rA(i)) > max)
				max = std::abs(rA(i));

		return -std::log2(max);
	}

	// input is a matrix

	// check square matrix
	if (!internal::_check_square_mat(rA))
		throw Exception("renyi_inf", Exception::Type::MATRIX_NOT_SQUARE);

	// get the eigenvalues
	types::cmat ev = evals(rA);
	double max = 0;
	// take the absolut values of the entries
	// to get rid of unwanted imaginary parts
	for (size_t i = 0; i < static_cast<size_t>(ev.size()); i++)
		if (std::abs((types::cplx) ev(i)) > max)
			max = std::abs((types::cplx) ev(i));

	return -std::log2(max);
}

} /* namespace qpp */
#endif /* ENTROPY_H_ */
