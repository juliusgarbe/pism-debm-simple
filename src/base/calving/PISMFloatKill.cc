/* Copyright (C) 2013, 2014 PISM Authors
 *
 * This file is part of PISM.
 *
 * PISM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * PISM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PISM; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "PISMFloatKill.hh"
#include "Mask.hh"
#include "iceModelVec.hh"

namespace pism {

FloatKill::FloatKill(IceGrid &g, const Config &conf)
  : Component(g, conf) {
  // empty
}

FloatKill::~FloatKill() {
  // empty
}

PetscErrorCode FloatKill::init(Vars &/*vars*/) {
  PetscErrorCode ierr;
  ierr = verbPrintf(2, grid.com,
                    "* Initializing the 'calving at the grounding line' mechanism...\n");
  CHKERRQ(ierr);
  return 0;
}

/**
 * Updates ice cover mask and the ice thickness using the calving rule
 * removing all floating ice.
 *
 * @param[in,out] pism_mask ice cover (cell type) mask
 * @param[in,out] ice_thickness ice thickness
 *
 * @return 0 on success
 */
PetscErrorCode FloatKill::update(IceModelVec2Int &pism_mask, IceModelVec2S &ice_thickness) {
  PetscErrorCode ierr;
  MaskQuery M(pism_mask);

  ierr = pism_mask.begin_access();     CHKERRQ(ierr);
  ierr = ice_thickness.begin_access(); CHKERRQ(ierr);
  for (Points p(grid); p; p.next()) {
    const int i = p.i(), j = p.j();
    if (M.floating_ice(i, j)) {
      ice_thickness(i, j) = 0.0;
      pism_mask(i, j)     = MASK_ICE_FREE_OCEAN;
    }
  }
  ierr = ice_thickness.end_access(); CHKERRQ(ierr);
  ierr = pism_mask.end_access();     CHKERRQ(ierr);

  ierr = pism_mask.update_ghosts();     CHKERRQ(ierr);
  ierr = ice_thickness.update_ghosts(); CHKERRQ(ierr);
  return 0;
}

void FloatKill::add_vars_to_output(const std::string &/*keyword*/,
                                       std::set<std::string> &/*result*/) {
  // empty
}

PetscErrorCode FloatKill::define_variables(const std::set<std::string> &/*vars*/, const PIO &/*nc*/,
                                               IO_Type /*nctype*/) {
  // empty
  return 0;
}

PetscErrorCode FloatKill::write_variables(const std::set<std::string> &/*vars*/, const PIO& /*nc*/) {
  // empty
  return 0;
}

} // end of namespace pism
