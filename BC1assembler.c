#include <stdio.h>
#include <string.h>

void mov(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 8) fprintf(fo, "0%c0%c ", input[5], input[8]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void add(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 11) fprintf(fo, "1%c%c%c ", input[5], input[8], input[11]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void sub(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 11) fprintf(fo, "2%c%c%c ", input[5], input[8], input[11]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void and(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 11) fprintf(fo, "3%c%c%c ", input[5], input[8], input[11]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void or(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 10) fprintf(fo, "4%c%c%c ", input[4], input[7], input[10]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void xor(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 11) fprintf(fo, "5%c%c%c ", input[5], input[8], input[11]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void not(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 8) fprintf(fo, "60%c%c ", input[5], input[8]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void inc(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 8) fprintf(fo, "7%c0%c ", input[5], input[8]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void tst(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 8) fprintf(fo, "8%c%c0 ", input[5], input[8]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void io(FILE* fo, char input[], int counter)
{
	char temp;
	if(strlen(input) < 11)
	{
		printf("Unable to resolve code written at line %d\n", counter);
		return;
	}
	temp = input[3] - 0x30;
	temp = temp << 2;
	temp = temp | (input[5] - 0x30);
	fprintf(fo, "9%x%c%c ", temp, input[8], input[11]);
	
	return;
}

void save(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 9) fprintf(fo, "a%c%c0 ", input[6], input[9]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void load(FILE* fo, char input[], int counter)
{
	if(strlen(input) > 9) fprintf(fo, "b%c0%c ", input[6], input[9]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void jmp(FILE* fo, char input[], int counter)
{
	int flags;
	switch(input[2])
	{
		case 'p':	flags = 0; break;
		case 'z':	flags = 2; break;
		case 'g':	flags = 6; break; 
		case 'o':	flags = 4; break;
		case 'i':	flags = 14; break;
		case 'a':	flags = 0; break;
		default:	printf("Unable to resolve code written at line %d\n", counter);
					return;
	}
	if(input[5] != ' ' && input[6] != ' ' && input[5] != '\n' && input[6] != '\n')
	{
		flags = flags | 1;
		fprintf(fo, "c%x%c%c ", flags, input[5], input[6]);
	}
	else fprintf(fo, "c%x%c%c ", flags, input[4], input[5]);
	
	return;
}

void ldi(FILE* fo, char input[], int counter)
{
	char number;
	char saveReg;
	if(input[4] == '\'')
	{
		if(input[5] == '\\')
		{
			switch(input[6])
			{
				case '0':	number = 0; break;
				case 'n':	number = '\n'; break;
				case 't':	number = '\t'; break;
				default:	printf("Unable to resolve code written at line %d\n", counter); return;
			}
			saveReg = input[10];
		}
		else
		{
			number = input[5];
			saveReg = input[9];
		}
		fprintf(fo, "d%02x%c ", number, saveReg);
	}
	else
	{
		if(input[8] == '\n' || input[8] == ' ')
		{
			printf("Unable to resolve code written at line %d\n", counter);
			return;
		}
		else fprintf(fo, "d%c%c%c ", input[4], input[5], input[8]);
	}
	
	return;
}

void lsf(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 11) fprintf(fo, "3%c%c%c ", input[5], input[8], input[11]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

void dec(FILE* fo, char input[], int counter)
{
	if(strlen(input) >= 8) fprintf(fo, "f%c0%c ", input[5], input[8]);
	else printf("Unable to resolve code written at line %d\n", counter);
	return;
}

int main()
{
	char input[200];
	int counter = 0;
	int trueCounter = 1;
	FILE* fi = fopen("input.txt", "r");
	FILE* fo = fopen("output.txt", "w");
	if(fi == NULL || fo == NULL) 
	{
		printf("Failed to open one or more files, make sure you have input.txt in the parent folder! Press any key to exit. ");
		scanf("%c", input);
		return 2;
	}
	
	while(fgets(input, 199, fi) != NULL)
	{
		switch(input[0])
		{
			case '/':	--trueCounter;
						break;
			case 'j':	jmp(fo, input, counter);
						break;
			case 'i':	if(input[1] == 'n' && input[2] == 'c') inc(fo, input, counter);
						else if(input[1] == 'o') io(fo, input, counter);
						else goto FAILURE;
						break;
			case 'd':	if(input[1] == 'e' && input[2] == 'c') dec(fo, input, counter);
						else goto FAILURE;
						break;
			case 'a':	if(input[1] == 'd' && input[2] == 'd') add(fo, input, counter);
						else if(input[1] == 'n' && input[2] == 'd') and(fo, input, counter);
						else goto FAILURE;
						break;
			case 's':	if(input[1] == 'u' && input[2] == 'b') sub(fo, input, counter);
						else if(input[1] == 'a' && input[2] == 'v' && input[3] == 'e') save(fo, input, counter);
						else goto FAILURE;
						break;
			case 'x':	if(input[1] == 'o' && input[2] == 'r') xor(fo, input, counter);
						else goto FAILURE;
						break;
			case 'l':	if(input[1] == 'd' && input[2] == 'i') ldi(fo, input, counter);
						else if(input[1] == 's' && input[2] == 'f') lsf(fo, input, counter);
						else if(input[1] == 'o' && input[2] == 'a' && input[3] == 'd') load(fo, input, counter);
						else goto FAILURE;
						break;
			case 'o':	if(input[1] == 'r') or(fo, input, counter);
						else goto FAILURE;
						break;
			case 'm':	if(input[1] == 'o' && input[2] == 'v') mov(fo, input, counter);
						else goto FAILURE;
						break;
			case 'n':	if(input[1] == 'o' && input[2] == 'p') fprintf(fo, "0000 ");
						else if(input[1] == 'o' && input[2] == 't') not(fo, input, counter);
						else goto FAILURE;
						break;
			case 't':	if(input[1] == 's' && input[2] == 't') tst(fo, input, counter);
						else goto FAILURE;
						break;
			default:	FAILURE:	
						printf("Unable to resolve code written at line %d\n", counter);
		}
		if(trueCounter % 8 == 0) fputc('\n', fo);
		++counter;
		++trueCounter;
	}
	
	fclose(fi);
	fclose(fo);
	
	printf("\n\n\nAll Done! Click any key to exit.");
	scanf("%c", input);
	return 0;
}

