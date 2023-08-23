#include<stdio.h>
#include<string.h>
#include"room.h"

struct room* create_room(char *name, char *description){  
 
	char[20] miestnost; 
	strcpy( miestnost, name);  
	struct room miestnost;
   	strcpy( miestnost.name, name);
   	strcpy( miestnost.description, description); 
   
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
	strcpy( room->north, north);
   	strcpy( room->south, south);
   	strcpy( room->east, east);
   	strcpy( room->west, west);
}

void show_room(const struct room* room){
	printf("%s\n",room->description);
	printf("Mozne vychody z miesnosti:\n");
	if(room->north != NULL)
		printf("Sever\n");
	if(room->south != NULL)
		printf("Juh\n");
	if(room->east != NULL)
		printf("Vychod\n");
	if(room->west != NULL)
		printf("zapad\n");
	printf("Vidis:\n");
	printf("%s", room->items);
}

struct room* destroy_room(struct room* room){
	strcpy( room->name, NULL);
   	strcpy( room->description, NULL); 
	strcpy( room->north, NULL);
   	strcpy( room->south, NULL);
   	strcpy( room->east, NULL);
   	strcpy( room->west, NULL);	
}
