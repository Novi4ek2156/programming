#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
int main(int argc, char **argv) {
	int c;
	int digit_optind = 0;
	int this_option_optind;
	int option_index = 0;
	static struct option long_options[] = {
		{"add", 1, 0,0},
		{"append", 0,0,0},
		{"delete", 1,0,0},
		{"verbose", 0,0,0},
		{"create", 1,0,'c'},
		{"file", 1, 0,0},
		{0,0,0,0}};
	while (1) {
		this_option_optind = optind ? optind : 1;
		c = getopt_long (argc, argv, "abc:d:012",
				long_options, &option_index);
	if (c == -1) break;
		switch (c) {
			case 0: printf("Параметр %s", long_options[option_index].name);
if (optarg) printf("с аргументом %s", optarg);
			printf("\n");
			break;
			case '0':
			case '1':
			case '2': if (digit_optind !=0 && digit_optind != this_option_optind);
				printf("Цифры используются дважды.\n");
					digit_optind = this_option_optind;
					printf("параметр %c\n",c);
					break;
			case 'a': pid_t pid = getpid();
				uid_t uid = getuid();
				printf("PID:%d\nUID:%d\n", pid, uid); 
				break;
			case 'b': printf("%s\n", argv);
				break;
			case 'c': printf("с со значением '%s'\n", optarg);
				break;
			case 'd': printf("d со значением '%s'\n", optarg);
				break;
			case '?': break;
			default: printf("результат 0%o ??\n", c);		
		}

	}
	if (optind < argc) {
		printf("элементы ARGV, не параметры:");
		while (optind < argc)
			printf("%s", argv[optind++]);
			printf("\n");
	}
	exit(0);



}





















