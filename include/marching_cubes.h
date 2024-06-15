/*
# marching_cubes.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : marching_cubes.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
typedef enum vertex_type{
	normal = 0,
	vertex,
	begin,
	begin_strip,
	end
}vertex_type;

typedef struct vertex_coord{
	float x;
	float y;
	float z;
}vertex_coord;

typedef struct marching_one_vertex{
	vertex_type type;
	vertex_coord coord;

	marching_one_vertex* next;
	marching_one_vertex* previous;
}marching_one_vertex;

typedef struct marching_cubes{
	marching_one_vertex* top;
	marching_one_vertex* current;
	marching_one_vertex* bottom;
}marching_cubes;
