#algoritmo que retorna todos os
#numeros primos entre um intervalo. Baseado do algoritmo de Eratostenes

def primo(list, j,i):
	for num in list:
		if num%j==0 and num !=j:
			 list.remove(num)
	print(f'\nj={j}')
	print(f'lista=',list)
	print(f'Tamanho da lista parcial:',len(list))
	j =list[i+1]
	i+=1

	if j<=k:
		primo(list,j,i)
		
#Cria a lista de números		
list = [*range(2, 100,1)]
print(f'Lista original:\n',list)
print(f'Tamanho lista original=', len(list))

k = int(len(list) ** 0.5)

j=list[0]
i=0

print(f'Condição de parada (k)=',k)

#Chama a função
primo(list,j,i)

#printa a lista final
print(f'\nlista num_primos:',list)