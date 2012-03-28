#include "extern/dierckx/surfit.h"
#include "extern/dierckx/fpsurf.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

void surfit(int iopt, int m, const float *x, const float *y, const float *z,
        const float *w, float xb, float xe, float yb, float ye, int kx,
        int ky, float s, int nxest, int nyest, int nmax, float eps, int *nx,
        float *tx, int *ny, float *ty, float *c, float *fp, float *wrk1,
        int lwrk1, float *wrk2, int lwrk2, int *iwrk, int kwrk, int *ier)
{
    /* Local variables */
    int i, la, lf, ki, lh, kn, lq, ib1, jb1, ib3, km1, km2, kx1, ky1,
    lff, lco, nek, lfp, lbx, lby;
    float tol;
    int nxk, nyk, nmx, nmy, lsx, lsy, nreg, kmax, nest, ncest, maxit,
    nminx, nminy, nrint, kwest, lwest;

    /* Parameter adjustments */
    --w;
    --z;
    --y;
    --x;
    --c;
    --ty;
    --tx;
    --wrk1;
    --wrk2;
    --iwrk;

    /* Function Body */
    /*  we set up the parameters tol and maxit. */
    maxit = 20;
    tol = .001f;
    /*  before starting computations a data check is made. if the input data */
    /*  are invalid,control is immediately repassed to the calling program. */
    *ier = 10;
    if (eps <= 0.f || eps >= 1.f) return;
    if (kx <= 0 || kx > 5) return;
    kx1 = kx + 1;
    if (ky <= 0 || ky > 5) return;
    ky1 = ky + 1;
    kmax = max(kx, ky);
    km1 = kmax + 1;
    km2 = km1 + 1;
    if (iopt < -1 || iopt > 1) return;
    if (m < kx1 * ky1) return;
    nminx = kx1 << 1;
    if (nxest < nminx || nxest > nmax) return;
    nminy = ky1 << 1;
    if (nyest < nminy || nyest > nmax) return;
    nest = max(nxest,nyest);
    nxk = nxest - kx1;
    nyk = nyest - ky1;
    ncest = nxk * nyk;
    nmx = nxest - nminx + 1;
    nmy = nyest - nminy + 1;
    nrint = nmx + nmy;
    nreg = nmx * nmy;
    ib1 = kx * nyk + ky1;
    jb1 = ky * nxk + kx1;
    ib3 = kx1 * nyk + 1;
    if (ib1 > jb1)
    {
        ib1 = jb1;
        ib3 = ky1 * nxk + 1;
    }
    lwest = ncest * (ib1 + 2 + ib3) + (nrint + nest * km2 + m * km1 << 1) + ib3;
    kwest = m + nreg;
    if (lwrk1 < lwest || kwrk < kwest) return;
    if (xb >= xe || yb >= ye) return;
    for (i = 1; i <= m; ++i)
    {
        if (w[i] <= 0.f) return;
        if (x[i] < xb || x[i] > xe) return;
        if (y[i] < yb || y[i] > ye) return;
    }
    if (iopt >= 0) {
        goto L50;
    }
    if (*nx < nminx || *nx > nxest) return;
    nxk = *nx - kx1;
    tx[kx1] = xb;
    tx[nxk + 1] = *xe;
    for (i = kx1; i <= nxk; ++i)
    {
        if (tx[i + 1] <= tx[i]) return;
    }
    if (*ny < nminy || *ny > nyest) return;
    nyk = *ny - ky1;
    ty[ky1] = yb;
    ty[nyk + 1] = ye;
    for (i = ky1; i <= nyk; ++i)
    {
        if (ty[i + 1] <= ty[i]) return;
    }
    goto L60;
L50:
    if (s < 0.f) return;
L60:
    *ier = 0;
    /*  we partition the working space and determine the spline approximation */
    kn = 1;
    ki = kn + m;
    lq = 2;
    la = lq + ncest * ib3;
    lf = la + ncest * ib1;
    lff = lf + ncest;
    lfp = lff + ncest;
    lco = lfp + nrint;
    lh = lco + nrint;
    lbx = lh + ib3;
    nek = nest * km2;
    lby = lbx + nek;
    lsx = lby + nek;
    lsy = lsx + m * km1;
    fpsurf(iopt, m, &x[1], &y[1], &z[1], &w[1], xb, xe, yb, ye, kx, ky, s,
            nxest, nyest, eps, &tol, &maxit, &nest, &km1, &km2, &ib1, &ib3,
            &ncest, &nrint, &nreg, nx, &tx[1], ny, &ty[1], &c[1], fp, &wrk1[1],
            &wrk1[lfp], &wrk1[lco], &wrk1[lf], &wrk1[lff], &wrk1[la], &wrk1[lq],
            &wrk1[lbx], &wrk1[lby], &wrk1[lsx], &wrk1[lsy], &wrk1[lh],
            &iwrk[ki], &iwrk[kn], &wrk2[1], lwrk2, ier);
}

#ifdef __cplusplus
}
#endif