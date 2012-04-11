/* 
   Declaration for yamsort function "qsort" style
*/

extern void
yamsort (void *base,   // array for sorting
	size_t nmemb,  // number of items
	size_t size,   // item size
	int (*fpcmp)(const void *, const void *));

