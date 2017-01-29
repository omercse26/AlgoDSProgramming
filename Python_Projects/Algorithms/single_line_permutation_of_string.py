c = "omer"
def p(s, n):
	return [s] if n == len(c) else [x for y in [p(i, n+1) for i in [s[0:j]+c[n]+s[j:] for j in xrange(len(s)+1)]] for x in y]

print p ("",0)