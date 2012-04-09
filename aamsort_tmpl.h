  /* 
In-place Merge Sort implementation. (c)2012, Andrey Astrelin, astrelin@tochka.ru 
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef SORT_NAME
#error "Must declare SORT_NAME"
#endif

#ifndef SORT_TYPE
#error "Must declare SORT_TYPE"
#endif

#ifndef SORT_CMP
#define SORT_CMP(x, y)  ((x) < (y) ? -1 : ((x) == (y) ? 0 : 1))
#endif

#define SORT_SWAP(x,y) ({SORT_TYPE __SORT_SWAP_t = (x); (x) = (y); (y) = __SORT_SWAP_t;})

#define SORT_CONCAT(x, y) x ## _ ## y
#define SORT_MAKE_STR1(x, y) SORT_CONCAT(x,y)
#define SORT_MAKE_STR(x) SORT_MAKE_STR1(SORT_NAME,x)


#define AAMSORT           SORT_MAKE_STR(aamsort)


void AAMSORT (SORT_TYPE *array, const size_t size);

#if 0
static
int NumCmp(SORT_TYPE x,SORT_TYPE y){
	return x<y ? -1 : x==y ? 0 : 1;
}
static
int (*msort_cmp)(SORT_TYPE x,SORT_TYPE y)=NumCmp;

//#if 0
//bool myfunction (TYP i,TYP j) { return strcmp(i,j)<0; }
bool myfunction (SORT_TYPE i,SORT_TYPE j) { return i<j; }


extern "C" int icmp(const void *a,const void *b){
	int A=*(const int *)a;
	int B=*(const int *)b;
	return A<B ? -1 : A>B ? 1 : 0;
}
#endif

/***** In-place Merge Sort implementation. (c)2012, Andrey Astrelin, astrelin@tochka.ru  *****/ 
static
inline void iswap(SORT_TYPE *a,SORT_TYPE *b){
	SORT_TYPE u=*a; *a=*b; *b=u;
}
static
inline void aswap(SORT_TYPE *arr1,SORT_TYPE *arr2,int len){
	do iswap(arr1++,arr2++);
	while(--len);
}	

static
void isort(SORT_TYPE *a,int b){
	int i,k;
	while(--b){
		k=0;
		for(i=1;i<=b;i++) if(SORT_CMP(a[i],a[k])<0) k=i;
		iswap(a,a+k);
		a++;
	}
}

// arr1(-l1..0] :merge: arr2(-l2..0] -> arr2(-l2..l1]
static
inline int backmerge(SORT_TYPE *arr1,int l1,SORT_TYPE *arr2,int l2){
	int res;
	SORT_TYPE *arr0=arr2+l1;
	if(SORT_CMP(arr1[1-l1],arr2[0])>=0){
		aswap(arr1-l1+1,arr0-l1+1,l1); return l1;
	}
	do{
		while(SORT_CMP(*arr2,*arr1)<0){ 
			iswap(arr1--,arr0--); 
			if(--l1==0) return 0;
		} 
		iswap(arr2--,arr0--); 
	}while(--l2);
	res=l1; 
	do iswap(arr1--,arr0--); while(--l1);
	return res;
}
// arr1[0..l1) :merge: arr2[0..l2) -> arr2[-l1..l2)
static
inline void frontmerge(SORT_TYPE *arr1,int l1,SORT_TYPE *arr2,int l2){
	int res;
	SORT_TYPE *arr0=arr2-l1;
	if(SORT_CMP(arr1[l1-1],arr2[0])<=0){
		aswap(arr1,arr0,l1); return;
	}
	do{
		while(SORT_CMP(*arr2,*arr1)>0){ 
			iswap(arr1++,arr0++); 
			if(--l1==0) return;
		} 
		iswap(arr2++,arr0++); 
	}while(--l2);
	do iswap(arr1++,arr0++); while(--l1);
}
// merge arr[p0..p1) by buffer arr[p1..p1+r)
static
inline void rmerge(SORT_TYPE *arr,int l,int lp,int r){
	if(SORT_CMP(arr[lp],arr[lp-1])>=0) return;
	int q,cv,lq, i,j;
	lq=lp;
	for(i=0;i<l;i+=r){
		// select smallest arr[p0+n*r]
		q=i;
		for(j=lp;j<=lq;j+=r){
			cv=SORT_CMP(arr[j],arr[q]);
			if(cv==0) cv=SORT_CMP(arr[j+r-1],arr[q+r-1]);
			if(cv<0) q=j;
		}		
		if(q!=i){
			aswap(arr+i,arr+q,r); // swap it with current position
			if(q==lq && q<l-r) lq+=r;
		}
		if(i!=0 && SORT_CMP(arr[i],arr[i-1])<0){
			aswap(arr+l,arr+i,r);  // swap current position with buffer
			backmerge(arr+(l+r-1),r,arr+(i-1),r); // buffer :merge: arr[i-r..i) -> arr[i-r..i+r)
		}
		if(lp==i) lp+=r;
	}
}
static
int rbnd(int len){
	int i,k=0;
	len=len/2;
	for(i=1;i<len;i*=2) k++;
	len/=k;
	for(k=1;k<=len;k*=2) ;
	return k;
}

//void msort(SORT_TYPE *arr,int len){
static void msort(SORT_TYPE *arr,int len){
	int r,lr,p,m,q,q1,p0;
	SORT_TYPE *arr1=arr-1;
	if(len<12){ isort(arr,len); return; }
	r=rbnd(len);
	lr=(len/r-1)*r;
	for(p=2;p<=lr;p+=2){
		arr1+=2;
		if(SORT_CMP(arr1[0],arr1[-1])<0) iswap(arr1,arr1-1);
		if(p&2) continue;
		m=len-p;
		q=2;
		while((p&q)==0){
			if(SORT_CMP(arr1[1-q],arr1[-q])<0) break;
			q*=2;
		}
		if(p&q) continue;
		if(q<m){
			p0=len-q;
			aswap(arr+p-q,arr+p0,q);
			for(;;){
				q1=2*q;
				if(q1>m || (p&q1)) break;
				p0=len-q1;
				frontmerge(arr+(p-q1),q,arr+p0+q,q);
				q=q1;
			}		
			backmerge(arr+(len-1),q,arr1-q,q);
			q*=2;
		}
		q1=q; while(q1>m) q1/=2;
		while((q&p)==0){
			q*=2;
			rmerge(arr+(p-q),q,q/2,q1);
		}
	}
	q1=0;
	for(q=r;q<lr;q*=2) if((lr&q)!=0){
		q1+=q;
		if(q1!=q) rmerge(arr+(lr-q1),q1,q,r);
	}
	m=len-lr;
	msort(arr+lr,m);
	aswap(arr,arr+lr,m);
	m+=backmerge(arr+(m-1),m,arr+(lr-1),lr-m);
	msort(arr,m);
}

/***** end of In-Place Merge Sort implementation *****/ 

void
AAMSORT (SORT_TYPE *a, const size_t size)
{
  msort(a,size);
}
