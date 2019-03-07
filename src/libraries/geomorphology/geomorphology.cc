
#define Pi 3.14159265358979

#include "turtle.h"

//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

void find_slope(double deltax, double deltay, Matrix<double> *topo,
                Matrix<double> *dzdx, Matrix<double> *dzdy, long undef)
{

    long r,c,R1,C1,R2,C2;
    long nc=topo->nch;
    long nr=topo->nrh;
    double a, delta;

    /**Find dzdx*/
    for (r=1; r<=nr; r++)
    {
        for (c=1; c<=nc; c++)
        {
            if ((long)(*topo)(r,c)!=undef)
            {

                a=0.0;
                R1=r;
                R2=r;
                C1=c-1;
                C2=c+1;
                delta=deltax;

                if (R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc)
                {
                    if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        if ( ((*topo)(R2,C2) - (*topo)(r,c)) * ((*topo)(r,c) - (*topo)(R1,C1)) < 0)
                        {
                            if ( fabs((*topo)(r,c) - (*topo)(R1,C1)) > fabs((*topo)(R2,C2) - (*topo)(r,c)) )
                            {
                                a += ((*topo)(r,c) - (*topo)(R1,C1)) / delta;
                            }
                            else
                            {
                                a += ((*topo)(R2,C2) - (*topo)(r,c)) / delta;
                            }
                        }
                        else
                        {
                            a += ((*topo)(R2,C2) - (*topo)(R1,C1)) / (2.*delta);
                        }
                    }
                    else if ((long)(*topo)(R1,C1)==undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        a += ((*topo)(R2,C2) - (*topo)(r,c)) / delta;
                    }
                    else if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)==undef)
                    {
                        a += ((*topo)(r,c) - (*topo)(R1,C1)) / delta;
                    }
                }
                (*dzdx)(r,c) = a;

                a=0.0;
                R1=r+1;
                R2=r-1;
                C1=c;
                C2=c;
                delta=deltay;

                if (R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc)
                {
                    if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        if ( ((*topo)(R2,C2) - (*topo)(r,c)) * ((*topo)(r,c) - (*topo)(R1,C1)) < 0)
                        {
                            if ( fabs((*topo)(r,c) - (*topo)(R1,C1)) > fabs((*topo)(R2,C2) -
                                                                            (*topo)(r,c)) )
                            {
                                a += ((*topo)(r,c) - (*topo)(R1,C1)) / delta;
                            }
                            else
                            {
                                a += ((*topo)(R2,C2) - (*topo)(r,c)) / delta;
                            }
                        }
                        else
                        {
                            a += ((*topo)(R2,C2) - (*topo)(R1,C1)) / (2.*delta);
                        }
                    }
                    else if ((long)(*topo)(R1,C1)==undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        a += ((*topo)(R2,C2) - (*topo)(r,c)) / delta;
                    }
                    else if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)==undef)
                    {
                        a += ((*topo)(r,c) - (*topo)(R1,C1)) / delta;
                    }
                }
                (*dzdy)(r,c) = a;

                //Some compilers will not allow dzdx and dzdy to both be 0.0 in the atan2 computation.
                //if (fabs((*dzdx)(r,c))<1.E-10) (*dzdx)(r,c) = 1.E-10;
                if (fabs((*dzdy)(r,c))<1.E-10) (*dzdy)(r,c) = 1.E-10;

            }
            else
            {

                (*dzdx)(r,c) = (double)undef;
                (*dzdy)(r,c) = (double)undef;
            }
        }
    }
}

//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

Matrix<double> * find_max_slope(Matrix<double> *topo, Matrix<double> *dzdx,
                                Matrix<double> *dzdy, long undef)
{

    long r, c;
    long nc = topo->nch;
    long nr = topo->nrh;
    Matrix<double> *M;

    M = new Matrix<double>{nr, nc};

    for (r=1; r<=nr; r++)
    {
        for (c=1; c<=nc; c++)
        {
            if ((long)(*topo)(r,c)!=undef)
            {
                (*M)(r,c) = (180./Pi) * atan(pow(pow((*dzdx)(r,c), 2.0) + pow((*dzdy)(r,c), 2.0), 0.5));
            }
            else
            {
                (*M)(r,c) = (double)undef;
            }
        }
    }
    return M;
}

//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

Matrix<double> * find_aspect(Matrix<double> *topo, Matrix<double> *dzdx,
                             Matrix<double> *dzdy, long undef)
{

    long r, c;
    long nc = topo->nch;
    long nr = topo->nrh;
    Matrix<double> *M;

    M = new Matrix<double>{nr, nc};

    for (r=1; r<=nr; r++)
    {
        for (c=1; c<=nc; c++)
        {
            if ((long)(*topo)(r,c)!=undef)
            {
                (*M)(r,c) = (180./Pi) * (3.0 / 2.0 * Pi - atan2((*dzdy)(r,c), (*dzdx)(r,c)));

                if ((*M)(r,c)>=360.0)
                    (*M)(r,c) -= 360.0;
            }
            else
            {
                (*M)(r,c) = (double)undef;
            }
        }
    }
    return M;
}


//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************

void curvature(double deltax, double deltay, Matrix<double> *topo,
               Matrix<double> *c1, Matrix<double> *c2, Matrix<double> *c3, Matrix<double> *c4,
               long undef)
{

    long r,c;
    long R1, R2, C1, C2;
    long nc=topo->nch;
    long nr=topo->nrh;
    double delta;

    // Compute the curvature.
    for (r=1; r<=nr; r++)
    {
        for (c=1; c<=nc; c++)
        {
            if ((long)(*topo)(r,c)!=undef)
            {

                (*c1)(r,c)=0.0;
                R1=r-1;
                R2=r+1;
                C1=c;
                C2=c;
                delta=deltay;
                if (R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc)
                {
                    if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        (*c1)(r,c) += ((*topo)(R1,C1)+(*topo)(R2,C2)-2.*(*topo)(r,c))/pow(
                                delta,2.);
                    }
                }

                (*c2)(r,c)=0.0;
                R1=r;
                R2=r;
                C1=c+1;
                C2=c-1;
                delta=deltax;
                if (R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc)
                {
                    if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        (*c2)(r,c) += ((*topo)(R1,C1)+(*topo)(R2,C2)-2.*(*topo)(r,c))/pow(
                                delta,2.);
                    }
                }

                (*c3)(r,c)=0.0;
                R1=r-1;
                R2=r+1;
                C1=c-1;
                C2=c+1;
                delta=sqrt(deltax*deltay);
                if (R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc)
                {
                    if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        (*c3)(r,c) += ((*topo)(R1,C1)+(*topo)(R2,C2)-2.*(*topo)(r,c))/pow(
                                delta,2.);
                    }
                }

                (*c4)(r,c)=0.0;
                R1=r-1;
                R2=r+1;
                C1=c+1;
                C2=c-1;
                delta=sqrt(deltax*deltay);
                if (R1>=1 && R1<=nr && R2>=1 && R2<=nr && C1>=1 && C1<=nc && C2>=1 && C2<=nc)
                {
                    if ((long)(*topo)(R1,C1)!=undef && (long)(*topo)(R2,C2)!=undef)
                    {
                        (*c4)(r,c) += ((*topo)(R1,C1)+(*topo)(R2,C2)-2.*(*topo)(r,c))/pow(
                                delta,2.);
                    }
                }


            }
            else
            {

                (*c1)(r,c) = (double)undef;
                (*c2)(r,c) = (double)undef;
                (*c3)(r,c) = (double)undef;
                (*c4)(r,c) = (double)undef;

            }

        }
    }
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/


void topofilter(Matrix<double> *Zin, Matrix<double> *Zout, long novalue, long n) {

    long r, c, nr, nc, ir, ic, i;
    std::unique_ptr<Vector<double>> values;
    long cnt;

    values.reset(new Vector<double>{(2*n+1)*(2*n+1)});

    nr=Zin->nrh;
    nc=Zin->nch;

    for (r=1; r<=nr; r++)
    {
        for (c=1; c<=nc; c++)
        {
            if ((long)(*Zin)(r,c) != novalue)
            {
                cnt=0;
                for (ir=-n; ir<=n; ir++)
                {
                    for (ic=-n; ic<=n; ic++)
                    {
                        if (r+ir>=1 && r+ir<=nr && c+ic>=1 && c+ic<=nc)
                        {
                            if ((long)(*Zin)(r+ir,c+ic)!=novalue)
                            {
                                cnt++;
                                (*values)(cnt)=(*Zin)(r+ir,c+ic);
                            }
                        }
                    }
                }

                /*order_values(values, cnt);
                 if (fmod(cnt, 2)>1.E-5) {
                 (*Zout)(r,c) = values->co[(long)(0.5*(cnt+1))];
                 }else{
                 (*Zout)(r,c) = 0.5*(values->co[(long)(0.5*(cnt))]+values->co[(long)(0.5*(cnt)+1)]);
                 }*/

                (*Zout)(r,c) = 0.;
                for (i=1; i<=cnt; i++)
                {
                    (*Zout)(r,c) += (*values)(i)/(double)cnt;
                }

            }
            else
            {

                (*Zout)(r,c) = (double)novalue;

            }

        }
    }

}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

void order_values(Vector<double>* list, long n)
{

    long i,j,k=0;
    double min;

    for (i=1; i<=n; i++)
    {
        min = 1.E99;
        for (j=i; j<=n; j++)
        {
            if (min > list->co[j])
            {
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

void multipass_topofilter(long ntimes, Matrix<double> *Zin, Matrix<double> *Zout, long novalue, long n)
{

    long i, r, c;
    Matrix<double> *M;

    M = new Matrix<double>{Zin->nrh, Zin->nch};

    for (r=1; r<=Zin->nrh; r++)
    {
        for (c=1; c<=Zin->nch; c++)
        {
            (*Zout)(r,c) = (*Zin)(r,c);
        }
    }

    for (i=1; i<=ntimes; i++)
    {

        for (r=1; r<=Zout->nrh; r++)
        {
            for (c=1; c<=Zout->nch; c++)
            {
                (*M)(r,c) = (*Zout)(r,c);
            }
        }

        topofilter(M, Zout, novalue, n);

    }

    delete M;
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

short is_boundary(long r, long c, Matrix<double> *dem, long novalue)
{

    long ir, ic;
    short yes = 0;

    ir=-1;
    ic=0;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=-1;
    ic=1;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=0;
    ic=1;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=1;
    ic=1;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=1;
    ic=0;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=1;
    ic=-1;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=0;
    ic=-1;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    ir=-1;
    ic=-1;
    if ( (long)(*dem)(r+ir,c+ic)==novalue ) yes = 1;

    return yes;

}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

void find_min_max(Matrix<double> *M, long novalue, double *max, double *min)
{

    long r, c, nr=M->nrh, nc=M->nch;

    *max=-1.E99;
    *min=1.E99;

    for (r=1; r<=nr; r++)
    {
        for (c=1; c<=nc; c++)
        {
            if ((long)(*M)(r,c) != novalue)
            {
                if (*max < (*M)(r,c)) *max = (*M)(r,c);
                if (*min > (*M)(r,c)) *min = (*M)(r,c);
            }
        }
    }
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

long row(double N, long nrows, T_INIT *UV, long novalue)
{

    long cnt;

    if (N<(*UV->U)(3) || N>(*UV->U)(3)+nrows*(*UV->U)(1))
    {
        return novalue;

    }
    else
    {
        cnt=0;
        do
        {
            cnt++;
        }
        while ((*UV->U)(3)+(nrows-cnt)*(*UV->U)(1)>N);
        return cnt;
    }
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

long col(double E, long ncols, T_INIT *UV, long novalue)
{

    long cnt;

    if (E<(*UV->U)(4) || E>(*UV->U)(4)+ncols*(*UV->U)(2))
    {
        return novalue;
    }
    else
    {
        cnt=0;
        do
        {
            cnt++;
        }
        while ((*UV->U)(4)+cnt*(*UV->U)(2)<E);
        return cnt;
    }
}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

double topo_from_origin(double **topo, double E, double N, long ncols,
                        long nrows, T_INIT *UV, long novalue)
{

    return topo[row(N, nrows, UV, novalue)][col(E, ncols, UV, novalue)];

}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

double interp_value(double E, double N, Matrix<double> *M, Matrix<double> *Z,
                    T_INIT *UV, long novalue)
{

    double  dN, dE, N0, E0, DN, DE, w1, V;
    long r, c;

    r=row(N, Z->nrh, UV, novalue);
    c=col(E, Z->nch, UV, novalue);

    if (r==0 || c==0 || (long)(*Z)(r,c)==novalue)
    {

        V=(double)novalue;

    }
    else
    {

        dN=(*UV->U)(1);
        dE=(*UV->U)(2);

        N0=(*UV->U)(3) + (Z->nrh-r+0.5)*dN;
        E0=(*UV->U)(4) + (c-0.5)*dE;

        DN=(N-N0)/(0.5*dN);
        DE=(E-E0)/(0.5*dE);

        if (DN<=DE && DN>=-DE)
        {

            if ((long)(*Z)(r,c+1)!=novalue)
            {
                w1=(E0+dE-E)/dE;
                V=w1*(*M)(r,c)+(1.0-w1) * (*M)(r,c+1);
            }
            else
            {
                V=(*M)(r,c);
            }

        }
        else if (DN>=DE && DN>=-DE)
        {

            if ((long)(*Z)(r-1,c)!=novalue)
            {
                w1=(N0+dN-N)/dN;
                V=w1*(*M)(r,c)+(1.0-w1)*(*M)(r-1,c);
            }
            else
            {
                V=(*M)(r,c);
            }

        }
        else if (DN>=DE && DN<=-DE)
        {

            if ((long)(*Z)(r,c-1)!=novalue)
            {
                w1=(E-(E0-dE))/dE;
                V=w1*(*M)(r,c)+(1.0-w1)*(*M)(r,c-1);
            }
            else
            {
                V=(*M)(r,c);
            }

        }
        else
        {

            if ((long)(*Z)(r+1,c)!=novalue)
            {
                w1=(N-(N0-dN))/dN;
                V=w1*(*M)(r,c)+(1.0-w1)*(*M)(r+1,c);
            }
            else
            {
                V=(*M)(r,c);
            }

        }
    }

    return (V);

}

/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
