/* AVL tree implementation by Omer Asif */
#include<stdio.h>
#define MAXTOKEN 100
char word[100];
struct node
{
 char token[100];
 int count;
 int ldepth;
 int rdepth;
 int factor;
 struct node* lchild;
 struct node* rchild;
};
struct node *root = NULL;
//int trace_height;
struct node* form_tree(struct node*);
void tree_traverse(struct node*,int);
struct node* rotation(struct node*);
struct node* rot_ll(struct node*);
struct node* rot_rr(struct node*);
struct node* rot_rl(struct node*);
struct node* rot_lr(struct node*);
int main()
{
 int c;
 //struct node *curr=root;//*root = NULL;
 clrscr();
 while((c=gettoken())!='.')
 {
   if( c==0)
   {
     //printf("adsasdsd");
     //root = curr;
     //trace_height = -1;
     root = form_tree(root); // not curr
     //printf("%u %s\n",root,root->token);
   }
   //printf("\n%s\n",word);
 }
 printf("\n");
 printf("\n******************* in order traversal *********************\n");
 tree_traverse(root,0);
// printf("\n******************* pre order traversal *********************\n");
// tree_pretrav(root);
 printf("\n******************* after recalculation *********************\n");
 tree_posttrav(root);
 tree_traverse(root,0);
 getch();
}


/***********  get token   *****************/
int gettoken()
{
 int c;
 char *local = word;
 strcpy(word,"");
 while((c=getche())==' '||c=='\t'){}
 if(isalpha(c))
 {
  *local++ = c;
  while(isalpha(c=getche()))
  {
   *local++ = c;
  }
  *local = '\0';
  return 0;
 }
 else if(c=='.')
 {
   return c;
 }
 else
 {
   printf("word starting with\n" );
   return -1;
 }
}
/**********  form_tree *******************/
struct node* form_tree(struct node *curr)
{
  struct node *temp;
  int l,r;
  //trace_height++;
  if (curr == NULL)
  {
   temp = NULL;
   create_node(&temp);
   temp->count=1;
   //temp->height = trace_height;
   temp->ldepth = 0;
   temp->rdepth = 0;
   temp->factor = 0;
   curr = temp;
  }
  else
  {
      //printf("itt : %u\n",curr);
      //   getch();
      //printf("%s %s \n",word,curr->token);
   if(strcmp(word,curr->token)<0)
   {
       curr->lchild = form_tree(curr->lchild);
       l = curr ->lchild -> ldepth;
       r = curr ->lchild -> rdepth;
       curr->ldepth = ((l>r)?l:r) + 1;
   }
   else if(strcmp(word,curr->token)>0)
   {
       curr->rchild = form_tree(curr->rchild);
       l = curr ->rchild -> ldepth;
       r = curr ->rchild -> rdepth;
       curr->rdepth = ((l>r)?l:r) + 1;
   }
   else if(strcmp(word,curr->token)==0)
   {
       curr->count++;
   }
   curr->factor = (curr->ldepth) - (curr->rdepth);
   if (curr->factor<-1 || curr->factor>1)
   {
        printf("%s \n",curr->token);
        curr =  rotation(curr);
        printf("%s \n",curr->token);
   }
  }
  return curr;

}
/***************** create_node  ************************/
void create_node(struct node** temp)
{
  *temp =(struct node*)malloc(sizeof(struct node));
  strcpy((*temp)->token,word);
  (*temp)->lchild = NULL;
  (*temp)->rchild = NULL;
}
/********************* tree traveral  **********************/

void tree_traverse(struct node *root,int flag)
{
   if (root!=NULL)
   {
    tree_traverse(root->lchild,1);
    printf("word: %10s count: %4d ldepth:%4d rdepth:%4d balance:%4d %5s\n",root->token,root->count,root->ldepth,root->rdepth,root->ldepth-root->rdepth,(flag!=0)?(flag==1?"left":"right"):"root");
    tree_traverse(root->rchild,2);
   }
}
/***************************          ****************************************/

/*void tree_pretrav(struct node *root,int flag)
{
   //printf("in root: %d\n",root);
   if (root!=NULL)
   {
    printf("word: %10s count: %4d height:%4d %5s\n",root->token,root->count,root->height,(flag != 0)?(flag==1?"left":"right"):"root");
    tree_traverse(root->lchild,1);
    tree_traverse(root->rchild,2);
   }
}
    */

void tree_posttrav(struct node *root)
{
   //printf("in root: %d\n",root);
   int l,r;
   if (root!=NULL)
   {

    tree_posttrav(root->lchild);
    if (root->lchild == NULL)
    {
      root->ldepth = 0;
    }
    else
    {
      l = root ->lchild -> ldepth;
      r = root ->lchild -> rdepth;
      root->ldepth = ((l>r)?l:r) + 1;
    }
    tree_posttrav(root->rchild);
    if (root->rchild == NULL)
    {
      root->rdepth = 0;
    }
    else
    {
      l = root ->rchild -> ldepth;
      r = root ->rchild -> rdepth;
      root->rdepth = ((l>r)?l:r) + 1;
    }
    //printf("word: %10s    count: %4d   height:%4d\n",root->token,root->count,root->height);
   }
}
/* if it is LL rotation only left should have more depth and vice versa */
struct node* rotation(struct node* curr)
{
 // return (curr = rot_ll(curr));
   if (curr->factor > 1)
   {
     if(curr->lchild->ldepth > curr->lchild->rdepth)
     {
      curr = rot_ll(curr);
     }
     else
     {
      curr = rot_rl(curr);
     }
   }
   else
   {
     if(curr->rchild->rdepth > curr->rchild->ldepth)
     {
      curr = rot_rr(curr);
     }
     else
     {
      curr = rot_lr(curr);
     }
   }

}

struct node* rot_ll(struct node * curr)
{
  struct node *temp = curr->lchild;
  curr -> lchild = curr->lchild->rchild;
  temp -> rchild = curr;
  return temp;
}

struct node* rot_rl(struct node* curr)
{
 curr->lchild=rot_rr(curr->lchild);
 curr = rot_ll(curr);
 return curr;
}
struct node* rot_rr(struct node* curr)
{
  struct node *temp = curr->rchild;
  curr ->  rchild = curr -> rchild -> lchild;
  temp -> lchild = curr;
  return temp;
}
struct node* rot_lr(struct node* curr)
{
 curr->rchild=rot_ll(curr->rchild);
 curr = rot_rr(curr);
 return curr;
}

