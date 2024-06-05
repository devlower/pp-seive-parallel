# Algoritmo que retorna todos os numeros primos entre um intervalo entre zero e um número fornecido. 
# Baseado no algoritmo Crivo de Eratostenes

def primo(list, j,i,n,n_exec):
	for num in list:
		n+=1
		if num%j==0 and num !=j:
			n+=1
			list.remove(num)
	print(f'\nj=',j)
	print(f'lista=',list)
	print(f'Tamanho da lista resultante:',len(list))
	j =list[i+1]
	i+=1
	n_exec.append(n)
	n=0

	if j<=k:
		primo(list,j,i,n,n_exec)


import time
# Obtém o valor do tempo atual
start = time.process_time()


#Quantidade de números
n = 500

#Cria a lista de números		
list = [*range(1, n,1)]
print(f'Lista original:\n',list)
Qtd_numeros = len(list)
print(f'Tamanho lista original=', len(list))

k = int(len(list) ** 0.5)
print(f'Condição de parada (k)=',k)

#remove o número 1 da lista  pois ele não é primo
if list[0] == 1:
		list.remove(list[0])

j=list[0]
i=0
n=0
n_exec =[]

#Chama a função
primo(list,j,i,n,n_exec)

#printa a lista final
print(list)

# print(f'\nQtd itens verificados por passada:\n',n_exec)

soma =0
for w in n_exec:
	soma += w
# print(f'\nQuantidade números:', Qtd_numeros)
# print(f'Soma execuções:', soma)

# Obtém o valor do tempo atual
end = time.process_time()

# Calcula o tempo de execução em segundos
thicks = end - start

# Imprime o tempo de execução
print("O tempo de execução em milissegundos é:", thicks*1000)