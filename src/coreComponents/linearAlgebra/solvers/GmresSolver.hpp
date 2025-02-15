/*
 * ------------------------------------------------------------------------------------------------------------
 * SPDX-License-Identifier: LGPL-2.1-only
 *
 * Copyright (c) 2018-2020 Lawrence Livermore National Security LLC
 * Copyright (c) 2018-2020 The Board of Trustees of the Leland Stanford Junior University
 * Copyright (c) 2018-2020 TotalEnergies
 * Copyright (c) 2019-     GEOSX Contributors
 * All rights reserved
 *
 * See top level LICENSE, COPYRIGHT, CONTRIBUTORS, NOTICE, and ACKNOWLEDGEMENTS files for details.
 * ------------------------------------------------------------------------------------------------------------
 */

/**
 * @file GmresSolver.hpp
 */

#ifndef GEOS_LINEARALGEBRA_SOLVERS_GMRESSOLVER_HPP_
#define GEOS_LINEARALGEBRA_SOLVERS_GMRESSOLVER_HPP_

#include "linearAlgebra/solvers/KrylovSolver.hpp"

namespace geos
{

/**
 * @brief This class implements Generalized Minimized RESidual method
 *        (right-preconditioned) for monolithic and block linear operators.
 * @tparam VECTOR type of vectors this solver operates on.
 * @note  The notation is consistent with "Iterative Methods for
 *        Linear and Non-Linear Equations" from C.T. Kelley (1995)
 *        and "Iterative Methods for Sparse Linear Systems"
 *        from Y. Saad (2003).
 */
template< typename VECTOR >
class GmresSolver : public KrylovSolver< VECTOR >
{
public:

  /// Alias for the base type
  using Base = KrylovSolver< VECTOR >;

  /// Alias for the vector type
  using Vector = typename Base::Vector;

  /**
   * @name Constructor/Destructor Methods
   */
  ///@{

  /**
   * @brief Solver object constructor.
   * @param[in] params  parameters for the solver
   * @param[in] matrix  reference to the system matrix
   * @param[in] precond reference to the preconditioning operator
   */
  GmresSolver( LinearSolverParameters params,
               LinearOperator< Vector > const & matrix,
               LinearOperator< Vector > const & precond );

  ///@}

  /**
   * @name KrylovSolver interface
   */
  ///@{

  /**
   * @brief Solve preconditioned system
   * @param [in] b system right hand side.
   * @param [inout] x system solution (input = initial guess, output = solution).
   */
  virtual void solve( Vector const & b, Vector & x ) const override final;

  virtual string methodName() const override final
  {
    return "GMRES";
  };

  ///@}

protected:

  /// Alias for vector type that can be used for temporaries
  using VectorTemp = typename KrylovSolver< VECTOR >::VectorTemp;

  using Base::m_params;
  using Base::m_operator;
  using Base::m_precond;
  using Base::m_residualNorms;
  using Base::m_result;
  using Base::createTempVector;
  using Base::logProgress;
  using Base::logResult;

  /// Storage for Krylov subspace vectors
  array1d< VectorTemp > m_kspace;

  /// Flag indicating whether kspace vectors have been created
  bool mutable m_kspaceInitialized;
};

} // namespace geos

#endif //GEOS_LINEARALGEBRA_SOLVERS_GMRESSOLVER_HPP_
