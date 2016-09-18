#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
};

void insert(struct node**,int,int);
void create(struct node** head){
	int n;
	printf("Enter number of elements: ");
	scanf("%d",&n);
	if(n>0){
		int key;
		printf("Enter the elements:\n");
		for(int i=1;i<=n;i++){
			scanf("%d",&key);
			insert(head,i,key);
		}
		printf("List created successfully!!\n");
	}
}

void insert(struct node **head,int pos,int key){
	if(pos<=0){
		printf("Invalid postion\n");
		return;
	}
	if(!(*head)&&pos==1){
		printf("Head is NULL. Inserting 1st element\n");
		struct node *newnode=malloc(sizeof(struct node));
		newnode->data=key;
		newnode->next=NULL;
		*head = newnode;
		return;
	}
	if(*head){
		struct node *newnode=malloc(sizeof(struct node));
		newnode->data=key;
		if(pos==1){
			newnode->next=*head;
			*head=newnode;
		}
		else{
			int count=1;
			struct node* temp=*head;
			while(temp && ++count<pos-1) temp=temp->next;
			if(!temp){
				printf("Invalid position!\n");
				return;
			}
			else{
				newnode->next=temp->next;
				temp->next=newnode;
			}
		}
	}	
}

void print_nth_beg(struct node *head,int pos){
	int c=1;
	if(!head) return;
	while(++c<pos) head=head->next;
	printf("%d",head->data);
}

void print_nth_end(struct node *head,int pos){
	struct node *mainp=malloc(sizeof(struct node));
	struct node *refp=malloc(sizeof(struct node));
	mainp=head;
	refp=head;
	int count=1;
	while(count++<=pos){
		if(!refp){
			printf("Invalid position!\n");
			return;
		}
		refp=refp->next;
	}
	while(refp){
		mainp=mainp->next;
		refp=refp->next;
	}
	printf("%d",mainp->data);
}

int count(struct node* head){
	int count=0;
	while(head){
		count++;
		head=head->next;
	}
	return count;
}

void print_list(struct node *head){
	if(!head){
		printf("Empty list!!\n");
		return;
	}
	printf("The current list is: ");
	while(head){
		printf("%d ",head->data);
		head=head->next;
	}
}

void delete_element(struct node **head,int pos){
	if(!(*head)) return;
	struct node *temp=*head;
	if(pos==1){
		(*head)=(*head)->next;
		free(temp);
	}
	else{
		int count=1;
		while(++count<pos-1) temp=temp->next;
		struct node *t=temp->next;
		temp->next=t->next;
		free(t);
	}
}

void delete_list(struct node** head){
	struct node *temp;
	while(*head){
		temp=*head;
		*head=(*head)->next;
		free(temp);
	}
	(*head)=NULL;
}
	
void reverse(struct node **head){
	struct node* prev=malloc(sizeof(struct node));
	struct node* current=malloc(sizeof(struct node));
	struct node* next=malloc(sizeof(struct node));
	prev=NULL;
	current=*head;
	while(current){
		next=current->next;
		current->next=prev;
		prev=current;
		current=next;
	}
	*head=prev;
}
	
int main(){
	int n,choice,cont=1,key,pos;
	struct node *head = NULL;
	while(cont){
		printf("1. CREATE LIST\n2. PRINT LIST\n3. PRINT THE nTH ELEMENT FROM BEGINING\n4. PRINT THE nTH ELEMENT FROM END\n5. INSERT AN ELEMENT\n6. DELETE AN ELEMENT\n7. COUNT NUMBER OF ELEMENTS\n8. REVERSE LIST\n9. DELETE LIST\n\nEnter your choice\n");
		scanf("%d",&choice);
		switch(choice){		
			case 1:
				create(&head); break;
			case 2:
				print_list(head); break;
			case 3:
				printf("Enter n: ");
				scanf("%d",&pos);
				print_nth_beg(head,pos);
				break; 
			case 4:
				printf("Enter n: ");
				scanf("%d",&pos);
				print_nth_end(head,pos);
				break; 
			case 5:
				printf("Enter position and data\n");
				scanf("%d %d",&pos,&key);
				insert(&head,pos,key);
				break;
			case 6:
				printf("Enter position\n");
				scanf("%d",&pos);
				delete_element(&head,pos);
				break;
			case 7:
				printf("Number of elements in current list is: %d",count(head));
				break;
			case 8:
				reverse(&head);
				break;
			case 9:
				delete_list(&head);
				break;
			default:
				printf("Wrong choice\n");
		}
		printf("\nEnter 1 to continue, 0 to exit: ");
		scanf("%d",&cont);
	}
	return 0;
}
