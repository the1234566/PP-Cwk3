
/* This is a template with the functions you must implement for this assignment. 
 * 
 * Note that you are free to implement any additional function you consider appropriate.
 * 
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
struct astack 
{
	char *array;
	int top;
	int capability;
}stack;

int flag;

void Init_stack()
{
	stack.capability = 1;//初始容量 
	stack.top = -1;//数组指针置空 
	stack.array = (char*)malloc(sizeof(char) * stack.capability);//分配内存 
}

// push a character into the stack

void stack_push(char c) 
{ 
	int i;
	if (stack.capability == 0) Init_stack();
	while(stack.top >= stack.capability - 1)
	{ 
		stack.capability = stack.top + 4;//容量扩为当前top+4 
		char *new_array = malloc(sizeof(char) * stack.capability);//新建数组分配内存 
		for(i=0; i <= stack.top; i++)//复制原数组数据 
		{
			new_array[i] = stack.array[i];
		}
		free(stack.array);
		stack.array = new_array;//替换原数组 
	}
	stack.array[++stack.top] = c; 
} 

/* Overwrites the character pointed by c with the character currently on
 * top of the stack.
 * 
 * The function returns 0 if the operation can be carried out successfully,
 * and any non-zero number if the operation could not be performed (for instance
 * because the stack is empty).
 */

int stack_top(char *c)
{  
	if (stack.capability == 0) Init_stack();
	if(stack.top == -1)
	{
		return -1;
	}
	*c = stack.array[stack.top];
	return 0; 
}


/* Overwrites the character pointed by c with the character currently on
 * top of the stack, and removes the character from the top of the stack.
 * 
 * The function returns 0 if the operation can be carried out successfully,
 * and any non-zero number if the operation could not be performed (for instance
 * because the stack is empty).
 */
 
int stack_pop(char *c)
{ 	
	if (stack.capability == 0) Init_stack();
	if(stack.top == -1)
	{
		/*if(flag == 0)
		{
		free(stack.array);
		}*/
		return 1;
	}
	*c = stack.array[stack.top--];
	return 0;
}

/* Returns a dynamically allocated string (in the heap) 
 * containing the characters in the string pointed by source,
 * excluding any one-line comment. 
 */
char *remove_single_line_comment(const char *source)
{	
	int i = 0;
	int j = 0;
	int length = strlen(source);
	char *read = (char*)malloc(sizeof(char) * (length+1));
	for(i=0; i<length; i++)
	{
		if( source[i] == '/' && source[i+1] == '/')
		{
			while(source[i+1] != '\n') i++;
			continue;
		}
		read[j] = source[i];
		j++;
	}
	read[j] = '\0'; 
	return read;
}

/* Returns a dynamically allocated string (in the heap) 
 * containing the characters in the string pointed by source,
 * excluding any multi-line comment.
 */
char *remove_multi_line_comment(const char *source)
{
	int i = 0;
	int j = 0;
	int length = strlen(source);
	char *read = (char*)malloc(sizeof(char) * (length+1));
	for(i=0; i<length; i++)
	{
		if(source[i] == '/' && source[i+1] == '*')
		{	
			i += 2; 
			while(source[i] != '*' || source[i+1] != '/') i++;
			i += 1;
			continue;
		}
		read[j] = source[i];
		j++;
	}	
	read[j] = '\0';
	return read;
}

char match(char element)
{
	if (element = ']') return '[';
	if (element = '}') return '{';
	if (element = ')') return '(';
}

char *readfile(char *afile)
{
	int i;
	char *text = malloc (sizeof(char) * 1000000);
	FILE *fp = fopen(afile, "r");
	char ch;
	for (i=0;(ch = fgetc(fp)) != EOF ;i++ ) text[i] = ch;
	text[i] = '\0';
	return text;	
}

/* The main function of your program. Rename into mymain
 * for testing.
 */
int mymain(int argc, char **argv) 
{
	int line = 1;
	int i;
	flag = 1;
	char idk;
	char *letter = &idk;
	char *content = readfile("writeTree.c");
	content = remove_single_line_comment(content);
	content = remove_multi_line_comment(content);
	for (i=0; content[i] != '\0'; i++)
	{
		*letter = content[i];
		if (content[i] == '\n') line++;
		if (content[i] == '[' || content[i] == '{' || content[i] == '(') stack_push(*letter);
		if (content[i] == ']' || content[i] == '{' || content[i] == ')')
		{
			
			if (stack_pop(letter)) printf("Type 1 error in line %i\n", line);
			if (*letter != match(content[i])) printf("Type 2 error in line %i\n", line);
		}
	}
	
	//if (stack.top != -1) printf("Type 3 error in line %i\n", line);	
	printf("%s\n", content);
	return 0;
}

