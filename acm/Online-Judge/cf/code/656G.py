a,b,c=map(int, raw_input().split())
s=[0 for i in range(b)]
for i in xrange(a):
	y=raw_input()
	for j in xrange(b):
		s[j]+=y[j]=='Y'
l=0
for i in xrange(b):
	l+=s[i]>=c
kitten=0
print l