#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP simpleCall_impl(SEXP x) {
    int n = Rf_length(x);
    int m = n * sizeof(double);

    double* srcptr = REAL(x);
    double* dstptr = malloc(m);			// allocate, never release --> leak
    memcpy((void*)dstptr, (void*)srcptr, m);	// so compiler does not complain about unused ptr

    Rprintf("n=%d x[1]=%f\n", n, (double) dstptr[1]);
    return R_NilValue;
}

static const R_CallMethodDef CallEntries[] = {
    {"simpleCall_impl", (DL_FUNC) &simpleCall_impl, 1},
    {NULL, NULL, 0}
};

void R_init_demovalgrindnonfail(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
