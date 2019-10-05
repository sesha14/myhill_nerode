#include<stdio.h>
main()
{
	FILE *fp;
	FILE *fp1;
	int i,j,k,n1,n,z,m=0,s;
	char ch,ch1;
	printf("enter no.of states:\n");
	scanf("%d",&n);
	n1=n-1;
	char a[n],b[n],c[n];//to store states
	char col[n-1][n-1];
	int zero[n],one[n],zero1[n],one1[n],zero2[n],one2[n];//to store indices of characters of one,zero transition
	for(i=0;i<n;i++)
	{
		a[i]='\0';
		b[i]='\0';
		c[i]='\0';
	}
	for(i=0;i<n1;i++)//initialize with '\0'
	{
		for(j=0;j<n1;j++)
		{
			col[i][j]='\0';
		}
	}
	for(i=0;i<n1;i++)//creating jagged array shape
	{
		for(j=0;j<=i;j++)
		{
			col[i][j]='0';
		}
	}
	for(j=0;j<n1;j++)//mark last row as '1'
	{
		col[n1-1][j]='1';
	}
	/*for(i=0;i<n1;i++)//print jagged array
	{
		for(j=0;j<n1;j++)
		{
			printf("%c",col[i][j]);
		}
		printf("\n");
	}*/
	printf("enter the states from initial to final state:\n");
	for(i=0;i<n;i++)//store states
	{
		scanf(" %c",&a[i]);
	}
	printf("enter transitions on zero:\n");//store indices of zero transition
	for(i=0;i<n;i++)
	{
		scanf(" %c",&ch);
		for(j=0;j<n;j++)
		{
			if(ch==a[j])
			zero[i]=j;
		}
	}
	printf("enter transitions on one:\n");//store indices of one transition
	for(i=0;i<n;i++)
	{
		scanf(" %c",&ch);
		for(j=0;j<n;j++)
		{
			if(ch==a[j])
			one[i]=j;
		}
	}
	/*for(i=0;i<n;i++)//print state,index of zero,one transition
	{
		printf("%c %d %d\n",a[i],zero[i],one[i]);
	}*/
	z=0;//compute jagged array values
	while(z<2)
	{
	 for(i=n1-1;i>=0;i--)
	 {
		 for(j=0;j<n1-1;j++)
		 {
		 	//printf("%c\n",col[one[one[i+1]]-1][one[one[j]]]);
			 if(col[one[i+1]-1][one[j]]=='1'||col[zero[i+1]-1][zero[j]]=='1')
			 {
			 	//printf("%c %c\n",col[zero[zero[i+1]]][zero[zero[j]]],col[one[one[i+1]]][one[one[j]]]);
			 	if(col[i][j]!='\0')
				col[i][j]='1';
			 }
		 }
	 }
	 z++;
    }
    for(i=0;i<n1;i++)//print jagged array
	{
		for(j=0;j<n1;j++)
		{
			printf("%c",col[i][j]);
		}
		printf("\n");
	}
	printf("Input file generation successful\n");
	for(i=0;i<n1;i++)//store indistinguishable states
	{
		for(j=0;j<n1;j++)
		{
			if(col[i][j]=='0')
			{
				s=0;
				for(k=0;k<n;k++)
				{
					if(a[i+1]==b[k])
					{
						s=1;
					}
				}
				if(s!=1)
				{
					b[m]=a[i+1];
					m++;
				}
				s=0;
				for(k=0;k<n;k++)
				{
					if(a[j]==b[k]&&s==0)
					{
						s=1;
					}
				}
				if(s!=1)
				{
					b[m]=a[j];
					m++;
				}
			}
		}
	}
	printf("indistinguishable states are:");
	for(i=0;i<n;i++)//print merged states
	{
		if(b[i]!='\0')
		{
			printf("%c",b[i]);
		}	 	
    }
	m=0;
	for(i=0;i<n;i++)
	{
		s=0;
		for(k=0;k<n;k++)
		{
			if(a[i]==b[k])
			{
				s=1;
			}
		}
		if(s!=1)
		{
			c[m]=a[i];
			m++;
		}
	}
	printf("\n distinguishable states are:");
	for(i=0;i<n;i++)//print unmerged states
	{
		if(c[i]!='\0')
		{
			printf("%c ",c[i]);
		}	 	
	}
	fp=fopen("E:\\file2.txt","w+");//first output file
	fputs("digraph finite_state_machine {rankdir=LR;",fp);
	//fputc(a[--i],fp);
	fputs("node [shape = doublecircle];",fp);
	fputc(a[n-1],fp);
	fputs(";",fp);
	fputs("node [shape = circle];",fp);
	ch='"';
	for(i=0;(i<n&&a[i]!='\0');i++)
	{
		fputc(a[i],fp);
		fputs("->",fp);
		fputc(a[zero[i]],fp);
		fputs(" [ label =",fp);
		fputc(ch,fp);
		fputs("0",fp);
		fputc(ch,fp);
		fputs("];",fp);
	}
	for(i=0;(i<n&&a[i]!='\0');i++)
	{
		fputc(a[i],fp);
		fputs("->",fp);
		fputc(a[one[i]],fp);
		fputs(" [ label =",fp);
		fputc(ch,fp);
		fputs("1",fp);
		fputc(ch,fp);
		fputs("];",fp);
	}
	fputs("}",fp);
	fclose(fp);
	for(i=0;i<n;i++)//store 0 and 1 of merged
	{
		for(j=0;j<n;j++)
		{
			if(b[i]==a[j])
			{
				zero1[i]=zero[j];
				one1[i]=one[j];
			}
		}
	}
	for(i=0;i<n;i++)//store o and 1 of unmerged
	{
		for(j=0;j<n;j++)
		{
			if(c[i]==a[j])
			{
				zero2[i]=zero[j];
				one2[i]=one[j];
			}
		}
	}
	/*for(i=0;i<n&&c[i]!='\0';i++)
	printf("%d %c",i,c[i]);*/
	fp1=fopen("E:\\file3.txt","w+");//second output file
	fputs("digraph finite_state_machine {rankdir=LR;",fp1);
	//fputc(a[--i],fp);
	fputs("node [shape = doublecircle];",fp1);
	fputc(a[n-1],fp1);
	fputs(";",fp1);
	fputs("node [shape = circle];",fp1);
	ch='"';
	for(i=0;(i<n&&b[i]!='\0');i++)
	{
		fputc(b[i],fp1);
	}
	fputs("->",fp1);
	for(i=0;i<n;i++)
	{
		s=0;
		for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[zero1[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[zero1[i]];
		}
    }
    if(s==1)
    {
    	for(i=0;(i<n&&b[i]!='\0');i++)
	    {
		 fputc(b[i],fp1);
	    }
    }
    else
    fputc(ch1,fp1);
	fputs("[label=",fp1); 
	fputc(ch,fp1);
	fputs("0",fp1);
	fputc(ch,fp1);
	fputs("];",fp1); //end of merged 0  	
    for(i=0;(i<n&&c[i]!='\0');i++)
    {
    	s=0;
    	//printf("\n%c",c[i]);
    	fputc(c[i],fp1);
    	fputs("->",fp1);
    	for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[zero2[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[zero2[i]];
		}
		if(s==1)
        {
    	 for(j=0;(j<n&&b[j]!='\0');j++)
	     {
		  fputc(b[j],fp1);
	     }
        }
        else
        fputc(ch1,fp1);
        fputs("[label=",fp1); 
	    fputc(ch,fp1);
	    fputs("0",fp1);
	    fputc(ch,fp1);
	    fputs("];",fp1);
    }//end of unmerged 0
    for(i=0;(i<n&&b[i]!='\0');i++)
	{
		fputc(b[i],fp1);
	}
	fputs("->",fp1);
	for(i=0;i<n;i++)
	{
		s=0;
		for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[one1[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[one1[i]];
		}
    }
    if(s==1)
    {
    	for(i=0;(i<n&&b[i]!='\0');i++)
	    {
		 fputc(b[i],fp1);
	    }
    }
    else
    fputc(ch1,fp1);
	fputs("[label=",fp1); 
	fputc(ch,fp1);
	fputs("1",fp1);
	fputc(ch,fp1);
	fputs("];",fp1); //end of merged 1  	
    for(i=0;(i<n&&c[i]!='\0');i++)
    {
    	s=0;
    	fputc(c[i],fp1);
    	fputs("->",fp1);
    	for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[one2[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[one2[i]];
		}
		if(s==1)
        {
    	 for(j=0;(j<n&&b[j]!='\0');j++)
	     {
		  fputc(b[j],fp1);
	     }
        }
        else
        fputc(ch1,fp1);
        fputs("[label=",fp1); 
	    fputc(ch,fp1);
	    fputs("1",fp1);
	    fputc(ch,fp1);
	    fputs("];",fp1);
    }//end of unmerged 1
    fputs("}",fp1);
    fclose(fp1);
    /*printf("new states\t\t\tONZERO\t\t\tONONE\n");//output print
    for(i=0;i<n&&b[i]!='\0';i++)
    printf("%c",b[i]);
    printf("\t\t\t");
    for(i=0;i<n;i++)
	{
		s=0;
		for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[zero1[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[zero1[i]];
		}
    }
    if(s==1)
    {
    	for(i=0;(i<n&&b[i]!='\0');i++)
	    {
		 printf("%c",b[i]);
	    }
    }
    else
    printf("%c",ch1);
    printf("\t\t\t");
    for(i=0;i<n;i++)
	{
		s=0;
		for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[one1[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[one1[i]];
		}
    }
    if(s==1)
    {
    	for(i=0;(i<n&&b[i]!='\0');i++)
	    {
		 printf("%c",b[i]);
	    }
    }
    else
    printf("%c",ch1);
    //printf("\n");
    for(i=0;(i<n&&c[i]!='\0');i++)
    {
    	s=0;
    	printf("\n%c\t\t\t",c[i]);
    	for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[zero2[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[zero2[i]];
		}
		if(s==1)
        {
    	 for(j=0;(j<n&&b[j]!='\0');j++)
	     {
		  printf("%c",b[i]);
	     }
        }
        else
        printf("%c\t\t\t",ch1);
        s=0;
    	printf("%c\t\t\t",c[i]);
    	for(j=0;(j<n&&b[j]!='\0');j++)
		{
			if(a[one2[i]]==b[j])
			{
				s=1;
			}
			else
			ch1=a[one2[i]];
		}
		if(s==1)
        {
    	 for(j=0;(j<n&&b[j]!='\0');j++)
	     {
		  printf("%c",b[j]);
	     }
        }
        else
        printf("%c",ch1);
    }//end of unmerged 0
    printf("final states:[%d]\n",i+1);
    printf("no.of states reduced:%d\n",(n-(i+1)));
    printf("Output file generation successful");*/
}
