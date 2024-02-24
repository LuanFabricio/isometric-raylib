#ifndef QUADTREE_H_
#define QUADTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../types.h"

#define QUADTREE static

QUADTREE bool AABB_contains_point(AABB aabb, Point p);
QUADTREE QuadTree *QuadTree_new(float x, float y, float half_dimension);
QUADTREE void QuadTree_subdivide(QuadTree *root);
QUADTREE bool QuadTree_insert(QuadTree *root, Point p);
QUADTREE void QuadTree_print(const QuadTree *root);

#ifdef QUADTREE_IMPLEMENTATION
QUADTREE QuadTree *QuadTree_new(float x, float y, float half_dimension)
{
	AABB node = {
		.center = {
			.x = x,
			.y = y,
		},
		.half_dimension = half_dimension,
	};

	QuadTree *q_ptr = (QuadTree*) malloc(sizeof(QuadTree));
	q_ptr->node = node;
	q_ptr->points_size = 0;
	for (size_t i = 0; i < NODE_CAPACITY; i++) {
		q_ptr->points[i] = NULL;
	}
	q_ptr->north_west = NULL;
	q_ptr->north_east = NULL;
	q_ptr->south_west = NULL;
	q_ptr->south_east = NULL;

	return q_ptr;
}

QUADTREE bool AABB_contains_point(AABB aabb, Point p)
{
	float left = aabb.center.x - aabb.half_dimension;
	float right = aabb.center.x + aabb.half_dimension;
	float top = aabb.center.y - aabb.half_dimension;
	float bottom = aabb.center.y + aabb.half_dimension;

	return left <= p.x && right >= p.x
		&& top <= p.y && bottom >= p.y;
}

QUADTREE void QuadTree_subdivide(QuadTree *root)
{
	float x, y, half_dimension = root->node.half_dimension;
	x = root->points[0]->x;
	y = root->points[0]->y;
	root->north_west = QuadTree_new(x, y, half_dimension);

	x = root->points[1]->x;
	y = root->points[1]->y;
	root->north_east = QuadTree_new(x, y, half_dimension);

	x = root->points[2]->x;
	y = root->points[2]->y;
	root->south_west = QuadTree_new(x, y, half_dimension);

	x = root->points[3]->x;
	y = root->points[3]->y;
	root->south_east = QuadTree_new(x, y, half_dimension);

	root->points_size = 0;
}

QUADTREE bool QuadTree_insert(QuadTree *root, Point p)
{
	if (!AABB_contains_point(root->node, p)) {
		return false;
	}

	if (root->points_size < NODE_CAPACITY && root->north_west == NULL) {
		Point *p_ptr = (Point*)malloc(sizeof(Point));
		p_ptr->x = p.x;
		p_ptr->y = p.y;

		root->points[root->points_size] = p_ptr;
		root->points_size += 1;
		return true;
	}

	if(root->north_west == NULL) {
		QuadTree_subdivide(root);
	}

	if (QuadTree_insert(root->north_west, p)) return true;
	if (QuadTree_insert(root->north_east, p)) return true;
	if (QuadTree_insert(root->south_west, p)) return true;
	if (QuadTree_insert(root->south_east, p)) return true;

	return true;
}

QUADTREE void QuadTree_print(const QuadTree *root)
{
	printf("Root: { %.2f, %.2f } %.2f\n", root->node.center.x, root->node.center.y, root->node.half_dimension);
	if (root->points_size > 0){
		printf("Points: \n");
	}
	for (size_t i = 0; i < root->points_size; i++) {
		printf("\t[%lu]: ", i);
		Point *p = root->points[i];
		if (p) {
			printf("{ %.2f, %.2f }", p->x, p->y);
		} else {
			printf("NULL");
		}
		printf("\n");
	}

	if (root->north_west) {
		printf("North west:\n");
		QuadTree_print(root->north_west);
	}

	if (root->north_east) {
		printf("North east:\n");
		QuadTree_print(root->north_east);
	}

	if (root->south_west) {
		printf("South west:\n");
		QuadTree_print(root->south_west);
	}

	if (root->south_east) {
		printf("South east:\n");
		QuadTree_print(root->south_east);
	}
}
#endif // QUADTREE_IMPLEMENTATION

#endif // QUADTREE_H_
