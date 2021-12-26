

horizontal = 0
depth = 0
aim = 0

with open('input.txt', 'r') as data:
	lines = data.readlines()
	for line in lines:
		if 'forward ' in line:
			num = int(line.split()[1])
			horizontal += num
			depth += num * aim
		elif 'down' in line:
			aim += int(line.split()[1])
		elif 'up' in line:
			aim -= int(line.split()[1])
		else:
			raise Error


print(f'horizontal={horizontal}, depth={depth}, aim={aim}')
