#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*-------------------------------*/
typedef struct Player
{
	int id;
	char name[10];
} Player;
/*--------------------------------*/
Player* SelectPlayer(void)
{
	static Player p1;
	printf("taper l id de player\n");
	scanf("%d", &p1.id);
	printf("taper le nom de player\n");
	scanf("%s", &p1.name);
	printf("success\n");
	return &p1;
}
/*----------------------------------*/
int main(int argc, char const *argv[])
{
	Player* pGlobal;
	pGlobal=SelectPlayer();
	printf("%s |----> %d |---> %d \n", pGlobal->name, pGlobal->id, 0);
	printf("terminer\n");
	return 0;
}