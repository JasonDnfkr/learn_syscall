#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE (1024 * 1024)

int main() {
	char* some_memory;
	int megs_obtained = 0;
	struct rlimit rlt;
	rlim_t j = RLIM_INFINITY;
	rlim_t k = RLIM_INFINITY;

	getrlimit(RLIMIT_AS, &rlt);

	if (rlt.rlim_cur == RLIM_INFINITY) {
		printf("no limit on virture memory\n");
		exit(0);
	}

	while (1) {
		some_memory = (char*)malloc(CHUNK_SIZE);
		if (some_memory == NULL) {
			printf("no mo memory\n");
			exit(EXIT_FAILURE);
		}

		megs_obtained++;
		printf("now allocated %d Megabytes\n", megs_obtained);
	}

	exit(EXIT_SUCCESS);
}
