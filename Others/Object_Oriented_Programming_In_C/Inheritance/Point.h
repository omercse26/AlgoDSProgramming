/* Point.h*/

extern const void * Point;

void move (void * point,int dx,int dy);

void * new (const void * class, ...);
void delete (void * item);
void draw (const void * self);