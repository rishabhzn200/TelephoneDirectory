/*This program makes use of Binary Search Trees to simulate Telephone Directory.
*It keeps track of all the names and number stored in it.
*It allows you to Add a contact , Delete a contact and Display all the contacts in alphabetical order.
*It takes input from file called as direct.cpp.
*/



#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct node
{
 char name[40];
 char ph_no[12];
 struct node *left,*right;
};


void built_tree(struct node **);
void Search(struct node *,int);
void find_more(struct node *,char []);
void Insert(struct node **);
void Insert_node(struct node ***,char *,char *);
void Display(struct node *);
struct node * Delete(struct node *);
void fileUpdate(char *,char *);
void makeNewFile(struct node *);
 int i=0;
 struct node *p[10];            //array of pointers to keep track track of name if it occurs more than once

void main()
{
 clrscr();
 int choice;
 FILE *fp;
 struct node *root=NULL;
 built_tree(&root);  //inserts data from file into tree and returns starting address of tree to root by reference

//menu

 for(;;)
  {
   printf("\n1. Search the list for specified name\n");
   printf("2. Insert a new name\n");
   printf("3. Delete an existing name\n");
   printf("4. Print the entire phone list\n");
   printf("5. Exit\n");
   scanf("%d",&choice);
   switch(choice)
    {
     case 1:Search(root,0);                //no need to pass address of root
    break;
     case 2:Insert(&root);           //might require root to be updated
    break;
     case 3:root=Delete(root);
    break;
     case 4:printf("The Names in the list are\n\n");
    printf("\tNAME\t\tPHONE NUMBER\n");
    Display(root);               //no need to pass address of root
    break;
     case 5:
    fclose(fp);
    exit(0);
     default:printf("Wrong choice entered\n");
    }
  }

}



void built_tree(struct node **rt)
{
 char name1[30],phn[30];
 FILE *fp=fopen("names.txt","r");
 while(fscanf(fp,"%s%s",name1,phn)!=EOF)
  {
    printf("\n%s%s",name1,phn);  //name will get name as well as no. from file
    Insert_node(&rt,name1,phn);
  }
 fclose(fp);
}


void Insert(struct node **rt)   //rt is pointer to pointer to tree
{
 char name1[30],phn[12];
 printf("Enter the name and Phone number\n");
 printf("NAME:-");
 scanf("%s",name1);
 printf("PH_NO.:-");
 scanf("%s",phn);
 Insert_node(&rt,name1,phn);
 fileUpdate(name1,phn);
}



void Insert_node(struct node ***r,char *name1,char *phn)
{
 struct node *n=(struct node *)malloc(sizeof(struct node));
 if(n==NULL)
   {
    printf("Out of Memory\n");
    exit(0);
   }
 //char *strcpy(char *dest, const char *src);
 strcpy(n->name,name1);
 strcpy(n->ph_no,phn);
 n->left=n->right=NULL;

    if(**r==NULL)     //*rt is double pointer
     {
      **r=n;          //tree has one node and links are null
     }
    else
     {
      struct node *t=**r;   //t is single temporary pointer pointing to tree
      struct node *p=**r;   //p holds previous value of t
      int lR=0;
      while(t!=NULL)
       {
 p=t;               //p holds previous value of tree
 if(strcmp(n->name,t->name)<0)
    {t=t->left;  lR=0;}
 else if(strcmp(n->name,t->name)>0)
    {t=t->right;   lR=1;}
 else if(strcmp(n->name,t->name)==0)
   {
    if(strcmp(n->ph_no,t->ph_no)<0)
       {t=t->left;  lR=0;}
    else
       {t=t->right;  lR=1;}
   }
 else;
       }                          //after while loop we get p as leaf node
      if(lR==0)                   //based on value of lR=0/1 we set n as either left or right child of p
 p->left=n;
      else
 p->right=n;

  }
}

void fileUpdate(char *name,char *phn)
{FILE *fp=fopen("names.txt","a"); //point to last

 fprintf(fp,"%s\t\t%s\n",name,phn);
 fclose(fp);
}

void Search(struct node *t,int s_d)
{
 char nm[30];
 if(t==NULL)
  {
   printf("Tree is Empty\n");
   return;
  }
 if(!s_d)    //if s_d==0
   printf("Enter the name to be seached\n");
 else        //if s_d==1, delete function has called search fn
   printf("Enter the number to be deleted\n");
 scanf("%s",nm);


//declare all pointers to be null
 for(i=0;i<10;i++)
   p[i]=NULL;
 i=0;
 int flag=0;

//finds more name with same name



 while(t!=NULL)
  {
   if(strcmp(nm,t->name)<0)
      t=t->left;                         //move t to left subtree
   else if(strcmp(nm,t->name)>0)
      t=t->right;                        //move t to right subtree
   else if(  strcmp(nm,t->name) == 0 )
    {flag=1;
     find_more(t,nm);    //make t as root and traverse inorder
     break;
    }
  }
 if(!s_d)
 {
  i=0;
  if(!flag)
    printf("\nName not found in the tree List\n");
  else
    {
     printf("\n\n\tName\tPhone No.\n");
     while((p)[i]!=NULL)
      {
       printf("\t%s\t%s\n",((p)[i])->name,((p)[i])->ph_no);
       i++;
      }
    }
  }
}

void find_more(struct node *temp,char nm[])
  {
   if(temp!=NULL)
    {
     find_more(temp->left,nm);
     if(strcmp(temp->name,nm)==0)
      {
       p[i++]=temp;             //store pointer in pointer array and increment i
      }
     find_more(temp->right,nm);
    }
  }



void Display(struct node *t)
{
 if(t!=NULL)
  {
   Display(t->left);
   printf("\t%s\t\t%s\t\t%p\n",t->name,t->ph_no,t);
   Display(t->right);
  }
}

struct node * getParent(struct node *rt,struct node *t)
{
 struct node *par=rt;
 while(rt!=NULL)
  {
   int cmp_nm=strcmp(t->name,rt->name);
   if(cmp_nm==0)
    {
     int cmp_ph=strcmp(t->ph_no,rt->ph_no);
     if(cmp_ph==0)
      break;
     else if(cmp_ph<0)
      {par=rt; rt=rt->left;}     //left
     else
      {par=rt; rt=rt->right;}      //right
    }
   else if(cmp_nm<0)
    {par=rt;rt=rt->left;}
   else
    {par=rt;rt=rt->right;}
  }
 printf("\n\nparent=%s\n\n",par->name);
 return par;
}

struct node * Delete(struct node *rt)
{int j=0;
 char phn[12];
 struct node *t=NULL;
 Search(rt,1);
 /*if one name is found delete it otherwise ask for no to be deleted*/
 if(p[0]==NULL)       //no occurance of name found
  {
   printf("\nName not Found in the list\n");
   return rt;
  }
 else if(p[0]!=NULL&&p[1]==NULL)  //one occurance of name found
  t=p[0];
 else        //more than one occurance of name is found
  {
   printf("Enter the phone no. corresponding to the name to be deleted\n");
   printf("\n\n\tName\tPhone No.\n");
   while((p)[j]!=NULL)
    {
     printf("\t%s\t%s\n",((p)[j])->name,((p)[j])->ph_no);
     j++;
    }
   scanf("%s",phn);
   j=0;
   while((p)[j]!=NULL)
    {
     if(strcmp(p[j]->ph_no,phn)==0)
      {
       t=p[j];
      }
     j++;
    }
  }

 if(t==NULL)     //phone number not found
  {
   printf("Phone Number is Invalid\n");
   return rt;
  }
 //struct node *parent=getParent(rt,t);
 //now t points to the node to be deleted
 //perform delete operation
 /*3 cases:-
  1.node has 2 children
  2.node has 1 child
  3.node has no child*/

 makeNewFile(t);


  int flag=0;
  struct node *prev=t,*cur=t,*parent=NULL;
  if((t->left!=NULL&&t->right!=NULL)||t==rt||t==NULL)
   {if(cur->right!=NULL)
     {
      cur=cur->right;          //root is processed go to right sub tree
      while(cur!=NULL)            //find its inorder successor in left subtree
       {
 prev=cur;
 cur=cur->left;
       }
     }
    else if(cur->left!=NULL)
     {
      cur=cur->left;
      while(cur!=NULL)
       {
 prev=cur;
 cur=cur->right;
       }
     }
    else
     {
      free(t);   //only single node is left
      return NULL;
     }
      printf("prev=%s\tcur=%s",prev->name,cur->name);
      flag=1;    //after end of while prev=inorder successor
      parent=getParent(rt,prev);        //get parent of previous
      printf("PARENT=%s",parent->name);
      strcpy(t->name,prev->name);
      strcpy(t->ph_no,prev->ph_no);
    t=prev;  //t is the node to be deleted. it has 0 or 1 child.
   }
   if(!flag)
    parent=getParent(rt,t);

  if(t->left==NULL&&t->right!=NULL)
   {
    if(parent->left==t)
       parent->left=t->right;
    else
       parent->right=t->right;
    free(t);
   }

 else if(t->left!=NULL&&t->right==NULL)
   {
    if(parent->left==t)
       parent->left=t->left;
    else
       parent->right=t->left;
    free(t);
   }

 else if(t->left==NULL&&t->right==NULL)
   {
    if(parent->left==t)
       parent->left=NULL;
    else
       parent->right=NULL;
    free(t);
   }
 else;
 return rt;
}

void makeNewFile(struct node *t)
{
 FILE *old_fp,*new_fp;
 char name[30],phn[12];
 old_fp=fopen("names.txt","r");
 new_fp=fopen("newNames.txt","w");
 while(fscanf(old_fp,"%s%s",name,phn)!=EOF)
  {
   if(strcmp(name,t->name)==0&&strcmp(phn,t->ph_no)==0);
   else
     {fprintf(new_fp,"%s\t\t%s\n",name,phn);
      printf("name=%s\tphn=%s",name,phn);
     }
  }
 getch();
 //If your file is open, be sure to close it before removing it.
 fclose(old_fp);
 remove("names.txt");
 //rename(oldname, newname);
 rename("newNames.txt","names.txt");
}
