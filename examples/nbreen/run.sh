#!/bin/bash

GRIDLIST="{500, 250, 125, 62}"
TYPELIST="{dist, event, routing}"

if [ $# -lt 4 ] ; then
  echo "run.sh ERROR: needs five arguments ... ENDING NOW"
  echo "  format:"
  echo "    run.sh PROCS GRID DURATION TYPE REPORTING"
  echo "  where"
  echo "    PROCS     = 1,2,3,... is number of MPI processes"
  echo "    GRID      is in $GRIDLIST, the grid spacing in meters"
  echo "    DURATION  is run duration in years"
  echo "    TYPE      is in $TYPELIST"
  echo "    REPORTING is either a Delta t in years or in {hourly, daily, monthly, yearly}"
  echo "  example usage:"
  echo "    run.sh 4 500 0.25 dist daily"
  echo "  is a run with 4 processors, 500 m grid, 3 model month run,"
  echo "  using '-hydrology distributed', and with daily reporting"
  exit
fi

NN="$1"

if [ "$2" -eq "500" ]; then
  dx=500
  dtmax=0.1
  myMx=67
  myMy=52
elif [ "$2" -eq "250" ]; then
  dx=250
  dtmax=0.1
  myMx=133
  myMy=104
elif [ "$2" -eq "125" ]; then
  dx=125
  dtmax=0.01  # more frequent just because so many hydrology substeps occur
  myMx=264
  myMy=207
elif [ "$2" -eq "62" ]; then
  echo ""
  echo "WARNING: 62 m run is computationally intensive; may exceed 100 proc.-hours"
  echo ""
  dx=62
  dtmax=0.01  # more frequent just because so many hydrology substeps occur
  myMx=528
  myMy=414
else
  echo "invalid second argument: must be in $GRIDLIST"
  exit
fi

YY="$3"

DT="$5"

etimes="0:$DT:$YY"

# these extra_ diagnostics apply to "dist" and "event":
evarlist="thk,cbase,bmelt,hydroinput,bwat,bwp,bwatvel,bwprel,effbwp,enwat,wallmelt"

if [ "$4" = "dist" ]; then

  # distributed run
  oname=nbreen_y${YY}_${dx}m_dist.nc
  hydro="-hydrology distributed -hydrology_null_strip 1.0 -report_mass_accounting -ssa_sliding -ssa_dirichlet_bc"

elif [ "$4" = "event" ]; then

  # distributed run with summer event
  oname=nbreen_y${YY}_${dx}m_event.nc
  hydro="-hydrology distributed -hydrology_null_strip 1.0 -report_mass_accounting -ssa_sliding -ssa_dirichlet_bc -input_to_bed_file fakesummerevent.nc -input_to_bed_period 1.0 -input_to_bed_reference_year 0.0"

elif [ "$4" = "routing" ]; then

  # routing run: very fast
  oname=nbreen_y${YY}_${dx}m_routing.nc
  hydro="-hydrology routing -hydrology_null_strip 1.0 -report_mass_accounting -hydrology_hydraulic_conductivity_at_large_W 1.0e-3"
  evarlist="thk,bmelt,hydroinput,bwat,bwp,bwatvel,wallmelt"  # revised

else
  echo "invalid fourth argument; must be in $TYPELIST"
  exit
fi

pismexec="pismr"

data=pismnbreen.nc

grid="-Mx $myMx -My $myMy -Mz 11 -z_spacing equal -Lz 600"

climate="-surface given -surface_given_file $data"

physics="-config_override nbreen_config.nc -no_mass -no_energy"

diagnostics="-extra_file extras_$oname -extra_times $etimes -extra_vars $evarlist"

mpiexec -n $NN $pismexec -boot_file $data $climate $physics $hydro \
    $grid -max_dt $dtmax -ys 0.0 -y $YY $diagnostics -o $oname
