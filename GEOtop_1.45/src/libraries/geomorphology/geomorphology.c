
#define Pi 3.14159265358979			

#include "../fluidturtle/turtle.h"

//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

void find_slope(double deltax, double deltay, DOUBLEMATRIX *topo, DOUBLEMATRIX *dzdx, DOUBLEMATRIX *dzdy, long undef){
	
	long r,c,R1,C1,R2,C2;
	long nc=topo->nch;
	long nr=topo->nrh;
	double a, delta;
		
	// Find dzdx.
	for(r=1;r<=nr;r++){
		for(c=1;c<=nc;c++){
			if((long)topo->co[r][c]!=undef){
								
				a=0.0;
				R1=r;
				R2=r;
				C1=c-1;
				C2=c+1;			
				delta=deltax;
				if(R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc){
					if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]!=undef){
						if( (topo->co[R2][C2] - topo->co[r][c]) * (topo->co[r][c] - topo->co[R1][C1]) < 0){
							if( fabs(topo->co[r][c] - topo->co[R1][C1]) > fabs(topo->co[R2][C2] - topo->co[r][c]) ){
								a += (topo->co[r][c] - topo->co[R1][C1]) / delta;
							}else {
								a += (topo->co[R2][C2] - topo->co[r][c]) / delta;
							}
						}else {
							a += (topo->co[R2][C2] - topo->co[R1][C1]) / (2.*delta);
						}
					}else if((long)topo->co[R1][C1]==undef && (long)topo->co[R2][C2]!=undef){
						a += (topo->co[R2][C2] - topo->co[r][c]) / delta;
					}else if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]==undef){
						a += (topo->co[r][c] - topo->co[R1][C1]) / delta;
					}
				}
				dzdx->co[r][c] = a;
				
				a=0.0;
				R1=r+1;
				R2=r-1;
				C1=c;
				C2=c;			
				delta=deltay;
				if(R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc){
					if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]!=undef){
						if( (topo->co[R2][C2] - topo->co[r][c]) * (topo->co[r][c] - topo->co[R1][C1]) < 0){
							if( fabs(topo->co[r][c] - topo->co[R1][C1]) > fabs(topo->co[R2][C2] - topo->co[r][c]) ){
								a += (topo->co[r][c] - topo->co[R1][C1]) / delta;
							}else {
								a += (topo->co[R2][C2] - topo->co[r][c]) / delta;
							}
						}else {
							a += (topo->co[R2][C2] - topo->co[R1][C1]) / (2.*delta);
						}
					}else if((long)topo->co[R1][C1]==undef && (long)topo->co[R2][C2]!=undef){
						a += (topo->co[R2][C2] - topo->co[r][c]) / delta;
					}else if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]==undef){
						a += (topo->co[r][c] - topo->co[R1][C1]) / delta;
					}
				}
				dzdy->co[r][c] = a;
				
				//Some compilers will not allow dzdx and dzdy to both be 0.0 in the atan2 computation.
				//if (fabs(dzdx->co[r][c])<1.E-10) dzdx->co[r][c] = 1.E-10;
				if (fabs(dzdy->co[r][c])<1.E-10) dzdy->co[r][c] = 1.E-10;
				
			}else {
				
				dzdx->co[r][c] = (double)undef;
				dzdy->co[r][c] = (double)undef;
				
			}

		}
	}
}

//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

DOUBLEMATRIX *find_max_slope(DOUBLEMATRIX *topo, DOUBLEMATRIX *dzdx, DOUBLEMATRIX *dzdy, long undef){
	
	long r, c;
	long nc=topo->nch;
	long nr=topo->nrh;
	DOUBLEMATRIX *M;
	
	M=new_doublematrix(nr, nc);
	
	for(r=1;r<=nr;r++){
		for(c=1;c<=nc;c++){
			if((long)topo->co[r][c]!=undef){
				M->co[r][c] = (180./Pi) * atan(pow(pow(dzdx->co[r][c], 2.0) + pow(dzdy->co[r][c], 2.0), 0.5));
			}else {
				M->co[r][c] = (double)undef;
			}

		}
	}
	
	return M;
}

//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

DOUBLEMATRIX *find_aspect(DOUBLEMATRIX *topo, DOUBLEMATRIX *dzdx, DOUBLEMATRIX *dzdy, long undef){
	
	long r, c;
	long nc=topo->nch;
	long nr=topo->nrh;
	DOUBLEMATRIX *M;
	
	M=new_doublematrix(nr, nc);
	
	for(r=1;r<=nr;r++){
		for(c=1;c<=nc;c++){
			if((long)topo->co[r][c]!=undef){
				M->co[r][c] = (180./Pi) * (3.0 / 2.0 * Pi - atan2(dzdy->co[r][c], dzdx->co[r][c]));
				if (M->co[r][c]>=360.0) M->co[r][c] -= 360.0;
			}else {
				M->co[r][c] = (double)undef;
			}		
		}
	}
	
	return M;
}


//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

void curvature(double deltax, double deltay, DOUBLEMATRIX *topo, DOUBLEMATRIX *c1, DOUBLEMATRIX *c2, DOUBLEMATRIX *c3, DOUBLEMATRIX *c4, long undef){
	
	long r,c;
	long R1, R2, C1, C2;
	long nc=topo->nch;
	long nr=topo->nrh;
	double delta;
		
	// Compute the curvature.
	for(r=1;r<=nr;r++){
		for(c=1;c<=nc;c++){
			if((long)topo->co[r][c]!=undef){
				
				c1->co[r][c]=0.0;
				R1=r-1;
				R2=r+1;
				C1=c;
				C2=c;			
				delta=deltay;
				if(R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc){
					if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]!=undef){
						c1->co[r][c] += (topo->co[R1][C1]+topo->co[R2][C2]-2.*topo->co[r][c])/pow(delta,2.);
					}
				}
				
				c2->co[r][c]=0.0;
				R1=r;
				R2=r;
				C1=c+1;
				C2=c-1;			
				delta=deltax;
				if(R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc){
					if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]!=undef){
						c2->co[r][c] += (topo->co[R1][C1]+topo->co[R2][C2]-2.*topo->co[r][c])/pow(delta,2.);
					}
				}
				
				c3->co[r][c]=0.0;
				R1=r-1;
				R2=r+1;
				C1=c-1;
				C2=c+1;			
				delta=sqrt(deltax*deltay);
				if(R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc){
					if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]!=undef){
						c3->co[r][c] += (topo->co[R1][C1]+topo->co[R2][C2]-2.*topo->co[r][c])/pow(delta,2.);
					}
				}				
				
				c4->co[r][c]=0.0;
				R1=r-1;
				R2=r+1;
				C1=c+1;
				C2=c-1;			
				delta=sqrt(deltax*deltay);
				if(R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc){
					if((long)topo->co[R1][C1]!=undef && (long)topo->co[R2][C2]!=undef){
						c4->co[r][c] += (topo->co[R1][C1]+topo->co[R2][C2]-2.*topo->co[r][c])/pow(delta,2.);
					}
				}				
				
				
			}else {
				
				c1->co[r][c] = (double)undef;
				c2->co[r][c] = (double)undef;
				c3->co[r][c] = (double)undef;
				c4->co[r][c] = (double)undef;

			}

		}
	}
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/


void topofilter(DOUBLEMATRIX *Zin, DOUBLEMATRIX *Zout, long novalue, long n){
	
	long r, c, nr, nc, ir, ic, i;
	DOUBLEVECTOR *values;
	long cnt;
	
	values=new_doublevector((2*n+1)*(2*n+1));
	
	nr=Zin->nrh;
	nc=Zin->nch;
	
	for (r=1; r<=nr; r++) {
		for (c=1; c<=nc; c++) {
			if ((long)Zin->co[r][c] != novalue) {
				cnt=0;
				for (ir=-n; ir<=n; ir++) {
					for (ic=-n; ic<=n; ic++) {
						if (r+ir>=1 && r+ir<=nr && c+ic>=1 && c+ic<=nc) {
							if((long)Zin->co[r+ir][c+ic]!=novalue){
								cnt++;
								values->co[cnt]=Zin->co[r+ir][c+ic];
							}
						}
					}
				}
				
				/*order_values(values, cnt);
				 if (fmod(cnt, 2)>1.E-5) {
				 Zout->co[r][c] = values->co[(long)(0.5*(cnt+1))];
				 }else{
				 Zout->co[r][c] = 0.5*(values->co[(long)(0.5*(cnt))]+values->co[(long)(0.5*(cnt)+1)]);
				 }*/
				
				Zout->co[r][c] = 0.;
				for (i=1; i<=cnt; i++) {
					Zout->co[r][c] += values->co[i]/(double)cnt;
				}
				
			}else {
				
				Zout->co[r][c] = (double)novalue;
				
			}
			
		}
	}
	
	free_doublevector(values);
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

void order_values(DOUBLEVECTOR *list, long n){
	
	long i,j,k;
	double min;
	
	for (i=1; i<=n; i++) {
		min = 1.E99;
		for (j=i; j<=n; j++) {
			if (min > list->co[j]){
				min = list->co[j];
				k=j;
			}
		}
		list->co[k] = list->co[i];
		list->co[i] = min;
	}
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

void multipass_topofilter(long ntimes, DOUBLEMATRIX *Zin, DOUBLEMATRIX *Zout, long novalue, long n){
	
	long i, r, c;
	DOUBLEMATRIX *M;
	
	M=new_doublematrix(Zin->nrh, Zin->nch);
	
	for (r=1; r<=Zin->nrh; r++) {
		for (c=1; c<=Zin->nch; c++) {
			Zout->co[r][c] = Zin->co[r][c];
		}
	}
	
	for (i=1; i<=ntimes; i++) {
		
		for (r=1; r<=Zout->nrh; r++) {
			for (c=1; c<=Zout->nch; c++) {
				M->co[r][c] = Zout->co[r][c];
			}
		}
		
		topofilter(M, Zout, novalue, n);
		
	}
	
	free_doublematrix(M);
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

short is_boundary(long r, long c, DOUBLEMATRIX *dem, long novalue){
	
	long ir, ic;
	short yes = 0;
	
	ir=-1;
	ic=0;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=-1;
	ic=1;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=0;
	ic=1;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=1;
	ic=1;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=1;
	ic=0;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=1;
	ic=-1;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=0;
	ic=-1;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	ir=-1;
	ic=-1;
	if( (long)dem->co[r+ir][c+ic]==novalue ) yes = 1;
	
	return yes;
	
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

void find_min_max(DOUBLEMATRIX *M, long novalue, double *max, double *min){
	
	long r, c, nr=M->nrh, nc=M->nch;
	
	*max=-1.E99;
	*min=1.E99;
	
	for (r=1; r<=nr; r++) {
		for (c=1; c<=nc; c++) {
			if ((long)M->co[r][c] != novalue) {
				if(*max < M->co[r][c]) *max = M->co[r][c];
				if(*min > M->co[r][c]) *min = M->co[r][c];
			}
		}
	}
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

long row(double N, long nrows, T_INIT *UV, long novalue){
	
	long cnt;
	
	if(N<UV->U->co[3] || N>UV->U->co[3]+nrows*UV->U->co[1]){
		return novalue;
	}else {
		cnt=0;
		do{
			cnt++;
		}while(UV->U->co[3]+(nrows-cnt)*UV->U->co[1]>N);
		return cnt;
	}	
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

long col(double E, long ncols, T_INIT *UV, long novalue){
	
	long cnt;
	
	if(E<UV->U->co[4] || E>UV->U->co[4]+ncols*UV->U->co[2]){
		return novalue;
	}else{
		cnt=0;
		do{
			cnt++;
		}while(UV->U->co[4]+cnt*UV->U->co[2]<E);
		return cnt;
	}
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

double interp_value(double E, double N, DOUBLEMATRIX *M, DOUBLEMATRIX *Z, T_INIT *UV, long novalue){
	
	double  dN, dE, N0, E0, DN, DE, w1, V;
	long r, c;
	
	r=row(N, Z->nrh, UV, novalue);
	c=col(E, Z->nch, UV, novalue);
	
	if(r==0 || c==0 || (long)Z->co[r][c]==novalue){
		
		V=(double)novalue;
		
	}else{
		
		dN=UV->U->co[1];
		dE=UV->U->co[2];
		
		N0=UV->U->co[3] + (Z->nrh-r+0.5)*dN;
		E0=UV->U->co[4] + (c-0.5)*dE;
		
		DN=(N-N0)/(0.5*dN);
		DE=(E-E0)/(0.5*dE);
		
		if(DN<=DE && DN>=-DE){
			
			if((long)Z->co[r][c+1]!=novalue){
				w1=(E0+dE-E)/dE;
				V=w1*M->co[r][c]+(1.0-w1)*M->co[r][c+1];
			}else{
				V=M->co[r][c];
			}
			
		}else if(DN>=DE && DN>=-DE){
			
			if((long)Z->co[r-1][c]!=novalue){
				w1=(N0+dN-N)/dN;
				V=w1*M->co[r][c]+(1.0-w1)*M->co[r-1][c];
			}else{
				V=M->co[r][c];
			}
			
		}else if(DN>=DE && DN<=-DE){
			
			if((long)Z->co[r][c-1]!=novalue){
				w1=(E-(E0-dE))/dE;
				V=w1*M->co[r][c]+(1.0-w1)*M->co[r][c-1];
			}else{
				V=M->co[r][c];
			}
			
		}else{
			
			if((long)Z->co[r+1][c]!=novalue){
				w1=(N-(N0-dN))/dN;
				V=w1*M->co[r][c]+(1.0-w1)*M->co[r+1][c];
			}else{
				V=M->co[r][c];
			}
			
		}
	}
	
	return(V);
	
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
