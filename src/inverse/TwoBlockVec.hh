// Copyright (C) 2012  David Maxwell
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// PISM is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with PISM; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef TWOBLOCKVEC_HH_51CJ6YY0
#define TWOBLOCKVEC_HH_51CJ6YY0

#include <petsc.h>

class TwoBlockVec {
public:
  TwoBlockVec(Vec a, Vec b);
  ~TwoBlockVec();

  IS blockAIndexSet();
  IS blockBIndexSet();

  PetscErrorCode scatter(Vec a, Vec b);
  PetscErrorCode scatterToA(Vec a);
  PetscErrorCode scatterToB(Vec b);

  PetscErrorCode scatter(Vec ab, Vec a, Vec b);
  PetscErrorCode scatterToA(Vec ab, Vec a);
  PetscErrorCode scatterToB(Vec ab, Vec b);

  PetscErrorCode gather(Vec a, Vec b);
  PetscErrorCode gatherFromA(Vec a);
  PetscErrorCode gatherFromB(Vec b);

  PetscErrorCode gather(Vec a, Vec b, Vec ab);
  PetscErrorCode gatherFromA(Vec a, Vec ab);
  PetscErrorCode gatherFromB(Vec b, Vec ab);

  operator Vec &() {
    return m_ab;
  }

protected:
  PetscErrorCode construct(Vec a, Vec b);
  PetscErrorCode destruct();

  Vec m_ab;
  
  PetscInt m_na_local, m_na_global, m_nb_local, m_nb_global;
  
  IS m_a_in_ab;
  IS m_b_in_ab;
  
  VecScatter m_scatter_a;
  VecScatter m_scatter_b;
};

#endif /* end of include guard: TWOBLOCKVEC_HH_51CJ6YY0 */
