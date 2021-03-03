#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	bool flag[10];
	int file_exists = access(argv[1], F_OK);

	if ((argc < 2 || argv[1][0] != '-' || strlen(argv[1]) == 1) && file_exists != 0) {  // If file exists, ignore
		fputs("Usage mv [OPTION]... [SRC]... [DEST]\n", stderr);
		fputs("Try mv --help for more information\n", stderr);

		return 1;
	}

	if (argv[1][0] == '-' && argv[1][1] != '-' && file_exists != 0) {
		for (int i = 1; i < strlen(argv[1]); ++i) {  // Go through each index of string argv[1]
			switch (argv[1][i]) {
				case 'v':  // visual
					flag[1] = true;
					break;
				case 'i':  // force
					flag[2] = true;
					break;
				default:
					flag[0] = true;
			}
		}

	} else if (strcmp("--help", argv[1]) == 0) {
		puts("Usage mv [OPTION]... [SRC]... [DEST]\n");
		puts("Rename SRC to DEST, or move SRC to DEST");
		printf("\n");
		puts("-v\t\t\tGive visual feedback of what has just been renamed/moved");
		puts("-i\t\t\tInteractive mode, confirm wheather or not to do a task");
		return 0;
	}

	if (flag[0] == true) {  // invalid option flag
		fprintf(stderr, "Invalid option: %s\n", argv[1]);
		fputs("Try mv --help for more information\n", stderr);
		return 1;
	}


	char *oldname = argv[argc - 2], *newname = argv[argc - 1];
	char current_dir = '.';
	char *parent_dir = "..";

	char confirm;
	if (flag[2] == true) {  // interactive flag
		if (access(oldname, F_OK) == 0) {
			printf("rename '%s' to '%s'?\n", oldname, newname);
			scanf("%1c", &confirm);
		} else {
			fprintf(stderr, "'%s': No such file or directory\n", oldname);
			return -1;
		}

		if (confirm == 'y') {
			rename(oldname, newname);
		} else {
			fprintf(stderr, "Enter either option y (yes), or n (no)");
			return -1;

		}

		return 0;

	}


	if (flag[1] == true) {
		if (access(oldname, F_OK) == 0) {
			rename(oldname, newname);
			printf("renamed '%s' -> '%s'\n", oldname, newname);
		} else {
			fprintf(stderr, "'%s': No such file or directory\n", oldname);
		}

	} else if (access(argv[1], F_OK) == 0)  {
		rename(oldname, newname);

	} else {
		fprintf(stderr, "'%s': No such file or directory\n", oldname);
	}
	
	

	return 0;
}
