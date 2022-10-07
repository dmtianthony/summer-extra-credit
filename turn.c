#include <stdio.h>
#include <stdlib.h>

int reobtain(int d[],int dtotal,int p[],int ptotal,int i, int test){

	int j,k,m;

	for(j=i+1;j<ptotal;j++){
		if(p[j]!=0&&j!=test){
			k=0;
			while(d[k]<=abs(p[j]-p[test])&&k<dtotal){
				k++;
			}
			for(m=dtotal;m>k;m--){
				d[m]=d[m-1];
			}
			dtotal++;
			d[k]=abs(p[j]-p[test]);
		}
	}
	return dtotal;
}

int recursion(int d[],int dtotal,int p[], int ptotal, int test,int largeboole){
	
	int boole1=0,boole2=0,i,j,k,m,match,positive=1,large,small;

	if(largeboole==1){
		if(p[test+1]==d[dtotal-1]){
			printf("\nbiggest element in d is in p so break");
			return 0; //duplicates
		}
		p[test]=d[dtotal-1];
		dtotal--;
	}
	if(largeboole==0){
		for(i=1;i<dtotal;i++){
			if(d[i]==p[ptotal-1]-d[dtotal-1]){
				break;
			}
		}
		p[test]=d[i];
		for(j=i;j<dtotal-1;j++){		
			d[j]=d[j+1];
		}
		dtotal--;
	}
	// test for matches in distances
	for(i=ptotal-1;i>0;i--){
		if(p[i]!=0&&i!=test){
			printf("\np[i]=%d p[test]=%d",p[i],p[test]);
			match=0;
			for(j=0;j<dtotal;j++){
				if(abs(p[i]-p[test])==d[j]){
					for(k=j;k<dtotal;k++){		
						d[k]=d[k+1];
					}
					dtotal--;
					match=1;
					break;
				}	
			}
			if(match==0){
				printf("\n[i]=%d p[test]=%d break. itself is zero.",p[i],p[test]);
				dtotal=reobtain(d,dtotal,p,ptotal,i,test);
				j=0;
				while(d[j]<=p[test]&&j<dtotal){
					j++;
				}
				for(k=dtotal;k>j;k--){
					d[k]=d[k-1];
				}
				d[j]=p[test];
				dtotal++;
				p[test]=0;
				return 0;
			}
		}			
		
	}
	//test if solved
	for(i=1;i<ptotal;i++){
		if(p[i]==0){
			positive=0;
			break;
		}
	}
	if(positive==1){
		printf("\nanswer ");
		for(i=0;i<ptotal;i++){
			printf("%d ",p[i]);
		}
		return 1;
	}
	small=i;
	for(i=ptotal-1;i>0;i--){
		if(p[i]==0){
			large=i;
			break;
		}
	}
	if(small==large){

		int matchboole,allmatchboole;

		for(i=dtotal-1;i>=0;i--){
			allmatchboole=1;
			p[large]=d[i];
			for(j=i;j<dtotal-1;j++){
				d[j]=d[j+1];
			}
			dtotal--;
			for(j=ptotal-1;j>0;j--){
				if(p[j]!=0&&j!=large){
					printf("\np[j]=%d p[large]=%d",p[j],p[large]);
					match=0;
					for(k=0;k<dtotal;k++){
						if(abs(p[j]-p[large])==d[k]){
							for(m=k;m<dtotal-1;m++){		
								d[m]=d[m+1];
							}
							dtotal--;
							match=1;
							matchboole=1;
							break;
						}	
					}
					if(match==0){
						dtotal=reobtain(d,dtotal,p,ptotal,j,large);
						k=0;
						while(d[k]<=p[large]&&k<dtotal){
							k++;
						}
						for(m=dtotal;m>k;m--){
							d[m]=d[m-1];
						}
						d[k]=p[large];
						dtotal++;
						p[large]=0;
						matchboole=0;
						allmatchboole=0;
						break;
					}			
				}
				if(matchboole==0)break;
			}
			if(allmatchboole==1){
				printf("\nanswer ");
				for(j=0;j<ptotal;j++){  
					printf("%d ",p[j]);
				}
				printf("\n");
				return 1;
			}
			if(i==0)return 0;
		}
	}
	printf("\nbefore next step p: ");
	for(i=0;i<ptotal;i++){
		printf("%d ",p[i]);
	}
	boole1=recursion(d,dtotal,p,ptotal,large,1);
	if(boole1==0){
		boole2=recursion(d,dtotal,p,ptotal,small,0);
	}
	if(boole1==0&&boole2==0){
		printf("\nboth children 0");
		dtotal=reobtain(d,dtotal,p,ptotal,0,test);
		i=0;
		while(d[i]<=p[test]&&i<dtotal){
			i++;
		}
		for(j=dtotal;j>i;j--){
			d[j]=d[j-1];
		}
		d[i]=p[test];
		dtotal++;
		p[test]=0;
		return 0;
	}
	if(boole1==1||boole2==1)return 1;
	return 0;
}

int main(){

	int i=0,j=0,scan=0,intarray[100000],total,zeros=0;
	FILE *fp;
	int ptotal=0,dtotal=0,p[900],d[100000]; 
	int small,large;

	fp=fopen("turnpike.txt","r");
	while(1){
		scan=fscanf(fp,"%d",&intarray[i]);
		if(scan<0)break;
		if(intarray[i]==0)
			zeros++;
		i++;
	}
	fclose(fp);
	total=i;
	ptotal=zeros;
	dtotal=(total-zeros)/2;
	for(i=total-dtotal;i<total;i++){
		d[j]=intarray[i];
		j++;
	}
	for(i=0;i<ptotal;i++){
		p[i]=0; // first position is zero. set all zero p
	}
	p[ptotal-1]=d[dtotal-1]; //largest
	p[ptotal-2]=d[dtotal-2]; //second largest
	dtotal--; //update d
	dtotal--;
	for(i=0;i<dtotal;i++){
		if(d[i]==p[ptotal-1]-p[ptotal-2]){
			for(j=i;j<dtotal;j++){		
				d[j]=d[j+1];
			}
			dtotal--;
			break;
		}
	}
	large=ptotal-3;
	small=1;
	if(recursion(d,dtotal,p,ptotal,large,1)==0){ //recursive
		printf("\ngets here printf dtotal%d ptotal%d\n",dtotal,ptotal);
		printf("\none d: ");
		for(i=0;i<dtotal;i++){
			printf("%d ",d[i]);
		}
		recursion(d,dtotal,p,ptotal,small,0);
	}
	return 0;
}
