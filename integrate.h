#ifndef INTEGRATE_H
#define INTEGRATE_H
/** \file integrate.h    Molecular dynamics integrator.
 *
 *  <b>Responsible:</b>
 *  <a href="mailto:limbach@mpip-mainz.mpg.de">Hanjo</a>
 *
 *  For more information see \ref integrate.c "integrate.c".
*/   
#include <tcl.h>

/** \name Exported Variables */
/************************************************************/
/*@{*/

/** Time step for the integration. */
extern double time_step;
/** Physical start time of the simulation. */
extern double start_time;
/** Actual simulation time (only on MASTER NODE). */
extern double sim_time;
/** Maximal interaction cutoff. */
extern double max_cut;
/** Verlet list skin. */
extern double skin;
/** Maximal interaction range (max_cut + skin). */
extern double max_range;
/** square of \ref max_range. */
extern double max_range2;
/** If non-zero, some particles have moved since last
    integration. */
extern int    particle_changed;
/** If non-zero, some non-bonded interactions have changed since last
    integration. */
extern int    interactions_changed;
/** If non-zero, the system topology has changed since last
    integration. */
extern int    topology_changed;
/** If non-zero, some other parameter (e.g. time_step, skin) has changed
    since last integration. */
extern int    parameter_changed;

/*@}*/

/** \name Exported Functions */
/************************************************************/
/*@{*/

/** tcl procedure for integrator steering.
    USAGE: integrate <task>                       \\
           task can either be init, #steps, exit. \\
    EXAMPLE for an integration:                   \\
           integrate init                         \\
           integrate 100                          \\
           integrate exit      
    \return TCL status.
*/
int integrate(ClientData data, Tcl_Interp *interp,
	      int argc, char **argv);

/** update maxrange etc. */
void integrate_vv_recalc_maxrange();

/** integrate with velocity verlet integrator.
    \param n_steps number of steps to integrate.
 */
void integrate_vv(int n_steps);

/** Callback for setmd skin.
    \return TCL status.
*/
int skin_callback(Tcl_Interp *interp, void *_data);

/** Callback for integration time_step (0.0 <= time_step).
    \return TCL status.
*/
int time_step_callback(Tcl_Interp *interp, void *_data);

/** Callback for start_time of the integration.
    If no value is set the integration starts at start_time = 0.0.
    \return TCL status.
*/
int start_time_callback(Tcl_Interp *interp, void *_data);

/** Callback for integrator flag calc_forces_first (= 0 or 1).
    <ul>
    <li> 1 means the integrator calculates the forces befor the
    first integration step.
    <li> 0 means the integrator reuses the forces that it remembers 
    from the last integration step.
    </ul>
    \return TCL status.
*/
int calc_forces_first_callback(Tcl_Interp *interp, void *_data);
/*@}*/

#endif
