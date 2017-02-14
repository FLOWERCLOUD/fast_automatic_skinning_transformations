// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "is_symmetric.h"
#include "find.h"

template <typename T>
IGL_INLINE bool igl::is_symmetric(const Eigen::SparseMatrix<T>& A)
{
  if(A.rows() != A.cols())
  {
    return false;
  }
  assert(A.size() != 0);
  Eigen::SparseMatrix<T> AT = A.transpose();
  Eigen::SparseMatrix<T> AmAT = A-AT;
  //// Eigen screws up something with LLT if you try to do
  //SparseMatrix<T> AmAT = A-A.transpose();
  //// Eigen crashes at runtime if you try to do
  // return (A-A.transpose()).nonZeros() == 0;
  return AmAT.nonZeros() == 0;
}

template <typename DerivedA>
IGL_INLINE bool igl::is_symmetric(
	const Eigen::PlainObjectBase<DerivedA>& A)
{
	if (A.rows() != A.cols())
	{
		return false;
	}
	assert(A.size() != 0);
	//const typename Eigen::PlainObjectBase<DerivedA>& AT = A.transpose();
	//Eigen::PlainObjectBase<DerivedA>& AT = 
	auto AT = A.transpose();
	//  const typename Eigen::PlainObjectBase<DerivedA>& AmAT = A-AT;
	auto AmAT = A - AT;
	//// Eigen screws up something with LLT if you try to do
	//SparseMatrix<T> AmAT = A-A.transpose();
	//// Eigen crashes at runtime if you try to do
	// return (A-A.transpose()).nonZeros() == 0;
	return AmAT.nonZeros() == 0;
}

template <typename AType, typename epsilonT>
IGL_INLINE bool igl::is_symmetric(
  const Eigen::SparseMatrix<AType>& A, 
  const epsilonT epsilon)
{
  using namespace Eigen;
  using namespace std;
  if(A.rows() != A.cols())
  {
    return false;
  }
  assert(A.size() != 0);
  SparseMatrix<AType> AT = A.transpose();
  SparseMatrix<AType> AmAT = A-AT;
  VectorXi AmATI,AmATJ;
  Matrix<AType,Dynamic,1> AmATV;
  find(AmAT,AmATI,AmATJ,AmATV);
  if(AmATI.size() == 0)
  {
    return true;
  }
  
  return AmATV.maxCoeff() < epsilon && AmATV.minCoeff() > -epsilon;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template bool igl::is_symmetric<Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&);
// generated by autoexplicit.sh
template bool igl::is_symmetric<double>(Eigen::SparseMatrix<double, 0, int> const&);
template bool igl::is_symmetric<double, double>(Eigen::SparseMatrix<double, 0, int> const&, double);
template bool igl::is_symmetric<double, int>(Eigen::SparseMatrix<double, 0, int> const&, int);
#endif
