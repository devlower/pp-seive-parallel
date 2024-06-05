def sieve_of_eratosthene(N,qtd_instrucoes):
    #qtd_instrucoes = 0

    # Lista de numeros primos:
    numbers = []
 
    # Cria-se uma lista referente a todos os inteiros entre 0 e N:
    A = [True] * (N+1)
 
    # Define os numeros 0 e 1 como nao primos:
    A[0] = A[1] = False
 
    # Percorra a lista ate encontrar o primeiro numero primo:
    for value, prime in enumerate(A):
        qtd_instrucoes = qtd_instrucoes + 1

        # O numero eh primo?
        if prime:
            qtd_instrucoes = qtd_instrucoes + 1
            # Retorna o numero primo:
            numbers.append(value)
 
            # Remova da lista todos os multiplos do numero enontrado:
            for i in range(value**2, N+1, value):
                A[i] = False
                qtd_instrucoes = qtd_instrucoes + 1
    
    #print(f'Quantidade de instruções realizadas: ',qtd_instrucoes)            
    return numbers, qtd_instrucoes


#Quantidade de números desejados
n=500000

qtd_instrucoes = 0

import time
# Obtém o valor do tempo atual
start = time.process_time() 

primos = sieve_of_eratosthene(n,qtd_instrucoes)
print(f'Lista numeros primos: ',primos[0])
print(f'Quantidade execuções: ',primos[1])


# Obtém o valor do tempo atual
end = time.process_time()

# Calcula o tempo de execução em segundos
thicks = end - start

# Imprime o tempo de execução
print("O tempo de execução em milissegundos é:", thicks*1000)
