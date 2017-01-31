#include<stdio.h>
#define MAXTOKEN 100
char word[100];
struct node
{
 char token[100];
 int count;
 int height;
 int factor;
 struct node* lchild;
 struct node* rchild;
};
struct node *root = NULL;
int trace_height;
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
     trace_height = -1;
     form_tree(root); // not curr
   }
   //printf("\n%s\n",word);
 }
 printf("\n");
 printf("\n******************* in order traversal *********************\n");
 tree_traverse(root);
// printf("\n******************* pre order traversal *********************\n");
// tree_pretrav(root);
// printf("\n******************* post order traversal *********************\n");
// tree_posttrav(root);
// getch();
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
void form_tree(struct node *curr)
{
  struct node *temp;
  //printf("asas");
  trace_height++;
  if (root == NULL)
  {
   temp = NULL;
   //printf("\nifoaif");
   create_node(&temp);
   //printf("in :: rooty:%u\n",temp);
   //printf("in :: root:%s\n",temp->token);
   temp->count=1;
   temp->height = trace_height;
   root = temp;
   //printf("in :: root:%s\n",root->token);
  }
  else
  {
   //printf("ii before curr: %u \n",curr);
   if(strcmp(word,curr->token)<0)
   {
     if(curr->lchild!=NULL)
     {
      form_tree(curr->lchild);
      
     }
     else
     {
      temp = NULL;
      create_node(&temp);
      temp->count=1;
      temp->height = trace_height+1;
      temp->factor = 0;
      curr->lchild= temp;
     }
   }
   else if(strcmp(word,curr->token)>0)
   {
     //printf("\n oner right\n");
     if (curr->rchild !=NULL)
       form_tree(curr->rchild);
     else
     {
        //printf("before curr: %u \n",curr);
        temp = NULL;
        //printf("before curr: %u \n",curr);
        create_node(&temp);
        //printf("\ntemp %u root: %u curr: %u word: %s\n",temp,root,curr,temp->token);
        temp->count=1;
        temp->height = trace_height+1;
        temp->factor = 0;
        curr->rchild = temp;
     }
   }
   else if(strcmp(word,curr->token)==0)
   {
     curr->count++;
   }
  }
}
/***************** create_node  ************************/
void create_node(struct node** temp)
{
  //printf("\non fsd\n");
  *temp =(struct node*)malloc(sizeof(struct node));
  //printf("\nuhuafy word: %s\n",word);
  strcpy((*temp)->token,word);
  //printf("in :: tempty:%u\n",*temp);
  //printf("\ndfdsdfsdfsdfsdfsfsdf   %s\n",(*temp)->token);
  (*temp)->lchild = NULL;
  (*temp)->rchild = NULL;
  //printf("\nifjisdj\n");
}
/********************* tree traveral  **********************/

void tree_traverse(struct node *root)
{
   //printf("in root: %d\n",root);
   if (root!=NULL)
   {
    tree_traverse(root->lchild);
    printf("word: %10s count: %4d height:%4d factor:%4d\n",root->token,root->count,root->height,root->factor);
    tree_traverse(root->rchild);
   }
}

void tree_pretrav(struct node *root)
{
   //printf("in root: %d\n",root);
   if (root!=NULL)
   {
    printf("word: %10s count: %4d height:%4d factor:%4d\n",root->token,root->count,root->height,root->lchild->     height - root->rchild->height);
    tree_traverse(root->lchild);
    tree_traverse(root->rchild);
   }
}


void tree_posttrav(struct node *root)
{
   //printf("in root: %d\n",root);
   if (root!=NULL)
   {
    tree_traverse(root->lchild);
    tree_traverse(root->rchild);
    printf("word: %10s    count: %4d   height:%4d\n",root->token,root->count,root->height);
   }
}
