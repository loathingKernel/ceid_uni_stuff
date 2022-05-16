/* Nonlinear Optimization using the algorithm of Hooke and Jeeves  */
/*	12 February 1994	author: Mark G. Johnson 	   */

/* Find a point X where the nonlinear function f(X) has a local    */
/* minimum.  X is an n-vector and f(X) is a scalar.  In mathe-	   */
/* matical notation  f: R^n -> R^1.  The objective function f()    */
/* is not required to be continuous.  Nor does f() need to be	   */
/* differentiable.  The program does not use or require 	   */
/* derivatives of f().						   */

/* The software user supplies three things: a subroutine that	   */
/* computes f(X), an initial "starting guess" of the minimum point */
/* X, and values for the algorithm convergence parameters.  Then   */
/* the program searches for a local minimum, beginning from the    */
/* starting guess, using the Direct Search algorithm of Hooke and  */
/* Jeeves.							   */

/* This C program is adapted from the Algol pseudocode found in    */
/* "Algorithm 178: Direct Search" by Arthur F. Kaupe Jr., Commun-  */
/* ications of the ACM, Vol 6. p.313 (June 1963).  It includes the */
/* improvements suggested by Bell and Pike (CACM v.9, p. 684, Sept */
/* 1966) and those of Tomlin and Smith, "Remark on Algorithm 178"  */
/* (CACM v.12).  The original paper, which I don't recommend as    */
/* highly as the one by A. Kaupe, is:  R. Hooke and T. A. Jeeves,  */
/* "Direct Search Solution of Numerical and Statistical Problems", */
/* Journal of the ACM, Vol. 8, April 1961, pp. 212-229. 	   */

/* Calling sequence:						   */
/*  int hooke(nvars, startpt, endpt, rho, epsilon, itermax)	   */
/*								   */
/*     nvars	   {an integer}  This is the number of dimensions  */
/*		   in the domain of f().  It is the number of	   */
/*		   coordinates of the starting point (and the	   */
/*		   minimum point.)				   */
/*     startpt	   {an array of doubles}  This is the user-	   */
/*		   supplied guess at the minimum.		   */
/*     endpt	   {an array of doubles}  This is the location of  */
/*		   the local minimum, calculated by the program    */
/*     rho	   {a double}  This is a user-supplied convergence */
/*		   parameter (more detail below), which should be  */
/*		   set to a value between 0.0 and 1.0.	Larger	   */
/*		   values of rho give greater probability of	   */
/*		   convergence on highly nonlinear functions, at a */
/*		   cost of more function evaluations.  Smaller	   */
/*		   values of rho reduces the number of evaluations */
/*		   (and the program running time), but increases   */
/*		   the risk of nonconvergence.	See below.	   */
/*     epsilon	   {a double}  This is the criterion for halting   */
/*		   the search for a minimum.  When the algorithm   */
/*		   begins to make less and less progress on each   */
/*		   iteration, it checks the halting criterion: if  */
/*		   the stepsize is below epsilon, terminate the    */
/*		   iteration and return the current best estimate  */
/*		   of the minimum.  Larger values of epsilon (such */
/*		   as 1.0e-4) give quicker running time, but a	   */
/*		   less accurate estimate of the minimum.  Smaller */
/*		   values of epsilon (such as 1.0e-7) give longer  */
/*		   running time, but a more accurate estimate of   */
/*		   the minimum. 				   */
/*     itermax	   {an integer}  A second, rarely used, halting    */
/*		   criterion.  If the algorithm uses >= itermax    */
/*		   iterations, halt.				   */

/* The user-supplied objective function f(x,n) should return a C   */
/* "double".  Its  arguments are  x -- an array of doubles, and    */
/* n -- an integer.  x is the point at which f(x) should be	   */
/* evaluated, and n is the number of coordinates of x.	That is,   */
/* n is the number of coefficients being fitted.		   */

/* rho, the algorithm convergence control			   */
/*	The algorithm works by taking "steps" from one estimate of */
/*    a minimum, to another (hopefully better) estimate.  Taking   */
/*    big steps gets to the minimum more quickly, at the risk of   */
/*    "stepping right over" an excellent point.  The stepsize is   */
/*    controlled by a user supplied parameter called rho.  At each */
/*    iteration, the stepsize is multiplied by rho  (0 < rho < 1), */
/*    so the stepsize is successively reduced.			   */
/*	Small values of rho correspond to big stepsize changes,    */
/*    which make the algorithm run more quickly.  However, there   */
/*    is a chance (especially with highly nonlinear functions)	   */
/*    that these big changes will accidentally overlook a	   */
/*    promising search vector, leading to nonconvergence.	   */
/*	Large values of rho correspond to small stepsize changes,  */
/*    which force the algorithm to carefully examine nearby points */
/*    instead of optimistically forging ahead.	This improves the  */
/*    probability of convergence.				   */
/*	The stepsize is reduced until it is equal to (or smaller   */
/*    than) epsilon.  So the number of iterations performed by	   */
/*    Hooke-Jeeves is determined by rho and epsilon:		   */
/*	    rho**(number_of_iterations) = epsilon		   */
/*	In general it is a good idea to set rho to an aggressively */
/*    small value like 0.5 (hoping for fast convergence).  Then,   */
/*    if the user suspects that the reported minimum is incorrect  */
/*    (or perhaps not accurate enough), the program can be run	   */
/*    again with a larger value of rho such as 0.85, using the	   */
/*    result of the first minimization as the starting guess to    */
/*    begin the second minimization.				   */

/* Normal use: (1) Code your function f() in the C language	   */
/*	       (2) Install your starting guess {or read it in}	   */
/*	       (3) Run the program				   */
/*	       (4) {for the skeptical}: Use the computed minimum   */
/*		      as the starting point for another run	   */

/* Data Fitting:						   */
/*	Code your function f() to be the sum of the squares of the */
/*	errors (differences) between the computed values and the   */
/*	measured values.  Then minimize f() using Hooke-Jeeves.    */
/*	EXAMPLE: you have 20 datapoints (ti, yi) and you want to   */
/*	find A,B,C such that  (A*t*t) + (B*exp(t)) + (C*tan(t))    */
/*	fits the data as closely as possible.  Then f() is just    */
/*	f(x) = SUM (measured_y[i] - ((A*t[i]*t[i]) + (B*exp(t[i])) */
/*				  + (C*tan(t[i]))))^2		   */
/*	where x[] is a 3-vector consisting of {A, B, C}.	   */

/*								   */
/*  The author of this software is M.G. Johnson.		   */
/*  Permission to use, copy, modify, and distribute this software  */
/*  for any purpose without fee is hereby granted, provided that   */
/*  this entire notice is included in all copies of any software   */
/*  which is or includes a copy or modification of this software   */
/*  and in all copies of the supporting documentation for such	   */
/*  software.  THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT    */
/*  ANY EXPRESS OR IMPLIED WARRANTY.  IN PARTICULAR, NEITHER THE   */
/*  AUTHOR NOR AT&T MAKE ANY REPRESENTATION OR WARRANTY OF ANY	   */
/*  KIND CONCERNING THE MERCHANTABILITY OF THIS SOFTWARE OR ITS    */
/*  FITNESS FOR ANY PARTICULAR PURPOSE. 			   */
/*								   */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MAXVARS (250)   /* max # of variables	     */
#define RHO_BEGIN (0.5) /* stepsize geometric shrink */
#define EPSMIN (1E-6)   /* ending value of stepsize  */
#define IMAX (5000)     /* max # of iterations	     */

//#define DEBUG 0

/* Rosenbrocks classic parabolic valley ("banana") function */
double f(double *x, int n, unsigned long *funevals) {
  double fv;
  int i;

  (*funevals)++;
  fv = 0.0;
  for (i = 0; i < n - 1; i++) /* rosenbrock */
    fv = fv + 100.0 * pow((x[i + 1] - x[i] * x[i]), 2) + pow((x[i] - 1.0), 2);

  return fv;
}

/* given a point, look for a better one nearby, one coord at a time */
double best_nearby(double delta[MAXVARS], double point[MAXVARS],
                   double prevbest, int nvars, unsigned long *funevals) {
  double z[MAXVARS];
  double minf, ftmp;
  int i;
  minf = prevbest;
  for (i = 0; i < nvars; i++)
    z[i] = point[i];
  for (i = 0; i < nvars; i++) {
    z[i] = point[i] + delta[i];
    ftmp = f(z, nvars, funevals);
    if (ftmp < minf)
      minf = ftmp;
    else {
      delta[i] = 0.0 - delta[i];
      z[i] = point[i] + delta[i];
      ftmp = f(z, nvars, funevals);
      if (ftmp < minf)
        minf = ftmp;
      else
        z[i] = point[i];
    }
  }
  for (i = 0; i < nvars; i++)
    point[i] = z[i];

  return (minf);
}

int hooke(int nvars, double startpt[MAXVARS], double endpt[MAXVARS], double rho,
          double epsilon, int itermax, unsigned long *funevals) {
  double delta[MAXVARS];
  double newf, fbefore, steplength, tmp;
  double xbefore[MAXVARS], newx[MAXVARS];
  int i, j, keep;
  int iters, iadj;

  for (i = 0; i < nvars; i++) {
    newx[i] = xbefore[i] = startpt[i];
    delta[i] = fabs(startpt[i] * rho);
    if (delta[i] == 0.0)
      delta[i] = rho;
  }
  iadj = 0;
  steplength = rho;
  iters = 0;
  fbefore = f(newx, nvars, funevals);
  newf = fbefore;
  while ((iters < itermax) && (steplength > epsilon)) {
    iters++;
    iadj++;
#if DEBUG
    printf("\nAfter %5d funevals, f(x) =  %.4le at\n", funevals, fbefore);
    for (j = 0; j < nvars; j++)
      printf("   x[%2d] = %.4le\n", j, xbefore[j]);
#endif
    /* find best new point, one coord at a time */
    for (i = 0; i < nvars; i++) {
      newx[i] = xbefore[i];
    }
    newf = best_nearby(delta, newx, fbefore, nvars, funevals);
    /* if we made some improvements, pursue that direction */
    keep = 1;
    while ((newf < fbefore) && (keep == 1)) {
      iadj = 0;
      for (i = 0; i < nvars; i++) {
        /* firstly, arrange the sign of delta[] */
        if (newx[i] <= xbefore[i])
          delta[i] = 0.0 - fabs(delta[i]);
        else
          delta[i] = fabs(delta[i]);
        /* now, move further in this direction */
        tmp = xbefore[i];
        xbefore[i] = newx[i];
        newx[i] = newx[i] + newx[i] - tmp;
      }
      fbefore = newf;
      newf = best_nearby(delta, newx, fbefore, nvars, funevals);
      /* if the further (optimistic) move was bad.... */
      if (newf >= fbefore)
        break;

      /* make sure that the differences between the new */
      /* and the old points are due to actual */
      /* displacements; beware of roundoff errors that */
      /* might cause newf < fbefore */
      keep = 0;
      for (i = 0; i < nvars; i++) {
        keep = 1;
        if (fabs(newx[i] - xbefore[i]) > (0.5 * fabs(delta[i])))
          break;
        else
          keep = 0;
      }
    }
    if ((steplength >= epsilon) && (newf >= fbefore)) {
      steplength = steplength * rho;
      for (i = 0; i < nvars; i++) {
        delta[i] *= rho;
      }
    }
  }
  for (i = 0; i < nvars; i++)
    endpt[i] = xbefore[i];

  return (iters);
}

double get_wtime(void) {
  struct timeval t;

  gettimeofday(&t, NULL);

  return (double)t.tv_sec + (double)t.tv_usec * 1.0e-6;
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank, procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procs);

  double endpt[MAXVARS];
  int itermax = IMAX;
  double rho = RHO_BEGIN;
  double epsilon = EPSMIN;
  int nvars;
  int trial, ntrials;
  double fx;
  int i, jj;
  double t0, t1;

  double best_fx = 1e10;
  double best_pt[MAXVARS];
  int best_trial = -1;
  int best_jj = -1;

  unsigned long funevals = 0;

  for (i = 0; i < MAXVARS; i++)
    best_pt[i] = 0.0;

  ntrials = 128 * 1024; /* number of trials */
  nvars = 16;           /* number of variables (problem dimension) */
  srand48(1);

  double const step = (ntrials) / procs;
  unsigned long start = rank * step;
  unsigned long end = (rank + 1) * step;
  if (rank == procs - 1)
    end = ntrials;

  // allocate guess array for every trial
  double **startpt = (double **)malloc(ntrials * sizeof(double *));
  for (int i = 0; i < ntrials; i++)
    startpt[i] = (double *)malloc(MAXVARS * sizeof(double));

  t0 = get_wtime();
  /* initializing guess for rosenbrock test function, search space in [-4, 4) */
  if (!rank) {
  for (int j = 0; j < ntrials; j++)
    for (int i = 0; i < nvars; i++)
      startpt[j][i] = 4.0 * drand48() - 4.0;
  }

  if (!rank) {
    for (int c = 1; c < procs; c++) {
      unsigned long c_start = c * step;
      unsigned long c_end = (c + 1) * step;
      if (c == procs - 1)
        c_end = ntrials;
      MPI_Send(startpt[c_start], (c_end - c_start) * MAXVARS, MPI_DOUBLE, c, 50,
               MPI_COMM_WORLD);
    }
    //printf("Rank %d chunk size %lu\n", rank, end - start);
  } else {
    MPI_Status status;
    MPI_Recv(startpt[start], (end - start) * MAXVARS, MPI_DOUBLE, 0, 50,
             MPI_COMM_WORLD, &status);
    //printf("Rank %d chunk size %lu\n", rank, end - start);
  }

  for (trial = start; trial < end; trial++) {

    jj = hooke(nvars, startpt[trial], endpt, rho, epsilon, itermax, &funevals);
#if DEBUG
    printf("\n\n\nHOOKE %d USED %d ITERATIONS, AND RETURNED\n", trial, jj);
    for (i = 0; i < nvars; i++)
      printf("x[%3d] = %15.7le \n", i, endpt[i]);
#endif

    fx = f(endpt, nvars, &funevals);
#if DEBUG
    printf("f(x) = %15.7le\n", fx);
#endif

    if (fx < best_fx) {
      best_trial = trial;
      best_jj = jj;
      best_fx = fx;
      for (int i = 0; i < nvars; i++)
        best_pt[i] = endpt[i];
    }
  }

  if (rank) {
    MPI_Send(&best_fx, 1, MPI_DOUBLE, 0, 60, MPI_COMM_WORLD);
    MPI_Send(&best_trial, 1, MPI_INT, 0, 61, MPI_COMM_WORLD);
    MPI_Send(&best_jj, 1, MPI_INT, 0, 62, MPI_COMM_WORLD);
    MPI_Send(&best_pt, MAXVARS, MPI_DOUBLE, 0, 63, MPI_COMM_WORLD);
    MPI_Send(&funevals, 1, MPI_UNSIGNED_LONG, 0, 64, MPI_COMM_WORLD);
    /*
    printf("Rank %d, fx %15.7le, trial %d, jj %d, evals %lu\n", rank,
           best_fx,
           best_trial,
           best_jj,
           funevals);
    for (i = 0; i < nvars; i++)
      printf("x[%3d] = %15.7le \n", i, best_pt[i]);
    */
  } else {
    double best_fx_buf[procs-1];
    int best_trial_buf[procs-1];
    int best_jj_buf[procs-1];
    double best_pt_buf[procs-1][MAXVARS];
    unsigned long funevals_buf[procs-1];

    /*
    printf("Rank %d, fx %15.7le, trial %d, jj %d, evals %lu\n", rank,
           best_fx,
           best_trial,
           best_jj,
           funevals);
    for (i = 0; i < nvars; i++)
      printf("x[%3d] = %15.7le \n", i, best_pt[i]);
    */
    MPI_Status status;

    for (int c = 0; c < procs-1; c++) {
      MPI_Recv(&best_fx_buf[c], 1, MPI_DOUBLE, c+1, 60, MPI_COMM_WORLD, &status);
      MPI_Recv(&best_trial_buf[c], 1, MPI_INT, c+1, 61, MPI_COMM_WORLD, &status);
      MPI_Recv(&best_jj_buf[c], 1, MPI_INT, c+1, 62, MPI_COMM_WORLD, &status);
      MPI_Recv(&best_pt_buf[c], MAXVARS, MPI_DOUBLE, c+1, 63, MPI_COMM_WORLD,
               &status);
      MPI_Recv(&funevals_buf[c], 1, MPI_UNSIGNED_LONG, c+1, 64, MPI_COMM_WORLD,
               &status);
    }

    for (int c = 0; c < procs-1; c++) {
      if (best_fx_buf[c] < best_fx) {
        best_trial = best_trial_buf[c];
        best_jj = best_jj_buf[c];
        best_fx = best_fx_buf[c];
        for (int v = 0; v < MAXVARS; v++)
          best_pt[v] = best_pt_buf[c][v];
      }
      funevals += funevals_buf[c];
    }
  }

  t1 = get_wtime();

  if (!rank) {
  printf("\n\nFINAL RESULTS:\n");
  printf("Elapsed time = %.3lf s\n", t1 - t0);
  printf("Total number of trials = %d\n", ntrials);
  printf("Total number of function evaluations = %ld\n", funevals);
  printf("Best result at trial %d used %d iterations, and returned\n",
          best_trial, best_jj);
  for (i = 0; i < nvars; i++) {
    printf("x[%3d] = %15.7le \n", i, best_pt[i]);
  }
  printf("f(x) = %15.7le\n", best_fx);
  }

  // Cleanup
  for (int i = 0; i < ntrials; i++)
    free(startpt[i]);
  free(startpt);

  MPI_Finalize();

  return 0;
}

// kate: space-indent on; indent-width 2;
