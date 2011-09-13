#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//-----------------------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0
//-----------------------------------------------------------------------------
// STRUCTURES
//-----------------------------------------------------------------------------
struct color_rectangle
{
	unsigned int lx;
	unsigned int ly;
	unsigned int wx;
	unsigned int wy;
	unsigned int color;
};
//-----------------------------------------------------------------------------
struct rect_list_element
{
	struct color_rectangle   rectangle;
	struct rect_list_element *next;
};
//-----------------------------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------------------------
int ParseFirstRectangle(
	struct color_rectangle *rect,
	unsigned int           *N
) {
int	scanf_ret_code;
	// first rectangle
	rect->lx = 0;
	rect->ly = 0;
	rect->color = 1;

	scanf_ret_code = scanf(
		"%d %d %d", 
		&rect->wx, &rect->wy, N
	);
	if (scanf_ret_code < 3)	{
		printf ("Can't recongnize first line\n");
		return FALSE;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
int ParseNextRectangle (struct color_rectangle *rect)
{
int scanf_ret_code;
	scanf_ret_code = scanf (
		"%d %d %d %d %d",
		&rect->lx, &rect->ly,
		&rect->wx, &rect->wy,
		&rect->color
	);
	if (scanf_ret_code < 5) {
		printf ("Can't recognize input line\n");
		return FALSE;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
int AddFirstRectangle (
	struct rect_list_element *head,
	unsigned int             *N
) {
	assert (head == NULL);
	head = (struct rect_list_element *) malloc(sizeof(struct rect_list_element));
	head->next = NULL;
	return ParseFirstRectangle (&head->rectangle, N);
}
//-----------------------------------------------------------------------------
int Rectangle_PointIn(
	unsigned int x,
	unsigned int y,
	struct color_rectangle *rect
) {
	if (x >= rect.lx && x =< rect.wx &&
		y >= rect.ly && x =< rect.wy	
	)
		return TRUE;
	return FALSE;
}
//-----------------------------------------------------------------------------
int Rectangle_IsOverlap(
	struct color_rectangle *rect1,
	struct color_rectangle *rect2
) {
	if (TRUE == Rectangle_PointIn(
			rect1->lx,
			rect1->ly,
			rect2
		))
		return TRUE;
	if (TRUE == Rectangle_PointIn(
			rect1->wx,
			rect1->wy,
			rect2
		))
		return TRUE;
	if (rect1->lx < rect2->lx && rect1->wx > rect2->wx &&
	    rect1->ly < rect2->ly && rect1->wy > rect2->wy 
	)
		return TRUE;
	if (rect2->lx < rect1->lx && rect2->wx > rect1->wx &&
	    rect2->ly < rect1->ly && rect2->wy > rect1->wy 
	)
		return TRUE;
	return FALSE;
}
//-----------------------------------------------------------------------------
int AddNextRectangle (struct rect_list_element *head) 
{
struct rect_list_element *element;
struct rect_list_element *current;
int    ret_code;
	element = (struct rect_list_element *)malloc(sizeof(struct rect_list_element));
	ret_code = ParseNextRectangle (&element->rectangle);
	if (ret_code != TRUE)
		return FALSE;
	current = head;
	while (current->next != NULL)
	{
		if (TRUE != Rectangle_IsOverlap(
			&element->rectangle,
			&current->rectangle
		))
			continue;
		// TODO: add actual rectangle placing code here
		current = current->next;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
int LoadData (struct rect_list_element *list_head)
{
unsigned int           N;
unsigned int           i;
int                    ret_code;
	ret_code = AddFirstRectangle (list_head, &N);
	if (ret_code != TRUE)
		return FALSE;
	for (i = 0; i < N; i++) {
		ret_code = AddNextRectangle (list_head);
		if (ret_code != TRUE)
			return FALSE;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
void SortRectangleList(struct rect_list_element *head)
{

}
//-----------------------------------------------------------------------------
void DeleteRectangleList (struct rect_list_element *rect_list)
{
struct rect_list_element *current;
struct rect_list_element *next;
	if (rect_list == NULL)
		return;
	current = rect_list;
	while (current->next != NULL)
	{
		next = rect_list->next;
		free(current);
		current = next;
	}
}
//-----------------------------------------------------------------------------
// MAIN
//-----------------------------------------------------------------------------
int main (int argc, char *argv[])
{
struct rect_list_element *list_head;
int                      ret_code;
	list_head = NULL;
	ret_code = LoadData (list_head);
	if (ret_code != TRUE)
		return -1;
	SortRectangleList (list_head);
	DeleteRectangleList (list_head);
	return 0;
}
