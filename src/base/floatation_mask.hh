/* Copyright (C) 2016 PISM Authors
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

#ifndef _FLOATATION_MASK_H_
#define _FLOATATION_MASK_H_

namespace pism {

class IceModelVec2S;
class IceModelVec2Int;

void compute_floatation_mask(double ice_density,
                             double ocean_density,
                             double sea_level,
                             const IceModelVec2S &ice_thickness,
                             const IceModelVec2S &bed_topography,
                             const IceModelVec2Int &mask,
                             IceModelVec2S &result);

} // end of namespace pism


#endif /* _FLOATATION_MASK_H_ */
