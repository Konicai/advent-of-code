
gamma = []
epsilon = []

lines = []
with open('input.txt', 'r') as data:
	for line in data:
		lines.append(line.strip())

# Amount of bits per word
length = len(lines[0])

for i in range(length):
	count_0 = 0
	count_1 = 0
	for word in lines:
		bit = word[i]
		if bit == '0':
			count_0 += 1
		elif bit == '1':
			count_1 += 1
		else:
			raise Exception(f'Got {bit} instead of a bit on row {count_0 + count_1}, column {i}')

	if count_0 > count_1:
		gamma.append('0')
		epsilon.append('1')
	else:
		gamma.append('1')
		epsilon.append('0')



gamma = int(''.join(gamma), 2)
epsilon = int(''.join(epsilon), 2)
print(f'power consumption={gamma * epsilon}')

