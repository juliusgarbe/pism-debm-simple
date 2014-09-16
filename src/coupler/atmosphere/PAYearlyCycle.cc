// Copyright (C) 2008-2014 Ed Bueler, Constantine Khroulev, Ricarda Winkelmann,
// Gudfinna Adalgeirsdottir and Andy Aschwanden
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

// Implementation of the atmosphere model using constant-in-time precipitation
// and a cosine yearly cycle for near-surface air temperatures.

#include "PAYearlyCycle.hh"
#include "PISMTime.hh"
#include "IceGrid.hh"
#include "PISMConfig.hh"

namespace pism {

PAYearlyCycle::PAYearlyCycle(IceGrid &g, const Config &conf)
  : AtmosphereModel(g, conf), m_air_temp_snapshot(g.get_unit_system()) {
  PetscErrorCode ierr = allocate_PAYearlyCycle(); CHKERRCONTINUE(ierr);
  if (ierr != 0)
    PISMEnd();

}

PAYearlyCycle::~PAYearlyCycle() {
  // empty
}

PetscErrorCode PAYearlyCycle::allocate_PAYearlyCycle() {
  PetscErrorCode ierr;

  m_snow_temp_july_day = config.get("snow_temp_july_day");

  // Allocate internal IceModelVecs:
  ierr = m_air_temp_mean_annual.create(grid, "air_temp_mean_annual", WITHOUT_GHOSTS); CHKERRQ(ierr);
  ierr = m_air_temp_mean_annual.set_attrs("diagnostic",
                           "mean annual near-surface air temperature (without sub-year time-dependence or forcing)",
                           "K", 
                           ""); CHKERRQ(ierr);  // no CF standard_name ??
  m_air_temp_mean_annual.metadata().set_string("source", m_reference);

  ierr = m_air_temp_mean_july.create(grid, "air_temp_mean_july", WITHOUT_GHOSTS); CHKERRQ(ierr);
  ierr = m_air_temp_mean_july.set_attrs("diagnostic",
                           "mean July near-surface air temperature (without sub-year time-dependence or forcing)",
                           "Kelvin",
                           ""); CHKERRQ(ierr);  // no CF standard_name ??
  m_air_temp_mean_july.metadata().set_string("source", m_reference);

  ierr = m_precipitation.create(grid, "precipitation", WITHOUT_GHOSTS); CHKERRQ(ierr);
  ierr = m_precipitation.set_attrs("climate_state", 
                              "mean annual ice-equivalent precipitation rate",
                              "m s-1", 
                              ""); CHKERRQ(ierr); // no CF standard_name ??
  ierr = m_precipitation.set_glaciological_units("m year-1");
  m_precipitation.write_in_glaciological_units = true;
  m_precipitation.set_time_independent(true);

  m_air_temp_snapshot.init_2d("air_temp_snapshot", grid);
  m_air_temp_snapshot.set_string("pism_intent", "diagnostic");
  m_air_temp_snapshot.set_string("long_name",
                         "snapshot of the near-surface air temperature");
  ierr = m_air_temp_snapshot.set_units("K"); CHKERRQ(ierr);

  return 0;
}

//! Allocates memory and reads in the precipitaion data.
PetscErrorCode PAYearlyCycle::init(Vars &vars) {
  m_t = m_dt = GSL_NAN;  // every re-init restarts the clock

  m_variables = &vars;

  bool do_regrid = false;
  int start = -1;
  PetscErrorCode ierr = find_pism_input(m_precip_filename, do_regrid, start); CHKERRQ(ierr);

  ierr = init_internal(m_precip_filename, do_regrid, start); CHKERRQ(ierr);

  return 0;
}

//! Read precipitation data from a given file.
PetscErrorCode PAYearlyCycle::init_internal(const std::string &input_filename, bool do_regrid,
                                            unsigned int start) {
  // read precipitation rate from file
  PetscErrorCode ierr = verbPrintf(2, grid.com,
                    "    reading mean annual ice-equivalent precipitation rate 'precipitation'\n"
                    "      from %s ... \n",
                    input_filename.c_str()); CHKERRQ(ierr);
  if (do_regrid == true) {
    ierr = m_precipitation.regrid(input_filename, CRITICAL); CHKERRQ(ierr); // fails if not found!
  } else {
    ierr = m_precipitation.read(input_filename, start); CHKERRQ(ierr); // fails if not found!
  }

  return 0;
}

void PAYearlyCycle::add_vars_to_output(const std::string &keyword, std::set<std::string> &result) {
  result.insert("precipitation");

  if (keyword == "big") {
    result.insert("air_temp_mean_annual");
    result.insert("air_temp_mean_july");
    result.insert("air_temp_snapshot");
  }
}


PetscErrorCode PAYearlyCycle::define_variables(const std::set<std::string> &vars, const PIO &nc, IO_Type nctype) {
  PetscErrorCode ierr;

  if (set_contains(vars, "air_temp_snapshot")) {
    ierr = m_air_temp_snapshot.define(nc, nctype, false); CHKERRQ(ierr);
  }

  if (set_contains(vars, "air_temp_mean_annual")) {
    ierr = m_air_temp_mean_annual.define(nc, nctype); CHKERRQ(ierr);
  }

  if (set_contains(vars, "air_temp_mean_july")) {
    ierr = m_air_temp_mean_july.define(nc, nctype); CHKERRQ(ierr);
  }

  if (set_contains(vars, "precipitation")) {
    ierr = m_precipitation.define(nc, nctype); CHKERRQ(ierr);
  }

  return 0;
}


PetscErrorCode PAYearlyCycle::write_variables(const std::set<std::string> &vars, const PIO &nc) {
  PetscErrorCode ierr;

  if (set_contains(vars, "air_temp_snapshot")) {
    IceModelVec2S tmp;
    ierr = tmp.create(grid, "air_temp_snapshot", WITHOUT_GHOSTS); CHKERRQ(ierr);
    tmp.metadata() = m_air_temp_snapshot;

    ierr = temp_snapshot(tmp); CHKERRQ(ierr);

    ierr = tmp.write(nc); CHKERRQ(ierr);
  }

  if (set_contains(vars, "air_temp_mean_annual")) {
    ierr = m_air_temp_mean_annual.write(nc); CHKERRQ(ierr);
  }

  if (set_contains(vars, "air_temp_mean_july")) {
    ierr = m_air_temp_mean_july.write(nc); CHKERRQ(ierr);
  }

  if (set_contains(vars, "precipitation")) {
    ierr = m_precipitation.write(nc); CHKERRQ(ierr);
  }

  return 0;
}

//! Copies the stored precipitation field into result.
PetscErrorCode PAYearlyCycle::mean_precipitation(IceModelVec2S &result) {
  PetscErrorCode ierr;
  ierr = m_precipitation.copy_to(result); CHKERRQ(ierr);
  return 0;
}

//! Copies the stored mean annual near-surface air temperature field into result.
PetscErrorCode PAYearlyCycle::mean_annual_temp(IceModelVec2S &result) {
  PetscErrorCode ierr;
  ierr = m_air_temp_mean_annual.copy_to(result); CHKERRQ(ierr);
  return 0;
}

PetscErrorCode PAYearlyCycle::init_timeseries(const std::vector<double> &ts) {
  // constants related to the standard yearly cycle
  const double
    julyday_fraction = grid.time->day_of_the_year_to_day_fraction(m_snow_temp_july_day);

  size_t N = ts.size();

  m_ts_times.resize(N);
  m_cosine_cycle.resize(N);
  for (unsigned int k = 0; k < m_ts_times.size(); k++) {
    double tk = grid.time->year_fraction(ts[k]) - julyday_fraction;

    m_ts_times[k] = ts[k];
    m_cosine_cycle[k] = cos(2.0 * M_PI * tk);
  }

  return 0;
}

PetscErrorCode PAYearlyCycle::precip_time_series(int i, int j, std::vector<double> &result) {
  for (unsigned int k = 0; k < m_ts_times.size(); k++)
    result[k] = m_precipitation(i,j);
  return 0;
}

PetscErrorCode PAYearlyCycle::temp_time_series(int i, int j, std::vector<double> &result) {

  for (unsigned int k = 0; k < m_ts_times.size(); ++k) {
    result[k] = m_air_temp_mean_annual(i,j) + (m_air_temp_mean_july(i,j) - m_air_temp_mean_annual(i,j)) * m_cosine_cycle[k];
  }

  return 0;
}

PetscErrorCode PAYearlyCycle::temp_snapshot(IceModelVec2S &result) {
  PetscErrorCode ierr;

  const double
    julyday_fraction = grid.time->day_of_the_year_to_day_fraction(m_snow_temp_july_day),
    T                = grid.time->year_fraction(m_t + 0.5 * m_dt) - julyday_fraction,
    cos_T            = cos(2.0 * M_PI * T);

  ierr = result.begin_access(); CHKERRQ(ierr);
  ierr = m_air_temp_mean_annual.begin_access(); CHKERRQ(ierr);
  ierr = m_air_temp_mean_july.begin_access(); CHKERRQ(ierr);

  for (Points p(grid); p; p.next()) {
    const int i = p.i(), j = p.j();
    result(i,j) = m_air_temp_mean_annual(i,j) + (m_air_temp_mean_july(i,j) - m_air_temp_mean_annual(i,j)) * cos_T;
  }

  ierr = m_air_temp_mean_july.end_access(); CHKERRQ(ierr);
  ierr = m_air_temp_mean_annual.end_access(); CHKERRQ(ierr);
  ierr = result.end_access(); CHKERRQ(ierr);

  return 0;
}

PetscErrorCode PAYearlyCycle::begin_pointwise_access() {
  PetscErrorCode ierr;

  ierr = m_air_temp_mean_annual.begin_access(); CHKERRQ(ierr);
  ierr = m_air_temp_mean_july.begin_access(); CHKERRQ(ierr);
  ierr = m_precipitation.begin_access(); CHKERRQ(ierr);

  return 0;
}

PetscErrorCode PAYearlyCycle::end_pointwise_access() {
  PetscErrorCode ierr;

  ierr = m_air_temp_mean_annual.end_access(); CHKERRQ(ierr);
  ierr = m_air_temp_mean_july.end_access(); CHKERRQ(ierr);
  ierr = m_precipitation.end_access(); CHKERRQ(ierr);

  return 0;
}


} // end of namespace pism
