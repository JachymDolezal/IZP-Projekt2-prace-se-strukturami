n:
	gcc -std=c99 -Wall -Wextra -Werror newsetcal.c -o newsetcal && ./newsetcal set.txt
v:
	gcc -std=c99 -Wall -Wextra -Werror newsetcal.c -o newsetcal && valgrind ./newsetcal set.txt