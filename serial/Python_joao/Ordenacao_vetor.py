import random
import datetime

inic = datetime.datetime. now()

n = []
i=0
qtdNb = 1000

while i<=qtdNb:
	rn = random.randint(0,10000)
	n.append (rn)
	i +=1
print (n)
	
i=0
q=1

while (q>=1):
	q=0
	i=0
	while i<qtdNb:
		if (n[i]>n[i+1]):
			aux=n[i]
			n[i]=n[i+1]
			n[i+1]=aux
			q+=1
			print(q)
		i +=1
	
print (q)
print (n)

tempo = datetime.datetime.now() - inic
print (tempo)
			