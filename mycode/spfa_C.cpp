/* 
	 shortest path fast algorithm, a faster way to calculate shortest path
 
 *   Ti Liang from Shandong University
*/

/* common functions */
#include "common_matlab.h"
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

#define N 2005
#define inff 99999999

void spfa_allpair(double *dis_mat, double *ang_mat,
						  double *X, double *Y, int n_V,
						  double *E, int n_E);
double dis[N];
double dis2[N];
double angle[N];
bool flag[N];
double ans[N][N];
int n,m;
struct node
{
    int en;
	double len;
};
vector<node>e[N];
/*-----------------------------------------------------------------------
     [dis_mat,ang_mat] = spfa_C(X,Y,E)

 ------------------------------------------------------------------------*/
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
    /* Input data */
	double	*X	= mxGetPr(prhs[0]);
	double	*Y	= mxGetPr(prhs[1]);
    double	*E	= mxGetPr(prhs[2]);
    int		n_V	= mxGetM(prhs[0]);		/* Number of nodes */
    int		n_E	= mxGetM(prhs[2]);		/* Number of edges */
    
    n=n_V;
    m=n_E;
    
    /* Output data */
    mxArray	*pMxDisMat	= mxCreateDoubleMatrix(n_V,n_V,mxREAL);
    mxArray	*pMxAngMat	= mxCreateDoubleMatrix(n_V,n_V,mxREAL);
    double	*dis_mat	= mxGetPr(pMxDisMat);
    double	*ang_mat	= mxGetPr(pMxAngMat);

	/* call algorithm */
	spfa_allpair(dis_mat, ang_mat,
						 X, Y, n_V,
						 E, n_E);

    /* Return */
    plhs[0] = pMxDisMat;
    plhs[1] = pMxAngMat;
}


void spfa(int st)
{
    int i,j;
    queue<int>q;
    for(i=0;i<n;i++)
    {
        dis[i]=inff;
        flag[i]=false;
    }
    dis[st]=0;
    flag[st]=true;
    q.push(st);
    while(!q.empty())
    {
       
		int sta=q.front(); 
        q.pop();
        flag[sta]=false;
        for(i=0;i<e[sta].size();i++)
        {
            int en=e[sta][i].en;
            double len=e[sta][i].len;
            if(dis[en]>len+dis[sta])
            {
                dis[en]=len+dis[sta];
                if(dis[en]!=dis2[en])
                angle[en]=angle[sta];
                if(!flag[en])
                {
                    flag[en]=true;
                    q.push(en);
                }
            }
        }
    }
}
//----------------------------------------------------------------------
void spfa_allpair(double *dis_mat, double *ang_mat,
						  double *X, double *Y, int n_V,
						  double *E, int n_E)
{
	const double INF_DIS	= n_V*n_E;
	const double INF_THRE	= INF_DIS-2;
	const double PI	= 3.14159265;
	int		n_E1,s,u,v,i;
	double	dx,dy,w,ang;
	bool	bstop;
    
	int		*Ep1 = new int[n_E];
	int		*Ep2 = new int[n_E];
	double	*Ew	 = new double[n_E];
	
	// initialize dis_mat and ang_mat
	double	*pD,*pA;
	pD	= dis_mat;
	pA	= ang_mat;
	for(u=0;u<n_V*n_V;u++) {
		*(pD++)	= inff;
		*(pA++)	= -10;
	}
    
    for(i=0;i<n;i++)
    	e[i].clear();
	// set viewable values
	double *pu	= E;
	double *pv	= E+n_E;
	double *pw	= pv+n_E;
	for(i=0;i<n_E;i++)
	{
		u		= (int)pu[i]-1;
		v		= (int)pv[i]-1;
		w		= pw[i];
	    node s1={v,w};
        node s2={u,w};
        e[u].push_back(s1);
        e[v].push_back(s2);
		
		// set dis_mat
		MAT_SET(dis_mat,u,v,w,n_V);
		MAT_SET(dis_mat,v,u,w,n_V);

		// set ang_mat
		dx	= X[v]-X[u];
		dy	= Y[v]-Y[u];
		ang	= atan2(dy,dx);
		MAT_SET(ang_mat,u,v,ang,n_V);
		MAT_SET(ang_mat,v,u,(ang>0)?(ang-PI):(ang+PI),n_V);
	}


	// shortest pathes from every start point s
	// for each start point run the spfa algorithm
	for(s=0;s<n_V;s++)
	{
		pD		= dis_mat+s*n_V;
		pA		= ang_mat+s*n_V;
		pD[s]	= 0;
		//pA[s]	= -100;

		
		n_E1	= n_E;
		n_E1	= 0;
	
		
        for(i=0;i<n_V;i++){
           dis2[i]=pD[i];
           angle[i]=pA[i];
        }
	    spfa(s);
	    for(i=0;i<n_V;i++){
	        pD[i]=dis[i];
	        pA[i]=angle[i];
	    }
	    
	}//of start point s

	
	delete	[]Ep1;
	delete	[]Ep2;
	delete	[]Ew;

}
