#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<time.h>
#include<limits.h>


// macros used in the code below
#define forl(i,st,n) for(int i=st;i<n;i++)
#define form(i,end,n) for(int i=end;i<0;i--)
#define scan(c) scanf("%d",&c)
#define print(c) printf("%d",c)
#define scand(c) scanf("%lf",&c)
#define printd(c) printf("%lf",c)
#define newl printf("\n")
#define space printf(" ")
#define bar printf("-")




int max(int a,int b)
{
	if(a>b) return a;
	else return b;
}

int min(int a,int b)
{
	if(a<b) return a;
	else return b;
}

// simply swaps the variables sent to it
void swap(int*a,int*b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}





// struct 'node' is a single node in a linked list
typedef struct A 
{
	int val;
	struct A* next;
} node;

// structure 'list' is the linked list 
// implementation of adjacency list of a graph
typedef struct L
{
	node* st; 
	node* end;
	int sz; 
} list;

// push is used to push nodes in a linked list
// it first checks if the linked list is empty

// if yes it creates a new node and makes start and
// end pointers of struct list point to it

// else it creates a node and makes the next pointer 
// of the current end node point to it
void push(int v,int adj,list* ll)
{
	node* temp=(node*)malloc(sizeof(node));
	temp->val=adj;
	temp->next=NULL;
	if(ll[v].st==NULL)
	{
		ll[v].st=temp;
		ll[v].end=temp;
	}
	else
	{
		(ll[v].end)->next=temp;
		ll[v].end=temp;
	}
	ll[v].sz++;
}





// functions getp : get_parent and unite are functions
// for maintainin disjoint sets 
// getemp works with path compression 
// unite works on the "unite by size" heuristic
int getp(int a,int*par)
{
	int ans;
	if(a == par[a]) ans=a;
	else
	{
		par[a] = getp(par[a],par);
		ans=par[a];
	} 
	return ans;
}


// we do a slight modification in unite function such that 
// after each unite it also maintains the root/source of a 
// compressed component of imdmediate children
int unite(int a, int b,int* par,int* deg,int* src)
{
	a = getp(a,par);
	b = getp(b,par);
	if (a == b) return 1;

	src[b]=src[a];
	if (deg[a] < deg[b])
	{
		swap(&a,&b);
	}
	deg[a] += deg[b];
	par[b] = a;

	return 0;
}




// ts is a subroutine of topsort function
// it uses 0,1,2 coloring of nodes to find cycles in digraphs 
// and finds the reverse topological sort order
void ts(int v,int*same,int *pos,int*used,int* ord,list *ll)
{
	used[v] = 1;
	node* temp=ll[v].st;
	while(temp)
	{
		int ch=temp->val;
		if(used[ch]==0) ts(ch,same,pos,used,ord,ll);
		else if(used[ch]==1) (*same)=1;
		if(*same) return;
		temp=temp->next;
	}
	ord[*pos]=v;
	(*pos)+=1;
	used[v] = 2;
}

// topsort function calls function ts and if there is no cycle, 
// returns true with the topological sort order of the vertices
int topsort(int n,int*search,int*used,int*ord,list *ll)
{
	int pos=0;
 	int same=0;
	forl(j,0,n)
	{
		int i=search[j];
		if(!used[i])
		{
			ts(i,&same,&pos,used,ord,ll);
			if(same) return 0;
		}
	}
	forl(i,0,n/2)
	{
		swap(&ord[n-1-i],&ord[i]);
	}
	return 1;
}




// function dfs checks if the 'final schedule' found from the 
// decompression of topologically sorted compressed graph is valid

// it does so by checking if the position of immediate/non-imdiate
// child in the 'final schedule' is before its parent or not 

// if yes the 'final schedule' is invalid and return false
// else return true
int isvalid(int parent,int * pos,list *ll)
{
	node * temp=ll[parent].st;
	while(temp)
	{
		int child=temp->val;
		if (pos[child] < pos[parent]) return 0;
		if (!isvalid(child,pos,ll)) return 0;
		temp=temp->next;
	}
	return 1;
}



int main()
{
	int n,m,i,j,k,t,a,b,c,d,e;
	int inf=INT_MAX;  // use DBL_MAX for floaticompG point min and max 
	int mod=1e9+7;
	

	printf("Enter number of nodes: ");
	scan(n);
	// newl;
	printf("Enter number of immdediate edges: ");
	scan(m);
	// newl;


	list * orgnG=(list*)malloc((n+5)*sizeof(list));
	// orgnG is the orginal graph (a rooted directed tree)
	list * imdtG=(list*)malloc((n+5)*sizeof(list));
	// imdtG is the graph of immediate children
	list * compG=(list*)malloc((n+5)*sizeof(list));
	// compG is the compressed graph

	
	// Intializing all the graphs with start and 
	// end pointing to NULL and size 0
	forl(i,1,n+1)
	{
		orgnG[i].st=NULL;
		orgnG[i].end=NULL;
		orgnG[i].sz=0;

		imdtG[i].st=NULL;
		imdtG[i].end=NULL;
		imdtG[i].sz=0;

		compG[i].st=NULL;
		compG[i].end=NULL;
		compG[i].sz=0;

	}

	int *search  =(int*)malloc((n+5)*sizeof(int));
	// search will store the nodes to be sent to 
	// topsort functions i.e. for a particular graph 
	// it will have all the nodes present in that graph
	// for example orgnG has n nodes 
	// but imdtG and compG can have less than n nodes
	




	int *ctx  =(int*)malloc((n+5)*sizeof(int));
	// checks if all x'is are pairwise distinct by samegicompG if there are two same
	// x'is in the input for immediate edges

	int *cty  =(int*)malloc((n+5)*sizeof(int));
	// checks if all y'is are pairwise distinct by samegicompG if there are two same
	// y'is in the input for immediate edges






	int *ord  =(int*)malloc((n+5)*sizeof(int));		
	// ord will store the topsort order for each topsort

	int *fin  =(int*)malloc((n+5)*sizeof(int));
	// fin will store the final answer

	int *pos  =(int*)malloc((n+5)*sizeof(int));
	// pos stores the pos of nodes in the topsort ord
	// for example if we find ord to  be 	3 2 5 1 4
	// their corresponding positions are	1 2 3 5 4
	
	// hence, pos will be 4 2 1 5 3, since pos[3]=1,pos[2]=2, pos[5]=3 ....




	int *used =(int*)malloc((n+5)*sizeof(int));
	// used marks nodes which have been visited duricompG the traversal of some other node duricompG topsort




	// Below arrays will all be used for the DSU data structure
	int *par =(int*)malloc((n+5)*sizeof(int));
	// par stores the parent of a disjoint set

	int *deg = (int*)malloc((n+5)*sizeof(int));
	// deg/degree stores the  size of an individual set

	int *src= (int*)malloc((n+5)*sizeof(int));
	// src stores the root node of each compressed component




	int root=0;		
	// root is the root of original graph corresponding to input 0 among the first n input numbers

	


	int cycle=0;
	// 'cycle' is a binary variable and checks for cycles in the immediate graph
	int same=0;
	// 'same' is a binary variable and checks if two x'is or y'is in the immediate graph are same
	int outrng=0;
	// 'outrng' is a binary variable and checks if the input vertices are out of range




	int len=0;		
	// len store the size of search array

	// some more initializations
	forl(i,1,n+1)
	{
		used[i]=0;

		ctx[i]=0;
		cty[i]=0;

		par[i]=i;
		deg[i]=1;
		src[i]=i;
	}





	printf("Enter the parent node of the i'th node: ");
	newl;
	forl(i,1,n+1)
	{
		scan(a);
		
		// Checking if the input vertices are out of range or not
		if(a>n+1 || a<0)
		{
			outrng=1;
			continue;
		}
		if(a)
		{
			push(a,i,orgnG);
  		}
		else root=i;
	}
	// if(root==0)
	// {
	// 	printf("The input graph must be a rooted tree");
	// 	newl;
	// 	// print(0);
	// 	return 0;
	// }






	printf("Enter immediate edges: ");newl;
	forl(i,0,m)
	{
		scan(a);scan(b);
		
		// Checking if the input vertices are 
		// out of range or not
		if(a>n+1 || a<=0 || b>n+1 || b<=0)
		{
			outrng=1;
			continue;
		}

		// Checking if two x'is are not same
		if(ctx[a]) same=1;
		else ctx[a]=1;
		// CheckinG if two y'is are not same
		if(cty[b]) same=1;
		else cty[b]=1;


		// uniting disjoint sets/components 
		if(unite(a,b,par,deg,src)) cycle=1; 
		push(a,b,imdtG);
	}
	if(outrng)
	{
		printf("Out or range nodes detected");
		return 0;
	}
	if(same)
	{
		printf("Xi's and Yi's must be pairwise distinct");
		newl;
		return 0;
	}
	if(cycle)
	{
		printf("Cycle detected in immmediate graph");
		newl;
		// print(0);
		return 0;
	}






	forl(i,1,n+1)
	{
		node* temp=orgnG[i].st;
		if(getp(i,par)==i) 
		{
			search[len++]=i;
		}


		// finding roots/representative elements
		// of each component and adding edges 
		// between them to form compressed graph
		while(temp)
		{
			int v=i,u=temp->val;
			int vroot=getp(v,par);
			int uroot=getp(u,par);
			if(vroot!= uroot)
			{
				push(vroot,uroot,compG);
			}
			temp=temp->next;
		}
	}
	if(!topsort(len,search,used,ord,compG))
	{
		printf("Cycle detected in compressed graph");
		newl;
		// print(0);
		return 0;
	}






	// finding a schedule by decompressing components
	// in the order they are present in the topsort
	// of the compressed graph

	// Such a schedule may be invalid
	// we will check later using isvalid function 
	int curr=0;
	int source;
	forl(i,0,len)
	{
		source=src[getp(ord[i],par)];
		fin[curr++]=source;
		pos[source]=curr;
		node *temp;
		temp=imdtG[source].st;
		while(temp)
		{
			source=temp->val;
			temp=imdtG[source].st;
			
			fin[curr++]=source;
			pos[source]=curr;
		}
	}
	if (!isvalid(root,pos,orgnG))
	{
		printf("No valid order because of cycles");
		// print(0);
		newl;
		return 0;
	}




	// Finally printing the schedule found
	// Note that there can be many schedules and 
	// our algorithm finds one of the possibilites!
	printf("Schedule found :"); newl;
	forl(i,0,n)	print(fin[i]),space;
	newl;

}