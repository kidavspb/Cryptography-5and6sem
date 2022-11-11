#include "tests.hpp"

//Frequency
//LongestRunOfOnes
//Runs
//Serial
//Universal
//LinearComplexity


void Frequency(int n, int epsilon[]) {
    int        i;
    double    f, s_obs, p_value, sum, sqrt2 = 1.41421356237309504880;
    
    sum = 0.0;
    for ( i=0; i<n; i++ )
        sum += 2*(int)epsilon[i]-1;
    s_obs = fabs(sum)/sqrt(n);
    f = s_obs/sqrt2;
    p_value = erfc(f);

    printf("\t\t\t      FREQUENCY TEST\n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\tCOMPUTATIONAL INFORMATION:\n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\t(a) The nth partial sum = %d\n", (int)sum);
    printf("\t\t(b) S_n/n               = %f\n", sum/n);
    printf("\t\t---------------------------------------------\n");

    printf("%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
//    printf("%f\n", p_value);
}

void LongestRunOfOnes(int n, int epsilon[]) {
    double            pval, chi2, pi[7];
    int                run, v_n_obs, N, i, j, K, M, V[7];
    unsigned int    nu[7] = { 0, 0, 0, 0, 0, 0, 0 };

    if ( n < 128 ) {
        printf("\t\t\t  LONGEST RUNS OF ONES TEST\n");
        printf("\t\t---------------------------------------------\n");
        printf("\t\t   n=%d is too short\n", n);
        return;
    }
    if ( n < 6272 ) {
        K = 3;
        M = 8;
        V[0] = 1; V[1] = 2; V[2] = 3; V[3] = 4;
        pi[0] = 0.21484375;
        pi[1] = 0.3671875;
        pi[2] = 0.23046875;
        pi[3] = 0.1875;
    }
    else if ( n < 750000 ) {
        K = 5;
        M = 128;
        V[0] = 4; V[1] = 5; V[2] = 6; V[3] = 7; V[4] = 8; V[5] = 9;
        pi[0] = 0.1174035788;
        pi[1] = 0.242955959;
        pi[2] = 0.249363483;
        pi[3] = 0.17517706;
        pi[4] = 0.102701071;
        pi[5] = 0.112398847;
    }
    else {
        K = 6;
        M = 10000;
            V[0] = 10; V[1] = 11; V[2] = 12; V[3] = 13; V[4] = 14; V[5] = 15; V[6] = 16;
        pi[0] = 0.0882;
        pi[1] = 0.2092;
        pi[2] = 0.2483;
        pi[3] = 0.1933;
        pi[4] = 0.1208;
        pi[5] = 0.0675;
        pi[6] = 0.0727;
    }
    
    N = n/M;
    for ( i=0; i<N; i++ ) {
        v_n_obs = 0;
        run = 0;
        for ( j=0; j<M; j++ ) {
            if ( epsilon[i*M+j] == 1 ) {
                run++;
                if ( run > v_n_obs )
                    v_n_obs = run;
            }
            else
                run = 0;
        }
        if ( v_n_obs < V[0] )
            nu[0]++;
        for ( j=0; j<=K; j++ ) {
            if ( v_n_obs == V[j] )
                nu[j]++;
        }
        if ( v_n_obs > V[K] )
            nu[K]++;
    }

    chi2 = 0.0;
    for ( i=0; i<=K; i++ )
        chi2 += ((nu[i] - N * pi[i]) * (nu[i] - N * pi[i])) / (N * pi[i]);

    pval = cephes_igamc((double)(K/2.0), chi2 / 2.0);

    printf("\t\t\t  LONGEST RUNS OF ONES TEST\n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\tCOMPUTATIONAL INFORMATION:\n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\t(a) N (# of substrings)  = %d\n", N);
    printf("\t\t(b) M (Substring Length) = %d\n", M);
    printf("\t\t(c) Chi^2                = %f\n", chi2);
    printf("\t\t---------------------------------------------\n");
    printf("\t\t      F R E Q U E N C Y\n");
    printf("\t\t---------------------------------------------\n");

    if ( K == 3 ) {
        printf("\t\t  <=1     2     3    >=4   P-value  Assignment");
        printf("\n\t\t %3d %3d %3d  %3d ", nu[0], nu[1], nu[2], nu[3]);
    }
    else if ( K == 5 ) {
        printf("\t\t<=4  5  6  7  8  >=9 P-value  Assignment");
        printf("\n\t\t %3d %3d %3d %3d %3d  %3d ", nu[0], nu[1], nu[2], nu[3], nu[4], nu[5]);
    }
    else {
        printf("\t\t<=10  11  12  13  14  15 >=16 P-value  Assignment");
        printf("\n\t\t %3d %3d %3d %3d %3d %3d  %3d ", nu[0], nu[1], nu[2], nu[3], nu[4], nu[5], nu[6]);
    }
    if ( isNegative(pval) || isGreaterThanOne(pval) )
        printf("WARNING:  P_VALUE IS OUT OF RANGE.\n");

    printf("%s\t\tp_value = %f\n\n", pval < ALPHA ? "FAILURE" : "SUCCESS", pval);
//    printf("%f\n", pval);
}

void Runs(int n, int epsilon[]) {
    int        S, k;
    double    pi, V, erfc_arg, p_value;

    S = 0;
    for ( k=0; k<n; k++ )
        if ( epsilon[k] )
            S++;
    pi = (double)S / (double)n;

    if ( fabs(pi - 0.5) > (2.0 / sqrt(n)) ) {
        printf("\t\t\t\tRUNS TEST\n");
        printf("\t\t------------------------------------------\n");
        printf("\t\tPI ESTIMATOR CRITERIA NOT MET! PI = %f\n", pi);
        p_value = 0.0;
    }
    else {

        V = 1;
        for ( k=1; k<n; k++ )
            if ( epsilon[k] != epsilon[k-1] )
                V++;
    
        erfc_arg = fabs(V - 2.0 * n * pi * (1-pi)) / (2.0 * pi * (1-pi) * sqrt(2*n));
        p_value = erfc(erfc_arg);
        
        printf("\t\t\t\tRUNS TEST\n");
        printf("\t\t------------------------------------------\n");
        printf("\t\tCOMPUTATIONAL INFORMATION:\n");
        printf("\t\t------------------------------------------\n");
        printf("\t\t(a) Pi                        = %f\n", pi);
        printf("\t\t(b) V_n_obs (Total # of runs) = %d\n", (int)V);
        printf("\t\t(c) V_n_obs - 2 n pi (1-pi)\n");
        printf("\t\t    -----------------------   = %f\n", erfc_arg);
        printf("\t\t      2 sqrt(2n) pi (1-pi)\n");
        printf("\t\t------------------------------------------\n");
        if ( isNegative(p_value) || isGreaterThanOne(p_value) )
            printf("WARNING:  P_VALUE IS OUT OF RANGE.\n");

        printf("%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
    }

//    printf("%f\n", p_value);
}

double psi2(int m, int n, int epsilon[]) {
    int                i, j, k, powLen;
    double            sum, numOfBlocks;
    unsigned int    *P;
    
    if ( (m == 0) || (m == -1) )
        return 0.0;
    numOfBlocks = n;
    powLen = (int)pow(2, m+1)-1;
    if ( (P = (unsigned int*)calloc(powLen,sizeof(int)))== NULL ) {
        printf("Serial Test:  Insufficient memory available.\n");
        return 0.0;
    }
    for ( i=1; i<powLen-1; i++ )
        P[i] = 0;      /* INITIALIZE NODES */
    for ( i=0; i<numOfBlocks; i++ ) {         /* COMPUTE FREQUENCY */
        k = 1;
        for ( j=0; j<m; j++ ) {
            if ( epsilon[(i+j)%n] == 0 )
                k *= 2;
            else if ( epsilon[(i+j)%n] == 1 )
                k = 2*k+1;
        }
        P[k-1]++;
    }
    sum = 0.0;
    for ( i=(int)pow(2, m)-1; i<(int)pow(2, m+1)-1; i++ )
        sum += pow(P[i], 2);
    sum = (sum * pow(2, m)/(double)n) - (double)n;
    free(P);
    
    return sum;
}
void Serial(int m, int n, int epsilon[]) {
    double    p_value1, p_value2, psim0, psim1, psim2, del1, del2;
    
    psim0 = psi2(m, n, epsilon);
    psim1 = psi2(m-1, n, epsilon);
    psim2 = psi2(m-2, n, epsilon);
    del1 = psim0 - psim1;
    del2 = psim0 - 2.0*psim1 + psim2;
    p_value1 = cephes_igamc(pow(2, m-1)/2, del1/2.0);
    p_value2 = cephes_igamc(pow(2, m-2)/2, del2/2.0);
    
    printf("\t\t\t       SERIAL TEST\n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\t COMPUTATIONAL INFORMATION:          \n");
    printf("\t\t---------------------------------------------\n");
    printf("\t\t(a) Block length    (m) = %d\n", m);
    printf("\t\t(b) Sequence length (n) = %d\n", n);
    printf("\t\t(c) Psi_m               = %f\n", psim0);
    printf("\t\t(d) Psi_m-1             = %f\n", psim1);
    printf("\t\t(e) Psi_m-2             = %f\n", psim2);
    printf("\t\t(f) Del_1               = %f\n", del1);
    printf("\t\t(g) Del_2               = %f\n", del2);
    printf("\t\t---------------------------------------------\n");

    printf("%s\t\tp_value1 = %f\n", p_value1 < ALPHA ? "FAILURE" : "SUCCESS", p_value1);
//    printf("%f\n", p_value1);

    printf("%s\t\tp_value2 = %f\n\n", p_value2 < ALPHA ? "FAILURE" : "SUCCESS", p_value2);
//    printf("%f\n", p_value2);
}

void Universal(int n, int epsilon[]) {
    int        i, j, p, L, Q, K;
    double    arg, sqrt2, sigma, phi, sum, p_value, c;
    long    *T, decRep;
    double    expected_value[17] = { 0, 0, 0, 0, 0, 0, 5.2177052, 6.1962507, 7.1836656,
                8.1764248, 9.1723243, 10.170032, 11.168765,
                12.168070, 13.167693, 14.167488, 15.167379 };
    double   variance[17] = { 0, 0, 0, 0, 0, 0, 2.954, 3.125, 3.238, 3.311, 3.356, 3.384,
                3.401, 3.410, 3.416, 3.419, 3.421 };
    
    /* * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * THE FOLLOWING REDEFINES L, SHOULD THE CONDITION:     n >= 1010*2^L*L       *
     * NOT BE MET, FOR THE BLOCK LENGTH L.                                        *
     * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    L = 5;
    if ( n >= 387840 )     L = 6;
    if ( n >= 904960 )     L = 7;
    if ( n >= 2068480 )    L = 8;
    if ( n >= 4654080 )    L = 9;
    if ( n >= 10342400 )   L = 10;
    if ( n >= 22753280 )   L = 11;
    if ( n >= 49643520 )   L = 12;
    if ( n >= 107560960 )  L = 13;
    if ( n >= 231669760 )  L = 14;
    if ( n >= 496435200 )  L = 15;
    if ( n >= 1059061760 ) L = 16;
    
    Q = 10*(int)pow(2, L);
    K = (int) (floor(n/L) - (double)Q);                 /* BLOCKS TO TEST */
    
    p = (int)pow(2, L);
    if ( (L < 6) || (L > 16) || ((double)Q < 10*pow(2, L)) ||
         ((T = (long *)calloc(p, sizeof(long))) == NULL) ) {
        printf("\t\tUNIVERSAL STATISTICAL TEST\n");
        printf("\t\t---------------------------------------------\n");
        printf("\t\tERROR:  L IS OUT OF RANGE.\n");
        printf("\t\t-OR- :  Q IS LESS THAN %f.\n", 10*pow(2, L));
        printf("\t\t-OR- :  Unable to allocate T.\n");
        return;
    }
    
    /* COMPUTE THE EXPECTED:  Formula 16, in Marsaglia's Paper */
    c = 0.7 - 0.8/(double)L + (4 + 32/(double)L)*pow(K, -3/(double)L)/15;
    sigma = c * sqrt(variance[L]/(double)K);
    sqrt2 = sqrt(2);
    sum = 0.0;
    for ( i=0; i<p; i++ )
        T[i] = 0;
    for ( i=1; i<=Q; i++ ) {        /* INITIALIZE TABLE */
        decRep = 0;
        for ( j=0; j<L; j++ )
            decRep += epsilon[(i-1)*L+j] * (long)pow(2, L-1-j);
        T[decRep] = i;
    }
    for ( i=Q+1; i<=Q+K; i++ ) {     /* PROCESS BLOCKS */
        decRep = 0;
        for ( j=0; j<L; j++ )
            decRep += epsilon[(i-1)*L+j] * (long)pow(2, L-1-j);
        sum += log(i - T[decRep])/log(2);
        T[decRep] = i;
    }
    phi = (double)(sum/(double)K);

    printf("\t\tUNIVERSAL STATISTICAL TEST\n");
    printf("\t\t--------------------------------------------\n");
    printf("\t\tCOMPUTATIONAL INFORMATION:\n");
    printf("\t\t--------------------------------------------\n");
    printf("\t\t(a) L         = %d\n", L);
    printf("\t\t(b) Q         = %d\n", Q);
    printf("\t\t(c) K         = %d\n", K);
    printf("\t\t(d) sum       = %f\n", sum);
    printf("\t\t(e) sigma     = %f\n", sigma);
    printf("\t\t(f) variance  = %f\n", variance[L]);
    printf("\t\t(g) exp_value = %f\n", expected_value[L]);
    printf("\t\t(h) phi       = %f\n", phi);
    printf("\t\t(i) WARNING:  %d bits were discarded.\n", n-(Q+K)*L);
    printf("\t\t-----------------------------------------\n");

    arg = fabs(phi-expected_value[L])/(sqrt2 * sigma);
    p_value = erfc(arg);
    if ( isNegative(p_value) || isGreaterThanOne(p_value) )
        printf("\t\tWARNING:  P_VALUE IS OUT OF RANGE\n");

    printf("%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
//    printf("%f\n", p_value);
    
    free(T);
}

void LinearComplexity(int M, int n, int epsilon[]) {
    int       i, ii, j, d, N, L, m, N_, parity, sign, K = 6;
    double    p_value, T_, mean, nu[7], chi2;
    double    pi[7] = { 0.01047, 0.03125, 0.12500, 0.50000, 0.25000, 0.06250, 0.020833 };
    unsigned int  *T = NULL, *P = NULL, *B_ = NULL, *C = NULL;
    
    N = (int)floor(n/M);
    if ( ((B_ = (unsigned int *) calloc(M, sizeof(unsigned int))) == NULL) ||
         ((C  = (unsigned int *) calloc(M, sizeof(unsigned int))) == NULL) ||
         ((P  = (unsigned int *) calloc(M, sizeof(unsigned int))) == NULL) ||
         ((T  = (unsigned int *) calloc(M, sizeof(unsigned int))) == NULL) ) {
        printf("Insufficient Memory for Work Space:: Linear Complexity Test\n");
        if ( B_ != NULL )
            free(B_);
        if ( C != NULL )
            free(C);
        if ( P != NULL )
            free(P);
        if ( T != NULL )
            free(T);
        return;
    }


    printf("-----------------------------------------------------\n");
    printf("\tL I N E A R  C O M P L E X I T Y\n");
    printf("-----------------------------------------------------\n");
    printf("\tM (substring length)     = %d\n", M);
    printf("\tN (number of substrings) = %d\n", N);
    printf("-----------------------------------------------------\n");
    printf("        F R E Q U E N C Y                            \n");
    printf("-----------------------------------------------------\n");
    printf("  C0   C1   C2   C3   C4   C5   C6    CHI2    P-value\n");
    printf("-----------------------------------------------------\n");
    printf("\tNote: %d bits were discarded!\n", n%M);

    for ( i=0; i<K+1; i++ )
        nu[i] = 0.00;
    for ( ii=0; ii<N; ii++ ) {
        for ( i=0; i<M; i++ ) {
            B_[i] = 0;
            C[i] = 0;
            T[i] = 0;
            P[i] = 0;
        }
        L = 0;
        m = -1;
        d = 0;
        C[0] = 1;
        B_[0] = 1;
        
        /* DETERMINE LINEAR COMPLEXITY */
        N_ = 0;
        while ( N_ < M ) {
            d = (int)epsilon[ii*M+N_];
            for ( i=1; i<=L; i++ )
                d += C[i] * epsilon[ii*M+N_-i];
            d = d%2;
            if ( d == 1 ) {
                for ( i=0; i<M; i++ ) {
                    T[i] = C[i];
                    P[i] = 0;
                }
                for ( j=0; j<M; j++ )
                    if ( B_[j] == 1 )
                        P[j+N_-m] = 1;
                for ( i=0; i<M; i++ )
                    C[i] = (C[i] + P[i])%2;
                if ( L <= N_/2 ) {
                    L = N_ + 1 - L;
                    m = N_;
                    for ( i=0; i<M; i++ )
                        B_[i] = T[i];
                }
            }
            N_++;
        }
        if ( (parity = (M+1)%2) == 0 )
            sign = -1;
        else
            sign = 1;
        mean = M/2.0 + (9.0+sign)/36.0 - 1.0/pow(2, M) * (M/3.0 + 2.0/9.0);
        if ( (parity = M%2) == 0 )
            sign = 1;
        else
            sign = -1;
        T_ = sign * (L - mean) + 2.0/9.0;
        
        if ( T_ <= -2.5 )
            nu[0]++;
        else if ( T_ > -2.5 && T_ <= -1.5 )
            nu[1]++;
        else if ( T_ > -1.5 && T_ <= -0.5 )
            nu[2]++;
        else if ( T_ > -0.5 && T_ <= 0.5 )
            nu[3]++;
        else if ( T_ > 0.5 && T_ <= 1.5 )
            nu[4]++;
        else if ( T_ > 1.5 && T_ <= 2.5 )
            nu[5]++;
        else
            nu[6]++;
    }
    chi2 = 0.00;
    for ( i=0; i<K+1; i++ )
        printf("%4d ", (int)nu[i]);
    for ( i=0; i<K+1; i++ )
        chi2 += pow(nu[i]-N*pi[i], 2) / (N*pi[i]);
    p_value = cephes_igamc(K/2.0, chi2/2.0);

    printf("%9.6f%9.6f\n", chi2, p_value);
    printf("%f\n", p_value);

    free(B_);
    free(P);
    free(C);
    free(T);
}



static const double    rel_error = 1E-12;

double MACHEP = 1.11022302462515654042E-16;        // 2**-53
double MAXLOG = 7.09782712893383996732224E2;    // log(MAXNUM)
double MAXNUM = 1.7976931348623158E308;            // 2**1024*(1-MACHEP)
double PI     = 3.14159265358979323846;            // pi, duh!

static double big = 4.503599627370496e15;
static double biginv =  2.22044604925031308085e-16;

int sgngam = 0;

double
cephes_igamc(double a, double x)
{
    double ans, ax, c, yc, r, t, y, z;
    double pk, pkm1, pkm2, qk, qkm1, qkm2;

    if ( (x <= 0) || ( a <= 0) )
        return( 1.0 );

    if ( (x < 1.0) || (x < a) )
        return( 1.e0 - cephes_igam(a,x) );

    ax = a * log(x) - x - cephes_lgam(a);

    if ( ax < -MAXLOG ) {
        printf("igamc: UNDERFLOW\n");
        return 0.0;
    }
    ax = exp(ax);

    /* continued fraction */
    y = 1.0 - a;
    z = x + y + 1.0;
    c = 0.0;
    pkm2 = 1.0;
    qkm2 = x;
    pkm1 = x + 1.0;
    qkm1 = z * x;
    ans = pkm1/qkm1;

    do {
        c += 1.0;
        y += 1.0;
        z += 2.0;
        yc = y * c;
        pk = pkm1 * z  -  pkm2 * yc;
        qk = qkm1 * z  -  qkm2 * yc;
        if ( qk != 0 ) {
            r = pk/qk;
            t = fabs( (ans - r)/r );
            ans = r;
        }
        else
            t = 1.0;
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        if ( fabs(pk) > big ) {
            pkm2 *= biginv;
            pkm1 *= biginv;
            qkm2 *= biginv;
            qkm1 *= biginv;
        }
    } while ( t > MACHEP );

    return ans*ax;
}

double
cephes_igam(double a, double x)
{
    double ans, ax, c, r;

    if ( (x <= 0) || ( a <= 0) )
        return 0.0;

    if ( (x > 1.0) && (x > a ) )
        return 1.e0 - cephes_igamc(a,x);

    /* Compute  x**a * exp(-x) / gamma(a)  */
    ax = a * log(x) - x - cephes_lgam(a);
    if ( ax < -MAXLOG ) {
        printf("igam: UNDERFLOW\n");
        return 0.0;
    }
    ax = exp(ax);

    /* power series */
    r = a;
    c = 1.0;
    ans = 1.0;

    do {
        r += 1.0;
        c *= x/r;
        ans += c;
    } while ( c/ans > MACHEP );

    return ans * ax/a;
}


/* A[]: Stirling's formula expansion of log gamma
 * B[], C[]: log gamma function between 2 and 3
 */
static unsigned short A[] = {
    0x6661,0x2733,0x9850,0x3f4a,
    0xe943,0xb580,0x7fbd,0xbf43,
    0x5ebb,0x20dc,0x019f,0x3f4a,
    0xa5a1,0x16b0,0xc16c,0xbf66,
    0x554b,0x5555,0x5555,0x3fb5
};
static unsigned short B[] = {
    0x6761,0x8ff3,0x8901,0xc095,
    0xb93e,0x355b,0xf234,0xc0e2,
    0x89e5,0xf890,0x3d73,0xc114,
    0xdb51,0xf994,0xbc82,0xc131,
    0xf20b,0x0219,0x4589,0xc13a,
    0x055e,0x5418,0x0c67,0xc12a
};
static unsigned short C[] = {
    /*0x0000,0x0000,0x0000,0x3ff0,*/
    0x12b2,0x1cf3,0xfd0d,0xc075,
    0xd757,0x7b89,0xaa0d,0xc0d0,
    0x4c9b,0xb974,0xeb84,0xc10a,
    0x0043,0x7195,0x6286,0xc131,
    0xf34c,0x892f,0x5255,0xc143,
    0xe14a,0x6a11,0xce4b,0xc13e
};

#define MAXLGM 2.556348e305


/* Logarithm of gamma function */
double
cephes_lgam(double x)
{
    double    p, q, u, w, z;
    int        i;

    sgngam = 1;

    if ( x < -34.0 ) {
        q = -x;
        w = cephes_lgam(q); /* note this modifies sgngam! */
        p = floor(q);
        if ( p == q ) {
lgsing:
            goto loverf;
        }
        i = (int)p;
        if ( (i & 1) == 0 )
            sgngam = -1;
        else
            sgngam = 1;
        z = q - p;
        if ( z > 0.5 ) {
            p += 1.0;
            z = p - q;
        }
        z = q * sin( PI * z );
        if ( z == 0.0 )
            goto lgsing;
        /*      z = log(PI) - log( z ) - w;*/
        z = log(PI) - log( z ) - w;
        return z;
    }

    if ( x < 13.0 ) {
        z = 1.0;
        p = 0.0;
        u = x;
        while ( u >= 3.0 ) {
            p -= 1.0;
            u = x + p;
            z *= u;
        }
        while ( u < 2.0 ) {
            if ( u == 0.0 )
                goto lgsing;
            z /= u;
            p += 1.0;
            u = x + p;
        }
        if ( z < 0.0 ) {
            sgngam = -1;
            z = -z;
        }
        else
            sgngam = 1;
        if ( u == 2.0 )
            return( log(z) );
        p -= 2.0;
        x = x + p;
        p = x * cephes_polevl( x, (double *)B, 5 ) / cephes_p1evl( x, (double *)C, 6);

        return log(z) + p;
    }

    if ( x > MAXLGM ) {
loverf:
        printf("lgam: OVERFLOW\n");

        return sgngam * MAXNUM;
    }

    q = ( x - 0.5 ) * log(x) - x + log( sqrt( 2*PI ) );
    if ( x > 1.0e8 )
        return q;

    p = 1.0/(x*x);
    if ( x >= 1000.0 )
        q += ((   7.9365079365079365079365e-4 * p
                - 2.7777777777777777777778e-3) *p
                + 0.0833333333333333333333) / x;
    else
        q += cephes_polevl( p, (double *)A, 4 ) / x;

    return q;
}

double
cephes_polevl(double x, double *coef, int N)
{
    double    ans;
    int        i;
    double    *p;

    p = coef;
    ans = *p++;
    i = N;

    do
        ans = ans * x  +  *p++;
    while ( --i );

    return ans;
}

double
cephes_p1evl(double x, double *coef, int N)
{
    double    ans;
    double    *p;
    int        i;

    p = coef;
    ans = x + *p++;
    i = N-1;

    do
        ans = ans * x  + *p++;
    while ( --i );

    return ans;
}

double
cephes_erf(double x)
{
    static const double two_sqrtpi = 1.128379167095512574;
    double    sum = x, term = x, xsqr = x * x;
    int        j = 1;

    if ( fabs(x) > 2.2 )
        return 1.0 - cephes_erfc(x);

    do {
        term *= xsqr/j;
        sum -= term/(2*j+1);
        j++;
        term *= xsqr/j;
        sum += term/(2*j+1);
        j++;
    } while ( fabs(term)/sum > rel_error );

    return two_sqrtpi*sum;
}

double
cephes_erfc(double x)
{
    static const double one_sqrtpi = 0.564189583547756287;
    double    a = 1, b = x, c = x, d = x*x + 0.5;
    double    q1, q2 = b/d, n = 1.0, t;

    if ( fabs(x) < 2.2 )
        return 1.0 - cephes_erf(x);
    if ( x < 0 )
        return 2.0 - cephes_erfc(-x);

    do {
        t = a*n + b*x;
        a = b;
        b = t;
        t = c*n + d*x;
        c = d;
        d = t;
        n += 0.5;
        q1 = q2;
        q2 = b/d;
    } while ( fabs(q1-q2)/q2 > rel_error );

    return one_sqrtpi*exp(-x*x)*q2;
}


double
cephes_normal(double x)
{
    double arg, result, sqrt2=1.414213562373095048801688724209698078569672;

    if (x > 0) {
        arg = x/sqrt2;
        result = 0.5 * ( 1 + erf(arg) );
    }
    else {
        arg = -x/sqrt2;
        result = 0.5 * ( 1 - erf(arg) );
    }

    return( result);
}
