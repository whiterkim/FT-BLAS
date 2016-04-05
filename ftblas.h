#ifndef FTBLAS
#define FTBALS

#include "complex.h"

extern	void	init_();

//level 1
//						dim				scalar				vector 									vector 									scalars																			5-element array
//xROTG
extern	void	srotg_(																																				float*a,	float*b,	float*c,	float*s);
		void 	srotg(																																				float*a, 	float*b,	float*c,	float*s){ srotg_(a,b,c,s); }
extern	void	drotg_(																																				double*a,	double*b,	double*c,	double*s);
		void 	drotg(																																				double*a, 	double*b,	double*c,	double*s){ drotg_(a,b,c,s); }


//xROTMG
extern	void	srotmg_(																													float*d1,	float*d2,	float*a,	float*b,								float*param);
		void 	srotmg(																														float d1,	float d2,	float a,	float b,								float*param){ srotmg_(&d1,&d2,&a,&b,param); }
extern	void	drotmg_(																													double*d1,	double*d2,	double*a,	double*b,								double*param);
		void 	drotmg(																														double d1,	double d2,	double a,	double b,								double*param){ drotmg_(&d1,&d2,&a,&b,param); }


//xROT
extern	void	srot_(	const int*n,						float *x,			const int*incx,		float *y,			const int*incy,														float*c,	float*s);
		void	srot(	const int n,						float *x,			const int incx,		float *y,			const int incy,														float c,	float s) { srot_(&n,x,&incx,y,&incy,&c,&s); }
//D
/*
//xROTM
//extern	void	srotm_(	const int*n,						float *x,			const int*incx,		float *y,			const int*incy,																				float*param);
//		void	srotm();
//D

//xSWAP
extern	void	sswap_(	const int*n,						float *x,			const int*incx,		float *y,			const int*incy);
		void	sswap(	const int n,						float *x,			const int incx,		float *y,			const int incy) { return sswap_(&n,x,&incx,y,&incy); }
//D C Z

//xSCAL
extern	void	sscal_(	const int*n,	const float*alpha,	float *x,			const int*incx);
		void	sscal(	const int n,	const float alpha,	float *x,			const int incx) { return sscal_(&n,&alpha,x,&incx); }
//D C Z CS ZD

//xCOPY
extern	void	scopy_(	const int*n, 						const float *x,		const int*incx, 	float *y,			const int*incy);
		void	scopy(	const int n, 						const float *x,		const int incx, 	float *y,			const int incy) { return scopy_(&n,x,&incx,y,&incy); }

extern	void	dcopy_(	const int*n, 						const double *x,	const int*incx, 	double *y,			const int*incy);
		void	dcopy(	const int n, 						const double *x,	const int incx, 	double *y,			const int incy) { return dcopy_(&n,x,&incx,y,&incy); }

//extern	void	ccopy_(	const int*n,						const scom *x,		const int*incx,		scom *y,			const int*incy);
//		void	ccopy(	const int n,						const scom *x,		const int incx,		scom *y,			const int*incy) { return ccopy_(&n,x,&incx,y,&incy); }
//		void	zcopy(	const int n,						const void *x,	const int incx,		void *y,		const int incy);

//xAXPY
extern	void 	saxpy_(	const int*n, 	const float*alpha,	const float *x,		const int*incx, 	float *y,			const int*incy);
		void	saxpy(	const int n, 	const float alpha,	const float *x,		const int incx, 	float *y,			const int incy) { return saxpy_(&n,&alpha,x,&incx,y,&incy); }

//D C Z

//xDOT
extern	float	sdot_(	const int*n,						const float *x,		const int*incx,		const float *y,		const int*incy);
		float	sdot(	const int n,						const float *x,		const int incx,		const float *y,		const int incy) { return sdot_(&n,x,&incx,y,&incy); }

extern	double	ddot_(	const int*n,						const double *x,	const int*incx,		const double *y,	const int*incy);
		double	ddot(	const int n,						const double *x,	const int incx,		const double *y,	const int incy) { return ddot_(&n,x,&incx,y,&incy); }
//DS

//xDOTU
//void	cdotu(	const int n,						const void *x,	const int incx,		const void *y,	const int incy,
//				void *ans);
//Z

//xDOTC
//C Z

//xxDOT
//SDS

//xNRM2
extern	float	snrm2_(	const int*n,						const float *x,		const int*incx);
		float	snrm2(	const int n,						const float *x,		const int incx) { return snrm2_(&n,x,&incx); }
//D SC DZ
*/
#endif