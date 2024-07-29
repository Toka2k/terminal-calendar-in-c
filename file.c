#include	<stdio.h>
#include	<stdlib.h>

int _fsize(FILE* fp){
	int size = 0;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	rewind(fp);

	return size;
}

int _flines(FILE* fp){	
	int n = 0;

	rewind(fp);
	
	int ch;
	
	while((ch = fgetc(fp)) != EOF){
		if(ch == '\n'){
			n++;
		}
	}

	rewind(fp);
	
	return n;
}

void _fapp(const char *fileName, const char* text){
	FILE *file = fopen(fileName, "a");

	fputs(text, file);

	fclose(file);
	return;
}

void _fdel(const char *fileName, int line_number) {
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Error: Could not open file.\n");
		return;
	}

	char _tempFileName[25];
	sprintf(_tempFileName, ".%s", fileName);

	FILE *temp_file = fopen(_tempFileName, "w");
	if (temp_file == NULL) {
		printf("Error: Could not create temporary file.\n");
		fclose(file);
		return;
	}

	char buffer[1024];
	int current_line = 0;
	
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		current_line++;
		if (current_line != line_number) {
			fputs(buffer, temp_file);
		}
	}

	fclose(file);
	fclose(temp_file);
 
	remove(fileName);
	rename(_tempFileName, fileName);
}

void _fins(const char *fileName, const char* text, int line){
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Error: Could not open file.\n");
		return;
	}

	char _tempFileName[25];
	sprintf(_tempFileName, ".%s", fileName);

	FILE *temp_file = fopen(_tempFileName, "w");
	if (temp_file == NULL) {
		printf("Error: Could not create temporary file.\n");
		fclose(file);
		return;
	}

	char buffer[1024];
	int current_line = 0;
	
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		if (current_line == line) {
			fputs(text, temp_file);
		}
		fputs(buffer, temp_file);

		current_line++;	
	}

	fclose(file);
	fclose(temp_file);
 
	remove(fileName);
	rename(_tempFileName, fileName);
	
	return;
}
