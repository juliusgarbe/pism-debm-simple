// Copyright (C) 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018 PISM Authors
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
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

#ifndef _PODSLFORCING_H_
#define _PODSLFORCING_H_

#include "pism/coupler/util/PScalarForcing.hh"
#include "pism/coupler/OceanModel.hh"

namespace pism {
namespace ocean {
class Delta_SL : public PScalarForcing<OceanModel,OceanModel>
{
public:
  Delta_SL(IceGrid::ConstPtr g, std::shared_ptr<OceanModel> in);
  virtual ~Delta_SL();

private:

  typedef PScalarForcing<OceanModel,OceanModel> super;

  void init_impl();
  void update_impl(double t, double dt);
  const IceModelVec2S& sea_level_elevation_impl() const;

  IceModelVec2S::Ptr m_sea_level_elevation;
};

} // end of namespace ocean
} // end of namespace pism
#endif /* _PODSLFORCING_H_ */
