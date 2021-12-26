

pos = [0, 0]


with open('input.txt', 'r') as data:
	lines = data.readlines()
	for line in lines:
		if 'forward ' in line:
			pos[0] += int(line.split()[1])
		elif 'down' in line:
			pos[1] += int(line.split()[1])
		elif 'up' in line:
			pos[1] -= int(line.split()[1])
		else:
			raise Error


print(pos)
