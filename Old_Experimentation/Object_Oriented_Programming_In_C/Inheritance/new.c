void draw (const void * self)
{ const struct Class * const * cp = self;
assert(self && * cp && (* cp) —> draw);
(* cp) —> draw(self);
}