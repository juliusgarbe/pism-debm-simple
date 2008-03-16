// THE ONLY PURPOSE OF THIS FILE IS TO BE A LOCATION FOR MAJOR SOURCE CODE COMMENTS.
// IT NEEDS TO BE A .hh (OR OTHER STANDARD SOURCE TYPE) AND IT NEEDS TO BE IN THE
// pism/src/ TREE SO THAT doxygen WILL AUTOMATICALLY READ IT.


// add commentary and GPL to first page of doxygen-erated HTML source browser
/*! @cond BROWSER \mainpage 
 *
 * This source browser shows the C++ class (object) structure of PISM.  It 
 * shows \em all the classes in PISM, \em all the inheritance structure and
 * \em all the members (variables and methods) of all the PISM classes.  
 * It was automatically generated by doxygen (http://www.doxygen.org/)
 * from comments in the PISM source code.
 *
 * See https://gna.org/projects/pism/ to download the PISM source code.  See 
 * http://www.pism-docs.org/ for all documentation of PISM.
 *
 * See the PISM <i>User's Manual</i> (do <tt>cd doc/ && make</tt> and then view 
 * <tt>pism/doc/manual.pdf</tt>, or see the stable version at
 * http://www.pism-docs.org/manual.pdf) for help
 * with installing and using PISM.  
 * Most users should stick to the User's Manual for quite a while; only when 
 * a user needs to extend PISM is a look at this source browser really 
 * worthwhile.
 *
 * See the PISM <i>Reference Manual</i> (do <tt>cd doc/ && make</tt> and then view 
 * <tt>pism/doc/refman.pdf</tt>, or see the stable version at 
 * http://www.pism-docs.org/refman.pdf)
 * for a useful subset of this source browser
 * in PDF form.  The <i>Reference Manual</i> contains the minimum documentation 
 * of the PISM class structure in order to document 
 * the continuum models and numerical methods of PISM.  (Such continuum model
 * and numerical method documentation is widely scattered in this source browser.)
 *
 * There is also a source code <i>repository</i> browsing tool at the PISM download site
 * (https://gna.org/projects/pism/).  That tool is very different from this one.  This one
 * documents the C++ class structure of the current revision.  The one at gna.org
 * shows changes between revisions but it ignors the class structure as it only cares 
 * about source code files as text files and generally ignors their semantics.
 *
 * <i>
 * Copyright (C) 2008 Ed Bueler
 *
 * This document is part of PISM.
 *
 * PISM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
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
 * </i>
 * @endcond
 */
 

// add commentary and GPL to first page of doxygen-erated PDF Reference Manual
/*! @cond REFMAN \mainpage


\e Author:  Ed Bueler

 
\section purposeID Purpose, and relation to the User's Manual

This \e Reference \e Manual documents the continuum models and numerical
methods in PISM.  It is organized by C++ class.  

This \e Reference \e Manual can be built in any source code release.  Just do
<tt>cd doc/ && make</tt> and then view <tt>refman.pdf</tt>

Most users should start with the PISM <i>User's Manual</i>.  The latest
stable version of the <i>User's Manual</i> is at
 
      http://www.pism-docs.org/manual.pdf  

The <i>User's Manual</i> is also in any source code release.  Just do
<tt>cd doc/ && make</tt> and then view <tt>manual.pdf</tt>

The <i>User's Manual</i> is the guide to installing and using PISM.  
Really smart know-it-all developers
should \e also see the <i>User's Manual</i> before getting too far into this 
<i>Reference Manual</i>.

This <i>Reference Manual</i> is a greatly shortened version of an HTML
source code browser.  That browser can be generated from a copy of the PISM source by 
<tt>cd pism/doc/ && make</tt> .  Then use a web browser like Firefox to view
\c pism/doc/doxy/html/index.html .
 
This \e Reference \e Manual was automatically generated by doxygen

      http://www.doxygen.org/

from comments in the PISM source code.  Most of the source files from 
which this \e Reference \e Manual was created are in the <tt>pism/src/base/</tt> 
subdirectory.  Only those parts of the source with 
doxygen-formatted comments are documented here.  (By contrast, the source 
code browser described above includes all the classes, class members, 
and source files in PISM.)

 
\section gnuID GNU Public License

<i>
Copyright (C) 2008 Ed Bueler

This document is part of PISM.

PISM is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

PISM is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License
along with PISM; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA 
</i>

 
\section pismsourceID Classes in the PISM source code

\subsection overviewID Overview

PISM is implemented as a collection of C++ object classes.  There are five basic 
classes to know about, the sources for each of which are in \c pism/src/base/:
  - IceGrid.  Describes the computational box and grid, and the parallel layout
    of the grid.  For instance, which processor owns which part of the grid is stored in an
    instance of IceGrid.
  - IceModel.  Contains myriad data structures, flags, PETSc \c Vecs (below), and 
    most of the numerical methods of PISM.  The most important class.  An instance of 
    IceModel has data members including an instance of IceGrid, many instances of IceModelVec,
    many instances of MaterialType, and an instance of NCTool. 
  - IceModelVec.  Abstracts the idea of a scalar field distributed across the PISM grid.  Elements of 
       this class can read and write themselves to NetCDF files, for instance.  The three dimensional 
       case, the derived class \c IceModelVec3, can hand back a requested column or stencil, for instance.
  - MaterialType.  Various materials are derived from the class \c MaterialType which merely defines 
       a couple of physical constants.  \c IceType is a derived class, but still an abstract class.  It \
       defines the physical properties of ice as a material.  Concrete classes derived from \c IceType
       are \c ThermoGlenIce (which uses the EISMINT constants) and \c GKIce as well as \c HybridIce, 
       which implements the Goldsby-Kohlstedt flow law \lo\cite{GoldsbyKohlstedt}\elo.  \lo\footnote{Actually, it is 
       difficult or impossible to implement a complete Goldsby-Kohlstedt \c IceType because the effective
       viscosity (inverse) form of the constitutive relation is required for computation of SSA velocity 
       fields. \c HybridIce is Goldsby-Kohlstedt ice in SIA regions and Glen ice in other regions.}\elo
       There is a basal material type \c BasalType which can be plastic or linearly viscous.  Similarly, 
       there are \c BedrockType and \c OceanType types which define associated physical constants.
  - NCTool.  Collects the methods which read and write and regrid the actual PETSc 
    \c Vecs in PISM.  These methods do nontrivial parallel data transfers.

Additional classes are \c Data1D and \c LocalInterpCtx, among others.
 
\subsection icemodelID Description of IceModel

The methods for \c IceModel are many.  In addition to numerics, they initialize the model 
from input data files.  (Note several derived classes of \c IceModel initialize from 
formulas describing simplified geometry experiments or exact solutions.)  The methods
in \c IceModel read user options, allocate arrays in a distributed manner under PETSc, 
control diagnostic viewers, run the adaptive time-stepping mechanism, report the state 
of PISM to the user, and write out the model state to files.

A derived class of \c IceModel called \c IceCompModel is used for verification.  It has additional 
structures which allow compensatory sources and compute initial conditions from, and errors relative to,
known exact solutions \lo\cite{BLKCB,BBL,BB}\elo.  Another derived class used for verification is 
\c IceExactSSAModel, which implements the exact solution described in \lo\cite{SchoofStream}\elo.

Other derived classes of \c IceModel are \c IceEISModel, \c IceGRNModel, and \c IceROSSModel.  
These correspond to the EISMINT II simplified geometry experiments \lo\cite{EISMINT00}\elo, and the 
EISMINT-Greenland ice sheet and EISMINT-Ross ice shelf models described in the \e User's \e Manual.

There are five established drivers which just call constructors and destructors for an instance 
of \c IceModel, or a derived class thereof, and tell the instance to run itself.  These are in the 
source files \c pgrn.cc, \c pismd.cc, \c pismr.cc, \c pisms.cc, and \c pismv.cc, corresponding to 
the executables with the same names.  The drivers \c pismr.cc and \c pismd.cc only use the base 
class \c IceModel, so one is required to initialize from a PISM model state NetCDF file with 
\c -if or from an incomplete model state NetCDF file using \c -bif.

The different derived classes generally invoke the same numerical procedures to handle the various 
partial differential equations of the continuum model.  In the case of \c IceCompModel and
\c IceExactSSAModel, this fact is at the heart of the verification mechanism.


\section petscID PETSc: An overview for PISM users

The PETSc library \lo\cite{petsc-user-ref}\elo provides essential support for distributed 
arrays and linear solvers in a parallel computing environment.  ``PETSc'' stands for 
``Portable, Extensible Toolkit for Scientific Computation.''  It is a suite of data structures 
and routines in C for the scalable parallel solution of partial differential equations and their 
scientific applications.  Large parts of PETSc relate especially to finite-difference-type regular, 
rectangular grids but PETSc has been used for unstructured grids as well.

PETSc employs the MPI standard for all message-passing communicationbut it is deliberately at a 
higher level of abstraction than MPI.  We find that using PETSc protects the programmer from 
explicit consideration of message passing about 90% of the time.

Documentation for PETSc is at 

http://www-unix.mcs.anl.gov/petsc/petsc-as/.

Although PISM is a C++ program, PETSc is a C library.  All PISM calls to PETSc use standard (ANSI) C.


\subsection petsctypesID PETSc types

Most important variables in a PETSc program are of these types:
  - \c DA
  - \c Vec
  - \c KSP

In fact most of the PETSc types merely declare pointers, but these types should be regarded 
as abstract data types.  Variables must be created with calls to functions like \c DACreate2d(), 
\c VecCreate(), etc., and destroyed when no longer needed.


\subsection distributedID Distributed arrays and vectors

PETSc has an abstract date type called a Distributed Array (type \c DA).  \c DAs contain 
information about the grid and stencil.  They set up \e ghosted values which are intended to
duplicate the values on neighboring processors so communication can be done in big batches.

Vectors (type \c Vec) are created \e using a \c DA with \c DAVecCreate() and similar 
procedures.  These vectors are distributed across the processors according to the information
in the \c DA.  Just for emphasis: <i>PISM distributes itself across the processors by calling
PETSc procedures which create a \c DA</i>.

There are two parameters of note when creating a \c DA: \e stencil \e type and 
\e stencil \e width.  

The stencil types are \c DA_STENCIL_STAR and \c DA_STENCIL_BOX.  
They are generalizations of the five point and nine point stencils typical of two-dimensional 
discretizations of second order partial derivatives.  Using \c DA_STENCIL_STAR means
that ghosted points are needed only along the coordinate axes, while \c DA_STENCIL_BOX 
indicates that ghosted points are needed in the box-shaped region surrounding each point, 
and thus each processor.  (On processor \e N, information owned by a neighboring processor 
but duplicated onto \e N is called \e ghosted.  A picture is worth a thousand words here, so 
find the appropriate picture in the PETSc manual!)  We only need \c BOX style stencils when gradient 
terms must be evaluated on a staggered grid (\e h in SIA regions and \f$\bar{u},\bar{v}\f$
in the computation of effective viscosity in SSA regions).  Keeping all other 
two-dimensional vectors on a \c STAR type stencil would reduce the necessary communication
slightly, but for now all two dimensional arrays are based on \c BOX.

The stencil width indicates how many points in each direction will be needed.  We never 
need a stencil width greater than 1.

The three dimensional distributed arrays are distributed across processors in the same way
as two-dimensional arrays, in the sense that <i>each column of the ice (or bedrock in that 
thermal model) is owned by exactly one processor</i>.  From the point of view of parallelization,
our problem is two-dimensional.  All three-dimensional arrays have stencil type \c STAR in the 
horizontal directions.

One point of confusion (we admit ...) is the redefinition of the \f$x,y,z\f$ axes. Contrary 
to the PETSc default, our \f$z\f$ axis changes most rapidly through memory while the
\f$x\f$ axis changes most slowly.  The desirable consequence, however, is that our C
arrays are addressed as <tt>u[i][j][k]</tt> where <tt>i,j,k</tt> are the coordinate 
indices in the directions \f$x,y,z\f$ respectively.


\subsection davecsID Accessing the processor's part of a DA-managed Vec

\c DA -based vectors must be accessed by a call to \c DAVecGetArray() before the access and
a call to \c DAVecRestoreArray() after.  This just means that one gets a valid pointer 
to the actual memory, for the abstract data type \c Vec.  The point has type 
<tt>double**</tt> for a 2-dimensional array and type <tt>double***</tt> for a 3-dimensional 
array.

The resulting pointer can be addressed using normal (to the extent that C is "normal" in 
this regard ...) multidimensional array indexing.  Furthermore, the indices themselves 
allow one to pretend that the given processor is addressing the entire array, even though only a
chunk is stored on the local processor.  <i>No message passing occurs here.</i>  Instead, the crucial
idea is that the \c DA knows what are the valid index ranges for each processor.  That's why 
essentially all loops over two dimensional arrays in PISM look like this:

\code
  for (PetscInt i = grid.xs; i < grid.xs + grid.xm; ++i) {
    for (PetscInt j = grid.ys; j < grid.ys + grid.ym; ++j) {

    ... H[i][j] ...
    
    ... ubar[i][j] ...
    
    ... T[i][j][k] ...

    }
  }
\endcode

The integers \c grid.xs, \c grid.xm, \c grid.ys, \c grid.ym, are just the numbers that come
from a call to \c DAGetLocalInfo(), just after the \c DA is created.


\subsection localglobalID ``Local'' versus ``global'' Vecs

PETSc \c DA -based vectors can be ``local'' or ``global''.   (This weird PETSc language should
probably be translated as ``has ghosts'' or ``sans ghosts''.)  ``Local'' vectors include 
space for the ghosted points.  That is, when \c DAVecGetArray() is called, the resulting 
array can be indexed on all of the local portion owned by the processor, \e plus the 
ghosted points.  The processor owns \e copies of the values at grid points owned by the neighboring
processors, according to the stencil type and stencil width in the \c DA.  The processor should 
treat these ghost values as ``read-only'', because of what happens at the communication stage 
(which we describe in a moment).

\e Example.  We create a local \c Vec \c v which we want to have \c STAR type stencil.  Assuming 
\c da is \c DA created with \c DA_STENCIL_STAR then we do this to create \c v and get an array 
pointer \c arr into the local portion of it:
\code
   DACreateLocalVector(da, &v);
   DAVecGetArray(da, v, &arr);
\endcode
Now the processor can access <tt>arr[i][j]</tt> for every 
\code 
   grid.xs <= i <= grid.xs + grid.xm - 1
\endcode
and
\code 
   grid.ys <= j <= grid.ys + grid.ym - 1
\endcode
But this is just the regular (owned by the processor) portion.  In addition, all of these 
are valid for every \c i and \c j in the above ranges:
\code
   arr[i+1][j],   arr[i-1][j],   arr[i][j+1],   arr[i][j-1].
\endcode
(\e If the \c da were of type \c DA_STENCIL_BOX then, in addition 
\code
   arr[i+1][j+1],   arr[i-1][j+1],   arr[i+1][j-1],   arr[i-1][j-1].
\endcode
would all be valid.)  Once the processor is done with modifying its portion of \c v (i.e. not including 
the ghosts, although it may read them) then we would want to update the ghost values so that
all processors agree on the values at those grid points:
\code
   DAVecRestoreArray(da, v, &arr);
   DALocalToLocalBegin(da, v, INSERT_VALUES, v);
   DALocalToLocalEnd(da, v, INSERT_VALUES, v);
\endcode
(Note we release the array pointer before the communication stage, although that may not be
essential.)

\c DALocalToLocalBegin() and then \c DALocalToLocalEnd() are called to update (communicate) the 
ghosted values before the next stage at which they will be needed.  This pair of commands 
perform a stage of actual (MPI) message passing.  Only enough values are passed around to 
update the ghosts.  The size of the messages is relatively small, and <i>latency is more important
(in slowing performance) than bandwidth</i>.  The significance of \c STAR versus \c BOX is not
in the size of the extra memory, but in the extra messages which must be passed to the ``diagonal''
neighboring processors.

Global vectors do not hold ghosted values.  Certain array operations are more appropriate to
these kind of vectors, like viewing arrays in graphics windows.  (Of course, viewing an array 
distributed across all the processors requires message passing.  I think PETSc sends all the
values to processor 0 to display then.)  In any case, when ghosts are not needed there is
no need to allocate space for them, and a ``global'' \c Vec is appropriate.  Local vectors
typically need to be mapped to global vectors before viewing or using in a linear system, but
this is an entirely ``local'' operation which does not require message passing (\c DALocalToGlobal()).


\subsection linearsysID Solving linear systems

PETSc is designed for solving large, sparse systems in parallel.  Iterative methods are 
the name of the game and especially Krylov subspace methods such as conjugate gradients and 
GMRES \lo\cite{TrefethenBau,Saad}\elo.  For consistency, all methods use the same 
Krylov-subspace-method-with-preconditioner \c KSP interface, even though some are really direct 
methods.

The place in PISM where this is already used is in the solution of the linearized SSA velocity
problem.  See the documentation for IceModel::velocitySSA() and IceModel::assembleSSAMatrix() 
in this \e Manual.

One starts by declaring an object of type \c KSP; in PISM this is done in IceModel::createVecs().
Various options can be set by the program, but, if the program calls \c KSPSetFromOptions() 
before any linear systems are solved, which PISM does, then user options like 
\c -ksp_type, \c -pc_type, and \c -ksp_rtol can be read to control (respectively) 
which Krylov method is used, which preconditioner is used, and what relative 
tolerance will be used as the convergence criterion of the Krylov solver.  The default is
GMRES(30) with ILU preconditioning.

(As a general mechanism, PETSc has an options database which holds command line options.
All PISM options use this database.  See IceModel::setFromOptions().)

To solve the system, a matrix must be attached to the \c KSP.  The first time
\c KSPSolve() is called, the matrix will be factored by the preconditioner and reused
when the system is called for additional right hand sides.  In the case of PISM and the 
solution of the balance of momentum equations for the SSA, the matrix changes because the
equations are nonlinear (because the effective viscosity depends on the strain rates).

The default matrix format is similar to the \e Matlab \c sparse format.  Each processor
owns a range of rows.  Elements in matrices and vectors can be set using \c MatSetValues()
and \c VecSetValues().  These routines use a ``global'' indexing which is not based on the regular
grid and stencil choices in the \c DA.  One can set any value on any processor but a lot of
message passing has to occur; fortunately PETSc manages that all.  Values are
cached until one calls \c MatAssemblyBegin() followed by \c MatAssemblyEnd() to
communicate the values.

In fact, in the SSA velocity computation, the matrix, the solution and right hand side 
vectors are not DA based.  The solution is moved into DA based arrays (for vertically-averaged 
velocity) by IceModel::moveVelocityToDAVectors() and IceModel::broadcastSSAVelocity().

The vector (field) components are interlaced and distributed.  This seemed to be the
most straightforward method to solve the system (as opposed to using more advanced
features intended for multiple degrees of freedom on DA based vectors).  This also allows
the matrix to have an optimal parallel layout.


\subsection additionalpetscID Additional PETSc utility functions

The \c PetscViewer interface allows PETSc objects to be displayed.  One can ``view''
a \c Vec to a graphical (X) window, but the ``view'' can be saving the \c Vec to a binary
file on disk, in plain text to the terminal (standard out), or even by sending to a running
instance of \e Matlab.  (This last capability is not used yet in PISM.)

When viewing \c Vec s graphically in multiprocessor jobs, the display may have to be 
set on the command line, for instance as <tt>-display :0</tt> or similar; this must be given 
as the final option.  For example,
\code
   mpiexec -n 2 pismv -test C -Mx 101 -My 101 -Mz 31 -y 1000 -d HT -display :0
\endcode
allows a two processor run to view (graphically) both the ice thickness (<tt>-d H</tt>)
and the ice temperature (<tt>-d T</tt>).

Quite ellaborate error tracing and performance monitoring is possible with PETSc.  All
functions return \c PetscErrorCode which should be checked by the macro \c CHKERRQ().
Therefore runtime errors normally print sufficient traceback information.

If this information is not present (because the error did not get traced back), you 
may need to use a debugger which is accessible with the command line (PETSc) options 
\c -start_in_debugger and \c -on_error_attach_debugger.  

Option \c -log_summary is useful to get some diagnostics written to the terminal.

@endcond
 */


/*! \fn PetscErrorCode IceModel::temperatureStep()
    \brief Takes a semi-implicit time-step for the temperature equation.

In summary, the conservation of energy equation is
    \f[ \rho c_p \frac{dT}{dt} = k \frac{\partial^2 T}{\partial z^2} + \Sigma,\f] 
where \f$T(t,x,y,z)\f$ is the temperature of the ice.  This equation is the shallow approximation
of the full three-dimensional conservation of energy.  Note \f$dT/dt\f$ stands for the material
derivative, so advection is included.  Here \f$\rho\f$ is the density of ice, 
\f$c_p\f$ is its specific heat, and \f$k\f$ is its conductivity.  Also \f$\Sigma\f$ is the volume
strain heating.

In summary, the numerical method is first-order upwind for advection and centered-differences with
semi-implicitness for the vertical conduction term.  We work from the bottom 
of the column upward in building the system to solve (in the semi-implicit time-stepping scheme).
The excess energy above pressure melting is converted to melt-water, and that a fraction 
of this melt water is transported to the base according to the scheme in excessToFromBasalMeltLayer().

The method uses equally-spaced calculation but the methods getValColumn(), setValColumn() interpolate 
back and forth from this equally-spaced calculational grid to the (usually) non-equally space storage 
grid.

In this procedure four scalar fields are modified: vHmelt, vbasalMeltRate, Tb3, and Tnew3.
But vHmelt, vbasalMeltRate and Tb3 will never need to communicate ghosted values (i.e. horizontal 
stencil neighbors.  The ghosted values for T3 are updated from the values in Tnew3 in the
communication done by temperatureAgeStep().
 
@cond REFMAN
Here is a more complete discussion and derivation.

Consider a column of a slowly flowing and heat conducting material as shown in the left side 
of the next figure.  (The left side shows a general column of flowing and heat conduction 
material showing a small segment \f$V\f$.  The right side shows a more specific column of ice 
flowing and sliding over bedrock.)  This is an \em Eulerian view so the material flows through 
a column which remains fixed (and is notional).  The column is vertical.  We will 
assume when needed that it is rectangular in cross-section with cross-sectional area 
\f$\Delta x\Delta y\f$.

\image latex earlycols.png "Left: a general column of material.  Right: ice over bedrock." width=3in

[FIXME: CONTINUE TO MINE eqns3D.tex FOR MORE]

The application of the geothermal flux at the base of a column is a special case for which 
we give a finite difference argument.  This scheme follows the equation (2.114) in 
Morton and Mayers (2005).  We have the boundary condition
	\f[  -k \frac{\partial T}{\partial z} = G(t,x,y) \f]
where \f$G(t,x,y)\f$ is the applied geothermal flux, and it is applied at level \f$z=-B_0\f$ 
in the bedrock (which is the only case considered here).  We <em> add a virtual lower grid 
point </em> \f$z_{-1} = z_0 - \Delta  z\f$ and we approximate the above boundary condition 
at $z_0$ by the centered-difference
	\f[  -k \frac{T_{1} - T_{-1}}{2 \Delta z} = G. \f]
Here \f$T_k = T_{ijk}^{l+1}\f$.  We also apply the discretized conduction equation at $z_0$.  These two combined equations 
yield a simplified form
	\f[(1 + 2 KR) T_0 - 2 K T_1 = T_0 + \frac{2\Delta t}{\rho c_p \Delta z} G \f]
where \f$K = k \Delta t (\rho c \Delta z^2)^{-1}\f$.

@endcond
 */
 

/*! \page pismreferences References

\latexonly

\begin{thebibliography}{10}

\bibitem{petsc-user-ref}
{\sc S.~Balay and eight others}, {\em {PETS}c users manual}, Tech. Rep.
  ANL-95/11 - Revision 2.3.2, Argonne National Laboratory, 2006.

\bibitem{BB}
{\sc E.~Bueler and J.~Brown}, {\em On exact solutions and numerics for cold,
  shallow, and thermocoupled ice sheets}.
\newblock preprint \texttt{arXiv:physics/0610106}, 2006.

\bibitem{BBL}
{\sc E.~Bueler, J.~Brown, and C.~Lingle}, {\em Exact solutions to the
  thermomechanically coupled shallow ice approximation: effective tools for
  verification}, J. Glaciol., 53 (2007), pp.~499--516.

\bibitem{BLKfastearth}
{\sc E.~Bueler, C.~S. Lingle, and J.~A. Kallen-Brown}, {\em Fast computation of
  a viscoelastic deformable {E}arth model for ice sheet simulation}, Ann.
  Glaciol., 46 (2007), pp.~97--105.

\bibitem{BLKCB}
{\sc E.~Bueler, C.~S. Lingle, J.~A. Kallen-Brown, D.~N. Covey, and L.~N.
  Bowman}, {\em Exact solutions and numerical verification for isothermal ice
  sheets}, J. Glaciol., 51 (2005), pp.~291--306.

\bibitem{CalovGreve05}
{\sc R.~Calov and R.~Greve}, {\em Correspondence: {A} semi-analytical solution
  for the positive degree-day model with stochastic temperature variations}, J.
  Glaciol, 51 (2005), pp.~173--175.

\bibitem{VostokCore}
{\sc {{EPICA} community members}}, {\em Eight glacial cycles from an
  {A}ntarctic ice core}, Nature, 429 (2004), pp.~623--628.
\newblock doi: 10.1038/nature02599.

\bibitem{Fowler}
{\sc A.~C. Fowler}, {\em Mathematical Models in the Applied Sciences},
  Cambridge Univ. Press, 1997.

\bibitem{GoldsbyKohlstedt}
{\sc D.~L. Goldsby and D.~L. Kohlstedt}, {\em Superplastic deformation of ice:
  experimental observations}, J. Geophys. Res., 106 (2001), pp.~11017--11030.

\bibitem{Halfar83}
{\sc P.~Halfar}, {\em On the dynamics of the ice sheets 2}, J. Geophys. Res.,
  88 (1983), pp.~6043--6051.

\bibitem{Hooke}
{\sc R.~Hooke}, {\em Flow law for polycrystalline ice in glaciers: comparison
  of theoretical predictions, laboratory data, and field measurements}, Rev.
  Geophys. Space. Phys., 19 (1981), pp.~664--672.

\bibitem{HuybrechtsEISMINT}
{\sc P.~Huybrechts}, {\em Report of the {T}hird {EISMINT} {W}orkshop on {M}odel
  {I}ntercomparison}.
\newblock
  \texttt{http://homepages.vub.ac.be/~phuybrec/pdf/EISMINT3.Huyb.1998.pdf}; 120
  p., 1998.

\bibitem{LingleClark}
{\sc C.~S. Lingle and J.~A. Clark}, {\em A numerical model of interactions
  between a marine ice sheet and the solid earth: {A}pplication to a {W}est
  {A}ntarctic ice stream}, J. Geophys. Res., 90 (1985), pp.~1100--1114.

\bibitem{MacAyeal}
{\sc D.~R. MacAyeal}, {\em Large-scale ice flow over a viscous basal sediment:
  theory and application to ice stream {B}, {A}ntarctica}, J. Geophys. Res., 94
  (1989), pp.~4071--4087.

\bibitem{MortonMayers}
{\sc K.~W. Morton and D.~F. Mayers}, {\em Numerical {S}olutions of {P}artial
  {D}ifferential {E}quations: {A}n {I}ntroduction}, Cambridge University Press,
  second~ed., 2005.

\bibitem{Paterson}
{\sc W.~S.~B. Paterson}, {\em The {P}hysics of {G}laciers}, Pergamon, 3rd~ed.,
  1994.

\bibitem{PatersonBudd}
{\sc W.~S.~B. Paterson and W.~F. Budd}, {\em Flow parameters for ice sheet
  modeling}, Cold Reg. Sci. Technol., 6 (1982), pp.~175--177.

\bibitem{EISMINT00}
{\sc A.~Payne et~al.}, {\em Results from the {EISMINT} model intercomparison:
  the effects of thermomechanical coupling}, J. Glaciol., 153 (2000),
  pp.~227--238.

\bibitem{RitzEISMINT}
{\sc C.~Ritz}, {\em {EISMINT} {I}ntercomparison {E}xperiment: {C}omparison of
  existing {G}reenland models}.
\newblock \texttt{http://homepages.vub.ac.be/~phuybrec/eismint/greenland.html},
  1997.
  

\bibitem{Saad}
{\sc Y. Saad}, {\em Iterative {M}ethods for {L}inear {A}lgebra ??}, ??,
  ????.

\bibitem{SchoofStream}
{\sc C.~Schoof}, {\em A variational approach to ice stream flow}, J. Fluid
  Mech., 556 (2006), pp.~227--251.

\bibitem{Trefethen}
{\sc L.~N. Trefethen}, {\em Spectral {M}ethods in {MATLAB}}, SIAM Press,
  2000.

\bibitem{TrefethenBau}
{\sc L.~N. Trefethen and D. Bau}, {\em Numerical {L}inear {A}lgebra}, SIAM Press,
  1997.

\end{thebibliography}

\endlatexonly

 */



